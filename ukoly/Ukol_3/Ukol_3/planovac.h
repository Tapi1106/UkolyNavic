#ifndef PLANOVAC_H
#define PLANOVAC_H

#include "Bludiste.h"
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// T��da pro pl�nov�n� cesty
class Planovac {
public:
    Bludiste& bludiste;  // Odkaz na objekt bludi�t�

    // Konstruktor t��dy Planovac
    Planovac(Bludiste& b) : bludiste(b) {}

    // Metoda pro nalezen� nejkrat�� cesty (BFS)
    vector<Bod> najdi_cestu() {
        vector<vector<bool>> navstiveno(bludiste.mapa.size(), vector<bool>(bludiste.mapa[0].size(), false));
        vector<vector<Bod>> predchozi(bludiste.mapa.size(), vector<Bod>(bludiste.mapa[0].size()));
        queue<Bod> q;

        q.push(bludiste.start);
        navstiveno[bludiste.start.x][bludiste.start.y] = true;

        const vector<Bod> smer = { Bod(1, 0), Bod(-1, 0), Bod(0, 1), Bod(0, -1) }; // dol�, nahoru, vpravo, vlevo

        while (!q.empty()) {
            Bod aktualni = q.front();
            q.pop();

            // Pokud jsme dos�hli c�le, sestav�me cestu
            if (aktualni.x == bludiste.cil.x && aktualni.y == bludiste.cil.y) {
                vector<Bod> cesta;
                Bod p = bludiste.cil;
                while (!(p.x == bludiste.start.x && p.y == bludiste.start.y)) {
                    cesta.push_back(p);
                    p = predchozi[p.x][p.y];
                }
                cesta.push_back(bludiste.start);
                reverse(cesta.begin(), cesta.end());
                return cesta;
            }

            // Prozkoum�me v�echny sousedy
            for (const Bod& s : smer) {
                int nx = aktualni.x + s.x;
                int ny = aktualni.y + s.y;

                if (nx >= 0 && nx < bludiste.mapa.size() && ny >= 0 && ny < bludiste.mapa[0].size() &&
                    !navstiveno[nx][ny] && (bludiste.mapa[nx][ny] == '.' || bludiste.mapa[nx][ny] == 'E')) {
                    navstiveno[nx][ny] = true;
                    predchozi[nx][ny] = aktualni;
                    q.push(Bod(nx, ny));
                }
            }
        }

        return {}; // Pokud cesta neexistuje, vrac�me pr�zdn� vektor
    }
};

#endif
