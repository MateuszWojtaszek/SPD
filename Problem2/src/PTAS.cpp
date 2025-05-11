
#include "Task.hpp"
#include "Processor.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "PTAS.hpp"


PTAS::PTAS(std::vector<Task> tasks, int maszyny): BaseProblem(tasks, maszyny) {
  std::cout << "PTAS" << std::endl;
}



void PTAS::calculate_heuristic() {
  // to do   
}