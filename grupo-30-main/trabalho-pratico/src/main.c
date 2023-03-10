#include "../include/funcAux.h"
#include "../include/catalogoDrivers.h"
#include "../include/catalogoRides.h"
#include "../include/catalogoUsers.h"
#include"../include/interpretador.h"
#include"../include/loaders.h"
#include"../include/stats.h"
#include<stdio.h>
#include<string.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	CatDrivers drivers = initCatDrivers();
	CatUsers users = initCatUsers();
	CatRides rides = initCatRides();
	Estatisticas e = initStats();

	if(argc>1){
		//modo batch
		char* input=strdup(argv[1]);
		char* queries=strdup(argv[2]);

		interpretadorBatch(input, queries, users, drivers, rides, e);

		free(input);
		free(queries);
	}
	else{
		//modo interactivo

		//loadUsers("entrada/users.csv", users, e, 1);
		//loadDrivers("entrada/drivers.csv", drivers, e, 1);
		//loadRides("entrada/rides.csv", rides, drivers, users, e, 1);

		//FILE *f = fopen("teste.txt", "w");
		//printArrayQuery2(query2(100, drivers), f);
		//fclose(f);

		interpretador(users, drivers, rides, e);
		deleteEstatistica(e);
	}
	destroiCatUsers(users);
	destroiCatDrivers(drivers);
	destroiCatRides(rides);	
		
	return 0;
}