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

class NEH :public BaseProblem {
  public:
    NEH(std::vector<Task> tasks, int maszyny);
    virtual void calculate_heuristic() override;

    static bool compare_total_time(const Task& a, const Task& b);
  private:
  };