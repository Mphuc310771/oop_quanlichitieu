#include "../include/ExpenseManager.h"
#include "../include/CustomException.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

ExpenseManager::ExpenseManager(const std::string &file) : storageFile(file) { load(); }

std::vector<Expense> ExpenseManager::all() {
    std::lock_guard<std::mutex> lk(mtx);
    return items;
}

Expense ExpenseManager::add(const Expense &e) {
    std::lock_guard<std::mutex> lk(mtx);
    Expense copy = e;
    copy.id = nextId++;
    items.push_back(copy);
    save_unlocked();
    return copy;
}

bool ExpenseManager::edit(int id, const Expense &e) {
    std::lock_guard<std::mutex> lk(mtx);
    for (auto &it : items) {
        if (it.id == id) {
            it.title = e.title;
            it.amount = e.amount;
            it.category = e.category;
            it.date = e.date;
            save_unlocked();
            return true;
        }
    }
    return false;
}

bool ExpenseManager::remove(int id) {
    std::lock_guard<std::mutex> lk(mtx);
    auto it = std::remove_if(items.begin(), items.end(),
                             [&](const Expense &x) { return x.id == id; });
    if (it != items.end()) {
        items.erase(it, items.end());
        save_unlocked();
        return true;
    }
    return false;
}

bool ExpenseManager::save_unlocked() {
    json arr = json::array();
    for (auto &e : items)
        arr.push_back(e.to_json());
    fs::create_directories(fs::path(storageFile).parent_path());
    std::ofstream ofs(storageFile + ".tmp");
    if (!ofs) {
        // Minh họa ném ngoại lệ tự định nghĩa
        throw FileException("Lỗi: Không thể mở file để ghi: " + storageFile);
    }
    ofs << std::setw(2) << arr;
    ofs.close();
    std::error_code ec;
    fs::rename(storageFile + ".tmp", storageFile, ec);
    return !ec;
}

void ExpenseManager::load() {
    if (!fs::exists(storageFile))
        return;
    std::ifstream ifs(storageFile);
    if (!ifs)
        return;
    json arr;
    try {
        ifs >> arr;
    } catch (...) {
        return;
    }
    items.clear();
    nextId = 1;
    for (auto &v : arr) {
        Expense e = Expense::from_json(v);
        items.push_back(e);
        if (e.id >= nextId)
            nextId = e.id + 1;
    }
}
