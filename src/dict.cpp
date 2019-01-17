#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "dict.h"

#define end_char '\1'

using namespace std;

Trie::Trie(){
    root = new vector<Node>(); 
}

// An insert function to add new word into the dictionary
void insert(vector<Node> *children, string word){
    if (word.empty()){
        return;
    }

    for (int i = 0; i < children->size(); i++){
        Node child = (*children)[i];
        if (word[0] == child.letter){
            //word.erase(i,1);
            insert(child.children, word.substr(1));
            return;
        }
    }

    //if child.letter != word[index]
    Node child;
    child.letter = word[0];
    child.children = new vector<Node>();
    children->push_back(child);
    //word.erase(0,1);
    insert(child.children, word.substr(1));
}

void Trie::add(string word){
    insert(root, word + end_char);
}

bool wordValidate(string word){
    if(word.empty()){
        return false;
    }
    return true;
}

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

bool Trie::find(string word){
    if (wordValidate(word) == false){
        return false;
    }
    return toFind(root, word + end_char);
}

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

        for (int j = 0; j < child.children->size(); j++) {
            if ((*child.children)[j].letter == end_char) {
                string word = "";
                words.push_back(child.letter + word);
            }
        }
        
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

vector<string> Trie::getwords(char prefix){
    vector<string> words = togetwords(root, prefix);
    for (int i = 0; i < words.size(); i++) {
        words[i] = words[i].substr(0, words[i].length());
    }
    return words;
}

vector<string> Trie::getwords(){
    return getwords(end_char);
}


// testing
int getNumOfChar(char c){
    string letters = " -()abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < letters.length(); i++){
        if (letters[i] == c){
            return i;
        }
    }
}

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

Flag ErrorChecking(vector<Node> *children, string word){
    Flag flag;

    if (word.empty()){
        flag.subError = false;
        flag.transError = false;   
        return flag; 
    }
    
    sort(word);
    
    do
    {    
        if (toFind(children, word) == true){
            flag.transError = true;
            flag.subError = false;
            return flag;
        }
    }while(next_permutation(word.begin(),word.end()));
    flag.subError = true;
    flag.transError = false;
    return flag;
}

Flag Trie::errorChecker(string word){
    return ErrorChecking(root, word);
}

/*
Result findingError(vector<Node> *children, string word, bool subError){
    if (word.empty()) {
        Result result;
        result.found = true;
        result.subError = false;
        result.addError = false;
        return result;
    }

    for (int i = 0; i < children->size(); i++) {
        Node child = (*children)[i];

        if (word[0] == child.letter) {
            Result result = findingError(child.children, word.substr(1), subError);
            if (result.found) {
                return result;
            }
        } 
        else {
            if (!subError && word[0] != end_char) {
                Result result = findingError(child.children, word.substr(1), true);
                if (result.found) {
                    return result;
                }
            }
        }
    }

    Result result;
    result.found = false;
    result.subError = subError;
    result.addError = false;
    return result;
}

Result Trie::findError(string word){
    // Appends the special char to the string to mark its end within the trie.
    Result result = findingError(root, word + end_char, false);
    if (result.found) {
        return result;
    }

    for (int i = 0; i < word.length(); i++) {
        string wordCopy = string(word);
        wordCopy.erase(i, i + 1);

        Result result = findingError(root, wordCopy + end_char, false);
        if (result.found) {
            result.subError = false;
            result.addError = true;
            return result;
        }
    }

  return result;
}   */