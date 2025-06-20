#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>


#include "BaseProblem.hpp"
#include "Task.hpp" 
#include "Zupelny.hpp"
#include "NEH.hpp"
#include "FNEH.hpp"
#include "Jonson.hpp"

template <typename T>
int pronto_task(std::vector<Task> &tasks, int maszyny,int expected_cmax = 0) {
  static_assert(std::is_base_of<BaseProblem, T>::value, "T must derive from BaseProblem");
  T problem(tasks, maszyny);
  problem.start_timer();
  problem.calculate_heuristic();
  auto a = problem.stop_timer();
  auto cmax = problem.get_cmax();
  // problem.print_task_instance();
  float error = (float)(cmax - expected_cmax) / (float)expected_cmax * 100.0f;
  std::cout << "Cmax: " << cmax << " Time:" << a << " Error:" <<  error<< std::endl;
  return cmax;
}

int main() {
  std::vector<Task> tasks;

  std::srand(0); // generate not random numbers 
  int min_pval=1;
  int max_pval=10;
  int machines = 4; // Assuming 3 machines
  int expected_cmax = 0;


  for (int i = 1; i <= 10; ++i) {
    int random_value = min_pval + (std::rand() % (max_pval - min_pval + 1));
    // Generate a random processing time for each task
    std::vector<int> processing_times;
    for (int j = 0; j < machines; ++j) { // Assuming 3 machines
      processing_times.push_back(random_value);
    }
    tasks.push_back(Task(i, processing_times));
  }

  // tasks.push_back(Task(1, {3, 5,4}));
  // tasks.push_back(Task(2, {6, 3,7}));
  // tasks.push_back(Task(3, {5, 4,2}));
  // tasks.push_back(Task(4, {2, 6,1}));
  // tasks.push_back(Task(5,  {6, 5,7}));
  // tasks.push_back(Task(6, {1, 4,9}));


  expected_cmax= pronto_task<Zupelny>(tasks, machines, expected_cmax);
  pronto_task<NEH>(tasks, machines, expected_cmax);
  pronto_task<Jonson>(tasks, 2, expected_cmax); // Jonson is for 2 machines only
  pronto_task<FNEH>(tasks, machines, expected_cmax);



  

  return 0;
}