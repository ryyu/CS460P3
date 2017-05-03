P2.out : Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -std=c++11 -g -o P2.out Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project2.o : Project2.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -std=c++11 -g -c Project2.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -std=c++11 -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.save
	cp LexicalAnalyzer.save LexicalAnalyzer.o

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -std=c++11  -g -c SyntacticalAnalyzer.cpp

clean : 
	rm *.o P2.out *.gch *~

submit : Project2.cpp LexicalAnalyzer.h LexicalAnalyzer.save SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf TeamBP2
	mkdir TeamBP2
	cp Project2.cpp TeamBP2
	cp LexicalAnalyzer.h TeamBP2
	cp LexicalAnalyzer.save TeamBP2
	cp SyntacticalAnalyzer.h TeamBP2
	cp SyntacticalAnalyzer.cpp TeamBP2
	cp makefile TeamBP2
	cp README.txt TeamBP2
	tar cfvz TeamBP2.tgz TeamBP2
	cp TeamBP2.tgz ~tiawatts/cs460drop
