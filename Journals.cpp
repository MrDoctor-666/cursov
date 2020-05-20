#include "JournalStructs.h";
#include "f_string.h";
#include<fstream>

Journal* GetNext(Journal* a)
{
	return a->next;
}

void SetCur(Journal** cur, Journal* next)
{
	*cur = next;
}

bool WannaExit()
{
	String s;
	cout << "Wanna exit? Press 0: ";
	GetStringCin(&s);
	if (s.a[0] == '0') return true;
	else return false;
}

unsigned StringInInt(String s)
{
	int n = 0;
	for (int i = 0; i < s.length; i++)
	{
		if (s.a[i] >= '0' && s.a[i] <= '9') n = n * 10 + s.a[i] - 48;
	}
	return n;
}

bool IfExists(Journal* a, String s) {
	Journal* cur; cur = a;
	while (!Compare(cur->Name, s) && cur!=NULL) {
		cur = cur->next;
		if (cur == NULL) break;
	}
	if (cur == NULL) return 0;
	else return 1;
}

bool EdExists(Journal* nw, unsigned n)
{
	Editions* cur;  cur = nw->ed;
	while (cur != NULL)
	{
		if (n == cur->number) return true;
		cur = cur->next;
	}
	if (cur == NULL) return false;
}

bool ArExists(Editions* edi, String Name, String Author)
{
	Articles* cur; cur = edi->ar;
	while (cur != NULL)
	{
		if (Compare(cur->Name, Name) && Compare(cur->AuthorName, Author)) return true;
		cur = cur->next;
	}
	return false;
}

bool CheckIfDateCorrect(String date, ofstream* fout) 
{
	int i = 0; bool k;
	if (!(date.a[0] <= '3' && date.a[3] <= '1' && date.a[6] <= '2')) { k = false; }
	else if ((date.length == 10) && (date.a[2] == '.') && (date.a[5] == '.'))
	{
		for (i = 0; i < date.length; i++)
			if ((date.a[i] < '0' || date.a[i] > '9') && (i != 2 && i != 5)) break;
	}
	else k = false;
	if (i == date.length) k = true;
	else k = false;
	if (date.a[0] == '-' && date.length == 1) *fout << "No date";
	else if (k == true) *fout << "Date is in";
	else *fout << "Date is incorrect";
	OutStringF(date, fout);
	return k;
}

Author* SearchSameAuthor(Author* h, String name)
{
	Author* newau = h;
	while (newau != NULL)
	{
		if (Compare(newau->ar->AuthorName, name)) return newau;
		newau = newau->next;
	}
	return NULL;
}

Author* InputA(Author* newa, Author* h)
{
	Author* cur, * prev, *before, *after; prev = NULL;
	cur = SearchSameAuthor(h, newa->ar->AuthorName);
	if (cur == NULL) {
		cur = h;
		newa->same = NULL;
		while (1) {
			if (IsTheFirstBigger(newa->ar->AuthorName, cur->ar->AuthorName)) {
				prev = cur;  cur = cur->next;
			}
			else {
				if (prev == NULL) { newa->next = cur; h = newa;  break; }
				else { prev->next = newa; newa->next = cur;  break; }
			}
			if (cur == NULL) { prev->next = newa; newa->next = NULL;  break; }
		}
	}
	else
		while (1) {
			newa->next = NULL;
			if (IsTheFirstBigger(newa->ar->Name, cur->ar->Name)) {
				prev = cur;  cur = cur->same;
			}
			else {
				if (prev == NULL) { prev = cur;  cur = cur->same;  }
				else { prev->same = newa; newa->same = cur;  break; }
			}
			if (cur == NULL) { prev->same = newa; newa->same = NULL;  break; }
		}
	return h;
}

Journal* SearchSame(Journal* a, String s) {
	Journal* cur; cur = a;
	while (!Compare(cur->Name, s)) cur = cur->next;
	return cur;
}

Editions* SearchSameE(Journal* nw, unsigned n)
{
	Editions* cur; cur = nw->ed;
	while (n != cur->number) cur = cur->next;
	return cur;
}

