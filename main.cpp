#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Function prototypes at the top of the file for function decomposition
string vrot(string line, string key); //Rotates letters for vigenere cipher
string newKeys(string message, string key); //Sets the key as long as the message
string cap(string str); //Capitalizes the message
string capkey(string str); //Capitalizes the key
void deCode(string message,vector<string> &solvedWords); //Decrypts the message
int checkBook(string message);//Checks if the word is in the dictionary
void split(vector<string> &words,string message);//Splits up the sentance into a vector of words
/**
 * Print instructions for using the program.
 */
void printMenu();
/**
 * Returns the 0-based index in the English alphabet where `c` appears,
 * or -1 if `c` is not an uppercase letter in the alphabet.
 *
 * For example:
 *  - `findIndexInAlphabet('A')` returns 0
 *  - `findIndexInAlphabet('D')` returns 3
 *  - `findIndexInAlphabet('+')` returns -1
 *  - `findIndexInAlphabet('a')` returns -1
 */
int findIndexInAlphabet(char c);
/**
 * Returns `c` rotated by `amount` many characters forward. If we run out
 * of letters in the alphabet, wrap around back to 'A'. This method
 * assumes that `c` is an uppercase letter.
 * For example:
 *  - `rot('A', 0)` returns 'A'
 *  - `rot('A', 1)` returns 'B'
 *  - `rot('Z', 1)` returns 'A'
 *  - `rot('A', 10)` returns 'K'
 *  - `rot('J', 25)` returns 'I'
 */
char rot(char c, int amount);
/**
 * Returns a new string in which every character has been rotated by `amount`
 * letters. Lowercase letters are converted to uppercase and rotated.
 * Non-alphabetic characters are left alone.
 * For example:
 *  `rot("A", 0)` returns "A"
 *  `rot("AA", 3)` returns "DD"
 *  `rot("HELLO", 0)` returns "HELLO"
 *  `rot("HELLO", 1)` returns "IFMMP"
 *  `rot("oh HEL-LO!", 1)` returns "PI IFM-MP!"
 */
string rot(string line, int amount);

int main() {
    string command;

    cout << "Welcome to Ciphers!" << endl;
    cout << "-------------------" << endl;
    cout << endl;

    do {
        printMenu();
        cout << endl
             << "Enter a command (case does not matter): ";

        // Use getline for all user input to avoid needing to handle
        // input buffer issues relating to using both >> and getline
        getline(cin, command);
        cout << endl;

        //If the user wishes to enrycpt a piece of text using the caesar cipher
        //this will initiate, encrypt, and print out the new hidden text
        if(command=="c" || command=="C"){
            string message;
            string amount;
            cout << "Enter the text to encrypt:" << endl;
            getline(cin,message);
            cout << "Enter the number of characters to rotate by:" << endl;
            getline(cin,amount);
            cout << endl;
            cout << rot(message,stoi(amount)); 
        }

        //If the user wishes to decrypt a piece of text, this will initiate, decrypt, and print out the new text
        else if(command=="d" || command=="D"){
            string secret;
            vector<string> solvedWords;
            cout << "Enter the text to Caesar-cipher decrypt:" << endl;
            getline(cin, secret);
            split(solvedWords,secret);
            deCode(secret,solvedWords);
        }

        //If the user wishes to enrycpt a piece of text using the vigenre cipher, 
        //this will initiate, encrypt, and print out the new hidden text
        else if(command=="v" || command=="V"){
            string message;
            string key;
            string newKey;
            cout << "Enter text to encrypt:" << endl;
            getline(cin,message);
            cout << "Enter the Vigenère key:" << endl;
            getline(cin,key);
            message=cap(message);
            key=capkey(key);
            newKey=newKeys(message,key);
            cout << vrot(message,newKey);
        }

        cout << endl;

    } while (!(command == "x" || command == "X"));

    return 0;
}

void printMenu() {
    cout << "Ciphers Menu" << endl;
    cout << "------------" << endl;
    // Caesar Ciphers
    cout << "C - Encrypt with Caesar Cipher" << endl;
    cout << "D - Decrypt Caesar Cipher" << endl;
    // Vigenere
    cout << "V - Encrypt with Vigenère" << endl;
    // Utility
    cout << "X - Exit Program" << endl;
}

int findIndexInAlphabet(char c) {
    int check;
    check = ALPHABET.find(c);
    if(check==string::npos)
    {
        return -1;
    }
    else{
        return check;
    }
}

char rot(char c, int amount) {
    c = c+amount;
    if(c>'Z'){
        c = c - 'Z' + 'A' - 1;
    }
    return c;
}

