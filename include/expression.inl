#include <string>
#include <cmath>
#include "stackar.h"
#include "queuear.h"
#include "symbol.h"

int Expression::AvalPosfix(){
	Symbol symb;
	StackAr <int> stackint;
	int opnd1, opnd2;
	int result = 0;

	while(!posfixExpression.isEmpty()){
		symb = posfixExpression.dequeue();
		if (!symb.isOperator()){
			//cout << symb.getValue() << "\n";
			stackint.push(symb.getValue());
		}
		else{
			opnd2 = stackint.pop();
			opnd1 = stackint.pop();
			//cout << opnd1 << " " << symb.getOperator() << " " << opnd2 << " = ";

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
		//cout << stackint.top() << "\n";
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
				//cout << stack << "\n";
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
			//cout << stack << "\n";

		}
	}
	while(!stack.isEmpty()){
		if (stack.top().getOperator() == "(" or stack.top().getOperator() == ")") stack.pop();
		else posfixExpression.enqueue(stack.pop());
	}
	//return posfixExpression;
	cout << "\nPosfix: " << posfixExpression << "\n";
	/*while(!posfixExpression.isEmpty()){
		cout << posfixExpression.dequeue();
	}*/
}

void Expression::tokenize (void){
	unsigned int foundParenthesis1 = 0; // Counting opening parenthesis
	unsigned int foundParenthesis2 = 0; // Counting closing parenthesis
	unsigned int foundParenthesis = 0;
	unsigned int foundUnary = 0;
	bool hasNumbers = 0;
	int lastWas = -1; // 0 if operand, 1 if operator

	for (auto i(0u); i < origExpr.size(); i++){

		// Looking for final parenthesis and counting.
		if (origExpr[i] == ')'){
			if (foundParenthesis != 0 and hasNumbers == 0){
					addError(i+1, 2);
					break;
			}else hasNumbers = 0, foundParenthesis = 0;
			foundParenthesis2++;
			//foundParenthesis++;		

			if (foundParenthesis2 > foundParenthesis1){
				// Envia a coluna e o código do erro. A função que receber vai escolher o que aparece primeiro.
				// Tipo: if (_col < _menorcol) _menorcol = _col; cod_error = _cod. 
				//cout << "Mismatch ’)’: column " << i+1 << ".\n";
				addError(i+1, 5);
				break;
			}
			
			Symbol s (")", true, i);
			expression.enqueue(s);
			//lastWas = 0;
			continue;
		}

		// Looking for initial parenthesis and counting.
		if (origExpr[i] == '('){
			if(lastWas == 0){
				addError(i+1, 4);
				break;
			}
			//cout << "Initial parenthesis found!\n";		
			
			foundParenthesis1++;
			foundParenthesis++;

			Symbol s ("(", true, i);
			expression.enqueue(s);
			//cout << "Found: " << foundParenthesis << "\n";
			//lastWas = 0; // WARNING, I think it can generate a bug. Not sure if this line is necessary.
			continue;
		}

		// Looking for white space.
		if (origExpr[i] == ' '){
			//cout << "White space found!\n";
			continue; // Ignore it.
		}

		// Looking for operators (+/-)

		// Looking for operators.
		if (origExpr[i] == '+' or origExpr[i] == '-' or origExpr[i] == '%' or origExpr[i] == '*' or origExpr[i] == '/' or origExpr[i] == '^' ){
			// Se chegou no fim da expressão e apareceu um símbolo antes ou antes não tinha algo.
			if (i == origExpr.size()-1 and (lastWas == 1 or lastWas == -1)){
				addError(i+1, 6);
				break;
			}

			// Se chegou no fim da expressão e tem um número antes do sinal.
			if (i == origExpr.size()-1 and lastWas == 0){
				addError(origExpr.size()+1, 2);
				break;
			}		

			// Substituindo menos unários por @.
			if (origExpr[i] == '-'){
				if (lastWas == 1 or lastWas == -1){
					origExpr[i] = '@';
					foundUnary++;
					continue;
				}
			}

			// Se anteriormente apareceu um operador ou não apareceu algo e o símbolo atual não for unário.
			if((lastWas == 1 or lastWas == -1) and origExpr[i] != '@'){
				addError(i+1, 6);
				break;
			}

			//cout << "Operator found!\n";
			std::string oper = "";
			// Resolver erro de operando inválido depois q passar pra classe.
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
			/*if(i == origExpr.size()-1 and foundParenthesis != 0){
				addError(i+1, 4);
				break;
			}*/
			std::string number = "";			
			if(foundUnary != 0 and foundUnary%2 != 0){
				number += "-";
				foundUnary=0;
			}
			// Prestar atenção aqui. Possível bug após o fim do while.
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
			//cout << "Number found!\n";
			continue;
		}
		if(lastWas == -1){
			addError(i+1, 2);
			break;
		}

		if(lastWas == 1){
			addError(i+1, 2);
			break;
		}
		if(lastWas == 0){
			addError(i+1, 3);
			break;
		}
	}

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
						//j = onlyParenthesis.size()-1;
						break;
					}
				}
			}
		}
		for(auto i(0u); i < onlyParenthesis.size(); i++){
			if(onlyParenthesis[i] == '('){
				//cout << "Missing closing ‘)’ to match opening ‘(’ at: column " << i+1 << "\n";
				addError(i+1, 7);
				return;
			}
		}
	}	
	//cout << onlyParenthesis << "\n";
	//printqueue();
}


//CRIAR UMA CLASSE PARA ERRORS DEPOIS
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
		//cout << ">>> " << origExpr << " = ";
		cout << "E" << code << " " << column << "\n";
	}
	else{
		if (expression.isEmpty()) {
			cout << "\n";
			return;
		}
		//cout << "Calculando?\n";
		cout << ">>> " << origExpr << " = ";
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
	//cout << "teste: " << a.getOperator() << "\n";
	if 		(c == "(") return 4;
	else if (c == ")") return 0;
	else if (c == "^") return 1;
	else if (c == "/") return 2;
	else if (c == "%") return 2;
	else if (c == "*") return 2;	
	else if (c == "+") return 3;
	else if (c == "-") return 3;
	else return EXIT_FAILURE;
}