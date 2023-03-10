#include"../include/interpretador.h"

void printArrayQuery2(ArrayQuery q, FILE *f){
	int ordem;
	char* info=NULL;
	if(getArrayQuerySize(q)==0){
		info=strdup("");
		fwrite(info,1,strlen(info),f);
	}
	else{
		for(int i=0;i<getArrayQueryLength(q);i++){
			ordem=getArrayQueryOrder(q)[i];
			Driver d = getArrayQueryDriver(q, ordem);
			int tamanhoOutput=strlen(getDriverId(d)) + strlen(getDrivernome(d)) + 5;
			info=malloc(sizeof(char)*tamanhoOutput);
			sprintf(info, "%s;%s;%.3f\n", getDriverId(d), getDrivernome(d), getDriverAvaliacaoMedia(d));
			fwrite(info,1,strlen(info),f);
		}	
	deleteArrayQuery(q, 2);
	}
	free(info);
}

void printArrayQuery3(ArrayQuery q, FILE *f){
	int ordem;
	char* info=NULL;
	if(getArrayQuerySize(q)==0){
		info=strdup("");
		fwrite(info,1,strlen(info),f);
	}
	else{
		for(int i=0;i<getArrayQueryLength(q);i++){
			ordem=getArrayQueryOrder(q)[i];
			User u = getArrayQueryUser(q,ordem);
			int tamanhoOutput=strlen(getUserUName(u)) + strlen(getUserNome(u)) + 7;
			info=malloc(sizeof(char)*tamanhoOutput);
			sprintf(info, "%s;%s;%d\n", getUserUName(u), getUserNome(u), (int) getUserKmPerc(u));
			fwrite(info,1,strlen(info),f);
		}	
		deleteArrayQuery(q, 3);
	}
	free(info);
}

void printArrayQuery7(ArrayQuery q, FILE *f){
	int ordem;
	char* info=NULL;
	if(getArrayQueryLength(q)==0){
		info=strdup("");
		fwrite(info,1,strlen(info),f);
	}
	else{
		for(int i=0;i<getArrayQueryLength(q);i++){
			ordem=getArrayQueryOrder(q)[i];
			Driver d = getArrayQueryDriver(q, ordem);
			int tamanhoOutput=strlen(getDriverId(d)) + strlen(getDrivernome(d)) + 5;
			info=malloc(sizeof(char)*tamanhoOutput);
			sprintf(info, "%s;%s;%.3f\n", getDriverId(d), getDrivernome(d), getScoreCidade(d, getArrayQueryInfo(q)));
			fwrite(info,1,strlen(info),f);
		}	
	}
	free(info);
	deleteArrayQuery(q, 7);
}

void printQuery8(Catalogos ct, FILE *f){
	GList* aux = getListaViagens(ct);
	int tamanho=g_list_length(aux);
	char* info=NULL;
	if(tamanho==1){
		info=strdup("");
		fwrite(info,1,strlen(info),f);
	}
	else{
		CatDrivers drivers = getDrivers(ct);
		CatUsers users = getUsers(ct);
		for(int i=1;i<tamanho;i++){
			Ride r = (Ride) g_list_nth_data(aux, i);
			char* driver_id=getIdDriver(r);
			char* user_id=getUsername(r);
			Driver d = procuraDriver(drivers, driver_id);
			User u = procuraUser(users, user_id);
			char* nome_driver=getDrivernome(d);
			char* nome_user=getUserNome(u);
			int tamanhoOutput=strlen(driver_id)+strlen(user_id)+strlen(nome_driver)+strlen(nome_user)+5;
			info=malloc(sizeof(char)*tamanhoOutput);
			sprintf(info, "%s;%s;%s;%s\n", driver_id, nome_driver, user_id, nome_user);
			fwrite(info, 1, strlen(info), f);
			free(driver_id);
			free(user_id);
			free(nome_driver);
			free(nome_user);
		}
	}
	free(info);
}

