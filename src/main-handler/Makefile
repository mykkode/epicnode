all: newBuild clean main-handler.o access-handler.o thread-handler.o database-handler.o errors.o container.o evaluator.o
	g++-7 -Wall main-handler.o access-handler.o thread-handler.o database-handler.o errors.o container.o evaluator.o -lmysqlcppconn -pthread -o main-handler -std=c++11

main-handler.o: src/main-handler.cpp
	g++-7 -c src/main-handler.cpp -std=c++11

access-handler.o: src/main-handler.cpp
	g++-7 -c src/access-handler.cpp -std=c++11

thread-handler.o: src/thread-handler.cpp
	g++-7 -c src/thread-handler.cpp -std=c++11

database-handler.o: src/database-handler.cpp
	g++-7 -c src/database-handler.cpp -std=c++11

container.o: src/container.cpp
	g++-7 -c src/container.cpp -std=c++11

evaluator.o: src/evaluator.cpp
	g++-7 -c src/evaluator.cpp -std=c++11

errors.o: src/errors.cpp
	g++-7 -c src/errors.cpp -std=c++11

newBuild:
	bash update

clean:
	-rm main-handler;
	-rm *.o;
