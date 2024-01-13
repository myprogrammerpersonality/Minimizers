# generate a random DNA sequence of length 100000 and write it to the file
# Alphabet: A, C, G, T

import random

DNA_SIZE = 1_000_000
OUTPUT_FILE = f'input_{DNA_SIZE}.txt'


# generate a random DNA sequence of length
def generate_sequence(length):
    return ''.join(random.choice('ACGT') for _ in range(length))


# write the sequence to the file input.txt
def write_sequence(sequence):
    with open(OUTPUT_FILE, 'w') as f:
        f.write(sequence)


if __name__ == '__main__':
    sequence = generate_sequence(DNA_SIZE)
    write_sequence(sequence)
