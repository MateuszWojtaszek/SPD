//
// Created by Mateusz Wojtaszek on 30/03/2025.
//

#include "Permutations.h"
#include <algorithm>
#include <iostream>
#include <limits>

Permutations::Permutations(std::vector<Task> tasks) : BaseProblem(tasks) {}

void Permutations::calculate_heuristic() {
    // This method is not applicable for permutations, so it can be left empty or throw an exception
}

int Permutations::generate_permutations() {
    std::sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        return a.id < b.id;
    });

    int min_Cmax = std::numeric_limits<int>::max();
    std::vector<Task> best_permutation;

    do {
        int Cmax = get_cmax();
        if (Cmax < min_Cmax) {
            min_Cmax = Cmax;
            best_permutation = tasks;
        }
    } while (std::next_permutation(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        return a.id < b.id;
    }));

    std::cout << "Minimum Cmax: " << min_Cmax << std::endl;
    std::cout << "Best permutation:" << std::endl;
    std::cout << "ID | Processing Time | Release Time | Cooling Time" << std::endl;
    for (const auto &task : best_permutation) {
        std::cout << task.id << "  | " << task.processing_time << "              | "
                  << task.release_time << "            | " << task.cooling_time << std::endl;
    }
    return min_Cmax;
}

void Permutations::print_permutations(const std::vector<std::vector<Task>> &permutations) {
    for (const auto &permutation : permutations) {
        for (const auto &task : permutation) {
            std::cout << task.to_string() << " ";
        }
        std::cout << std::endl;
    }
}