Journal* InputMiddleJ(Journal* a, Journal* nw) {
	Journal* cur, * prev; cur = a; prev = NULL;
	while (1) {
		if ( IsTheFirstBigger(nw->Name, cur->Name)) {
			prev = cur;  cur = cur->next;
		}
		else {
			if (prev == NULL) { nw->next = cur; a = nw;  break; }
			else { prev->next = nw; nw->next = cur; break; }
		}
		if (cur == NULL) { prev->next = nw; nw->next = NULL; break; }
	}
	return a;
}

void InputMiddleE(Journal** nw, Editions* edi, ofstream* f) {
	Editions* cur, * prev; cur = (*nw)->ed; prev = NULL; 
	*f << "New Edition number " << edi->number <<  " added\n"; 
	while (1) {
		if (cur == NULL && prev == NULL) { (*nw)->ed = edi; edi->next = NULL; break; }
		if (cur->number < edi->number) {
			prev = cur;  cur = cur->next;
		}
		else {
			if (prev == NULL) { edi->next = cur; (*nw)->ed = edi;  break; }
			else { prev->next = edi; edi->next = cur; break; }
		}
		if (cur == NULL) { prev->next = edi; edi->next = NULL; break; }
	}
}

void InputMiddleA(Editions** edi, Articles* art, ofstream* f)
{
	Articles* cur, * prev; cur = (*edi)->ar; prev = NULL;
	*f << "New article added"; OutStringF(art->Name, f);
	while (1) {
		if (cur == NULL && prev == NULL) { (*edi)->ar = art; art->next = NULL; break; }
		if (IsTheFirstBigger(art->Name, cur->Name)) {
			prev = cur;  cur = cur->next;
		}
		else {
			if (prev == NULL) { art->next = cur; (*edi)->ar = art;  break; }
			else { prev->next = art; art->next = cur; break; }
		}
		if (cur == NULL) { prev->next = art; art->next = NULL; break; }
	}
}

Author* InputMiddleAuthor(Author* h, int edition, String jname, Articles* art)
{
	Author *newa = new Author;
	//newa->Edition = edition; 
	newa->JournalName = jname;
	newa->ar = art; 
	if (h == NULL) {
		h = newa;
		h->next = NULL, h->same = NULL;
	}
	else { 
		h = InputA(newa, h);
	}
	return h;
}

Journal* InputJ(Journal** a, String s, ofstream* fout)
{
	Journal* nw; 
	if (!IfExists(*a, s))
	{
		nw = new Journal; nw->Name = s; *a = InputMiddleJ(*a, nw); nw->ed = NULL;
		*fout << "New journal created"; OutStringF(s, fout);
	}
	else { nw = SearchSame(*a, s); *fout << "Journal already exists"; OutStringF(s, fout);}
	return nw;
}

Journal* InputNewCin(Journal* a, Author** h) {

	ofstream f; f.open("out.txt", ios::app);
	cout << "Input journal name: ";
	String s; GetStringCin(&s);
	Journal* nw;  unsigned n;
	f << "\nNew Cin input:\n";
	if (a != NULL) nw = InputJ(&a, s, &f);
	else { a = new Journal; a->Name = s; nw = a; a->next = NULL; a->ed = NULL; 
	f << "New Journal created"; OutStringF(s, &f);
	}

	char g;
	while (1) {
		cout << "Input edition number: ";
		GetStringCin(&s); n = StringInInt(s);
		Editions* edi;
		if (!EdExists(nw, n))
		{
			edi = new Editions;
			edi->number = n;
			cout << "Input date (xx.xx.xxxx) or -: ";
			GetStringCin(&(edi->date)); // cin >> edi->date;
			InputMiddleE(&nw, edi, &f);
			while (!CheckIfDateCorrect(edi->date, &f))
			{
				if ((edi->date).a[0] == '-' && edi->date.length == 1) break;
				cout << "Wrong\n";
				GetStringCin(&(edi->date)); //cin >> edi->date;
			}
			edi->ar = NULL;
		}
		else { edi = SearchSameE(nw, n); f << "Edition number " << n << " exists going forth"; }
		if (WannaExit()) break; //Номер журанала введен/найден

		while (1)
		{
			Articles* art; String ns, s;
			cout << "Input Article Name: "; GetStringCin(&ns);
			cout << "Input Author's Name: "; GetStringCin(&s);
			if (!ArExists(edi, ns, s))
			{
				art = new Articles;
				art->Name = ns;
				art->AuthorName = s;
				InputMiddleA(&edi, art, &f);
				*h = InputMiddleAuthor(*h, edi->number, nw->Name, art);
			}
			else f << "Article already exists\n";
			cout << "\nYou can either input another article or go back to editions\n";
			if (WannaExit()) break;
		}
		cout << "Now you can exit in main menu\n";
		if (WannaExit()) break;
	}
	f.close();
	return a;
}

