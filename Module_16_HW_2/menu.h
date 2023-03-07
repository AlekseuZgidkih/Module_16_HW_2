#pragma once
#include <iostream>
//#include"User.h"
//#include"Message.h"
#include <vector>
#include <memory>
#include <unordered_map> //unordered_
#include < map >

using namespace std;

class Menu {

private:
	unordered_map < string /* login */, string /* password */> mapUsers;

	multimap<string/* login */,string /*text*/> messages;

public:
	Menu() = default;							// �����������
	~Menu() = default;							// ����������

	string _curentName;
	bool chatRun = false;						// ��� �������� ������������� ������ �����

	// ������� �������� ���������
	int findMessage(string& login);
	// ����� ������ � ����
	bool changeLogin(string& login);

	// ���������� ������ ������
	void saveLogPass(string& login, string& password);

	// ���� ���������
	bool main_menu();
	// ���� ���� ( ����� ����� � �������)
	bool chat();
};

