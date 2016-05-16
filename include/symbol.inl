#include <string>

Symbol::Symbol (void){
	symbol = "";
	isOpnd = true;
	column = -1;
}

Symbol::Symbol (std::string _symbol, bool _isOpnd, int _column){
	symbol = _symbol;
	isOpnd = _isOpnd;
	column = _column;
}

int Symbol::getValue (void){
	int number = std::stoi(symbol, 0);
	return number;
}

std::string Symbol::getOperator (void){
	return symbol;
}

bool Symbol::isOperator (){
	//return symbol == "+" or symbol == "-" or symbol == "%" or symbol == "*" or symbol == "/" or symbol == "^";
	return isOpnd;
}