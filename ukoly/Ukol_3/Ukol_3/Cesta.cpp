#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

class Bludiste {
public:
    vector<string> bludiste; 
    pair<int, int> start;    // Sou�adnice startovn� pozice
    pair<int, int> cil;      // Sou�adnice c�lov� pozice

    // Konstruktor na��taj�c� bludi�t� ze souboru
    Bludiste(const string& soubor)
    {
        nacteni_bludiste(soubor);
    }

    void nacteni_bludiste(const string& soubor)
    {
        ifstream file(soubor);
        string line;
        int y = 0;

        while (getline(file, line)) {
            bludiste.push_back(line);
            for (int x = 0; x < line.size(); ++x)
            {
                if (line[x] == 'S')
                    start = { y, x }; // Ulo�en� startovn� pozice
                if (line[x] == 'E')
                    cil = { y, x };   // Ulo�en� c�lov� pozice
            }
            ++y;
        }
    }

    // Funkce pro vykreslen� bludi�t� do konzole
    void vykreslit_bludiste()
    {
        for (const auto& row : bludiste)
            cout << row << endl;
    }

    // Funkce pro ulo�en� bludi�t� do souboru
    void uloz_bludiste(const string& soubor)
    {
        ofstream file(soubor);
        for (const auto& row : bludiste)
            file << row << endl;
    }
};

class Planovac
{
public:
    Bludiste& bludiste;
    Planovac(Bludiste& b) : bludiste(b) {}

    // Hled�n� nejkrat�� cesty pomoc� BFS (Breadth-First Search)
    vector<pair<int, int>> najdi_cestu()
    {
        int rows = bludiste.bludiste.size();
        int cols = bludiste.bludiste[0].size();
        vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // Sm�ry pohybu
        queue<pair<pair<int, int>, vector<pair<int, int>>>> q;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        q.push({ bludiste.start, {bludiste.start} }); 
        visited[bludiste.start.first][bludiste.start.second] = true;

        while (!q.empty())
        {
            auto front = q.front();
            q.pop();

            pair<int, int> current_pos = front.first;
            vector<pair<int, int>> path = front.second;

            if (current_pos == bludiste.cil)
                return path; // Pokud jsme dos�hli c�le, vrac�me cestu

            for (const auto& dir : directions)
            {
                int new_y = current_pos.first + dir.first;
                int new_x = current_pos.second + dir.second;

                // Ov��en� platnosti nov�ho kroku
                if (new_y >= 0 && new_y < rows && new_x >= 0 && new_x < cols &&
                    !visited[new_y][new_x] && bludiste.bludiste[new_y][new_x] != '#')
                {
                    visited[new_y][new_x] = true;
                    vector<pair<int, int>> new_path = path;
                    new_path.push_back({ new_y, new_x });
                    q.push({ {new_y, new_x}, new_path });
                }
            }
        }
        return {};
    }

    // Funkce pro vykreslen� cesty v bludi�ti pomoc� symbolu '*' fancy way
    void vykresli_cestu(const vector<pair<int, int>>& cesta)
    {
        for (size_t i = 1; i < cesta.size() - 1; ++i) 
        {
            bludiste.bludiste[cesta[i].first][cesta[i].second] = '*';
        }
    }
};

int main() {
    // Na�teme bludi�t� ze souboru
    Bludiste bludiste("bludiste.txt");
    cout << "Puvodni bludiste:\n";
    bludiste.vykreslit_bludiste();

    // Inicializace pl�nova�e
    Planovac planovac(bludiste);
    vector<pair<int, int>> cesta = planovac.najdi_cestu();

    // Pokud existuje cesta, vykresl�me ji
    if (!cesta.empty()) {
        cout << "\nNejkratsi cesta (souradnice):\n";
        for (const auto& step : cesta)
            cout << "(" << step.first << ", " << step.second << ")\n";

        cout << "\nPocet kroku: " << cesta.size() - 1 << "\n";
        planovac.vykresli_cestu(cesta);
        cout << "\nBludiste s cestou:\n";
        bludiste.vykreslit_bludiste();
        bludiste.uloz_bludiste("bludiste_s_cestou.txt");
    }
    else {
        cout << "\nCesta neexistuje.\n";
    }

    return 0;
}