#include <iostream>
#include <map>
#include <vector>
#include "Token.h"
using namespace std;

int tokenIndex;
const int MAX_SYMBOL_SIZE = 2;
map<string, int> m;

vector<char> SINGLE_SYMBOLS = {'!', '%', '&', '(', ')', '*', '+', ',', '-', '-', '/', ';', '<', '=', '>', '{', '|', '}', '~'};
vector<string> DOUBLE_SYMBOLS = {"!=", "&&", "<<", "<=", "==", ">=", ">>", "||"};
vector<string> KEYWORDS = {"char", "cin", "class", "cout", "else", "if", "int", "void", "while"};
int UNKNOWN = 0, IDENT = 298, INTEGER = 299;

int main(int argc, char** argv){
	Token* t = new Token("test", 1);
	t->print();
	for (int i = 0; i < KEYWORDS.size(); i++)
	{
		cout << "Keyword " << i << ":\t" << KEYWORDS[i] << "\n";
	}
	cin.ignore();
}
