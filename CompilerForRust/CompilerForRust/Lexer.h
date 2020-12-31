#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Token.h"
#include "Log.h"

using namespace std;

class Lexer
{
public:
	string code;
	vector<Token*> tokens;
	size_t current_token_index;
	unsigned int line = 1;		//�к�
	unsigned int col = 1;		//�к�
	unsigned int tempCol = col;
public:
	Lexer(const string file);

	void split();	//�����ַ���
	bool is_split_symbol(char symbol);  //�жϷ���

	void next_token();
	token_type current_token_type();
	Token* current_token();
	string current_token_value();

	void print();   // д���ļ�
};
