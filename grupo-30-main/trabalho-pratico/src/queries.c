#include "../include/queries.h"

//ESTRUTURAS

struct arrayQuery{
    int size; // tamanho maximo do array
    double lowest; // valor do menor elemento no array
    int lowest_index; // index do menor elemento no array
    char* info;
    char* data_viagem_lowest_id;
    int lowest_id;
    char* lowest_username;
    int* order;
	char* dataA;
    char* dataB; 
    GArray* array;
};

//Viagens contém um apontador para uma lista onde vão ser guardadas as viagens que passem a verificação da query8 pela ordem pedida no enunciado.
struct viagens{
	GList* vgs;
};

//Catálogos contém um apontador para as hashtables de condutores e utilizadores assim como um apontador para viagens, uma string genero e um inteiro anos
struct catalogos{
    CatDrivers drivers;
    CatUsers users;
    Viagens viagens;
    char* genero;
    char* data_a;
    char* data_b;
    int anos;
};











//FUNÇÕES AUXILIARES ÀS ESTRUTURAS

Catalogos initCatalogos(){
    Catalogos ct = malloc(sizeof(struct catalogos));  
    return ct;
}

void setCatalogos(Catalogos ct, CatUsers u, CatDrivers d){
	ct->users=u;
	ct->drivers=d;
	ct->viagens = malloc(sizeof(struct viagens));
	ct->viagens->vgs = g_list_alloc();
}

int getArrayQuerySize(ArrayQuery array){
    return array->size;
}

int getArrayQueryLength(ArrayQuery array){
    return array->array->len;
}

int* getArrayQueryOrder(ArrayQuery array){
	return array->order;
}

Driver getArrayQueryDriver(ArrayQuery array, int i){
	return g_array_index(array->array,Driver,i);
}

User getArrayQueryUser(ArrayQuery array, int i){
	return g_array_index(array->array,User,i);
}

char* getArrayQueryInfo(ArrayQuery array){
	return strdup(array->info);
}

GList* getListaViagens(Catalogos ct){
	return ct->viagens->vgs;
}

CatDrivers getDrivers(Catalogos ct){
	return ct->drivers;
}

CatUsers getUsers(Catalogos ct){
	return ct->users;
}

void deleteArrayQuery(ArrayQuery a, int query){
	if(query==2)
	    free(a->data_viagem_lowest_id);
	if(query==3){
		free(a->data_viagem_lowest_id);
		free(a->lowest_username);
	}
	if(query==7)
		free(a->info);
	g_array_free(a->array, TRUE);
    free(a);
}













//FUNÇÕES AUXILIARES ÀS QUERIES

//////////////////////////QUERY2//////////////////////////


int* returnIndexesQuery2(ArrayQuery q){
	int* res = malloc(sizeof(int)*q->array->len);							//array resultado
	double* values = malloc(sizeof(double)*q->array->len);					//array de scores
	int* ids = malloc(sizeof(int)*q->array->len);							//array de ids
	char** datas = malloc(sizeof(char)*10*q->array->len);						//array de datas
	double a;
	int b, id_aux;
	char* data_aux = NULL;

	for(int i=0;i<q->array->len;i++){										//preencher os arrays com os valores do arrayquery
		Driver d=g_array_index(q->array, Driver,i);
		double score_medio=getDriverAvaliacaoMedia(d);
		values[i]=score_medio;
		res[i]=i;
		ids[i]=atoi(getDriverId(d));
		datas[i]=getDriverUltimaViagem(d);
	}

	for(int i=0;i<q->array->len;i++){
		for(int j=i+1;j<q->array->len;j++){
			if(values[i]<=values[j]){							//se o scoremedio do driver i <= scoremedio do driver j
				if(values[i]==values[j]){						//se o scoremedio for igual
					//se as datas forem iguais e o id de i for inferior ao de j ou se a data de j for mais recente que a de i
					if(((comparaDatas(datas[i], datas[j])==0) && (ids[i]>ids[j])) || comparaDatas(datas[i], datas[j])==1){
						a = values[i];						
						b = res[i];
						id_aux=ids[i];
						data_aux = strdup(datas[i]);
						values[i]=values[j];
						res[i]=res[j];
						ids[i]=ids[j];
						datas[i]=datas[j];
						values[j]=a;
						res[j]=b;
						ids[j]=id_aux;
						datas[j]=data_aux;
					}
				}
				else{
					a = values[i];						
					b = res[i];
					id_aux=ids[i];
					data_aux = strdup(datas[i]);
					values[i]=values[j];
					res[i]=res[j];
					ids[i]=ids[j];
					datas[i]=datas[j];
					values[j]=a;
					res[j]=b;
					ids[j]=id_aux;
					datas[j]=data_aux;
				}
			}
		}
	}
	free(data_aux);
	free(datas);
	return res;
}

