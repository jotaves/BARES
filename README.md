# BARES

### Sobre
A palavra "BARES" é uma abreviação para "Basic Arithmetic Expression Evaluator based on Stacks", a qual já diz muito por si só. É um algoritmo que recebe uma expressão com operações matemáticas, analisa o que foi dado, se hover erro na expressão o mesmo exibe-o dando a coluna e código relacionado ao erro apresentado, caso contrário o mesmo exibe o resultado da operação solicitada.

### Como funciona
Para poder realizar as operações solicitadas, o código primeiramente tokeniza cada termo da expressão e os armazena em uma fila. Em seguida, passa os termos armazenados nessa fila da forma infixa para posfixa, podendo assim tornar os cálculos mais facilmente realizáveis pelo computador, além de retirar possíveis ambiguidades.
Com isso feito, uma stack é usada para auxiliar na realização dos cálculos, armazenando os operandos de acordo com as exigências para um cálculo correto na notação posfixa.


### Limitações operacionais
Os valores expressáveis em um termo e no resultado da operação têm que estar entre -32768 e 32767.

### Os símbolos aceitos são:
	Parênteses:		--> ( ) <--
	Adição:			-->  +  <-- 
	Subtração:		-->  -  <--
	Multiplicação:		-->  *  <--
	Divisão:		-->  /  <--
	Exponenciação:		-->  ^  <--
	Módulo:			-->  %  <--

### Erros detectáveis pelo código:
	1 --> Um dos operandos da expressão está fora da faixa permitida.
	2 --> Em alguma parte da expressão está faltando um operando ou existe algum operando em formato errado.
	3 --> Existe um símbolo correspondente a um operador que não está na lista de operadores válidos.
	4 --> Aparentemente o programa encontrou um símbolo extra “perdido” na expressão.
	5 --> Existe um parêntese fechando sem ter um parêntese abrindo correspondente.
	6 --> Apareceu um operador sem seus operandos.
	7 --> Está faltando um parêntese de fechamento ’)’ para um parêntese de abertura ‘(’ correspondente.
	8 --> Houve divisão cujo quociente é zero.
	9 --> Uma operação dentro de uma operação ou da expressão inteira estoura o limite das constantes numéricas definidas.

### Erros ou bugs
Nenhum caso de anormalidades foi detectado durantes os testes realizados na produção do código nem em sua execução.

### Como compilar
Para compilar, abra o terminal na pasta onde se encontra o BARES e digite:

`g++ -Wall -std=c++11 src/bares_drive.cpp -o bin/bares -I include/`

Para executar e exibir os resultados no terminal, digite:

`./bin/bares [nome do arquivo de entrada]`

E para gerar um arquivo com os resultados:

`./bin/bares [nome do arquivo de entrada] >> [nome do arquivo de saída]`

### Autores
Desenvolvido por:

	João Victor Bezerra Barboza

	Carlos Vincius Fernandes Rodrigues
