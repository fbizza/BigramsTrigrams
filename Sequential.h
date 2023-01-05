#ifndef BIGRAMSTRIGRAMS_SEQUENTIAL_H
#define BIGRAMSTRIGRAMS_SEQUENTIAL_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <unordered_map>

using namespace std;

class Sequential {

public:
    void build_bigram_histogram(const string& filename);

};


#endif //BIGRAMSTRIGRAMS_SEQUENTIAL_H
