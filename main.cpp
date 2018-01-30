#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include "clase.h"

/*clasa Fotbalist*/
int Fotbalist::ordine=0;
Fotbalist::Fotbalist(char* nume,char* echipa,int pret)
{
	this->nume=new char[strlen(nume)+1];
	strcpy(this->nume,nume);
	this->echipa=new char[strlen(echipa)+1];
	strcpy(this->echipa,echipa);
	this->pret=pret;
}
Fotbalist::Fotbalist(const Fotbalist& f)
{
	nume=new char[strlen(f.nume)+1];
	strcpy(nume,f.nume);
	echipa=new char[strlen(f.echipa)+1];
	strcpy(echipa,f.echipa);
	pret=f.pret;
}
Fotbalist::Fotbalist()
{
	nume=0;
	echipa=0;
}
Fotbalist::~Fotbalist()
{
	if(nume)delete[] nume;
	if(echipa)delete[] echipa;
}
char* Fotbalist::getNume()
{
	return nume;
}
void Fotbalist::setNume(char* nume)
{
	if(this->nume)delete[] this->nume;
	nume=new char[strlen(nume)+1];
	strcpy(this->nume,nume);
}
char* Fotbalist::getEchipa()
{
	return echipa;
}
void Fotbalist::setEchipa(char* echipa)
{
	if(this->echipa)delete[] this->echipa;
	echipa=new char[strlen(echipa)+1];
	strcpy(this->echipa,echipa);
}
int Fotbalist::getPret()
{
	return pret;
}
void Fotbalist::setPret(int pret)
{
	this->pret=pret;
}
Fotbalist& Fotbalist::operator=(const Fotbalist& f)
{
	if(this!=&f){
		if(nume)delete nume;
		nume=new char[strlen(f.nume)+1];
		strcpy(nume,f.nume);
		if(echipa)delete echipa;
		echipa=new char[strlen(f.echipa)+1];
		strcpy(echipa,f.echipa);
		pret=f.pret;
	}
	return *this;
}
int Fotbalist::operator==(const Fotbalist& s)
{
	return pret==s.pret;
}
ostream& operator<<(ostream& out, const Fotbalist& f)
{
	out<<"Nume: "<<f.nume<<endl;
	out<<"Echipa: "<<f.echipa<<endl;
	out<<"Pret: "<<f.pret<<endl;
	return out;
}
istream& operator>>(istream& in, Fotbalist& f)
{
	return in;
}


/*clasa Nod*/
Nod::Nod()
{
	next=0;
}
Nod::Nod(Fotbalist info,Nod* next)
{
	this->info=info;
	this->next=next;
}
Nod::~Nod()
{

}
Fotbalist Nod::getInfo()
{
	return info;
}
void Nod::setInfo(Fotbalist info)
{
	this->info=info;
}
Nod* Nod::getNext()
{
	return next;
}
void Nod::setNext(Nod* next)
{
	this->next=next;
}
int Nod::operator == (const Fotbalist& f)
{
	return info==f;
}


/*clasa ListaFotbalisti*/
ListaFotbalisti::ListaFotbalisti()
{
	prim=ultim=curent=0;
}
ListaFotbalisti::ListaFotbalisti(const ListaFotbalisti& list)
{
	Nod *p;
	prim=ultim=curent=0;
	p=list.prim;
	while (p)
	{
		addElement(p->info);
		p = p->next;
	}
}
ListaFotbalisti::~ListaFotbalisti()
{
	clear();
}
int ListaFotbalisti::isEmpty()
{
	return prim==0;
}
void ListaFotbalisti::clear()
{
	Nod *p, *q;
	p = prim;
	while (p)
	{
		q=p;
		p=p->next;
		delete q;
	}
	prim = ultim=curent = 0;
}
void ListaFotbalisti::sterge(int id)
{	int i=1;
	Nod *p = prim;
	//daca nu sunt fotbalisti
	if(p == NULL) return;
	//daca e primul fotbalisti
	if (id == 0)
    {
        Nod* q = p;
        prim = p->next;
        delete q;
  		return;
    }
    //caut dupa pozitie
	while (p != NULL && i < id)
    {
        p=p->next;
        i++;
    }
    if (i == id)
    {
    	Nod* aux = p;
      	p = p->next;
      	aux->next=p->next;
      	delete p;
    	cout<<"*Fotbalistul a fost adaugat la fotbalistii achizitionati de dumneavoastra."<<endl;
    }
}
void ListaFotbalisti::addElement(Fotbalist info)
{
	Nod *p;
	p=new Nod;
	p->info=info;
	p->next=0;
	if(isEmpty())
	{
		curent=prim=ultim=p;
	}
	else
	{
		ultim->next=p;
		ultim = p;
	}
}
Nod* ListaFotbalisti::getFirst()
{
	return prim;
}
Nod* ListaFotbalisti::getElementAt(int index)
{
	int i;
	Nod* p;
	for(i = 0,p = prim;i < index && p != 0;i++,p = p -> next);
	return p;
}
int ListaFotbalisti::getCount()
{
	int n=0;
	Nod* p=prim;
	while(p)
	{
		n++;
		p=p->next;
	}
	return n;
}
ListaFotbalisti& ListaFotbalisti::operator++()
{
	if(curent)curent=curent->next;
	return *this;
}
ostream& operator<<(ostream& out, ListaFotbalisti& list)
{
	Nod* p= list.getFirst();
	while(p)
	{
		out<<endl<<p->getInfo()<<endl;
		p=p->getNext();
	}
	return out;
}
Fotbalist& ListaFotbalisti::operator[] (int index)
{
	return getElementAt(index)->info;
}


