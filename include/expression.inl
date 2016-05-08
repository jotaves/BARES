#include <string>

#include "symbol.h"


QueueAr <Symbol> Expression::Infx2Posfx (void){
	return expression;
}

void Expression::tokenize (){

	unsigned int foundParenthesis1 = 0;
	unsigned int foundParenthesis2 = 0;
	std::string onlyParenthesis = "";

	for (auto i(0u); i < origExpr.size(); i++){

		// Looking for final parenthesis and counting.
		if (origExpr[i] == ')'){
			foundParenthesis2++;			

			if (foundParenthesis2 > foundParenthesis1){
				// Envia a coluna e o código do erro. A função que receber vai escolher o que aparece primeiro.
				// Tipo: if (_col < _menorcol) _menorcol = _col; cod_error = _cod. 
				cout << "Mismatch ’)’: column " << i+1 << ".\n";
				break;
			}

			onlyParenthesis += ')';
			
			Symbol s (")", true, i);
			expression.enqueue(s);
			continue;
		}

		// Looking for initial parenthesis and counting.
		if (origExpr[i] == '('){
			//cout << "Initial parenthesis found!\n";		
			foundParenthesis1++;

			onlyParenthesis += '(';

			auto j(0u);
			bool notFoundPar = true;
			while (j < onlyParenthesis.size()*onlyParenthesis.size()){
				if (onlyParenthesis[j] == '(' and onlyParenthesis[j+1] == ')'){
					delete onlyParenthesis[j];
					delete onlyParenthesis[j+1];
				}
				j++;
			}
			j=0;
			while (onlyParenthesis[j] != '('){
				j++;
			}

			Symbol s ("(", true, i);
			expression.enqueue(s);

			//cout << "Found: " << foundParenthesis << "\n";
			continue;
		}

		/*
		// Se chegar no final da string e o saldo de parênteses for positivo. Se não, continua.
		if (foundParenthesis > 0 and i+1 == origExpr.size()){
			// j contará a posição do do parêntese que precisa ser fechado.
			auto j(0);
			while(foundParenthesis != 0){ // Enquanto o saldo de parênteses for menor que 0.
				if (origExpr[j] == '('){
					foundParenthesis--; // Se encontrar um parênteses, diminui o saldo.
				}
				j++;
			}
			cout << "Missing closing ‘)’ to match opening ‘(’ at: column " << j << "\n";
			break;
		}*/

		// Looking for white space.
		if (origExpr[i] == ' '){
			//cout << "White space found!\n";
			continue; // Ignore it.
		}

		// Looking for operators.
		if (origExpr[i] == '+' or origExpr[i] == '-' or origExpr[i] == '%' or origExpr[i] == '*' or origExpr[i] == '/' or origExpr[i] == '^' ){
			//cout << "Operator found!\n";
			std::string oper = "";
			oper += origExpr[i];
			Symbol s (oper, true, i);
			expression.enqueue(s);			
			continue;
		}

		// Looking for numbers.
		if (origExpr[i] > '0'-1 and origExpr[i] < '9'+1){
			std::string number = "";
			// Prestar atenção aqui. Possível bug após o fim do while.
			while (origExpr[i] > '0'-1 and origExpr[i] < '9'+1){
				number += origExpr[i];
				//cout << number << "\n";
				i++;
			}

			Symbol s (number, false, i);
			expression.enqueue(s);

			i--; // Para não pular o próximo elemento, já que while só termina quando o elemento não for número.

			//cout << "Number found!\n";
			continue;
		}
	}
	cout << onlyParenthesis << "\n";
}