//////////////////////////QUERY3//////////////////////////

int* returnIndexesQuery3(ArrayQuery q){
	int* res = malloc(sizeof(int)*q->array->len);							//array resultado
	double* values = malloc(sizeof(double)*q->array->len);					//array de distancias
	char** ids = malloc(sizeof(char)*40*q->array->len);							//array de ids
	char** datas = malloc(sizeof(char)*10*q->array->len);						//array de datas
	double a;
	int b;
	char* id_aux;
	char* data_aux = NULL;

	for(int i=0;i<q->array->len;i++){										//preencher os arrays com os valores do arrayquery
		User u=g_array_index(q->array, User,i);
		double distancia=getUserKmPerc(u);
		values[i]=distancia;
		res[i]=i;
		ids[i]=getUserUName(u);
		datas[i]=getUserDataUltViag(u);
	}
	

	for(int i=0;i<q->array->len;i++){
		for(int j=i+1;j<q->array->len;j++){
			if(values[i]<=values[j]){							//se a distancia do user i <= distancia do user j
				if(values[i]==values[j]){						//se a distancia for igual
					//se as datas forem iguais e o id de i for inferior ao de j ou se a data de j for mais recente que a de i
					if(((comparaDatas(datas[i], datas[j])==0) && (strcmp(ids[i], ids[j])>0 )) || comparaDatas(datas[i], datas[j])==1){
						a = values[i];						
						b = res[i];
						id_aux=strdup(ids[i]);
						data_aux = strdup(datas[i]);
						values[i]=values[j];
						res[i]=res[j];
						ids[i]=ids[j];
						datas[i]=datas[j];
						values[j]=a;
						res[j]=b;
						ids[j]=id_aux;
						datas[j]=data_aux;
					}
				}
				else{
					a = values[i];						
					b = res[i];
					id_aux=strdup(ids[i]);
					data_aux = strdup(datas[i]);
					values[i]=values[j];
					res[i]=res[j];
					ids[i]=ids[j];
					datas[i]=datas[j];
					values[j]=a;
					res[j]=b;
					ids[j]=id_aux;
					datas[j]=data_aux;
				}
			}
		}
	}

	
	free(data_aux);
	free(id_aux);
	free(datas);
	free(ids);
	return res;
}

//////////////////////////QUERY7//////////////////////////

int* returnIndexesQuery7(ArrayQuery q){

	int* res = malloc(sizeof(int)*q->array->len);
	double* values = malloc(sizeof(double)*q->array->len);
	int* ids = malloc(sizeof(int)*q->array->len);
	double a;
	int b, id_aux;

	for(int i=0;i<q->array->len;i++){
		Driver d=g_array_index(q->array, Driver,i);
		double score_medio=getScoreCidade(d, q->info);
		values[i]=score_medio;
		res[i]=i;
		ids[i]=atoi(getDriverId(d));
	}

	for(int i=0;i<q->array->len;i++){
		for(int j=i+1;j<q->array->len;j++){
			if(values[i]<=values[j]){
				if(values[i]==values[j]){
					if(ids[i]<ids[j]){
						a = values[i];
						b = res[i];
						id_aux=ids[i];
						values[i]=values[j];
						res[i]=res[j];
						ids[i]=ids[j];
						values[j]=a;
						res[j]=b;
						ids[j]=id_aux;
					}
				}
				else{
					a = values[i];
					b = res[i];
					id_aux=ids[i];
					values[i]=values[j];
					res[i]=res[j];
					ids[i]=ids[j];
					values[j]=a;
					res[j]=b;
					ids[j]=id_aux;
				}


			}
		}
	}
	return res;
}

