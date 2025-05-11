#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>


#include "BaseProblem.hpp"
#include "Task.hpp" 
#include "Processor.hpp"
#include "LSA.hpp"
#include "LPT.hpp"
#include "Zupelny.hpp"
#include "PDynamczine.hpp"
#include "PTAS.hpp"
#include "FPTAS.hpp"

/* Zadanie - Podział n zadań na m maszyn i liczenie Cmax -> maksymalny czas
 *
 * Przegląd zupełny
 * 
 * Algorytm programowania dynamicznego
 * Algorytm do…łądny - dający rozwiązanie optymalne.
 *
 * Schematy aproksymacyjne PTAS
 * 
 * FPTAS  to samo tylo zamiast urzycia przglądu zupełnego dla k 
 * urzywamy  Dynamcznego
 * 
 */

template <typename T>
void pronto_task(std::vector<Task> &tasks, int maszyny) {
  static_assert(std::is_base_of<BaseProblem, T>::value, "T must derive from BaseProblem");
  T problem(tasks, maszyny);
  problem.start_timer();
  problem.calculate_heuristic();
  auto a = problem.stop_timer();
  auto cmax = problem.get_cmax();
  problem.print_task_instance();
  std::cout << "Cmax: " << cmax << " Time:" << a << std::endl;

}



int main() {
  std::vector<Task> tasks;

  std::srand(std::time(nullptr)); // Seed the random number generator
  for (int i = 1; i <= 20; ++i) {
    int random_value = std::rand() % 101; // Generate a random value between 0 and 100
    tasks.push_back(Task(i, random_value));
  }

  // tasks.push_back(Task(1, 2));
  // tasks.push_back(Task(2, 3));
  // tasks.push_back(Task(3, 4));
  // tasks.push_back(Task(4, 5));
  // tasks.push_back(Task(5, 6));
  // tasks.push_back(Task(6, 7));
  // tasks.push_back(Task(7, 23));
  // tasks.push_back(Task(8, 4));
  // tasks.push_back(Task(9, 3));
  // tasks.push_back(Task(10, 1));
  
  pronto_task<LSA>(tasks, 2);
  pronto_task<LPT>(tasks, 2);
  pronto_task<Zupelny>(tasks, 2);
  pronto_task<PDynamczine>(tasks, 2);
  pronto_task<PTAS>(tasks, 2);
  // pronto_task<FPTAS>(tasks, 2);

  return 0;
}