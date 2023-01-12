#include "WordNgrams.h"
#define NUM_THREADS 16

void print_histogram(unordered_map<string, int> histogram) {
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


void WordNgrams::compute_word_ngrams(const string& filename) {

    cout << "Computing word ngrams..." << endl;
    int n = this->NgramLength;
    unordered_map<string, int> histogram;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening input txt file" << endl;
        return;
    }

    vector<string> previous_words(n - 1);
    int num_words = 0;
    string word;
    while (file >> word) {
        if (num_words >= n - 1) {   // control for handling the first words of the txt file
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


void WordNgrams::parallel_compute_word_ngrams(const string& filename) {

    cout << "Computing parallel word ngrams..." << endl;
    int n = this->getNgramLength();
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
        for (auto [ngram, count]: thread_histogram) {
            global_histogram[ngram] += count;
        }

    }   // end of parallel region
    print_histogram(global_histogram);
}

int WordNgrams::getNgramLength() const {
    return NgramLength;
}

