#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <chrono>
#include <functional>
#include "WordNgrams.h"
#include "CharacterNgrams.h"


using namespace std;


int clean_txt() {
    // This function removes punctuation and transforms every character to lowercase
    string filename = "../input.txt";
    ifstream input(filename);
    if (!input.is_open()) {
        cout << "Error opening input file" << endl;
        return 1;
    }
    string word;
    ofstream output("../clean_input.txt");
    if (!output.is_open()) {
        cout << "Error opening output file" << endl;
        return 1;
    }
    while (input >> word) {
        string clean_word;
        for (char c: word) {
            if (!ispunct(c)) {
                clean_word += tolower(c);
            }
        }
        if (!clean_word.empty()) {
            output << clean_word << " ";
        }
    }
    input.close();
    output.close();
    return 0;
}

void get_average_elapsed_time(CharacterNgrams& c, WordNgrams& w, int n, const string& s) {
    int c_length = c.getNgramLength();
    int w_length = w.getNgramLength();
    auto begin = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++){
        c.compute_character_ngrams(s);
    }
    auto end = chrono::high_resolution_clock::now();
    auto elapsed_character_ngrams = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    begin = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++){
        c.parallel_compute_character_ngrams(s);
    }
    end = chrono::high_resolution_clock::now();
    auto elapsed_parallel_character_ngrams = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    begin = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++){
        w.compute_word_ngrams(s);
    }
    end = chrono::high_resolution_clock::now();
    auto elapsed_word_ngrams = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    begin = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++){
        w.parallel_compute_word_ngrams(s);
    }
    end = chrono::high_resolution_clock::now();
    auto elapsed_parallel_word_ngrams = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("\n------------------------------------------------------------\n");
    printf("Average time for sequential character %d-grams:     %.3f s |\n", c_length, (elapsed_character_ngrams.count() * 1e-9)/n);
    printf("Average time for sequential word %d-grams:          %.3f s |\n", w_length, (elapsed_word_ngrams.count() * 1e-9)/n);
    printf("Average time for parallel character %d-grams:       %.3f s |\n", c_length, (elapsed_parallel_character_ngrams.count() * 1e-9)/n);
    printf("Average time for parallel word %d-grams:            %.3f s |\n", w_length, (elapsed_parallel_word_ngrams.count() * 1e-9)/n);
    printf("------------------------------------------------------------\n");
    printf("CHARACTER NGRAM SPEED-UP:                          %.3f   |\n", ((elapsed_character_ngrams.count() * 1e-9)/n)/((elapsed_parallel_character_ngrams.count() * 1e-9)/n));
    printf("WORD NGRAM SPEED-UP:                               %.3f   |\n", ((elapsed_word_ngrams.count() * 1e-9)/n)/((elapsed_parallel_word_ngrams.count() * 1e-9)/n));
    printf("------------------------------------------------------------");
}

int main() {
    clean_txt();
    CharacterNgrams c(2);
    WordNgrams w(2);
    //get_average_elapsed_time(c, w, 7, "../clean_input.txt");

}