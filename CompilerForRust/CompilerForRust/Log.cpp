#include "Log.h"

void create_new_log()
{
	ofstream log_file(LOG_PATH);
	if (log_file.is_open()) {
		log_file.close();

		cout << "New log file created successfully" << endl;
	}
}

void cout_log(string message)
{
	//ios::app   ���û���ļ�����ô���ɿ��ļ���������ļ�����ô���ļ�β׷��
	ofstream log_file(LOG_PATH, ios::app);
	if (log_file.is_open()) {
		log_file << message;

		log_file.close();
	}
}

void cout_log(token_type type)
{
	ofstream log_file(LOG_PATH, ios::app);
	if (log_file.is_open()) {
		log_file << (int)type;

		log_file.close();
	}
}

void endl_log()
{
	ofstream log_file(LOG_PATH, ios::app);
	if (log_file.is_open()) {
		log_file << endl;

		log_file.close();
	}
}