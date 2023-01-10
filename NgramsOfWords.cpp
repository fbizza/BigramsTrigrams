#include "NgramsOfWords.h"

void print_histogram(unordered_map<string, int> histogram) {
    string ngram;
    int count;

    //sort the histogram
    priority_queue<pair<int, string>> q;
    for (auto&[ngram, count]: histogram) {
        q.push({count, ngram});
    }

    // prinit the most common ngrams
    for (int i = 0; i < 3; i++) {
        auto[count, ngram] = q.top();
        q.pop();
        cout << ngram << ": " << count << endl;
    }
}


void NgramsOfWords::compute_words_ngrams(const string &filename) {

    cout << "Computing ngrams..." << endl;
    int n = this->ngram_length;
    unordered_map<string, int> histogram;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening input txt file" << endl;
        return;
    }

    vector<string> previous_words(n - 1);
    int num_words = 0;
    string word;
    while (file >> word) {   // control for handling the first words of the txt file
        if (num_words >= n - 1) {
            string ngram = "";
            for (int i = 0; i < n - 1; i++) {
                ngram += previous_words[i] + " ";
            }
            ngram += word;
            histogram[ngram]++;
        }
        for (int i = 0; i < n - 2; i++) {           // used when n >=3
            previous_words[i] = previous_words[i + 1];
        }
        previous_words[n - 2] = word;   // access the last element of previous_words vector (of length n-1)
        num_words++;
    }

    print_histogram(histogram);
}


void NgramsOfWords::parallel_compute_words_ngrams(const string &filename) {

    cout << "Computing parallel ngrams..." << endl;
    int n = this->ngram_length;
    unordered_map<string, int> global_histogram;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file: " << endl;
        return;
    }

    vector<string> words;
    string word;

    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    int size = words.size();

#pragma omp parallel
    {

        unordered_map<string, int> thread_histogram;

#pragma omp for nowait
        for (int i = n - 1; i < size; i++) {
            string ngram = "";
            for (int j = i - n + 1; j < i + 1; j++) {
                ngram += words[j] + " ";
            }
            ngram.pop_back(); // to remove the extra blank space
            thread_histogram[ngram]++;
        }

#pragma omp critical
        for (auto&[ngram, count]: thread_histogram) {
            global_histogram[ngram] += count;
        }
    }

    print_histogram(global_histogram);
}

