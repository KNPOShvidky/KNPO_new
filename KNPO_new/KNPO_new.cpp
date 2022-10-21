﻿#include <iostream>
#include <string>
#include <fstream>
#include "Header.h"

using namespace std;

int main() {
	//русский язык
	setlocale(LC_ALL, "rus");

	// Создаем fin для потоковых данных
	ifstream fin;

	//Установить маску исключений, чтобы выводилась ошибка открытия файла
	fin.exceptions(istream::badbit | ifstream::failbit);

	//Тут будут храниться строки
	vector<string> arrayStrings;

	//Название файла с входными данными
	string nameFileInput = "input.txt";

	try
	{
		//Открываем файел
		fin.open(nameFileInput);
	}
	catch (const exception& ex)
	{
		//Выводится тип ошибки
		cout << ex.what() << endl;

		//Если неверное расширение файла
		if (nameFileInput.find(".txt") == string::npos)
		{
			cout << "Неверно указано расширение файла. Файл должен иметь расширение .txt" << endl;
			exit(1);
		}

		//Если ошибка в названии файла
		cout << "Неверно указан файл с входными данными. Возможно, файл не существует" << endl;
		exit(1);
	}

	//Отключаем генерацию всех исключений
	fin.exceptions(ifstream::goodbit);

	//Размер вектора 
	int sizeOfVect = 1;

	//Число строк равно нулю, потом в цикле получится явное число
	int numbOfStrings = 0;

	//Если не равна нулю, то можно будет переходить на другую строку
	int moveToNextString = 0;

	//Если точка равна 0,  то можно будет переходить на другую строку
	int activePointForCycle = 0;

	//Если строки в файле еще есть
	while (!fin.eof())
	{
		//
		if (moveToNextString != 0 && activePointForCycle == 0)
		{
			//Увеличивается число строк
			numbOfStrings++;

			//Отдельно увеличивается размер вектора
			sizeOfVect++;
		}

		//Изменяется размер вектора до 1
		arrayStrings.resize(sizeOfVect);

		//Извлекается строка из файла
		//Возникает исключение при считывании пустой строки
		getline(fin, arrayStrings[numbOfStrings]);

		//Проверка на корректность строк (не пустая строка)
		if (arrayStrings[numbOfStrings] == "")
		{
			//Делаем данный флаг 1, чтобы при заходе на следующую итерацию
			activePointForCycle++;

			//Идем на новую итерацию
			continue;
		}

		//Если символов меньше трех (2 символа должны остаться, третий потом удалится)
		/*if (arrayStrings[numbOfStrings].size() < 3)
		{
			cout << "Количество символов меньше минимального!" << endl;
			exit(4);
		}*/

		//Размер строк не больше 255 символов
		if (arrayStrings[numbOfStrings].size() > 255)
		{
			cout << "Слишком много символов в строке! \nМаксимальное число символов в строке - 255! " << endl;
			exit(5);
		}

		//Если все соответствует условиям, переходим на другую строку
		moveToNextString++;

		//Если строка извлеклась корректно, то обнуляем переменную, чтобы перейти на следующую строку
		if (activePointForCycle != 0)
			activePointForCycle = 0;
	}

	//Максимальное число строк - 100
	if (sizeOfVect > 100)
	{
		cout << "Слишком много строк! \nМаксимальное число строк - 100! " << endl;
		exit(6);
	}


	//Если файл пустой, то программа вылетает с ошибкой
	if (sizeOfVect == 1 && arrayStrings[0] == "")
	{

		cout << "Файл пуст!" << endl;
		exit(3);
	}

	//Удалить все пустые строки
	if (arrayStrings[numbOfStrings] == "")
	{
		arrayStrings.resize(sizeOfVect - 1);
		sizeOfVect--;
		numbOfStrings--;
	}



	//Функция для разделения файла на правила и данные

	vector<string> result = divideIntoClasses(arrayStrings);

	//Вызывается объект ofstream для записи данных в файл 
	ofstream fout;

	//Названиев файла вывода
	string nameFileOutput = "output.txt";
	try
	{
		//Открываем файел
		fout.open(nameFileOutput);
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
		if (nameFileOutput.find(".txt") == string::npos)
		{
			cout << "Неверно указано расширение файла. Файл должен иметь расширение .txt" << endl;
			exit(1);
		}
		cout << "Ошибка открытия файла!" << endl;
		exit(1);
	}

	fout.clear();

	//Отправляем полученные результаты в файл.
	for (int i = 0; i < result.size(); i++)
	{
		fout << result[i] << "\n";
	}

	fin.close();
	fout.close();

}


