#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> extract_bigrams(const string& str) {
    vector<string> bigrams;
    for (int i = 0; i < str.size() - 1; i++) {
        bigrams.push_back(str.substr(i, 2));
    }
    return bigrams;
}

int main()
{
    string str = "Ciao, mi chiamo Francesco";
    vector<string> bigrams = extract_bigrams(str);
    for (const string& bg : bigrams) {
        cout << bg << endl;
    }
    return 0;
}