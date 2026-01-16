#include "../include/ServerSetup.h"
#include "../include/Utils.h"
#include <thread>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
#ifdef _WIN32
    FreeConsole();
#endif
    
    // Ensure data directory exists
    fs::create_directories("data");

    // Ensure users.json exists
    ensureUsersFile();

    Server svr;
    setupServer(svr);

    std::thread server_thread([&]() { svr.listen("127.0.0.1", 8080); });

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    openBrowser("http://127.0.0.1:8080");

    showMessageBox("Expense Manager", "Ứng dụng đang chạy!\n\n"
                                      "Truy cập: http://127.0.0.1:8080\n"
                                      "Đóng cửa sổ này để thoát ứng dụng.\n\n"
                                      "Tài khoản mặc định:\n"
                                      "- admin / admin\n"
                                      "- user / 123456");

    server_thread.join();

    return 0;
}
