CC=gcc

temp_app: main1.o temp_api.o temp_functions.o
	$(CC) -o temp_app main1.o temp_api.o temp_functions.o

main.o: main1.c temp_api.h
	$(CC) -c main1.c

temp_api.o: temp_api.c temp_api.h
	$(CC) -c temp_api.c

temp_functions.o: temp_functions.c temp_functions.h
	$(CC) -c temp_api.c

clean:
	del *.o temp_app.exe


## todo Не проверил, не нашёл команду make (0__0)  , CMakeLists.txt - собрал норм






