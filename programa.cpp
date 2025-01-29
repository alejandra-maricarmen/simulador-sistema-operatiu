
/// -----------------------------------------
///  	Implementació classe Programa
/// -----------------------------------------

#include "programa.hpp"

/*--------------------------------------------------------------------*/
/*                       Mètodes privats                              */
/*--------------------------------------------------------------------*/

// PRE: s és un string que correspon a una línia de codi.
// POST: torna un vector d'strings, un string per ítem a s.
// Exemple: si s = "GOTO 30"
// torna el vector ["GOTO", "30"]

vector<string> Programa::parse(const string& s)
{
	int N = s.size();
	int i = 0;
	int inici = 0, fi = 0;
	vector<string> r;
	
	while (i < N)
	{
		while (s[i] == ' ' and i < N)	i++;
		inici = i;
		while (s[i] != ' ' and i < N)	i++;
		fi = i - 1;
		if (inici <= fi)	r.push_back(s.substr(inici,fi - inici + 1));
	}

	return r;
}

bool Programa::totDigits(const string& s)		// Implementat
{
	if (s.size() == 0)							return false;
	
	if (s[0] != '-' and (not isdigit(s[0])))	return false;
	
	for (int i = 1 ; i < s.size() ; i++)
		if (not isdigit(s[i])) return false;
		
	return true;
}

/*--------------------------------------------------------------------*/

Programa::Programa(int id, int proc, int pri, Dispositiu d)
{
	_id 		= id;
	_proc 		= proc;
	_prioritat 	= pri;
	
	AC 			= 0;
	PC 			= 0;
	STATUS 		= 0;
	COMPARACIO	= 0;
	dispositiu	= d;
};

Programa::Programa()
{};

Programa::Programa(const Programa& P)
{
	_id 		= P._id;
	_proc 		= P._proc;
	_prioritat 	= P._prioritat;
	
	AC 			= P.AC;
	PC 			= P.PC;
	STATUS 		= P.STATUS;
	COMPARACIO	= P.COMPARACIO;
	
	dispositiu 	= P.dispositiu;
	
	pila		= P.pila;
	llistat		= P.llistat;
	memoria		= P.memoria;
};

/*********************************************************************/
/************* IMPLEMENTEU ELS MÈTODES A CONTINUACIÓ *****************/
/*********************************************************************/

Programa::~Programa() {};

int Programa::id() const 
{
	return _id;
}

int Programa::prioritat() const 
{
	return _prioritat;
}

void Programa::prioritat (int p) 
{
	_prioritat = p;
}

/*POST: afegeix i al dispositiu del programa*/
void Programa::afegeixDispositiu (int i)
{
	dispositiu<<i;
}

/*POST escriu el dispositiu del programa pel canal os */
void Programa::escriuDispositiu (ostream& os) const
{
	os << dispositiu << endl;
}

/* POST: torna true sii el paràmetre implícit és menor
		 que el paràmetre pro2.
		 Un programa és més gran que l'altre si la 
		 prioritat és superior. En cas de tenir la 
		 mateixa prioritat, és qui té _id menor.*/
bool Programa::compare(const Programa& prog2) const
{
	bool es_menor = false;
	if ((prog2._prioritat < _prioritat) or (_prioritat == prog2._prioritat and prog2._id < _id)) es_menor = true;
	return es_menor;
}

/* interfície de compare*/
bool Programa::operator<(const Programa& prog2) const
{
	return this->compare(prog2);
}

Programa& Programa::operator=(const Programa& P)	// Implementat
{
    if (this == &P)        return *this;

	_id 		= P._id;
	_proc 		= P._proc;
	_prioritat 	= P._prioritat;
	
	AC 			= P.AC;
	PC 			= P.PC;
	STATUS 		= P.STATUS;
	COMPARACIO	= P.COMPARACIO;
 
	pila		= P.pila;
	llistat		= P.llistat;
	memoria		= P.memoria; 
 
	dispositiu	= P.dispositiu;

    return *this;
}

void Programa::escriuMemoria(ostream& os) const		// Implementat
{
	os << "Programa id: " << _id << " STATUS:" << STATUS << 
			" COMP: " << COMPARACIO << 
			" PC: " << (PC + 1) * 10 << endl;
			
	os << memoria << endl;

	return;
}

/*******************************************************
 * 				INSTRUCCIONS.
********************************************************/
/*
Totes les funcions següents implementen les operacions
que han estat especificades a l'enunciat.
*/

int Programa::opAritmetica(const vector<string>& instr)
{
	if (pila.size() == CAPACITAT) STATUS = -1;
	else 
	{
		int op1, op2;
		
		if (totDigits(instr[1])) op1 = stoi(instr[1]);
		else op1 = memoria.get(instr[1]);
		
		if (totDigits(instr[2])) op2 = stoi(instr[2]);
		else op2 = memoria.get(instr[2]);

		if (instr[0] == "SUMA") pila.push(op1 + op2);
		else if (instr[0] == "RESTA") pila.push(op1 - op2);
		else if (instr[0] == "MULT") pila.push(op1*op2);
		else if (op2 == 0) STATUS = -2;
		else pila.push(op1/op2);
	}

	++PC;
	return STATUS;
}

int Programa::opPila(const vector<string>& instr)
{
	int op;

	if (instr[0] == "EMPILA")
	{
		if (pila.size() == CAPACITAT) STATUS = -1;
		else
		{
			if (totDigits(instr[1])) op = stoi(instr[1]);
			else op = memoria.get(instr[1]);

			pila.push(op);
		}
	}
	else
	{
		if (pila.empty()) STATUS = -3;
		else
		{
			op = pila.top();
			pila.pop();

			memoria.set(instr[1], op);
		}
	}

	++PC;
	return STATUS;
}