void printQuery9(Catalogos ct, FILE *f){
	GList* aux = getListaViagens(ct);
	int tamanho=g_list_length(aux);
	char* info=NULL;
	if(tamanho==1){
		info=strdup("");
		fwrite(info,1,strlen(info),f);
	}
	else{
		for(int i=1;i<tamanho;i++){
			Ride r = (Ride) g_list_nth_data(aux, i);
			char* idviagem=getIdRides(r);
			char* data_viagem=getDataViagem(r);
			int distance=getDistance(r);
			char* cidade=getCity(r);
			double tip=getTip(r);
			int tamanhoOutput=strlen(idviagem)+strlen(data_viagem)+strlen(cidade)+20;
			info=malloc(sizeof(char)*tamanhoOutput);
			sprintf(info, "%s;%s;%d;%s;%.3f\n", idviagem, data_viagem, distance, cidade, tip);
			fwrite(info, 1, strlen(info), f);
			free(idviagem);
			free(data_viagem);
			free(cidade);
		}
	}
	free(info);
}

void paginarQuery2(ArrayQuery q){
    int i=0;
    int flag=1;
    int ordem;
    char action;
    while(i<getArrayQueryLength(q) && flag){
    	system("clear");
    	printf("\n ------------------------------------------------------------------\n");
    	printf("| %-12s | %-10s | %-30s \n","ID","AVALIAÇÃO MÉDIA","NOME");
    	printf(" ------------------------------------------------------------------\n");
    	action='p';
    	int counter = 0;
    	while(counter<10 && i<getArrayQueryLength(q)){
    	    ordem=getArrayQueryOrder(q)[i];
    	    Driver d = getArrayQueryDriver(q, ordem);
    	    char* driver_id = getDriverId(d);
    	    char* driverNome = getDrivernome(d);
    	    double aval = getDriverAvaliacaoMedia(d);
    	    printf("| %-12s | %-15.3f | %-32s \n",driver_id,aval,driverNome);
    	    i++;counter++;
    		free(driver_id);
    		free(driverNome);
    	}
    	printf(" ------------------------------------------------------------------\n");
    	printf("\n   Type 'a' : Previous           Page %d/%d \n   Type 'd' : Next\n   Type 'q' : Exit\n",1 + ((i - 1) / 10),1 + ((getArrayQueryLength(q)- 1) / 10));
        while ('q'!=action && ('a'!=action || i<=10) && ('d'!=action || i>=getArrayQueryLength(q))){
                action = getchar();
        }
        if('q'==action) flag = 0;
        else if('a'==action){
            i=i-10-counter;
        }
    }
}

int paginarQuery3(ArrayQuery q){
    int counter = 0;
    int i=0;
    int ordem;
    printf("\n ------------------------------------------------------------------\n");
    printf("| %-12s | %-10s | %-30s \n","USERNAME","DISTÂNCIA TOTAL","NOME");
    printf(" ------------------------------------------------------------------\n");
    while(i<getArrayQueryLength(q) && counter<10){
        ordem=getArrayQueryOrder(q)[i];
        User u = getArrayQueryUser(q, ordem);
        char* user_id = getUserUName(u);
        char* userNome = getUserNome(u);
        double distancia = getUserKmPerc(u);
        printf("| %-12s | %-15.3f | %-32s \n",user_id,distancia,userNome);
        i++;counter++;
    	free(user_id);
    	free(userNome);
    }
    printf(" ------------------------------------------------------------------\n");
    return counter;
}

