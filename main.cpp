#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <chrono>
#include "Sequential.h"
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
    ofstream output("../clean_input.txt");
    if (!output.is_open()) {
        cerr << "Error opening output file" << endl;
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
    return 0;
}

//vector<string> extract_bigrams(const string& str) {
//    vector<string> bigrams;
//    for (int i = 0; i < str.size() - 1; i++) {
//        bigrams.push_back(str.substr(i, 2));
//    }
//    return bigrams;
//}


void build_ngram_histogram_vector(int n, const string& filename) {
    unordered_map<std::string, int> histogram;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file: " << endl;
        return;
    }

    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }

    for (int i = n - 1; i < words.size(); i++) {
        string ngram = "";
        for (int j = i - n + 1; j <= i; j++) {
            ngram += words[j] + " ";
        }
        ngram.pop_back();

        // If we increment an element of an unordered_map that does not exist in the map,
        // the map will insert a new element with the key and a default-constructed value,
        // then increment it
        histogram[ngram]++;
    }

    // to print the most common ngrams
    priority_queue<pair<int, string>> q;
    for (auto& [ngram, count] : histogram) {
        q.push({count, ngram});
    }

    for (int i = 0; i < 3; i++) {
        auto [count, ngram] = q.top();
        q.pop();
        cout << ngram << ": " << count << endl;
    }
}

int main()
{
    // clean_txt();
    Sequential s(3);

    auto begin = chrono::high_resolution_clock::now();
    s.compute_words_ngrams("../clean_input.txt");
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured for normal version: %.3f seconds.\n", elapsed.count() * 1e-9);

    auto begin2 = chrono::high_resolution_clock::now();
    build_ngram_histogram_vector(3, "../clean_input.txt");
    auto end2 = chrono::high_resolution_clock::now();
    auto elapsed2 = chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);
    printf("Time measured for vectorized version: %.3f seconds.\n", elapsed2.count() * 1e-9);



}