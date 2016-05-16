/**
 *  @file symbol.h
 *  @brief Cabecalho da classe Symbol
 */

#ifndef SYMBOL_H
#define SYMBOL_H

class Symbol{
public:
	/** 
	* @brief Construtor que cria um simbolo vazio
	*/
	Symbol (void);
	
	/**
	* @brief Construtor da classe Symbol
	* @param _symbol Simbolo
	* @param _isOpnd Verdadeiro se for operador, falso se for operando
	* @param _column Coluna do simbolo
	*/
	Symbol (std::string, bool, int);
	
	/**
	* @brief Retorna se o simbolo eh operador ou nao
	* @return Verdadeiro se for operador, falso se nao
	*/
	bool isOperator ();

	/**
	* @brief Converte um numero em um valor inteiro
	* @return Valor inteiro
	*/
	int getValue (void);

	/**
	* @brief Retorna o operador
	* @return Operador
	*/
	std::string getOperator (void);

    /*inline friend std::ostream &operator<< (std::ostream& _os, const Symbol& _oList )
    {
        _os << _oList.symbol;
        return _os;
    }*/
	
private:
	/** String para armazenar o simbolo */
	std::string symbol = "";

	/** Variavel para indicar se eh operando (verdadeiro) ou operador (falso) */
	bool isOpnd;

	/** Variavel para indicar a coluna do simbolo */
	int column;
};

#include "symbol.inl"

#endif