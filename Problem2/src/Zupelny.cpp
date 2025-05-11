
#include "Task.hpp"
#include "Processor.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "Zupelny.hpp"


Zupelny::Zupelny(std::vector<Task> tasks, int maszyny) : BaseProblem(tasks, maszyny) {
    std::cout << "Zupelny" << std::endl;
}

// Implementacja prywatnej funkcji pomocniczej z optymalizacją dla 2 maszyn
void Zupelny::find_best_assignment_recursive(
    int current_task_index,
    std::vector<Processor> current_processors_state,
    int& min_cmax,
    std::vector<Processor>& best_processors_state) {

    // Warunek bazowy rekurencji: wszystkie zadania zostały przypisane
    if (current_task_index == this->tasks.size()) {
        int current_overall_cmax = 0;
        // Oblicz Cmax dla bieżącego przypisania
        for (const auto& processor : current_processors_state) {
            if (processor.get_cmax() > current_overall_cmax) {
                current_overall_cmax = processor.get_cmax();
            }
        }

        // Jeśli znaleziono lepsze rozwiązanie (mniejszy Cmax), zaktualizuj
        if (current_overall_cmax < min_cmax) {
            min_cmax = current_overall_cmax;
            best_processors_state = current_processors_state;
        }
        return; // Zakończ tę gałąź rekurencji
    }

    // Pobierz bieżące zadanie do przypisania
    const Task& task_to_assign = this->tasks[current_task_index];

    // Optymalizacja dla przypadku P2||Cmax (dwie maszyny)
    // Aby uniknąć symetrycznych rozwiązań, pierwsze zadanie zawsze przypisujemy do pierwszej maszyny.
    // Dla pozostałych zadań próbujemy obu maszyn.
    if (this->maszyny == 2 && current_task_index == 0) {
        // Przypisz pierwsze zadanie do pierwszej maszyny (indeks 0)
        std::vector<Processor> next_processors_state = current_processors_state;
        next_processors_state[0].tasks.push_back(task_to_assign);
        find_best_assignment_recursive(current_task_index + 1, next_processors_state, min_cmax, best_processors_state);
    } else {
        // Standardowa logika dla M maszyn (>2 lub <2) lub dla zadań innych niż pierwsze przy 2 maszynach
        for (int i = 0; i < this->maszyny; ++i) {
            // Stwórz kopię stanu procesorów dla nowej gałęzi rekurencji
            std::vector<Processor> next_processors_state = current_processors_state;
            // Przypisz zadanie do i-tej maszyny w tej kopii
            next_processors_state[i].tasks.push_back(task_to_assign);

            // Wywołaj rekurencyjnie dla następnego zadania
            find_best_assignment_recursive(current_task_index + 1, next_processors_state, min_cmax, best_processors_state);
        }
    }
}

void Zupelny::calculate_heuristic() {
    // Sprawdzenie, czy są zadania do uszeregowania
    if (this->tasks.empty()) {
        for (auto& p : this->processors) {
            p.tasks.clear();
        }
        return;
    }

    // Sprawdzenie, czy są dostępne maszyny
    if (this->maszyny <= 0) {
        return;
    }

    // Inicjalizacja stanu początkowego dla rekurencji.
    std::vector<Processor> initial_processors_state;
    initial_processors_state.reserve(this->maszyny);
    for (int i = 0; i < this->maszyny; ++i) {
        Processor p;
        p.id = i + 1;
        initial_processors_state.push_back(p);
    }

    int min_cmax_found = std::numeric_limits<int>::max();
    std::vector<Processor> best_assignment;

    // Rozpocznij rekurencyjne przeszukiwanie
    find_best_assignment_recursive(0, initial_processors_state, min_cmax_found, best_assignment);

    // Zapisz najlepsze znalezione przypisanie
    if (!best_assignment.empty()) {
        this->processors = best_assignment;
    }
}