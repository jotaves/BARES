/**
 *  @file expression.inl
 *  @brief Implementacao da classe Expression
 */

#include <string>
#include <cmath>
#include "stackar.h"
#include "queuear.h"
#include "symbol.h"

int Expression::AvalPosfix(){
	Symbol symb;
	StackAr <int> stackint;
	int opnd1, opnd2;
	int result;

	while(!posfixExpression.isEmpty()){
		symb = posfixExpression.dequeue();
		if (!symb.isOperator()){
			stackint.push(symb.getValue());
		}
		else{
			opnd2 = stackint.pop();
			opnd1 = stackint.pop();

			if (symb.getOperator() == "+"){
				result = opnd1 + opnd2;
			}

			if (symb.getOperator() == "-"){
				result = opnd1 - opnd2;
			}

			if (symb.getOperator() == "/"){
				if (opnd2 == 0){
					addError(0, 8);
					return -1;
				}
				result = (opnd1 / opnd2);
			}

			if (symb.getOperator() == "*"){
				result = opnd1 * opnd2;
			}

			if (symb.getOperator() == "%"){
				if (opnd2 == 0){
					addError(0, 8);
					return -1;
				}				
				result = opnd1 % opnd2;
			}

			if (symb.getOperator() == "^"){
				result = std::pow (opnd1, opnd2);
			}
			stackint.push(result);
		}
	}
	result = stackint.pop();
	if (result > 32767 or result < -32768){
		addError(0, 9);
		return -1;
	}
	return result;
}

void Expression::Infx2Posfx (void){
	Symbol symb;
	StackAr <Symbol> stack;
	while(!expression.isEmpty()){
		symb = expression.dequeue();
		if (symb.isOperator() == false){
			posfixExpression.enqueue(symb);
		}
		else{
			if (symb.getOperator() == ")"){
				while(stack.top().getOperator() != "("){
					posfixExpression.enqueue (stack.pop());
				}
				stack.pop();
			}else{
				if (symb.getOperator() != "("){
					while(!stack.isEmpty() and prcd (stack.top()) <= prcd (symb)){
						if (prcd (stack.top()) <= prcd(symb)){
							if (stack.top().getOperator() == "(" or stack.top().getOperator() == ")") stack.pop();
							else posfixExpression.enqueue (stack.pop());
						}
					}
				}
				stack.push(symb);
			}
		}
	}
	while(!stack.isEmpty()){
		if (stack.top().getOperator() == "(" or stack.top().getOperator() == ")") stack.pop();
		else posfixExpression.enqueue(stack.pop());
	}
}

