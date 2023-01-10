#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <chrono>
#include "NgramsOfWords.h"

using namespace std;


int clean_txt() {
    // This function removes punctuation and transforms every character to lowercase
    string filename = "../input.txt";
    ifstream input(filename);
    if (!input.is_open()) {
        cout << "Error opening input file" << endl;
        return 1;
    }
    string word;
    ofstream output("../clean_input.txt");
    if (!output.is_open()) {
        cout << "Error opening output file" << endl;
        return 1;
    }
    while (input >> word) {
        string clean_word;
        for (char c: word) {
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
    return 0;
}

//vector<string> extract_bigrams(const string& str) {
//    vector<string> bigrams;
//    for (int i = 0; i < str.size() - 1; i++) {
//        bigrams.push_back(str.substr(i, 2));
//    }
//    return bigrams;
//}

int main() {
    //clean_txt();
    NgramsOfWords s(3);

    auto begin = chrono::high_resolution_clock::now();
    s.compute_words_ngrams("../clean_input.txt");
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured for normal version: %.3f seconds.\n\n", elapsed.count() * 1e-9);

    auto begin2 = chrono::high_resolution_clock::now();
    s.parallel_compute_words_ngrams("../clean_input.txt");
    auto end2 = chrono::high_resolution_clock::now();
    auto elapsed2 = chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);
    printf("Time measured for parallel version: %.3f seconds.\n\n", elapsed2.count() * 1e-9);


}