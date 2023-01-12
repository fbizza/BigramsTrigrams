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
        NgramLength = n;
    };

    void compute_character_ngrams(const string &filename);

    void parallel_compute_character_ngrams(const string &filename);

    vector<string> extract_ngrams_from_word(const string& str);

    int getNgramLength() const;

private:
    int NgramLength;

};


#endif //BIGRAMSTRIGRAMS_CHARACTERNGRAMS_H
