
/// -----------------------------------------
///
///  	Implementació classe Dispositiu
///
/// -----------------------------------------

#include "dispositiu.hpp"

Dispositiu::Dispositiu()
{
};

Dispositiu::Dispositiu(int i, int c)
{
	_id = i;
	_capacitat = c;
};

Dispositiu::~Dispositiu()
{	
};

bool Dispositiu::buit() const
{
	return cua.empty();
};

bool Dispositiu::operator << (int i)
{
	bool dispositiu_afegir = false;

	if (cua.size() < _capacitat) 
	{
		cua.push_back(i);
		dispositiu_afegir = true;
	}
	
	return dispositiu_afegir;
};

bool Dispositiu::operator >> (int& i)
{
	bool dispositiu_treu = false;

	if (not cua.empty()) 
	{
		i = cua.front();
		cua.pop_front();
		dispositiu_treu = true;
	}

	return dispositiu_treu;
};

ostream& operator<<(ostream& os, const Dispositiu& d) 
{
	os << "DISPOSITIU_ID: " << d._id << " : ";
	
	deque<int>::const_iterator it = d.cua.begin();
	
	while (it != d.cua.end())
	{
		os << *it << " ";
		it++;
	}
	
	return os;
};