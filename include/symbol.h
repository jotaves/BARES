#ifndef SYMBOL_H
#define SYMBOL_H

class Symbol{
public:
	// Construtor que cria um símbolo vazio.
	Symbol (void);
	
	// Construtor da classe Symbol.
	Symbol (std::string, bool, int);
	
	/*
	// Retorna se o símbolo é operando ou não.
	bool isOperand (std::string);

	// Retorna se o símbolo é número ou não.
	bool isNumber (std::string);

	// Retorna se o símbolo é espaço em branco ou não.
	bool isWhiteSpace (std::string _symbol);
	*/

	// Conversão do símbolo em inteiro. Retorna o valor.
	int getValue (void);

	// Retorna o operador.
	std::string getOperator (void);
	
	// Retorna a coluna do operador.
	int getColumn (void);
	
private:
	// String para armazenar o símbolo.
	std::string symbol;

	// Variável para indicar se é operando (verdadeiro) ou operador (falso).
	bool isOpnd;

	// Variável para indicar a coluna do símbolo.
	int column;
};

#include "symbol.inl"

#endif