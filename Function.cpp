#include"Header.h"

void Trie::Insert(string s, int k)//k la stt document cua tu dc insert
{
	Node* cur = root;
	int t;
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
vector<int> Trie::Find(string s)// ko tim thay return vector empty,tim dc return vector stt
{
	Node*cur = root;
	int i = 0;
	int t = 97;
	if (s[i]<'9') { t = 22; }
	while (cur->Child[s[i] - t] != NULL && i<int(s.size()))
	{
		t = 97;
		if (s[i]<'9') { t = 22; }
		cur = cur->Child[s[i] - t];
		i++;
	}
	vector <int> ans;
	ans.clear();
	if (i<int(s.size())) return ans;
	else return cur->docNum;
}

void Trie::DocumentInsert()
{
	ofstream fout; fout.open("ans.txt");
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
				m = 0;
				fout << s << endl;
				while (m<int(s.size()))
				{
					if ((s[m]>'z' || s[m]<'a') && (s[m]>'9' || s[m]<'0')) s.erase(m, 1);
					else m++;
				}
				Insert(s, i * 1000 + y);
				fout << s << endl;
			}
			fin.close();
			fout << i * 10000 + y << endl;
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
	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 65 && str[i] < 90)
			str[i] = tolower(str[i]);
	}
	int start = 0, end = 0;
	string str1;
	for (int i = 0; i < str.length(); i++) {
		if (i == str.length() - 1 || str[i + 1] == ' ') {
			str1 = str.substr(start, i - start + 1);
			if (stopwords.Find(str1).size() != 0) {
				str.erase(start, i - start + 2);
			}
			else
				start = i + 2;
		}
	}
	cout << str;
	classifyQuery(str, T);
}

void classifyQuery(string str, Trie T)
{
	if (str.find("and") != str.npos) {
		str.erase(str.find("and"), 4);
		cout << "AndSearching(str, T)";
	}
	else if (str.find("or") != str.npos) {
		str.erase(str.find("or"), 3);
		cout << "OrSearching(str, T)";
	}
	else if (str.find("#") != str.npos) {
		cout << "HashtagSearching";
	}
	else if (str.find("*") != str.npos) {
		cout << "WildcardSearching";
	}
	else if (str.find("$") != str.npos) {
		cout << "PriceSearching";
	}
	else if (str.find("\"") != str.npos){
		cout << "ExactMatching";
	}
}
/*
void AndSearching(string str, Trie T)
{
	int start = 0;
	int arr[101]{ 0 };
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ' || i == str.length() - 1) {
			string str1 = str.substr(start, i - start);
			if (str1 != "AND") {
				vector < int > ans = T.Find(str1);
				for (int j = 0; j < ans.size; j++) {
					arr[ans[j]]++;
				}
			}
		}
	}
	for (int i = 0; i < 101; i++) {
		if (arr[i] >= 2) {
			cout << i << endl;
		}
	}
}

void OrSearching(string str, Trie T)
{
	int start = 0;
	int arr[101]{ 0 };
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ' || i == str.length() - 1) {
			string str1 = str.substr(start, i - start);
			if (str1 != "AND") {
				vector < int > ans = T.Find(str1);
				for (int j = 0; j < ans.size; j++) {
					arr[ans[j]]++;
				}
			}
		}
	}
	for (int i = 0; i < 101; i++) {
		if (arr[i] != 0) {
			cout << i << endl;
		}
	}
}
*/
