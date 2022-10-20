#include <iostream>
#include <string>
#include <fstream>
#include "Header.h"
#include <Windows.h>
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
		//cout << "\nHAS_PROP V " << i << " STROKE = "<< rules[i].find("HasProp") << endl << endl;


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

	for (int k = 0; k < result.size(); k++) {
		cout << "Result: " << result[k] << endl;
	}

	return result;
}

void razelenieDannyx(vector<string>& arrayStrings, vector<string>& rules, vector<string>& data) {
	
	int i = 0;
	while (arrayStrings[i + 1] != "������:") {
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

	for (int i = 0; i < data.size(); i++) {
		
		correctData(data[i],i);
	}
	
}

string hasProp(string rules, vector<string>& data)
{
	
	//������ ��������� ����� HasProp � rules
	int x = rules.find("HasProp");

	//������ ������ ��������� �������� �������� � rules
	x += size("HasProp");
	
	int rul_size = rules.size()-x;
	//������, ���������� �������� ��������

	string Nalichie = rules.substr(x,rul_size);

	//������ ��������� ������ ������� � rules
	int g = rules.find(",");
	//cout << "Nalichie= " << Nalichie << endl;

	//������, ���������� �������� ������
	string Klass = rules.substr(0, g);
	int index = data[0].rfind("]");
	int kol = data[0].size();

	//����� ���������
	string res = "\""+Klass + "\": ";

	int kol_vo_el = 0;


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
	if (kol_vo_el == 0) {
		res += " - ";
	}

	// cout << res << endl;
	return res;
}

string hasAmount(string rules, vector<string>& data)
{
	//������ ��������� ����� HasAmount � rules
	int x = rules.find("HasAmount");

	int indexColZn = rules.rfind(",");
	
	//������ ������ ��������� �������� �������� � rules
	x += size("HasAmount");
	

	

	//int rul_size = indexColZn - x;
	//������, ���������� �������� ��������
	int c = rules.size()-indexColZn;
	int y = rules.size()-c;
	y -= x;
	string Nalichie = rules.substr(x, y);

	
	//������ ��������� ������ ������� � rules
	int g = rules.find(",");
	//cout << "Nalichie= " << Nalichie << endl;

	//������, ���������� �������� ������
	string Klass = rules.substr(0, g);

	//����� ���������
	string res = "\"" + Klass + "\": ";

	int kol_vo_el = 0;


	//�������� ���������� �������� � �������
	
	string ColZn_str = rules.substr((indexColZn+1),rules.size());
	int ColZn_int = stoi(ColZn_str);
	//int count = .count();
	

	for (int i = 0; i < data.size(); i++)
	{	
		if (data[i].find(Nalichie) != string::npos)
		{
			int indexZnach = data[i].find(Nalichie) + Nalichie.size()+1;
			
			int col_zap = 0;
			for (int t = indexZnach; data[i][t] != ']'; t++) {
				if (data[i][t] == ',')
					col_zap++;
			}

			if (col_zap == ColZn_int-1) {

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
	//������ ��������� ����� HasAmount � rules
	int x = rules.find("HasOne");

	int indexColZn = rules.rfind(",");

	//������ ������ ��������� �������� �������� � rules
	x += size("HasOne");


	

	//int rul_size = indexColZn - x;
	//������, ���������� �������� ��������
	int c = rules.size() - indexColZn;
	int y = rules.size() - c;
	y -= x;
	string Nalichie = rules.substr(x, y);

	//������ ��������� ������ ������� � rules
	int g = rules.find(",");
	//cout << "Nalichie= " << Nalichie << endl;

	//������, ���������� �������� ������
	string Klass = rules.substr(0, g);

	//����� ���������
	string res = "\"" + Klass + "\": ";

	int kol_vo_el = 0;


	//�������� ���������� �������� � �������

	string Zn_str = rules.substr((indexColZn + 1), rules.size());

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(Nalichie) != string::npos)
		{
			//������ ������ ��������
			int indexZnach = data[i].find(Nalichie) + Nalichie.size() + 1;
			

			bool zap = false;
			int PravScob = 0;   // ���� 
			
			//���� ����� ��������
			for (int t = indexZnach; data[i][t]!=']'; t++) {
				PravScob = t;
			}
			PravScob++;
			//cout << "������ ������ = " << PravScob << endl;
			//cout << "����� ������ = " << data[i].size() << endl;
			string copy = data[i].substr(indexZnach+1, PravScob-indexZnach-1);
			string copy_zn;
			
			int u = 0;
			while (u<copy.size()) {
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
			
			if (zap==true) {

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
	//������ ��������� ����� HasAll � rules
	int x = rules.find("HasAll");
	int indexColZn_left = rules.find("[");
	int indexColZn_right = rules.find("]");


	//������ ������ ��������� �������� �������� � rules
	x += size("HasAll");




	//int rul_size = indexColZn - x;
	//������, ���������� �������� ��������
	
	string Nalichie = rules.substr(x, indexColZn_left-x-1);
	
	//������ ��������� ������ ������� � rules
	int g = rules.find(",");


	//������, ���������� �������� ������
	string Klass = rules.substr(0, g);

	//����� ���������
	string res = "\"" + Klass + "\": ";

	int kol_vo_el = 0;


	//�������� �������� � �������
	
	string Zn_str = rules.substr((indexColZn_left+1), (indexColZn_right-indexColZn_left-1));


	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(Nalichie) != string::npos)
		{
			//������ ������ ��������
			int indexZnach = data[i].find(Nalichie) + Nalichie.size() + 2;
			

			bool zap = false;
			int PravScob = 0;

			//���� ����� ��������
			for (int t = indexZnach; data[i][t] != ']'; t++) {
				PravScob = t;
			}
		
			string copy = data[i].substr(indexZnach, PravScob - indexZnach+1 );
			string copy_zn;
		
			

			if (Zn_str==copy) {

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

//������� �������� ������������ ������
bool correctRules(string str,int num) {
	int col_zap = 0;
	if (str.find("HasProp")){
		for (int i; i < str.size(); i++) {
			if (str[i] == ',') {
				col_zap++;
			}
			if (!isalnumRus(str[i]) || str[i] != ',') {
				return false;
			}
		}
		if (col_zap != 2) {
			cout << "������������� ���������� ������� � ������� #" << num;
			return false;
		}
		else {
			return true;
		}

	}
	else if (str.find("HasAmount")) {

	}
	else if (str.find("HasOne")) {

	}
	else if (str.find("HasAll")) {

	}
	else {
		cout << "�� ������� ������� � ������ #" << num;
		return false;
	}

}

//������� ������������ ������
bool correctData(string str, int num) {
	bool res = true;

	//"������" �������� ������������(������� ������ ��������)	
	if (str.find("=") == string::npos) { //� ������ ������ ��� �����
		res = false;
		cout << "� ������ ������ ��� �����";
		exit(1);
	}else if (str.find(":") == string::npos) { //� ������ ������ ��� ���������
		res = false;
		cout << "� ������ ������ ��� ���������";
		exit(2);
	}
	else if (str.find("[") == string::npos || str.find("]") == string::npos) { //� ������ ������ ��� ���������� ������
		res = false;
		cout << "� ������ ������ ��� ���������� ������";
		exit(3);
	}
	else if (str.find("=") < str.find(":")) {//� ������ ������ ��������� ������ ����� �����
		res = false;
		cout << "� ������ ������ ��������� ������ ����� �����";
		exit(4);
	}
	else if (str.find(" ") != string::npos) {
		res = false;
		cout << "� ������ ������ #"<<num+1<<  " ������������ ������ �������";
		exit(10);
	}


	int col_vo_ravno=0;
	int col_vo_left=0;
	int col_vo_right=0;
	
		//������������ �������� �� ������������
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

			if (isalnumRus(str[i]) == false)	//���� ������ �� ����� � �� �����
			{
				if (str[i] == ':') {	//���� ������ ���������
					if (isalnumRus(str[i - 1]) == false || isalnumRus(str[i + 1]) == false) {
						res = false;
						cout << "���������� ������� �� �� ��������";
						exit(5);

					}

				}
				else if (str[i] == '=') {	//���� ������ �����
					if (isalnumRus(str[i - 1]) == false || str[i + 1] != '[') {
						res = false;
						cout << "����� ������� �� �� ��������";
						exit(5);

					}
				}
				else if (str[i] == '[') {	//���� ������ ����� ������
					if (str[i - 1] != '=') {
						res = false;
						cout << "� ������ ������ #"<<num+1<<" ����������� �����";	//���� ��� ����� ����� �������
						exit(5);
					}
					else if (isalnumRus(str[i + 1]) == false) {	//���� ������ ������ ��� ��������
						res = false;
						cout << "� ������ ������ #" << num+1 << " ����������� ��������";
						exit(5);
					}
				}
				else if (str[i] == ']') {	//���� ������ ������ ������
					if (i+1 == str.size() ) {	//���� ������ ������ - ��������� � ������
						if (isalnumRus(str[i - 1]) == false) {
							res = false;
							cout << "� ������ ������ #" << num + 1 << " ����������� ��������";
							exit(6);
						}
					}
					else if (isalnumRus(str[i - 1]) == false){	//���� 	
						res = false;
						cout << "� ������ ������ #" << num + 1 << " ����������� ��������";
						exit(6);

					}
					else if (str[i + 1] != ',') {	//���� ��� ������� ����� ����������
						res = false;
						cout << "� ������ ������ #" << num + 1 << " ����������� �������";
						exit(6);
					}
				}
				else if (str[i] == ',') {	//���� ������ �������
					if (isalnumRus(str[i - 1]) == false && isalnumRus(str[i + 1]) == false) {	//������� � ���������
						res = false;
						cout << "� ������ ������ #" << num + 1 << " ����������� ��������";
						exit(6);

					}
					else if (isalnumRus(str[i + 1]) == false && str[i - 1] != ']') {	//������� ����� �������
						res = false;
						cout << "� ������ ������ #" << num + 1 << " ������� ������ ��������";
						exit(1);
					}
				}
			}
			else if (isalnumRus(str[i])) {

			}
			else {	//������������ ������
					res = false; 
					cout << "� ������ ���� ������������ ������";
					exit(7);
				}
	
		}
		if (col_vo_left != col_vo_ravno || col_vo_right != col_vo_ravno) {
			res = false;
			cout << "������������ �������� ������";
			exit(7);
		}
		return res;
		
}


int isalnumRus(const char  sym)
{
	return ((sym >= '�') && (sym <= '�') ||
		(sym >= '�') && (sym <= '�') || (sym >= 'A') && (sym <= 'Z') || (sym >= 'a') && (sym <= 'z') ||
		(sym >= '0') && (sym <= '9'));
}