
#include "Task.hpp"
#include "Processor.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "PDynamczine.hpp"
#include <iomanip>
#include <stdexcept>
#include <cmath>

PDynamczine::PDynamczine(std::vector<Task> tasks, int maszyny): BaseProblem(tasks, maszyny) {
  if (maszyny != 2) {
    throw std::invalid_argument("Me need two machines");
  }
  std::cout << "PDynamczine" << std::endl;
}


void PDynamczine::calculate_heuristic() {
  // algorytm programowania dynamicznego dla problemu P2
  int n = tasks.size();
  int max_time_k = 0;
  for (const auto &task : tasks) {
    max_time_k += task.processing_time;
  }
  max_time_k = max_time_k / maszyny + 1;
  std::vector<std::vector<bool>> T(n + 1, std::vector<bool>(max_time_k, 0));
  for (auto &&i : T) {
    i[0] = true;
  }

  for (size_t j = 1; j <= tasks.size(); j++)
  {
    auto pj = tasks[j-1].processing_time;
    for (size_t k = pj; k < max_time_k; k++)
    {
      bool arg1 = T[j-1][k];
      bool arg2 = (k >= pj);
      bool arg3 = T[j-1][k-pj];
      T[j][k] = arg1 || (arg2 && arg3);
      // if( arg1 || (arg2 && arg3) ){
      //    = true;
      // }
    }
  }
  T[n][0] = false;

  // printowanie tabelki PD
  // std::cout << "PDynamczine Table" << std::endl;
  // std::cout << "     "; 
  // for (size_t k = 0; k < max_time_k; k++) {
  //   std::cout << std::setw(4) << k << " ";
  // }
  // std::cout << std::endl;

  // for (size_t j = 0; j <= tasks.size(); j++) {
  //   std::cout << std::setw(4) << j << " ";
  //   for (size_t k = 0; k < max_time_k; k++) {
  //     std::cout << std::setw(4) << T[j][k] << " ";
  //   }
  //   std::cout << std::endl;
  // }
  
    // Backtrace to find the solution
  int k = max_time_k - 1;
  while (k > 0 && T[n][k] == false) {
    k--;
  }

  processors[0].id = 1;
  processors[1].id = 2;
  for (int j = n; j > 0; j--) {
    auto pj = tasks[j-1].processing_time;
    
    if (k >= pj && T[j - 1][k - pj]) {
      processors[0].tasks.push_back(tasks[j - 1]);
      k -= pj;
    } 
    else {
      processors[1].tasks.push_back(tasks[j - 1]);
    }
  }


}
