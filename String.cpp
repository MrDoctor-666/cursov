#include "f_string.h"
//ЭТО ЗАНОВО ИЗОБРЕТЕННАЯ БИБЛИОТЕКА СТРОЧЕК ЗА ЧТО
void GetStringCin(String* s)
{
	cin >> noskipws;
	int i = 0; cin >> (*s).a[0];
	while ((*s).a[i] != '\n')
	{
		i++;
		cin >> (*s).a[i]; 
	}
	(*s).length = i;
}

void GetStringFile( String* s, fstream* f)
{
	*f >> noskipws;
	int i = 1; 
	*f >> (*s).a[0];
	while ((*s).a[i-1] != '\n')
	{
		*f >> (*s).a[i];
		if ((*s).a[i] == '\n' || (*f).eof()) break;
		i++;
	}
	(*s).length = i;
}

bool Compare(String s1, String s2)
{
	if (s1.length != s2.length) return false;
	for (int i = 0; i < s1.length; i++)
	{
		if (s1.a[i] != s2.a[i]) return false;
	}
	return true;
}

bool IsTheFirstBigger(String s1, String s2)
{
	//if s1 > s2 return true
	int n;
	if (s1.length > s2.length) n = s2.length;
	else n = s1.length;
	for (int i = 0; i < n; i++)
	{
		if (s1.a[i] > s2.a[i]) return true;
		if (s1.a[i] < s2.a[i]) return false;
	}
	if (s1.length > s2.length) return true;
	else return false;
}

void EraseString(String* s, int pos, int amount)
{
	int k = (*s).length - amount;
	for (int i = pos; i < k; i++)
	{
		(*s).a[i] = (*s).a[i + amount];
	}
	(*s).length = k;
}

void OutStringF(String s, ofstream* f)
{
	*f << " '";
	for (int i = 0; i < s.length; i++)
		 *f << s.a[i];
	*f << "' \n";
}

void OutString(String s)
{
	for (int i = 0; i < s.length; i++)
		cout << s.a[i]; 
}
