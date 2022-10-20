#pragma once
#include <vector>

using namespace std;
int isalnumRus(const char  sym);

vector<string> divideIntoClasses(vector<string>& arrayStrings);

void razelenieDannyx(vector<string>& arrayStrings, vector<string>& rules, vector<string>& data);

string hasProp(string rules, vector<string>& data);

string hasAmount(string rules, vector<string>& data);

string hasOne(string rules, vector<string>& data);

string hasAll(string rules, vector<string>& data);
bool correctData(string str);