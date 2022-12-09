4uzduotis: functions.o main.o
	gcc functions.o main.o -o 4uzduotis
functions.o: functions.c functions.h
	gcc -c functions.c
main.o: functions.h main.c
	gcc -c main.c

clean:
	rm -f *.o 4uzduotis.exe
rebuild: clean 4uzduotis