void paginarQuery7(ArrayQuery q){
    int i=0;
    int ordem;
    int flag=1;
    char action;
    while(i<getArrayQueryLength(q) && flag){
    	action='p';
    	system("clear");
    	printf("\n ------------------------------------------------------------------\n");
    	printf("| %-12s | %-10s | %-30s \n","ID","AVALIAÇÃO MÉDIA NA CIDADE","NOME");
    	printf(" ------------------------------------------------------------------\n");
    	int counter = 0;
    	while(counter<10 && i<getArrayQueryLength(q)){
        	ordem=getArrayQueryOrder(q)[i];
        	Driver d = getArrayQueryDriver(q, ordem);
        	char* driver_id = getDriverId(d);
        	char* driverNome = getDrivernome(d);
        	double aval = getScoreCidade(d, getArrayQueryInfo(q));
        	printf("| %-12s | %-25.3f | %-32s \n",driver_id,aval,driverNome);
        	i++;counter++;
    		free(driver_id);
    		free(driverNome);
    	}
    	printf(" ------------------------------------------------------------------\n");
        printf("\n   Type 'a' : Previous           Page %d/%d \n   Type 'd' : Next\n   Type 'q' : Exit\n",1 + ((i - 1) / 10),1 + ((getArrayQueryLength(q)- 1) / 10));
        while ('q'!=action && ('a'!=action || i<=10) && ('d'!=action || i>=getArrayQueryLength(q))){
                action = getchar();
        }
        if('q'==action) flag = 0;
        else if('a'==action){
            i=i-10-counter;
        }
    }
}

void paginarQuery8(Catalogos ct){
	int flag=1;
    int i=1;
    char action;
    GList* aux = getListaViagens(ct);
    int tamanho=g_list_length(aux);
    if(tamanho==1)
		printf("Não foram encontrados resultados.\n");
	else{
		CatDrivers drivers = getDrivers(ct);
		CatUsers users = getUsers(ct);
		while(i<tamanho && flag){
			action='p';
    		system("clear");
			printf("\n ----------------------------------------------------------------------------------------------------------\n");
    		printf("| %-12s | %-30s | %-30s | %-30s \n","IDCONDUTOR","NOMECONDUTOR","IDUTILIZADOR","NOMEUTILIZADOR");
    		printf(" ----------------------------------------------------------------------------------------------------------\n");
    		int counter = 0;
    		while(counter<20 && i<tamanho){
    			Ride r = (Ride) g_list_nth_data(aux, i);
				char* driver_id=getIdDriver(r);
				char* user_id=getUsername(r);
				Driver d = procuraDriver(drivers, driver_id);
				User u = procuraUser(users, user_id);
				char* nome_driver=getDrivernome(d);
				char* nome_user=getUserNome(u);
				printf("| %-12s | %-30s | %-30s | %-30s \n",driver_id, nome_driver, user_id, nome_user);
				counter++;i++;
				free(driver_id);
				free(user_id);
				free(nome_driver);
				free(nome_user);
    		}
    	printf(" ----------------------------------------------------------------------------------------------------------\n");
    	printf("\n   Type 'a' : Previous           Page %d/%d \n   Type 'd' : Next\n   Type 'q' : Exit\n",1 + ((i - 2) / 20),1 + ((tamanho- 1) / 20));
    	while ('q'!=action && ('a'!=action || i<=10) && ('d'!=action || i>=tamanho)){
                action = getchar();
        }
        if('q'==action) flag = 0;
        else if('a'==action){
            i=i-10-counter;
        	}
        }
	}
}

void paginarQuery9(Catalogos ct){
	int flag=1;
    int i=1;
    char action;
    GList* aux = getListaViagens(ct);
    int tamanho=g_list_length(aux);
    if(tamanho==1)
		printf("Não foram encontrados resultados.\n");
	else{
		while(i<tamanho && flag){
			action='p';
    		system("clear");
			printf("\n ----------------------------------------------------------------------------------------------------------\n");
    		printf("| %-12s | %-10s | %-8s | %-12s | %8s\n","IDVIAGEM","DATAVIAGEM","DISTANCIA","CIDADE","GORJETA");
    		printf(" ----------------------------------------------------------------------------------------------------------\n");
    		int counter = 0;
    		while(counter<20 && i<tamanho){
    			Ride r = (Ride) g_list_nth_data(aux, i);
    			char* idRide = getIdRides(r);
    			char* data = getDataViagem(r);
    			int dist = getDistance(r);
    			char* city = getCity(r);
    			double tip = getTip(r);
				printf("| %-12s | %-10s | %-8d | %-12s | %.3f\n",idRide, data, dist, city, tip);
				counter++;i++;
				free(idRide);
				free(data);
				free(city);
    		}
    	printf(" ----------------------------------------------------------------------------------------------------------\n");
    	printf("\n   Type 'a' : Previous           Page %d/%d \n   Type 'd' : Next\n   Type 'q' : Exit\n",1 + ((i - 2) / 20),1 + ((tamanho- 1) / 20));
    	while ('q'!=action && ('a'!=action || i<=10) && ('d'!=action || i>=tamanho)){
                action = getchar();
        }
        if('q'==action) flag = 0;
        else if('a'==action){
            i=i-10-counter;
        	}
        }
	}
}

