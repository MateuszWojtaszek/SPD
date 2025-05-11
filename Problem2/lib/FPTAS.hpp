#pragma once

#include "Task.hpp"
#include "Processor.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "BaseProblem.hpp"

class FPTAS : public BaseProblem {
public:
  FPTAS() = delete; // Usuwamy domyślny konstruktor
  // Konstruktor przyjmuje teraz epsilon
  FPTAS(std::vector<Task> tasks, int maszyny);

  void calculate_heuristic() override;

private:
  float epsilon = 0.1; // Wartość epsilon do kontroli aproksymacji

  // Prywatna metoda do rozwiązania P2||Cmax za pomocą PD, zaadaptowana z PDynamczine
  // Przyjmuje listę zadań (z przeskalowanymi czasami, ale oryginalnymi ID)
  // Zwraca przypisanie tych zadań (z oryginalnymi ID i przeskalowanymi czasami) do dwóch procesorów.
  std::vector<Processor> solve_p2_cmax_with_dp(const std::vector<Task>& tasks_to_schedule);
};