string rot(string line, int amount) {
    string word;
    word=line;
    char letter;
    //Rotates each letter of the word
    for(int i=0;i<line.size();i++){
        letter = word.at(i);
        if(isalpha(letter)){
            if(letter>='a' && letter<='z'){
                letter = rot(toupper(letter),amount);
            }
            else{
                letter = rot(letter,amount);
            }
            word.at(i)=letter;
        }
    }
    return word;
}

//This function's purpose is to shift the message using the vigenere cipher
//It will take in the key and the message and will return the word once it has been encrypted
string vrot(string line, string key){
    string word;
    word=line;
    char letter;
    //Rotates the letter of the word based on they key
    for(int i=0;i<line.size();i++){
        if(isalpha(line.at(i))){
            letter=(line.at(i)+key.at(i))%26;
            letter+='A';
            word.at(i)=letter;
        }
        
        
    }
    return word;
}

//This function's purpose is to take in the key and message and make the key as long as the message
//It will then return the new key to be used to encrypt the message
string newKeys(string message, string key){
    string temp;
    string keytemp;
    keytemp=key;
    temp=message;
    int j=0;
    //Makes the key size the same as the message
    for(int i=0;i<message.size();i++){
        if(j==keytemp.size()){
            j=0;
        }
        if(isalpha(temp.at(i))){
            temp.at(i)=keytemp.at(j);
            j++;
        }
    }
    return temp;
}

//This function's purpose is to capitalize every letter of the message
string cap(string str){
    string CAPWORD;
    CAPWORD=str;
    //Capitalizes the string
    for(int i=0;i<str.size();i++){
        if(isalpha(CAPWORD.at(i))){
            CAPWORD.at(i)=toupper(CAPWORD.at(i));
        }
    }
    return CAPWORD;
}

//This functions purpose is to capitalize every letter in the key and return it
string capkey(string str){
    string CAPWORD;
    //Capitalizes the key
    for(int i=0;i<str.size();i++){
        if(isalpha(str.at(i))){
            CAPWORD.push_back(toupper(str.at(i)));
        }
    }
    return CAPWORD;
}

//This function's purpose is to decrypt the message from a caesar cipher
//It takes in the vector of words from the message and decrypts it
//This will either return multiple words for a single piece of text
//Or it will return a sentence that has now been decrpyted
void deCode(string message,vector<string> &solvedWords){
    string solved;
    char letter;
    int check=-1;
    int count=0;
    int breakCheck=0;
    int single=0;
    //Goes through each vector and decodes them
    for(int i=0;i<27;i++){
        for(int b=0;b<solvedWords.size();b++){
            solved=solvedWords.at(b);
            for(int j=0;j<solved.size();j++){
                letter = solved.at(j);
                if(isalpha(letter)){
                    if(letter>='a' && letter<='z'){
                        letter = rot(toupper(letter),1);
                    }
                    else{
                        letter = rot(letter,1);
                    }
                    solved.at(j)=letter;
                }
            }
            solvedWords.at(b)=solved;
        }
        //Checks if it is a word in the dictionary
        for(int b=0;b<solvedWords.size();b++){
            check = checkBook(solvedWords.at(b));
            if(check==1){
                single=1;
                count++;
            }
            //If more than half are in the dictionary, it will print out the vectors
            if(solvedWords.size()>1){
                if(count==(solvedWords.size()/2)+1){
                    for(int m=0;m<solvedWords.size();m++){
                        cout << solvedWords.at(m) << " ";
                        breakCheck=100;
                    }
                    break;
                }
            }
            //If it is a single word and in the dictionary, it prints
            else{
                if(single==1){
                    cout << solvedWords.at(b) << endl;
                }
            }
            single=0;
            check=-1;
        }
        count = 0;
        if(breakCheck==100){
            break;
        }
    }
}

//This function's purpose is to read in the words from the dictionary txt file and see if the 
//words matches with a word from the dictionary
//If it does, it will then return 1, saying that this is a real word
int checkBook(string message){
    string word;
    ifstream inFs;
    inFs.open("dictionary.txt");
    while(!inFs.eof()){
        getline(inFs,word);
        if(message==word){
            return 1;
        }
    }
    return -1;
    inFs.close();
}

//The purpose of this function is to split up a sentence into multiple words using a vector
//If will then pass by reference changing the vector
void split(vector<string> &words, string message){
    string tempWord;
    for(int i=0;i<message.size();i++){
        char c=message.at(i);
        if(isspace(c)){
            if(!tempWord.empty()){
                tempWord=cap(tempWord);
                words.push_back(tempWord);
                tempWord.clear();
            }
        }
        else{
            tempWord.push_back(c);
        }
    }
    if(!tempWord.empty()){
        tempWord=cap(tempWord);
        words.push_back(tempWord);
    }
}
