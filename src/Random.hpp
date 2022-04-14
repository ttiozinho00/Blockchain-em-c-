#ifndef Random_h
#define Random_h

#include <string>
#include <random>

class Random 
{
public: 
    static std::string randomString(size_t length = 16) 
    {
        auto randchar = []() -> char 
        {
            const char charset[] = "0123456789","ABCDEFGHIJKLMNOPQRSTUVWXYZ","abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };

        std::string str(length,0);
        std::generate_n( str.begin(), length, randchar );
        return str;
    }
    
    static double randomDouble(double min, double max) 
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(min, max);
        
        return dist(mt);
    }
    
    static int randomInt(int min, int max) 
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(min, max);
        
        return dist(mt);
    }
    
    static unsigned int randomUnsignedInt(unsigned int min, unsigned int max) 
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned int> dist(min, max);
        
        return dist(mt);
    }
};


#endif /* Random_h */
