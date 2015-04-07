#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "Token.h"

using namespace std;

int main(int argc, char** argv){
	//int tokenIndex;
	const int MAX_SYMBOL_SIZE = 2;
	//map<string, int> tokenMap;

	vector<char> SINGLE_SYMBOLS = {'!', '%', '&', '(', ')', '*', '+', ',', '-', '-', '/', ';', '<', '=', '>', '{', '|', '}', '~'};
	vector<string> DOUBLE_SYMBOLS = {"!=", "&&", "<<", "<=", "==", ">=", ">>", "||"};
	vector<string> KEYWORDS = {"char", "cin", "class", "cout", "else", "if", "int", "void", "while"};
	int UNKNOWN = 0, IDENT = 298, INTEGER = 299;


	//Token* t = new Token("test", 1);
	//t->print();
	//for (int i = 0; i < KEYWORDS.size(); i++)
	//{
	//	cout << "Keyword " << i << ":\t" << KEYWORDS[i] << endl;
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
		if (c == '\''){
			str += c;
			is.get(c);
			while (c != '\'') {
				str += c;
				is.get(c);
			}
			str += c;
		}
		else if (isalpha(c)){
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

		if (str.empty()){
			continue;
		}

		cout << "Token: " << str << endl;
	}

	cin.ignore();
	return 0;
}

