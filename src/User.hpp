#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include <string>

class User 
{
public:
    User(unsigned int _id, std::string _name, std::string _publicKey, double _balance) : id(_id), name(_name), publicKey(_publicKey), balance(_balance) { }
    
    unsigned int getId() const 
    {
        return id;
    }
    
    double getBalance() const
    {
        return balance;
    }
private:
    unsigned int id;
    std::string name;
    std::string publicKey;
    double balance;
};

#endif /* User_hpp */