//////////////////////////QUERY8//////////////////////////

//devolve 1 se a viagem 1 tem que vir antes da 2, -1 se ao contrário
int compareRides(char* datad1, char* datad2, char* datau1, char* datau2, char* idviagem1, char* idviagem2){
	int resultado = comparaDatas(datad1, datad2);

	if(resultado==0){
		resultado = comparaDatas(datau1, datau2);
		if(resultado==0){
			resultado = atoi(idviagem2) - atoi(idviagem1);
			free(idviagem1);
			free(idviagem2);
		}
	}

	return resultado;

}

int comparaViagens(Ride r1, Ride r2, CatDrivers drivers, CatUsers users){
	char* idd1 = getIdDriver(r1);
	char* idd2 = getIdDriver(r2);
	char* idu1 = getUsername(r1);
	char* idu2 = getUsername(r2);
	Driver d1 = procuraDriver(drivers, idd1);
	Driver d2 = procuraDriver(drivers, idd2);
	User u1 = procuraUser(users, idu1);
	User u2 = procuraUser(users, idu2);

	char* datad1 = getDriverDataConta(d1);
	char* datad2 = getDriverDataConta(d2);
	char* datau1 = getUserDataConta(u1);
	char* datau2 = getUserDataConta(u2);
	int res = compareRides(datad1, datad2, datau1, datau2, getIdRides(r1), getIdRides(r2));

	free(idd1);
	free(idd2);
	free(idu1);
	free(idu2);
	free(datad1);
	free(datad2);
	free(datau1);
	free(datau2);

	if(res>0)
		return 1;
	else
		return -1;
}
//////////////////////////QUERY9//////////////////////////

int compareRidesQ9(Ride a, Ride b){ // 1 sse a > b
	char* idA = getIdRides(a);
	char* idB = getIdRides(b);
	int res = -1;
	char* data_viagem_a = getDataViagem(a);
	char* data_viagem_b = getDataViagem(b);
	if((getDistance(a) > getDistance(b))  || 
	  ((getDistance(a) == getDistance(b)) &&  comparaDatas(data_viagem_a ,data_viagem_b) < 0) || 
	  ((getDistance(a) == getDistance(b)) &&  (comparaDatas(data_viagem_a, data_viagem_b) == 0) && (atoi(idA)>atoi(idB)))
	  ){
		res = 1;
	}
	
	free(idA);
	free(idB);
	free(data_viagem_a);
	free(data_viagem_b);
	return res;
}


int indexainserir(Viagens viagens, Ride r, CatDrivers drivers, CatUsers users, int query){

	Ride rmeio = NULL;
	int tamanho = g_list_length(viagens->vgs);
	int inicio = 0;
	int meio;
	int fim=tamanho;
	int res;
	if(tamanho==1){
		return 1;
	}
	while(fim!=tamanho-1 || fim!=inicio){
		meio=(fim+inicio)/2;
		if(meio==0){
			meio=1;
		}
		rmeio = (Ride) g_list_nth_data(viagens->vgs, meio);
		if(query==8)
			res=comparaViagens(r, rmeio, drivers, users);
		if(query==9)
			res=compareRidesQ9(r, rmeio);
		if(res>0){		//se a nova r deve vir antes de rmeio

			if(meio-1==0)
				return meio;

			Ride rantes = (Ride) g_list_nth_data(viagens->vgs, meio-1);
			if(query==8)
				res=comparaViagens(r, rantes, drivers, users);
			if(query==9)
				res=compareRidesQ9(r, rantes);
			if(rantes!=NULL && res>0){	//se r deve vir antes de rantes
				fim=meio-2;
			}
			if(rantes !=NULL && res<0){
				//se r deve vir depois de rantes
				return meio;
			}
		}
		else{	//se r deve vir depois de rmeio
			if(meio==tamanho-1)
				return meio+1;
			Ride rdepois = (Ride) g_list_nth_data(viagens->vgs, meio+1);
			if(query==8)
				res=comparaViagens(r, rdepois, drivers, users);
			if(query==9)
				res=compareRidesQ9(r, rdepois);
			if(rdepois!=NULL && res>0){		//se r deve vir antes de rdepois
				return meio+1;

			}
			if(rdepois!=NULL && res<0){		//se r deve vir depois de rdepois
				inicio=meio+1;
			}
		}
	}
	return -1;
}










