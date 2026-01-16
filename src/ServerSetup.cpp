#include "../include/ServerSetup.h"
#include "../include/Utils.h"
#include "../include/GlobalContext.h"
#include "../include/HtmlContent.h"
#include "../include/Expense.h"
#include <fstream>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

void ensureUsersFile() {
    if (!fs::exists("users.json")) {
        json defaultUsers = json::array();
        defaultUsers.push_back({{"username", "admin"}, {"password", "admin"}});
        defaultUsers.push_back({{"username", "user"}, {"password", "123456"}});
        std::ofstream out("users.json");
        out << std::setw(2) << defaultUsers;
        out.close();
    }
}

void setupServer(Server &svr) {
    // Login endpoint
    svr.Post("/login", [&](const Request &req, Response &res) {
        set_cors(res);
        try {
            auto j = json::parse(req.body);
            std::string user = j["username"];
            std::string pass = j["password"];

            std::ifstream in("users.json");
            if (!in.is_open()) {
                res.status = 500;
                res.set_content(R"({"error":"User database not found"})",
                                "application/json");
                return;
            }
            json arr;
            in >> arr;
            in.close();

            bool ok = false;
            for (auto &u : arr) {
                if (u["username"] == user && u["password"] == pass) {
                    ok = true;
                    break;
                }
            }

            if (!ok) {
                res.status = 401;
                res.set_content(R"({"error":"Invalid credentials"})",
                                "application/json");
                return;
            }

            std::string sid = randomToken();
            {
                std::lock_guard<std::mutex> lk(g_ctx.mtx);
                g_ctx.sessions[sid] = user;
            }

            res.set_header("Set-Cookie", "session=" + sid + "; Path=/; HttpOnly");
            res.status = 200;
            res.set_content(R"({"ok":true})", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content(R"({"error":"Invalid request"})", "application/json");
        }
    });

    // Register endpoint
    svr.Post("/register", [&](const Request &req, Response &res) {
        set_cors(res);
        try {
            auto j = json::parse(req.body);
            std::string user = j.value("username", "");
            std::string email = j.value("email", "");
            std::string pass = j.value("password", "");
            std::string confirmPass = j.value("confirmPassword", "");

            // Validate username
            if (user.empty()) {
                res.status = 400;
                res.set_content(R"({"error":"Vui lòng nhập tên đăng nhập"})", "application/json");
                return;
            }
            if (user.length() < 3) {
                res.status = 400;
                res.set_content(R"({"error":"Tên đăng nhập phải có ít nhất 3 ký tự"})", "application/json");
                return;
            }

            // Validate email
            if (email.empty()) {
                res.status = 400;
                res.set_content(R"({"error":"Vui lòng nhập email"})", "application/json");
                return;
            }
            // Simple email validation
            if (email.find('@') == std::string::npos || email.find('.') == std::string::npos) {
                res.status = 400;
                res.set_content(R"({"error":"Email không hợp lệ"})", "application/json");
                return;
            }

            // Validate password
            if (pass.empty()) {
                res.status = 400;
                res.set_content(R"({"error":"Vui lòng nhập mật khẩu"})", "application/json");
                return;
            }

            // Complex password validation
            if (pass.length() < 8) {
                res.status = 400;
                res.set_content(R"({"error":"Mật khẩu phải có ít nhất 8 ký tự"})", "application/json");
                return;
            }
            bool hasUpper = false, hasLower = false, hasDigit = false;
            for (char c : pass) {
                if (std::isupper(c)) hasUpper = true;
                if (std::islower(c)) hasLower = true;
                if (std::isdigit(c)) hasDigit = true;
            }
            if (!hasUpper || !hasLower || !hasDigit) {
                res.status = 400;
                res.set_content(R"({"error":"Mật khẩu phải có chữ hoa, chữ thường và số"})", "application/json");
                return;
            }

            // Validate confirm password
            if (pass != confirmPass) {
                res.status = 400;
                res.set_content(R"({"error":"Mật khẩu xác nhận không khớp"})", "application/json");
                return;
            }

            std::ifstream in("users.json");
            json arr = json::array();
            if (in.is_open()) {
                try {
                    in >> arr;
                } catch (...) {
                    arr = json::array();
                }
                in.close();
            }

            // Check if username or email already exists
            for (auto &u : arr) {
                if (u.value("username", "") == user) {
                    res.status = 409;
                    res.set_content(R"({"error":"Tên đăng nhập đã tồn tại"})", "application/json");
                    return;
                }
                if (u.contains("email") && u["email"] == email) {
                    res.status = 409;
                    res.set_content(R"({"error":"Email đã được sử dụng"})", "application/json");
                    return;
                }
            }

            // Add new user with email
            arr.push_back({{"username", user}, {"email", email}, {"password", pass}});

            std::ofstream out("users.json");
            if (!out.is_open()) {
                res.status = 500;
                res.set_content(R"({"error":"Không thể lưu người dùng"})", "application/json");
                return;
            }
            out << std::setw(2) << arr;
            out.close();

            res.status = 201;
            res.set_content(R"({"ok":true})", "application/json");
        } catch (...) {
            res.status = 400;
            res.set_content(R"({"error":"Yêu cầu không hợp lệ"})", "application/json");
        }
    });

    // Logout endpoint
    svr.Post("/logout", [&](const Request &req, Response &res) {
        set_cors(res);
        auto cookie = req.get_header_value("Cookie");
        auto pos = cookie.find("session=");
        if (pos != std::string::npos) {
            std::string sid_part = cookie.substr(pos + 8);
            auto end_pos = sid_part.find(';');
            std::string sid = (end_pos == std::string::npos)
                                  ? sid_part
                                  : sid_part.substr(0, end_pos);

            std::lock_guard<std::mutex> lk(g_ctx.mtx);
            g_ctx.sessions.erase(sid);
        }
        res.set_header("Set-Cookie", "session=; Path=/; Max-Age=0; HttpOnly");
        res.status = 200;
        res.set_content(R"({"ok":true})", "application/json");
    });

    // Home page - serve embedded HTML
    svr.Get("/", [&](const Request &req, Response &res) {
        if (!isValidSession(req)) {
            res.set_redirect("/login.html");
            return;
        }
        res.set_content(INDEX_HTML, "text/html; charset=utf-8");
    });

    // Login page - serve embedded HTML
    svr.Get("/login.html", [&](const Request &req, Response &res) {
        res.set_content(LOGIN_HTML, "text/html; charset=utf-8");
    });

    // Register page - serve embedded HTML
    svr.Get("/register.html", [&](const Request &req, Response &res) {
        res.set_content(REGISTER_HTML, "text/html; charset=utf-8");
    });

    // API endpoints
    svr.Options(R"(/.*)", [&](const Request &req, Response &res) {
        set_cors(res);
        res.status = 200;
    });

    svr.Get("/api/expenses", [&](const Request &req, Response &res) {
        set_cors(res);
        std::string user = getUsernameFromSession(req);
        if (user.empty()) {
            res.status = 401;
            return;
        }
        auto &mgr = get_manager_for_user(user);
        json arr = json::array();
        for (auto &e : mgr.all())
            arr.push_back(e.to_json());
        res.set_content(arr.dump(), "application/json");
    });

    svr.Post("/api/expenses", [&](const Request &req, Response &res) {
        set_cors(res);
        std::string user = getUsernameFromSession(req);
        if (user.empty()) {
            res.status = 401;
            return;
        }
        auto &mgr = get_manager_for_user(user);
        json j = json::parse(req.body);
        Expense e = Expense::from_json(j);
        if (e.title.empty())
            e.title = "(không tiêu đề)";
        Expense created = mgr.add(e);
        res.status = 201;
        res.set_content(created.to_json().dump(), "application/json");
    });

    svr.Put(R"(/api/expenses/(\d+))", [&](const Request &req, Response &res) {
        set_cors(res);
        std::string user = getUsernameFromSession(req);
        if (user.empty()) {
            res.status = 401;
            return;
        }
        auto &mgr = get_manager_for_user(user);
        int id = std::stoi(req.matches[1]);
        json j = json::parse(req.body);
        Expense e = Expense::from_json(j);
        bool ok = mgr.edit(id, e);
        if (ok)
            res.set_content(R"({"ok":true})", "application/json");
        else {
            res.status = 404;
            res.set_content(R"({"error":"not found"})", "application/json");
        }
    });

    svr.Delete(R"(/api/expenses/(\d+))", [&](const Request &req, Response &res) {
        set_cors(res);
        std::string user = getUsernameFromSession(req);
        if (user.empty()) {
            res.status = 401;
            return;
        }
        auto &mgr = get_manager_for_user(user);
        int id = std::stoi(req.matches[1]);
        bool ok = mgr.remove(id);
        if (ok)
            res.set_content(R"({"ok":true})", "application/json");
        else {
            res.status = 404;
            res.set_content(R"({"error":"not found"})", "application/json");
        }
    });
}
