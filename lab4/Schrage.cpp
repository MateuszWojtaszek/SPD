//
// Created by Mateusz Wojtaszek on 31/03/2025.
//

#include "Schrage.h"

Schrage::Schrage(std::vector<Task> tasks) : BaseProblem(tasks) {}


void Schrage::calculate_heuristic() {
    auto cmp_r = [](const Task &a, const Task &b) { return a.release_time > b.release_time; };
    auto cmp_q = [](const Task &a, const Task &b) { return a.cooling_time < b.cooling_time; };

    std::priority_queue<Task, std::vector<Task>, decltype(cmp_r)> N(cmp_r);
    std::priority_queue<Task, std::vector<Task>, decltype(cmp_q)> G(cmp_q);

    for (const auto &task : tasks) {
        N.push(task);
    }

    int t = 0;
    std::vector<Task> pi;

    while (!N.empty() || !G.empty()) {
        while (!N.empty() && N.top().release_time <= t) {
            G.push(N.top());
            N.pop();
        }

        if (G.empty()) {
            t = N.top().release_time;
        } else {
            Task e = G.top();
            G.pop();
            pi.push_back(e);
            t += e.processing_time;
            tasks = pi;  // Update tasks to the current permutation
        }
    }
}