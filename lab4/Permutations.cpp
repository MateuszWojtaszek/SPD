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

void Permutations::generate_permutations(std::vector<std::vector<Task>> &permutations) {
    std::sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        return a.id < b.id;
    });

    do {
        permutations.push_back(tasks);
    } while (std::next_permutation(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
        return a.id < b.id;
    }));
}

void Permutations::print_permutations(const std::vector<std::vector<Task>> &permutations) {
    for (const auto &permutation : permutations) {
        for (const auto &task : permutation) {
            std::cout << task.to_string() << " ";
        }
        std::cout << std::endl;
    }
}

void Permutations::calculate_Cmax_for_permutations(const std::vector<std::vector<Task>> &permutations) {
    int min_Cmax = std::numeric_limits<int>::max();
    std::vector<Task> best_permutation;

    for (const auto &permutation : permutations) {
        Permutations problem(permutation);
        int Cmax = problem.get_cmax();
        std::cout << "Cmax: " << Cmax << std::endl;
        if (Cmax < min_Cmax) {
            min_Cmax = Cmax;
            best_permutation = permutation;
        }
    }

    std::cout << "Minimum Cmax: " << min_Cmax << std::endl;
    std::cout << "Best permutation:" << std::endl;
    std::cout << "ID | Processing Time | Release Time | Cooling Time" << std::endl;
    for (const auto &task : best_permutation) {
        std::cout << task.id << "  | " << task.processing_time << "              | "
                  << task.release_time << "            | " << task.cooling_time << std::endl;
    }
}