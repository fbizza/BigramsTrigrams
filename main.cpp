#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;


int clean_txt() {
    // This function removes punctuation and transforms every character to lowercase
    string filename = "../input.txt";
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error opening input file: " << filename << endl;
        return 1;
    }
    string word;
    ofstream output("../output.txt");
    if (!output.is_open()) {
        cerr << "Error opening output file: output.txt" << endl;
        return 1;
    }
    while (input >> word) {
        string clean_word;
        for (char c : word) {
            if (!ispunct(c)) {
                clean_word += tolower(c);
            }
        }
        if (!clean_word.empty()) {
            output << clean_word << " ";
        }
    }
    input.close();
    output.close();
}

vector<string> extract_bigrams(const string& str) {
    vector<string> bigrams;
    for (int i = 0; i < str.size() - 1; i++) {
        bigrams.push_back(str.substr(i, 2));
    }
    return bigrams;
}

int main()
{
    clean_txt();
    string str = "Ciao, mi chiamo Francesco";
    vector<string> bigrams = extract_bigrams(str);
    for (const string& bg : bigrams) {
        cout << bg << endl;
    }
    return 0;
}