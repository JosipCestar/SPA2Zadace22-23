#include <iostream>
#include <list>
#include <random>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

vector<int> dobiznamenke(int broj) {
    vector<int> znamenke;

    if (broj == 0)
        return {0};

    while (broj > 0) {
        znamenke.push_back(broj % 10);
        broj /= 10;
    }

    return znamenke;
};

template<typename V>
struct HashTable {
    HashTable();

    vector<list<pair<int, V>>> kontajner;
    vector<int> randomVars;

    void insert(int key, V value);
    pair<int, V> search(int key);

    int hash(int key);

};

template<typename V>
HashTable<V>::HashTable() {
    default_random_engine generator(time(0));
    uniform_int_distribution<int> distribute(0, 6);

    for (int i = 0; i < 7; ++i)
        randomVars.push_back(distribute(generator));

    kontajner.resize(7);
}

template<typename V>
int HashTable<V>::hash(int key) {
    vector<int> znamenke = dobiznamenke(key);
    int sum = 0;

    for (int i = 0; i < znamenke.size(); ++i)
        sum += randomVars[i] * znamenke[i];

    return sum % 7;
}

template<typename V>
void HashTable<V>::insert(int key, V value) {
    int h = hash(key);

    auto it = find_if(kontajner[h].begin(), kontajner[h].end(), [&key](const auto &p){ return p.first == key; });
    if (it != kontajner[h].end())
        it->second = value;
    else
        kontajner[h].push_front({key, value});
}

template<typename V>
pair<int, V> HashTable<V>::search(int key) {
    int h = hash(key);

    auto it = find_if(kontajner[h].begin(), kontajner[h].end(), [&key](const auto &p){ return p.first == key; });
    if (it == kontajner[h].end()) {
        cout << "Nije pronaden kljuc"<< endl;
        return {};
    }
    else
        return *it;
}

int main() {
    HashTable<float> hashTable;

    vector<int> keys = {131, 261, 310, 8, 3, 1, 85, 79, 120, 210, 0};

    float value = 0.0f;
    for (auto key : keys) {
        hashTable.insert(key, value);
        value += 0.1f;
    }

    pair<int, float> p = hashTable.search(7);

    cout << p.first << ", " << p.second << endl;


    return 0;
}
