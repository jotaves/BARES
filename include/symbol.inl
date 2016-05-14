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

int Symbol::getColumn (void){
	return column;
}

bool Symbol::isOperator (){
	//return symbol == "+" or symbol == "-" or symbol == "%" or symbol == "*" or symbol == "/" or symbol == "^";
	return isOpnd;
}

bool Symbol::isOperand (){
	for (auto i(0u); i < symbol.size(); i++){
		if (symbol[i] > '0'-1 and symbol[i] < '9'-1) continue;
		else return false;
	}
	return true;
}

bool Symbol::isUnary (){
	return /*symbol == "+" or */symbol == "-";
}