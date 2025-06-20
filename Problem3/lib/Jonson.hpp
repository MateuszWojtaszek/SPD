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

class Jonson :public BaseProblem {
  public:
    // Johnson's algorithm is for 2-machine flow shop
    Jonson(std::vector<Task> tasks, int maszyny);
    virtual void calculate_heuristic() override;
};