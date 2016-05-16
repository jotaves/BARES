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

	// Imprimir a fila de símbolos feita.
	void printqueue(){
		cout << expression << "\n";
	}

	void calculate();

private:
	int AvalPosfix();	
	// Converte de infixo para posfixo.
	void Infx2Posfx (void);

	// Retorna a precedência de um símbolo.
	int prcd(Symbol);
	// Tokeniza a expressão.
	void tokenize (void);
	// Compara se um erro da expressão aparece primeiro que outro. Se sim, possui prioridade e substitui o erro.
	void addError (const int _col, const int _code);
	// Retorna o primeiro erro na expressão.
	int firstError (int &);	
	int errorCode = -1;
	int col = -1;
	// String para guardar a expressão original.
	std::string origExpr;
	// String para guardar a expressão sem espaços entre os valores.
	std::string noSpace = "";
	// Guarga a expressão em uma fila de símbolos.
	QueueAr <Symbol> expression;
	QueueAr <Symbol> posfixExpression;
};

#include "expression.inl"

#endif