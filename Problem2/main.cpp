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
void pronto_task(std::vector<Task> &tasks, int maszyny,int expected_cmax = 0) {
  static_assert(std::is_base_of<BaseProblem, T>::value, "T must derive from BaseProblem");
  T problem(tasks, maszyny);
  problem.start_timer();
  problem.calculate_heuristic();
  auto a = problem.stop_timer();
  auto cmax = problem.get_cmax();
  // problem.print_task_instance();
  float error = (float)(cmax - expected_cmax) / (float)expected_cmax * 100.0f;
  std::cout << "Cmax: " << cmax << " Time:" << a << " Error:" <<  error<< std::endl;

}

int getcmax(std::vector<Task> &tasks, int maszyny) {
  PDynamczine problem(tasks, maszyny);
  problem.calculate_heuristic();
  auto a = problem.stop_timer();
  auto cmax = problem.get_cmax();
  return cmax;
}

void pronto_task_Fptas(std::vector<Task> &tasks, int maszyny,int expected_cmax = 0, float epsilon = 0.1) {
  FPTAS problem(tasks, maszyny);
  problem.epsilon = epsilon;
  problem.start_timer();
  problem.calculate_heuristic();
  auto a = problem.stop_timer();
  auto cmax = problem.get_cmax();
  // problem.print_task_instance();
  float error = (float)(cmax - expected_cmax) / (float)expected_cmax * 100.0f;
  std::cout << "Cmax: " << cmax << " Time:" << a << " Error:" <<  error<< " Eps" << epsilon << std::endl;
}

void pronto_task_Ptas(std::vector<Task> &tasks, int maszyny,int expected_cmax = 0,int k = 3) {
  PTAS problem(tasks, maszyny);
  problem.k = k;
  problem.start_timer();
  problem.calculate_heuristic();
  auto a = problem.stop_timer();
  auto cmax = problem.get_cmax();
  // problem.print_task_instance();
  float error = (float)(cmax - expected_cmax) / (float)expected_cmax * 100.0f;
  std::cout << "Cmax: " << cmax << " Time:" << a << " Error:" <<  error<< "  K:" << k << std::endl;
}

int main() {
  std::vector<Task> tasks;

  std::srand(0); // generate not random numbers 
  int min_pval=50;
  int max_pval=100;
  for (int i = 1; i <= 50; ++i) {
    int random_value = min_pval + (std::rand() % (max_pval - min_pval + 1));
    tasks.push_back(Task(i, random_value));
  }

  auto cmax = getcmax(tasks, 2);

  std::cout << "Tasks:" << tasks.size() << std::endl;
  pronto_task<LSA>(tasks, 2,cmax);
  pronto_task<LPT>(tasks, 2,cmax);
  pronto_task<PDynamczine>(tasks, 2,cmax);
  pronto_task_Fptas(tasks, 2,cmax,0.1);
  pronto_task_Fptas(tasks, 2,cmax,0.4);
  pronto_task_Fptas(tasks, 2,cmax,0.9);
  pronto_task_Ptas(tasks, 2,cmax,2);
  pronto_task_Ptas(tasks, 2,cmax,3);
  pronto_task_Ptas(tasks, 2,cmax,4);

  return 0;
}