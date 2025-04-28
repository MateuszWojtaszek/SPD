#include "BaseProblem.hpp"

BaseProblem::BaseProblem(std::vector<Task> tasks, int _maszyny) : tasks(tasks),maszyny(_maszyny) {}

void BaseProblem::print_task_instance() {
    std::cout << "Task ID | Processing Time" << std::endl;
    for (const auto &task : tasks) {
        std::cout << task.to_string() << std::endl;
    }
}

int BaseProblem::get_cmax() {
    int Cmax = 0;
    int current_time = 0;

    // for (const auto &task : tasks) {
    //     if (current_time <= task.release_time) {
    //         current_time = task.release_time;
    //     }
    //     current_time += task.processing_time;
    //     Cmax = std::max(Cmax, current_time + task.cooling_time);
    // }
    return Cmax;
}

std::vector<Task> BaseProblem::get_tasks() {
    return tasks;
}
// in txt is R, P and Q
std::vector<Task> BaseProblem::read_tasks_from_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    int num_tasks;
    file >> num_tasks;
    std::vector<Task> tasks;
    tasks.reserve(num_tasks);

    for (int i = 0; i < num_tasks; ++i) {
        Task task;
        file >> task.processing_time;
        task.id = i + 1;
        tasks.push_back(task);
    }
    return tasks;
}
std::chrono::time_point<std::chrono::high_resolution_clock> BaseProblem::start_time;

void BaseProblem::start_timer() {
    start_time = std::chrono::high_resolution_clock::now();
}

float BaseProblem::stop_timer() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    return duration.count() / 1000.0f; // Convert to mseconds
}