vector<string> divideIntoClasses(vector<string>& arrayStrings)
{
	//Разделить данные и правила
	//Строки правил
	vector<string> rules;

	//Строки данных
	vector<string> data;

	//Функция, разделяющая строки и данные
	razelenieDannyx(arrayStrings, rules, data);

	//Итоговый резултататат
	vector<string> result;
	for (int i = 0; i < rules.size(); i++)
	{
		//cout << "\nHAS_PROP V " << i << " STROKE = "<< rules[i].find("HasProp") << endl << endl;


		if (rules[i].find("HasProp") != string::npos)
		{
			result.resize(i + 1);
			result[i] = hasProp(rules[i], data);
			continue;
		}

		if (rules[i].find("HasAmount") != string::npos)
		{
			result.resize(i + 1);
			result[i] = hasAmount(rules[i], data);
			continue;
		}

		if (rules[i].find("HasOne") != string::npos)
		{
			result.resize(i + 1);
			result[i] = hasOne(rules[i], data);
			continue;
		}

		if (rules[i].find("HasAll") != string::npos)
		{
			result.resize(i + 1);
			result[i] = hasAll(rules[i], data);
			continue;
		}

	}

	for (int k = 0; k < result.size(); k++) {
		cout << "Result: " << result[k] << endl;
	}

	return result;
}

void razelenieDannyx(vector<string>& arrayStrings, vector<string>& rules, vector<string>& data) {

	int i = 0;
	while (arrayStrings[i + 1] != "Данные:") {
		rules.resize(i + 1);
		rules[i] = arrayStrings[i + 1];
		i++;
	}


	int sizeArray = arrayStrings.size();

	int k = 0;
	for (int j = i + 2; j < sizeArray; j++)
	{
		data.resize(k + 1);
		data[k] = arrayStrings[j];
		k++;
	}

	bool bool_correct;
	for (int i = 0; i < data.size(); i++) {

		bool_correct = correctData(data[i], i);

		if (!bool_correct)
			exit(1);

	}
	for (int i = 0; i < rules.size(); i++) {

		correctRules(rules[i], i);

	}

}

string hasProp(string rules, vector<string>& data)
{

	//Индекс вхождения слова HasProp в rules
	int x = rules.find("HasProp");

	//Индекс начала вхождения названия свойства в rules
	x += size("HasProp");

	int rul_size = rules.size() - x;
	//Строка, содержащая название свойства

	string Nalichie = rules.substr(x, rul_size);

	//Индекс вхождения первой запятой в rules
	int g = rules.find(",");
	//cout << "Nalichie= " << Nalichie << endl;

	//Строка, содержащая название класса
	string Klass = rules.substr(0, g);
	int index = data[0].rfind("]");
	int kol = data[0].size();

	//Задаём результат
	string res = "\"" + Klass + "\": ";

	int kol_vo_el = 0;


	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(Nalichie) != string::npos)
		{

			int gov = data[i].find(":");

			string nameEl = data[i].substr(0, gov);

			if (kol_vo_el == 0) {
				res += nameEl;
			}
			if (kol_vo_el != 0) {
				res += ", " + nameEl;
			}
			kol_vo_el++;
		}

	}
	if (kol_vo_el == 0) {
		res += " - ";
	}

	// cout << res << endl;
	return res;
}

string hasAmount(string rules, vector<string>& data)
{
	//Индекс вхождения слова HasAmount в rules
	int x = rules.find("HasAmount");

	int indexColZn = rules.rfind(",");

	//Индекс начала вхождения названия свойства в rules
	x += size("HasAmount");




	//int rul_size = indexColZn - x;
	//Строка, содержащая название свойства
	int c = rules.size() - indexColZn;
	int y = rules.size() - c;
	y -= x;
	string Nalichie = rules.substr(x, y);


	//Индекс вхождения первой запятой в rules
	int g = rules.find(",");
	//cout << "Nalichie= " << Nalichie << endl;

	//Строка, содержащая название класса
	string Klass = rules.substr(0, g);

	//Задаём результат
	string res = "\"" + Klass + "\": ";

	int kol_vo_el = 0;


	//Выяснить количество значений в правиле

	string ColZn_str = rules.substr((indexColZn + 1), rules.size());
	int ColZn_int = stoi(ColZn_str);
	//int count = .count();


	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(Nalichie) != string::npos)
		{
			int indexZnach = data[i].find(Nalichie) + Nalichie.size() + 1;

			int col_zap = 0;
			for (int t = indexZnach; data[i][t] != ']'; t++) {
				if (data[i][t] == ',')
					col_zap++;
			}

			if (col_zap >= ColZn_int - 1) {

				int gov = data[i].find(":");
				string nameEl = data[i].substr(0, gov);

				if (kol_vo_el == 0) {
					res += nameEl;
				}
				if (kol_vo_el != 0) {
					res += ", " + nameEl;
				}
				kol_vo_el++;
			}
		}

	}
	if (kol_vo_el == 0) {
		res += " - ";
	}

	// cout << res << endl;
	return res;
}