Journal* InputNewFile(Journal* a, Author** h)
{
	fstream f;
	ofstream fout; f.open("in.txt", ios::in); fout.open("out.txt", ios::app);
	String s; 
	GetStringFile(&s, &f);
	while (1)
	{
		fout << "\nNew File Enter:\n";
		Journal* nw;  unsigned n, k = 0; 
		if (a != NULL) nw = InputJ(&a, s, &fout);
		else {a = new Journal; a->Name = s; nw = a; a->next = NULL; a->ed = NULL; 
		fout << "New Journal created"; OutStringF(s, &fout);
		}
		//журнальчики вроде введены
		if (f.eof()) break;
		GetStringFile(&s, &f); 
		while ((s.a[0] == '#' || s.a[0] == '№') && s.length > 1)
		{
			Editions* edi; Articles* art;
			int i = 1; n = 0;
			//n = StringInInt(s);
			while (s.a[i] <= '9' && s.a[i] >= '0')
			{
				n = n * 10 + s.a[i] - 48; i++;
			} 
			//number
			if (!EdExists(nw, n)) {
				edi = new Editions;
				edi->number = n;
				InputMiddleE(&nw, edi, &fout);
				(edi->date).a[0] = '-'; edi->date.length = 1;
				if (s.length != i) {
					EraseString(&s, 0, i + 1);
					if (CheckIfDateCorrect(s, &fout)) edi->date = s;
				}
				edi->ar = NULL;
			}
			else { edi = SearchSameE(nw, n); fout << "Edition number " << n << " exists going forth\n"; }\
			//date
			if (f.eof()) {k = 1;  break;}
			GetStringFile(&s, &f); String ns; //всю строчку с именем статьи и автора прочитали
			while (s.a[0] == '-') {
				EraseString(&s, 0, 2); i = 0;
				while (s.a[i] != '(')
				{
					ns.a[i] = s.a[i]; i++;
				}
				//все записывается в формает "- Имя (Автор)"
				ns.length = i; //имя статьи
				EraseString(&s, 0, i + 1); EraseString(&s, s.length - 1, 1);
				if (ns.a[ns.length - 1] == ' ') EraseString(&ns, ns.length - 1, 1); //подчищаем проблельчики и скобки
				if (!ArExists(edi, ns, s))
				{
					art = new Articles;
					art->Name = ns;
					art->AuthorName = s;
					InputMiddleA(&edi, art, &fout);
					*h = InputMiddleAuthor(*h, edi->number, nw->Name, art);
				}
				else { fout << "Article exists"; OutStringF(ns, &fout); }
				EraseString(&s, 0, s.length);
				if (f.eof()) { k = 1;  break; }
				GetStringFile(&s, &f);
			}
			if (k == 1) break;
		}
		if ((s.a[0] == '#' || s.a[0] == '№') && s.length == 1) GetStringFile(&s, &f);
		if (k == 1) break;
	}
	f.close(); fout.close();
	return a;
}

void OutputArticle(Articles* ar)
{
	cout << "	Article: "; OutString(ar->Name);
	cout << " by ";
	OutString(ar->AuthorName); cout << "\n";
}

void OutputEdition(Editions* cure)
{
	Articles* cura = cure->ar;
	while (cura != NULL)
	{
		OutputArticle(cura);
		cura = cura->next;
	}
}

void OutputJournal (Journal* nw){
	Editions* cure = nw->ed; Articles* cura;
	while (cure != NULL)
	{
		cout << "  Edition #" << (cure->number) << " from "; OutString(cure->date); cout << "\n";
		OutputEdition(cure);
		cout << "\n";
		cure = cure->next;
	}
}

