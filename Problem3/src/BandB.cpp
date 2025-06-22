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
    // 1. Użyj heurystyki NEH, aby znaleźć dobre rozwiązanie początkowe i mocne górne ograniczenie (UB).
    NEH neh_for_ub(tasks, maszyny);
    neh_for_ub.calculate_heuristic();
    upper_bound = neh_for_ub.get_cmax();
    best_permutation_so_far = neh_for_ub.get_tasks();

    std::cout << "B&B: Initial Upper Bound from NEH = " << upper_bound << std::endl;

    // 2. Przygotuj wektory do przeszukiwania rekurencyjnego
    std::vector<Task> initial_permutation; // Zaczynamy od pustej permutacji
    std::vector<Task> initial_unscheduled = tasks; // Na początku wszystkie zadania są nieuszeregowane

    // 3. Uruchom rekurencyjne przeszukiwanie drzewa
    branch(initial_permutation, initial_unscheduled);

    // 4. Po zakończeniu przeszukiwania, przypisz znalezioną optymalną permutację
    tasks = best_permutation_so_far;
}

// Rekurencyjna funkcja przeszukująca drzewo rozwiązań
void BandB::branch(std::vector<Task>& current_permutation, std::vector<Task>& unscheduled_tasks) {

    // Warunek bazowy rekurencji: jeśli nie ma już zadań do uszeregowania
    if (unscheduled_tasks.empty()) {
        // Dotarliśmy do liścia drzewa, czyli pełnej permutacji. Jej Cmax jest już obliczony
        // w ramach dolnego ograniczenia w poprzednim kroku. Sprawdzamy, czy jest lepszy od UB.
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

        // Tworzymy nowy wektor zadań pozostałych do uszeregowania
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
        // W przeciwnym razie (else), gałąź jest "przycinana" i pętla idzie dalej.
    }
}

// Funkcja obliczająca dolne ograniczenie (LB)
int BandB::calculate_lower_bound(const std::vector<Task>& partial_permutation, const std::vector<Task>& unscheduled_tasks) {

    // Krok 1: Oblicz macierz czasów zakończenia C dla permutacji częściowej
    std::vector<std::vector<int>> C(partial_permutation.size(), std::vector<int>(maszyny, 0));
    if (!partial_permutation.empty()) {
        for (size_t i = 0; i < partial_permutation.size(); ++i) {
            for (int j = 0; j < maszyny; ++j) {
                C[i][j] = std::max(i > 0 ? C[i - 1][j] : 0, j > 0 ? C[i][j - 1] : 0) + partial_permutation[i].processing_time[j];
            }
        }
    }

    // Jeśli nie ma już zadań do uszeregowania, LB jest po prostu Cmaxem pełnej permutacji
    if (unscheduled_tasks.empty()) {
        return C.back().back();
    }

    // Krok 2: Oblicz sumę czasów pozostałych zadań dla każdej maszyny
    std::vector<int> sum_of_remaining_times(maszyny, 0);
    for (const auto& task : unscheduled_tasks) {
        for (int j = 0; j < maszyny; ++j) {
            sum_of_remaining_times[j] += task.processing_time[j];
        }
    }

    // Krok 3: Oblicz LB jako maksimum po wszystkich maszynach
    int max_lb = 0;
    std::vector<int> c_times_last_job = partial_permutation.empty() ? std::vector<int>(maszyny, 0) : C.back();

    for (int j = 0; j < maszyny; ++j) {
        // LB dla maszyny j = (czas zakończenia ostatniego uszeregowanego zadania na tej maszynie) + (suma czasów reszty zadań na tej maszynie)
        int machine_lb = c_times_last_job[j] + sum_of_remaining_times[j];
        if (machine_lb > max_lb) {
            max_lb = machine_lb;
        }
    }

    return max_lb;
}