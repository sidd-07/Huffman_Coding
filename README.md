#Huffman Coding Compression and Decompression

#Overview

This project implements Huffman Coding, a lossless data compression algorithm, in C++. It reads text from a file, calculates character frequencies and probabilities, builds a Huffman Tree, and generates Huffman codes. Additionally, it allows users to encode words into Huffman codes and decode Huffman-encoded text interactively.

#Features

Reads a text file and calculates character frequencies.

Builds a Huffman Tree and generates Huffman codes.

Encodes a user-input word into Huffman code.

Decodes a given Huffman code back into text.

Saves character frequencies, probabilities, Huffman codes, and user interactions into an output file.

Prerequisites

#C++ Compiler (G++ recommended)

Basic understanding of data structures like trees and priority queues

#File Structure

huffman.cpp - Main implementation file containing Huffman Coding logic.

James C. Maxwell Biography.txt - Sample input file (replace with any text file of your choice).

Out_text.txt - Output file to save results.

How to Run

Compile the code:

g++ -o huffman huffman.cpp

Run the executable:

./huffman

Provide the text file path inside huffman.cpp (update inputFile variable accordingly).

Choose options:

Encode a word to Huffman code.

Decode a Huffman code back to text.

Save results and exit.

Example Usage

Options:
1. Encode a word to Huffman code
2. Decode Huffman code to text
3. Exit and Save Outputs
Enter your choice: 1
Enter the word to encode: hello
Huffman code for 'hello': 1010110110

Output File (Out_text.txt)

This file stores:

Character frequencies and probabilities

Generated Huffman codes

Encoded and decoded text from user interactions

License

This project is open-source. You are free to modify and distribute it.

Author

Developed by [Your Name]