//IMPLEMENTAÇÃO DE QUERIES

//////////////////////////QUERY1//////////////////////////

char* query1(char* chave, CatDrivers drivers, CatUsers users){
	char* info=NULL;
	if(isNumber(chave)==1){
		Driver d = procuraDriver(drivers, chave);
		if(d!=NULL){
			if(strcasecmp(getDriverStatusConta(d), "active")==0){
				info=malloc(sizeof(char)*(TAMANHO_QUERY1));
				char* dob=getDriverDataNascimento(d);
				int idade=calculaIdade(dob);
				free(dob);
				sprintf(info, "%s;%s;%d;%.3f;%d;%.3f\n", getDrivernome(d), getDriverGenero(d), idade, getDriverAvaliacaoMedia(d), getDriverNumViagens(d), getTotalAuferido(d));
			}
		}
	}
	else{
		User u=procuraUser(users, chave);
		if(u!=NULL){
			if(strcasecmp(getUserStatus(u), "active")==0){
				info=malloc(sizeof(char)*(TAMANHO_QUERY1));
				char* dob=getUserDataNascimento(u);
				int idade=calculaIdade(dob);
				free(dob);
				sprintf(info, "%s;%s;%d;%.3f;%d;%.3f\n", getUserNome(u), getUserGenero(u), idade, getUserScoreMedio(u), getUserNumViag(u), getUserTotalGasto(u));	
			}
		}
	}
	if(info==NULL)
		info=strdup(""); //ID Inválido!
	return info;
}

//////////////////////////QUERY2//////////////////////////

void query2aux(gpointer key, gpointer value, gpointer data){
	Driver d = (Driver) value;
	ArrayQuery qarray = (ArrayQuery) data;

	char* dt = NULL;

	double score_medio=getDriverAvaliacaoMedia(d);
	char* status = getDriverStatusConta(d);
	if(strcasecmp(status, "active")==0){
		if(qarray->array->len<qarray->size){						//se o array tiver menos do que n condutores
			if(qarray->lowest>score_medio){							//se o novo score for inferior ao mais baixo, actualizar
				qarray->lowest=score_medio;
				qarray->lowest_index=qarray->array->len;
				qarray->lowest_id=atoi(getDriverId(d));
				dt = getDriverUltimaViagem(d);
				qarray->data_viagem_lowest_id=dt;
			}
			qarray->array=g_array_append_val(qarray->array,d);		//inserir condutor no array
		}
		else{													//se o array tiver mais que n elementos
			if(score_medio>=qarray->lowest){					//apenas interessam os novos condutores com scoremedio superior aos que já estão no array
				qarray->array = g_array_remove_index_fast(qarray->array,qarray->lowest_index);	//remove o valor mais baixo do array
				qarray->array = g_array_append_val(qarray->array,d);		//insere o condutor no array
				qarray->lowest=10.0;
				qarray->lowest_id=111111111;

				for(int i=0;i<qarray->size;i++){						//agora vai procurar pelo novo valor mais baixo e qual o seu indice
					Driver d1 = g_array_index(qarray->array, Driver,i);		
					double score_medio1=getDriverAvaliacaoMedia(d1);
					char* data1 = getDriverUltimaViagem(d1);
					if(score_medio1<qarray->lowest){
        		  	    qarray->lowest = score_medio1;
        		  	    qarray->lowest_index = i;
        		  	    qarray->lowest_id=atoi(getDriverId(d1));
						qarray->data_viagem_lowest_id=data1;
        		  	}

        		  	if(score_medio1==qarray->lowest){
        		  		if(comparaDatas(data1, qarray->data_viagem_lowest_id)==0){
        		  			if(atoi(getDriverId(d1))>qarray->lowest_id){
        		  				qarray->lowest=score_medio1;
        		  				qarray->lowest_index = i;
        		  	  	 		qarray->lowest_id=atoi(getDriverId(d1));
								qarray->data_viagem_lowest_id=data1;
        		  			}
        		  		}

        	  			if(comparaDatas(data1, qarray->data_viagem_lowest_id)==1){
        	  				qarray->lowest=score_medio1;
        	  				qarray->lowest_index = i;
        	  		  	 	qarray->lowest_id=atoi(getDriverId(d1));
							qarray->data_viagem_lowest_id=data1;
        	  			}
        	  		}
        	  		else
        	  			free(data1);
				}
			}
		}
	}	
}


