#pragma once

#include "Task.hpp"
#include "Processor.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "LSA.hpp"


LSA::LSA(std::vector<Task> tasks, int maszyny): BaseProblem(tasks, maszyny) {

}



void LSA::calculate_heuristic() {
  
  int proc_count=0;
  for (size_t i = 0; i < tasks.size(); i++)
  {
    processors[proc_count].tasks.push_back(tasks[i]);
    proc_count++;
    if(proc_count >= processors.size())
    {
      proc_count = 0;
    }
  }
    
}