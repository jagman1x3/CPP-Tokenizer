#pragma once
#include <iostream>
#include <string>
using namespace std;


class Token
{
public:
	int type;
	string value;
	Token(const string v, const int t);
	void print();
};
