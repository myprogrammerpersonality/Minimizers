from collections import deque
from typing import List
import random
import time

mapping = {"A": 0,
           "C": 1,
           "G": 2,
           "T": 3}

def order_kmer(seq: str):
    order = 0
    for i, letter in enumerate(seq[::-1]):
        if letter not in mapping:
            raise ValueError("Letter not in ACGT")
        order += 4**i * mapping[letter]
    return order

def find_minimizer_in_window(seq_window: str, k: int):
    min_order = order_kmer(seq_window[:k])
    min_pos = 0
    for i in range(len(seq_window) - k + 1):
        order = order_kmer(seq_window[i: i + k])
        if order < min_order:
            min_order = order
            min_pos = i
    return min_pos

def find_minimizers(seq: str, w: int, k: int) -> List[int]:
    minimizers = []
    for window in range(len(seq) - (w + k - 1) + 1):
        minimizers.append(find_minimizer_in_window(seq[window: window + (w + k - 1)], k) +  window)

    return minimizers

def minimizerSlidingWindow(seq: str, w: int, k: int) -> List[int]:

    deq = deque()
    result = []
    left = 0

    for right in range(len(seq) - k + 1):
        # pop larger elements
        while deq and order_kmer(seq[right: right + k]) < \
                      order_kmer(seq[deq[-1]: deq[-1] + k]):
            deq.pop()
        
        # add new element to queue
        deq.append(right)

        # pop expired values
        if left > deq[0]:
            deq.popleft()
        
        # start appending the result
        if right >= w - 1:
            result.append(deq[0])
            left += 1
    
    return result

if __name__ == "__main__":
    ns = [100, 1000, 5000, 10_000, 50_000, 100_000]  # Different values of n to test
    w = 40
    k = 15

    for n in ns:
        seq = "".join([random.choice("ATGC") for _ in range(n)])
        
        start_time = time.time()
        find_minimizers(seq, w, k)
        end_time = time.time()
        print(f"find_minimizers with n={n}: {end_time - start_time:.6f} seconds")
        
        start_time = time.time()
        minimizerSlidingWindow(seq, w, k)
        end_time = time.time()
        print(f"minimizerSlidingWindow with n={n}: {end_time - start_time:.6f} seconds")
        print()