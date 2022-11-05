#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "routerecords.h"

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("ERROR: Missing file\n");
		return -1;
	}

	printf("Opening <passenger-data.csv> ...\n");

	FILE *fileIn = fopen(argv[1], "r");
	if(fileIn == NULL)
        {
                printf("ERROR: Could not open file\n");
        }
	
	routeRecord *route = createRecords(fileIn);
	int unqRoute = fillRecords(route, fileIn);
	printf("Unique routes operated by airlines: %d\n", unqRoute);
		
	char select[5]; 
	char start[4];
	char end[4];
	char airline[4];
	SearchType type;
	
	while(strcmp(select, "5") != 0)
	{
		printMenu();
		scanf("%s", select);
		if(strcmp(select, "1") == 0)
		{	
			type = ROUTE;
			printf("Enter origin: \n");
     			scanf("%s", start);
			printf("Enter destination: \n");
     			scanf("%s", end);
     			searchRecords(route, unqRoute, start, end, type);
		}
		else if(strcmp(select, "2")== 0)
		{
			type = ORIGIN;
			printf("Enter origin: \n");
      			scanf("%s", start);
			
    			searchRecords(route, unqRoute, start, end, type);	
		}
		else if(strcmp(select, "3") == 0)
		{
			
			type = DESTINATION;
			printf("Enter destination: \n");
                        scanf("%s", end);
			searchRecords(route, unqRoute, end, start, type);
                 
		}
		else if(strcmp(select, "4") == 0)
		{
			type = AIRLINE;
			printf("Enter airline: \n");
                        scanf("%s", airline);
			                        
                        searchRecords(route, unqRoute, airline, end, type);
		}                
		else if(strcmp(select, "5") == 0)
		{	
			printf("Good-bye!\n");
			free(route);
			continue;
			
		}
		else{
			printf("Invalid input.\n");

		}

	}

	fclose(fileIn);
	return 0;

}
