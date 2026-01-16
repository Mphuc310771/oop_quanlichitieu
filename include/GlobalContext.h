#pragma once
#include <map>
#include <string>
#include <memory>
#include <mutex>
#include "ExpenseManager.h"

struct GlobalContext {
    std::map<std::string, std::string> sessions;
    std::map<std::string, std::unique_ptr<ExpenseManager>> userManagers;
    std::mutex mtx;
};

extern GlobalContext g_ctx;