int main()
{
	ListaFotbalisti Fotbalisti, Achizitionati;
	ifstream f("fotbalisti.in");
	char name[100],team[100];
	int i,pret,buget,option,suplim;
	if(!f)
	{
		cout<<"Eroare la deschiderea fisierului!"<<endl;
		return 0;
	}
	i=1;
	///citesc fotbalistii din fisier
	while(!f.eof())
	{
		f>>name;
		f>>team;
		f>>pret;
		Fotbalisti.addElement(Fotbalist(name,team,pret));
	}
	buget = 0;
	suplim = 0;
	cout<<"Care este bugetul dumneavoastra pentru aceasta fereastra de transferuri?";
	cout<<endl;
	cin>>buget;
	option=0;
	do
	{
	system("cls");
	cout<<"\t\tMeniu"<<endl;
	cout<<"Alegeti una din urmatoarele optiuni:"<<endl;
	cout<<"1.Cumparare fotbalist"<<endl;
	cout<<"2.Lista fotbalisti achizitionati"<<endl;
	cout<<"3.Iesire"<<endl;
	cin>>option;
	switch(option)
	{
	case 1:
	{
		system("cls");
		cout<<"Lista fotbalistilor disponibili:"<<endl;
		///verific daca mai sunt jucatori disponibili de transferat
		if(Fotbalisti.isEmpty())
		{
		cout<<"Nu mai sunt fotbalisti de transferat!"<<endl<<endl;
		cout<<endl<<"0.Iesire"<<endl<<"1.Inapoi";
		cin>>option;
		switch(option)
		{
			case 1: break;
			case 0: return 0;
			default: cout<<"Raspuns incorect!";
		}
		}
		else
		{
		///afisez jucatorii disponibili
		for(i=0;i<Fotbalisti.getCount();i++)
		{
		cout<<"Jucator "<<i<<endl;
		cout<<"Nume:"<<Fotbalisti[i].getNume()<<endl;
		cout<<"Echipa:"<<Fotbalisti[i].getEchipa()<<endl;
		cout<<"Pret:"<<Fotbalisti[i].getPret()<<"$"<<endl;
		cout<<endl;
		}
		cout<<"Ce fotbalist doriti sa achizitionati?"<<endl;
		cin>>option;
		if(option > Fotbalisti.getCount()-1 || option < 0)
		{
			cout<<"Raspuns incorect!";
			break;
		}
		else
		{
		if(buget>Fotbalisti[option].getPret())
		{
		system("cls");
		cout<<"Felicitari!";
		cout<<"Ati achizitionat fotbalistul: "<<endl;
		cout<<"Nume:"<<Fotbalisti[option].getNume()<<endl;
		cout<<"Echipa:"<<Fotbalisti[option].getEchipa()<<endl;
		cout<<"Pret:"<<Fotbalisti[option].getPret()<<"$"<<endl<<endl;
		buget = buget - Fotbalisti[option].getPret();
		cout<<"Noul dumneavoastra buget este: "<<buget<<"$"<<endl<<endl;
		///achizitionare fotbalist
		Achizitionati.addElement(Fotbalist(Fotbalisti[option].getNume(),Fotbalisti[option].getEchipa(),Fotbalisti[option].getPret()));
		Fotbalisti.sterge(option);
		cout<<endl<<"0.Iesire"<<endl<<"1.Inapoi";
		cin>>option;
		switch(option)
		{
			case 1: break;
			case 0: return 0;
			default: cout<<"Raspuns incorect!";
		}
		}
		else
		{
			cout<<"Nu aveti buget pentru acest jucator!"<<endl;
			cout<<"Suplimentati bugetul?"<<endl;
			cout<<"1.Da"<<endl<<"2.Nu"<<endl;
			cin>>option;
			if(option==1)
			{
				system("cls");
				cout<<"Suma cu care suplimentati bugetul este:";
				cin>>suplim;
				buget = buget + suplim;
				cout<<"Noul dumneavoastra buget este: "<<buget<<"$"<<endl<<endl;
				cout<<endl<<"0.Iesire"<<endl<<"1.Inapoi";
				cin>>option;
				switch(option)
				{
					case 1: break;
					case 0: return 0;
					default: cout<<"Raspuns incorect!";
				}
			}
		}
		}
		}
	}break;
	case 2:
		{
			system("cls");
			cout<<"Fotbalistii achizitionati sunt:"<<endl;
			cout<<Achizitionati<<endl;

			cout<<endl<<"0.Iesire"<<endl<<"1.Inapoi";
			cin>>option;
			switch(option)
			{
				case 1: break;
				case 0: return 0;
				default: cout<<"Raspuns incorect!";
			}
		}break;

	case 3: return 0;

	default:
			cout<<"Raspuns incorect!";
	}
	}while(option!=0);

	return 0;
	/* BUDUIANU ALEXANDRU */
}
