#ifndef TransactionBuilder_h
#define TransactionBuilder_h

#include <vector>
#include <string>
#include <climits>
#include "Transaction.hpp"
#include "User.hpp"
#include "Random.hpp"

class TransactionBuilder 
{
public:
    TransactionBuilder(unsigned int n, std::vector<User> users) 
    {
        for (unsigned int i = 0; i < n; i++) 
        {
            Transaction trans = newRandomTransaction(users);
            transactions.push_back(trans);
        }
    }
    
    std::vector<Transaction> getTransactions() 
    {
        return transactions;
    }
private:
    std::vector<Transaction> transactions;
    
    Transaction newRandomTransaction(std::vector<User> &users) 
    {
        unsigned int recipientId = getRandomRecipient(users);
        unsigned int senderId = getRandomSender(users, recipientId);
        unsigned int timestamp = Random::randomUnsignedInt(0, INT_MAX);
        double amount = Random::randomDouble(0.1, 100);
        return Transaction(recipientId, senderId, amount, timestamp);
    }
    
    unsigned int getRandomRecipient(std::vector<User> &users) 
    {
        unsigned int index = Random::randomUnsignedInt(0, users.size() - 1);
        return users.at(index).getId();
    }
    
    unsigned int getRandomSender(std::vector<User> &users, unsigned int recipientId) 
    {
        unsigned int index = NULL;
        
        while (index == NULL) 
        {
            unsigned int number = Random::randomUnsignedInt(0, users.size() - 1);
            if (number != recipientId) 
            {
                index = number;
            }
        }
        
        return users.at(index).getId();
    }
};


#endif /* TransactionBuilder_h */
