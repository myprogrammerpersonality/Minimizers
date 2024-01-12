#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

const std::string input_file = "./input_100.txt";
const int kmer_size = 3;
const int window_size = 5;


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

    std::unordered_map<std::string, unsigned long> kmer_hashes;

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
        kmer_hashes[min_kmer] = min_hash;
    }

    // Output minimizers
    for (const auto &pair : kmer_hashes) {
        std::cout << "Minimizer: " << pair.first << " Hash: " << pair.second << std::endl;
    }

    return 0;
}
