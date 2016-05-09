#include <string>

#include "symbol.h"


QueueAr <Symbol> Expression::Infx2Posfx (void){
	return expression;
}

void Expression::tokenize (){

	unsigned int foundParenthesis1 = 0;
	unsigned int foundParenthesis2 = 0;
	
	// LOOKING FOR '(' ERRORS
	std::string onlyParenthesis = origExpr;
	// Substitui '(' por '1' e ')' por '(', assim, se sobrar algum no final, haverá erro.
	if (onlyParenthesis.size()>0){
		for (auto j(onlyParenthesis.size()-1); j > 0; j--){
			if(onlyParenthesis[j] == ')'){
				onlyParenthesis[j] = '1';
				for(int k(j-1); k >= 0; k--){
					if(onlyParenthesis[k] == '('){
						onlyParenthesis[k] = '2';
						j = onlyParenthesis.size()-1;
						break;
					}
				}
			}
		}
		for(auto i(0u); i < onlyParenthesis.size(); i++){
			if(onlyParenthesis[i] == '('){
				cout << "Missing closing ‘)’ to match opening ‘(’ at: column " << i+1 << "\n";
				return;
			}
		}
	}

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
			
			Symbol s (")", true, i);
			expression.enqueue(s);
			continue;
		}

		// Looking for initial parenthesis and counting.
		if (origExpr[i] == '('){
			//cout << "Initial parenthesis found!\n";		
			
			foundParenthesis1++;

			Symbol s ("(", true, i);
			expression.enqueue(s);

			//cout << "Found: " << foundParenthesis << "\n";
			continue;
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
	//cout << onlyParenthesis << "\n";
}