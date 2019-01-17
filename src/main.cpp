#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#include "dict.h"

using namespace std;

//global declaration(s)
Trie *dict = new Trie();

void changeCase(string word){
    transform(word.begin(),word.end(),word.begin(), ::tolower);
}

void addWord(Trie *dict){
    string word;

    cout << "Enter a word: ";
    cin >> word;
    cin.clear();

    changeCase(word);

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

    changeCase(word);
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
    cout << "Example: /home/bread/ZJ/School/DSA/Practical/Spellchecker/data/RandomWords100.txt" << endl;
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
        changeCase(word);
        if (dict->find(word) == false){
            cout << word << " is spelt incorrectly." << endl;
        }
    }

    dictionary.close();
    return true;
}

bool saveDict(Trie *dict){
    ofstream dictionary;
    dictionary.open("/home/bread/ZJ/School/DSA/Practical/Spellchecker/data/UserDictionary.txt");

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

    cout << "This checks for transposition and substitution errors." << endl;
    cout << "Enter a word: "; 
    cin >> word;
    cin.clear();

    if (dict->find(word) == true){
        cout << "Word is spelt correctly." << endl;
        return;
    }
    Flag flags = dict->errorChecker(word);
    if (flags.subError == true){
        cout << "You had substitution error." << endl;
        return;
    } 
    else if (flags.transError == true){
        cout << "You had transposition error." << endl;
        return;
    }
    else if (!flags.transError && !flags.subError){
        cout << "No input given." << endl;
    }
    else {
        cout << "Word is spelt incorrectly or does not exist." << endl;
        return;
    }
}

bool loadDict(Trie *dict){
    ifstream dictionary;
    ofstream userdictionary;
    dictionary.open("/home/bread/ZJ/School/DSA/Practical/Spellchecker/data/dictionary.txt");
    userdictionary.open("/home/bread/ZJ/School/DSA/Practical/Spellchecker/data/UserDictionary.txt");

    if (!dictionary.is_open() || !userdictionary.is_open()){
        return false;
    }

    while (!dictionary.eof()){
        string word;
        getline(dictionary, word);
        dict->add(word);
        userdictionary << word << endl;
    }

    userdictionary.close();
    dictionary.close();
    return true;
}

//Menu for user to give an input
void menu(){
    cout << "\nThis is a spell checker\n";
    cout << "[1] Spell check a word (no errors allowed)\n";
    cout << "[2] Spell check a file\n";
    cout << "[3] Add a new word to dictionary\n";
    cout << "[4] Save to dictionary\n";
    cout << "[5] Display all words in dictionary that starts with a user specified letter\n";
    cout << "[6] Spell check a word with error\n";
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

bool inputValidator(string option){
    for (int i = 0; i < option.length(); i++){
        char c = option[i];
        if (isalpha(c)){
            return false;
        }
    }
    return true;
}

int main(){
    string option;

    loadDict(dict);

    while (true){
        start:
        menu();
        cin >> option;
        cin.clear();
        if (!inputValidator(option)){
            cout << "We do not accept characters as an option. Try again." << endl;
            goto start;
        }
        int choice = stoi(option);
        if (call(choice) == false){
            goto start;
        } 
    }

    return 0;
}