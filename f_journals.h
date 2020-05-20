#pragma once
#include "JournalStructs.h";

Journal* InputNewCin(Journal* a, Author** h);
Journal* InputNewFile(Journal* a, Author** h);
void OutputJournal(Journal* nw);
void OutputEdition(Editions* cure);
void OutputAuthor(Author* h);
Journal* SearchJournal(Journal* a);
Editions* SearchEdition(Journal* a);
bool SearchArticle(Author *h);
void Output(Journal* a);
void DeleteAuthor(Author* h);
Journal* Delete(Journal* h);
