//
// Created by Patryk Dudziński on 3/04/2025.
//

#pragma once
#include "BaseProblem.h"


class SchrageDiv:public BaseProblem {
public:
    int Cmax;
    explicit SchrageDiv(std::vector<Task> tasks);
    void calculate_heuristic() override;
    int get_thsis_Cmax() const {
        return Cmax;
    }

};



