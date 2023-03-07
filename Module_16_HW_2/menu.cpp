
#include <iostream>
#include "menu.h"
#include <vector>
#include <memory>
#include <unordered_map> 
#include < map >
#include <string>

using namespace std;



int Menu::findMessage(string& login) {
		
	// проходим по всему списку сообщений и считаем сколько текущему пользователю
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
	// Поиск логина в базе
bool Menu:: changeLogin(string& login) {							// функция проверки логина на наличие		

		unordered_map<string, string>::iterator itFindLogin = mapUsers.find(login);

		if (itFindLogin != mapUsers.end()) {						// 
			return true;
		}

		return false;
}

	// сохранение логина пароля
void Menu::saveLogPass(string& login, string& password) {														// запись логина
	mapUsers.emplace(login, password);
}

	// меню стартовое
bool Menu:: main_menu() {	//char operation	
				
	char operation;
	cout << " 1 - Enter, 2 - Registration, 0 - Out" << endl;

	cin >> operation;

	switch (operation)
	{
	case '1': {																// вход в профиль

		if (mapUsers.empty()) { cout << "No users" << endl; return true; }	// если база пустая	
		string login, password;

		cout << " Enter login: ";
		cin >> login;

		cout << " Enter password: ";
		cin >> password;

		unordered_map < string, string >::iterator itBegin = mapUsers.find(login);
		if (changeLogin(login) && (itBegin->second == password)) {					// проверка логина и пароля пройдены

			_curentName = login;							// запоминаем текущий логин 
			chatRun = true;	
			cout << endl << endl << "\tUser:" << _curentName << " You have: " << findMessage(login) << " messenge(s)." << endl;
			}	

			else {
				cout << "Try again" << endl; 
			}
		return true;
		}

		case '2': {					// регистрация пользователя
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

		case '0': {					// выход из программы
			chatRun = false;
			_curentName = " ";
			return false;
		}
		default: {
			cout << "wrong command." << endl;	// не правильно введено значение
		}				
				 return true;
		}
	}

	// меню чата ( после входа в профиль)
bool Menu:: chat() {
	char operation;
	cout << "1 - read, 2 - send, 3 - send to all, 4 - delete messages, other - exit" << endl;
	cin >> operation;

	switch (operation)
	{
	case '1': {														// прочитать сообщения
		cout << "read message" << endl;

		for (multimap<string, string >::iterator it = messages.begin(); it != messages.end(); ++it)
		{
			if (it->first == _curentName)
				cout << it->second << endl;
		}

		return true;													// остаемся в меню чата
	}
	case '2': {															// отправить сообщение адресату
		cout << " Send to: ";
		string nameTo;
		cin >> nameTo;

		if (!changeLogin(nameTo)) {						// проверка адресата на наличие
			cout << " Recipient not found." << endl;
			break;
		}

		cout << "text: ";// << endl;

		string text;
		cin >> text;
		/*vector<string> vec;
		while ((getline(cin, text, ';')) && vec.size() < 4) vec.push_back(text);*/

		messages.emplace(nameTo, text);
			// добавляем сообщение 

		return true;													// остаемся в меню чата
		}
		case '3': {														// сообщение всем пользователям
			cout << "text:";// << endl;
			string text;
			cin >> text;
		
			for (unordered_map < string, string >::iterator it = mapUsers.begin(); it != mapUsers.end(); ++it) {
				if (it->first == _curentName) continue;
				messages.emplace(it->first, text);
			}

		}
		 return true;

		case '4': {												// удаляем все сообщения пользователя

			for (multimap < string, string >::iterator it = messages.begin(); it != messages.end();) {
				if (it->first == _curentName) {
					it = messages.erase(it);
					continue;
				}
				++it;
			}

			return true;											// остаемся в меню чата

		}
		default:
			chatRun = false;
			return false;											// покидаем чат
	}
}

