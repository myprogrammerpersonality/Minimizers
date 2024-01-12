#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

const int kmerSize = 3;
const int windowSize = 5;
const std::string filename = "./input.txt";

// Function to read the DNA sequence from a file
std::string readDNASequence(const std::string &filename) {
    std::ifstream file(filename);
    std::string sequence;
    if (file.is_open()) {
        file >> sequence;
    } else {
        std::cerr << "Unable to open file\n";
    }
    return sequence;
}

// Function to generate all k-mers from the DNA sequence
std::vector<std::string> generateKmers(const std::string &sequence, int k) {
    std::vector<std::string> kmers;
    for (size_t i = 0; i <= sequence.size() - k; ++i) {
        kmers.push_back(sequence.substr(i, k));
    }
    return kmers;
}

// Function to find minimizers from a vector of k-mers
std::vector<std::string> findMinimizers(const std::vector<std::string> &kmers, int windowSize) {
    std::vector<std::string> minimizers;
    for (size_t i = 0; i <= kmers.size() - windowSize; ++i) {
        auto windowBegin = kmers.begin() + i;
        auto windowEnd = windowBegin + windowSize;
        auto minKmer = std::min_element(windowBegin, windowEnd);
        minimizers.push_back(*minKmer);
    }
    return minimizers;
}

int main() {
    // Step 1: Reading the DNA sequence
    std::string dnaSequence = readDNASequence(filename);

    // Step 2 & 3: Generating k-mers and applying random ordering
    std::vector<std::string> kmers = generateKmers(dnaSequence, kmerSize);
    std::random_shuffle(kmers.begin(), kmers.end());

    // Step 4: Finding minimizers
    std::vector<std::string> minimizers = findMinimizers(kmers, windowSize);

    // Step 5: Outputting the first ten minimizers
    for (int i = 0; i < 10 && i < minimizers.size(); ++i) {
        std::cout << minimizers[i] << std::endl;
    }

    return 0;
}
