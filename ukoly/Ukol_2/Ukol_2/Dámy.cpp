#include <iostream>
#include <vector>
#include <cmath>

// Funkce pro zkontrolov�n�, zda je pozice bezpe�n� pro um�st�n� d�my
bool isSafe(int row, int col, const std::vector<int>& positions) {
    for (int i = 0; i < row; i++) {
        // Kontrola stejn�ho sloupce nebo diagon�l
        if (positions[i] == col || abs(positions[i] - col) == row - i) {
            return false;
        }
    }
    return true;
}

// Rekurzivn� funkce pro nalezen� v�ech �e�en�
void solveNQuens(int row, std::vector<int>& positions, int& solutionCount) {
    int n = positions.size();

    if (row == n) {
        solutionCount++;
        // Vytiskneme aktu�ln� konfiguraci
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (positions[i] == j)
                    std::cout << "Q";
                else
                    std::cout << ".";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        return;
    }

    // Pro ka�dou pozici ve sloupci aktu�ln� �ady
    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, positions)) {
            positions[row] = col;
            solveNQuens(row + 1, positions, solutionCount); // Rekurzivn� zkou��me dal�� �adu
            // Pokud se ��dn� �e�en� nenajde, pozice bude zkou�ena s jin�mi sloupci
        }
    }
}
//https://cs.wikipedia.org/wiki/Probl%C3%A9m_osmi_dam
int main() {
    int n = 8; 
    std::vector<int> positions(n, -1); // Pole pro uchov�n� pozic d�m (indexy sloupc�)
    int solutionCount = 0;

    // Za�neme hledat �e�en� od prvn� �ady
    solveNQuens(0, positions, solutionCount);

    std::cout << "Celkovy pocet reseni: " << solutionCount << std::endl;

    return 0;
}
