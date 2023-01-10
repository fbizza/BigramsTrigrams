#ifndef BIGRAMSTRIGRAMS_NGRAMSOFWORDS_H
#define BIGRAMSTRIGRAMS_NGRAMSOFWORDS_H

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cctype>
#include <unordered_map>

using namespace std;

class NgramsOfWords {
public:
    NgramsOfWords(int n) {
        ngram_length = n;
    };

    void compute_words_ngrams(const string& filename);
    void parallel_compute_words_ngrams(const string& filename);

private:
    int ngram_length;

};


#endif //BIGRAMSTRIGRAMS_NGRAMSOFWORDS_H
