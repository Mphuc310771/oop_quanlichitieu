#pragma once
#include <vector>
#include <mutex>
#include <string>
#include "Expense.h"

class ExpenseManager {
private:
    std::vector<Expense> items;
    int nextId = 1;
    std::mutex mtx;
    std::string storageFile;

    bool save_unlocked();
    void load();

public:
    ExpenseManager(const std::string &file);

    std::vector<Expense> all();
    Expense add(const Expense &e);
    bool edit(int id, const Expense &e);
    bool remove(int id);
};
