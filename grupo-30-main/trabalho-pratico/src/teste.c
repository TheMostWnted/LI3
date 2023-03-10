#include "../include/funcAux.h"
#include "../include/catalogoDrivers.h"
#include "../include/catalogoRides.h"
#include "../include/catalogoUsers.h"
#include"../include/loaders.h"
#include"../include/stats.h"
#include"../include/interpretador.h"
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
	clock_t start, end;
    double cpu_time_used;

    CatDrivers drivers = initCatDrivers();
	CatUsers users = initCatUsers();
	CatRides rides = initCatRides();
	Estatisticas e = initStats();

	loadUsers("entrada/users.csv", users, e, 2);
	loadDrivers("entrada/drivers.csv", drivers, e, 2);
	loadRides("entrada/rides.csv", rides, drivers, users, e, 2);

	if(argc>1){				//chamado com o número da query a ser corrida
		FILE* out = fopen("Testes/output_query.txt", "w");
		char* info=NULL;
		switch (atoi(argv[1])){
			case 1:;
				char* id=NULL;
				size_t len_id=0;
				printf("Qual o identificador do perfil?\n");
				getline(&id, &len_id, stdin);
				id = strdup(strsep(&id, "\n"));
				start = clock();
				info=(query1(id, drivers, users));
            	end = clock();
				fwrite(info,1,strlen(info),out);
            	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            	printf("Tempo de execução da Query 1 com input %s -> %.5f\n", id, cpu_time_used);
            	free(info);
            	free(id);
				break;
	
			case 2:;
				char* num=NULL;
				size_t len_num=0;
				printf("Qual o número de condutores que deseja?\n");
				getline(&num, &len_num, stdin);
				num=strdup(strsep(&num, " \n"));
				int t=atoi(num);
				start = clock();
				ArrayQuery q = query2(t, drivers);
				end = clock();
				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				printArrayQuery2(q, out);
            	printf("Tempo de execução da Query 2 com input %s -> %.5f\n", num, cpu_time_used);
				free(num);
				break;
	
			case 3:;
				char* num3=NULL;
				size_t len_num3=0;
				printf("Qual o número de condutores que deseja?\n");
				getline(&num3, &len_num3, stdin);
				num=strdup(strsep(&num3, " \n"));
				int t3=atoi(num3);
				start = clock();
				ArrayQuery q3 = query3(t3, users);
				end = clock();
				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				printArrayQuery3(q3, out);
				printf("Tempo de execução da Query 3 com input %s -> %.5f\n", num, cpu_time_used);
				free(num3);
				break;
	
			case 4:;
				char* city=NULL;
				size_t len_city=0;
				printf("Qual a cidade a pesquisar?\n");
				getline(&city, &len_city, stdin);
				city = strdup(strsep(&city, "\n"));
				start = clock();
				info=(query4(city, rides));
				end = clock();
				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				fwrite(info,1,strlen(info),out);
				printf("Tempo de execução da Query 4 com input %s -> %.5f\n", city, cpu_time_used);
				free(city);
				free(info);
				break;
	
			case 5:;
				char* data_a=NULL;
				char* data_b=NULL;
				size_t len_data_a=0;
				size_t len_data_b=0;
				printf("Qual a data inicial a pesquisar?\n");
				getline(&data_a, &len_data_a, stdin);
				printf("Qual a data final a pesquisar?\n");
				getline(&data_b, &len_data_b, stdin);
				data_a = strdup(strsep(&data_a, "\n"));
				data_b = strdup(strsep(&data_b, "\n"));
				//start = clock();
				info=(query5(data_a, data_b, rides));
				//end = clock();
				//cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				printf("res%s\n", info);
				fprintf(out,"%s", info);
				//printf("Tempo de execução da Query 5 com input %s, %s -> %.5f\n", data_a, data_b, cpu_time_used);
				free(data_a);
				free(data_a);
				free(info);
				break;
	
			case 6:;
				char* cidade=NULL;
				char* data_i=NULL;
				char* data_f=NULL;
				size_t len_data_i=0;
				size_t len_data_f=0;
				size_t len_cidade=0;
				printf("Qual a cidade a pesquisar?\n");
				getline(&cidade, &len_cidade, stdin);
				cidade = strdup(strsep(&cidade, "\n"));
				printf("Qual a data inicial a pesquisar?\n");
				getline(&data_i, &len_data_i, stdin);
				printf("Qual a data final a pesquisar?\n");
				getline(&data_f, &len_data_f, stdin);
				data_i = strdup(strsep(&data_i, "\n"));
				data_f = strdup(strsep(&data_f, "\n"));
				start = clock();
				info=(query6(data_i, data_f, cidade, rides));
				end = clock();
				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				fwrite(info,1,strlen(info),out);
				printf("Tempo de execução da Query 6 com input %s, %s, %s -> %.5f\n", cidade, data_a, data_b, cpu_time_used);
				free(data_i);
				free(data_f);
				free(cidade);
				break;
	
			case 7:;
				char* num7=NULL;
				size_t len_num7=0;
				printf("Qual o número de condutores que deseja?\n");
				getline(&num7, &len_num7, stdin);
				num7=strdup(strsep(&num7, " \n"));
				int t7=atoi(num7);
				char* cidade7=NULL;
				size_t len_cidade7=0;
				printf("Qual a cidade a pesquisar?\n");
				getline(&cidade7, &len_cidade7, stdin);
				cidade7 = strdup(strsep(&cidade7, "\n"));
				start = clock();
				ArrayQuery q7 = query7(t7, cidade7, drivers);
				end = clock();
				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				printArrayQuery7(q7, out);
				free(num7);
				free(cidade7);
				break;
			case 8:;
				char* genero=NULL;
				size_t len_genero=0;
				printf("Qual o género dos perfis a procurar?\n");
				getline(&genero, &len_genero, stdin);
				genero=strdup(strsep(&genero, " \n"));
				char* anos=NULL;
				size_t len_anos=0;
				printf("Qual a idade mínima dos perfis a procurar?\n");
				getline(&anos, &len_anos, stdin);
				anos=strdup(strsep(&anos, " \n"));
				int years=atoi(anos);
				start = clock();
				Catalogos cata=query8(genero, years, drivers, rides, users);
				end = clock();
				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				printQuery8(cata, out);
				free(genero);
				free(anos);
				break;
	
			case 9:;
				char* di=NULL;
				char* df=NULL;
				size_t len_di=0;
				size_t len_df=0;
				printf("Qual a data inicial a pesquisar?\n");
				getline(&di, &len_di, stdin);
				printf("Qual a data final a pesquisar?\n");
				getline(&df, &len_df, stdin);
				di = strdup(strsep(&di, "\n"));
				df = strdup(strsep(&df, "\n"));
				start = clock();
				Catalogos ct1=query9(di, df, rides, drivers, users);
				end = clock();
				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				printQuery9(ct1, out);
				free(di);
				free(df);
				break;
			default:;
	            break;
		}
		fclose(out);
	}

	else{					//correr todas as queries
		printf("other\n");
	}

	destroiCatUsers(users);
	destroiCatDrivers(drivers);
	destroiCatRides(rides);	
	return 0;
}