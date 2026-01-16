#pragma once
#include <string>
#include "../external/httplib.h"
#include "ExpenseManager.h"

using namespace httplib;

std::string randomToken();
std::string sanitize_filename(const std::string &input);
void openBrowser(const std::string &url);
void showMessageBox(const std::string &title, const std::string &message);

#ifdef _WIN32
#include <windows.h>
std::wstring utf8_to_wstring(const std::string &str);
#endif

std::string getUsernameFromSession(const Request &req);
bool isValidSession(const Request &req);
ExpenseManager &get_manager_for_user(const std::string &user);
void set_cors(Response &res);
