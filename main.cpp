#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <unordered_map>
#include <chrono>

using namespace std;


int clean_txt() {
    // This function removes punctuation and transforms every character to lowercase
    string filename = "../input.txt";
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Error opening input file: " << filename << endl;
        return 1;
    }
    string word;
    ofstream output("../clean_input.txt");
    if (!output.is_open()) {
        cerr << "Error opening output file" << endl;
        return 1;
    }
    while (input >> word) {
        string clean_word;
        for (char c : word) {
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
}

vector<string> extract_bigrams(const string& str) {
    vector<string> bigrams;
    for (int i = 0; i < str.size() - 1; i++) {
        bigrams.push_back(str.substr(i, 2));
    }
    return bigrams;
}


void build_bigram_histogram(const string& filename) {

    unordered_map<std::string, int> histogram;

    ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    string prev_word;
    string word;
    while (file >> word) {
        if (!prev_word.empty()) {
            string bigram = prev_word + " " + word;

            // If we increment an element of an unordered_map that does not exist in the map,
            // the map will insert a new element with the key and a default-constructed value,
            // then increment it
            histogram[bigram]++;
        }
        prev_word = word;
    }

    for (const auto& [bigram, count] : histogram) {
        std::cout << bigram << ": " << count << std::endl;
    }
}

void build_bigram_histogram_from_vector(const string& filename) {
    unordered_map<std::string, int> histogram;

    ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }

    for (int i = 1; i < words.size(); i++) {
        string bigram = words[i - 1] + " " + words[i];

        // If we increment an element of an unordered_map that does not exist in the map,
        // the map will insert a new element with the key and a default-constructed value,
        // then increment it
        histogram[bigram]++;
    }

    for (const auto& [bigram, count] : histogram) {
        std::cout << bigram << ": " << count << std::endl;
    }
}
int main()
{
    clean_txt();
    auto begin = chrono::high_resolution_clock::now();
    build_bigram_histogram("../clean_input.txt");
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured for normal version: %.3f seconds.\n", elapsed.count() * 1e-9);

    auto begin2 = chrono::high_resolution_clock::now();
    build_bigram_histogram_from_vector("../clean_input.txt");
    auto end2 = chrono::high_resolution_clock::now();
    auto elapsed2 = chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2);
    printf("Time measured for vectorized version: %.3f seconds.\n", elapsed2.count() * 1e-9);
}