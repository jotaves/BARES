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

	// Imprimir a fila de símbolos feita.
	void printqueue(){
		cout << expression;
	}

	void calculate();

private:
	// Tokeniza a expressão.
	void tokenize (void);
	// Verifica problemas em uma expressão já tokenizada.
	void verify (void);
	// Compara se um erro da expressão aparece primeiro que outro. Se sim, possui prioridade e substitui o erro.
	void addError (const int _col, const int _code);
	// Retorna o primeiro erro na expressão.
	int firstError (int &);	
	int errorCode = -1;
	int col = -1;
	// String para guardar a expressão original.
	std::string origExpr;
	// Guarga a expressão em uma fila de símbolos.
	QueueAr <Symbol> expression;
};

#include "expression.inl"

#endif