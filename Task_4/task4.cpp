#include <iostream>
#include <vector>
#include <string>

struct Task {
    std::string description;
    bool completed;

    Task(const std::string& desc) : description(desc), completed(false) {}
};

class ToDoList {
private:
    std::vector<Task> tasks;

public:
    void addTask(const std::string& description) {
        tasks.emplace_back(description);
        std::cout << "Task added successfully.\n";
        std::cout << "-------------------------\n";
    }

    void viewTasks() const {
        std::cout << "Current Tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". " << tasks[i].description 
                      << " [" << (tasks[i].completed ? "Completed" : "Pending") << "]\n";
        }
        std::cout << "-------------------------\n";
    }

    void markTaskCompleted(size_t index) {
        if (index < tasks.size()) {
            tasks[index].completed = true;
            std::cout << "Task marked as completed.\n";
        } else {
            std::cout << "Invalid task number.\n";
        }
        std::cout << "-------------------------\n";
    }

    void removeTask(size_t index) {
        if (index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
            std::cout << "Task removed successfully.\n";
        } else {
            std::cout << "Invalid task number.\n";
        }
        std::cout << "-------------------------\n";
    }
};

int main() {
    ToDoList todoList;
    int choice;
    std::string description;
    size_t taskNumber;

    while (true) {
        std::cout << "1. Add Task\n2. View Tasks\n3. Mark Task as Completed\n4. Remove Task\n5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter task description: ";
                std::cin.ignore();
                std::getline(std::cin, description);
                todoList.addTask(description);
                break;
            case 2:
                todoList.viewTasks();
                break;
            case 3:
                std::cout << "Enter task number to mark as completed: ";
                std::cin >> taskNumber;
                todoList.markTaskCompleted(taskNumber - 1);
                break;
            case 4:
                std::cout << "Enter task number to remove: ";
                std::cin >> taskNumber;
                todoList.removeTask(taskNumber - 1);
                break;
            case 5:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                std::cout << "-------------------------\n";
        }
    }
}
