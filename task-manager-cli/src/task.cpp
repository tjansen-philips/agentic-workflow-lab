#include "task.h"

Task::Task(int id, const std::string& description, bool completed)
    : id(id), description(description), completed(completed) {
}

int Task::getId() const {
    return id;
}

std::string Task::getDescription() const {
    return description;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::setCompleted(bool completed) {
    this->completed = completed;
}

json Task::toJson() const {
    return json{
        {"id", id},
        {"description", description},
        {"completed", completed}
    };
}

Task Task::fromJson(const json& j) {
    return Task(
        j.at("id").get<int>(),
        j.at("description").get<std::string>(),
        j.at("completed").get<bool>()
    );
}
