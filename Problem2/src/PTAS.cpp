
#include "Task.hpp"
#include "Processor.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "PTAS.hpp"
#include "Zupelny.hpp"


PTAS::PTAS(std::vector<Task> tasks, int maszyny): BaseProblem(tasks, maszyny) {
  std::cout << "PTAS" << std::endl;
}



void PTAS::calculate_heuristic() {
  // to do   

  // Sort tasks in non-increasing order of their processing times
  std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
    return a.processing_time > b.processing_time;
  });

  // Select the first k tasks as large tasks
  std::vector<Task> k_tasks(tasks.begin(),tasks.begin()+k);
  std::vector<Task> unprocessed_tasks(tasks.begin()+k, tasks.end());

  // Sort first k tasks using Zupelny
  Zupelny zupelny(k_tasks, maszyny);
  zupelny.calculate_heuristic();
  processors = zupelny.get_processors();

  std::vector<int> machine_loads(maszyny, 0);
  // Assign small tasks greedily
  for (const auto& task : unprocessed_tasks) {
    auto min_machine = std::min_element(machine_loads.begin(), machine_loads.end());
    int min_index = std::distance(machine_loads.begin(), min_machine);
    processors[min_index].tasks.push_back(task);
    *min_machine += task.processing_time;
  }
}