int Programa::opDispositiu(const vector<string>& instr)
{
	int op;

	if (instr[0] == "LLEGEIX")
	{
		if (dispositiu>>op) memoria.set(instr[1], op);
		else STATUS = -8;
	}
	else
	{
		if (totDigits(instr[1])) op = stoi(instr[1]);
		else op = memoria.get(instr[1]);

		if (not (dispositiu<<op)) STATUS = -9;
	}
	
	++PC;
	return STATUS;
}

int Programa::opMemoria(const vector<string>& instr)
{
	int op;
	if (totDigits(instr[2])) op = stoi(instr[2]);
	else op = memoria.get(instr[2]);

	memoria.set(instr[1], op);
	
	++PC;
	return STATUS;
}

int Programa::opSalt(const vector<string>& instr)
{
	int op = stoi(instr[1]);
	op = op/10 - 1;

	if (op < 0 or llistat.size() <= op) 
	{
		STATUS = -5;
		++PC;
	}
	else
	{
		if (instr[0] == "GOTO" or 
		(instr[0] == "MESGRAN" and COMPARACIO == 1) or 
		(instr[0] == "MESPETIT" and COMPARACIO == 2) or 
		(instr[0] == "IGUAL" and COMPARACIO == 3) or 
		(instr[0] == "PILABUIDA" and pila.empty()) or 
		(instr[0] == "DISPBUIT" and dispositiu.buit())) {
			PC = op;
		}
		else ++PC;
	}

	return STATUS;
}

int Programa::opComparacio(const vector<string>& instr)
{
	int op1, op2;

	if (totDigits(instr[1])) op1 = stoi(instr[1]);
	else op1 = memoria.get(instr[1]);
		
	if (totDigits(instr[2])) op2 = stoi(instr[2]);
	else op2 = memoria.get(instr[2]);

	if (op2 < op1) COMPARACIO = 1;
	else if (op1 < op2) COMPARACIO = 2;
	else COMPARACIO = 3;

	++PC;
	return STATUS;
}

int Programa::opIncrement(const vector<string>& instr)
{
	int op = memoria.get(instr[1]);
	
	if (instr[0] == "INCREMENTA") ++op;
	else --op;

	memoria.set(instr[1], op);

	++PC;
	return STATUS;
}

int Programa::opNofares(const vector<string>& instr)	//Implementat
{
	if (instr[0] == "NOFARES")		PC++;	// per evitar error de compilació
											// "variable not used"
		
	return STATUS;
}

int Programa::executa ()		// Implementat
{
	if (STATUS < 0 )			return STATUS;
	if (PC >= llistat.size())	{STATUS = -10; return STATUS;} // programa acabat
	
	int RETORN = 0;
	
	assert (PC < llistat.size());

	string instr = llistat[PC][0];

	if (instr == "SUMA" or 
		instr == "RESTA" or 
		instr == "MULT" or 
		instr == "DIV")				RETORN = opAritmetica(llistat[PC]);
		
	if (instr == "EMPILA" or 
		instr == "DESEMPILA")		RETORN = opPila(llistat[PC]);

	if (instr == "LLEGEIX" or 
		instr == "ESCRIU")			RETORN = opDispositiu(llistat[PC]);

	if (instr == "MOU")				RETORN = opMemoria(llistat[PC]);
	
	if (instr == "GOTO" or 
		instr == "MESGRAN" or 
		instr == "MESPETIT" or 
		instr == "IGUAL" or
		instr == "PILABUIDA" or
		instr == "DISPBUIT")		RETORN = opSalt(llistat[PC]);
	
	if (instr == "CMP")				RETORN = opComparacio(llistat[PC]);
	
	if (instr == "INCREMENTA" or
		instr == "DECREMENTA")		RETORN = opIncrement(llistat[PC]);	

	if (instr == "NOFARES")			RETORN = opNofares(llistat[PC]);
			
	return RETORN;
};

string Programa::status() const		// Implementat
{
	string s;
	s = "PROGRAM ID: " 	+ to_string(_id) +
		" PRIO: " 	 	+ to_string(_prioritat) +
		" PROC#: " 	 	+ to_string(_proc) +
		" AC: " 		+ to_string(AC) +
		" PC: "			+ to_string( (PC + 1) * 10) +
		" STATUS: "		+ to_string(STATUS) +
		" STACK: " 		+ to_string(pila.size()) + "/" + to_string(CAPACITAT);

	return s;
};

/* Els operadors << i >> també us els donem implementats */

ostream& operator<<(ostream& os, const Programa& p) 
{
	os << "--------------------------------" << endl;
	os  << p.status() << endl;
	
	for (int i = 0 ; i < p.llistat.size() ; i++)
	{
		os << (i + 1) * 10 << ": ";
		
		for (int j = 0 ; j < p.llistat[i].size() ; j++)	
			os << p.llistat[i][j] << " ";
		
		if (p.PC == i)				os << " <- PC";

		os << endl;
	}
	
	os << "--------------------------------" << endl;
	
	return os;
};

istream& operator>>(istream& is, Programa& programa)
{	
	string linia;
	
	getline(is,linia);
	while (linia != "FINAL_PROGRAMA")
	{
		vector<string> llista = programa.parse(linia);		
		programa.llistat.push_back(llista);
		getline(is,linia);
	}
	
	return is;
};




