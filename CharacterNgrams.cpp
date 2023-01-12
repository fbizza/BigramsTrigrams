#include "CharacterNgrams.h"
#define NUM_THREADS 16


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
    int n = this->getNgramLength();
    vector<string> ngrams;
    if (word.size() >= n) {
        for (int i = 0; i < word.size() - (n - 1); i++) {
            ngrams.push_back(word.substr(i, n));
        }
    }
    return ngrams;
}

void CharacterNgrams::parallel_compute_character_ngrams(const string& filename) {

    cout << "Computing parallel character ngrams..." << endl;
    unordered_map<string, int> global_histogram;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening input txt file" << endl;
        return;
    }

    vector<string> words;
    string word;

    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    int size = words.size();

#pragma omp parallel num_threads(NUM_THREADS)
    {

        unordered_map<string, int> thread_histogram;
        vector<string> current_ngrams;

#pragma omp for nowait
        for (auto word: words) {
            current_ngrams = extract_ngrams_from_word(word);
            for (auto ngram : current_ngrams) {
                thread_histogram[ngram]++;
            }
        }

#pragma omp critical
        for (auto [ngram, count]: thread_histogram) {
            global_histogram[ngram] += count;
        }

    }   // end of parallel region
    print_character_histogram(global_histogram);
}

int CharacterNgrams::getNgramLength() const {
    return NgramLength;
}

