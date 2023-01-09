//
// Created by bizza on 05/01/2023.
//

#include "Sequential.h"


void Sequential::compute_words_ngrams(const string& filename) {
    int n = this->ngram_length;
    unordered_map<string, int> histogram;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening input txt file" << endl;
        return;
    }

    vector<string> previous_words(n - 1);
    int num_words = 0;  // for handling the first words of the txt file
    string word;
    while (file >> word) {
        if (num_words >= n - 1) {
            string ngram = "";
            for (int i = 0; i < n - 1; i++) {
                ngram += previous_words[i] + " ";
            }
            ngram += word;
            histogram[ngram]++;
        }
        for (int i = 0; i < n - 2; i++) {
            previous_words[i] = previous_words[i + 1];
        }
        previous_words[n - 2] = word;
        num_words++;
    }


//    // to print the whole histogram
//    for (const auto& [ngram, count] : histogram) {
//        cout << ngram << ": " << count << endl;
//    }


    // to print the most common ngrams
    priority_queue<pair<int, string>> q;
    for (auto& [ngram, count] : histogram) {
        q.push({count, ngram});
    }

    for (int i = 0; i < 3; i++) {
        auto [count, ngram] = q.top();
        q.pop();
        std::cout << ngram << ": " << count << std::endl;
    }
}




