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

  std::string to_string() const {
    std::string result = "Processor ID: " + std::to_string(id) + ", Tasks: ";
    for (const auto &task : tasks) {
      result += task.to_string() + " ";
    }
    return result;
  } 
  
};
