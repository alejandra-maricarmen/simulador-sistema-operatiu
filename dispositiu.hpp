#ifndef DISPOSITIU_HPP
#define DISPOSITIU_HPP

#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <cassert>
#include <deque>

using namespace std;

/// INVARIANT DE LA CLASSE:

/// ------------------------------------------------------
///  Declaració operacions tipus Dispositiu
/// ------------------------------------------------------


class Dispositiu
{

	private:
		deque<int> cua;
		int _id;
		int _capacitat;

	public:

		Dispositiu						();							
		Dispositiu						(int,int);					
		~Dispositiu						();							

		bool buit						() const;

		bool operator << 				(int);						
		bool operator >> 				(int&);						
		
		friend ostream& operator<<		(ostream&, const Dispositiu&);	
};

#endif
