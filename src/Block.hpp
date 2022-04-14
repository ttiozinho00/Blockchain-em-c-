#ifndef Block_hpp
#define Block_hpp

#define BLOCK_VERSION 1

#include <stdio.h>
#include <string>
#include <vector>
#include "Transaction.hpp"
#include "Hash.h"
#include "MerkleTree.h"
#include "sha256/sha256.hpp"

class Block 
{
public:
    Block(std::string _prevHash, unsigned int _timestamp, unsigned int _difficultyTarget, std::vector<Transaction> &transactions) : version(BLOCK_VERSION), prevHash(_prevHash), timestamp(_timestamp), difficultyTarget(_difficultyTarget) 
    {
        for (const auto &transaction : transactions) 
        {
            transactionHashes.push_back(transaction.getId());
        }
        
        MerkleTree merkleTree(transactionHashes, Hash::getHash);
        // merkleHash = merkleTree.getRoot(); // My implementation
        merkleHash = merkleTree.getMerkleHashFromLibBitcoin();
    }
    
    void addTransaction(Transaction &transaction) 
    {
        transactions.push_back(transaction);
    }
    
    std::string getHash() 
    {
        return Hash::getHash(std::to_string(nonce) + toString());
        // return sha256(toString());
    }
    
    bool isGoldenBlock() 
    {
        return getHash().substr(0, difficultyTarget) == std::string(difficultyTarget, '0');
    }
    
    void setNonce(unsigned int _nonce) 
    {
        nonce = _nonce;
    }
    
    unsigned int getNonce() const 
    {
        return nonce;
    }
    
    std::string getPrevHash() const 
    {
        return prevHash;
    }
    
    unsigned int getTimestamp() const 
    {
        return timestamp;
    }
    
    unsigned int getDifficultyTarget() const 
    {
        return difficultyTarget;
    }
private:
    unsigned int version;
    std::string prevHash;
    std::string merkleHash;
    unsigned int timestamp;
    unsigned int difficultyTarget;
    unsigned int nonce;
    std::vector<Transaction> transactions;
    std::vector<std::string> transactionHashes;
    
    std::string toString()
    {
        return std::to_string(version) + "_" + prevHash + "_" + merkleHash + "_" + std::to_string(timestamp) + "_" + std::to_string(difficultyTarget) + "_" + std::to_string(nonce);
    }
};

#endif /* Block_hpp */
