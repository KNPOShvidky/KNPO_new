#pragma once
#include <vector>

using namespace std;

vector<string> divideIntoClasses(vector<string>& arrayStrings);

void razelenieDannyx(vector<string>& arrayStrings, vector<string>& rules, vector<string>& data);

string hasProp(string rules, vector<string>& data);

string hasAmount(string rules, vector<string>& data);

string hasOne(string rules, vector<string>& data);

string hasAll(string rules, vector<string>& data);