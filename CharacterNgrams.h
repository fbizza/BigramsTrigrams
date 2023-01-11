#ifndef BIGRAMSTRIGRAMS_CHARACTERNGRAMS_H
#define BIGRAMSTRIGRAMS_CHARACTERNGRAMS_H

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cctype>
#include <unordered_map>

using namespace std;

class CharacterNgrams {
public:
    CharacterNgrams(int n) {
        ngram_length = n;
    };

    void compute_character_ngrams(const string &filename);

    void parallel_compute_character_ngrams(const string &filename);

    vector<string> extract_ngrams_from_word(const string& str);

private:
    int ngram_length;
};


#endif //BIGRAMSTRIGRAMS_CHARACTERNGRAMS_H