ArrayQuery query2(int n,CatDrivers drivers){
	ArrayQuery qarray = malloc(sizeof(struct arrayQuery));
	qarray->size=n;
	qarray->lowest=10.0;		//inicializar a 10. em princípio nunca haverá condutores com scoremedio > 5.0
	qarray->lowest_id=111111111;
	qarray->data_viagem_lowest_id = NULL;
	qarray->array = g_array_new(FALSE,FALSE,sizeof(Driver));

	if(n>0){
		foreachDriver(drivers, query2aux, qarray);	
		qarray->order=returnIndexesQuery2(qarray);
	}

	return qarray;
}

//////////////////////////QUERY3//////////////////////////

int comparaUsers(User u1, User u2){
	int res=-1;
	int distancia_viajada1=getUserKmPerc(u1);
	int distancia_viajada2=getUserKmPerc(u2);
	if(distancia_viajada1==0)
		return -1;
	char* datau1=getUserDataUltViag(u1);
	char* datau2=getUserDataUltViag(u2);
	char* idu1=getUserUName(u1);
	char* idu2=getUserUName(u2);

	if(distancia_viajada1>distancia_viajada2 || (distancia_viajada1==distancia_viajada2 && comparaDatas(datau1, datau2)==-1) ||
		(distancia_viajada1==distancia_viajada2 && comparaDatas(datau1, datau2)==0 && strcmp(idu1, idu2)>0)){
			res=1;
		}

	free(datau1);
	free(datau2);
	free(idu1);
	free(idu2);
	return res;
}

void query3aux(gpointer key, gpointer value, gpointer data){
	User u = (User) value;
	ArrayQuery qarray = (ArrayQuery) data;


	char* dt = NULL;

	double distancia_viajada=getUserKmPerc(u);
	char* status = getUserStatus(u);

	if(strcasecmp(status, "active")==0){
		if(qarray->array->len<qarray->size){						//se o array tiver menos do que n utilizadores
			if(qarray->lowest>distancia_viajada){					//se a nova distancia for inferior à mais baixa, actualizar
				qarray->lowest=distancia_viajada;
				qarray->lowest_index=qarray->array->len;
				qarray->lowest_username=strdup(key);
				dt = getUserDataUltViag(u);
				qarray->data_viagem_lowest_id=dt;
			}
			qarray->array=g_array_append_val(qarray->array,u);		//inserir utilizador no array
		}
		else{			//se o array tiver mais que n utilizadores
			if(comparaUsers(u, g_array_index(qarray->array, User, qarray->lowest_index))==1){					//apenas interessam os novos utilizadores com distancia superior aos que já estão no array
				qarray->array = g_array_remove_index_fast(qarray->array,qarray->lowest_index);	//remove o valor mais baixo do array
				qarray->array = g_array_append_val(qarray->array,u);		//insere o utilizador no array
				qarray->lowest=10000000.0;
				qarray->lowest_username=strdup("»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»");

				for(int i=0;i<qarray->size;i++){						//agora vai procurar pelo novo valor mais baixo e qual o seu indice
					User u1 = g_array_index(qarray->array, User,i);		
					double distancia_viajada1=getUserKmPerc(u1);
					char* data1 = getUserDataUltViag(u1);
					char* username = getUserUName(u1);
					if(distancia_viajada1<qarray->lowest){
        		  	    qarray->lowest = distancia_viajada1;
        		  	    qarray->lowest_index = i;
        		  	    qarray->lowest_username=username;
						qarray->data_viagem_lowest_id=data1;
        		  	}

        		  	if(distancia_viajada1==qarray->lowest){										//se a distancia for igual
        		  		if(comparaDatas(data1, qarray->data_viagem_lowest_id)==0){				//se as datas forem iguais
        		  			if(strcmp(username, qarray->lowest_username)>0){					//se o novo username for mais baixo que aquele em lowest_username
        		  				qarray->lowest=distancia_viajada1;
        		  				qarray->lowest_index = i;
        		  	  	 		qarray->lowest_username=username;
								qarray->data_viagem_lowest_id=data1;
        		  			}
        		  		}
        		  		if(comparaDatas(data1, qarray->data_viagem_lowest_id)==1){				//se a data do novo utilizador for mais recente
        	  				qarray->lowest=distancia_viajada1;
        	  				qarray->lowest_index = i;
        	  		  	 	qarray->lowest_username=username;
							qarray->data_viagem_lowest_id=data1;
        	  			}
        		  	}
        		  	else{
        		  		free(username);
        		  		free(data1);
        		  	}
				}
			}
		}
	}
}

