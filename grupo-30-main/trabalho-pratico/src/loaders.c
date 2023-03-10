#include"../include/loaders.h"

int tamanhoLinha=0;
int tamanhoLinhadriver=0;

int loadDrivers(char* ficheiro, CatDrivers drivers, Estatisticas e, int modo){
	FILE* f= fopen(ficheiro, "r");
	if(f==NULL){
		printf("Ficheiro de input de condutores não encontrado\n");
		return 0;
	}
	else
		printf("Ficheiro de Drivers lido com sucesso\n");

	char* line=NULL;
	size_t len=0;
	int totaldrivers=0;

	getline(&line, &len, f);
	while((getline(&line, &len, f)) != -1){
		if(len>tamanhoLinhadriver)
			tamanhoLinhadriver=len;
		Driver d=novoDriver(line, ";\n\r");
		if(d!=NULL){
			insereDriver(drivers, d);
			totaldrivers++;
		}
	}

	free(line);
	fclose(f);
	if(modo==2)
		updateTotalDrivers(e, totaldrivers);
	return 1;
}

int loadUsers(char* ficheiro, CatUsers users, Estatisticas e, int modo){
	FILE *f = fopen(ficheiro, "r");
	if(f==NULL){
		printf("Ficheiro de input de utilizadores não encontrado\n");
		return 0;
	}
	else
		printf("Ficheiro de Users lido com sucesso\n");

	char* line=NULL;
	size_t len=0;
	int totalusers=0;

	getline(&line, &len, f);
	while((getline(&line, &len, f)) != -1){
		if(len>tamanhoLinha)
			tamanhoLinha=len;
		User u=novoUser(line, ";\n\r");
		if(u!=NULL){
			insereUser(users, u);
			totalusers++;
		}
	}

	free(line);
	fclose(f);
	if(modo==2)
		updateTotalUsers(e, totalusers);

	return 1;
}

int loadRides(char* ficheiro, CatRides rides, CatDrivers drivers, CatUsers users, Estatisticas e, int modo){
	FILE *f = fopen(ficheiro, "r");
	if(f==NULL){
		printf("Ficheiro de input de viagens não encontrado\n");
		return 0;
	}
	else
		printf("Ficheiro de Rides lido com sucesso\n");

	char* line=NULL;
	size_t len=0;
	int totalRides=0;

	getline(&line, &len, f);
	while((getline(&line, &len, f)) != -1){
		if(len>tamanhoLinha)
			tamanhoLinha=len;
		Ride r=novaRide(line, ";\n\r");
		if(r!=NULL){
			char* iddriver=getIdDriver(r);
			Driver d=procuraDriver(drivers, iddriver);
			char* username = getUsername(r);
			User u=procuraUser(users, username);


			//free(iddriver);
			free(username);

			int classe=getClasse_Carro(d);
			updateCarClass(r, classe);

			updateDriverScoreTotal(d, getScoreDriver(r));
			updateDriverNumViagens(d);

			double custo=calculaCustoViagem(r);
			updateTotalAuferido(d, custo, getTip(r));
			char* data_viagem=getDataViagem(r);
			mudarDataDriver(d, strdup(data_viagem));
			updateDriverAvalicaoMedia(d);
			char* cidade = getCity(r);
			updateScore(d, strdup(cidade), getScoreDriver(r));
			free(cidade);

			updateUserScoreTotal(u, getScoreUser(r));
			updateUserNumViagens(u);
			updateTotalGasto(u, custo, getTip(r));
			mudarDataUser(u, strdup(data_viagem));
			free(data_viagem);
			updateKmsPercorridos(u, getDistance(r));
			updateUserAvalicaoMedia(u);

			insereRide(rides, r);
			totalRides++;
			
			if(modo==2){
				updateUserStats(e, getUserUName(u), getUserKmPerc(u), getUserTotalGasto(u), getUserNumViag(u));
				updateDriverStats(e, getDriverId(d), getTotalAuferido(d), getDriverNumViagens(d));
				updateStatsViagens(e, getIdRides(r), getDistance(r), custo);
				updateStatsClasses(e, classe);
			}
		}
	}


	free(line);
	fclose(f);
	if(modo==2)
		updateTotalRides(e, totalRides);

	return 1;
}