string hasOne(string rules, vector<string>& data)
{
	//Индекс вхождения слова HasAmount в rules
	int x = rules.find("HasOne");

	int indexColZn = rules.rfind(",");

	//Индекс начала вхождения названия свойства в rules
	x += size("HasOne");




	//int rul_size = indexColZn - x;
	//Строка, содержащая название свойства
	int c = rules.size() - indexColZn;
	int y = rules.size() - c;
	y -= x;
	string Nalichie = rules.substr(x, y);

	//Индекс вхождения первой запятой в rules
	int g = rules.find(",");
	//cout << "Nalichie= " << Nalichie << endl;

	//Строка, содержащая название класса
	string Klass = rules.substr(0, g);

	//Задаём результат
	string res = "\"" + Klass + "\": ";

	int kol_vo_el = 0;


	//Выяснить количество значений в правиле

	string Zn_str = rules.substr((indexColZn + 1), rules.size());

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(Nalichie) != string::npos)
		{
			//Индекс начала значений
			int indexZnach = data[i].find(Nalichie) + Nalichie.size() + 1;


			bool zap = false;
			int PravScob = 0;   // Иниц 

			//Ищем конец значений
			for (int t = indexZnach; data[i][t] != ']'; t++) {
				PravScob = t;
			}
			PravScob++;
			//cout << "Скобка Индекс = " << PravScob << endl;
			//cout << "Длина строки = " << data[i].size() << endl;
			string copy = data[i].substr(indexZnach + 1, PravScob - indexZnach - 1);
			string copy_zn;

			int u = 0;
			while (u < copy.size()) {
				if (copy[u] == ',') {
					if (copy_zn == Zn_str) {
						zap = true;
					}
					copy_zn = "";
					u++;
				}
				copy_zn += copy[u];

				u++;
			}

			if (zap == true) {

				int gov = data[i].find(":");
				string nameEl = data[i].substr(0, gov);

				if (kol_vo_el == 0) {
					res += nameEl;
				}
				if (kol_vo_el != 0) {
					res += ", " + nameEl;
				}
				kol_vo_el++;
			}
		}

	}
	if (kol_vo_el == 0) {
		res += " - ";
	}

	//cout << res << endl;
	return res;
}

string hasAll(string rules, vector<string>& data)
{
	//Индекс вхождения слова HasAll в rules
	int x = rules.find("HasAll");
	int indexColZn_left = rules.find("[");
	int indexColZn_right = rules.find("]");


	//Индекс начала вхождения названия свойства в rules
	x += size("HasAll");


	//int rul_size = indexColZn - x;
	//Строка, содержащая название свойства

	string Nalichie = rules.substr(x, indexColZn_left - x - 1);

	//Индекс вхождения первой запятой в rules
	int g = rules.find(",");


	//Строка, содержащая название класса
	string Klass = rules.substr(0, g);

	//Задаём результат
	string res = "\"" + Klass + "\": ";

	int kol_vo_el = 0;


	//Выяснить значения в правиле

	string Zn_str = rules.substr((indexColZn_left + 1), (indexColZn_right - indexColZn_left - 1));
	vector<string> znach;
	int p = 0;
	string promej;
	int y = 0;
	cout << "Zn_str = " << Zn_str << endl;

	for (int i = 0; i <= Zn_str.size(); i++) {

		if (Zn_str[i] == ',' || i == Zn_str.size())
		{
			p++;
			znach.resize(p);
			znach[y] = promej;
			y++;

			promej = "";
			continue;
		}

		promej += Zn_str[i];
	}

	for (int i = 0; i < znach.size(); i++) {
		cout << i << "-й = " << znach[i] << endl;
	}

	//Ищем соответствия с данными
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(Nalichie) != string::npos)
		{
			//Индекс начала значений
			int indexZnach = data[i].find(Nalichie) + Nalichie.size() + 2;


			bool zap = false;
			int PravScob = 0;

			//Ищем конец значений
			for (int t = indexZnach; data[i][t] != ']'; t++) {
				PravScob = t;
			}

			string copy = data[i].substr(indexZnach, PravScob - indexZnach + 1);
			string copy_zn;

			bool soderjit = true;
			for (int i = 0; i < znach.size(); i++) {

				if (copy.find(znach[i]) == string::npos) {
					soderjit = false;
				}
			}

			if (soderjit) {

				int gov = data[i].find(":");
				string nameEl = data[i].substr(0, gov);

				if (kol_vo_el == 0) {
					res += nameEl;
				}
				if (kol_vo_el != 0) {
					res += ", " + nameEl;
				}
				kol_vo_el++;
			}
		}

	}
	if (kol_vo_el == 0) {
		res += " - ";
	}

	//cout << res << endl;
	return res;
}

