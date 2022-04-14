#ifndef MerkleTree_h
#define MerkleTree_h

#include <vector>
#include <string>
#include <cstring>
#include <bitcoin/bitcoin.hpp>

class MerkleTree 
{

public:
    MerkleTree(std::vector<std::string> _nodes, std::function<std::string (std::string)> _hash) : nodes(_nodes), hash(_hash) { }
    
    std::string getRoot() 
    {
        return hashLevel(nodes);
    }
    
    std::string getMerkleHashFromLibBitcoin() 
    {
        bc::hash_list tx_hashes;
        for (const auto &hash : nodes) 
        {
            char hashLiteral[65];
            strncpy(hashLiteral, hash.c_str(), 65);
            tx_hashes.push_back(bc::hash_literal(hashLiteral));
        }
        
        const bc::hash_digest merkle_root = createMerkle(tx_hashes);
        return bc::encode_base16(merkle_root);
    }
private:
    std::vector<std::string> nodes;
    std::function<std::string (std::string)> hash;
    
    std::string hashLevel(std::vector<std::string> &levelNodes) 
    {
        std::vector<std::string> hashes;
        
        for (int i = 0; i < levelNodes.size(); i += 2) 
        {
            if (i + 1 < levelNodes.size()) 
            {
                hashes.push_back(hash(levelNodes.at(i) + levelNodes.at(i+1)));
            } 

            else 
            {
                hashes.push_back(levelNodes[i]);
            }
        }
        
        if (hashes.empty()) 
        {
            return "";
        }
        
        if (hashes.size() == 1) 
        {
            return hashes.at(0);
        }
        
        return hashLevel(hashes);
    }
    
    bc::hash_digest createMerkle(bc::hash_list& merkle) 
    {
        // Stop if hash list is empty or contains one element
        if (merkle.empty())
        {
            return bc::null_hash;
        }

        else if (merkle.size() == 1)
        {
            return merkle[0];
        }

        // While there is more than 1 hash in the list, keep looping...
        while (merkle.size() > 1)
        {
            // If number of hashes is odd, duplicate last hash in the list.
            if (merkle.size() % 2 != 0)
            {
                merkle.push_back(merkle.back());
            }
            // List size is now even.
            assert(merkle.size() % 2 == 0);

            // New hash list.
            bc::hash_list new_merkle;
            // Loop through hashes 2 at a time.
            for (auto it = merkle.begin(); it != merkle.end(); it += 2)
            {
                // Join both current hashes together (concatenate).
                bc::data_chunk concat_data(bc::hash_size * 2);
                auto concat = bc::serializer < decltype(concat_data.begin())>(concat_data.begin());
                concat.write_hash(*it);
                concat.write_hash(*(it + 1));
                // Hash both of the hashes.
                bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
                // Add this to the new list.
                new_merkle.push_back(new_root);
            }
            // This is the new list.
            merkle = new_merkle;
        }
        // Finally we end up with a single item.
        return merkle[0];
    }
};

#endif /* MerkleTree_h */
