/**
 *  @mainpage Basic Arithmetic Expression Evaluator based on Stacks
 *  @author Carlos Vinicius Fernandes Rodrigues
 *  @author Joao Victor Bezerra Barboza
 *  @date 2016
 *  @version 1.0
 *
 *  @file bares_drive.cpp
 *  @brief Arquivo principal
 *
 *  Arquivo que eh compilado e executado.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "expression.h"
#include "symbol.h"

using namespace std;
/**
 *  @brief Main function
 * 
 *  Tal função é usada para executar o resto do código.
 */
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
