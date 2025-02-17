#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "cisla.h" // Na�ten� ��sel ze souboru

using namespace std;
using namespace chrono;

// Implementace sekven�n�ho vyhled�v�n� (Linear Search)
// https://cs.wikipedia.org/wiki/Line%C3%A1rn%C3%AD_vyhled%C3%A1v%C3%A1n%C3%AD
int linearSearch(const vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i; // Nalezeno, vrac�me index
        }
    }
    return -1; // Nenalezeno
}

// Implementace bin�rn�ho vyhled�v�n� (Binary Search)
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
    vector<int> data = numbers; // Na�ten� dat z cisla.h
    int target = 57; // Hledan� hodnota

    // M��en� �asu pro Linear Search
    auto start = high_resolution_clock::now();
    int linearResult = linearSearch(data, target);
    auto stop = high_resolution_clock::now();
    auto linearDuration = duration_cast<nanoseconds>(stop - start);

    // M��en� �asu pro Binary Search
    start = high_resolution_clock::now();
    int binaryResult = binarySearch(data, target);
    stop = high_resolution_clock::now();
    auto binaryDuration = duration_cast<nanoseconds>(stop - start);

    // V�sledky
    cout << "Linear Search: " << (linearResult != -1 ? "Nalezeno" : "Nenalezeno") << " at index " << linearResult << " in " << linearDuration.count() << " ns\n";
    cout << "Binary Search: " << (binaryResult != -1 ? "Nalezeno" : "Nenalezeno") << " at index " << binaryResult << " in " << binaryDuration.count() << " ns\n";

    // Anal�za efektivity
    cout << "\nAnalyza:\n";
    if (linearDuration > binaryDuration)
        cout << "Binary Search je efektivnejsi pro serazena data.\n";
    else
        cout << "Linear Search je efektivnejsi pro serazena data .\n";

    return 0;
}
