// C++ implementation of search and insert
// operations on Trie
// index : done
#include <ctime>
#include <bits/stdc++.h>
using namespace std;
//-----------------Trie----------------------

struct Node
{
    char value;
    Node* Child[26]={0};
    vector < pair <int,int> > index;
    Node(char x)
    {
        value=x;
        index.clear();
    }
};
class Trie
{
    Node* root= new Node(' ');
    public:
    void Insert(string s,int k,int l);
    vector<pair <int,int> > Find(string s);
};
void Trie::Insert(string s,int k,int l)
{
    Node* cur=root;
    for (int i=0;i<int(s.size());i++)
    {
        if (cur->Child[s[i]-97]==NULL)
        {
            cur->Child[s[i]-97]= new Node(s[i]);
        }
        cur=cur->Child[s[i]-97];
    }
    pair <int,int> temp;
    temp.first=k;
    temp.second=l;
    cur->index.push_back(temp);
}
vector<pair <int,int> > Trie::Find(string s)// ko tim thay return vector empty,tim dc return vector index
{
    Node*cur =root;
    int i=0;
    while (cur->Child[s[i]-97]!=NULL&&i<int(s.size()))
    {
        cur=cur->Child[s[i]-97];
        i++;
    }
    vector <pair <int,int> > ans;
    ans.clear();
    if (i<int(s.size())) return ans;
    else return cur->index;
}
//----------------------output-----------------------------
fstream fin,fout;
//---------Global Var-----------------------------------------
int loc=0;
Trie T;
//----------Helper Function-----------------------------------------
void split(const string& str, const string& delim,int docNum)//split str into words
{
    string temp;
  size_t start, end = 0;
  while (end < str.size()) {
    start = end;
    while (start < str.size() && (delim.find(str[start]) != string::npos)) {
      start++;  // skip initial whitespace
    }
    end = start;
    while (end < str.size() && (delim.find(str[end]) == string::npos)) {
      end++; // skip to end of word
    }
    if (end-start != 0) {  // just ignore zero-length strings.
        //output here
        fout<<string(str, start, end-start)<<":"<<start+loc<<endl;
        temp=string(str, start, end-start);
        if(temp[0]<'a') temp[0]+=32;
        T.Insert(temp,start+loc,docNum);
    }
  }
  loc+=str.size();
}
//----------------------------------------------------------------------
int main()
{

    fin.open("test.txt",ios::in);
    fout.open("ans.txt",ios::out);
    string s="";
    clock_t Begin = clock();
    //----------------input-----
    while (!fin.eof())
    {
        getline(fin,s);
        split(s,".,;: ",1);
        loc++;
    }
    //--------------------------
    cout<<T.Find("donec")[0].first;
    clock_t End = clock();
    //cout<<"time:"<<(double)(End - Begin) / CLOCKS_PER_SEC;
    delete &T;
    fin.close();
    fout.close();
    return 0;

}
