//
// Created by Mateusz Wojtaszek on 30/03/2025.
//

#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H
#include "BaseProblem.h"

class Permutations : public BaseProblem {
public:
    Permutations(std::vector<Task> tasks);
    void calculate_heuristic() override;
    void generate_permutations(std::vector<std::vector<Task>> &permutations);
    void print_permutations(const std::vector<std::vector<Task>> &permutations);
    void calculate_Cmax_for_permutations(const std::vector<std::vector<Task>> &permutations);
};
#endif //PERMUTATIONS_H
