//
// Created by Mateusz Wojtaszek on 31/03/2025.
//

#include "Schrage.h"
#include <queue>

Schrage::Schrage(std::vector<Task> tasks) : BaseProblem(tasks) {
}


void Schrage::calculate_heuristic() {
    // Sprawdzenie, czy są jakiekolwiek zadania do przetworzenia
    if (tasks.empty()) {
        return; // Nic do zrobienia
    }

    // Definicja komparatora dla kolejki N (min-heap wg release_time)
    auto cmp_r = [](const Task &a, const Task &b) {
        // Jeśli czasy równe, można dodać dodatkowe kryterium (np. ID) dla stabilności
        if (a.release_time == b.release_time) return a.id > b.id; // Opcjonalnie
        return a.release_time > b.release_time;
    };

    // Definicja komparatora dla kolejki G (max-heap wg cooling_time)
    auto cmp_q = [](const Task &a, const Task &b) {
        // Jeśli czasy równe, można dodać dodatkowe kryterium (np. ID) dla stabilności
        if (a.cooling_time == b.cooling_time) return a.id > b.id; // Opcjonalnie
        return a.cooling_time < b.cooling_time;
    };

    // Kolejka priorytetowa N: zadania niegotowe (min-heap wg r_j)
    std::priority_queue<Task, std::vector<Task>, decltype(cmp_r)> N(cmp_r);

    // Kolejka priorytetowa G: zadania gotowe (max-heap wg q_j)
    std::priority_queue<Task, std::vector<Task>, decltype(cmp_q)> G(cmp_q);

    // Wypełnienie kolejki N wszystkimi zadaniami (kopiami, oryginały zostają w tasks na razie)
    for (const auto &task: this->tasks) {
        // Używamy this->tasks jako źródła
        N.push(task);
    }

    int t = 0; // Aktualny czas
    std::vector<Task> pi; // Wektor na wynikową permutację
    pi.reserve(this->tasks.size()); // Pre-alokacja pamięci dla wydajności

    // Główna pętla algorytmu
    while (!N.empty() || !G.empty()) {
        // Przenieś dostępne zadania z N do G
        while (!N.empty() && N.top().release_time <= t) {
            G.push(N.top());
            N.pop();
        }

        // Jeśli nie ma gotowych zadań, przesuń czas
        if (G.empty()) {
            // Upewnij się, że N nie jest puste przed dostępem do N.top()
            // (teoretycznie niemożliwe, jeśli while(!N.empty() || !G.empty()) jest prawdziwe)
            if (!N.empty()) {
                t = N.top().release_time;
            }
            // W przeciwnym razie (N i G puste), pętla while się zakończy
        } else {
            // Wybierz zadanie z G z największym q_j
            Task e = G.top();
            G.pop();

            // Dodaj zadanie do permutacji wynikowej
            pi.push_back(e);

            // Zaktualizuj czas
            t += e.processing_time;

        }
    }
    // Po zakończeniu pętli, wektor 'pi' zawiera poprawną permutację Schrage'a.
    this->tasks = pi;
}
