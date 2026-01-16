#include "../include/Expense.h"

json Expense::to_json() const {
    return json{{"id", id},
                {"title", title},
                {"amount", amount},
                {"category", category},
                {"date", date}};
}

Expense Expense::from_json(const json &j) {
    Expense e;
    e.id = j.value("id", 0);
    e.title = j.value("title", "");
    e.amount = j.value("amount", 0.0);
    e.category = j.value("category", "");
    e.date = j.value("date", "");
    return e;
}
