#include "BaseProblem.hpp"
#include <limits>

BaseProblem::BaseProblem(std::vector<Task> tasks, int _maszyny) : tasks(tasks),maszyny(_maszyny) {

}

void BaseProblem::print_task_instance() {
    std::cout << "Task ID | Processing Time" << std::endl;
    for (const auto &proc : tasks) {
        std::cout << proc.to_string() << std::endl;
    }
}

int BaseProblem::get_cmax() {
  return cmax_calcualate(tasks);
}

int BaseProblem::cmax_calcualate(const std::vector<Task> &dp) {
    if (dp.empty() || maszyny == 0) return 0;

    // dp[i][j] = completion time of i-th task on j-th machine
    std::vector<std::vector<int>> completion_times(dp.size(), std::vector<int>(maszyny, 0));

    for (size_t i = 0; i < dp.size(); ++i) {
        for (int j = 0; j < maszyny; ++j) {
            int proc_time = (j < dp[i].processing_time.size()) ? dp[i].processing_time[j] : 0;
            if (i == 0 && j == 0) {
                completion_times[i][j] = proc_time;
            } else if (i == 0) {
                completion_times[i][j] = completion_times[i][j-1] + proc_time;
            } else if (j == 0) {
                completion_times[i][j] = completion_times[i-1][j] + proc_time;
            } else {
                completion_times[i][j] = std::max(completion_times[i-1][j], completion_times[i][j-1]) + proc_time;
            }
        }
    }
    return completion_times[dp.size()-1][maszyny-1];
}

std::vector<Task> BaseProblem::get_tasks() {
    return tasks;
}
// in txt is R, P and Q
std::vector<Task> BaseProblem::read_tasks_from_file(const std::string &filename) {
  std::vector<Task> tasks;
  return tasks; // Placeholder for actual file reading logic
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