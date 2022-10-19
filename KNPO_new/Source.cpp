#include <iostream>
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
		cout << ex.what()<< endl;

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
	
	vector<string> poh = divideIntoClasses(arrayStrings);

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
	for (int i = 0; i < sizeOfVect; i++)
	{
		fout << arrayStrings[i] << "\n";
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
		cout << "\nHAS_PROP V " << i << " STROKE = "<< rules[i].find("HasProp") << endl << endl;


		if (rules[i].find("HasProp")!= string::npos)
		{
			result.resize(i + 1);
			result[i] = hasProp(rules[i], data);
			continue;
		}

		if (rules[i].find("HasAmount")!= string::npos)
		{
			result.resize(i + 1);
			result[i] = hasAmount(rules[i], data);
			continue;
		}

		if (rules[i].find("HasOne")!= string::npos)
		{
			result.resize(i + 1);
			result[i] = hasOne(rules[i], data);
			continue;
		}

		if (rules[i].find("HasAll")!= string::npos)
		{
			result.resize(i + 1);
			result[i] = hasAll(rules[i], data);
			continue;
		}
		
	}

	return result;
}
//

void razelenieDannyx(vector<string>& arrayStrings, vector<string>& rules, vector<string>& data) {
	
	int i =0;
	while (arrayStrings[i+1] != "Данные:") {
		rules.resize(i + 1);
		rules[i] = arrayStrings[i+1];
		i++;
	}
	

	int sizeArray = arrayStrings.size();

	int k = 0;
	for (int j = i+2; j < sizeArray; j++)
	{
		data.resize(k + 1);
		data[k] = arrayStrings[j];
		k++;
	}
	
	
}
//Говно HasProp
/*
Тут он прогоняет все строки Данных и смотрит, есть ли в них нужные слова
Плюс проверяет каждую строку на адекватность

*/

string hasProp(string rules, vector<string>& data)
{
	cout << "Rules= " << rules<<endl<<endl;
	//Индекс вхождения слова HasProp в rules
	int x = rules.find("HasProp");

	//Индекс начала вхождения названия свойства в rules
	x += size("HasProp");
	
	int rul_size = rules.size()-x;
	//Строка, содержащая название свойства

	string Nalichie = rules.substr(x,rul_size);

	//Индекс вхождения первой запятой в rules
	int g = rules.find(",");
	cout << "Nalichie= " << Nalichie << endl;

	//Строка, содержащая название класса
	string Klass = rules.substr(0, g);

	//Задаём результат
	string res = "\""+Klass + "\": ";

	int kol_vo_el = 0;

	for (int d = 0; d < data.size(); d++) {
		cout << d << "-е Данное = " << data[d] << endl;
	}

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(Nalichie)!= string::npos)
		{

			int gov = data[i].find(":");

			string nameEl = data[i].substr(0, gov);

			if (kol_vo_el == 0) {
				res += nameEl;
			}
			if (kol_vo_el!=0) {
				res += ", "+nameEl;
			}
				kol_vo_el++;
		}
		
	}

	cout << res<<endl;
	return Klass;
}

string hasAmount(string rules, vector<string>& data)
{
	return rules;
}

string hasOne(string rules, vector<string>& data)
{
	return rules;
}

string hasAll(string rules, vector<string>& data)
{
	return rules;
}