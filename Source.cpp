#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Game {
    int id;
    string name;
    int year;
    int rating;
};
vector<string> split(const string& str, char delim)
{
    vector<string> tokens;

    if (!str.empty())
    {
        size_t start = 0, end;
        do {

            end = str.find(delim, start);
            tokens.push_back(str.substr(start, (end - start)));
            start = end + 1;
        } while (end != string::npos);
    }

    return tokens;
}

int main()
{
    vector<Game> games;

    ifstream fin("games.csv");
    if (fin.is_open()) {
        while (!fin.eof()) {
            string str;
            getline(fin, str);
            auto tokens = split(str, ';');
            Game c;
            c.id = stoi(tokens[0]);
            c.name = tokens[1];
            c.year = stoi(tokens[2]);
            c.rating = stoi(tokens[3]);
            games.push_back(c);
        }

        sort(games.begin(), games.end(), [](const Game& c1, const Game& c2) {
            return c1.year < c2.year;
            });
        for (const auto& c : games) {
            if (c.year > 2003)
                cout << c.id << "," << c.name << endl;
        }
        ofstream fout("games_out.csv");
        if (fout.is_open()) {
            for (const auto& c : games) {
                fout << c.id << "," << c.name << endl;
            }
        }

    }
    return 0;
}