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

class Zupelny: public BaseProblem {
  public:
  Zupelny() = delete;
  Zupelny(std::vector<Task> tasks, int maszyny);

  void calculate_heuristic() override;

};