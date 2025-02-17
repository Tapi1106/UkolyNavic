#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "cisla.h" // Naètení èísel ze souboru

using namespace std;
using namespace chrono;

// Implementace sekvenèního vyhledávání (Linear Search)
// https://cs.wikipedia.org/wiki/Line%C3%A1rn%C3%AD_vyhled%C3%A1v%C3%A1n%C3%AD
int linearSearch(const vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i; // Nalezeno, vracíme index
        }
    }
    return -1; // Nenalezeno
}

// Implementace binárního vyhledávání (Binary Search)
//https://cs.wikipedia.org/wiki/Bin%C3%A1rn%C3%AD_vyhled%C3%A1v%C3%A1n%C3%AD
int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid; // Nalezeno
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // Nenalezeno
}

int main() {
    vector<int> data = numbers; // Naètení dat z cisla.h
    int target = 57; // Hledaná hodnota

    // Mìøení èasu pro Linear Search
    auto start = high_resolution_clock::now();
    int linearResult = linearSearch(data, target);
    auto stop = high_resolution_clock::now();
    auto linearDuration = duration_cast<nanoseconds>(stop - start);

    // Mìøení èasu pro Binary Search
    start = high_resolution_clock::now();
    int binaryResult = binarySearch(data, target);
    stop = high_resolution_clock::now();
    auto binaryDuration = duration_cast<nanoseconds>(stop - start);

    // Výsledky
    cout << "Linear Search: " << (linearResult != -1 ? "Nalezeno" : "Nenalezeno") << " at index " << linearResult << " in " << linearDuration.count() << " ns\n";
    cout << "Binary Search: " << (binaryResult != -1 ? "Nalezeno" : "Nenalezeno") << " at index " << binaryResult << " in " << binaryDuration.count() << " ns\n";

    // Analýza efektivity
    cout << "\nAnalyza:\n";
    if (linearDuration > binaryDuration)
        cout << "Binary Search je efektivnejsi pro serazena data.\n";
    else
        cout << "Linear Search je efektivnejsi pro serazena data .\n";

    return 0;
}
