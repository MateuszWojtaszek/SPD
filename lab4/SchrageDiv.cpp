//
// Created by Patryk Dudziński on 3/04/2025.
//

#include "SchrageDiv.h"
#include <queue>
#include <algorithm>

SchrageDiv::SchrageDiv(std::vector<Task> tasks) : BaseProblem(tasks) {}


void SchrageDiv::calculate_heuristic() {
  auto cmp_r = [](const Task &a, const Task &b) { return a.release_time > b.release_time; };
  auto cmp_q = [](const Task &a, const Task &b) { return a.cooling_time < b.cooling_time; };

  std::priority_queue<Task, std::vector<Task>, decltype(cmp_r)> N(cmp_r);
  std::priority_queue<Task, std::vector<Task>, decltype(cmp_q)> G(cmp_q);

  for (const auto &task : tasks) {
      N.push(task);
  }

  int t = 0;
  std::vector<Task> pi;
  Task current_task{-1, 0, 0, 0}; // Dummy task to track the running task
  int remaining_time = 0;

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

          if (remaining_time > 0 && e.cooling_time > current_task.cooling_time) {
              // Preempt the current task
              current_task.processing_time = remaining_time;
              G.push(current_task);
          }

          current_task = e;
          remaining_time = current_task.processing_time;

          // Simulate processing the task
          t += remaining_time;
          pi.push_back(current_task);
          remaining_time = 0; // Task completed
      }
  }

  tasks = pi;  // Update tasks to the correct order
}