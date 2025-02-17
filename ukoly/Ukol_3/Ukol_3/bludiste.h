#ifndef BLUDISTE_H
#define BLUDISTE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Struktura pro bod (sou�adnice)
struct Bod {
    int x, y;
    Bod(int x = 0, int y = 0) : x(x), y(y) {}
};

// T��da pro bludi�t�
class Bludiste {
public:
    vector<vector<char>> mapa;
    Bod start, cil;

    // Konstruktor na��taj�c� bludi�t� ze souboru
    Bludiste(const string& soubor) {
        ifstream file(soubor);
        if (!file) {
            cerr << "Nelze otev��t soubor!" << endl;
            exit(1);
        }

        string line;
        while (getline(file, line)) {
            mapa.push_back(vector<char>(line.begin(), line.end()));
        }

        // Naj�t startovn� a c�lov� bod
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

    // Metoda pro vykreslen� bludi�t�
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
