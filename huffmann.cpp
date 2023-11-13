#include <iostream>
#include <queue>
#include <map>
#include <string>

using namespace std;

struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = right = nullptr;
    }
};

struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

HuffmanNode* buildHuffmanTree(map<char, int>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;

    for (auto& entry : frequencies) {
        HuffmanNode* node = new HuffmanNode(entry.first, entry.second);
        pq.push(node);
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

void generateHuffmanCodes(HuffmanNode* root, string code, map<char, string>& huffmanCodes) {
    if (!root)
        return;

    if (root->data != '$') {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

string compress(string text) {
    map<char, int> frequencies;

    for (char c : text) {
        frequencies[c]++;
    }

    HuffmanNode* root = buildHuffmanTree(frequencies);

    map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    string compressed = "";
    for (char c : text) {
        compressed += huffmanCodes[c];
    }

    return compressed;
}

string decompress(string compressed, HuffmanNode* root) {
    string decompressed = "";
    HuffmanNode* current = root;

    for (char bit : compressed) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current->data != '$') {
            decompressed += current->data;
            current = root;
        }
    }

    return decompressed;
}

int main() {
    string text = "Abhay Raj Yadav";

    string compressed_text = compress(text);
    cout << "Compressed Text: " << compressed_text << endl;

    map<char, int> frequencies;
    for (char c : text) {
        frequencies[c]++;
    }
    HuffmanNode* root = buildHuffmanTree(frequencies);

    string decompressed = decompress(compressed_text, root);
    cout << "Decompressed Text: " << decompressed << endl;

    delete root;

    return 0;
}
