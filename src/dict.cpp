#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "dict.h"

#define end_char '\1'

using namespace std;

//default constructor 
Trie::Trie(){
    root = new vector<Node>(); 
}

// An insert function to add new word into the dictionary
void insert(vector<Node> *children, string word){
    if (word.empty()){
        return;
    }

    //checks if char is found in the given Trie
    //if exists, substring the character away
    for (int i = 0; i < children->size(); i++){
        Node child = (*children)[i];
        if (word[0] == child.letter){
            //word.erase(i,1);
            insert(child.children, word.substr(1));
            return;
        }
    }

    //if char does not exists in current children of Trie
    //add a new child with the char into the Trie
    Node child;
    child.letter = word[0];
    child.children = new vector<Node>();
    children->push_back(child);
    insert(child.children, word.substr(1));
}

//part of Trie function to call insert
void Trie::add(string word){
    insert(root, word + end_char);
}

//ensure word is not empty
bool wordValidate(string word){
    if(word.empty()){
        return false;
    }
    return true;
}
bool charValidate(char c){
    if(!isalpha(c)){
        return false;
    }
    return true;
}

//a find function to loop thorugh the Trie and check with each char
//if all char of string is checked till is empty, that means word exists
//within Trie
//If a char is not found within Trie branch, that means given word does not exist
bool toFind(vector<Node> *children, string word){
    if (word.empty()){
        return true;
    }

    for (int i = 0; i < children->size(); i++){
        Node child = (*children)[i];
        if (child.letter == word[0]){
            //word.erase(i,1);
            return toFind(child.children, word.substr(1));
        }
    }
    return false;

}

//part of Trie class to find if word exist
bool Trie::find(string word){
    if (!wordValidate(word)){
        return false;
    }
    return toFind(root, word + end_char);
}

//For a given prefix, loop through all of Trie to find prefix and use another
//loop to obtain all words of the given prefix
vector<string> togetwords(vector<Node> *children, char prefix){
    vector<string> words;
    if (prefix == '\0'){
        cout << "You did not specify a prefix" << endl;
        return words;
    }

    //Looks through all children to find if prefix exists in trie
    for (int i = 0; i < children->size(); i++){
        Node child = (*children)[i];

        // Skip the endings
        //Prevent words from other prefix to be displayed
        if (prefix ==  end_char) {
            if (child.letter == end_char) {
            continue;
            }
        } 
        else {
            if (child.letter != prefix) {
            continue;
            }
        }

        //If end_char is found, do not add char with the word
        for (int j = 0; j < child.children->size(); j++) {
            if ((*child.children)[j].letter == end_char) {
                string word = "";
                words.push_back(child.letter + word);
            }
        }
        
        //Combination of the char to form a word and append into vector of childwords
        vector<string> childWords = togetwords(child.children, end_char);
        for (int j = 0; j < childWords.size(); j++) {
            string childWord = childWords[j];
            words.push_back(child.letter + childWord);
        }
    }

    //prefix not found after iteration loop
    //cout << "No words containing the prefix you have given." << endl;
    /*if (words.empty()){
        cout << "No words containing the prefix you have given." << endl;
    }*/
    return words;

}

//Append words into vector of data type string
vector<string> Trie::getwords(char prefix){
    vector<string> words;
    if (!charValidate(prefix)){
        return words;
    }
    

    words = togetwords(root, prefix);
    for (int i = 0; i < words.size(); i++) {
        words[i] = words[i].substr(0, words[i].length());
    }
    return words;
}

//Part of Trie to call getwords and prove '\1' as prefix
vector<string> Trie::getwords(){
    return getwords(end_char);
}


//get index of character 
int getNumOfChar(char c){
    string letters = " -()abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < letters.length(); i++){
        if (letters[i] == c){
            return i;
        }
    }
}

//bubble sort algorithm to sort all the characters of a word in ascending order
void sort(string &word){
    for (int i = 0; i < word.length(); i++){
        if (word.length() - 1 == i){
            break;
        }
        if (getNumOfChar(word[i]) > getNumOfChar(word[i + 1])){
            swap(word[i], word[i + 1]);
        }
    }
}

//see what is the error in the given word by iterating through the Trie
Flag ErrorChecking(vector<Node> *children, string word){
    Flag flag;

    //no error, just empty string
    if (word.empty()){
        flag.subError = false;
        flag.transError = false;   
        return flag; 
    }
    
    //sort the given word in ascending order for full permutation
    sort(word);
    
    //full permutation of the given word
    do
    {    //permutation word exists within Trie means there is transposition error
        if (toFind(children, word) == true){
            flag.transError = true;
            flag.subError = false;
            return flag;
        }
    }while(next_permutation(word.begin(),word.end()));

    //if permutation does not equate to any word within the Trie,
    //substitution error has occurred.
    flag.subError = true;
    flag.transError = false;
    return flag;
}

//part of Trie to do error checking of a word
Flag Trie::errorChecker(string word){
    return ErrorChecking(root, word);
}
