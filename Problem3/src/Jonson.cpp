#pragma once

#include "Task.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "BaseProblem.hpp"
#include "Task.hpp"
#include "Jonson.hpp"
#include "NEH.hpp"

Jonson::Jonson(std::vector<Task> tasks, int maszyny): BaseProblem(tasks, maszyny) {
    std::cout << "Jonson" << std::endl;
}

void Jonson::calculate_heuristic() {
    if (maszyny != 2) {
        std::cerr << "Algorytm Johnsona dziala tylko dla 2 maszyn!" << std::endl;
        return;
    }

    // Krok 1: Podział na grupy
    std::vector<Task> group1, group2;
    for (const auto& task : tasks) {
        if (task.processing_time.size() >= 2) { // Zabezpieczenie
            if (task.processing_time[0] < task.processing_time[1]) {
                group1.push_back(task);
            } else {
                group2.push_back(task);
            }
        }
    }


    // Krok 2: Sortowanie grupy 1 (rosnąco po czasie na maszynie 1)
    std::sort(group1.begin(), group1.end(), [](const Task& a, const Task& b) {
        return a.processing_time[0] < b.processing_time[0];
    });

    // Krok 3: Sortowanie grupy 2 (malejąco po czasie na maszynie 2)
    std::sort(group2.begin(), group2.end(), [](const Task& a, const Task& b) {
        return a.processing_time[1] > b.processing_time[1];
    });


    // Krok 4: Złączenie grup i zapisanie wyniku
    std::vector<Task> optimal_sequence;
    optimal_sequence.insert(optimal_sequence.end(), group1.begin(), group1.end());
    optimal_sequence.insert(optimal_sequence.end(), group2.begin(), group2.end());

    tasks = optimal_sequence;
}