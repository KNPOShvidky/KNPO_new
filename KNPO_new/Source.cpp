#include <iostream>
#include <string>
#include <fstream>
#include "Header.h"

using namespace std;

int main() {
	//������� ����
	setlocale(LC_ALL, "rus");

	// ������� fin ��� ��������� ������
	ifstream fin;

	//���������� ����� ����������, ����� ���������� ������ �������� �����
	fin.exceptions(istream::badbit | ifstream::failbit);

	//��� ����� ��������� ������
	vector<string> arrayStrings;

	//�������� ����� � �������� �������
	string nameFileInput = "inpt.txt";

	try
	{
		//��������� �����
		fin.open(nameFileInput);
	}
	catch (const exception& ex)
	{
		//��������� ��� ������
		cout << ex.what()<< endl;

		//���� �������� ���������� �����
		if (nameFileInput.find(".txt") == string::npos)
		{
			cout << "������� ������� ���������� �����. ���� ������ ����� ���������� .txt" << endl;
			exit(1);
		}

		//���� ������ � �������� �����
		cout << "������� ������ ���� � �������� �������. ��������, ���� �� ����������" << endl;
		exit(1);
	}

	//��������� ��������� ���� ����������
	fin.exceptions(ifstream::goodbit);

	//������ ������� 
	int sizeOfVect = 1;

	//����� ����� ����� ����, ����� � ����� ��������� ����� �����
	int numbOfStrings = 0;

	//���� �� ����� ����, �� ����� ����� ���������� �� ������ ������
	int moveToNextString = 0;

	//���� ����� ����� 0,  �� ����� ����� ���������� �� ������ ������
	int activePointForCycle = 0;

	//���� ������ � ����� ��� ����
	while (!fin.eof())
	{
		//
		if (moveToNextString != 0 && activePointForCycle == 0)
		{
			//������������� ����� �����
			numbOfStrings++;

			//�������� ������������� ������ �������
			sizeOfVect++;
		}

		//���������� ������ ������� �� 1
		arrayStrings.resize(sizeOfVect);

		//����������� ������ �� �����
		//��������� ���������� ��� ���������� ������ ������
		getline(fin, arrayStrings[numbOfStrings]);

		//�������� �� ������������ ����� (�� ������ ������)
		if (arrayStrings[numbOfStrings] == "")
		{
			//������ ������ ���� 1, ����� ��� ������ �� ��������� ��������
			activePointForCycle++;

			//���� �� ����� ��������
			continue;
		}

		//���� �������� ������ ���� (2 ������� ������ ��������, ������ ����� ��������)
		/*if (arrayStrings[numbOfStrings].size() < 3)
		{
			cout << "���������� �������� ������ ������������!" << endl;
			exit(4);
		}*/

		//������ ����� �� ������ 255 ��������
		if (arrayStrings[numbOfStrings].size() > 255)
		{
			cout << "������� ����� �������� � ������! \n������������ ����� �������� � ������ - 255! " << endl;
			exit(5);
		}

		//���� ��� ������������� ��������, ��������� �� ������ ������
		moveToNextString++;

		//���� ������ ���������� ���������, �� �������� ����������, ����� ������� �� ��������� ������
		if (activePointForCycle != 0)
			activePointForCycle = 0;
	}

	//������������ ����� ����� - 100
	if (sizeOfVect > 100)
	{
		cout << "������� ����� �����! \n������������ ����� ����� - 100! " << endl;
		exit(6);
	}


	//���� ���� ������, �� ��������� �������� � �������
	if (sizeOfVect == 1 && arrayStrings[0] == "")
	{

		cout << "���� ����!" << endl;
		exit(3);
	}

	//������� ��� ������ ������
	if (arrayStrings[numbOfStrings] == "")
	{
		arrayStrings.resize(sizeOfVect - 1);
		sizeOfVect--;
		numbOfStrings--;
	}
	

	
	//������� ��� ���������� ����� �� ������� � ������
	
	vector<string> poh = divideIntoClasses(arrayStrings);

	//���������� ������ ofstream ��� ������ ������ � ���� 
	ofstream fout;

	//��������� ����� ������
	string nameFileOutput = "output.txt";
	try
	{
		//��������� �����
		fout.open(nameFileOutput);
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
		if (nameFileOutput.find(".txt") == string::npos)
		{
			cout << "������� ������� ���������� �����. ���� ������ ����� ���������� .txt" << endl;
			exit(1);
		}
		cout << "������ �������� �����!" << endl;
		exit(1);
	}

	fout.clear();

	//���������� ���������� ���������� � ����.
	for (int i = 0; i < sizeOfVect; i++)
	{
		fout << arrayStrings[i] << "\n";
	}

	fin.close();
	fout.close();

}


vector<string> divideIntoClasses(vector<string>& arrayStrings)
{
	//��������� ������ � �������
	//������ ������
	vector<string> rules;

	//������ ������
	vector<string> data;

	//�������, ����������� ������ � ������
	razelenieDannyx(arrayStrings, rules, data);

	//�������� ������������
	vector<string> result;
	for (int i = 0; i < rules.size(); i++)
	{
		if (rules[i].find("HasProp"))
		{
			result.resize(i + 1);
			result[i] = hasProp(rules[i], data);
			continue;
		}
		if (rules[i].find("HasAmount"))
		{
			result.resize(i + 1);
			result[i] = hasAmount(rules[i], data);
			continue;
		}
		if (rules[i].find("HasOne"))
		{
			result.resize(i + 1);
			result[i] = hasOne(rules[i], data);
			continue;
		}
		if (rules[i].find("HasAll"))
		{
			result.resize(i + 1);
			result[i] = hasAll(rules[i], data);
			continue;
		}
	}
}
//

void razelenieDannyx(vector<string>& arrayStrings, vector<string>& rules, vector<string>& data) {
	
	int i = 1;
	while (arrayStrings[i] != "������:") {
		rules.resize(i + 1);
		rules[i] = arrayStrings[i];
		i++;
	}


	int sizeArray = arrayStrings.size();

	int k = 0;
	for (int j = i+1; i < sizeArray; j++, k++)
	{
		data.resize(k + 1);
		data[k] = arrayStrings[j];
	}
	
}
//����� HasProp
/*
��� �� ��������� ��� ������ ������ � �������, ���� �� � ��� ������ �����
���� ��������� ������ ������ �� ������������

*/

string hasProp(string rules, vector<string>& data)
{

}

string hasAmount(string rules, vector<string>& data)
{

}

string hasOne(string rules, vector<string>& data)
{

}

string hasAll(string rules, vector<string>& data)
{

}