void OutputArA(Author* cur, ofstream* f)
{
	cout << "	Article: "; *f << "	Article: "; OutStringF(cur->ar->Name, f);
	OutString(cur->ar->Name);  cout << " in journal '"; *f << "	In journal ";
	OutString(cur->JournalName); OutStringF(cur->JournalName, f);
	cout << "'\n";
}

void OutputAuthor(Author* h)
{
	ofstream f;
	f.open("out.txt", ios::app); f << "\nOutputing Authors\n"; 
	Author* cur = h, *cur2 = NULL;
	cout << "here\n";
	while (cur != NULL)
	{
		cur2 = cur;
		cout << "Author: "; f << "Author: "; OutStringF(cur2->ar->AuthorName, &f);
		OutString(cur2->ar->AuthorName); cout << endl;
		while (cur2 != NULL)
		{
			OutputArA(cur2, &f);
			cur2 = cur2->same;
		}
		cout << endl;
		cur = cur->next;
	}
	f.close();
}

Journal* SearchJournal(Journal* a)
{
	ofstream f; f.open("out.txt", ios::app);
	cout << "Search journal: ";
	f << "\nChecking journal existence:\nJournal";
	Journal* nw = NULL; String s; GetStringCin(&s);
	OutStringF(s, &f);
	if (a != NULL) {
		if (IfExists(a, s)) {
			cout << "Exists\n"; f << "Exists\n";  nw = SearchSame(a, s);
		}
		else { cout << "Doesn't exist\n"; f << "Doesn't exist\n"; }
	}
	else { cout << "Doesn't exist\n"; f << "Doesn't exist\n"; }
	f.close();
	return nw;
}

Editions* SearchEdition(Journal* a)
{
	ofstream f; f.open("out.txt", ios::app); f << "\nEdition Search:\n";
	String s, num; Journal* nw = NULL, *curj = a; Editions* cur, * edi = NULL; int n = 0, i = 0;
	cout << "Do you know in which journal is it? ";
	nw = SearchJournal(a);
	cout << "What do you wanna find? Start with edition, then input date: "; 
	GetStringCin(&num); GetStringCin(&s);
	n = StringInInt(num);
	if (nw != NULL) {
		curj = nw; i = -1; f << "It's in journal"; OutStringF(nw->Name, &f);
	}
	//OutString(curj->Name);
	while (curj != NULL)
	{
		cur = curj->ed;
		while (cur != NULL)
		{
			if ((Compare(s, cur->date) && s.a[0] != '-') || n == cur->number) 
			{ edi = cur; 
			cout << "YES in journal '"; OutString(curj->Name); cout << "'\n";
			f << "Edition number " << edi->number << " exists in journal"; OutStringF(curj->Name, &f);// f << "'\n";
			}
			cur = cur->next;
		}
		if (i == -1) break;
		curj = curj->next;
	}
	return edi;
}

/*void SearchArticle(Journal* a)
{
	Articles * cura; 
	String s, what, an, name; 
	Editions* cure, * edi = NULL; Journal* curj = a, *nw = NULL; int i = 0, g = 0, k = -1;
	nw = SearchJournal(a);
	if (nw != NULL) { curj = nw; i = -2; }
	while (1)
	{
		cout << "Do you wanna search name (1), author (2) or both (3)? "; GetStringCin(&what);
		g = what.a[0] - 48;
		if (g == 2 || g == 3) { cout << "Author: "; GetStringCin(&an);  }
		if (g == 1 || g == 3) { cout << "Article Name: "; GetStringCin(&name); }
		if (g != 1 && g != 2 && g != 3) cout << "Wrong\n";
		else break;
	}
	while (curj != NULL)
	{
		cure = curj->ed;
		while (cure != NULL)
		{
			cura = cure->ar;
			while (cura != NULL)
			{
				if ((g == 1) && Compare(cura->Name, name)) {
					OutString(curj->Name); cout << "\n   #"  << cure->number << "\n"; 
					OutputArticle(cura); k = 0;
				}
				if ((g == 2) && Compare(cura->AuthorName, an)) { 
					OutString(curj->Name); cout << "\n   #" << cure->number << "\n";
					OutputArticle(cura); k = 0;
				}
				if (g == 3 && Compare(cura->AuthorName, an) && Compare(cura->Name, name)) {
					OutString(curj->Name); cout << "\n   #" << cure->number << "\n";
					OutputArticle(cura); k = 0;
				}
				cura = cura->next;
			}
			cure = cure->next;
		}
		if (i == -2) break;
		curj = curj->next;
	}
	if (k != 0) cout << "Such article doesn't exist\n";
}*/

