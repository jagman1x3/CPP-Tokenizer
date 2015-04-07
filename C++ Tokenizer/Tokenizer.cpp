#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include "Token.h"

using namespace std;

const set<char> SINGLE_SYMBOLS = { '!', '%', '&', '(', ')', '*', '+', ',', '-', '-', '/', ';', '<', '=', '>', '{', '|', '}', '~', 
									'.', ',', ':', '\'', '"', '?', '[', ']'};
const set<string> DOUBLE_SYMBOLS = { "!=", "&&", "<<", "<=", "==", ">=", ">>", "||", "::", "+=", "-=", "*=", "/", "%=", "&=", "^=",
									"<<=", ">>=", "->", "->*", ".*"};
const set<string> KEYWORDS = { "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break", "case", 
	"catch","char", "char16_t", "char32_t", "class", "compl", "concept", "const", "constexpr", "const_cast", "continue", "decltype",
	"default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float", "for", 
	"friend","goto", "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", 
	"or","or_eq", "private", "protected", "public", "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof",
	"static", "static_assert", "static_cast", "struct", "switch", "template", "this", "thread_local", "throw", "true", "try", "typedef",
	"typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq" };
int UNKNOWN = 0, IDENT = 298, INTEGER = 299;
//int tokenIndex;
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

int main(int argc, char** argv){

	//Token* t = new Token("test", 1);
	//t->print();
	//for (int i = 0; i < KEYWORDS.size(); i++)
	//{
	//	cout << "Keyword " << i << ":\t" << KEYWORDS[i] << endl;
	//}

	//for (set<string>::iterator i = KEYWORDS.begin(); i != KEYWORDS.end(); i++){
	//	string x = *i;
	//	cout << x << endl;
	//}
	

	ifstream is("C:\\Users\\Jordan\\workspace\\Tokenizer\\src\\test.txt");
	if (!is){
		cout << "Couldn't open the file." << endl;
		return 1;
	}

	char c;
	while (is.get(c)){
		while (isspace(c)){
			is.get(c);
		}
		string str;
		int tokenType = UNKNOWN;
		//if (c == '\''){
		//	str += c;
		//	is.get(c);
		//	while (c != '\'') {
		//		str += c;
		//		is.get(c);
		//	}
		//	str += c;
		//}
		if (isalpha(c)){
			str += c;
			is.get(c);
			while (isalnum(c)){
				str += c;
				is.get(c);
			}
			is.unget();
		}
		else if (isdigit(c)){
			str += c;
			is.get(c);
			while (isdigit(c)){
				str += c;
				is.get(c);
			}
			is.unget();
			tokenType = INTEGER;
		}

		else if (isSingleSymbol(c)){
			str += c;
			for (int j = 0; j < MAX_SYMBOL_SIZE - 1; j++){
				is.get(c);
				if (isSingleSymbol(c)){
					str += c;
				}
				else{
					is.unget();
					break;
				}
				if (!isDoubleSymbol(str)){
					str = str.substr(0, str.size() - 1);
					is.unget();
					break;
				}
			}
		}



		if (str.empty()){
			continue;
		}

		//cout << str << endl;
	}

	makeTokenMap();
	//map<string, int>::iterator it;
	//for (it = tokenMap.begin(); it != tokenMap.end(); ++it){
	//	cout << it->first << '\t' << it->second << endl;
	//}

	cin.ignore();
	return 0;
}

