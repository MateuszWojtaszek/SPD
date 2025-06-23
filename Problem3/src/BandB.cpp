// Plik: BandB.cpp
#include "BandB.hpp"
#include "NEH.hpp" // Potrzebny do wyznaczenia początkowego górnego ograniczenia
#include <algorithm>
#include <limits>
#include <numeric>
#include <iostream>

BandB::BandB(std::vector<Task> tasks, int maszyny) : BaseProblem(tasks, maszyny) {
    std::cout << "Branch and Bound" << std::endl;
    this->upper_bound = std::numeric_limits<int>::max(); // Inicjalizacja UB jako nieskończoność
}

// Główna funkcja, którą wywołuje main
void BandB::calculate_heuristic() {
    // --- Inicjalizacja ---
    // Używamy NEH do znalezienia początkowego górnego ograniczenia (UB)
    NEH neh_for_ub(tasks, maszyny);
    neh_for_ub.calculate_heuristic();
    upper_bound = neh_for_ub.get_cmax();
    best_permutation_so_far = neh_for_ub.get_tasks();

    // Debug: Wyświetlenie początkowego górnego ograniczenia
    //std::cout << "B&B: Initial Upper Bound from NEH = " << upper_bound << std::endl;

    // Wektory do przeszukiwania rekurencyjnego
    std::vector<Task> initial_permutation; // Zaczynamy od pustej permutacji
    std::vector<Task> initial_unscheduled = tasks; // Na początku wszystkie zadania są nieuszeregowane

    // Uruchom rekurencyjne przeszukiwanie drzewa
    branch(initial_permutation, initial_unscheduled);

    // Po zakończeniu przeszukiwania, przypisz znalezioną optymalną permutację
    tasks = best_permutation_so_far;
}

// Rekurencyjna funkcja przeszukująca drzewo rozwiązań
void BandB::branch(std::vector<Task> &current_permutation, std::vector<Task> &unscheduled_tasks) {
    // Jeśli zadań do uszeregowania się skończyły -> liść (pełna permutacja)
    if (unscheduled_tasks.empty()) {
        // Porównanie czy jest lepszy od UB.
        int final_cmax = cmax_calcualate(current_permutation);
        if (final_cmax < upper_bound) {
            upper_bound = final_cmax; // Aktualizujemy najlepszy wynik
            best_permutation_so_far = current_permutation; // Zapisujemy najlepszą permutację
        }
        return; // Zakończ tę gałąź
    }

    // Pętla po wszystkich nieuszeregowanych jeszcze zadaniach
    for (size_t i = 0; i < unscheduled_tasks.size(); ++i) {
        // Tworzymy nową, dłuższą permutację częściową
        std::vector<Task> new_permutation = current_permutation;
        new_permutation.push_back(unscheduled_tasks[i]);

        // Tworzymy nowy wektor zadań pozostałych do uszeregowania,
        // ale bez zadania, które właśnie wybraliśmy do uszeregowania
        std::vector<Task> new_unscheduled = unscheduled_tasks;
        new_unscheduled.erase(new_unscheduled.begin() + i);

        // Obliczamy dolne ograniczenie (LB) dla tego nowego węzła
        int lower_bound = calculate_lower_bound(new_permutation, new_unscheduled);

        // --- PRZYCINANIE (PRUNING) ---
        // Jeśli optymistyczne oszacowanie (LB) jest już gorsze lub równe
        // niż najlepszy znaleziony dotąd wynik (UB), nie ma sensu dalej badać tej gałęzi.
        if (lower_bound < upper_bound) {
            // Jeśli węzeł jest obiecujący, kontynuuj w głąb drzewa
            branch(new_permutation, new_unscheduled);
        }
        // W przeciwnym razie, gałąź jest "przycinana" i pętla idzie dalej.
    }
}

// Funkcja obliczająca dolne ograniczenie (LB)
int BandB::calculate_lower_bound(const std::vector<Task>& partial_permutation,
                                 const std::vector<Task>& unscheduled_tasks) {

    // --- Krok 1: Oblicz czasy zakończenia dla już uszeregowanych zadań ---
    std::vector<std::vector<int>> completion_times(partial_permutation.size(), std::vector<int>(maszyny));

    if (!partial_permutation.empty()) {
        for (size_t job_idx = 0; job_idx < partial_permutation.size(); ++job_idx) {
            for (int machine_idx = 0; machine_idx < maszyny; ++machine_idx) {

                int c_prev_job;
                if (job_idx > 0) {
                    // Jeśli to nie jest pierwsze zadanie, bierzemy Cmax poprzedniego zadania na tej maszynie.
                    c_prev_job = completion_times[job_idx - 1][machine_idx];
                } else {
                    // Dla pierwszego zadania ten czas wynosi 0.
                    c_prev_job = 0;
                }

                int c_prev_machine;
                if (machine_idx > 0) {
                    // Jeśli to nie jest pierwsza maszyna, bierzemy Cmax tego zadania na poprzedniej maszynie.
                    c_prev_machine = completion_times[job_idx][machine_idx - 1];
                } else {
                    // Dla pierwszej maszyny ten czas wynosi 0.
                    c_prev_machine = 0;
                }

                int proc_time = partial_permutation[job_idx].processing_time[machine_idx];

                completion_times[job_idx][machine_idx] = std::max(c_prev_job, c_prev_machine) + proc_time;
            }
        }
    }

    if (unscheduled_tasks.empty()) {
        return completion_times.back().back();
    }

    // --- Krok 2: Zsumuj minimalny pozostały czas pracy dla każdej maszyny ---
    std::vector<int> sum_of_remaining_times(maszyny, 0);
    for (const auto& task : unscheduled_tasks) {
        for (int machine_idx = 0; machine_idx < maszyny; ++machine_idx) {
            sum_of_remaining_times[machine_idx] += task.processing_time[machine_idx];
        }
    }

    // --- Krok 3: Oblicz dolne ograniczenie (Lower Bound) ---
    int lower_bound = 0;

    std::vector<int> last_job_c_times;
    if (partial_permutation.empty()) {
        // Jeśli permutacja jest pusta (korzeń drzewa), czasy zakończenia wynoszą 0.
        last_job_c_times.assign(maszyny, 0);
    } else {
        // W przeciwnym razie, pobieramy ostatni wiersz z macierzy czasów zakończenia.
        last_job_c_times = completion_times.back();
    }

    for (int machine_idx = 0; machine_idx < maszyny; ++machine_idx) {
        int bound_for_machine = last_job_c_times[machine_idx] + sum_of_remaining_times[machine_idx];
        lower_bound = std::max(lower_bound, bound_for_machine);
    }

    return lower_bound;
}
