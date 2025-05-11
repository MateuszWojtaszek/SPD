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
#include <limits>

class Zupelny : public BaseProblem {
public:
  Zupelny() = delete;
  Zupelny(std::vector<Task> tasks, int maszyny);

  void calculate_heuristic() override;

private:
  // Funkcja pomocnicza do rekurencyjnego generowania wszystkich przypisań
  void find_best_assignment_recursive(
      int current_task_index,                          // Indeks bieżącego zadania do przypisania
      std::vector<Processor> current_processors_state, // Aktualny stan procesorów (przekazywany przez wartość)
      int& min_cmax,                                   // Referencja do minimalnego znalezionego Cmax
      std::vector<Processor>& best_processors_state    // Referencja do najlepszego znalezionego przypisania
  );
};