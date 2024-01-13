#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <deque>
#include <utility>
#include <set>

template <typename X, typename T>
class MonotonicQueue {
private:
        std::deque<std::pair<X, T>> dq;

    public:
        // Insert an element into the queue
        void Insert(X item, T time) {
            while (!dq.empty() && dq.back().first > item) {
                dq.pop_back();
            }
            dq.emplace_back(item, time);
        }

        // Fetch the current minimum and remove old elements
        std::pair<X, T> Fetch(T time) {
            while (!dq.empty() && dq.front().second < time) {
                dq.pop_front();
            }
            return dq.empty() ? std::pair<X, T>() : dq.front(); // return default pair if deque is empty
        }
};


std::string readFile(std::string path) {
    std::ifstream file(path);
    std::string dna_sequence;
    if (file.is_open()) {
        std::getline(file, dna_sequence);
        file.close();
    } else {
        std::cerr << "Error opening file" << std::endl;
        return "";
    }
    return dna_sequence;
};

int main(int argc, char* argv[]) {
    std::string dna_sequence = "GATACACTTCCCGAGTAGGTACTG";
    int kmer_size = 3;
    int window_size = 5;
    if (argc > 2) {
        dna_sequence = readFile(argv[1]);
        kmer_size = std::stoi(argv[2]);
        window_size = std::stoi(argv[3]);
    }
    std::hash<std::string> str_hash;
    MonotonicQueue<size_t, int> mq;
    std::set<std::string> minimizers;

    for (int i = 0; i <= static_cast<int>(dna_sequence.size()) - kmer_size; ++i) {
        std::string kmer = dna_sequence.substr(i, kmer_size);
        size_t hash_val = str_hash(kmer);
        mq.Insert(hash_val, i);

        if (i >= window_size - 1) {
            auto fetch_pair = mq.Fetch(i - window_size + 1);
            std::string temp_kmer = dna_sequence.substr(fetch_pair.second, kmer_size);
            minimizers.insert(temp_kmer);
        }
    }

    // Output the minimizers
    std::cout << "Minimizers: ";
    if (minimizers.size() > 10) {
        std::cout << "size: " << minimizers.size() << std::endl;
        int count = 0;
        for (const auto& min_kmer : minimizers) {
            if (count == 10) {
                break;
            }
            std::cout << min_kmer << " ";
            ++count;
        }
        std::cout << std::endl;
        return 0;
    }
    for (const auto& min_kmer : minimizers) {
        std::cout << min_kmer << " ";
    }
    std::cout << std::endl;

    return 0;
}
