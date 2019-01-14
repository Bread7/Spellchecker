#include <fstream>
#include <iostream>
#include <string>

#include "dict.h"

using namespace std;

//global declaration(s)
Trie *dict = new Trie();

void addWord(Trie *dict){
    string word;

    cout << "Enter a word: ";
    cin >> word;
    cin.clear();

    dict->add(word);

    cout << endl;

    cout << "Word added" << endl;
}
void spellCheckWord(Trie *dict){
    string word;

    cout << "Enter word to check: ";
    cin >> word;
    cin.clear();
    cout << endl;

    if (dict->find(word) == true){
        cout << "Word is spelt correctly." << endl;
    }
    else {
        cout << "Word is spelt incorrectly or it does not exist." << endl;
    }
}

bool spellCheckFile(Trie *dict){
    string path;
    ifstream dictionary;
    cout << "Example: /home/bread/ZJ/School/DSA/Practical/word/data/RandomWords100.txt" << endl;
    cout << "Enter a path: ";
    cin >> path;
    cin.clear();
    cout << endl;
    dictionary.open(path);

    if (!dictionary.is_open()){
        return false;
    }

    while (!dictionary.eof()){
        string word;
        getline(dictionary, word);
        if (dict->find(word) == false){
            cout << word << " is spelt incorrectly." << endl;
        }
    }

    dictionary.close();
    return true;
}

bool saveDict(Trie *dict){
    ofstream dictionary;
    dictionary.open("/home/bread/ZJ/School/DSA/Practical/word/data/UserDictionary.txt");

    if (!dictionary.is_open()){
        return false;
    }

    vector<string> words = dict->getwords();

    for (int i = 0; i < words.size(); i++) {
        dictionary << words[i];
        if (i != words.size() - 1) {
            dictionary << endl;
        }
    }

    dictionary.close();
    return true;
}

void prefixSearch(Trie *dict){
    char c;

    cout << "Enter a letter to display all words starting with the given letter: ";
    cin >> c;
    cin.clear();

    vector<string> words = dict->getwords(c);

    for (int i = 0; i < words.size(); i++){
        cout << words[i] << endl;
    }
}

void errorCheck(Trie *dict){
    string word;

    cout << "Enter a word: ";
    cin >> word;
    cin.clear();

    if (dict->find(word) == true){
        cout << "Word is spelt correctly." << endl;
        return;
    }
    Result flags = dict->findError(word);
    if (flags.addError){
        cout << "You had substitution error." << endl;
        return;
    } 
    else if (flags.addError){
        cout << "You had addition error." << endl;
        return;
    }
    else {
        cout << "Word is spelt incorrectly." << endl;
        return;
    }
}

bool loadDict(Trie *dict){
    ifstream dictionary;
    dictionary.open("/home/bread/ZJ/School/DSA/Practical/word/data/dictionary.txt");

    if (!dictionary.is_open()){
        return false;
    }

    while (!dictionary.eof()){
        string word;
        getline(dictionary, word);
        dict->add(word);
    }

    dictionary.close();
    return true;
}

//Menu for user to give an input
void menu(){
    cout << "\nThis is a spell checker\n";
    cout << "[1] Spell check a word\n";
    cout << "[2] Spell check a file\n";
    cout << "[3] Add a new word to dictionary\n";
    cout << "[4] Save to dictionary\n";
    cout << "[5] Display all words in dictionary that starts with a user specified letter\n";
    cout << "[6] Spell check a word with error\n";
    //cout << "";
    cout << "[0] Exit\n";
    cout << "Please enter an option: " << endl;
}

bool call(int option){
    if(option == 1){
        spellCheckWord(dict);
        return true;
    }
    else if (option == 2){
        spellCheckFile(dict);
        return true;
    }
    else if (option == 3){
        addWord(dict);
        return true;
    }
    else if (option == 4){
        saveDict(dict);
        return true;
    }
    else if (option == 5){
        prefixSearch(dict);
        return true;
    }
    else if (option == 6){
        errorCheck(dict);
        return true;
    }
    else if (option == 0){
        exit(0);
        //return true;
    }
    else {
        cout << "Invalid Option" << endl;
        return false;
    }
}

int main(){
    int option;

    loadDict(dict);

    while (true){
        start:
        menu();
        cin >> option;
        cin.clear();
        if (call(option) == false){
            goto start;
        } 
    }

    return 0;
}