#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main() {
	//русский язык
	setlocale(LC_ALL, "rus");

	// Создаем fin для потоковых данных
	std::ifstream fin;

	//Установить маску исключений, чтобы выводилась ошибка открытия файла
	fin.exceptions(std::istream::badbit | std::ifstream::failbit);

	//Тут будут храниться строки
	std::vector<std::string> arrayStrings;

	//Название файла с входными данными
	std::string nameFileInput = "inpt.txt";

	try
	{
		//Открываем файел
		fin.open(nameFileInput);
	}
	catch (const std::exception& ex)
	{
		//Выводится тип ошибки
		std::cout << ex.what()<< std::endl;

		//Если неверное расширение файла
		if (nameFileInput.find(".txt") == std::string::npos)
		{
			std::cout << "Неверно указано расширение файла. Файл должен иметь расширение .txt" << std::endl;
			exit(1);
		}

		//Если ошибка в названии файла
		std::cout << "Неверно указан файл с входными данными. Возможно, файл не существует" << std::endl;
		exit(1);
	}

	//Отключаем генерацию всех исключений
	fin.exceptions(std::ifstream::goodbit);



}
