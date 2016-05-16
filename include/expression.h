#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "queuear.h"
#include "symbol.h"

#include <iostream>

class Expression{
public:
	/**
	* @brief Construtor da classe Expression
	* @param _expression String com a expressao original
	*/
	Expression (std::string _expression){
		origExpr = _expression;
	}

	/**
	* @brief Calcula o resultado de uma expressao
	* Essa funcao coordena as funcoes de tokenizar, converter, avaliar e visualizar erros na expressao.
	* Por fim, exibe-a no terminal.
	*/
	void calculate();

	/*void printqueue(){
		cout << expression << "\n";
	}*/

private:
	/**
	* @brief Analisa expressao posfixa e retorna o resultado
	* @return Resultado da expressao
	*/
	int AvalPosfix(void);

	/**
	* @brief Converte uma expressao do formato infixo para o posfixo
	*/
	void Infx2Posfx (void);
	
	/**
	* @brief Retorna a precedencia de um simbolo
	* @return Precedencia do simbolo
	* @param a Objeto Symbol 
	*/
	int prcd(Symbol a);
	
	/**
	* @brief Tokeniza uma expressao
	*/
	void tokenize (void);
	
	/**
	* @brief Adiciona um erro de uma expressao
	* Compara se um erro da expressao aparece primeiro que outro. Se sim, o substitui.
	* @param _col Coluna em que aparece o erro
	* @param _code Codigo do erro
	*/
	void addError (const int _col, const int _code);
	
	/**
	* @brief Retorna o primeiro erro na expressao.
	* @param column Passa por parametro a coluna do erro
	* @return Codigo do erro
	*/
	int firstError (int & column);	
	
	/** Armazena o erro do codigo. -1 se nao houver erro. */
	int errorCode = -1;
	
	/** Armazena a coluna do erro. -1 se nao houver erro. */
	int col = -1;

	/** String para guardar a expressao original. */
	std::string origExpr;
	
	/** Guarga a expressao em uma fila de simbolos no formato infixo. */
	QueueAr <Symbol> expression;
	
	/** Armazena a expressao em uma fila se simbolos no formato posfixo. */
	QueueAr <Symbol> posfixExpression;
};

#include "expression.inl"

#endif