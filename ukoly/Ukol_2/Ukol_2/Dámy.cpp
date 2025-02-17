#include <iostream>
#include <vector>
#include <cmath>

// Funkce pro zkontrolování, zda je pozice bezpeèná pro umístìní dámy
bool isSafe(int row, int col, const std::vector<int>& positions) {
    for (int i = 0; i < row; i++) {
        // Kontrola stejného sloupce nebo diagonál
        if (positions[i] == col || abs(positions[i] - col) == row - i) {
            return false;
        }
    }
    return true;
}

// Rekurzivní funkce pro nalezení všech øešení
void solveNQuens(int row, std::vector<int>& positions, int& solutionCount) {
    int n = positions.size();

    if (row == n) {
        solutionCount++;
        // Vytiskneme aktuální konfiguraci
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

    // Pro každou pozici ve sloupci aktuální øady
    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, positions)) {
            positions[row] = col;
            solveNQuens(row + 1, positions, solutionCount); // Rekurzivnì zkoušíme další øadu
            // Pokud se žádné øešení nenajde, pozice bude zkoušena s jinými sloupci
        }
    }
}
//https://cs.wikipedia.org/wiki/Probl%C3%A9m_osmi_dam
int main() {
    int n = 8; 
    std::vector<int> positions(n, -1); // Pole pro uchování pozic dám (indexy sloupcù)
    int solutionCount = 0;

    // Zaèneme hledat øešení od první øady
    solveNQuens(0, positions, solutionCount);

    std::cout << "Celkovy pocet reseni: " << solutionCount << std::endl;

    return 0;
}