void runProgram(char* filename_users, char* filename_drivers, char* filename_rides, CatUsers users, CatDrivers drivers, CatRides rides, Estatisticas e){
	int modo=2;
	int output1, output2, output3;

	output1=loadUsers(filename_users, users, e, modo);
	output2=loadDrivers(filename_drivers, drivers, e, modo);
	output3=loadRides(filename_rides, rides, drivers, users, e, modo);

	if(output1==1 && output2==1 && output3==1){
		system("clear");


		printf("O que deseja fazer?\n");
		printf("1: Correr queries\n");
		printf("2: Estatísticas\n");
		printf("3: Sair\n");
	
	
		char comando[1];
		scanf("%s", comando);
	
		while(strcmp(comando, "3")!=0){
	
			switch(atoi(comando)){
				case 1:;
					char* query=NULL;
					size_t len_query=0;
					getline(&query, &len_query, stdin);
					printf("Qual query pretende correr? Digite 1, 2, 3, 4, 5, 6, 7, 8 ou 9?\n");
					getline(&query, &len_query, stdin);
					query=strdup(strsep(&query, "\n"));
					printf("Escolheu a query %s\n", query);
					switch(atoi(query)){
						case 1:;
							//query 1
							char* info=NULL;
							char* id=NULL;
							size_t len_id=0;
							printf("Qual o identificador do perfil?\n");
							getline(&id, &len_id, stdin);
							id = strdup(strsep(&id, "\n"));
							info=(query1(id, drivers, users));
							if(strcmp(info, "")!=0)
								printf("Perfil pedido: %s", info);
							else
								printf("Não foram encontrados resultados.\n");
							free(id);
							free(info);
							break;
	
						case 2:;
							//query 2
							char* num=NULL;
							size_t len_num=0;
							printf("Qual o número de condutores que deseja?\n");
							getline(&num, &len_num, stdin);
							num=strdup(strsep(&num, " \n"));
							int t=atoi(num);
	
							ArrayQuery q = query2(t, drivers);
							free(num);
	
							paginarQuery2(q);
							break;
	
						case 3:;
							//query3
							char* num3=NULL;
							size_t len_num3=0;
							printf("Qual o número de condutores que deseja?\n");
							getline(&num3, &len_num3, stdin);
							num=strdup(strsep(&num3, " \n"));
							int t3=atoi(num3);
	
							ArrayQuery q3 = query3(t3, users);
							free(num3);
	
							paginarQuery3(q3);
							break;
	
						case 4:;
							//query4
							char* info4=NULL;
							char* city=NULL;
							size_t len_city=0;
							printf("Qual a cidade a pesquisar?\n");
							getline(&city, &len_city, stdin);
							city = strdup(strsep(&city, "\n"));
							info4=(query4(city, rides));
							if(strcmp(info4, "")!=0)
								printf("Preço médio das viagens na cidade %s: %s", city, info4);
							else
								printf("Não foram encontrados resultados.\n");
							free(city);
							free(info4);
							break;
	
						case 5:;
							//query5
							char* info5=NULL;
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
							info5=(query5(data_a, data_b, rides));
							if(strcmp(info5, "")!=0)
								printf("Preço médio das viagens entre as datas %s e %s é: %s", data_a, data_b, info5);
							else
								printf("Não foram encontrados resultados.\n");
							free(data_a);
							free(data_b);
							free(info5);
							break;
	
						case 6:;
							//query6
							char* info6=NULL;
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
							info6=(query6(data_i, data_f, cidade, rides));
							if(strcmp(info6, "")!=0)
								printf("A distância média percorrida na cidade %s entre as datas %s e %s é: %s", cidade, data_i, data_f, info6);
							else
								printf("Não foram encontrados resultados.\n");
							free(data_i);
							free(data_f);
							free(cidade);
							free(info6);
							break;
	
						case 7:;
							//query7
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
							ArrayQuery q7 = query7(t7, cidade7, drivers);
							paginarQuery7(q7);
							free(num7);
							system("clear");
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
							Catalogos cata=query8(genero, years, drivers, rides, users);
							paginarQuery8(cata);
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
							Catalogos ct1=query9(di, df, rides, drivers, users);
							paginarQuery9(ct1);
							free(di);
							free(df);
							break;
						default:;
							printf("Query Inválida!\n");
							break;
					}
					break;
	
				case 2:;
					system("clear");
					printf("Estatísticas\n");
					printStats(e);
					printf("\n\n");
					break;
	
				default:
					printf("Comando Incorrecto! Tente novamente.\n");
					break;
			}
	
			printf("1: Correr queries\n");
			printf("2: Estatísticas\n");
			printf("3: Sair\n");
			scanf("%s", comando);
		}	
	}
	else
		printf("Erro a ler ficheiros de input.\n");
}

