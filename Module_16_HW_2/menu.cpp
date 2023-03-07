
#include <iostream>
#include "menu.h"
#include <vector>
#include <memory>
#include <unordered_map> 
#include < map >
#include <string>

using namespace std;



int Menu::findMessage(string& login) {
		
	// �������� �� ����� ������ ��������� � ������� ������� �������� ������������
	int i = 0;
	for (multimap<string, string >::iterator it = messages.begin(); it != messages.end(); ++it)
	{
		if (it->first == _curentName) {
			i++;
			cout << i << endl;
		}
	}
	return i;

}
	// ����� ������ � ����
bool Menu:: changeLogin(string& login) {							// ������� �������� ������ �� �������		

		unordered_map<string, string>::iterator itFindLogin = mapUsers.find(login);

		if (itFindLogin != mapUsers.end()) {						// 
			return true;
		}

		return false;
}

	// ���������� ������ ������
void Menu::saveLogPass(string& login, string& password) {														// ������ ������
	mapUsers.emplace(login, password);
}

	// ���� ���������
bool Menu:: main_menu() {	//char operation	
				
	char operation;
	cout << " 1 - Enter, 2 - Registration, 0 - Out" << endl;

	cin >> operation;

	switch (operation)
	{
	case '1': {																// ���� � �������

		if (mapUsers.empty()) { cout << "No users" << endl; return true; }	// ���� ���� ������	
		string login, password;

		cout << " Enter login: ";
		cin >> login;

		cout << " Enter password: ";
		cin >> password;

		unordered_map < string, string >::iterator itBegin = mapUsers.find(login);
		if (changeLogin(login) && (itBegin->second == password)) {					// �������� ������ � ������ ��������

			_curentName = login;							// ���������� ������� ����� 
			chatRun = true;	
			cout << endl << endl << "\tUser:" << _curentName << " You have: " << findMessage(login) << " messenge(s)." << endl;
			}	

			else {
				cout << "Try again" << endl; 
			}
		return true;
		}

		case '2': {					// ����������� ������������
			string login, password;

			cout << " Enter login: ";
			cin >> login;

			cout << " Enter password: ";
			cin >> password;

			if (!changeLogin(login)) {
				cout << endl << endl << "\tUser: " << login << ". Registration completed. " << endl;
				saveLogPass(login, password);

				chatRun = true;
				_curentName = login;
				return true;
			}
			else {
				cout << " Login is busy." << endl;
				return true;
			}

		}

		case '0': {					// ����� �� ���������
			chatRun = false;
			_curentName = " ";
			return false;
		}
		default: {
			cout << "wrong command." << endl;	// �� ��������� ������� ��������
		}				
				 return true;
		}
	}

	// ���� ���� ( ����� ����� � �������)
bool Menu:: chat() {
	char operation;
	cout << "1 - read, 2 - send, 3 - send to all, 4 - delete messages, other - exit" << endl;
	cin >> operation;

	switch (operation)
	{
	case '1': {														// ��������� ���������
		cout << "read message" << endl;

		for (multimap<string, string >::iterator it = messages.begin(); it != messages.end(); ++it)
		{
			if (it->first == _curentName)
				cout << it->second << endl;
		}

		return true;													// �������� � ���� ����
	}
	case '2': {															// ��������� ��������� ��������
		cout << " Send to: ";
		string nameTo;
		cin >> nameTo;

		if (!changeLogin(nameTo)) {						// �������� �������� �� �������
			cout << " Recipient not found." << endl;
			break;
		}

		cout << "text: ";// << endl;

		string text;
		cin >> text;
		/*vector<string> vec;
		while ((getline(cin, text, ';')) && vec.size() < 4) vec.push_back(text);*/

		messages.emplace(nameTo, text);
			// ��������� ��������� 

		return true;													// �������� � ���� ����
		}
		case '3': {														// ��������� ���� �������������
			cout << "text:";// << endl;
			string text;
			cin >> text;
		
			for (unordered_map < string, string >::iterator it = mapUsers.begin(); it != mapUsers.end(); ++it) {
				if (it->first == _curentName) continue;
				messages.emplace(it->first, text);
			}

		}
		 return true;

		case '4': {												// ������� ��� ��������� ������������

			for (multimap < string, string >::iterator it = messages.begin(); it != messages.end();) {
				if (it->first == _curentName) {
					it = messages.erase(it);
					continue;
				}
				++it;
			}

			return true;											// �������� � ���� ����

		}
		default:
			chatRun = false;
			return false;											// �������� ���
	}
}