bool SearchArticle(Author* h)
{
	ofstream f; f.open("out.txt", ios::app); f << "\nArcticle Search:\n";
	String s, what, an, name; int g, k = 0;
	Author* cur = h, * cur2;
	while (1)
	{
		cout << "Do you wanna search name (1), author (2) or both (3)? "; GetStringCin(&what);
		g = what.a[0] - 48;
		if (g == 2 || g == 3) { cout << "Author: "; GetStringCin(&an); }
		if (g == 1 || g == 3) { cout << "Article Name: "; GetStringCin(&name); }
		if (g != 1 && g != 2 && g != 3) { f << "Wrong input\n"; cout << "Wrong\n"; }
		else { f << "Searching"; break; }
	}
	if (g == 1) { f << " by article's name\n"; OutStringF(name, &f); }
	if (g == 2) { f << " by author's name\n"; OutStringF(an, &f);}
	if (g == 3) { f << " by both article"; OutStringF(name, &f); f << "and author"; OutStringF(an, &f);}
	if (g == 2 || g == 3) {
		cur = SearchSameAuthor(h, an);
		if (cur == NULL) {
			cout << "We don't have this author's articles\n";
			f << "There are no this author's articles"; return false;
		}
	}
	while (cur != NULL)
	{
		cur2 = cur;
		if (g == 2 || g == 3) {
			cout << "Author: ";
			OutString(cur2->ar->AuthorName); cout << endl;
		}
		while (cur2 != NULL)
		{
			if (g == 2) { OutputArA(cur2, &f); k = 1; }
			if ((g == 1 || g == 3) && Compare(name, cur2->ar->Name)) { 
				if (g == 1) {
					cout << "Author: "; OutString(cur2->ar->AuthorName); cout << endl;
				}
				OutputArA(cur2, &f); k = 1; 
			}
			cur2 = cur2->same;
		}
		if (g == 2 || g == 3) break;
		cur = cur->next;
	}
	if (k == 0) { cout << "Such article doesn't exist\n"; f << "Such article doesn't exist\n";}
	f.close();
	return true;
}

void Output(Journal* a) {
	ofstream f;
	f.open("out.txt", ios::app); f << "\nOutputting everything\n"; f.close();
	Journal* curj = a; 
	while (curj != NULL)
	{
		cout << "Name: "; OutString(curj->Name); cout << "\n";
		OutputJournal(curj);
		curj = curj->next;
	}
}

void DeleteAuthor(Author* h)
{
	ofstream f;
	f.open("out.txt", ios::app); f << "\nDeleting Author list\n"; f.close();
	Author* cur = h, * cur2, *h2;
	while (cur != NULL)
	{
		cur2 = cur->same;
		while (cur2 != NULL)
		{
			h2 = cur2;
			cur2 = cur2->same;
			delete h2;
		}
		cur = cur->next;
		delete h;
		h = cur;
	}
}

Journal* Delete(Journal* h)
{
	ofstream f;
	f.open("out.txt", ios::app); f << "\nDeleting main list\n"; f.close();
	Journal* cur; Editions* he, * cure; Articles* ha, * cura;
	while (h != NULL)
	{
		SetCur(&cur, h); //*cur = h
		SetCur(&h, GetNext(h)); // *h = h->next
		he = cur->ed;
		while (he != NULL)
		{
			cure = he;
			he = he->next;
			ha = cure->ar;
			while (ha != NULL)
			{
				cura = ha;
				ha = ha->next;
				delete cura;
			}
			delete cure;
		}
		delete cur;
	}
	return h;
}
