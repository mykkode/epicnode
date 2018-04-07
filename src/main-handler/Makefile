all: newBuild clean main-handler.o access-handler.o thread-handler.o database-handler.o errors.o
	g++ -Wall main-handler.o access-handler.o thread-handler.o database-handler.o errors.o -lmysqlcppconn -pthread -o main-handler

main-handler.o: src/main-handler.cpp
	g++ -c src/main-handler.cpp

access-handler.o: src/main-handler.cpp
	g++ -c src/access-handler.cpp

thread-handler.o: src/thread-handler.cpp
	g++ -c src/thread-handler.cpp

database-handler.o: src/database-handler.cpp
	g++ -c src/database-handler.cpp

errors.o: src/errors.cpp
	g++ -c src/errors.cpp
newBuild:
	bash update
clean:
	-rm main-handler;
	-rm *.o;
