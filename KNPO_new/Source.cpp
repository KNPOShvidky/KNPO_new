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
	string nameFileInput = "input.txt";
	
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
	while (arrayStrings[i+1] != "������:") {
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
//����� HasProp
/*
��� �� ��������� ��� ������ ������ � �������, ���� �� � ��� ������ �����
���� ��������� ������ ������ �� ������������

*/

string hasProp(string rules, vector<string>& data)
{
	cout << "Rules= " << rules<<endl<<endl;
	//������ ��������� ����� HasProp � rules
	int x = rules.find("HasProp");

	//������ ������ ��������� �������� �������� � rules
	x += size("HasProp");
	
	int rul_size = rules.size()-x;
	//������, ���������� �������� ��������

	string Nalichie = rules.substr(x,rul_size);

	//������ ��������� ������ ������� � rules
	int g = rules.find(",");
	cout << "Nalichie= " << Nalichie << endl;

	//������, ���������� �������� ������
	string Klass = rules.substr(0, g);

	//����� ���������
	string res = "\""+Klass + "\": ";

	int kol_vo_el = 0;

	for (int d = 0; d < data.size(); d++) {
		cout << d << "-� ������ = " << data[d] << endl;
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