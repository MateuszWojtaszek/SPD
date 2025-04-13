//
// Created by Mateusz Wojtaszek on 13/04/2025.
//
#include "SortByRq.h"
#include <algorithm>

SortByRq::SortByRq(std::vector<Task> tasks) : BaseProblem(std::move(tasks)) {}

void SortByRq::calculate_heuristic() {
    std::sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        return (a.release_time + a.cooling_time) < (b.release_time + b.cooling_time);
    });
}