#ifndef SYMBOL_H
#define SYMBOL_H

#include "queuear.h"

class Symbol{
public:
	// Construtor que cria um símbolo vazio.
	Symbol (void){
		symbol = "";
		isOpnd = true;
		column = -1;
	}
	
	// Construtor da classe Symbol.
	Symbol (std::string *_symbol, bool *_isOpnd, int *_column){
		symbol = _symbol;
		isOpnd = _isOpnd;
		column = _column;
	}
	
	// Retorna se o símbolo é operando ou não.
	bool isOperand (std::string *_symbol){
		return _symbol == "+" || "-" || "." || "/";
	}
	
	// Conversão do símbolo em inteiro. Retorna o valor.
	int getValue (void){
		// Converter aqui.
		return symbol;
	}

	// Retorna o operador.
	std::string getOperator (void){
		return symbol;
	}
	
	// Retorna a coluna do operador.
	int getColumn (void){
		return column;
	}
	
private:
	std::string symbol; // String para armazenar o símbolo.
	bool isOpnd; // Variável para indicar se é operando (verdadeiro) ou operador (falso).
	int column; // Variável para indicar a coluna do símbolo.
};

#endif