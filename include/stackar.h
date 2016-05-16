#ifndef STACKAR_H
#define STACKAR_H
//#include "AbsStack.h" // Inclui a interface abstrata da pilha .

#include <iostream>
using namespace std;

// Implementando interface via herança
template < typename Object >
class StackAr {
	public:
		StackAr( int );
		~StackAr( void );

		void push ( const Object & );
		Object pop ( void );
		Object top ( void ) const;
		bool isEmpty ( void ) const;
		void makeEmpty ( void );

        inline friend std::ostream &operator<< (std::ostream& _os, const StackAr<Object>& _oList )
        {
            _os << "[ ";
            for( int i(0) ; i < _oList.topo ; ++i )
                _os << "{" << _oList.P[ i ] << "} ";
            _os << "]";
            return _os;
        }

	private:
		Object *P;
		int topo;
		int capacity;	
};

#include "stackar.inl"

#endif