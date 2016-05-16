// g++ -Wall -std=c++11 src/bares_drive.cpp -o bin/bares -I include/
// ./bin/bares data/entrada9.txt

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "expression.h"
#include "symbol.h"

using namespace std;

int main(int argc, char * argv[]){
	// LEITURA DE ENTRADA E SAÍDA
	std::string entrada/*, saida*/;
	if (argc == 2){
        std::stringstream (argv[1]) >> entrada;
        //std::stringstream (argv[2]) >> saida;
    }
    else{
        cout << ">>> Error. Try calling $ ./bin/bares [input filename]\n";
        return 0;
    }

    // PEGAR CONTEÚDO DO ARQUIVO
    std::ifstream file;
    std::string line;

    file.open (entrada);
    if (file.is_open()){
        while (!file.eof()){
        	getline (file, line);
            Expression e (line);
            e.calculate();
        }
    }else{
        cout << ">>> Input file wasn't found. Try again.\n";
    }
    return 0;
}