//
// Created by bizza on 05/01/2023.
//

#include "Sequential.h"


void Sequential::build_bigram_histogram(const string& filename) {
    unordered_map<std::string, int> histogram;

    ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    string prev_word;
    string word;
    while (file >> word) {
        if (!prev_word.empty()) {
            string bigram = prev_word + " " + word;

            // If we increment an element of an unordered_map that does not exist in the map,
            // the map will insert a new element with the key and a default-constructed value,
            // then increment it
            histogram[bigram]++;
        }
        prev_word = word;
    }

    for (const auto& [bigram, count] : histogram) {
        std::cout << bigram << ": " << count << std::endl;
    }

}
