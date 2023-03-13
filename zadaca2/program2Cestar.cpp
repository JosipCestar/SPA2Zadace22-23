#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Database {
    Database(int m);

    vector<bool> kontajner;

    int h1(const string& s);
    int h2(const string& s);
    int h3(const string& s);
    int h4(const string& s);

    void insert(const string& username);
    string search(const string &username);
};

Database::Database(int m) {
    kontajner.resize(m, false);
}

int Database::h1(const string &s) {
    unsigned long long sum = 0;
    int m = kontajner.size();
    for (int i = 0; i < s.size(); ++i)
        sum += s[i] % m;

    return sum % m;
}

int Database::h2(const string &s) {
    unsigned long long sum = 0;
    int m = kontajner.size();
    for (int i = 0; i < s.size(); ++i)
        sum += (s[i] * int(pow(19, i))) % m;

    return (1 + sum) % m;
}

int Database::h3(const string &s) {
    unsigned long long sum = 0;
    int m = kontajner.size();
    for (int i = 0; i < s.size(); ++i)
        sum += (s[i] * int(pow(30, i))) % m;

    return (7 + sum) % m;
}

int Database::h4(const string &s) {
    unsigned long long sum = 0;
    int m = kontajner.size();
    for (int i = 0; i < s.size(); ++i)
        sum += (s[i] * int(pow(3, i)) * int(pow(7, i))) % m;

    return (3 + sum) % m;
}

void Database::insert(const string &username) {
    kontajner[h1(username)] = true;
    kontajner[h2(username)] = true;
    kontajner[h3(username)] = true;
    kontajner[h4(username)] = true;
}

string Database::search(const string &username) {
    string fail = "Element NIJE u tablici!";
    string succ = "Element je vjerojatno u tablici.";

    if (!kontajner[h1(username)])
        return fail;
    if (!kontajner[h2(username)])
        return fail;
    if (!kontajner[h3(username)])
        return fail;
    if (!kontajner[h4(username)])
        return fail;

    return succ;
}

int main() {
    Database db(100);

    vector<string> names = {
            "jopis107", "hstranput", "Matej293", "MateaCucman", "JosipCestar",
            "lanamak", "DanijelaValjak", "filipuranjek", "domagojziros", "lsanic",
            "TomislavVinkovic", "IvoSusac", "matej2810", "KresimirSecan",
            "inespejic", "InesSimunovic", "IvanFrantal", "Frle001", "inesstrapac",
            "mkolak", "Dpritisa", "istvavk", "mtoldi", "lbrodar5", "mkristic",
            "andreamatasovic", "balentovicanja", "IvanaVinkovic", "prakidzija",
            "DMV1204", "JMesaric", "KarloKampic", "jurick1910", "LarisaDarojkovic"
    };

    for (auto name : names)
        db.insert(name);


    cout << db.search("krko") << endl;
    cout << db.search("IvoSusac") << endl;
    cout << db.search("JosipCestar") << endl;
    cout << db.search("furanjek") << endl;
    cout << db.search("ivosusacministar") << endl;
    cout << db.search("ministarmathosa") << endl;
    cout << db.search("hstranput") << endl;



    return 0;
}