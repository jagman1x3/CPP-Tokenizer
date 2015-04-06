#pragma once
#include <iostream>
#include <string>
using namespace std;

class Token
{
public:
	int type;
	string value;
	Token(string v, int t);
	~Token();
	void print();
};
