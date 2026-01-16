#include "../include/Utils.h"
#include "../include/GlobalContext.h"
#include "../include/HtmlContent.h"
#include <random>
#include <iostream>

GlobalContext g_ctx;

// Embedded HTML content definitions
const char *LOGIN_HTML = R"RAWHTML(<!DOCTYPE html>
<html lang="vi">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Đăng nhập - Quản lý chi tiêu</title>
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;500;700&display=swap" rel="stylesheet">
<style>
* { margin: 0; padding: 0; box-sizing: border-box; }
body {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    font-family: 'Roboto', sans-serif;
    display: flex;
    align-items: center;
    justify-content: center;
    min-height: 100vh;
    color: #202124;
}
.login-container {
    background: #fff;
    padding: 48px 40px 36px;
    border-radius: 16px;
    width: 100%;
    max-width: 420px;
    box-shadow: 0 20px 60px rgba(0,0,0,0.3);
    text-align: center;
}
.logo-area { margin-bottom: 16px; }
.app-icon { width: 56px; height: 56px; fill: #667eea; }
h1 { font-size: 28px; font-weight: 500; margin-bottom: 8px; color: #202124; }
.sub-title { font-size: 15px; color: #5f6368; margin-bottom: 32px; }
.form-group { position: relative; margin-bottom: 24px; text-align: left; }
.custom-input {
    width: 100%;
    padding: 16px;
    border: 2px solid #e0e0e0;
    border-radius: 12px;
    font-size: 16px;
    outline: none;
    transition: all 0.3s;
    background: #fafafa;
}
.custom-input:focus { border-color: #667eea; background: #fff; box-shadow: 0 0 0 4px rgba(102,126,234,0.1); }
.form-label {
    position: absolute; left: 14px; top: 16px;
    padding: 0 6px; background: #fafafa;
    color: #5f6368; font-size: 16px;
    transition: all 0.3s; pointer-events: none;
}
.custom-input:focus ~ .form-label,
.custom-input:not(:placeholder-shown) ~ .form-label {
    top: -10px; font-size: 12px; color: #667eea; background: #fff; font-weight: 500;
}
.btn-login {
    width: 100%;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    font-weight: 500;
    font-size: 16px;
    padding: 16px;
    border: none;
    border-radius: 12px;
    cursor: pointer;
    transition: all 0.3s;
    margin-top: 8px;
}
.btn-login:hover { transform: translateY(-2px); box-shadow: 0 8px 25px rgba(102,126,234,0.4); }
.btn-login:disabled { opacity: 0.7; cursor: default; transform: none; }
.divider { display: flex; align-items: center; margin: 28px 0; color: #9e9e9e; font-size: 14px; }
.divider::before, .divider::after { content: ''; flex: 1; height: 1px; background: #e0e0e0; }
.divider span { padding: 0 16px; }
.btn-register {
    width: 100%;
    background: #fff;
    color: #667eea;
    font-weight: 500;
    font-size: 15px;
    padding: 14px;
    border: 2px solid #667eea;
    border-radius: 12px;
    cursor: pointer;
    transition: all 0.3s;
    text-decoration: none;
    display: block;
}
.btn-register:hover { background: #667eea; color: #fff; }
#msg { text-align: left; font-size: 13px; margin-top: 8px; min-height: 20px; display: flex; align-items: center; }
#msg.error { color: #d93025; }
#msg.error svg { fill: #d93025; margin-right: 8px; }
@media (max-width: 500px) {
    body { background: #fff; }
    .login-container { box-shadow: none; padding: 24px; }
}
</style>
</head>
<body>
<div class="login-container">
    <div class="logo-area">
        <svg class="app-icon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
            <path d="M21 18v1c0 1.1-.9 2-2 2H5a2 2 0 01-2-2V5a2 2 0 012-2h14c1.1 0 2 .9 2 2v1h-9a2 2 0 00-2 2v8a2 2 0 002 2h9zm-9-2h10V8H12v8zm4-2.5c-.83 0-1.5-.67-1.5-1.5s.67-1.5 1.5-1.5 1.5.67 1.5 1.5-.67 1.5-1.5 1.5z"/>
        </svg>
    </div>
    <h1>Đăng nhập</h1>
    <div class="sub-title">Quản lý chi tiêu cá nhân</div>
    <div class="form-group">
        <input id="user" type="text" class="custom-input" placeholder=" " required>
        <label for="user" class="form-label">Tên đăng nhập</label>
    </div>
    <div class="form-group">
        <input id="pass" type="password" class="custom-input" placeholder=" " required>
        <label for="pass" class="form-label">Mật khẩu</label>
    </div>
    <div id="msg"></div>
    <button class="btn-login" id="submitBtn" onclick="login()">Đăng nhập</button>
    <div class="divider"><span>hoặc</span></div>
    <a href="/register.html" class="btn-register">Tạo tài khoản mới</a>
</div>
<script>
async function login() {
    const userInp = document.getElementById('user');
    const passInp = document.getElementById('pass');
    const user = userInp.value.trim();
    const pass = passInp.value.trim();
    const msgEl = document.getElementById('msg');
    const btn = document.getElementById('submitBtn');
    msgEl.innerHTML = ''; msgEl.className = '';
    if (!user) { showError('Vui lòng nhập tên đăng nhập.'); return; }
    if (!pass) { showError('Vui lòng nhập mật khẩu.'); return; }
    btn.innerText = 'Đang xử lý...'; btn.disabled = true;
    try {
        const res = await fetch('/login', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ username: user, password: pass })
        });
        if (res.ok) { window.location.href = '/'; }
        else {
            const err = await res.json().catch(() => ({}));
            showError(err.error || 'Sai thông tin đăng nhập.');
            btn.innerText = 'Đăng nhập'; btn.disabled = false;
        }
    } catch (e) {
        showError('Lỗi kết nối máy chủ.');
        btn.innerText = 'Đăng nhập'; btn.disabled = false;
    }
}
function showError(text) {
    const msgEl = document.getElementById('msg');
    msgEl.className = 'error';
    msgEl.innerHTML = `<svg xmlns="http://www.w3.org/2000/svg" height="16" width="16" viewBox="0 0 24 24"><path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm1 15h-2v-2h2v2zm0-4h-2V7h2v6z"/></svg>${text}`;
}
document.getElementById('pass').addEventListener('keydown', (e) => { if (e.key === 'Enter') login(); });
document.getElementById('user').addEventListener('keydown', (e) => { if (e.key === 'Enter') login(); });
</script>
</body>
</html>)RAWHTML";

const char *REGISTER_HTML = R"RAWHTML(<!DOCTYPE html>
<html lang="vi">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Đăng ký - Quản lý chi tiêu</title>
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;500;700&display=swap" rel="stylesheet">
<style>
* { margin: 0; padding: 0; box-sizing: border-box; }
body {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    font-family: 'Roboto', sans-serif;
    display: flex;
    align-items: center;
    justify-content: center;
    min-height: 100vh;
    padding: 20px;
    color: #202124;
}
.register-container {
    background: #fff;
    padding: 40px;
    border-radius: 16px;
    width: 100%;
    max-width: 480px;
    box-shadow: 0 20px 60px rgba(0,0,0,0.3);
}
.header { text-align: center; margin-bottom: 32px; }
.logo-area { margin-bottom: 16px; }
.app-icon { width: 56px; height: 56px; fill: #667eea; }
h1 { font-size: 28px; font-weight: 500; margin-bottom: 8px; color: #202124; }
.sub-title { font-size: 15px; color: #5f6368; }
.form-group { margin-bottom: 20px; }
.form-group label { display: block; font-size: 14px; font-weight: 500; color: #202124; margin-bottom: 8px; }
.form-group input {
    width: 100%;
    padding: 14px 16px;
    border: 2px solid #e0e0e0;
    border-radius: 10px;
    font-size: 15px;
    outline: none;
    transition: all 0.3s;
    background: #fafafa;
}
.form-group input:focus { border-color: #667eea; background: #fff; box-shadow: 0 0 0 4px rgba(102,126,234,0.1); }
.form-group input.error { border-color: #d93025; }
.form-group input.success { border-color: #1e8e3e; }
.form-group .hint { font-size: 12px; color: #5f6368; margin-top: 6px; }
.form-group .error-text { font-size: 12px; color: #d93025; margin-top: 6px; display: none; }
.form-group .error-text.show { display: block; }
.password-requirements {
    background: #f8f9fa;
    border-radius: 10px;
    padding: 16px;
    margin-bottom: 24px;
}
.password-requirements h4 { font-size: 13px; font-weight: 500; color: #202124; margin-bottom: 12px; }
.requirement { display: flex; align-items: center; font-size: 13px; color: #5f6368; margin-bottom: 8px; transition: all 0.3s; }
.requirement:last-child { margin-bottom: 0; }
.requirement svg { width: 18px; height: 18px; margin-right: 10px; fill: #9e9e9e; transition: all 0.3s; }
.requirement.valid { color: #1e8e3e; }
.requirement.valid svg { fill: #1e8e3e; }
.btn-register {
    width: 100%;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    font-weight: 500;
    font-size: 16px;
    padding: 16px;
    border: none;
    border-radius: 12px;
    cursor: pointer;
    transition: all 0.3s;
    margin-bottom: 20px;
}
.btn-register:hover { transform: translateY(-2px); box-shadow: 0 8px 25px rgba(102,126,234,0.4); }
.btn-register:disabled { opacity: 0.6; cursor: default; transform: none; box-shadow: none; }
.login-link { text-align: center; font-size: 14px; color: #5f6368; }
.login-link a { color: #667eea; text-decoration: none; font-weight: 500; }
.login-link a:hover { text-decoration: underline; }
#msg { text-align: center; font-size: 14px; padding: 12px; border-radius: 8px; margin-bottom: 20px; display: none; }
#msg.error { display: block; background: #fce8e6; color: #d93025; }
#msg.success { display: block; background: #e6f4ea; color: #1e8e3e; }
@media (max-width: 500px) {
    body { background: #fff; padding: 0; }
    .register-container { box-shadow: none; padding: 24px; border-radius: 0; }
}
</style>
</head>
<body>
<div class="register-container">
    <div class="header">
        <div class="logo-area">
            <svg class="app-icon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
                <path d="M21 18v1c0 1.1-.9 2-2 2H5a2 2 0 01-2-2V5a2 2 0 012-2h14c1.1 0 2 .9 2 2v1h-9a2 2 0 00-2 2v8a2 2 0 002 2h9zm-9-2h10V8H12v8zm4-2.5c-.83 0-1.5-.67-1.5-1.5s.67-1.5 1.5-1.5 1.5.67 1.5 1.5-.67 1.5-1.5 1.5z"/>
            </svg>
        </div>
        <h1>Tạo tài khoản</h1>
        <div class="sub-title">Đăng ký để quản lý chi tiêu cá nhân</div>
    </div>
    <div id="msg"></div>
    <form id="registerForm" onsubmit="return handleSubmit(event)">
        <div class="form-group">
            <label for="username">Tên đăng nhập *</label>
            <input type="text" id="username" placeholder="Ít nhất 3 ký tự" required>
            <div class="error-text" id="usernameError"></div>
        </div>
        <div class="form-group">
            <label for="email">Email *</label>
            <input type="email" id="email" placeholder="example@email.com" required>
            <div class="error-text" id="emailError"></div>
        </div>
        <div class="form-group">
            <label for="password">Mật khẩu *</label>
            <input type="password" id="password" placeholder="Tạo mật khẩu mạnh" required oninput="checkPassword()">
        </div>
        <div class="password-requirements">
            <h4>Yêu cầu mật khẩu:</h4>
            <div class="requirement" id="req-length">
                <svg viewBox="0 0 24 24"><path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm-2 15l-5-5 1.41-1.41L10 14.17l7.59-7.59L19 8l-9 9z"/></svg>
                Ít nhất 8 ký tự
            </div>
            <div class="requirement" id="req-upper">
                <svg viewBox="0 0 24 24"><path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm-2 15l-5-5 1.41-1.41L10 14.17l7.59-7.59L19 8l-9 9z"/></svg>
                Có chữ cái viết hoa (A-Z)
            </div>
            <div class="requirement" id="req-lower">
                <svg viewBox="0 0 24 24"><path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm-2 15l-5-5 1.41-1.41L10 14.17l7.59-7.59L19 8l-9 9z"/></svg>
                Có chữ cái viết thường (a-z)
            </div>
            <div class="requirement" id="req-number">
                <svg viewBox="0 0 24 24"><path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm-2 15l-5-5 1.41-1.41L10 14.17l7.59-7.59L19 8l-9 9z"/></svg>
                Có ít nhất 1 chữ số (0-9)
            </div>
        </div>
        <div class="form-group">
            <label for="confirmPassword">Xác nhận mật khẩu *</label>
            <input type="password" id="confirmPassword" placeholder="Nhập lại mật khẩu" required oninput="checkConfirmPassword()">
            <div class="error-text" id="confirmError"></div>
        </div>
        <button type="submit" class="btn-register" id="submitBtn">Đăng ký</button>
    </form>
    <div class="login-link">Đã có tài khoản? <a href="/login.html">Đăng nhập</a></div>
</div>
<script>
function checkPassword() {
    const pass = document.getElementById('password').value;
    const reqLength = document.getElementById('req-length');
    const reqUpper = document.getElementById('req-upper');
    const reqLower = document.getElementById('req-lower');
    const reqNumber = document.getElementById('req-number');
    
    reqLength.classList.toggle('valid', pass.length >= 8);
    reqUpper.classList.toggle('valid', /[A-Z]/.test(pass));
    reqLower.classList.toggle('valid', /[a-z]/.test(pass));
    reqNumber.classList.toggle('valid', /[0-9]/.test(pass));
    
    checkConfirmPassword();
}
function checkConfirmPassword() {
    const pass = document.getElementById('password').value;
    const confirm = document.getElementById('confirmPassword').value;
    const confirmInput = document.getElementById('confirmPassword');
    const confirmError = document.getElementById('confirmError');
    
    if (confirm && pass !== confirm) {
        confirmInput.classList.add('error');
        confirmInput.classList.remove('success');
        confirmError.textContent = 'Mật khẩu không khớp';
        confirmError.classList.add('show');
    } else if (confirm && pass === confirm) {
        confirmInput.classList.remove('error');
        confirmInput.classList.add('success');
        confirmError.classList.remove('show');
    } else {
        confirmInput.classList.remove('error', 'success');
        confirmError.classList.remove('show');
    }
}
function isValidEmail(email) {
    return /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email);
}
function isValidPassword(pass) {
    return pass.length >= 8 && /[A-Z]/.test(pass) && /[a-z]/.test(pass) && /[0-9]/.test(pass);
}
async function handleSubmit(e) {
    e.preventDefault();
    const username = document.getElementById('username').value.trim();
    const email = document.getElementById('email').value.trim();
    const password = document.getElementById('password').value;
    const confirmPassword = document.getElementById('confirmPassword').value;
    const msgEl = document.getElementById('msg');
    const btn = document.getElementById('submitBtn');
    
    // Reset errors
    msgEl.className = ''; msgEl.textContent = '';
    document.querySelectorAll('.error-text').forEach(el => { el.classList.remove('show'); el.textContent = ''; });
    document.querySelectorAll('input').forEach(el => el.classList.remove('error'));
    
    // Validate
    let hasError = false;
    if (username.length < 3) {
        document.getElementById('username').classList.add('error');
        document.getElementById('usernameError').textContent = 'Tên đăng nhập phải có ít nhất 3 ký tự';
        document.getElementById('usernameError').classList.add('show');
        hasError = true;
    }
    if (!isValidEmail(email)) {
        document.getElementById('email').classList.add('error');
        document.getElementById('emailError').textContent = 'Email không hợp lệ';
        document.getElementById('emailError').classList.add('show');
        hasError = true;
    }
    if (!isValidPassword(password)) {
        msgEl.className = 'error';
        msgEl.textContent = 'Mật khẩu chưa đáp ứng đủ yêu cầu';
        hasError = true;
    }
    if (password !== confirmPassword) {
        document.getElementById('confirmPassword').classList.add('error');
        document.getElementById('confirmError').textContent = 'Mật khẩu xác nhận không khớp';
        document.getElementById('confirmError').classList.add('show');
        hasError = true;
    }
    if (hasError) return false;
    
    btn.disabled = true;
    btn.textContent = 'Đang xử lý...';
    
    try {
        const res = await fetch('/register', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ username, email, password, confirmPassword })
        });
        const data = await res.json().catch(() => ({}));
        if (res.ok) {
            msgEl.className = 'success';
            msgEl.textContent = 'Đăng ký thành công! Đang chuyển đến trang đăng nhập...';
            setTimeout(() => { window.location.href = '/login.html'; }, 2000);
        } else {
            msgEl.className = 'error';
            msgEl.textContent = data.error || 'Đăng ký thất bại';
            btn.disabled = false;
            btn.textContent = 'Đăng ký';
        }
    } catch (err) {
        msgEl.className = 'error';
        msgEl.textContent = 'Lỗi kết nối máy chủ';
        btn.disabled = false;
        btn.textContent = 'Đăng ký';
    }
    return false;
}
</script>
</body>
</html>)RAWHTML";

std::string randomToken() {
    static const char alphanum[] =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string s(32, '0');
    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<> dist(0, sizeof(alphanum) - 2);
    for (auto &c : s)
        c = alphanum[dist(rng)];
    return s;
}

std::string getUsernameFromSession(const Request &req) {
    auto cookie = req.get_header_value("Cookie");
    if (cookie.empty())
        return "";
    auto pos = cookie.find("session=");
    if (pos == std::string::npos)
        return "";

    std::string sid_part = cookie.substr(pos + 8);
    auto end_pos = sid_part.find(';');
    std::string sid =
        (end_pos == std::string::npos) ? sid_part : sid_part.substr(0, end_pos);

    std::lock_guard<std::mutex> lk(g_ctx.mtx);
    if (g_ctx.sessions.count(sid)) {
        return g_ctx.sessions[sid];
    }
    return "";
}

bool isValidSession(const Request &req) {
    return !getUsernameFromSession(req).empty();
}

ExpenseManager &get_manager_for_user(const std::string &user) {
    std::string clean_user = sanitize_filename(user);
    std::lock_guard<std::mutex> lk(g_ctx.mtx);
    if (!g_ctx.userManagers.count(clean_user)) {
        std::string path = "data/" + clean_user + "_expenses.json";
        g_ctx.userManagers[clean_user] = std::make_unique<ExpenseManager>(path);
    }
    return *g_ctx.userManagers[clean_user];
}

void set_cors(Response &res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods",
                   "GET, POST, PUT, DELETE, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type, Cookie");
    res.set_header("Access-Control-Allow-Credentials", "true");
    res.set_header("Content-Type", "application/json");
}

void openBrowser(const std::string &url) {
#ifdef _WIN32
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOW);
#elif __linux__
    system(("xdg-open " + url).c_str());
#elif __APPLE__
    system(("open " + url).c_str());
#endif
}

std::string sanitize_filename(const std::string &input) {
    std::string sanitized;
    for (char c : input) {
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '-') {
            sanitized += c;
        }
    }
    return sanitized;
}

#ifdef _WIN32
std::wstring utf8_to_wstring(const std::string &str) {
    if (str.empty())
        return std::wstring();
    int size_needed =
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &wstr[0],
                        size_needed);
    return wstr;
}
#endif

void showMessageBox(const std::string &title, const std::string &message) {
#ifdef _WIN32
    std::wstring wtitle = utf8_to_wstring(title);
    std::wstring wmessage = utf8_to_wstring(message);
    MessageBoxW(NULL, wmessage.c_str(), wtitle.c_str(),
                MB_OK | MB_ICONINFORMATION);
#else
    std::cout << "[" << title << "] " << message << std::endl;
#endif
}
