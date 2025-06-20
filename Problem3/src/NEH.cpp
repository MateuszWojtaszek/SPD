#include "NEH.hpp"

// Helper: sum of processing times for a task
bool NEH::compare_total_time(const Task& a, const Task& b) {
    int suma_a = 0, suma_b = 0;
    for (int t : a.processing_time) suma_a += t;
    for (int t : b.processing_time) suma_b += t;
    return suma_a > suma_b;
}

NEH::NEH(std::vector<Task> tasks, int maszyny)
    : BaseProblem(tasks, maszyny) {
    std::cout << "NEH" << std::endl;
    }

void NEH::calculate_heuristic() {
    // Step 1: Sort tasks by decreasing sum of processing times
    std::vector<Task> sorted_tasks = tasks;
    std::sort(sorted_tasks.begin(), sorted_tasks.end(), compare_total_time);

    std::vector<Task> pi; // current best order 

    // Step 2: Insert each task into the best position
    for (size_t i = 0; i < sorted_tasks.size(); ++i) {
        int min_cmax = -1;
        size_t best_pos = 0;
        for (size_t pos = 0; pos <= pi.size(); ++pos) {
            std::vector<Task> temp = pi;
            temp.insert(temp.begin() + pos, sorted_tasks[i]);
            int cmax = cmax_calcualate(temp);
            if (min_cmax == -1 || cmax < min_cmax) {
                min_cmax = cmax;
                best_pos = pos;
            }
        }
        pi.insert(pi.begin() + best_pos, sorted_tasks[i]);
    }
    tasks = pi;
}
