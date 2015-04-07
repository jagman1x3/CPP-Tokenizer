#include "Token.h"

Token::Token(const string v, const int t)
{
	value = v;
	type = t;
}

void Token::print(){
	cout << "Token: " << value << "\tType: " << type << endl;
}