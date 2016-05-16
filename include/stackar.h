#ifndef STACKAR_H
#define STACKAR_H

#include <iostream>
using namespace std;

template < typename Object >
class StackAr {
public:
	/**
	* @brief Construtor da classe
	* @param _size Tamanho da pilha 
	*/	
	StackAr( int );

	/**
	* @brief Destrutor da classe
	*/	
	~StackAr( void );

	/**
	* @brief Adiciona um elemento a pilha
	* @param _x Elemento a ser adicionado
	*/
	void push ( const Object & );

	/**
	* @brief Retira elemento da pilha
	* @return Elemento retirado
	*/
	Object pop ( void );

	/**
	* @brief Retorna elemento no topo da pilha
	* @return Elemento no topo da pilha
	*/	
	Object top ( void ) const;

	/**
	* @brief Retorna se a pilha esta vazia
	* @return Verdadeiro se estiver vazia, falso se nao estiver
	*/		
	bool isEmpty ( void ) const;
	
	/**
	* @brief Esvazia a pilha
	*/		
	void makeEmpty ( void );

	/*inline friend std::ostream &operator<< (std::ostream& _os, const StackAr<Object>& _oList )
    {
        _os << "[ ";
        for( int i(0) ; i < _oList.topo ; ++i )
            _os << "{" << _oList.P[ i ] << "} ";
        _os << "]";
        return _os;
    }*/

private:
	/** Ponteiro para Object */
	Object *P;

	/** Armazena posicao do elemento do topo da pilha */
	int topo;
	
	/** Armazena a capacidade da pilha */
	int capacity;	
};

#include "stackar.inl"

#endif