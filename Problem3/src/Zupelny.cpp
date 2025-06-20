
#include "Task.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "Zupelny.hpp"

Zupelny::Zupelny(std::vector<Task> tasks, int maszyny) : BaseProblem(tasks, maszyny) {
  std::cout << "Zupelny" << std::endl;
}


void Zupelny::calculate_heuristic() {

  std::vector<std::vector<Task>> all_combinations;
  std::vector<Task> current = tasks;

  std::sort(current.begin(), current.end(), [](const Task& a, const Task& b) {
    return a.id < b.id;
  });

  do {
    all_combinations.push_back(current);
  } while (std::next_permutation(current.begin(), current.end(), [](const Task& a, const Task& b) {
    return a.id < b.id;
  }));

  int min_cmax = std::numeric_limits<int>::max();
  std::vector<Task> best_permutation;

  for (const auto& permutation : all_combinations) {
    int cmax = cmax_calcualate(permutation); 
    // for (const auto& task : permutation) {
    //   std::cout << task.id << " ";
    // }
    // std::cout << "cmax: " << cmax << std::endl;
    
    if (cmax < min_cmax) {
      min_cmax = cmax;
      best_permutation = permutation;
    }
  }

  tasks = best_permutation;

}
  