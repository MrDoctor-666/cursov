#include <stdlib.h>
#include<windows.h>
#include "f_string.h";
#include "f_journals.h";

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); 
	setlocale(LC_ALL, "Russian"); fstream f; f.open("out.txt", ios::out); f.close(); //я забыла как нормально чистить файл
	f.open("out.txt", ios::out);
	unsigned sw; 
	cout << "Welcome\n"; String s1;
	Journal* a,* t = NULL; a = NULL; 
	Editions* e; Author* h = NULL;
	while (1)
	{
		f.open("out.txt", ios::app); f << "\nWe are in the main menu\n"; f.close();
		cout << "1 - To insert manually 1\n";
		cout << "2 - To insert from file 2\n\n";
		cout << "3 - To search for a journal 3\n";
		cout << "4 - To search for an edition\n";
		cout << "5 - To search for an article\n\n";
		cout << "6 - To output all information\n";
		cout << "7 - To output all authors\n0 - To exit and delete all 0\n";
		GetStringCin(&s1);
		if (s1.a[0] == '0') break; sw = s1.a[0] - 48; 
		system("cls");
		switch (sw)
		{
		case 1: a = InputNewCin(a, &h); break;
		case 2: a = InputNewFile(a, &h); break;
		case 3: t = SearchJournal(a); if (t != NULL) OutputJournal(t);  break;
		case 4: e = SearchEdition(a); if (e != NULL) OutputEdition(e); break;
		case 5: SearchArticle(h); break;
		case 6: Output(a); break;
		case 7: OutputAuthor(h); break;
		default: cout << "Wrong input\n "; break;
		}
		system("pause");
		system("cls");
	}
	DeleteAuthor(h);
	Delete(a);
	f.open("out.txt", ios::app); f << "\n\nPROGRAMM WAS STOPPED. EVERYTHING IS DELETED\n"; f.close();
}