//
// Created by Patryk Dudziński on 3/04/2025.
//

#pragma once
#include "BaseProblem.h"


class SchrageDiv:public BaseProblem {
public:
    explicit SchrageDiv(std::vector<Task> tasks);
    void calculate_heuristic() override;
};



