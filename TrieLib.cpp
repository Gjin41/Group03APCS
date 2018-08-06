#include "TrieLib.h"
void Trie::Insert(string s,int k)//k la stt document cua tu dc insert
{
    Node* cur=root;
    int t;
    for (int i=0;i<int(s.size());i++)
    {
        t=97;
        if (s[i]<'9'){t=22;}
        if (cur->Child[s[i]-t]==NULL)
        {
            cur->Child[s[i]-t]= new Node(s[i]);
        }
        cur=cur->Child[s[i]-t];
    }
    cur->docNum.push_back(k);
}
vector<int> Trie::Find(string s)// ko tim thay return vector empty,tim dc return vector stt
{
    Node*cur =root;
    int i=0;
    int t=97;
    if (s[i]<'9'){t=22;}
    while (cur->Child[s[i]-t]!=NULL&&i<int(s.size()))
    {
        t=97;
        if (s[i]<'9'){t=22;}
        cur=cur->Child[s[i]-t];
        i++;
    }
    vector <int> ans;
    ans.clear();
    if (i<int(s.size())) return ans;
    else return cur->docNum;
}
