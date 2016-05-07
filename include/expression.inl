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
			if (i+1 != origExpr.size()) continue; // Se não for o último elemento da string, continua.
		}

		// Looking for initial parenthesis and counting.
		if (origExpr[i] == '('){
			//cout << "Initial parenthesis found!\n";
			ant = lastParenthesis2;
			lastParenthesis2 = i;			
			foundParenthesis++;
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
			continue;
		}

		// Looking for numbers.
		if (origExpr[i] > '0'-1 and origExpr[i] < '9'+1){
			//cout << "Number found!\n";
			continue;
		}
	}
}