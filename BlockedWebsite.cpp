/*
 * WSITES01.cpp
 *
 *  Created on: May 27, 2017
 *      Author: siddsahani
 *
 *  Problem Link : https://www.codechef.com/MAY17/problems/WSITES01
 */
#include <iostream>
#include <map>
#include <vector>

using namespace std;

enum WEBSITE_TYPE {
	BLOCKED,
	UNBLOCKED
};

class Trie {

public:
	map<char, Trie*>* childNode;
	bool isBlockedChar, isUnblockedChar;
	bool isEOS;  // Represents the end of string

	Trie() {
		childNode = new map<char, Trie*>();
		isUnblockedChar = isBlockedChar = false;
		isEOS = false;
	}
};

class BlockedWebsite {

private:
	Trie* trieRoot;

	void setTypeFlags(Trie* node, WEBSITE_TYPE type) {
		if (type == BLOCKED) {
			node->isBlockedChar = true;
		} else {
			node->isUnblockedChar = true;
		}
	}

	void insertString(Trie* root, char* str, WEBSITE_TYPE type) {
		if((str[0] == '\0') || root == NULL) {
			root->isEOS = true;
			return;
		}

		Trie* nextNode = NULL;
		map<char, Trie*>::iterator it = root->childNode->find(str[0]);
		if (it != root->childNode->end()) {
			nextNode = it->second;
		} else {
			Trie* newNode = new Trie();
			root->childNode->insert(pair<char, Trie*>(str[0], newNode));
			nextNode = newNode;
		}
		setTypeFlags(nextNode, type);
		insertString(nextNode, ++str, type);
	}

	void findFiltersUtil(Trie* root, vector<string>& filters, string filter) {

		if (root->isEOS) {
			return;
		}
		map<char, Trie*>::iterator it = root->childNode->begin();
		while(it != root->childNode->end()) {
			Trie* node = it->second;
			if (node->isBlockedChar && node->isUnblockedChar) {
				filter.push_back(it->first);
				findFiltersUtil(node, filters, filter);
			} else if (node->isBlockedChar) {
				filter.push_back(it->first);
				filters.push_back(filter);
			}
			filter.pop_back();
			++it;
		}
	}

public:
	BlockedWebsite() {
		trieRoot = new Trie();
	}

	void insertWebsiteName(string websiteName, WEBSITE_TYPE type) {
		char* inputString = const_cast<char*>(websiteName.c_str());
		if (inputString == NULL) {
			return;
		}
		insertString(trieRoot, inputString, type);
	}

	vector<string> findFilters() {
		vector<string> filters;
		string filter;
		findFiltersUtil(trieRoot, filters, filter);
		return filters;
	}
};

int main() {

	int N;
	cin>>N;
	BlockedWebsite* blockedWebsite = new BlockedWebsite();
	while(N--) {
		char type;
		string inputString;
		cin>>type;
		cin>>inputString;
		blockedWebsite->insertWebsiteName(inputString, type == '-' ? WEBSITE_TYPE::BLOCKED : WEBSITE_TYPE::UNBLOCKED);
	}

	vector<string> filters = blockedWebsite->findFilters();
	if (filters.size() == 0) {
		cout<<-1;
	} else {
		cout<<filters.size()<<"\n";
		vector<string>::iterator it = filters.begin();
		while(it != filters.end()) {
			cout<<*it<<"\n";
			++it;
		}
	}

	return 0;
}

