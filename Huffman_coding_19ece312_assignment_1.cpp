#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Node structure for the Huffman Tree
struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

// Custom comparator for the priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

// Function to calculate character frequencies and probabilities
void calculateFrequencies(const string& filePath, unordered_map<char, int>& frequencies, string& text) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file." << endl;
        exit(EXIT_FAILURE);
    }

    char ch;
    while (file.get(ch)) {
        frequencies[ch]++;
        text += ch;
    }
    file.close();
}

// Function to build the Huffman Tree
Node* buildHuffmanTree(const unordered_map<char, int>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (const auto& pair : frequencies) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* merged = new Node('\0', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    return pq.top();
}

// Recursive function to generate Huffman Codes
void generateHuffmanCodes(Node* root, const string& code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (root->character != '\0') {
        huffmanCodes[root->character] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Function to encode a word into Huffman code
string encodeWord(const string& word, const unordered_map<char, string>& huffmanCodes) {
    string encoded = "";
    for (char ch : word) {
        if (huffmanCodes.find(ch) != huffmanCodes.end()) {
            encoded += huffmanCodes.at(ch);
        } else {
            throw invalid_argument("Word contains characters not in the text.");
        }
    }
    return encoded;
}

// Function to decode Huffman codes back into text
string decodeHuffmanCode(Node* root, const string& encodedText) {
    string decoded = "";
    Node* current = root;

    for (char bit : encodedText) {
        current = (bit == '0') ? current->left : current->right;

        if (current->character != '\0') {
            decoded += current->character;
            current = root;
        }
    }
    return decoded;
}

// Save outputs to a file
void saveOutput(const string& fileName, const string& data) {
    ofstream file(fileName);
    if (file.is_open()) {
        file << data;
        file.close();
    } else {
        cerr << "Error: Cannot write to file." << endl;
    }
}

// Main Huffman Coding function
void huffmanCoding(const string& inputFilePath, const string& outputFilePath) {
    unordered_map<char, int> frequencies;
    unordered_map<char, string> huffmanCodes;
    string text;

    calculateFrequencies(inputFilePath, frequencies, text);

    Node* huffmanTree = buildHuffmanTree(frequencies);
    generateHuffmanCodes(huffmanTree, "", huffmanCodes);

    string outputData;
    outputData += "Character Frequencies:\n";
    for (const auto& pair : frequencies) {
        outputData += "'" + string(1, pair.first) + "': " + to_string(pair.second) + "\n";
    }

    outputData += "\nCharacter Probabilities:\n";
    for (const auto& pair : frequencies) {
        double probability = (double)pair.second / text.length();
        outputData += "'" + string(1, pair.first) + "': " + to_string(probability) + "\n";
    }

    outputData += "\nHuffman Codes:\n";
    for (const auto& pair : huffmanCodes) {
        outputData += "'" + string(1, pair.first) + "': " + pair.second + "\n";
    }

    while (true) {
        cout << "\nOptions:\n1. Encode a word to Huffman code\n2. Decode Huffman code to text\n3. Exit and Save Outputs\nEnter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Enter the word to encode: ";
            string word;
            cin >> word;
            try {
                string encodedWord = encodeWord(word, huffmanCodes);
                cout << "Huffman code for '" << word << "': " << encodedWord << endl;
                outputData += "\nEncoded '" + word + "' to Huffman code: " + encodedWord + "\n";
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
        } else if (choice == 2) {
            cout << "Enter the Huffman code to decode: ";
            string encodedText;
            cin >> encodedText;
            string decodedText = decodeHuffmanCode(huffmanTree, encodedText);
            cout << "Decoded text: " << decodedText << endl;
            outputData += "\nDecoded Huffman code '" + encodedText + "' to text: " + decodedText + "\n";
        } else if (choice == 3) {
            saveOutput(outputFilePath, outputData);
            cout << "Outputs saved to " << outputFilePath << ". Exiting." << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    string inputFile = "C:/Users/91939/Downloads/James C. Maxwell Biography.txt"; // Replace with your text file path
    string outputFile = "C:/Users/91939/Desktop/Out_text.txt";       // File to save outputs
    huffmanCoding(inputFile, outputFile);
    return 0;
}
