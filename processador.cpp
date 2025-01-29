
/// -----------------------------------------
///
///  	Implementació classe Processador
///
/// -----------------------------------------

#include "processador.hpp"

Processador::Processador()			// Implementat
{
	_id = -1;
	program_n = 0;
};

Processador::Processador(int i)		// Implementat
{
	_id = i;
	program_n = 0;
};

Processador::~Processador()			// Implementat
{};

int Processador::id() const {return _id;};	// Implementat

/********************************************************/
/*              Implementeu el que queda                */
/********************************************************/

/* POST: encua el programa p a la cua de prioritat del processador. */
void Processador::encuaPrograma(Programa& p)
{
	PROGRAMES.push(p);
};

/* POST: executa t unitats de temps (instruccions)
         del programa amb més prioritat */
void Processador::executa (int t)
{
	int passos_proc = 0;
	
	Programa p;
	int status_p = 0;
	while (passos_proc < t and not PROGRAMES.empty()) 
	{
		p = PROGRAMES.front();
		PROGRAMES.pop();
		
		cout << "PROC: " << _id << " CARREGA " << p.id() << " PRIORITAT " << p.prioritat() << endl;

		int passos_prog = 0;
		status_p = 0;

		while (0 <= status_p and passos_proc < t) 
		{
			status_p = p.executa();
			++passos_prog;
			++passos_proc;
		}

		cout << "PROC: " << _id << " EXECUTAT " << passos_prog << " PASSOS: " << passos_proc << " de " << t;
		cout << " STATUS " << status_p << endl;
		if (status_p < 0) p.escriuDispositiu(cout);
	}
	
	if (passos_proc == t and status_p == 0)
	{
		int nova_prio = p.prioritat();
		nova_prio -= 10;
		if (nova_prio < 0) nova_prio = 0;

		cout << "PROGRAMA " << p.id() << " PRIORITAT " << p.prioritat() << " a " << nova_prio << endl;

		p.prioritat(nova_prio);
		PROGRAMES.push(p);
	}
};

/*************************************************************/
/*           l'operador >> ja està implementat               */
/*************************************************************/

ostream& operator<<(ostream& os, const Processador& p) 
{
	os << "PROCESSADOR: " << p._id << " #PROG: " << p.PROGRAMES.size() << endl;

	Queue<Programa> 	copia = p.PROGRAMES;

	while (not copia.empty())
	{
		Programa prog = copia.front();	
		copia.pop();
		os << prog.status() << endl;
	}

	return os;
};

