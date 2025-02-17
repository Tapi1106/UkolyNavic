#ifndef BLUDISTE_H
#define BLUDISTE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Struktura pro bod (souøadnice)
struct Bod {
    int x, y;
    Bod(int x = 0, int y = 0) : x(x), y(y) {}
};

// Tøída pro bludištì
class Bludiste {
public:
    vector<vector<char>> mapa;
    Bod start, cil;

    // Konstruktor naèítající bludištì ze souboru
    Bludiste(const string& soubor) {
        ifstream file(soubor);
        if (!file) {
            cerr << "Nelze otevøít soubor!" << endl;
            exit(1);
        }

        string line;
        while (getline(file, line)) {
            mapa.push_back(vector<char>(line.begin(), line.end()));
        }

        // Najít startovní a cílový bod
        for (int i = 0; i < mapa.size(); ++i) {
            for (int j = 0; j < mapa[i].size(); ++j) {
                if (mapa[i][j] == 'S') {
                    start = Bod(i, j);
                }
                else if (mapa[i][j] == 'E') {
                    cil = Bod(i, j);
                }
            }
        }
    }

    // Metoda pro vykreslení bludištì
    void vykresli() const {
        for (const auto& radek : mapa) {
            for (char policko : radek) {
                cout << policko;
            }
            cout << endl;
        }
    }
};

#endif
