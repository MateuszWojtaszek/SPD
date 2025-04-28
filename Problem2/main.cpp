#include <iostream>
#include <vector>
#include "BaseProblem.hpp"
#include "Task.hpp" 
#include "Processor.hpp"
#include "LSA.hpp"
#include "LPT.hpp"

/* Zadanie - Podział n zadań na m maszyn i liczenie Cmax -> maksymalny czas
 *
 */

template <typename T>
void pronto_task(std::vector<Task> &tasks, int maszyny) {
  static_assert(std::is_base_of<BaseProblem, T>::value, "T must derive from BaseProblem");
  T problem(tasks, maszyny);
  problem.calculate_heuristic();
  auto cmax = problem.get_cmax();
  problem.print_task_instance();
  std::cout << "Cmax: " << cmax << std::endl;

}



int main() {
  std::cout << "Hello, World!" << std::endl;
  std::vector<Task> tasks;
  tasks.push_back(Task(1, 2));
  tasks.push_back(Task(2, 3));
  tasks.push_back(Task(3, 4));
  tasks.push_back(Task(4, 5));
  tasks.push_back(Task(5, 6));
  
  pronto_task<LSA>(tasks, 2);
  pronto_task<LPT>(tasks, 2);

  return 0;
}