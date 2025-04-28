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




int main() {
  std::cout << "Hello, World!" << std::endl;
  std::vector<Task> tasks;
  tasks.push_back(Task(1, 2));
  tasks.push_back(Task(2, 3));
  tasks.push_back(Task(3, 4));
  tasks.push_back(Task(4, 5));
  tasks.push_back(Task(5, 6));
  
  std::cout << "LSA:" << std::endl;
  LSA lsa(tasks, 2);

  lsa.calculate_heuristic();  
  auto cmax= lsa.get_cmax();
  lsa.print_task_instance();
  std::cout << "Cmax: " << cmax << std::endl; 
  
  std::cout << "LPT:" << std::endl;
  LPT lpt(tasks, 2);
  lpt.calculate_heuristic();
  cmax= lpt.get_cmax();
  lpt.print_task_instance();
  std::cout << "Cmax: " << cmax << std::endl;
  

  return 0;
}