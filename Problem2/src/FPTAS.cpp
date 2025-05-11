#include "FPTAS.hpp"
#include <cmath>     // Dla std::floor
#include <iostream>  // Dla std::cout, std::cerr

FPTAS::FPTAS(std::vector<Task> tasks, int maszyny)
    : BaseProblem(tasks, maszyny) {
    std::cout << "FPTAS initialized (epsilon = " << epsilon << ")" << std::endl;
    if (this->maszyny != 2 && !this->tasks.empty()) {
        std::cerr << "Ostrzezenie: FPTAS zaimplementowany tutaj jest dla 2 maszyn." << std::endl;
    }
}

// Prywatna metoda PD zaadaptowana z PDynamczine
std::vector<Processor> FPTAS::solve_p2_cmax_with_dp(const std::vector<Task>& tasks_to_schedule) {
    std::vector<Processor> assigned_processors(2);
    assigned_processors[0].id = 1;
    assigned_processors[1].id = 2;

    int n = tasks_to_schedule.size();
    if (n == 0) {
        return assigned_processors;
    }

    long long total_scaled_processing_time = 0;
    for (const auto& task : tasks_to_schedule) {
        total_scaled_processing_time += task.processing_time;
    }

    if (total_scaled_processing_time == 0) {
        for (const auto& task : tasks_to_schedule) {
            assigned_processors[0].tasks.push_back(task);
        }
        return assigned_processors;
    }

    int max_sum_on_one_processor = static_cast<int>(total_scaled_processing_time / 2);
    std::vector<std::vector<bool>> T(n + 1, std::vector<bool>(max_sum_on_one_processor + 1, false));

    for (int i = 0; i <= n; ++i) {
        T[i][0] = true;
    }

    for (int j = 1; j <= n; ++j) {
        int pj = tasks_to_schedule[j-1].processing_time;
        for (int s = 0; s <= max_sum_on_one_processor; ++s) {
            T[j][s] = T[j-1][s];
            if (s >= pj && T[j-1][s - pj]) {
                T[j][s] = true;
            }
        }
    }

    int optimal_sum_proc1 = 0;
    for (int s = max_sum_on_one_processor; s >= 0; --s) {
        if (T[n][s]) {
            optimal_sum_proc1 = s;
            break;
        }
    }

    int current_sum_on_proc1 = optimal_sum_proc1;
    for (int j = n; j > 0; --j) {
        const auto& current_task = tasks_to_schedule[j-1];
        int pj = current_task.processing_time;

        if (current_sum_on_proc1 >= pj && T[j-1][current_sum_on_proc1 - pj]) {
            assigned_processors[0].tasks.push_back(current_task);
            current_sum_on_proc1 -= pj;
        } else {
            assigned_processors[1].tasks.push_back(current_task);
        }
    }
    return assigned_processors;
}


void FPTAS::calculate_heuristic() {
    if (this->maszyny != 2) {
        std::cerr << "me need two machines" << std::endl;
        if (!this->tasks.empty() && !this->processors.empty()) {
             for(auto& proc : this->processors) {
                 proc.tasks.clear();
             }
        }
        return;
    }

    if (this->tasks.empty()) {
        return;
    }

    long long total_original_processing_time = 0;
    for (const auto& task : this->tasks) {
        total_original_processing_time += task.processing_time;
    }
    // jak łączny czas na wszystkich zadaniach wynosi 0 to nie ma co robić
    if (total_original_processing_time == 0) {
        if (!this->processors.empty()) {
             this->processors[0].tasks.clear();
             for(const auto& task : this->tasks) {
                this->processors[0].tasks.push_back(task);
            }
             if (this->processors.size() > 1) this->processors[1].tasks.clear();
        }
        return;
    }

    // Krok 1: Oblicz współczynnik skalujący k
    double k_double = std::floor((epsilon * static_cast<double>(total_original_processing_time)) /
                                 (2.0 * static_cast<double>(this->tasks.size())));

    int k_scaler = static_cast<int>(k_double);
    if (k_scaler < 1) {
        k_scaler = 1;
    }

    // Krok 2: Stwórz nową listę zadań z przeskalowanymi czasami
    std::vector<Task> scaled_tasks_with_ids;
    scaled_tasks_with_ids.reserve(this->tasks.size());
    for (const auto& original_task : this->tasks) {
        scaled_tasks_with_ids.push_back(
            Task(original_task.id,
                 static_cast<int>(std::floor(static_cast<double>(original_task.processing_time) / k_scaler)))
        );
    }

    // Krok 3: Rozwiąż problem P2||Cmax dla przeskalowanych zadań
    std::vector<Processor> assignment_from_dp = solve_p2_cmax_with_dp(scaled_tasks_with_ids);

    // Krok 4: Zastosuj przypisanie do oryginalnych zadań
    if (this->processors.size() == 2) {
        this->processors[0].tasks.clear();
        this->processors[1].tasks.clear();
    } else {
        this->processors.clear();
        Processor p1_instance, p2_instance;
        p1_instance.id = 1;
        p2_instance.id = 2;
        this->processors.push_back(p1_instance);
        this->processors.push_back(p2_instance);
    }

    for (const auto& task_from_dp_proc0 : assignment_from_dp[0].tasks) {
        for (const auto& original_task : this->tasks) {
            if (original_task.id == task_from_dp_proc0.id) {
                this->processors[0].tasks.push_back(original_task);
                break;
            }
        }
    }

    for (const auto& task_from_dp_proc1 : assignment_from_dp[1].tasks) {
        for (const auto& original_task : this->tasks) {
            if (original_task.id == task_from_dp_proc1.id) {
                this->processors[1].tasks.push_back(original_task);
                break;
            }
        }
    }
}