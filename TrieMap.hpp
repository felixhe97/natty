#ifndef TRIEMAP_H
#define TRIEMAP_H

#include <map>

// helper struct for TrieMap
struct TrieNode {
    std::map<int, TrieNode *> edges;
    std::string nodeVal;
};

// similar to std::map, but trie-based instead
class TrieMap {
    private:
        TrieNode *head;
        std::map<int, std::string> portMap;
    public:
        /**
         * Constructor
         */
        TrieMap(void);

        /**
         * Destructor
         */
        ~TrieMap(void);

        /**
         * Specific for NAT, takes in ip:port, and inserts that into Trie.
         * Implementation detail: the input port will be converted to negative,
         * thereby ensuring difference between ip and port (all ports are neg).
         *
         * '*' in ip will be INT_MAX on head, '*' in port edge will be INT_MIN
         */
        void insertNAT(const std::string& ipAndPort1,
                const std::string& ipAndPort2);

        /**
         * Specific for NAT, returns the converted ip:port, if input ip:port
         * was initialized in the TrieMap.
         */
        std::string retrieveNAT(const std::string&);
};

#endif