//Функция проверки корректности Правил
bool correctRules(string str, int num) {
	//Количество запятых в строке
	int col_zap = 0;

	//Если в строке есть пробелы
	if (str.find(" ") != string::npos)
	{
		cout << "Лишние пробелы в правиле #" << num + 1 << endl;
		return false;
	}
	//Если в строке есть HasProp
	if (str.find("HasProp") != string::npos) {
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == ',')
			{
				if (isalnumRus(str[i + 1]) == 0 || isalnumRus(str[i - 1]) == 0)
				{
					cout << "Недопустимая запись запятой в правиле #" << num + 1 << endl;
					return false;
				}
				col_zap++;
			}
			//Если в правиле есть недопустимые символы

			if (isalnumRus(str[i]) == 0 && str[i] != ',') {
				cout << "Недопустимые символы в правиле #" << num + 1 << endl;
				return false;
			}
		}
		if (col_zap != 2) {
			cout << "Недостаточное количество аргументов в правиле #" << num + 1 << endl;
			return false;
		}
		else {
			return true;
		}

	}
	//Если в строке есть HasAmount
	else if (str.find("HasAmount") != string::npos) {
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == ',') {
				if (isalnumRus(str[i + 1]) == 0 || isalnumRus(str[i - 1]) == 0)
				{
					cout << "Недопустимая запись запятой в правиле #" << num + 1 << endl;
					return false;
				}
				col_zap++;
			}
			//Если в правиле есть недопустимые символы
			if (isalnumRus(str[i]) == 0 && str[i] != ',') {

				cout << "Недопустимые символы в правиле #" << num + 1 << endl;
				return false;
			}
		}
		if (col_zap != 3) {
			cout << "Недостаточное количество аргументов в правиле #" << num + 1 << endl;
			return false;
		}
		else {
			return true;
		}
	}
	//Если в строке есть HasOne
	else if (str.find("HasOne") != string::npos) {

		for (int i = 0; i < str.size(); i++) {
			if (str[i] == ',') {
				if (isalnumRus(str[i + 1]) == 0 || isalnumRus(str[i - 1]) == 0)
				{
					cout << "Недопустимая запись запятой в правиле #" << num + 1 << endl;
					return false;
				}
				col_zap++;
			}
			//Если в правиле есть недопустимые символы
			if (isalnumRus(str[i]) == 0 && str[i] != ',') {
				cout << "Недопустимые символы в правиле #" << num + 1 << endl;
				return false;
			}
		}
		if (col_zap != 3) {
			cout << "Недостаточное количество аргументов в правиле #" << num + 1 << endl;
			return false;
		}
		else {
			return true;
		}
	}
	//Если в строке есть правило HasAll
	else if (str.find("HasAll") != string::npos) {
		//Индекс вождения левой скобки
		int index_left;
		//Индекс вождения правой скобки
		int index_right;

		//Если в строке нет скобок
		if (str.find("[") == string::npos || str.find("]") == string::npos) {
			cout << "Неправильно введены скобки для значений для главного правила HasAll в правиле #" << num + 1 << endl;
			return false;
		}

		for (int i = 0; i < str.size(); i++) {
			//Если в правиле есть недопустимые символы
			if (isalnumRus(str[i]) == 0 && str[i] != ',' && str[i] != '[' && str[i] != ']') {
				cout << "Недопустимые символы в правиле #" << num + 1 << endl;
				return false;
			}

			if (str[i] == ',')
			{
				if ((isalnumRus(str[i + 1]) == 0 && isalnumRus(str[i - 1]) == 0) || (isalnumRus(str[i - 1]) == 0 && str[i + 1] != ']'))
				{
					cout << "Недопустимая запись запятой в правиле #" << num + 1 << endl;
					return false;
				}
			}
			else if (str[i] == '[') {
				if (str[i - 1] != ',') {
					cout << "Неправильно введены скобки для значений для главного правила HasAll в правиле #" << num + 1 << endl;
				}
				else if (isalnumRus(str[i + 1]) == 0) {
					cout << "Неправильно введены значения для главного правила HasAll в правиле #" << num + 1 << endl;
				}
				else {
					return true;
				}
			}

			else if (str[i] == ']') {
				if (isalnumRus(str[i - 1]) == 0) {
					cout << "Неправильно введены значения для главного правила HasAll в правиле #" << num + 1 << endl;
				}
				else if (i + 1 != str.size()) {
					cout << "Неправильно введены значения для главного правила HasAll в правиле #" << num + 1 << endl;
				}
				else {
					return true;
				}
			}
		}

	}
	//Если в строке правила нет правил
	else {
		cout << "Не указано главное правило правило в строке #" << num + 1 << endl;
		return false;
	}

}