void Expression::tokenize (void){
	unsigned int foundParenthesis1 = 0; // Counting opening parenthesis
	unsigned int foundParenthesis2 = 0; // Counting closing parenthesis
	unsigned int foundUnary = 0; // True if found unary, false if not
	short int lastWas = -1; // 0 if operand, 1 if operator, -1 if none of them has appeared yet	
	bool foundParenthesis = 0; // True if found opening parenthesis
	bool hasNumbers = 0; // True if found numbers inside parenthesis

	for (auto i(0u); i < origExpr.size(); i++){
		// Looking for final parenthesis and counting.
		if (origExpr[i] == ')'){
			if(lastWas == 1){
				addError(i+1, 2);
				break;
			}	
			if (foundParenthesis != 0 and hasNumbers == 0){
				addError(i+1, 2);
				break;
			}else hasNumbers = 0, foundParenthesis = 0;
			
			foundParenthesis2++;

			if (foundParenthesis2 > foundParenthesis1){
				addError(i+1, 5);
				break;
			}
			
			Symbol s (")", true, i);
			expression.enqueue(s);
			continue;
		}

		// Looking for initial parenthesis and counting.
		if (origExpr[i] == '('){
			if(lastWas == 0){
				addError(i+1, 4);
				break;
			}		
			
			foundParenthesis1++;
			foundParenthesis++;

			Symbol s ("(", true, i);
			expression.enqueue(s);
			continue;
		}

		// Looking for white space.
		if (origExpr[i] == ' '){
			continue; // Ignoring white spaces.
		}

		// Looking for operators.
		if (origExpr[i] == '+' or origExpr[i] == '-' or origExpr[i] == '%' or origExpr[i] == '*' or origExpr[i] == '/' or origExpr[i] == '^' ){
			// If (1) It's the end of the expression and appeared an operator before; or (2) There was nothing before this operator.
			if (i == origExpr.size()-1 and (lastWas == 1 or lastWas == -1)){
				addError(i+1, 6);
				break;
			}

			// If it's the end of the expression and there's a number before the operator.
			if (i == origExpr.size()-1 and lastWas == 0){
				addError(origExpr.size()+1, 2);
				break;
			}		

			// Replacing unary minus with @.
			if (origExpr[i] == '-'){
				if (lastWas == 1 or lastWas == -1){
					origExpr[i] = '@';
					foundUnary++;
					continue;
				}
			}

			// If (1) There was an operator before or didn't appear something; and (2) The current symbol isn't unary.
			if((lastWas == 1 or lastWas == -1) and origExpr[i] != '@'){
				addError(i+1, 6);
				break;
			}

			std::string oper = "";
			oper += origExpr[i];
			Symbol s (oper, true, i);
			expression.enqueue(s);
			lastWas = 1;
			continue;
		}

		// Looking for numbers.
		if (origExpr[i] > '0'-1 and origExpr[i] < '9'+1){
			if (foundParenthesis != 0) hasNumbers = 1;
			if(lastWas == 0){
				addError(i+1, 4);
				break;
			}

			std::string number = "";			
			if(foundUnary != 0 and foundUnary%2 != 0){
				number += "-";
				foundUnary=0;
			}

			auto j(i); // Guarda a posição do primeiro número, em caso de erro.
			while (origExpr[i] > '0'-1 and origExpr[i] < '9'+1){
				number += origExpr[i];
				//cout << number << "\n";
				i++;
			}

			// Converte valor para int.
			int a = std::stoi(number, 0);

			// Vê se está dentro da faixa.
			if (a > 32767 or a < -32768){
				addError(j+1, 1);
				break;
			}

			Symbol s (number, false, i);
			expression.enqueue(s);

			i--; // Para não pular o próximo elemento, já que while só termina quando o elemento não for número.
			lastWas = 0;
			continue;
		}

		// If a symbol not listed was found.
		if(lastWas == -1){ // And there's nothing before.
			addError(i+1, 2);
			break;
		}

		if(lastWas == 1){ // And there's an operator before.
			addError(i+1, 2);
			break;
		}

		if(lastWas == 0){ // And there's a number before.
			addError(i+1, 3);
			break;
		}
	}

	// LOOKING FOR '(' ERRORS
	std::string onlyParenthesis = origExpr;
	// Percorre a expressão de trás para frente, substituindo ')' por '2' e o '(' correspondente por '1' (poderia ser qualquer outro símbolo).
	if (onlyParenthesis.size()>0){
		for (auto j(onlyParenthesis.size()-1); j > 0; j--){
			if(onlyParenthesis[j] == ')'){
				onlyParenthesis[j] = '2';
				for(int k(j-1); k >= 0; k--){
					if(onlyParenthesis[k] == '('){
						onlyParenthesis[k] = '1';
						break;
					}
				}
			}
		}

		// Looking for missing '('
		for(auto i(0u); i < onlyParenthesis.size(); i++){
			if(onlyParenthesis[i] == '('){
				addError(i+1, 7);
				return;
			}
		}
	}
}

void Expression::addError (const int _col, const int _code){
	if (col > _col or col == -1){
		errorCode = _code;
		col = _col;
	}
}

int Expression::firstError (int & column){
	if (col != -1) column = col;
	return errorCode;
}

void Expression::calculate (void){
	tokenize();
	int column;
	int code = firstError(column);
	if (code != -1){
		cout << "E" << code << " " << column << "\n";
	}
	else{
		if (expression.isEmpty()) {
			cout << "\n";
			return;
		}
		Infx2Posfx();
		int result = AvalPosfix();
		code = firstError(column);
		if (code != -1){
			cout << "E" << code << "\n";
		}
		else cout << result << "\n";
	}
}

int Expression::prcd(Symbol a){
	std::string c = a.getOperator();
	if (c == "^") 								return 1;
	else if (c == "/" or c == "%" or c == "*") 	return 2;	
	else if (c == "+" or c == "-") 				return 3;
	else if (c == "(") 							return 4;
	else 									   return -1;
}