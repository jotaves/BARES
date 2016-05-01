#include <stdexcept>

template < typename Object >
StackAr< Object >::StackAr( int _size = 10 ) : P(new Object[ _size ]), topo(0), capacity( _size ) 
{ /* Empty */}

template < typename Object >
StackAr< Object >::~StackAr( void ){
	delete [] P;
}

template < typename Object >
void StackAr< Object >::push ( const Object & _x ){
	if ( topo == capacity ) // Não há mais espaço.
		throw std::length_error( "[push()]: stack is full." );
	P[ topo++ ] = _x;	
}

template < typename Object >
Object StackAr< Object >::pop ( void ){
	if ( isEmpty() ) throw std::length_error( "[pop()]: stack size is 0." );
	return P[ --topo ];
}

template < typename Object >
Object StackAr< Object >::top ( void ) const{
	if ( isEmpty() ) throw std::length_error( "[top()]: stack size is 0." );
	return P[ topo-1 ];
}

template < typename Object >
bool StackAr< Object >::isEmpty ( void ) const{
	return topo == 0;
}

template < typename Object >
void StackAr< Object >::makeEmpty ( void ){
	topo = 0;
}