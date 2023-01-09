#ifndef BIGRAMSTRIGRAMS_SEQUENTIAL_H
#define BIGRAMSTRIGRAMS_SEQUENTIAL_H

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cctype>
#include <unordered_map>

using namespace std;

class Sequential {
public:
    Sequential(int n) {
        ngram_length = n;
    };

    void compute_words_ngrams(const string& filename);

private:
    int ngram_length;

};


#endif //BIGRAMSTRIGRAMS_SEQUENTIAL_H