//Функция корректности Данных
bool correctData(string str, int num) {


	//"Грубая" проверка корректности(наличия нужных символов)	
	if (str.find("=") == string::npos) { //В строке данных нет равно

		cout << "В строке данных нет равно";
		return false;
	}
	else if (str.find(":") == string::npos) { //В строке данных нет двоеточия

		cout << "В строке данных нет двоеточия";
		return false;
	}
	else if (str.find("[") == string::npos || str.find("]") == string::npos) { //В строке данных нет квадратных скобок

		cout << "В строке данных нет квадратных скобок";
		return false;
	}
	else if (str.find("=") < str.find(":")) {//В строке данных двоеточие правее знака равно

		cout << "В строке данных двоеточие правее знака равно";
		return false;
	}
	else if (str.find(" ") != string::npos) {

		cout << "В строке данных #" << num + 1 << " присутствуют лишние пробелы";
		return false;
	}


	int col_vo_ravno = 0;
	int col_vo_left = 0;
	int col_vo_right = 0;

	//Посимвольная проверка на корректность
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '=') {
			col_vo_ravno++;
		}

		if (str[i] == '[') {
			col_vo_left++;
		}

		if (str[i] == ']') {
			col_vo_right++;
		}

		if (isalnumRus(str[i]) == false)	//Если символ не буква и не цифра
		{
			if (str[i] == ':') {	//Если символ двоеточие
				if (isalnumRus(str[i - 1]) == false || isalnumRus(str[i + 1]) == false) {

					cout << "Двоеточние указано не по правилам";
					return false;

				}

			}
			else if (str[i] == '=') {	//Если символ равно
				if (isalnumRus(str[i - 1]) == false || str[i + 1] != '[') {

					cout << "Равно указано не по правилам";
					return false;

				}
			}
			else if (str[i] == '[') {	//Если символ левая скобка
				if (str[i - 1] != '=') {

					cout << "В строке данных #" << num + 1 << " отсутствует равно";	//Если нет равно перед скобкой
					return false;
				}
				else if (isalnumRus(str[i + 1]) == false) {	//если внутри скобки нет значений

					cout << "В строке данных #" << num + 1 << " отсутствует значение";
					return false;
				}
			}
			else if (str[i] == ']') {	//Если символ правая скобка
				if (i + 1 == str.size()) {	//Если Правая скобка - последняя в строке
					if (isalnumRus(str[i - 1]) == false) {

						cout << "В строке данных #" << num + 1 << " отсутствует значение";
						return false;
					}
				}
				else if (isalnumRus(str[i - 1]) == false) {	//Если 	

					cout << "В строке данных #" << num + 1 << " отсутствует значение";
					return false;

				}
				else if (str[i + 1] != ',') {	//Если нет запятой между свойствами

					cout << "В строке данных #" << num + 1 << " отсутствует запятая";
					return false;
				}
			}
			else if (str[i] == ',') {	//Если символ запятая
				if (isalnumRus(str[i - 1]) == false && isalnumRus(str[i + 1]) == false) {	//Запятая в значениях

					cout << "В строке данных #" << num + 1 << " отсутствует значение";
					return false;

				}
				else if (isalnumRus(str[i + 1]) == false && str[i - 1] != ']') {	//Запятая между свойств

					cout << "В строке данных #" << num + 1 << " найдена ошибка значений";
					return false;
				}
			}
		}
		else if (isalnumRus(str[i])) {

		}
		else {	//Недопустимый символ

			cout << "В данных есть недопустимых символ";
			return false;
		}

	}
	if (col_vo_left != col_vo_ravno || col_vo_right != col_vo_ravno) {

		cout << "Некорректные введённые данные";
		return false;
	}
	return true;

}


int isalnumRus(const char  sym)
{
	return ((sym >= 'А') && (sym <= 'Я') ||
		(sym >= 'а') && (sym <= 'я') || (sym >= 'A') && (sym <= 'Z') || (sym >= 'a') && (sym <= 'z') ||
		(sym >= '0') && (sym <= '9'));
}