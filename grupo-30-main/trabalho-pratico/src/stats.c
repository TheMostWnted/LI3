#include "../include/stats.h"

struct userMaisKM{
	char* u;
	double kms;
};

struct totalSpent{
	char* u;
	char* d;
	double dinheiroGasto;
	double dinheiroAuferido;
};

struct viagens{
	char* u;
	char* d;
	int userviagens;
	int driverviagens;
};

struct statsViagens{
	char* viagemmaiscara;
	char* viagemmaislonga;
	double custoviagemmaiscara;
	double distanciaviagemmaislonga;
};

struct stats{
	int totalUsers;
	int totalDrivers;
	int totalRides;
	UserMaisKm umk;
	Gastos g;
	MaisViagens mv;
	StatsViagens sv;
	int viagensBasic;
	int viagensGreen;
	int viagensPremium;
};

Estatisticas initStats(){
	Estatisticas e=malloc(sizeof(struct stats));
	e->totalUsers=0;
	e->totalDrivers=0;
	e->totalRides=0;
	e->viagensBasic=0;
	e->viagensGreen=0;
	e->viagensPremium=0;
	e->umk=malloc(sizeof(struct userMaisKM));
	e->g=malloc(sizeof(struct totalSpent));
	e->mv=malloc(sizeof(struct viagens));
	e->sv=malloc(sizeof(struct statsViagens));
	e->umk->u="";
	e->umk->kms=0.0;
	e->g->u="";
	e->g->d="";
	e->g->dinheiroGasto=0.0;
	e->g->dinheiroAuferido=0.0;
	e->mv->u="";
	e->mv->d="";
	e->mv->userviagens=0;
	e->mv->driverviagens=0;
	e->sv->viagemmaiscara="";
	e->sv->viagemmaislonga="";
	e->sv->custoviagemmaiscara=0.0;
	e->sv->distanciaviagemmaislonga=0.0;

	return e;
}



void updateTotalUsers(Estatisticas e, int total){
	e->totalUsers=total;
}

void updateTotalDrivers(Estatisticas e, int total){
	e->totalDrivers=total;
}

void updateTotalRides(Estatisticas e, int total){
	e->totalRides=total;
}

void updateUserStats(Estatisticas e, char* u, double kms, double dinheiro, int viagens){
	if(kms>e->umk->kms){
		e->umk->kms=kms;
		e->umk->u=strdup(u);
	}
	if(dinheiro>e->g->dinheiroGasto){
		e->g->dinheiroGasto=dinheiro;
		e->g->u=strdup(u);
	}

	if(viagens>e->mv->userviagens){
		e->mv->userviagens=viagens;
		e->mv->u=strdup(u);
	}
}

void updateDriverStats(Estatisticas e, char* d, double dinheiro, int viagens){
	if(dinheiro>e->g->dinheiroAuferido){
		e->g->dinheiroAuferido=dinheiro;
		e->g->d=strdup(d);
	}

	if(viagens>e->mv->driverviagens){
		e->mv->driverviagens=viagens;
		e->mv->d=strdup(d);
	}
}

void updateStatsViagens(Estatisticas e, char* id_viagem, double distancia, double custo){
	if(distancia>e->sv->distanciaviagemmaislonga){
		e->sv->distanciaviagemmaislonga=distancia;
		e->sv->viagemmaislonga=strdup(id_viagem);
	}
	if(custo>e->sv->custoviagemmaiscara){
		e->sv->custoviagemmaiscara=custo;
		e->sv->viagemmaiscara=strdup(id_viagem);
	}
}

void updateStatsClasses(Estatisticas e, int classe){
	if(classe==1)
		e->viagensBasic++;
	if(classe==3)
		e->viagensGreen++;
	if(classe==2)
		e->viagensPremium++;
}

void deleteEstatistica(Estatisticas e){
    free(e->umk->u);
    free(e->g->u);
    free(e->g->d);
    free(e->mv->u);
    free(e->mv->d);
    free(e->sv->viagemmaiscara);
    free(e->sv->viagemmaislonga);
    free(e->umk);
    free(e->g);
    free(e->mv);
    free(e->sv);

    free(e);
}

void printStats(Estatisticas e){
	printf("Total de Utilizadores:%d\n", e->totalUsers);
	printf("Total de Condutores:%d\n", e->totalDrivers);
	printf("Total de Viagens:%d\n", e->totalRides);
	printf("Utilizador com mais quilómetros percorridos: %s - %.2f kms.\n", e->umk->u, e->umk->kms);
	printf("Utilizador com mais dinheiro gasto: %s - %.3f€.\n", e->g->u, e->g->dinheiroGasto);
	printf("Utilizador com mais viagens: %s - %d viagens.\n", e->mv->u, e->mv->userviagens);
	printf("Condutor com mais dinheiro auferido: %s - %.3f€.\n", e->g->d, e->g->dinheiroAuferido);
	printf("Condutor com mais viagens: %s - %d viagens.\n", e->mv->d, e->mv->driverviagens);
	printf("Viagem mais longa: %s - %.2f kms.\n", e->sv->viagemmaislonga, e->sv->distanciaviagemmaislonga);
	printf("Viagem mais cara: %s - %.3f€.\n", e->sv->viagemmaiscara, e->sv->custoviagemmaiscara);
	printf("Número de viagens da classe Basic: %d viagens.\n", e->viagensBasic);
	printf("Número de viagens da classe Green: %d viagens.\n", e->viagensGreen);
	printf("Número de viagens da classe Premium: %d viagens.\n", e->viagensPremium);

}