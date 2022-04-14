//
//  Hash.h
//  Blockchain1
//
//  Created by Emilis Baliukonis on 26/09/2019.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#ifndef Hash_h
#define Hash_h

#define BASE_KEY "0d23a6f45d4a927f87671b4f8a0e4bdc6051e8fb2316b834f0156ac31cabd829"

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits.h>

#define CHARACTER_TABLE "0123456789abcdef"
#define CHARACTER_TABLE_SIZE 16
#define __PROFILE__ false

class Hash {
public:
    static std::string getHash(std::string inputText) {
        std::string baseKey = BASE_KEY;
        std::string result = baseKey;
        
        const size_t inputLength = inputText.length();
        const unsigned int inputSum = getStringSum(inputText);

        size_t offset = 0;
        size_t size = std::min(baseKey.length(), inputLength);

        do {
            const std::string newBlock = inputText.substr(offset, std::min(size, inputLength - offset));
            result = hashBlock(result, newBlock, inputSum);
            offset += size;
        } while (offset < inputLength);

        return numericToText(result);
    }
    
private:
    std::string baseKey;
    
    static inline unsigned int getStringSum(std::string text) {
        unsigned int sum = 0;
        for (size_t i = 0; i < text.length(); i++) {
            sum += text[i];
        }
        
        return sum;
    }
    
    static inline std::string hashBlock(std::string base, std::string block, unsigned int inputSum) {
#if __PROFILE__
        std::cout << "Hashing " << base << " with " << block << std::endl;
#endif
        const unsigned int baseSum = getStringSum(base);
        const unsigned int blockSum = getStringSum(block);
        
        std::string result = base;
        unsigned int blockDigit = 0;
        unsigned int iteration = 0;
        for (int i = 0; i < base.length(); i++) {
            const unsigned int extraLonger = base[i] + base[base.length() - i] + base[base.length() / 3];
            const unsigned int extraShorter = block[blockDigit] + block[block.length() - blockDigit] + block[block.length() / 3];
            
            const int key = 1000.012 * std::sin((base[i] + i) * (block[blockDigit] + blockDigit + 107) + extraLonger + extraShorter + inputSum) + (double)(101 + extraLonger + extraShorter + baseSum + blockSum + inputSum + iteration) + i + iteration + inputSum;
            
            result[i] = std::abs(key) % CHAR_MAX;
            if (blockDigit + 1 < block.length()) {
                blockDigit++;
            } else {
                blockDigit = 0;
                iteration++;
            }
        }
        
        return result;
    }
    
    static inline std::string numericToText(std::string numericValue) {
        std::string result;
        for (size_t i = 0; i < numericValue.length(); i++) {
            // std::cout << numericValue[i] % CHARACTER_TABLE_SIZE << std::endl;
            result += CHARACTER_TABLE[numericValue[i] % CHARACTER_TABLE_SIZE];
        }
        
        return result;
    }
};

#endif /* Hash_h */
