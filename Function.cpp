#include "TrieLib.h"

void Trie::DocumentInsert()
{
	ifstream fin;
	stringstream file;
	string a;
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
			string s;
			while (fin.good())
			{
				fin >> s;
				for (int m = 0; m < int(s.size()); m++)
				{
					if (s[m] >= 58 && s[m] <= 64 || s[m] >= 33 && s[m] <= 47 || s[m] >= 91 && s[m] <= 96)
					{
						s[m] = 0;
						for (int n = m; n < int(s.size()); n++)
							s[n] = s[n + 1];
					}
						if (s[m] <= 'Z' && s[m] >= 'A')
						s[m] -= ('Z' - 'z');
				}
				Insert(s, y, i);
			}
		}
	}
}

void Trie::Insert(string s, int k, int p)//k la stt document cua tu dc insert
{
	Node* cur = root;
	int t;
	cur->docGroup.push_back(p);
	for (int i = 0; i<int(s.size()); i++)
	{
		t = 97;
		if (s[i]<'9') { t = 22; }
		if (cur->Child[s[i] - t] == NULL)
		{
			cur->Child[s[i] - t] = new Node(s[i]);
		}
		cur = cur->Child[s[i] - t];
	}
	cur->docNum.push_back(k);
}
/*vector<int> Trie::Find(string s)// ko tim thay return vector empty,tim dc return vector stt
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
*/