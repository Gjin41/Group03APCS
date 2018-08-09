#include "TrieLib.h"
bool cmp(pair<int,int> a,pair <int,int> b)
{
    return (a.second>b.second);
}
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
    strs.push_back( txt.substr( initialPos, min( pos, txt.size() ) - initialPos + 1 ) );

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
void Trie::StopwordTrie()
{
	ifstream fin;
	fin.open("stopwords.txt");
	string s;
	int m;
	while (fin.good())
	{
		fin >> s;
		for (m = 0; m < int(s.size()); m++)
		{
			if (s[m] <= 'Z' && s[m] >= 'A')
				s[m] -= ('Z' - 'z');
		}
		m = 0;
		while (m<int(s.size()))
		{
			if ((s[m]>'z' || s[m]<'a') && (s[m]>'9' || s[m]<'0')) s.erase(m, 1);
			else m++;
		}
		Insert(s, 0);
	}
	fin.close();
}
void MainMenu()
{
    system("CLS");
	Trie T;
	T.DocumentInsert();
	Trie stopwords;
	stopwords.StopwordTrie();
	int choice;
	cout << "1 - Search " << endl;
	cout << "2 - Exit " << endl;
	cin >> choice;
	switch (choice) {
	case 1: {
		system("cls");
		string str;
		cout << "Please input what you want to search: ";
		cin.ignore();
		getline(cin, str);
		EliminateStopwords(str, stopwords, T);
		break;
	}
	case 2:
		exit(0);
		break;
	}
}

void EliminateStopwords(string& str,Trie stopwords, Trie T) {
	for (int i = 0; i < int(str.length()); i++) {
		if (str[i] >= 65 && str[i] < 90)
			str[i] = tolower(str[i]);
	}
	int start = 0;
	string str1;
	for (int i = 0; i < int(str.length()); i++) {
		if (i == int(str.length()) - 1 || str[i + 1] == ' ') {
			str1 = str.substr(start, i - start + 1);
			if (stopwords.Find(str1).size() != 0) {
				str.erase(start, i - start + 2);
			}
			else
				start = i + 2;
		}
	}
	classifyQuery(str, T);
}
void classifyQuery(string str, Trie T)
{
	if (str.find("and") != str.npos) {
		str.erase(str.find("and"), 4);
		Search(str,T,0);
	}
	else if (str.find("or") != str.npos) {
		str.erase(str.find("or"), 3);
		Search(str,T,0);
	}
	else if (str.find("#") != str.npos) {
		Search(str,T,0);
	}
	else if (str.find("*") != str.npos) {
        str.erase(str.find("and"), 2);
		cout << "WildcardSearching";
	}
	else if (str.find("$") != str.npos) {
		Search(str,T,0);
	}
	else if (str.find("\"") != str.npos){
		cout << "ExactMatching";
	}
	else
    {
        Search(str,T,0);
    }
}
void Trie::Print(string word,int g,int isStrict)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);
    int Q=0,m,color,isP=0;
    int C=50,P=5;//changable
    ofstream fout;
    fout.open("ans.txt");
	stringstream ss;
	ss << g/1000;
	stringstream temp2;
	temp2<<g%1000;
	string t;
	if(g/1000>=10)
		t="Group"+ss.str();
	else
		t="Group0"+ss.str();
	if (g%1000>=10)
		t+="News" +temp2.str()+ ".txt";
	else
		t+="News0"+temp2.str()+ ".txt";
	ifstream fin;
	string s;
	fin.open(t);
	cout<<t<<endl;
	t="";
	vector <string> input;
	queue <string> pre;
	split(word,input,' ');
    if (isStrict==0)
    {
    while (fin.good()&&C>0)
    {
        color=0;
        fin >> t;
        if (isP==0)
        {
            if (int(pre.size())>P) pre.pop();
            pre.push(t);
        }
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
        for (m=0;m<int(input.size());m++) if (s==input[m]) {Q=1;color=1;isP=1;}
        if (Q==1)
        {
            if (isP==1) while (pre.size()>1)
            {
                cout<<pre.front()<<" ";
                pre.pop();
            }
            if (color==1) SetConsoleTextAttribute(hConsole, 4);
            else SetConsoleTextAttribute(hConsole, 7);
            cout<<t<<" ";
            C--;
        }
    }
    cout<<endl;
    }
    else
    {
    while (fin.good()&&C>0)
    {
        color=0;
        fin >> t;
        if (isP==0)
        {
            if (int(pre.size())>P) pre.pop();
            pre.push(t);
        }
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
        for (m=0;m<int(input.size());m++) if (s==input[m]) {Q=1;color=1;isP=1;}
        if (Q==1)
        {
            if (isP==1) while (pre.size()>1)
            {
                cout<<pre.front()<<" ";
                pre.pop();
            }
            if (color==1) SetConsoleTextAttribute(hConsole, 4);
            else SetConsoleTextAttribute(hConsole, 7);
            cout<<t<<" ";
            C--;
        }
    }
    cout<<endl;
    }
}
void Search(string s,Trie T,int isStrict)
{
    int const p=5;
    unordered_map <int,int> H;
    vector <int> ans;
    vector <string> input;
    vector <pair<int,int>> L;// docnum score
    int i,j;
    split(s,input,' ');
    for (i=0;i<int(input.size());i++)
    {
        ans=T.Find(input[i]);ans.push_back(-1);
        //for (i=0;i<ans.size();i++) cout<<ans[i]<<endl;
        for (j=0;j<int(ans.size());j++)
        {
            if (H.find(ans[j])==H.end())
            {
                L.push_back(make_pair(ans[j],1));
            }
            if (ans[j]==ans[j+1]) H[ans[j]]+=1;
            else H[ans[j]]+=p;
        }
    }
    H[-1]=-10;
    for (i=0;i<int(L.size());i++) L[i].second=H[L[i].first];
    sort(L.begin(),L.end(),cmp);
    for (i=0;i<int(L.size());i++) cout<<L[i].first<<" "<<L[i].second<<endl;
    i=1;
    while (i<=5&&i<int(L.size()))
    {
        T.Print(s,L[i-1].first,isStrict);
        i++;
    }
    if (L.size()==1) cout<<"No result"<<endl;
    cout<<"0.Menu"<<endl;
    cin>>i;
    MainMenu();
}
