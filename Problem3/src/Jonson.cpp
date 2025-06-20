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

void Jonson::calculate_heuristic(){
  std::vector<Task> old_tasks = tasks;
  std::vector<Task>   m1;
  std::vector<Task>   m2;
  int prmin_1 = std::numeric_limits<int>::max();
  int prmin_2 = std::numeric_limits<int>::max();
  size_t index_1 = 0;
  size_t index_2 = 0;
  
  for (size_t i=0; i < tasks.size(); ++i)
  {
    for (size_t j=0; j < old_tasks.size(); ++j){
      auto& task = old_tasks[j];

      if (task.processing_time.size() < 2) {
        std::cerr << "Error: Jonson's algorithm requires at least two processing times per task." << std::endl;
        return;
      }
      if (task.processing_time[0] < prmin_1) {
        prmin_1 = task.processing_time[0];
        index_1 = j;
      }
      if (task.processing_time[1] < prmin_2) {
        prmin_2 = task.processing_time[1];
        index_2 = j;
      }
    }
    
    if (prmin_1 < prmin_2) {
      m1.push_back(old_tasks[index_1]);
      old_tasks.erase(old_tasks.begin() + index_1);
    } else {
      m2.push_back(old_tasks[index_2]);
      
      old_tasks.erase(old_tasks.begin() + index_2);
    }
    prmin_1 = std::numeric_limits<int>::max();
    prmin_2 = std::numeric_limits<int>::max();
  }

  // Combine m1 and m2 into tasks
  tasks.clear();
  tasks.insert(tasks.end(), m1.begin(), m1.end());
  tasks.insert(tasks.end(), m2.begin(), m2.end());

}