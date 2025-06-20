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

class Zupelny :public BaseProblem {
  public:
    Zupelny(std::vector<Task> tasks, int maszyny);
    virtual void calculate_heuristic() override;
  };