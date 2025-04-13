//
// Created by Patryk Dudziński on 3/04/2025.
//

#include "SchrageDiv.h"
#include <queue>
#include <algorithm>

SchrageDiv::SchrageDiv(std::vector<Task> tasks) : BaseProblem(tasks) {
}

void SchrageDiv::calculate_heuristic() {
    if (tasks.empty()) {
        return;
    }

    // Komparator dla N (min-heap wg r_j, potem ID dla stabilności)
    auto cmp_r = [](const Task *a, const Task *b) {
        if (a->release_time == b->release_time) return a->id > b->id;
        return a->release_time > b->release_time;
    };

    // Komparator dla G (max-heap wg q_j, potem ID dla stabilności)
    auto cmp_q = [](const Task *a, const Task *b) {
        if (a->cooling_time == b->cooling_time) return a->id > b->id;
        return a->cooling_time < b->cooling_time;
    };

    // Kolejki priorytetowe przechowujące wskaźniki do zadań
    std::priority_queue<Task *, std::vector<Task *>, decltype(cmp_r)> N(cmp_r);
    std::priority_queue<Task *, std::vector<Task *>, decltype(cmp_q)> G(cmp_q);

    // Reset stanu i wypełnienie N wskaźnikami do kopii zadań
    for (Task &task: tasks) {
        // task.processing_time = task.processing_time; // Resetuj pozostały czas
        N.push(&task);
    }

    long long current_time = 0;
    long long cmax_result = 0;
    Task *current_task_ptr = nullptr; // Wskaźnik na aktualnie wykonywane zadanie

    // Ustaw czas początkowy na czas dostępności pierwszego zadania
    if (!N.empty()) {
        current_time = N.top()->release_time;
    } else {
        return; // Brak zadań
    }

    // Główna pętla symulacji
    while (!N.empty() || !G.empty() || current_task_ptr != nullptr) {
        // 1. Przenieś wszystkie zadania, które stały się dostępne do G
        while (!N.empty() && N.top()->release_time <= current_time) {
            G.push(N.top());
            N.pop();
        }

        // 2. Sprawdź warunek przerwania, jeśli jakieś zadanie jest wykonywane
        if (current_task_ptr != nullptr && !G.empty()) {
            // Jeśli najlepsze zadanie w G ma większe q niż bieżące...
            if (G.top()->cooling_time > current_task_ptr->cooling_time) {
                // ... przerwij bieżące zadanie: dodaj je z powrotem do G
                G.push(current_task_ptr);
                current_task_ptr = nullptr; // Maszyna staje się wolna
            }
        }

        // 3. Wybierz nowe zadanie do wykonania, jeśli maszyna jest wolna
        if (current_task_ptr == nullptr && !G.empty()) {
            current_task_ptr = G.top(); // Wybierz zadanie z największym q
            G.pop(); // Usuń je z G
        }

        // --- Oblicz, o ile przesunąć czas ---
        long long time_step = 1; // 0
        // if (current_task_ptr != nullptr) {
        //     // Opcja 1: Aktualnie wykonywane zadanie się zakończy
        //     time_step = current_task_ptr->processing_time;

        //     // Opcja 2: Nadejdzie nowe zadanie wcześniej
        //     if (!N.empty()) {
        //         long long time_to_next_arrival = N.top()->release_time - current_time;
        //         // Jeśli nadejście jest w przyszłości i wcześniej niż zakończenie
        //         if (time_to_next_arrival > 0 && time_to_next_arrival < time_step) {
        //             time_step = time_to_next_arrival;
        //         }
        //         // Jeśli nadejście jest teraz lub w przeszłości, krok = 0
        //         else if (time_to_next_arrival <= 0) {
        //             time_step = 0; // Przetwórz zdarzenia w obecnej chwili
        //         }
        //     }
        // } else {
        //     // Maszyna jest bezczynna
        //     if (!N.empty()) {
        //         // Czekaj na następne zadanie
        //         time_step = N.top()->release_time - current_time;
        //         if (time_step < 0) time_step = 0; // Jeśli już nadeszło
        //     } else {
        //         // N puste, G puste, nic nie jest wykonywane -> Koniec
        //         if (G.empty()) break;
        //         // Jeśli G nie jest puste, to zadanie powinno zostać wybrane powyżej.
        //         // Ten `else` nie powinien być osiągnięty, jeśli G nie jest puste.
        //         time_step = 0; // Na wszelki wypadek
        //     }
        // }


        // --- Przesuń czas i zaktualizuj stan ---
        // if (time_step > 0) {
        current_time += time_step; // Przesuń czas
        if (current_task_ptr != nullptr) {
            // Zmniejsz pozostały czas bieżącego zadania
            current_task_ptr->processing_time -= time_step;
        }
        // }

        // --- Sprawdź, czy zadanie się zakończyło (tylko jeśli krok > 0) ---
        if (current_task_ptr != nullptr && current_task_ptr->processing_time <= 0) {
            // Zadanie zakończone
            cmax_result = std::max(cmax_result, current_time + current_task_ptr->cooling_time);
            current_task_ptr = nullptr; // Maszyna staje się wolna
        }

        // Jeśli time_step był 0 (np. nowe zadanie przybyło dokładnie teraz),
        // pętla wykona się ponownie, aby przetworzyć nowe zadania w G i ewentualnie przerwać/wybrać zadanie.
    } // Koniec pętli while

    this -> Cmax = static_cast<int>(cmax_result);
}
