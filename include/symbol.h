#ifndef SYMBOL_H
#define SYMBOL_H

class Symbol{
public:
	// Construtor que cria um símbolo vazio.
	Symbol (void);
	
	// Construtor da classe Symbol.
	Symbol (std::string, bool, int);
	
	// Retorna se o símbolo é operador ou não.
	bool isOperator ();

	// Retorna se o símbolo é operando ou não.
	bool isOperand ();

	// Retorna se o símbolo é um operador unário.
	bool isUnary();

	// Conversão do símbolo em inteiro. Retorna o valor.
	int getValue (void);

	// Retorna o operador.
	std::string getOperator (void);
	
	// Retorna a coluna do operador.
	int getColumn (void);

    inline friend std::ostream &operator<< (std::ostream& _os, const Symbol& _oList )
    {
        _os << _oList.symbol;
        return _os;
    }
	
private:
	// String para armazenar o símbolo.
	std::string symbol = "";

	// Variável para indicar se é operando (verdadeiro) ou operador (falso).
	bool isOpnd;

	// Variável para indicar a coluna do símbolo.
	int column;
};

#include "symbol.inl"

#endif