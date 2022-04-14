#ifndef Transaction_hpp
#define Transaction_hpp

#include <stdio.h>
#include <string>
#include "Hash.h"

class Transaction 
{
public:
    Transaction(unsigned int _senderId, unsigned int _recipientId, double _amount, unsigned int _timestamp) : senderId(_senderId), recipientId(_recipientId), amount(_amount), timestamp(_timestamp) 
    {
        id = getHash();
    }
    
    std::string getId() const 
    {
        return id;
    }
    
    unsigned int getSenderId() const 
    {
        return senderId;
    }
    
    unsigned int getRecipientId() const 
    {
        return recipientId;
    }
    
    unsigned int getTimestamp() const 
    {
        return timestamp;
    }
    
    double getAmount() const 
    {
        return amount;
    }
    
    std::string getHash() 
    {
        return Hash::getHash(toString());
    }
private:
    std::string id;
    unsigned int senderId;
    unsigned int recipientId;
    unsigned int timestamp;
    double amount;
    
    std::string toString() 
    {
        return std::to_string(senderId) + "_" + std::to_string(recipientId) + "_" + std::to_string(timestamp) + "_" + std::to_string(amount);
    }
};

#endif /* Transaction_hpp */
