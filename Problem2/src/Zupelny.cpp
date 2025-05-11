#pragma once

#include "Task.hpp"
#include "Processor.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "Zupelny.hpp"


Zupelny::Zupelny(std::vector<Task> tasks, int maszyny): BaseProblem(tasks, maszyny) {
  std::cout << "Zupelny" << std::endl;

}

void Zupelny::calculate_heuristic() {
  //  genarta eall all Permutations
  // dla 3 maszyn
    
}