# BARES


## Sobre
A palavra "BARES" é uma abreviação para "Basic Arithmetic Expression Evaluator based on Stacks", a qual já diz muito por si só. É um algoritmo que recebe uma expressão com operações matemáticas, analisa o que foi dado, se hover erros o mesmo exibe-os (na ordem de entrada das operações, linha a linha) dando a coluna e código relacionado ao erro apresentado, caso contrário o mesmo exibe o resultado da operação solicitada.

## Como funciona
Para poder realizar as operações solicitadas, o código primeiramente "tokeniza" cada termo das expressões e os armazena em uma fila. Em seguida um algorítmo para passa os termos armazenados nessa fila da forma infixa para pósfixa, podendo assim tornar as contas mais facilmente realizáveis pelo computador além de retirar possíveis ambiguidades.
Com isso feito, uma stack é usada para auxiliar na realização dos calculos, armazenando os operamdos de acordo com as exigencias para um calculo correto na notação pósfixa.


## Limitações operacionais
O maior/menor valor expressável em um termo e no resultado da operação tem que estar entre -32768 e 32767.

###Os símbolos aceitos são:
	Parênteses:		--> ( ) <--> Bastante importante para a transformação de infixo para pósfixo.
	Adição:			-->  +  <-- 
	Subtração:		-->  -  <--
	Multiplicação:	-->  *  <--
	Divisão:		-->  /  <--
	Exponenciação:	-->  ^  <--
	Módulo:			-->  %  <--

###Erros detectáveis pelo código:
	1 --> Um dos operandos da expressão está fora da faixa permitida.
	2 --> Em alguma parte da expressão está faltando um operando ou existe algum operando em formato errado.
	3 --> Existe um símbolo correspondente a um operador que não está na lista de operadores válidos.
	4 --> Aparentemente o programa encontrou um símbolo extra “perdido” na expressão.
	5 --> Existe um parêntese fechando sem ter um parêntese abrindo correspondente.
	6 --> Apareceu um operador sem seus operandos.
	7 --> Está faltando um parêntese de fechamento ’)’ para um parêntese de abertura ‘(’ correspondente.
	8 --> Houve divisão cujo quociente é zero.
	9 --> Uma operação dentro de uma operação ou da expressão inteira estoura o limite das constantes numéricas definidas.

## Erros ou bugs
Nenhum caso de anormalidades foi detectado durantes os testes realizados na produção do código nem em sua execução.

## Como compilar
Para compilar, abra o terminal na pasta onde se encontra o BARES e digite "make" ou "g++ -Wall -std=c++11 src/bares_drive.cpp -o bin/bares -I include/".
Para executar basta ./bin/bares data/(Nome do arquivo de entrada).txt (Nome do arquivo de saída)

## Autores
Desenvolvido por:
	João Victor Barbosa
	Carlos Vincius Fernandes Rodrigues 