ArrayQuery query3 (int n, CatUsers users){
	ArrayQuery qarray = malloc(sizeof(struct arrayQuery));
	if(n>0){
		qarray->size=n;
		qarray->array = g_array_new(FALSE,FALSE,sizeof(User));
		qarray->lowest_username=NULL;
		qarray->lowest=10000000.0;
		qarray->lowest_username=strdup("»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»");
		foreachUser(users, query3aux, qarray);
		qarray->order = returnIndexesQuery3(qarray);
	}
	return qarray;
}

//////////////////////////QUERY4//////////////////////////

void query4aux(gpointer key, gpointer value, gpointer data){
	Ride r = (Ride) value;
    ArrayQuery qarray = (ArrayQuery) data;
    char* cidade = getCity(r);
    if(strcmp(cidade, qarray->info)==0){
    	qarray->lowest+=calculaCustoViagem(r);
    	qarray->size++;
    }
    free(cidade);
}

char* query4(char* cidade, CatRides rides ){
    char* info = NULL;
	double precM=0.0;

    ArrayQuery qarray = malloc(sizeof(struct arrayQuery));

    qarray->info=cidade;
    qarray->size = 0; //numero Viagens
    qarray->lowest = 0.0; // preco total

    foreachRide(rides, query4aux, qarray);

    precM =(qarray->lowest)/(qarray->size);

    if(qarray->size > 0)					//para não dar nan
	    info=printFloatToString(precM);
    
    free(qarray);

    if(info==NULL)
        info=strdup(""); //Cidade Inválida!
    return info;
}

//////////////////////////QUERY5//////////////////////////

void query5aux(gpointer key, gpointer value, gpointer data){
    Ride r = (Ride) value;
    ArrayQuery qarray = (ArrayQuery) data;
    char* data_v = getDataViagem(r);
    if ((comparaDatas(data_v, qarray->dataB)==1 || comparaDatas(data_v, qarray->dataB)==0) && (comparaDatas(data_v, qarray->dataA)==-1 || comparaDatas(data_v, qarray->dataA)==0)){
        qarray->size++;
        qarray->lowest += calculaCustoViagem(r);
    }
    free(data_v);
}

char* query5(char* data_inicial, char* data_final, CatRides rides ){
    char* info = NULL;
    double average = 0.0;

    ArrayQuery qarray = malloc(sizeof(struct arrayQuery));

	if(comparaDatas(data_inicial, data_final)==1 || comparaDatas(data_inicial, data_final)==0){
        qarray->dataA = data_inicial;
        qarray->dataB = data_final;
        qarray->size = 0; //numero Viagens
        qarray->lowest = 0.0; // preco total

        foreachRide(rides, query5aux, qarray);

        average =(qarray->lowest)/(qarray->size);
        if(qarray->size > 0)						//para não dar nan
        	info=printFloatToString(average);
    }
    free(qarray);

    if(info==NULL)
        info=strdup(""); //Datas Inválidas!
    return info;
}

//////////////////////////QUERY6//////////////////////////

void query6aux(gpointer key, gpointer value, gpointer data){
    Ride r = (Ride) value;
    ArrayQuery qarray = (ArrayQuery) data;
    char* data_v = getDataViagem(r);
    char* cidade = getCity(r);
    if (strcmp(cidade,qarray->info)==0 && (comparaDatas(data_v, qarray->dataB)==1 || comparaDatas(data_v, qarray->dataB)==0) && (comparaDatas(data_v, qarray->dataA)==-1 || comparaDatas(data_v, qarray->dataA)==0)){
        qarray->size++;
        qarray->lowest += (double) getDistance(r);
    }
    free(data_v);
    free(cidade);
}

