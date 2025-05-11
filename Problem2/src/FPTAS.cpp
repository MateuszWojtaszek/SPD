
#include "Task.hpp"
#include "Processor.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "FPTAS.hpp"


FPTAS::FPTAS(std::vector<Task> tasks, int maszyny): BaseProblem(tasks, maszyny) {
  std::cout << "FPTAS" << std::endl;
}



void FPTAS::calculate_heuristic() {
  // to do
    
}