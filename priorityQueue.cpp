#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Task {
    string name;
    int priority;

    Task(string name, int priority) : name(name), priority(priority) {}

    bool operator>(const Task& other) const {
        return priority > other.priority;
    }
};

int main() {
    priority_queue<Task, vector<Task>, greater<Task>> taskQueue;

    taskQueue.push(Task("Task A", 3));
    taskQueue.push(Task("Task B", 1));
    taskQueue.push(Task("Task C", 2));
    taskQueue.push(Task("Task D", 2));

    while (!taskQueue.empty()) {
        Task currentTask = taskQueue.top();
        taskQueue.pop();
        cout << "Executing task: " << currentTask.name << " (Priority: " << currentTask.priority << ")" << endl;
    }

    return 0;
}
