#ifndef BIGRAMSTRIGRAMS_WORDNGRAMS_H
#define BIGRAMSTRIGRAMS_WORDNGRAMS_H

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cctype>
#include <unordered_map>

using namespace std;

class WordNgrams {
public:
    WordNgrams(int n) {
        ngram_length = n;
    };

    void compute_word_ngrams(const string &filename);

    void parallel_compute_word_ngrams(const string &filename);

private:
    int ngram_length;

};


#endif //BIGRAMSTRIGRAMS_WORDNGRAMS_H
