#include "CharacterNgrams.h"


void print_character_histogram(unordered_map<string, int> histogram) {
    string ngram;
    int count;

    //sort the histogram
    priority_queue<pair<int, string>> q;
    for (auto& [ngram, count]: histogram) {
        q.push({count, ngram});
    }

    // prinit the most common ngrams
    for (int i = 0; i < 3; i++) {
        auto [count, ngram] = q.top();
        q.pop();
        cout << ngram << ": " << count << endl;
    }
}


void CharacterNgrams::compute_character_ngrams(const string& filename) {

    cout << "Computing character ngrams..." << endl;
    unordered_map<string, int> histogram;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening input txt file" << endl;
        return;
    }

    string word;
    vector<string> ngrams;
    while (file >> word) {
        ngrams = extract_ngrams_from_word(word);
        for (auto ngram : ngrams) {
            histogram[ngram]++;
        }
    }
    print_character_histogram(histogram);
}


vector<string> CharacterNgrams::extract_ngrams_from_word(const string& word) {
    int n = this->ngram_length;
    vector<string> ngrams;
    if (word.size() >= n) {
        for (int i = 0; i < word.size() - (n - 1); i++) {
            ngrams.push_back(word.substr(i, n));
        }
    }
    return ngrams;
}
