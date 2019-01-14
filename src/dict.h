#ifndef DICT_H
#define DICT_H

#include <string>
#include <vector>

using namespace std;

struct Node{
    char            letter;
    vector<Node>    *children;    
};

struct Result{
    bool            found;
    bool            subError;
    bool            addError;
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

        Result findError(string word);
};

#endif