#include "Token.h"

Token::Token(string v, int t)
{
	value = v;
	type = t;
}


Token::~Token()
{
}

void Token::print(){
	cout << "Token: " << value << "\tType: " << type;
}