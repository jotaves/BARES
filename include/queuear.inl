#include "queuear.h"
#include <stdexcept>

template < typename Object >
QueueAr< Object >::QueueAr ( int _size = 10 ) : capacity( _size ), front( -1 ), back ( -1 ) {
	if ( _size < 1 ) throw length_error( "[QueueAr()]: invalid queue size.");
	P = new Object[_size];
}

template < typename Object >
QueueAr< Object >::~QueueAr( void ) {
	delete [] P;
}

template < typename Object >
void QueueAr< Object >::enqueue ( const Object & _x ){
	int _xPos = ( back+1 ) % capacity;
	if ( front == -1 && back == -1 ){
		front++, back++;
		P[ _xPos ] = _x;
	}
	else {
		// Se back for menor que front e a posição do próximo elemento a ser incluído for igual a front.
		if( back < front && _xPos == front ){
			cout << "Resizing (case 1)...\n";				
			resize();
			_xPos = ( back+1 ) % capacity;
		}
		else if ( back+1 == capacity && _xPos == front ){
			_xPos = capacity;
			cout << "Resizing (case 2)...\n";			
			resize();
			_xPos = ( back+1 ) % capacity;
		}
		P[ _xPos ] = _x;
		back = _xPos;
	}
}

template < typename Object >
Object QueueAr< Object >::dequeue ( void ){
	Object retrn = P[ front ];
	if( back == front ){
		retrn = P[front];
		back = front = -1;
		return retrn;
	}

	front = ( front + 1 ) % capacity;
	return retrn;
}

template < typename Object >
Object QueueAr< Object >::getFront ( void ) const{
	return P[front];
}

template < typename Object >
bool QueueAr< Object >::isEmpty ( void ) const{
	return front == -1 && back == -1;
}

template < typename Object >
void QueueAr< Object >::makeEmpty ( void ){
	front = back = -1;
	capacity = 1;
}

template < typename Object >
void QueueAr< Object >::resize( void ){
	Object *nQ = new Object[ (2*capacity)+1 ];
	if ( back < front ){
		auto i(0);
		auto j(front);
		while( j != capacity ){
			nQ[i]=P[j];
			i++;
			j++;
		}

		auto k(0);
		while( k <= back ){
			nQ[i]=P[k];
			i++;
			k++;
		}
	}
	else {
		auto i(0);
		auto k(back);
		while( k >= front ){
			nQ[i]=P[i];
			i++;
			k--;
		}
	}

	back = capacity-1;
	front = 0;
	capacity = (capacity*2)+1;
	delete [] P;
	P = nQ;
}