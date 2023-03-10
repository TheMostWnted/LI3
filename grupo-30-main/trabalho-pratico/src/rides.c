#include "../include/rides.h"


struct ride{
    char* id_ride;
    char* data_viagem;
    char* id_driver;
    char* username;
    char* city;
    double score_user;
    double score_driver;
    double tip;
    int car_class;
    int distance;
    //char* comment;
};

Ride novaRide(char* line, char* sep){
    
    char* linha=strdup(line);
    char* aux;
    int valido=1;
    char* tmp = linha;

    Ride ride=malloc(sizeof(struct ride));

    ride->id_ride=strdup(strsep(&linha, sep));
    
    char* data = strdup(strsep(&linha, sep));
    valido=stringdatavalida(data, "/");
    if(valido==0){
        linha=tmp;
        free(linha);
        free(data);
        return NULL;
    }
    ride->data_viagem=data;

    ride->id_driver=strdup(strsep(&linha, sep));
    ride->username=strdup(strsep(&linha, sep));
    ride->city=strdup(strsep(&linha, sep));
    aux=strdup(strsep(&linha, sep));
    if(strcmp(aux, "")==0 || isNumber(aux)==0 || atoi(aux)<=0){
        free(aux);
        linha=tmp;
        free(linha);
        return NULL;
    }
    ride->distance=atoi(aux);
    free(aux);
    aux=strdup(strsep(&linha, sep));
    if(strcmp(aux, "")==0 || isNumber(aux)==0 || atoi(aux)<=0){
        free(aux);
        linha=tmp;
        free(linha);
        return NULL;
    }
    ride->score_user=atof(aux);
    free(aux);
    aux=strdup(strsep(&linha, sep));
    if(strcmp(aux, "")==0 || isNumber(aux)==0 || atoi(aux)<=0){
        free(aux);
        linha=tmp;
        free(linha);
        return NULL;
    }
    ride->score_driver=atof(aux);
    free(aux);
    aux=strdup(strsep(&linha, sep));
    if(strcmp(aux, "")==0 || isDouble(aux)==0){
        free(aux);
        linha=tmp;
        free(linha);
        return NULL;
    }
    char* temp;
    ride->tip = strtod(aux, &temp);

    if(!validaRide(ride)){
        free(aux);
        linha=tmp;
        free(linha);
		return NULL;
    }

    free(aux);
    linha=tmp;
    free(linha);

    return ride;
}

int validaRide(Ride ride){
	int valido=1;

	if(strcmp(ride->username, "")==0 || strcmp(ride->id_ride, "")==0 || strcmp(ride->id_driver, "")==0 || strcmp(ride->city, "")==0)
		valido=0;

    else{
    	if(isNumber(ride->id_ride)==0 || atoi(ride->id_ride)<1 || isNumber(ride->id_driver)==0 || atoi(ride->id_driver)<1)
        	valido=0;
    }

	return valido;
}


char* getIdRides (Ride r){
	return strdup(r->id_ride);
}
char* getDataViagem (Ride r){
	return strdup(r->data_viagem);
}
char* getIdDriver (Ride r){
	return strdup(r->id_driver);
}
char* getUsername (Ride r){
	return strdup(r->username);
}
char* getCity (Ride r){
	return strdup(r->city);        
}
int getDistance (Ride r){
	return r->distance;
}
double getScoreUser (Ride r){
	return r->score_user;
}
double getScoreDriver (Ride r){
	return r->score_driver;
}
double getTip (Ride r){
	return r->tip;
}
//char* getComment (Ride r){
//	return strdup(r->comment);
//}
int getCarClass (Ride r){
	return (r->car_class);
}

void updateCarClass (Ride r, int class){
	r->car_class=(class);
}


double calculaCustoViagem(Ride r){
    double custo;

    if(r->car_class==2)
        custo=T_PREMIUM + (TKM_PREMIUM*r->distance);
    if(r->car_class==3)
        custo=T_GREEN + (TKM_GREEN*r->distance);
    if(r->car_class==1)
        custo=T_BASIC + (TKM_BASIC*r->distance);

    return custo;
}

char* printRide(Ride r, int tamanholinha){
	char* infoRide=malloc(sizeof(char)*tamanholinha);

	sprintf(infoRide, "%s, %s, %s, %s, %s, %d ", r->id_ride, r->data_viagem, r->id_driver, r->username, r->city, r->car_class);
	return infoRide;
}


void deleteRide(Ride r){
    free(r->id_ride);
    free(r->id_driver);
    free(r->username);
    free(r->data_viagem);
    free(r->city);
    //free(r->car_class);

    free(r);
}

void deleteRideKey(char* key){
    free(key);
}
