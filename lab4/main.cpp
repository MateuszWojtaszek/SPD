#include <iostream>
/*************************************************************************
 * n zadań J = {1, 2, 3, 4, 5...n}
 * 1 procesor
 * Pj - czas wykonywania zadania j
 * Rj - termin dostępności zadania j
 * Qj - czas stygnięcia zadania j
 * Cmax - długość szeregowania
 * np:
 * j|Pj|Rj|Qj
 * 1|2 |1 |2
 * 2|5 |2 |5
 * 3|1 |3 |1
 * 4|3 |0 |3
 * 5|2 |6 |2
 * pi = 4,1,3,2,5
 * Czas stygnięcia nie blokuje procesora (wyjmujesz ciasto z piekarnika to piekarnik wolny)
 * Cmax(pi) = 16
 * Cel: zminimalizować Cmax
 * Zadania:
 * 1) wygenreować instancje testową 5 elementową
 * 2) funckje liczącą kryterium
 * 3) sprawdzić działanie na instancji
 * 4) wygenerowanie permuitacji w pożadku lexograficznym dla instancji
 * 5) dla każdej wyliczyć funckje celu i sprawdzić
 **********************************************************************/



int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}