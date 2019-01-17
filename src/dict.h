#ifndef DICT_H
#define DICT_H

#include <string>
#include <vector>

using namespace std;

struct Node{
    char            letter;
    vector<Node>    *children;    
};

struct Flag{
    bool            transError;
    bool            subError;
};

class Trie{
    private:
        vector<Node> *root;

    public:
        Trie();

        void add(string word);

        bool find(string word);

        vector<string> getwords();

        vector<string> getwords(char prefix);

        Flag errorChecker(string word);
};

#endif