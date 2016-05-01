#ifndef QUEUEAR_H
#define QUEUEAR_H

#include <iostream>
//#include "AbsQueue.h"

using namespace std;

/**Classe interface fila (não pode ser instanciada!). */
template < class Object >
class QueueAr {
	public:
		QueueAr ( int );// Default constructor
		~QueueAr( void ); // Default destructor

		// Basic members
		void enqueue ( const Object & x );
		Object dequeue ( void );
		Object getFront ( void ) const;
		bool isEmpty ( void ) const;
		void makeEmpty ( void );
        
        /*inline friend std::ostream &operator<< (std::ostream& _os, const QueueAr<Object>& _oList )
        {
        	if ( _oList.back == -1 ) { _os << "[ ]"; return _os; } // olocar erro.
        	if ( _oList.back >= _oList.front ){
            _os << "[ ";
	            for( int i(_oList.front) ; i <= _oList.back ; ++i )
	                _os << "{" << _oList.P[ i ] << "} ";
	            _os << "]";
	            return _os;        		
        	}

        	else{ //_oList.front > _oList.back
	            _os << "[ ";

	            for( int i(_oList.front) ; i < _oList.capacity ; ++i )
	                _os << "{" << _oList.P[ i ] << "} ";

	            for( int i(0) ; i <= _oList.back ; ++i )
	                _os << "{" << _oList.P[ i ] << "} ";
	            _os << "]";

	            return _os;
        	}
        	return _os;
        }*/

	private:
		void resize();
		Object *P;
		int capacity;
		int front;
		int back;
};

#include "queuear.inl"

#endif