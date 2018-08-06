#ifndef TRIELIB_H_INCLUDED
#define TRIELIB_H_INCLUDED
#include <vector>
#include <iostream>
using namespace std;
//-----------------Trie----------------------
struct Node
{
    char value;
    Node* Child[36]={0};
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
};
#endif // TRIELIB_H_INCLUDED
