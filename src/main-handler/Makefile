all: newBuild clean main-handler.o access-handler.o thread-handler.o database-handler.o errors.o container.o evaluator.o
	g++ -Wall main-handler.o access-handler.o thread-handler.o database-handler.o errors.o container.o evaluator.o -lmysqlcppconn -pthread -o main-handler -std=c++11

main-handler.o: src/main-handler.cpp
	g++ -c src/main-handler.cpp -std=c++11

access-handler.o: src/main-handler.cpp
	g++ -c src/access-handler.cpp -std=c++11

thread-handler.o: src/thread-handler.cpp
	g++ -c src/thread-handler.cpp -std=c++11

database-handler.o: src/database-handler.cpp
	g++ -c src/database-handler.cpp -std=c++11

container.o: src/container.cpp
	g++ -c src/container.cpp -std=c++11

evaluator.o: src/evaluator.cpp
	g++ -c src/evaluator.cpp -std=c++11

errors.o: src/errors.cpp
	g++ -c src/errors.cpp -std=c++11

newBuild:
	bash update

clean:
	-rm main-handler;
	-rm *.o;
