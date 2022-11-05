routeRecords: project2-main.o routeRecords.o
	gcc project2-main.o routeRecords.o -o project2
project2-main.o: project2-main.c routerecords.h
	gcc -c project2-main.c
routeRecords.o: routeRecords.c routerecords.h
	gcc -c routeRecords.c
clean:
	rm *.o routeRecords
