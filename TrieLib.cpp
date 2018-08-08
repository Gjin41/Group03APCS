#include "TrieLib.h"
void Trie::Insert(string s,int k)//k la stt document cua tu dc insert
{
    Node* cur=root;
    int t;
    for (int i=0;i<int(s.size());i++)
    {
        if (s[i]<='$') t=-1;
        else if (s[i]<='9') t=22;
        else t=97;
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
    int i=0,t;
    if (s[i]<='$') t=-1;
    else if (s[i]<='9') t=22;
    else t=97;
    while (cur->Child[s[i]-t]!=NULL&&i<int(s.size()))
    {
        if (s[i]<='$') t=-1;
        else if (s[i]<='9') t=22;
        else t=97;
        cur=cur->Child[s[i]-t];
        i++;
        if (s[i]<='$') t=-1;
        else if (s[i]<='9') t=22;
        else t=97;
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
                while (m<int(s.size()))
                {
                    if ((s[m]>'z'||s[m]<'a')&&(s[m]>'9'||s[m]<'0')&&s[m]!='$'&&s[m]!='#') s.erase(m,1);
                    else m++;
                }
				Insert(s, i*1000+y);
				fout<<s<<endl;
			}
			fin.close();
		}
	}
}
int getword(string s,string word)
{
	for(int i=0;i<s.size();i++)
	{
		if (s[i]==word[0])
		{
			int l=word.size();
			int k;
			for(k=0;k<l;k++)
			{
				if (s[i+k]!=word[k])
					break;
			}
			if (k==l)
				return i;
		}

	}
	return -1;
}
void Trie::Print(string word,int g)
{
	ifstream fin;
	stringstream ss;
	ss << g%1000;
	stringstream temp2;
	temp2<<g/1000;
	string t;
	if(g%1000>=10)
		t="Group"+ss.str();
	else
		t="Group0"+ss.str();
	if (g/1000>=10)
		t+="News" +temp2.str()+ ".txt";
	else
		t+="News0" +temp2.str()+ ".txt";
	string s;
	string temp;
	fin.open(t);
	while(!fin.eof())
	{
		getline(fin,temp);
		s+=temp;
	}
	string s2=s;
	for(int m=0;m<s2.size();m++)
	{
		if (s2[m] <= 'Z' && s2[m] >= 'A')
						s2[m] -= ('Z' - 'z');
	}

	string tmp=".";
	int k=getword(s2,word);
	if (k !=-1)
	{

		int i=k;
		while(i>0&&s2[i]!=tmp[0])
			i--;

	if(i>0)
		i+=2;
	else
		i=0;
	while(s2[i]!=tmp[0])
	{
		if(i!=k)
		{
		cout<<s2[i];
		i++;
		}
		else
		{
			system("color 4");
			int j=k;
			for(j;j<word.size();j++)
				cout<<s2[j];
			i+=word.size();
			system("color 7");
		}
	}
	}
}