int runQueries(char* filename_users, char* filename_drivers, char* filename_rides, char* queries, CatUsers users, CatDrivers drivers, CatRides rides, Estatisticas e){
	int modo=1;
	loadUsers(filename_users, users, e, modo);
	loadDrivers(filename_drivers, drivers, e, modo);
	loadRides(filename_rides, rides, drivers, users, e, modo);

	FILE* f_queries=fopen(queries, "r");
	if(f_queries==NULL){
		printf("Ficheiro de queries não encontrado.\n");
		return 0;
	}

	char* line=NULL;
	char* tmp=NULL;
	size_t len=0;
	int i=1;
	char* q_number=NULL;

	while((getline(&line, &len, f_queries)) != -1){
		tmp=line;
		q_number=strdup(strsep(&line, " \n"));
		char filename[35];
		sprintf(filename,"Resultados/command%d_output.txt",i++);
		
		FILE* output = fopen(filename, "w");
	    if(output==NULL){
	    	printf("Erro ao criar ficheiro de output!\n");
	    	return 0;
	    }

		if(q_number!=NULL){
			char* info=NULL;
			switch(atoi(q_number)){
				case 1:;
					//query 1
					char* id=strdup(strsep(&line, " \n"));
					info=(query1(id, drivers, users));
					fwrite(info,1,strlen(info),output);
					free(id);
					free(info);
					break;
				case 2:;
					//query 2
					char* num=strdup(strsep(&line, " \n"));
					int t=atoi(num);
					printArrayQuery2(query2(t,drivers), output);
					free(num);
					break;
				case 3:;
					//query 3
					char* num3=strdup(strsep(&line, " \n"));
					int t3=atoi(num3);
					printArrayQuery3(query3(t3,users), output);
					free(num3);
					break;
				case 4:;
					//query 4
					char* cidade=strdup(strsep(&line, " \n"));
					info=(query4(cidade, rides));
					fwrite(info,1,strlen(info),output);
					free(cidade);
					free(info);
					break;
				case 5:;
					//query 5
					char* data_inicial=strdup(strsep(&line, " \n"));
					char* data_final=strdup(strsep(&line, " \n"));
					info=(query5(data_inicial, data_final, rides));
					fwrite(info,1,strlen(info),output);
					free(data_inicial);
					free(data_final);
					free(info);
					break;
				case 6:;
					//query 6
					char* c=strdup(strsep(&line, " \n"));
					char* data_i=strdup(strsep(&line, " \n"));
					char* data_f=strdup(strsep(&line, " \n"));
					info=(query6(data_i, data_f, c, rides));
					fwrite(info,1,strlen(info),output);
					free(data_i);
					free(data_f);
					free(c);
					free(info);
					break;
				case 7:;
					//query 7
					char* n=strdup(strsep(&line, " \n"));
					int top=atoi(n);
					char* city=strdup(strsep(&line, " \n"));
					printArrayQuery7(query7(top, city, drivers), output);
					free(n);
					break;
				case 8:;
					//query 8
					char* genero=strdup(strsep(&line, " \n"));
					char* anos=strdup(strsep(&line, " \n"));
					int years = atoi(anos);
					printQuery8(query8(genero, years, drivers, rides, users), output);
					free(genero);
					free(anos);
					break;
				case 9:;
					//query 9
					char* data_in=strdup(strsep(&line, " \n"));
					char* data_fin=strdup(strsep(&line, " \n"));
					printQuery9(query9(data_in, data_fin, rides, drivers, users), output);
					free(data_in);
					free(data_fin);
					break;
				default:
					printf("Query Inválida!\n");
					break;
			}
			fclose(output);
		}
		line=tmp;
	}
	free(q_number);
	free(line);
	fclose(f_queries);

	return 1;
}

