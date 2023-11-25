/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RType
*/

#include <iostream>
#include <fstream>
#include <memory>
#include <array>
#include <queue>
#include <asio.hpp>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <asio.hpp>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class RType {
    public:
        virtual ~RType() = default;
    protected:
    private:
};


struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {};
};

void serializeHuffmanTree(HuffmanNode* root, std::vector<uint8_t>& serializedData) {
        if (root) {
            if (root->data == '$') {
                serializedData.push_back(0);
                serializeHuffmanTree(root->left, serializedData);
                serializeHuffmanTree(root->right, serializedData);
            } else {
                serializedData.push_back(1);
                serializedData.push_back(static_cast<uint8_t>(root->data));
            }
        }
    }

    std::vector<uint8_t> serializeHuffmanTree(HuffmanNode* root) {
        std::vector<uint8_t> serializedData;
        serializeHuffmanTree(root, serializedData);
        return serializedData;
}

HuffmanNode* deserializeHuffmanTree(const std::vector<uint8_t>& serializedData, size_t& index) {
    if (index < serializedData.size()) {
        uint8_t marker = serializedData[index++];
        if (marker == 0) {
            HuffmanNode* internalNode = new HuffmanNode('$', 0);
            internalNode->left = deserializeHuffmanTree(serializedData, index);
            internalNode->right = deserializeHuffmanTree(serializedData, index);
            return internalNode;
        } else if (marker == 1) {
            char data = static_cast<char>(serializedData[index++]);
            return new HuffmanNode(data, 0);
        }
    }

    return nullptr;
}

struct CompareHuffmanNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

class HuffmanEncoder {
    public:
        HuffmanEncoder(const std::string& text) : text(text), root(nullptr) {
            buildTree();
            buildCodes(root, "");
        };
        std::string encode() {
            std::string encodedText;
            for (char c : text) {
                encodedText += huffmanCodes[c];
            }
            return encodedText;
        };
        std::vector<uint8_t> serializeTree() {
            return serializeHuffmanTree(root);
        };
        ~HuffmanEncoder() {};
        HuffmanNode* root;

    private:
        void buildTree() {
            for (char c : text) {
                frequencyTable[c]++;
            }

            std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareHuffmanNode> pq;

            for (const auto& pair : frequencyTable) {
                pq.push(new HuffmanNode(pair.first, pair.second));
            }

            while (pq.size() > 1) {
                HuffmanNode* left = pq.top();
                pq.pop();
                HuffmanNode* right = pq.top();
                pq.pop();

                HuffmanNode* merged = new HuffmanNode('$', left->frequency + right->frequency);
                merged->left = left;
                merged->right = right;
                pq.push(merged);
            }

            root = pq.top();
        };
        void buildCodes(HuffmanNode* node, const std::string& code) {
            if (node) {
                if (node->data != '$') {
                    huffmanCodes[node->data] = code;
                }
                buildCodes(node->left, code + "0");
                buildCodes(node->right, code + "1");
            }
        };
        std::string text;
        std::unordered_map<char, int> frequencyTable;
        std::unordered_map<char, std::string> huffmanCodes;
};


class HuffmanDecoder {
    public:
        HuffmanDecoder() : root(nullptr) {};
        void deserializeTree(const std::vector<uint8_t>& serializedTree) {
            size_t index = 0;
            root = deserializeHuffmanTree(serializedTree, index);
        };

        std::string decode(const std::string& code) {
            std::string decodedText;
            HuffmanNode* current = root;

            for (char bit : code) {
                if (bit == '0') {
                    current = current->left;
                } else if (bit == '1') {
                    current = current->right;
                }

                if (current->data != '$') {
                    decodedText += current->data;
                    current = root;
                }
            }

            return decodedText;
        };
        ~HuffmanDecoder() {};

    private:
        HuffmanNode* root;
};