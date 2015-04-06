#include "Tokenizer.h"

using namespace std;

Tokenizer::Tokenizer()
{
}


Tokenizer::~Tokenizer()
{
}

int main(char *argv[], int argc){
	cout << "hello world\n";
	Token t("test", 1);
	t.print();
	cin.ignore();
}
