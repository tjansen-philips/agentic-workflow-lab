#ifndef TASK_H
#define TASK_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Task {
private:
    int id;
    std::string description;
    bool completed;

public:
    // Constructor
    Task(int id, const std::string& description, bool completed = false);

    // Getters
    int getId() const;
    std::string getDescription() const;
    bool isCompleted() const;

    // Setters
    void setCompleted(bool completed);

    // JSON serialization
    json toJson() const;
    static Task fromJson(const json& j);
};

#endif // TASK_H