char* query6(char* data_inicial, char* data_final, char* city, CatRides rides ){
    char* info = NULL;
    double average = 0.0;

    ArrayQuery qarray = malloc(sizeof(struct arrayQuery));

	if(comparaDatas(data_inicial, data_final)==1 || comparaDatas(data_inicial, data_final)==0){
        qarray->dataA = data_inicial;
        qarray->dataB = data_final;
        qarray->info=city;
        qarray->size = 0; //numero Viagens
        qarray->lowest = 0.0; // preco total

        foreachRide(rides, query6aux, qarray);

        average =(qarray->lowest)/(qarray->size);
        if(qarray->size > 0)						//para não dar nan
	        info=printFloatToString(average);
    }
    free(qarray);

    if(info==NULL)
        info=strdup(""); //Datas Inválidas!
    return info;
}
//////////////////////////QUERY7//////////////////////////

void query7aux(gpointer key, gpointer value, gpointer data){
	Driver d = (Driver) value;
	ArrayQuery qarray = (ArrayQuery) data;
	char* status = getDriverStatusConta(d);
	if(strcasecmp(status, "active")==0){
		if(contemCidade(d, qarray->info)==1){							//se o condutor tiver viagens na cidade pedida
			double score_medio=getScoreCidade(d, qarray->info);			//calcular o scoremedio daquele condutor na cidade pedida
			if(qarray->array->len<qarray->size){						//se o array tiver menos do que n condutores
				if(qarray->lowest>score_medio){							//se o novo score for inferior ao mais baixo, actualizar
					qarray->lowest=score_medio;
					qarray->lowest_index=qarray->array->len;
					char* iddriver=getDriverId(d);
					qarray->lowest_id=atoi(iddriver);
					free(iddriver);
				}
				qarray->array=g_array_append_val(qarray->array,d);		//inserir condutor no array
			}
			else{														//se o array tiver mais que n elementos
				if(score_medio>=qarray->lowest){		//apenas interessam os novos condutores com scoremedio superior ou igual aos que já estão no array
					qarray->array = g_array_remove_index_fast(qarray->array,qarray->lowest_index);	//remove o valor mais baixo do array
					qarray->array = g_array_append_val(qarray->array,d);		//insere o condutor no array
					qarray->lowest=10.0;
					qarray->lowest_id=111111111;
		
					for(int i=0;i<qarray->size;i++){						//agora vai procurar pelo novo valor mais baixo e qual o seu indice
						Driver d1 = g_array_index(qarray->array, Driver,i);		
						double score_medio1=getScoreCidade(d1, qarray->info);
						if(score_medio1<qarray->lowest){
    	        	    	qarray->lowest = score_medio1;
    	        	      	qarray->lowest_index = i;
    	        	      	char* iddriver=getDriverId(d1);
    	        	      	qarray->lowest_id=atoi(iddriver);
    	        	      	free(iddriver);
    	        	    }
    	        	    if(score_medio1==qarray->lowest){
    	        	    	char* iddriver=getDriverId(d1);
    	        	    	if(atoi(iddriver)<qarray->lowest_id){
    	        	    		qarray->lowest = score_medio1;
    	        	      		qarray->lowest_index = i;
    	        	      		qarray->lowest_id=atoi(iddriver);
    	        	    	}
    	        	    	free(iddriver);
    	        	    }
					}
					
				}
			}
		}
	}
	free(status);
}

ArrayQuery query7(int n, char* cidade, CatDrivers drivers){
	ArrayQuery qarray = malloc(sizeof(struct arrayQuery));
	qarray->size=n;
	qarray->lowest=10.0;		//inicializar a 10. em princípio nunca haverá condutores com scoremedio > 5.0
	qarray->info=cidade;
	qarray->lowest_id=111111111;
	qarray->array = g_array_new(FALSE,FALSE,sizeof(Driver));

	foreachDriver(drivers, query7aux, qarray);
	
	qarray->order=returnIndexesQuery7(qarray);

	return qarray;
}

