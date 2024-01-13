#include <iostream>
#include <fstream>
#include <string>

const std::string input_file = "./input_100.txt";
const int kmer_size = 1;
const int window_size = 2;


// Simple hash function for k-mers
unsigned long hash_kmer(const std::string &kmer) {
    unsigned long hash = 0;
    for (char c : kmer) {
        hash = hash * 31 + c;
    }
    return hash;
}

int main() {
    std::ifstream file(input_file);
    std::string dna_sequence;
    if (file.is_open()) {
        std::getline(file, dna_sequence);
        file.close();
    } else {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    // Find minimizers
    for (size_t i = 0; i <= dna_sequence.length() - window_size; ++i) {
        unsigned long min_hash = ULONG_MAX;
        std::string min_kmer;
        for (size_t j = i; j <= i + window_size - kmer_size; ++j) {
            std::string kmer = dna_sequence.substr(j, kmer_size);
            unsigned long hash = hash_kmer(kmer);
            if (hash < min_hash) {
                min_hash = hash;
                min_kmer = kmer;
            }
        }
        std::cout << "Minimizer: " << min_kmer << " Hash: " << min_hash << std::endl;
    }

    return 0;
}
