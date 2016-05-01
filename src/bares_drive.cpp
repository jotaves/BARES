// g++ -Wall -std=c++11 src/bares_drive.cpp -o bin/bares
// ./bin/bares 
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "stackar.h"
#include "queuear.h"

using namespace std;

int main(int argc, char * argv[]){
	
	// LEITURA DE ENTRADA E SAÍDA
	std::string entrada, saida;
	if (argc > 2 && argc < 4)
    {
        std::stringstream (argv[1]) >> entrada;
        std::stringstream (argv[2]) >> saida;
    }
    else
    {
        cout << ">>> Error.\n";
    }

    //cout << entrada << " " << saida << "\n";

    //PEGAR CONTEÚDO DO ARQUIVO
    ifstream file;
    string line;

    file.open (entrada);

    while (!file.eof()){
    	getline (file, line);
    	cout << line << "\n";
    }

    return 0;
}