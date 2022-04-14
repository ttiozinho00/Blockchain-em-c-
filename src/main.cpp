#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include "Block.hpp"
#include "Hash.h"
#include "MerkleTree.h"
#include "TransactionBuilder.hpp"
#include "UserBuilder.hpp"
#include "User.hpp"
#include "Transaction.hpp"
#include "Random.hpp"
#include "Block.hpp"
#include "Miner.hpp"

#define TRANSACTIONS_PER_BLOCK 100
#define DEFAULT_ATTEMPTS_PER_MINER 100

std::string testHash(std::string input) 
{
    return "Hash(" + input + ")";
}

std::vector<Transaction> getRandomVerifiedTransactions(std::vector<Transaction> &allTransactions, int numTransactions, const std::vector<User> &users) 
{
    std::random_shuffle(allTransactions.begin(), allTransactions.end());
    
    std::vector<Transaction> randomTransactions(allTransactions.begin(), allTransactions.begin() + std::min(numTransactions, (int)allTransactions.size()));
    
    for (int i = 0; i < randomTransactions.size(); i++) 
    {
        Transaction originalTransaction = randomTransactions.at(i);
        Transaction newTransaction = Transaction(originalTransaction.getSenderId(), originalTransaction.getRecipientId(), originalTransaction.getAmount(), originalTransaction.getTimestamp());
        
        User sender = users.at(originalTransaction.getSenderId());
        
        if (originalTransaction.getId() != newTransaction.getHash() || sender.getBalance() < originalTransaction.getAmount()) 
        {
            randomTransactions.erase(randomTransactions.begin() + i);
            std::cout << "Fake transaction detected!" << std::endl;
            
            if (i > 0)
            {
                i--;
            }
        }
    }
    return randomTransactions;
}

void removeMinedTransactions(std::vector<Transaction> &allTransactions, int transactionsPerBlock) 
{
    allTransactions.erase(allTransactions.begin(), allTransactions.begin() + std::min(transactionsPerBlock, (int)allTransactions.size()));
}

void verifyAndPushBlock(std::stack<Block> &blockchain, Block block, std::vector<Transaction> blockTransactions, std::vector<Transaction> &transactions, unsigned int transanctionsPerBlock) {
    Block verification = Block(block.getPrevHash(), block.getTimestamp(), block.getDifficultyTarget(), blockTransactions);
    verification.setNonce(block.getNonce());
    if (verification.getHash() == block.getHash()) 
    {
        blockchain.push(block);
        
        removeMinedTransactions(transactions, TRANSACTIONS_PER_BLOCK);
        std::cout << "Block " << blockchain.size() << ": " << block.getHash() << std::endl;
        std::cout << "Transactions left in pool: " << transactions.size() << std::endl;
    } 

    else 
    {
        std::cout << "Fake block detected!" << std::endl;
    }
}

int main(int argc, const char * argv[]) 
{
    UserBuilder userBuilder(1000);
    std::vector<User> users = userBuilder.getUsers();
    
    TransactionBuilder transactionBuilder(10000, users);
    std::vector<Transaction> transactions = transactionBuilder.getTransactions();
    
    std::vector<Transaction> genesisTransactions;
    Block genesisBlock("0", 0, 0, genesisTransactions);
    
    std::stack<Block> blockchain;
    blockchain.push(genesisBlock);
    
    unsigned int difficultyTarget = 4;
    unsigned int attemptsPerMiner = 0;
    
    std::vector<Miner> miners;
    for (int i = 0; i < 5; i++) 
    {
        miners.push_back(Miner(i + 1));
    }
    
    for (int i = 0; i < 10000; i += TRANSACTIONS_PER_BLOCK) 
    {
        attemptsPerMiner = DEFAULT_ATTEMPTS_PER_MINER;
        
        for (auto &miner : miners) 
        {
            std::vector<Transaction> blockTransactions = getRandomVerifiedTransactions(transactions, TRANSACTIONS_PER_BLOCK, users);
            miner.setTransactions(blockTransactions);
        }
        
        bool mining = true;
        while (mining) 
        {
            for (auto &miner : miners) 
            {
                try 
                {
                    Block block = miner.mineBlock(blockchain.top().getHash(), difficultyTarget, attemptsPerMiner);
                    verifyAndPushBlock(blockchain, block, miner.getTransactions(), transactions, TRANSACTIONS_PER_BLOCK);
                    std::cout << "Miner " << miner.getId() << " was first!" << std::endl;
                    mining = false;
                    break;
                } 

                catch (const char *message) 
                {
                    // std::cout << message << std::endl;
                }
            }
            
            attemptsPerMiner *= 2;
        }
    }
    return 0;
}
