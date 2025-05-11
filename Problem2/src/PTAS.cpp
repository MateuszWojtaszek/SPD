
#include "Task.hpp"
#include "Processor.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "PTAS.hpp"


PTAS::PTAS(std::vector<Task> tasks, int maszyny): BaseProblem(tasks, maszyny) {
  std::cout << "PTAS" << std::endl;
}



void PTAS::calculate_heuristic() {
  // to do

  // Sort tasks in descending order of their processing times
  std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
    return a.processing_time > b.processing_time;
  });

  // Distribute tasks among machines to minimize makespan
  std::vector<int> machineLoad(maszyny, 0);
  for (const auto& task : tasks) {
    // Find the machine with the least load
    auto minMachine = std::min_element(machineLoad.begin(), machineLoad.end());
    auto minMachineIndex = std::distance(machineLoad.begin(), minMachine);
    *minMachine += task.processing_time;
    processors[minMachineIndex].tasks.push_back(task);
  }
    
}