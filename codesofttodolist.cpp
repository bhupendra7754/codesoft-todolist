#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Task {
    std::string description;
    std::string priority;
    bool isCompleted;
};

void displayMenu() {
    std::cout << "\n==== To-Do List Manager ====\n";
    std::cout << "1. Add a task\n";
    std::cout << "2. View all tasks\n";
    std::cout << "3. Mark a task as completed\n";
    std::cout << "4. Remove a task\n";
    std::cout << "5. Search for tasks\n";
    std::cout << "6. Edit a task description\n";
    std::cout << "7. Save tasks to file\n";
    std::cout << "8. Load tasks from file\n";
    std::cout << "9. Exit\n";
    std::cout << "Choose an option: ";
}

void addTask(std::vector<Task>& tasks) {
    Task newTask;
    std::cout << "Enter the task description: ";
    std::cin.ignore();
    std::getline(std::cin, newTask.description);

    std::cout << "Enter the task priority (High, Medium, Low): ";
    std::getline(std::cin, newTask.priority);

    newTask.isCompleted = false;
    tasks.push_back(newTask);
    std::cout << "Task added successfully!\n";
}

void viewTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks in your to-do list.\n";
    } else {
        std::cout << "\nYour tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". " << tasks[i].description
                      << " [" << tasks[i].priority << "]"
                      << " [" << (tasks[i].isCompleted ? "Completed" : "Pending") << "]\n";
        }
    }
}

void markTaskAsCompleted(std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks to mark as completed.\n";
        return;
    }

    int taskNumber;
    std::cout << "Enter the task number to mark as completed: ";
    std::cin >> taskNumber;

    if (taskNumber < 1 || static_cast<size_t>(taskNumber) > tasks.size()) {
        std::cout << "Invalid task number.\n";
    } else {
        tasks[taskNumber - 1].isCompleted = true;
        std::cout << "Task marked as completed successfully!\n";
    }
}

void removeTask(std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks to remove.\n";
        return;
    }

    int taskNumber;
    std::cout << "Enter the task number to remove: ";
    std::cin >> taskNumber;

    if (taskNumber < 1 || static_cast<size_t>(taskNumber) > tasks.size()) {
        std::cout << "Invalid task number.\n";
    } else {
        tasks.erase(tasks.begin() + taskNumber - 1);
        std::cout << "Task removed successfully!\n";
    }
}

void searchTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks to search.\n";
        return;
    }

    std::string keyword;
    std::cout << "Enter a keyword to search: ";
    std::cin.ignore();
    std::getline(std::cin, keyword);

    bool found = false;
    for (size_t i = 0; i < tasks.size(); ++i) {
        if (tasks[i].description.find(keyword) != std::string::npos) {
            std::cout << i + 1 << ". " << tasks[i].description
                      << " [" << tasks[i].priority << "]"
                      << " [" << (tasks[i].isCompleted ? "Completed" : "Pending") << "]\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No tasks found matching the keyword.\n";
    }
}

void editTaskDescription(std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks to edit.\n";
        return;
    }

    int taskNumber;
    std::cout << "Enter the task number to edit: ";
    std::cin >> taskNumber;

    if (taskNumber < 1 || static_cast<size_t>(taskNumber) > tasks.size()) {
        std::cout << "Invalid task number.\n";
    } else {
        std::cout << "Enter the new description: ";
        std::cin.ignore();
        std::getline(std::cin, tasks[taskNumber - 1].description);
        std::cout << "Task updated successfully!\n";
    }
}

void saveTasksToFile(const std::vector<Task>& tasks) {
    std::ofstream outFile("tasks.txt");
    if (outFile.is_open()) {
        for (const auto& task : tasks) {
            outFile << task.description << "|" << task.priority << "|" << task.isCompleted << "\n";
        }
        outFile.close();
        std::cout << "Tasks saved to file successfully!\n";
    } else {
        std::cout << "Error saving tasks to file.\n";
    }
}

void loadTasksFromFile(std::vector<Task>& tasks) {
    std::ifstream inFile("tasks.txt");
    if (inFile.is_open()) {
        tasks.clear();
        std::string line;
        while (std::getline(inFile, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.rfind('|');

            Task task;
            task.description = line.substr(0, pos1);
            task.priority = line.substr(pos1 + 1, pos2 - pos1 - 1);
            task.isCompleted = line.substr(pos2 + 1) == "1";

            tasks.push_back(task);
        }
        inFile.close();
        std::cout << "Tasks loaded from file successfully!\n";
    } else {
        std::cout << "Error loading tasks from file.\n";
    }
}

int main() {
    std::vector<Task> tasks;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskAsCompleted(tasks);
                break;
            case 4:
                removeTask(tasks);
                break;
            case 5:
                searchTasks(tasks);
                break;
            case 6:
                editTaskDescription(tasks);
                break;
            case 7:
                saveTasksToFile(tasks);
                break;
            case 8:
                loadTasksFromFile(tasks);
                break;
            case 9:
                std::cout << "Exiting the To-Do List Manager. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
   }
