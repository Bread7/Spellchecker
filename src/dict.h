#ifndef DICT_H
#define DICT_H

#include <string>
#include <vector>

using namespace std;

//data collection of node for trie
struct Node{
    char            letter;
    vector<Node>    *children;    
};

//data collection of bool to check for errors
struct Flag{
    bool            transError;
    bool            subError;
};

//Class diagram for Trie 
class Trie{
    private:
        //start of a node
        vector<Node> *root;

    public:
        //constructor
        Trie();

        //adds word into Trie
        void add(string word);

        //finds a word in Trie
        bool find(string word);

        //get words in Trie if no user input
        vector<string> getwords();

        //get words in Trie if user gave a char
        vector<string> getwords(char prefix);

        //checks for error in word given
        Flag errorChecker(string word);
};

#endif