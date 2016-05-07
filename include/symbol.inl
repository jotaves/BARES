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
	// Converter aqui.
	return 0;
}

std::string Symbol::getOperator (void){
	return symbol;
}

int Symbol::getColumn (void){
	return column;
}

/*bool Symbol::isOperand (std::string _symbol){
	return _symbol == "+" or _symbol == "-" or _symbol == "%" or _symbol == "*" or _symbol == "/" or _symbol == "^";
}

bool Symbol::isNumber (std::string _symbol){
	for (auto i(0u); i < _symbol.size(); i++){
		if (_symbol[i] > '0'-1 and _symbol[i] < '9'-1) continue;
		else return false;
	}
	return true;
}

bool Symbol::isWhiteSpace (std::string _symbol){
	return 0;
}*/