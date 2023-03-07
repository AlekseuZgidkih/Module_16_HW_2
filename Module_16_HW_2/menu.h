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
	Menu() = default;							// конструктор
	~Menu() = default;							// деструктор

	string _curentName;
	bool chatRun = false;						// дл€ проверки промежуточной версии проги

	// подсчет вход€щих сообщений
	int findMessage(string& login);
	// ѕоиск логина в базе
	bool changeLogin(string& login);

	// сохранение логина парол€
	void saveLogPass(string& login, string& password);

	// меню стартовое
	bool main_menu();
	// меню чата ( после входа в профиль)
	bool chat();
};

