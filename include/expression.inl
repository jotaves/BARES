#include <string>

#include "symbol.h"


QueueAr <Symbol> Expression::Infx2Posfx (void){
	return expression;
}

void Expression::tokenize (){

	unsigned int foundParenthesis1 = 0;
	unsigned int foundParenthesis2 = 0;


	for (auto i(0u); i < origExpr.size(); i++){

		// Looking for final parenthesis and counting.
		if (origExpr[i] == ')'){
			foundParenthesis2++;			

			if (foundParenthesis2 > foundParenthesis1){
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

			// Quando um '(' for encontrado, será feita uma varredura por ')' correspondentes.
			// Se for encontrado mais '(' que ')', o processo é parado e é retornado onde deve-se fechar o parênteses.
			// 
			auto j(0u);
			auto countp1(0);
			auto countp2(0);
			auto lastp1(0u);
			auto lastp2(0u);

			while(j < origExpr.size()){
				if (origExpr[j] == '('){
					countp1++;
					lastp1 = j;
				}
				if (origExpr[j] == ')'){
					countp2++;
					lastp2 = j;
				}
				j++;
			}

			auto pmissing(0);
			if (countp1 > countp2){ // Se tiver mais '(' que ')' na expressão
				
				if (countp2 == 0){ // Se não tiver ')' na expressão, retorna a posição do parênteses a ser fechado (o último que foi aberto).
					cout <<	"Missing closing ')' to match opening '(' at: column " << lastp1+1 << ".\n";
					break;
				}

				// Se tiver um ou mais ')' na expressão, fará o processo abaixo
				j = lastp2; // j recebe a posição do último ')'
				while(countp2 != 0){ // Enquanto o contador de ')' não zerar, vai procurando por '(' correspondentes.
					if (origExpr[j] == '('){
						pmissing = j;
						countp2--;
					}
					j--;
				}

				if (pmissing == 0){ // Se pmissing == 0, significa que tem outros '(' na frente, pois o número de '(' antes do último ')' é a mesma quantidade do total de ')' na expressão. Logo o último parêntese aberto deve ser o primeiro a ser fechado.
					cout <<	"Missing closing ')' to match opening '(' at: column " << lastp1+1 << ".\n";
					break;
				}

				// Caso countp1 > countp2 do último ')' para o início, então dirá a posição do parêntese que falta.
				cout <<	"Missing closing ')' to match opening '(' at: column " << pmissing << ".\n";	
				break;				
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
}