#ifndef UserBuilder_h
#define UserBuilder_h

#include "User.hpp"
#include "Random.hpp"

class UserBuilder 
{
public:
    UserBuilder(unsigned int n) 
    {
        for (unsigned int i = 0; i < n; i++) 
        {
            users.push_back(newRandomUser(i));
        }
    }
    
    std::vector<User> getUsers() 
    {
        return users;
    }
private:
    std::vector<User> users;
    
    User newRandomUser(unsigned int id) 
    {
        std::string name = Random::randomString(10);
        std::string publicKey = Random::randomString(64);
        double balance = Random::randomDouble(100, 1000000);
        return User(id, name, publicKey, balance);
    }
};

#endif /* UserBuilder_h */
