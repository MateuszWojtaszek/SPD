//
// Created by Mateusz Wojtaszek on 30/03/2025.
//

#include "SortByQ.h"
#include <algorithm>

SortByQ::SortByQ(std::vector<Task> tasks) : BaseProblem(tasks) {}

void SortByQ::calculate_heuristic() {
    std::sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        return a.cooling_time > b.cooling_time;
    });
}