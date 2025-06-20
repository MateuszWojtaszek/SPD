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

class FNEH :public BaseProblem {
  public:
    FNEH(std::vector<Task> tasks, int maszyny);
    virtual void calculate_heuristic() override;

  private:
    int fneh_cmax_calculate(const std::vector<Task>& seq,bool remember,bool save) const;
    
    // Cache for optimization
    mutable std::vector<std::vector<int>> last_completion_times;
};