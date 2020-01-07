#include <map>
#include <vector>
#include <climits>
#include <sstream>
#include <string>

#include "TrieMap.hpp"

#define STAR_PORT INT_MIN

TrieMap::TrieMap()
{
    this->head = new TrieNode;
    this->head->nodeVal = "";
}


void recursiveDelete(TrieNode *t)
{
    for (auto &p : t->edges) {
        recursiveDelete(p.second);
    }
    delete t;
}


TrieMap::~TrieMap()
{
    recursiveDelete(this->head);
}


void TrieMap::insertNAT(const std::string& ipAndPort1,
        const std::string& ipAndPort2)
{
    // ipAndPort1 is key, and can contain a '*' in one of ip or port component
    std::string ip, port;
    std::stringstream ssColon(ipAndPort1);
    std::getline(ssColon, ip, ':');
    std::getline(ssColon, port);

    if (ip == "*") {
        // need a one-level portMap on head
        this->portMap[-(stoi(port))] = ipAndPort2;
    } else {
        std::vector<int> putIntoTrie;
        std::string temp;
        std::stringstream ssPeriod(ip);
        while (std::getline(ssPeriod, temp, '.')) {
            putIntoTrie.push_back(stoi(temp));
        }
        if (port == "*") {
            putIntoTrie.push_back(STAR_PORT);
        } else {
            putIntoTrie.push_back(-(stoi(port)));
        }

        // now insert into trie
        TrieNode *tempNode = this->head;
        for (const int &item : putIntoTrie) {
            if (tempNode->edges.count(item)) {
                tempNode = tempNode->edges[item];
            } else {
                tempNode->edges[item] = new TrieNode;
                tempNode = tempNode->edges[item];
            }
        }
        tempNode->nodeVal = ipAndPort2;
    }
}


std::string TrieMap::retrieveNAT(const std::string &ipAndPort)
{
    // guaranteed no "*" in ipAndPort during retrieval
    std::string ip, port;
    std::stringstream ssColon(ipAndPort);
    std::getline(ssColon, ip, ':');
    std::getline(ssColon, port);

    std::vector<int> searchTrie;
    std::string temp;
    std::stringstream ssPeriod(ip);
    while (std::getline(ssPeriod, temp, '.')) {
        searchTrie.push_back(stoi(temp));
    }

    // the last int in our searchTrie is guaranteed to be the port
    searchTrie.push_back(-(stoi(port)));

    // traverse TrieMap
    TrieNode *tempNode = this->head;
    for (int i = 0; i < searchTrie.size(); ++i) {
        if (tempNode->edges.count(searchTrie[i])) {
            tempNode = tempNode->edges[searchTrie[i]];
        } else if (i == searchTrie.size() - 1 && tempNode->edges.count(STAR_PORT)) {
            tempNode = tempNode->edges[STAR_PORT];
        } else {
            tempNode = nullptr;
            break;
        }
    }

    // check if *:port exists, if so return it
    if (tempNode && !tempNode->nodeVal.empty()) {
        return tempNode->nodeVal;
    } else if (this->portMap.count(searchTrie.back())) {
        return this->portMap[searchTrie.back()];
    } else {
        return "";
    }
}
