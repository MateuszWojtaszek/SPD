#pragma once

#include <string>
#include <vector> 
#include "Task.hpp"


struct Processor {
  int id;
  std::vector<Task> tasks;
  int get_cmax() const {
    int Cmax = 0;
    for (const auto &task : tasks) {
      Cmax += task.processing_time;
    }
    return Cmax;
  };
  
};
