#pragma once

#include "Task.hpp"
#include "Processor.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "BaseProblem.hpp"

class PDynamczine: public BaseProblem {
  public:
  PDynamczine() = delete;
  PDynamczine(std::vector<Task> tasks, int maszyny);

  void calculate_heuristic() override;


};