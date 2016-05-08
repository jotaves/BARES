#include <string>

#include "symbol.h"


QueueAr <Symbol> Expression::Infx2Posfx (void){
	return expression;
}

void Expression::tokenize (){

	int foundParenthesis = 0;
	unsigned int lastParenthesis1 = 0;
	unsigned int lastParenthesis2 = 0;
	unsigned int ant = 0;


	for (auto i(0u); i < origExpr.size(); i++){
		// Looking for final parenthesis and counting.
		if (origExpr[i] == ')'){
			//cout << "Final parenthesis found!\n";
			foundParenthesis--;
			lastParenthesis1 = i;

			Symbol s (")", true, i);
			expression.enqueue(s);

			if (i+1 != origExpr.size()) continue; // Se não for o último elemento da string, continua.
		}

		// Looking for initial parenthesis and counting.
		if (origExpr[i] == '('){
			//cout << "Initial parenthesis found!\n";
			ant = lastParenthesis2;
			lastParenthesis2 = i;			
			foundParenthesis++;

			Symbol s ("(", true, i);
			expression.enqueue(s);

			//cout << "Found: " << foundParenthesis << "\n";
			if (i+1 != origExpr.size()) continue; // Se não for o último elemento da string, continua.
		}

		// Se chegar no final da string e o saldo de parênteses for negativo. Se não, continua.
		if (foundParenthesis < 0 and i+1 == origExpr.size()){
			cout << "Mismatch ’)’: column " << lastParenthesis1+1 << ".\n";
			break;
		}		
		
		// Se chegar no final da string e o saldo de parênteses for positivo. Se não, continua.
		if (foundParenthesis > 0 and i+1 == origExpr.size()){
			cout << "Missing closing ‘)’ to match opening ‘(’ at: column " << ant+1 << "\n";
			break;
		}

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
}