#include "TrieLib.h"
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}
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
				fout<<s<<endl;
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
			}
			fin.close();
		}
	}
}
void Trie::Print(string word,int g)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int C=20,Q=0,m,color;
    ofstream fout;
    fout.open("ans.txt");
	stringstream ss;
	ss << g%1000;
	stringstream temp2;
	temp2<<g/1000;
	string t;
	if(g%100>=10)
		t="Group"+ss.str();
	else
		t="Group0"+ss.str();
	if (g/1000>=10)
		t+="News" +temp2.str()+ ".txt";
	else
		t+="News0"+temp2.str()+ ".txt";
	ifstream fin;
	string s;
	fin.open(t);
	t="";
	//---------------------------
	vector <string> input;
	split(word,input,' ');
    while (fin.good()&&C>0)
    {
        color=0;
        fin >> t;
        s=t;
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
        for (m=0;m<int(input.size());m++) if (s==input[m]) {Q=1;color=1;}
        if (Q==1)
        {
            if (color==1) SetConsoleTextAttribute(hConsole, 4);
            else SetConsoleTextAttribute(hConsole, 7);
            cout<<t<<" ";
            C--;
        }

    }
	fin.close();
	fout.close();
}
void Search(string s,Trie T)
{
    int const p=2;
    unordered_map <int,int> H;
    vector <int> ans;
    vector <string> input;
    vector <pair<int,int>> L;// docnum score
    int i,j;
    split(s,input,' ');
    for (i=0;i<int(input.size());i++)
    {
        ans=T.Find(input[i]);ans.push_back(-1);
        for (j=0;j<int(ans.size());j++)
        if (H.find(ans[j])==H.end()) L.push_back(make_pair(ans[j],1));
    }
    for (i=0;i<int(L.size());i++) L[i].second=H[L[i].first];

}
