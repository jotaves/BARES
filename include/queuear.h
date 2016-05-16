/**
 *  @file queuear.h
 *  @brief Cabecalho da classe QueueAr (fila)
 */

#ifndef QUEUEAR_H
#define QUEUEAR_H

#include <iostream>

using namespace std;

/**Classe interface fila (nao pode ser instanciada). */
template < class Object >
class QueueAr {
	public:
		/**
		* @brief Construtor da fila
		*/
		QueueAr ( int );

		/**
		* @brief Destrutor da fila
		*/
		~QueueAr( void );

	    /**
	     * @brief Adiciona um elemento na fila
	     * @param x Elemento a ser adicionado na fila
	     */
		void enqueue ( const Object & x );

		/**
		* @brief Retira um elemento da fila
		* @return Elemento retirado da fila
		*/
		Object dequeue ( void );

		/**
		* @brief Retorna o elemento que esta frente da fila
		* @return Primeiro elemento da fila
		*/
		Object getFront ( void ) const;

		/**
		* @brief Retorna se a fila esta vazia
		* @return Verdadeiro se estiver vazia, falso se não estiver
		*/
		bool isEmpty ( void ) const;

		/**
		* @brief Esvazia a fila
		*/
		void makeEmpty ( void );
        
        /*inline friend std::ostream &operator<< (std::ostream& _os, const QueueAr<Object>& _oList )
        {
        	if ( _oList.back == -1 ) { _os << "[ ]"; return _os; } // olocar erro.
        	if ( _oList.back >= _oList.front ){
            _os << "[";
	            for( int i(_oList.front) ; i <= _oList.back ; ++i )
	                _os << _oList.P[ i ];
	            _os << "]";
	            return _os;        		
        	}

        	else{ //_oList.front > _oList.back
	            _os << "[";

	            for( int i(_oList.front) ; i < _oList.capacity ; ++i )
	                _os << _oList.P[ i ];

	            for( int i(0) ; i <= _oList.back ; ++i )
	                _os << _oList.P[ i ];
	            _os << "]";

	            return _os;
        	}
        	return _os;
        }*/

	private:
		/** Aumenta a capacidade da fila de acordo com a necessidade */
		void resize();

		/** Ponteiro para um Object */
		Object *P;
		
		/** Armazena a capacidade da fila */
		int capacity;
		
		/** Armazena a posição do primeiro elemento da fila */
		int front;
		
		/** Armazena a posição do último elemento da fila */
		int back;
};

#include "queuear.inl"

#endif