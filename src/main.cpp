//#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#include "dict.h"

using namespace std;

//global declaration(s)
Trie *dict = new Trie();



//changes case to lower case/upper case based on user input
char changeCase(char c){
    char caseChanged;

    if (islower(c)){
        caseChanged = toupper(c);
        cout << caseChanged << endl;
        cout << c << endl;
        return caseChanged;
    }
    if (isupper(c)){
        caseChanged = tolower(c);
        cout << caseChanged << endl;
        cout << c << endl;
        return caseChanged;
    }
}

//Function to append word into trie
void addWord(Trie *dict){
    string word;

    cout << "Enter a word: ";
    cin.ignore();
    getline(cin, word);
    cin.clear();

    dict->add(word);

    cout << endl;

    cout << "Word added" << endl;
}

//checks for word in trie
void spellCheckWord(Trie *dict){
    string word;

    cout << "Enter word to check: ";
    cin.ignore();
    getline(cin, word);
    cin.clear();
    cout << endl;

    if (dict->find(word) == true){
        cout << "Word is spelt correctly." << endl;
    }
    else {
        cout << "Word is spelt incorrectly or it does not exist." << endl;
    }
}

//Insert a file to see for incorrect words
bool spellCheckFile(Trie *dict){
    string path, extChecker;
    ifstream dictionary;

    cout << "We only accept .txt filetypes" << endl;

    cout << "Example: /home/bread/ZJ/School/DSA/Practical/Spellchecker/data/RandomWords100.txt" << endl;
    cout << "Enter a path: ";
    cin.ignore();
    getline(cin, path);
    cin.clear();
    cout << endl;

    //check for file extension
    extChecker = path.substr(path.length() - 4);
    if (extChecker != ".txt"){
        cout << "Do not try. \".txt\" extensions only" << endl;
        return false;
    }

    dictionary.open(path);

    if (!dictionary.is_open()){
        return false;
    }

    while (!dictionary.eof()){
        string word;
        getline(dictionary, word);
        if (word.empty()){
            continue;
        }
        if (dict->find(word) == false){
            cout << word << " is spelt incorrectly." << endl;
        }
    }

    dictionary.close();
    return true;
}

//save words from trie into user dictionary
bool saveDict(Trie *dict){
    ofstream dictionary;
    dictionary.open("/home/bread/ZJ/School/DSA/Practical/Spellchecker/data/UserDictionary.txt");

    if (!dictionary.is_open()){
        cout << "error" << endl;
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

//Search for all words that starts with user input char
void prefixSearch(Trie *dict){
    string str;
    char c, cOpp;

    cout << "Enter a letter to display all words starting with the given letter: ";
    cin.ignore();
    getline(cin, str);
    cout << str << endl;
    if (str.length() > 1){
        cout << "We only accept a character. Please adhere to the rules." << endl;
        return;
    }
    c = str[0];
    cin.clear();

    //check if prefix is alphabet
    //if prefix is not alphabet, do not attempt to change its case
    if (isalpha(c)){
        cOpp = changeCase(c);
        vector<string> words2 = dict->getwords(cOpp);
        for (int i = 0; i < words2.size(); i++){
            cout << words2[i] << endl;
        }
    }
    vector<string> words = dict->getwords(c);

    for (int i = 0; i < words.size(); i++){
        cout << words[i] << endl;
    }
}

//Error checking of a given word
void errorCheck(Trie *dict){
    string word;

    cout << "This checks for transposition and substitution errors." << endl;
    cout << "Enter a word: "; 
    cin.ignore();
    getline(cin, word);
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

//Loads the dictionary into trie and user dictionary
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

//Calls respective functions based on user input
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

//Checks that user input is a number and not a alphabet
bool inputValidator(string option){
    for (int i = 0; i < option.length(); i++){
        char c = option[i];
        if (!isdigit(c)){
            
            return false;
        }
    }
    return true;
}

//start of program
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