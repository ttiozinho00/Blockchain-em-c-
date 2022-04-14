#ifndef Miner_hpp
#define Miner_hpp

#include <string>
#include <iostream>
#include <vector>
#include <climits>
#include "Random.hpp"
#include "Block.hpp"
#include "Hash.h"
#include "Transaction.hpp"

class Miner 
{

public:
    Miner(unsigned int _id) : id(_id) {}
    Block mineBlock(std::string prevHash, unsigned int difficultyTarget, unsigned int attempts) 
    {
        Block block(prevHash, time(0), difficultyTarget, transactions);
        for (unsigned int i = 0; i < attempts; i++) 
        {
            unsigned int nonce = Random::randomUnsignedInt(0, UINT_MAX);
            block.setNonce(nonce);
            // std::cout << block.getHash() << '\n';
            if (block.isGoldenBlock()) 
            {
                std::cout << "Block mined in attempt " << i << std::endl;
                return block;
            }
        }
        
        throw "Could not mine block";
    }
    
    unsigned int getId() const 
    {
        return id;
    }
    
    void setTransactions(std::vector<Transaction> &_transactions) 
    {
        transactions = _transactions;
    }
    
    std::vector<Transaction> getTransactions() 
    {
        return transactions;
    }
private:
    unsigned int id;
    std::vector<Transaction> transactions;
};

#endif /* Miner_hpp */
