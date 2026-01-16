#pragma once
#include <string>
#include "../external/json.hpp" // Adjust path if needed, assuming external is in root

using json = nlohmann::json;

struct Expense {
    int id = 0;
    std::string title;
    double amount = 0.0;
    std::string category;
    std::string date;

    json to_json() const;
    static Expense from_json(const json &j);
};
