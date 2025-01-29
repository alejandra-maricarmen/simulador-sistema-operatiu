
/// -----------------------------------------
///
///  	Implementació classe Memoria
///
/// -----------------------------------------

#include "memoriaBST.hpp"

/* Cal que implementeu tots els mètodes, llevat de l'operator<< */

Memoria::Memoria() 
{};

Memoria::Memoria (const Memoria &m) 
{
	memoria = m.memoria;
};

Memoria::~Memoria() 
{};

/**
 * Pre: cert
 * Post: assigna a aquesta memòria la Memoria m passada per referència
 */
Memoria& Memoria::operator= (const Memoria& m) 
{
	memoria = m.memoria;
	return *this;
};

/**
 * Pre: c és una clau de tipus string, v és un enter
 * Post: assigna el valor v a la variable de clau c si ja existeix a la memòria,
 * o si no existeix a la memòria li inserta una nova tupla de nom e, clau c i valor v
 */
void Memoria::set(const string& c, int v)
{
	TUPLA s;
	s.clau = c;
	s.valor = v;

	pair<bool, Memoria::TUPLA> trobat = memoria.find(s);

	if (trobat.first == true) memoria.setValue(s, s);
	else memoria.insert(s);
};

/**
 * Pre: c és una clau de tipus string de una variable que existeix a la memòria
 * Post: retorna el valor de la variable de la clau c
 */
int Memoria::get (const string& c)
{
	TUPLA s;
	s.clau = c;
	s.valor = 0;

	pair<bool, Memoria::TUPLA> trobat = memoria.find(s);

	return trobat.second.valor;
};

ostream& operator<<(ostream& os, const Memoria& m) 
{
	vector<Memoria::TUPLA> pre;
	
	m.memoria.preOrdre(pre);
	
	for (Memoria::TUPLA t : pre)	os << t << endl;
	
	return os;
};


