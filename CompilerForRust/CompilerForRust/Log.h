#pragma once
#include <fstream>
#include <iostream>
#include "Token.h"

#define LOG_PATH "log.txt"

using namespace std;

//����һ���µ���־
void create_new_log();

//�������־�ļ�
void cout_log(string message);
void cout_log(token_type type);

//���һ�����з�
void endl_log();
