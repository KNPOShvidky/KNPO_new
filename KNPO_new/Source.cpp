#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main() {
	//������� ����
	setlocale(LC_ALL, "rus");

	// ������� fin ��� ��������� ������
	std::ifstream fin;

	//���������� ����� ����������, ����� ���������� ������ �������� �����
	fin.exceptions(std::istream::badbit | std::ifstream::failbit);

	//��� ����� ��������� ������
	std::vector<std::string> arrayStrings;

	//�������� ����� � �������� �������
	std::string nameFileInput = "inpt.txt";

	try
	{
		//��������� �����
		fin.open(nameFileInput);
	}
	catch (const std::exception& ex)
	{
		//��������� ��� ������
		std::cout << ex.what()<< std::endl;

		//���� �������� ���������� �����
		if (nameFileInput.find(".txt") == std::string::npos)
		{
			std::cout << "������� ������� ���������� �����. ���� ������ ����� ���������� .txt" << std::endl;
			exit(1);
		}

		//���� ������ � �������� �����
		std::cout << "������� ������ ���� � �������� �������. ��������, ���� �� ����������" << std::endl;
		exit(1);
	}

	//��������� ��������� ���� ����������
	fin.exceptions(std::ifstream::goodbit);



}
