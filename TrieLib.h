#ifndef TRIELIB_H_INCLUDED
#define TRIELIB_H_INCLUDED
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include<Windows.h>
#include <algorithm>
#include <stdlib.h>
#include <queue>
using namespace std;
//-----------------Trie----------------------
struct Node
{
    char value;
    Node* Child[38]={0};
    vector <int> docNum;//So thu tu document
    Node(char x)
    {
        value=x;
        docNum.clear();
    }
};
class Trie
{
    Node* root= new Node(' ');
    public:
    void Insert(string s,int k);
    vector<int> Find(string s);
    void DocumentInsert();
    void Print(string word,int g,int);
    void StopwordTrie();
};
void Search(string,Trie,int );
void MainMenu();
void EliminateStopwords(string& str,Trie stopwords, Trie T);
void classifyQuery(string str, Trie T);
#endif // TRIELIB_H_INCLUDED
