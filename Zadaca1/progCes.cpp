#include <iostream>
#include <vector>
using namespace std;

template<typename Z>
class Dictionary{
private:
    vector<pair<int,Z>> kontejner;
    int velicina = 0;
public:
    Dictionary(int s);
    int HashFunction(int k, int i);

    typename vector<pair<int,Z>>::iterator search(int key) const;
    bool insert(int key, Z value);
    bool remove(int key);

    void print() const;
};

template<typename Z>
Dictionary<Z>::Dictionary(int s){
    for(int i=0;i<s;i++){
        pair<int,Z> temp = {-1, Z()};
        kontejner.push_back(temp);
    }
}

template<typename Z>
int Dictionary<Z>::HashFunction(int k, int i){
    int m =  kontejner.size();
    int h1 = k % m;
    int h2 = i * (1 + (k % (m-1)));
    int h = (h1 + h2) % m;
    return h;
}


template<typename Z>
typename vector<pair<int,Z>>::iterator Dictionary<Z>::search(int key) const{
    int i = 0;
    while(true){
        int hash = HashFunction(key, i);
        if(kontejner[hash].first == -1){
            return kontejner.end();
        }else if(kontejner[hash].first == key){
            return kontejner.begin() + hash;
        }
        i++;
    }
}

template<typename Z>
bool Dictionary<Z>::insert(int key, Z value){
    int i = 0;
    while(true){
        int hash = HashFunction(key, i);
        if(kontejner[hash].first == -1){
            kontejner[hash].first = key;
            kontejner[hash].second = value;
            velicina++;
            return true;
        }else if(kontejner[hash].first == key){
            kontejner[hash].second = value;
            return true;
        }
        i++;
    }

    return false;
}

template<typename Z>
bool Dictionary<Z>::remove(int key){
    int i = 0;
    while(true){
        int hash = HashFunction(key, i);
        if(kontejner[hash].first == key){
            kontejner[hash].first = -1;
            kontejner[hash].second = Z();
            velicina--;
            return true;
        }
        i++;
    }
    return false;
}

template<typename Z>
void Dictionary<Z>::print() const{
    for(auto i : kontejner){
        if(i.first == -1){
            cout << "NIL ";
        }else{
            cout << "K:" << i.first << " " << "V:" << i.second << " ";
        }
    }
    cout << endl;
}

int main(){
    vector<int> keys(10);
    vector<float> values {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f};

    Dictionary<float> dict(19);

    for(int i = 0; i < 10; i++){
        cin >> keys[i];
        dict.insert(keys[i], values[i]);
    }

    dict.remove(keys[6]);
    dict.insert(keys[2], 1.1);
    dict.print();
    return 0;
}