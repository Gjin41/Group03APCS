void EliminateStopwords(string& str, Trie stopwords, Trie T) {
	int start = 0, end = 0;
	string str1;
	for (int i = 0; i < str.length(); i++) {
		if (str[i + 1] == ' ' || i == str.length() - 1) {
			str1 = str.substr(start, i - start + 1);
			vector < int > check = stopwords.Find(str1);
			if (check[0] != ' ') {
				str.erase(start, i - start + 1);
			}
			start = i + 2;
		}
	}
	classifyQuery(str, T);
}

void classifyQuery(string str, Trie T)
{
	if (str.find("AND") != str.npos) {
		cout << "AndSearching(str, T)\n";
	}
	else if (str.find("OR") != str.npos) {
		cout << "OrSearching(str, T)\n";
	}
	else if (str.find("#") != str.npos) {
		cout << "HashtagSearching\n";
	}
	else if (str.find("*") != str.npos) {
		cout << "WildcardSearching\n";
	}
	else if (str.find("$") != str.npos) {
		cout << "PriceSearching\n";
	}
}
