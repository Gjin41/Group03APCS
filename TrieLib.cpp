#include "TrieLib.h"
void Trie::Insert(string s,int k)//k la stt document cua tu dc insert
{
    Node* cur=root;
    int t;
    for (int i=0;i<int(s.size());i++)
    {
        t=97;
        if (s[i]<='9'){t=22;}
        int q=s[i]-t;
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
    if (s[i]<='9'){t=22;}
    while (cur->Child[s[i]-t]!=NULL&&i<int(s.size()))
    {
        if (s[i]<'9')t=22;else t=97;
        cur=cur->Child[s[i]-t];
        i++;
        if (s[i]<'9')t=22;else t=97;
    }
    vector <int> ans;
    ans.clear();
    if (i<int(s.size())) return ans;
    else return cur->docNum;
}
void Trie::DocumentInsert()
{
    ofstream fout;fout.open("ans.txt");
	ifstream fin;
	stringstream file;
	string a;
	int m;
	for (int i = 1; i < 10; i++)
	{
		for (int y = 1; y <= 100; y++)
		{
			if (y < 10)
				file << "Group0" << i << "News0" << y << ".txt";
			else
				file << "Group0" << i << "News" << y << ".txt";
			a = file.str();
			fin.open(a);
			file.str(string());
			string s;
			while (fin.good())
			{
				fin >> s;
				for (m = 0; m < int(s.size()); m++)
				{
				    if (s[m] <= 'Z' && s[m] >= 'A')
						s[m] -= ('Z' - 'z');
				}
				m=0;
				fout<<s<<endl;
                while (m<int(s.size()))
                {
                    if ((s[m]>'z'||s[m]<'a')&&(s[m]>'9'||s[m]<'0')) s.erase(m,1);
                    else m++;
                }
				Insert(s, i*1000+y);
				fout<<s<<endl;
			}
			fin.close();
			fout<<i*10000+y<<endl;
		}
	}
}