void interpretador(CatUsers users, CatDrivers drivers, CatRides rides, Estatisticas e){
	printf("Bem Vindo!\nIndique um dos comandos abaixo.\n");

	printf("1: Run\n");

	printf("2: Sair\n");

	char comando[1];
	scanf("%s", comando);

	while(strcmp(comando, "2")!=0){
		if(strcmp(comando, "1")==0){
			//getline(&line_users, &len_users, stdin);
			char* pasta_entrada=NULL;
			size_t len_input=0;
			getline(&pasta_entrada, &len_input, stdin);
			printf("Por favor digite o caminho para a pasta dos ficheiros de entrada.\n");
			getline(&pasta_entrada, &len_input, stdin);

			pasta_entrada=strdup(strsep(&pasta_entrada, "\n"));

			char* fileUsers=malloc(sizeof(char)*(strlen(pasta_entrada)+11));
			char* fileDrivers=malloc(sizeof(char)*(strlen(pasta_entrada)+13));
			char* fileRides=malloc(sizeof(char)*(strlen(pasta_entrada)+11));
		
			sprintf(fileUsers, "%susers.csv", pasta_entrada);
			sprintf(fileDrivers, "%sdrivers.csv", pasta_entrada);
			sprintf(fileRides, "%srides.csv", pasta_entrada);
		
			char* input_users=strdup(strsep(&fileUsers, "\n"));
			char* input_drivers=strdup(strsep(&fileDrivers, "\n"));
			char* input_rides=strdup(strsep(&fileRides, "\n"));

			runProgram(input_users, input_drivers, input_rides, users, drivers, rides, e);

			free(fileUsers);
			free(fileDrivers);
			free(fileRides);
			free(input_users);
			free(input_drivers);
			free(input_rides);
			free(pasta_entrada);

			break;
		}
		else{
			printf("Comando Incorrecto! Tente novamente.\n");
			printf("1: Run\n");
			printf("2: Sair\n");
			scanf("%s", comando);
		}
	}
}

void interpretadorBatch(char* input, char* queries, CatUsers users, CatDrivers drivers, CatRides rides, Estatisticas e){
	char* pasta_entrada=strdup(input);

	char* fileUsers=malloc(sizeof(char)*(strlen(pasta_entrada)+11));
	char* fileDrivers=malloc(sizeof(char)*(strlen(pasta_entrada)+13));
	char* fileRides=malloc(sizeof(char)*(strlen(pasta_entrada)+11));

	sprintf(fileUsers, "%s/users.csv", pasta_entrada);
	sprintf(fileDrivers, "%s/drivers.csv", pasta_entrada);
	sprintf(fileRides, "%s/rides.csv", pasta_entrada);

	char* input_users=strdup(strsep(&fileUsers, "\n"));
	char* input_drivers=strdup(strsep(&fileDrivers, "\n"));
	char* input_rides=strdup(strsep(&fileRides, "\n"));

	runQueries(input_users, input_drivers, input_rides, queries, users, drivers, rides, e);

	free(fileUsers);
	free(fileDrivers);
	free(fileRides);
	free(input_users);
	free(input_drivers);
	free(input_rides);
	free(pasta_entrada);
}