//
// Created by Mateusz Wojtaszek on 30/03/2025.
//

#include "SortByR.h"
#include <algorithm>

SortByR::SortByR(std::vector<Task> tasks) : BaseProblem(tasks) {}

void SortByR::calculate_heuristic() {
    std::sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        return a.release_time < b.release_time;
    });
}