#include <iostream>
using namespace std;

class Nod;
class ListaFotbalisti;
class Fotbalist{
private:
	char* nume;
	char* echipa; 
	int pret;
	static int ordine;

public: 
	Fotbalist(char* nume,char* echipa,int pret);
	Fotbalist(const Fotbalist&);
	Fotbalist();
	~Fotbalist();
	char* getNume();
	void setNume(char*);
	char* getEchipa();
	void setEchipa(char*);
	int getPret();
	void setPret(int);

	Fotbalist& operator=(const Fotbalist&);
	friend ostream& operator<<(ostream&, const Fotbalist&);
	friend istream& operator>>(istream&, Fotbalist&);
	int operator==(const Fotbalist&);
	friend class Nod;
	friend class ListaFotbalisti;
};

class Nod{
	Fotbalist info; 
	Nod *next; //leg catre urm nod
public:
	Nod();
	Nod(Fotbalist info,Nod* next=0);//constrcutor de initializare
	~Nod();
	Fotbalist getInfo();//
	void setInfo(Fotbalist info);
	Nod *getNext();
	void setNext(Nod* next);
	int operator == (const Fotbalist&);
	friend class ListaFotbalisti;
};

class ListaFotbalisti {
protected:
	Nod *prim,*ultim,*curent;
public:
	ListaFotbalisti(); //constructor fara param(implicit)
	ListaFotbalisti(const ListaFotbalisti&); //constructor de copy
	~ListaFotbalisti(); //destructor
	int isEmpty();
	void clear();
	void sterge(int id);//stergere fotbalist
	void addElement(Fotbalist info);//adauga un nod la sfarsitul listei
	Nod* getFirst();//intoarce primul elemnt din lista
	Nod* getElementAt( int index);
	int getCount();//intoarce numarul elementelor
	ListaFotbalisti& operator++();
	friend ostream& operator<<(ostream&,const ListaFotbalisti&);
	Fotbalist& operator[] (int index);
};

	/* BUDUIANU ALEXANDRU */