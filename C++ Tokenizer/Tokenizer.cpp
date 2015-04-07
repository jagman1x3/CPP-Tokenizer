#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <vector>
#include "Token.h"

using namespace std;

const set<char> SINGLE_SYMBOLS = { '!', '%', '&', '(', ')', '*', '+', ',', '-', '-', '/', ';', '<', '=', '>', '{', '|', '}', '~', 
									'.', ',', ':', '\'', '"', '?', '[', ']', '#'};
const set<string> DOUBLE_SYMBOLS = { "!=", "&&", "<<", "<=", "==", ">=", ">>", "||", "::", "+=", "-=", "*=", "/", "%=", "&=", "^=",
									"<<=", ">>=", "->", "->*", ".*", "//"};
const set<string> KEYWORDS = { "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break", "case", 
	"catch","char", "char16_t", "char32_t", "class", "compl", "concept", "const", "constexpr", "const_cast", "continue", "decltype",
	"default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float", "for", 
	"friend","goto", "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", 
	"or","or_eq", "private", "protected", "public", "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof",
	"static", "static_assert", "static_cast", "struct", "switch", "template", "this", "thread_local", "throw", "true", "try", "typedef",
	"typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq" };
int UNKNOWN = 0, IDENT = 298, INTEGER = 299;
const int MAX_SYMBOL_SIZE = 3;
map<string, int> tokenMap;


void makeTokenMap(){
	int code = 300;
	for_each(SINGLE_SYMBOLS.begin(), SINGLE_SYMBOLS.end(), [](char const& c){
		string s(1, c);
		tokenMap[s] = (int)c;
	});
	set<string>::iterator it;
	for (it = DOUBLE_SYMBOLS.begin(); it != DOUBLE_SYMBOLS.end(); ++it){
		tokenMap[*it] = code++;
	}
	for (it = KEYWORDS.begin(); it != KEYWORDS.end(); ++it){
		tokenMap[*it] = code++;
	}
}

bool isSingleSymbol(const char c){
	return SINGLE_SYMBOLS.find(c) != SINGLE_SYMBOLS.end();
}

bool isDoubleSymbol(const string s){
	return DOUBLE_SYMBOLS.find(s) != DOUBLE_SYMBOLS.end();
}

int getType(const string s){
	auto it = tokenMap.find(s);
	if (it == tokenMap.end()){
		return IDENT;
	}
	return it->second;
}

void tokenize(ifstream* is, vector<Token>* tokens){
	makeTokenMap();

	char c;
	// using is.get() here makes it loop on whitespace at end of file
	while (*is >> c){
		string str;
		int tokenType = UNKNOWN;
		if (isalpha(c)){
			str += c;
			is->get(c);
			while (isalnum(c) || c == '_'){
				str += c;
				is->get(c);
			}
			is->unget();
		}
		else if (isdigit(c)){
			str += c;
			is->get(c);
			while (isdigit(c)){
				str += c;
				is->get(c);
			}
			is->unget();
			tokenType = INTEGER;
		}
		else if (isSingleSymbol(c)){
			str += c;
			for (int j = 0; j < MAX_SYMBOL_SIZE - 1; j++){
				is->get(c);
				if (isSingleSymbol(c)){
					str += c;
				}
				else{
					is->unget();
					break;
				}
				if (!isDoubleSymbol(str)){
					str = str.substr(0, str.size() - 1);
					is->unget();
					break;
				}
			}
		}

		if (str.empty()){
			continue;
		}
		//ignore comments
		if (str.compare("//") == 0){
			is->get(c);
			while (c != '\n'){
				is->get(c);
			}
			continue;
		}

		if (tokenType != INTEGER){
			tokenType = getType(str);
		}
		Token* token = new Token(str, tokenType);
		tokens->push_back(*token);

	}
}

int main(int argc, char** argv){
	cout << "Enter a filename." << endl;
	string filename;
	cin >> filename;
	cin.ignore(100, '\n');
	ifstream is(filename);
	if (!is){
		cout << "Error: Couldn't open the file." << endl;
		cin.ignore();
		return 2;
	}

	vector<Token> tokens;
	tokenize(&is, &tokens);
	for (int i = 0; i < tokens.size(); i++){
		cout << tokens[i].value << "\t\t" << tokens[i].type << endl;
	}
	cin.ignore();
	return 0;
}   


