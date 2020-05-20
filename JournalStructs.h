#pragma once
#include"f_string.h";

struct Articles {
	String Name, AuthorName;
	Articles* next;
};

struct Editions {
	int number;
	String date;
	Editions* next;
	Articles* ar;
};

struct Journal {
	String Name;
	Journal *next;
	Editions* ed;
};

struct Author {
	String JournalName;
	//int Edition;
	Articles* ar;
	Author* same;
	Author* next;
};