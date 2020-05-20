#pragma once
#include<iostream>
#include<fstream>
using namespace std;
const int N = 100;

struct String {
	unsigned length;
	char a[N];
};

void GetStringCin(String *s);
void GetStringFile(String* s, fstream* f);
bool Compare(String s1, String s2);
bool IsTheFirstBigger(String s1, String s2);
void EraseString(String* s, int pos, int amount);
void OutStringF(String s, ofstream* f);
void OutString(String s);