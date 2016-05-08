#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "queuear.h"
#include "symbol.h"

#include <iostream>

class Expression{
public:
	Expression (std::string _expression){
		origExpr = _expression;
	}
	// Converte de infixo para posfixo.
	QueueAr <Symbol> Infx2Posfx (void);

	// Tokeniza a expressão.
	void tokenize ();

	// Imprimir a fila de símbolos feita.
	void printqueue(){
		cout << expression;
	}

private:
	// String para guardar a expressão original.
	std::string origExpr;
	// Guarga a expressão em uma fila de símbolos.
	QueueAr <Symbol> expression;
};

#include "expression.inl"

#endif