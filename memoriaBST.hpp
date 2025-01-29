#ifndef MEMORIA_HPP
#define MEMORIA_HPP

#include <cassert>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

#include "BST.hpp"

/// ------------------------------------------------------
///  Declaració operacions tipus Memoria
/// ------------------------------------------------------

class Memoria
{
	public:

		Memoria						();								/**/
		Memoria						(const Memoria &);				/**/
		~Memoria					();								/**/

		void 						set(const string&, int);		/**/
		int 						get (const string&);			/**/
		
		Memoria& operator=			(const Memoria&);				/**/
		
		friend ostream& operator<<	(ostream&, const Memoria&);		/*!!*/

	private:
	
		struct TUPLA
		{
			string clau;
			int valor;

			// Operadors de comparació per a TUPLA
			bool operator<(const TUPLA& t) const {
				return clau < t.clau;
			}
			bool operator>(const TUPLA& t) const {
				return clau > t.clau;
			}
			bool operator==(const TUPLA& t) const {
				return clau == t.clau;
			}

			// Operador d'inserció per a TUPLA
			friend ostream& operator<<(ostream& os, const TUPLA& t) {
				os << t.clau << ": " << t.valor;
				return os;
			}
		};

		BST<Memoria::TUPLA> 						memoria;
		
};

#endif
