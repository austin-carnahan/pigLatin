/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: raccoonmoonswoon
 *
 * Created on April 10, 2017, 3:47 PM
 */

#include <cstdlib>
#include <string>
#include <cctype>
#include <iostream>

using namespace std;
//Data types and global variables ==========================================


struct Word{
    string english;
    string piglatin;
};

bool decode = false; //flag for type of conversion


//function prototypes======================================================
Word *getSentence(string, int &);
Word *engToPig(Word *, int);
Word *pigToEng(Word *, int);
void printPig(Word*, int);
void printEng(Word *, int);
//==========================================================================


int main() {
    int wcount;
    string input;
    Word *ptr = nullptr;
    int choice;
    
    do {
        cout <<"Welcome to the Pig Latin translator. Would you like to...\n"
             <<"1) Convert English to Pig Latin\n"
             <<"2) Decode Pig Latin\n"
             <<"3) Quit\n";
        cin >> choice;
        
        while (choice < 1 || choice > 3){
            cout << "Please enter a valid selection (1-3): \n";
            cin >> choice;
        }
        
        if(choice == 1){
            decode = false; //set global flag    
            cout << "Please enter a sentence you would like to convert to pig latin: \n";
            cin.ignore();
            getline(cin, input);
            cout << "\nOutput:\n";
            ptr = getSentence(input, wcount);
            engToPig(ptr, wcount);
            printPig(ptr, wcount);
            cout << "\n";
            cout << "\n";

        } else if (choice == 2){
            decode = true; //set global flag
            cout << "Please enter a sentence you would like to decode: \n";
            cin.ignore();
            getline(cin, input);
            cout << "\nOutput:\n";
            ptr = getSentence(input, wcount);
            pigToEng(ptr, wcount);
            printEng(ptr, wcount);
            cout << "\n";
            cout << "\n";
        } else {
            continue;
        }
    }while (choice != 3);
    
    cout << "Thanks for using the pig latin translator.\n";
    ptr = nullptr;
    delete ptr;
    return 0;
}

//Function Definitions ========================================================

Word *getSentence(string input, int &wcount){
    int spaces = 0;
    Word *sentence = nullptr;
    string space = " ";
    
    //count the number of spaces
    for (int i = 0; i < input.length(); i++){
        if(input[i] == ' '){
            spaces += 1;
        }
    }
    
    //number of words is spaces + 1
    wcount = spaces + 1;
    
    //dynamically allocate arrays of Word structs & word index(size and pos))
    sentence = new Word[wcount];
    int wordIndex[wcount][2];
    
    //strore the length and location of each word
    int index= 0; //wordIndex array index
    int j = 0; //counter var
    int pos = 0; // pos of start of word in eng string
    int size = 0; //size of word

    while (j < input.size()){

        if(input[j] == ' '){
            wordIndex[index][0] = pos; //store words pos
            wordIndex[index][1] = size; //store words size
            index ++; //increment array index (move to next word))
            size = 0; //reset word size
            j++; //increment eng string counter
        }else if(j == input.size()-1){
            size ++;
            wordIndex[index][0] = pos; //store words pos
            wordIndex[index][1] = size; //store words size
            j++;
        }else if(input[j-1] == ' ' || j == 0){
            pos = j; //this is the start of a word, store its pos
            size ++; //increment size counter
            j++; 

        }else{
            size++; //neither a space or the start of a word, increment size
            j++;                      
        }
        
    }
    
    // store word subtrings in struct array
    if(decode == false){
        for(int i = 0; i < wcount; i++){
           sentence[i].english = input.substr(wordIndex[i][0], wordIndex[i][1]);       
        }
    } else {
       for(int i = 0; i < wcount; i++){
           sentence[i].piglatin = input.substr(wordIndex[i][0], wordIndex[i][1]);  
        }
    }
       
////for testing   
//    for (int i=0; i< wcount; i++){
//        cout << sentence[i].english << " ";
//    }
    
    
    //return a pointer to the struct array
    return sentence;
}
//=============================================================================

Word *engToPig(Word *arr, int n){
    string pig = "";
    string first = "";
    string way = "way";
    string ay = "ay";
    
    for(int i = 0; i < n; i++){
        //check for words beginning with vowels
        if(tolower(arr[i].english[0]) == 'a' ||
                tolower(arr[i].english[0]) == 'e' ||
                tolower(arr[i].english[0]) == 'i' ||
                tolower(arr[i].english[0]) == 'o' ||
                tolower(arr[i].english[0]) == 'u')
                 {
            pig = arr[i].english; //make a copy of the english word
            pig.append(way); //make it piggy
            arr[i].piglatin.swap(pig); //stick it into the array
        }else{
            pig = arr[i].english; //make a copy of the english word
            first = pig[0];//get the first letter
            pig.append(first); 
            pig.append(ay); //make it piggy
            pig.erase(0, 1);
            arr[i].piglatin.swap(pig); //stick it into the array
            first = ""; //reset fist
        }
    }
    
//    //for testing   
//    for (int i=0; i< n; i++){
//        cout << arr[i].piglatin << " ";
//    }
    
    
    return arr;
}
//=============================================================================

Word *pigToEng(Word *arr, int n){
    string first = "";
    string eng = "";
    int size;
    
    for(int i=0; i < n; i ++){
        size = arr[i].piglatin.size();
        
        if(arr[i].piglatin[size-3] == 'w'){
            eng = arr[i].piglatin;
            eng.erase((size-3), 3);
            arr[i].english.swap(eng);
        }else{
            eng = arr[i].piglatin;
            first = eng.substr(size-3, 1);
            eng.erase(size-3, 3);
            eng.insert(0, first);
            arr[i].english.swap(eng);
            first = "";
        }
    }
    
    
}
//============================================================================

void printPig(Word *arr, int n){
    for(int i = 0; i < n; i++){
        cout << arr[i].piglatin << " ";
    }
}
//=============================================================================

void printEng(Word *arr, int n){
    for(int i = 0; i < n; i++){
        cout << arr[i].english << " ";
    }
}

