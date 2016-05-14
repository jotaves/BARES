#include <string>

#include "symbol.h"


QueueAr <Symbol> Expression::Infx2Posfx (void){
	return expression;
}

void Expression::tokenize (void){

	unsigned int foundParenthesis1 = 0;
	unsigned int foundParenthesis2 = 0;
	int lastWas = -1; // 0 if operand, 1 if operator

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

	for (auto i(0u); i < origExpr.size(); i++){

		// Looking for final parenthesis and counting.
		if (origExpr[i] == ')'){
			foundParenthesis2++;			

			if (foundParenthesis2 > foundParenthesis1){
				// Envia a coluna e o código do erro. A função que receber vai escolher o que aparece primeiro.
				// Tipo: if (_col < _menorcol) _menorcol = _col; cod_error = _cod. 
				//cout << "Mismatch ’)’: column " << i+1 << ".\n";
				addError(i+1, 5);
				break;
			}
			
			Symbol s (")", true, i);
			expression.enqueue(s);
			noSpace += ")";
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

			Symbol s ("(", true, i);
			expression.enqueue(s);
			noSpace += "(";
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
			if (origExpr[i] == '-'){
				if (lastWas == 1 or lastWas == -1){
					origExpr[i] = '@';
				}
			}

			if((lastWas == 1 or lastWas == -1) and origExpr[i] != '@'){
				addError(i+1, 6);
				break;
			}
			if (i == origExpr.size()-1 and (lastWas == 1 or lastWas == -1)){
				addError(i+1, 6);
				break;
			}
			if (i == origExpr.size()-1 and lastWas == 0){
				addError(origExpr.size()+1, 2);
				break;
			}
			//cout << "Operator found!\n";
			std::string oper = "";
			// Resolver erro de operando inválido depois q passar pra classe.
			oper += origExpr[i];
			Symbol s (oper, true, i);
			expression.enqueue(s);
			noSpace += oper;
			lastWas = 1;
			continue;
		}

		// Looking for numbers.
		if (origExpr[i] > '0'-1 and origExpr[i] < '9'+1){
			if(lastWas == 0){
				addError(i+1, 4);
				break;
			}			
			std::string number = "";
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
			noSpace += number;

			i--; // Para não pular o próximo elemento, já que while só termina quando o elemento não for número.
			lastWas = 0;
			//cout << "Number found!\n";
			continue;
		}
		/*
		if(i == 0 and lastWas == 1){
			addError(i+1, 6);
			break;
		}*/
		if(lastWas == 1){
			addError(i+1, 2);
			break;
		}
		if(lastWas == 0){
			addError(i+1, 3);
			break;
		}
	}
	//cout << "Final: " << noSpace << "\n";
	//cout << onlyParenthesis << "\n";
	printqueue();
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
		cout << "E" << code << " " << column << "\n";
	}
	else{
		cout << "Calculando!";
	}
}

void verify (void){
/*	QueueAr <Symbol> expression;
	if (expression.getFront()==)
*/
}