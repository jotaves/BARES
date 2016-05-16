bares:
	g++ -Wall -std=c++11 src/bares_drive.cpp -o bin/bares -I include/
clean:
	rm bin/bares
cdata:
	rm data/out
run:
	./bin/bares data/entrada9.txt
print:
	./bin/bares data/entrada9.txt >> data/out