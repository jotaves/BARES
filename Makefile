bares:
	g++ -Wall -std=c++11 src/bares_drive.cpp -o bin/bares -I include/
clean:
	rm bin/bares
run:
	./bin/bares data/entrada9.txt saida9