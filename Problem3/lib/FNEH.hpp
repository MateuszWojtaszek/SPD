// Plik: FNEH.hpp
#pragma once

#include "NEH.hpp"

class FNEH : public NEH {
public:
  FNEH(std::vector<Task> tasks, int maszyny);
  void calculate_heuristic() override;

private:
  int calculate_cmax_for_permutation(const std::vector<Task>& permutation);
};