//////////////////////////QUERY8//////////////////////////

void query8aux(gpointer key, gpointer value, gpointer data){
	Catalogos ct = (Catalogos) data;
    Viagens viagens = ct->viagens;
    Ride r = (Ride) value;

    char* idd = getIdDriver(r);												//buscar id do condutor da viagem
	Driver d = procuraDriver(ct->drivers, idd);								//encontrar condutor na hashtable de condutores
	char* generodriver = getDriverGenero(d);								//buscar genero do condutor
	char* statusdriver = getDriverStatusConta(d);
	if(strcmp(generodriver, ct->genero)==0 && strcasecmp(statusdriver, "active")==0){		//se o condutor tiver o genero pedido e conta active
		char* data_conta_driver=getDriverDataConta(d);						//buscar a data de criação da conta do condutor
		int idadecontadriver=calculaIdade(data_conta_driver);				//calcular a idade da conta
		free(data_conta_driver);
		if(idadecontadriver>=ct->anos){										//se a conta a mesma ou mais idade que aquela pedida
			char* idu = getUsername(r);										//buscar id do passageiro da viagem
			User u = procuraUser(ct->users, idu);							//encontrar passageiro na hashtable de utilizadores
			char* generouser=getUserGenero(u);								//buscar genero do passageiro
			char* statususer = getUserStatus(u);
			if(strcmp(generouser, ct->genero)==0 && strcasecmp(statususer, "active")==0){		//se o passageiro tiver o genero pedido e conta active
				char* data_conta_user=getUserDataConta(u);					//buscar a data de criação da conta do passageiro
				int idadecontauser=calculaIdade(data_conta_user);			//calcular a idade da conta
				free(data_conta_user);
				if(idadecontauser>=ct->anos){								//se a conta a mesma ou mais idade que aquela pedida		
					int index=indexainserir(viagens, r, ct->drivers, ct->users, 8);		//calcula o indice a inserir esta viagem na lista de resultados
					viagens->vgs=g_list_insert(viagens->vgs, r, index);					//insere na lista de resultados
				}
			}
			free(statususer);
			free(generouser);
			free(idu);
		}
	}
	free(generodriver);
	free(statusdriver);
	free(idd);
}

Catalogos query8(char* genero, int anos, CatDrivers drivers, CatRides rides, CatUsers users){
	Catalogos ct = initCatalogos();
	setCatalogos(ct, users, drivers);
	ct->genero=strdup(genero);
	ct->anos=anos;
	foreachRide(rides, query8aux, ct);
	return ct;
}


//////////////////////////QUERY9//////////////////////////
void query9aux(gpointer key, gpointer value, gpointer data){
	Catalogos ct = (Catalogos) data;
    Viagens viagens = ct->viagens;
    Ride r = (Ride) value;

    char* data_viagem = getDataViagem(r);
    double tip = getTip(r);
    if(tip>0 && ((comparaDatas(data_viagem,ct->data_b)==1 || comparaDatas(data_viagem,ct->data_b)==0) && (comparaDatas(data_viagem, ct->data_a)==-1 || comparaDatas(data_viagem,ct->data_a)==0))){
    	int index=indexainserir(viagens, r, ct->drivers, ct->users, 9);		//calcula o indice a inserir esta viagem na lista de resultados
		viagens->vgs=g_list_insert(viagens->vgs, r, index);					//insere na lista de resultados
    }
    free(data_viagem);
}

Catalogos query9(char* data_inicial, char* data_final, CatRides rides, CatDrivers drivers, CatUsers users){
	Catalogos ct = initCatalogos();
	setCatalogos(ct, users, drivers);
	int valido=1;

    valido=stringdatavalida(data_inicial, "/");

    if(valido==1){
    	valido=stringdatavalida(data_final, "/");
    }
    if(valido==1){
    	if(comparaDatas(data_inicial, data_final)==1 || comparaDatas(data_inicial, data_final)==0){
    		ct->data_a=strdup(data_inicial);
    		ct->data_b=strdup(data_final);
            foreachRide(rides, query9aux, ct);
        }
    }
    return ct;
}