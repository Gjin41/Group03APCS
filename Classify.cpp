void EliminateStopwords(string& str, Trie stopwords, Trie T) {
	int start = 0, end = 0;
	string str1;
	for (int i = 0; i < str.length(); i++) {
		if (str[i + 1] == ' ' || i == str.length() - 1) {
			str1 = str.substr(start, i - start + 1);
			vector < int > ans = stopwords.Find(str1);
			if (ans[0] != ' ') {
				str.erase(start, i - start + 1);
			}
			start = i + 2;
		}
	}
	classifyQuery(str, T);
}

void classifyQuery(string str, Trie T)
{
	if (str.find('AND') != -1) {
		cout << "AndSearching(str, T)\n";
	}
	else if (str.find('OR') != -1) {
		cout << "OrSearching(str, T)\n";
	}
	else if (str.find('#') != -1) {
		cout << "HashtagSearching\n";
	}
	else if (str.find('*') != -1) {
		cout << "WildcardSearching\n";
	}
	else if (str.find('$') != -1) {
		cout << "PriceSearching\n";
	}
}
