# Minimizer Implementation

This project implements a DNA sequence minimizer algorithm using a monotonic queue. It identifies the minimal k-mers within sliding windows of a given DNA sequence, which is useful in bioinformatics for sequence analysis and comparison. The algorithm is described in the following paper: [Zheng et al 2023](https://www.liebertpub.com/doi/pdf/10.1089/cmb.2023.0094).

## Installation

Ensure you have a C++ compiler installed. Clone the repository and navigate to its directory.

```bash
git clone https://github.com/myprogrammerpersonality/Minimizers
cd Minimizers
```

## Compilation

Compile the source code using the following command:

```bash
g++ -O3 -o minimizer minimizer.cpp
```

## Usage

Run the program with a DNA sequence file, specifying the k-mer size and window size:

```bash
./minimizer <filepath> <k> <w>
```

filepath: Path to the file containing the DNA sequence.
k: Size of the k-mer.
w: Size of the sliding window.

## Example

```bash
./minimizer input.txt 3 5
```

## Output

The program outputs the minimizers found in the sequence. If there are more than 10 minimizers, it shows the first 10.
