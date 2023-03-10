#include "../include/driver.h"

struct parScoreViagens{
	double score;
	int num_viagens;
};

struct score{
	GHashTable* score;
};

struct driver{
	char* id;
	char* nome;
	char* genero;
	char* data_nascimento;
	char* data_conta;
	char* matricula;
	char* cidade;
	char* status;
	char* data_ultima_viagem;
	double score_total;
	double score_medio;
	double total_auferido;
	int classe_carro;
	int num_viagens;
	Score scorecidade;
};

int tamanhoLinhaDriver=120;

int validaDriver(Driver driver){
	int valido=1;

	if(strcasecmp(driver->genero, "M")!=0 && strcmp(driver->genero, "F")!=0)
		return 0;

	//if(strcasecmp(driver->classe_carro, "basic")!=0 && strcasecmp(driver->classe_carro, "green")!=0 && strcasecmp(driver->classe_carro, "premium")!=0)
	//	return 0;

	if(strcasecmp(driver->status, "active")!=0 && strcasecmp(driver->status, "inactive")!=0)
		return 0;

	if(strcmp(driver->id, "")==0 || strcmp(driver->nome, "")==0 || strcmp(driver->matricula, "")==0 || strcmp(driver->cidade, "")==0)
		valido=0;
	else if(isNumber(driver->id)==0 || atoi(driver->id)<1)
		valido=0;

	return valido;
}

Score initScore(){
	Score sc = malloc(sizeof(struct score));

    sc->score = g_hash_table_new_full(g_str_hash, g_str_equal,(GDestroyNotify) deleteScoreKey,(GDestroyNotify) deleteParScore);
    return sc;
}

Driver novoDriver(char* line, char* sep){

	char* linha=strdup(line);
	char* tmp=linha;

	int valido=1;
	int flag = 0;
	Driver driver=malloc(sizeof(struct driver));

	driver->id=strdup(strsep(&linha, sep));
	driver->nome=strdup(strsep(&linha, sep));

	char* dob = strdup(strsep(&linha, sep));
	valido=stringdatavalida(dob, "/");
	if(valido==0){
		free(dob);
		return NULL;
	}
	driver->data_nascimento=dob;

	driver->genero=strdup(strsep(&linha, sep));

	char* aux = strdup(strsep(&linha, sep));

	if(strcasecmp(aux, "Basic")==0){
		flag = 1;
		driver->classe_carro=1;
	}
	if(strcasecmp(aux, "Premium")==0){
		flag = 1;
		driver->classe_carro=2;
	}
	if(strcasecmp(aux, "Green")==0){
		flag = 1;
		driver->classe_carro=3;
	}
	if(flag==0){
		free(aux);
		linha=tmp;
		free(linha);
		return NULL;
	}
	free(aux);

	driver->matricula=strdup(strsep(&linha, sep));
	driver->cidade=strdup(strsep(&linha, sep));

	char* doc = strdup(strsep(&linha, sep));
	valido=stringdatavalida(doc, "/");
	if(valido==0){
		free(doc);
		linha=tmp;
		free(linha);
		return NULL;
	}
	driver->data_conta=doc;


	driver->status=strdup(strsep(&linha, sep));


	if(!validaDriver(driver)){
		linha=tmp;
		free(linha);
		return NULL;
	}

	driver->score_total=0.0;
	driver->num_viagens=0;
	driver->score_medio=0.0;
	driver->total_auferido=0.0;
	driver->data_ultima_viagem=NULL;
	driver->scorecidade = initScore();

	linha=tmp;
	free(linha);


	return driver;
}

char* getDriverId(Driver d){
	return strdup(d->id);
}

char* getDrivernome(Driver d){
	return strdup(d->nome);
}

char* getDriverGenero(Driver d){
	return strdup(d->genero);
}

char* getDriverDataNascimento(Driver d){
	return strdup(d->data_nascimento);
}

int getClasse_Carro(Driver d){
	return (d->classe_carro);
}

char* getMatricula(Driver d){
	return strdup(d->matricula);
}

char* getCidade(Driver d){
	return strdup(d->cidade);
}

char* getDriverDataConta(Driver d){
	return strdup(d->data_conta);
}

char* getDriverStatusConta(Driver d){
	return strdup(d->status);
}

double getDriverScoreTotal(Driver d){
	return d->score_total;
}

double getTotalAuferido(Driver d){
	return d->total_auferido;
}

double getDriverAvaliacaoMedia(Driver d){
	return d->score_medio;
}

int getDriverNumViagens(Driver d){
	return d->num_viagens;
}

char* getDriverUltimaViagem(Driver d){
	return strdup(d->data_ultima_viagem);
}

double getScoreCidade(Driver d, char* cidade){
	ParScoreViagens ps = (ParScoreViagens) g_hash_table_lookup(d->scorecidade->score, cidade);
	return ps->score/ps->num_viagens;
}

void updateDriverAvalicaoMedia(Driver d){
	d->score_medio=d->score_total/d->num_viagens;
}

void updateDriverScoreTotal(Driver d, double score){
	d->score_total+=score;
}

void updateDriverNumViagens(Driver d){
	d->num_viagens++;
}

void updateTotalAuferido(Driver d, double fare, double tip){
	d->total_auferido+=fare+tip;
}
void mudarDataDriver(Driver d, char* data){
	updateDriverDataUltimaViagem(&d->data_ultima_viagem, data);
}

void updateDriverDataUltimaViagem(char** d, char* data){

	if((*d==NULL) || (comparaDatas(*d, data)>0))
		*d=data;
	else
		free(data);
}

void updateScore(Driver d, char* city, double score){
	if((int) g_hash_table_contains(d->scorecidade->score, city)==1){
		ParScoreViagens ps = (ParScoreViagens) g_hash_table_lookup(d->scorecidade->score, city);
		ps->score+=score;
		ps->num_viagens++;
		free(city);
	}
	else{
		ParScoreViagens psv=malloc(sizeof(struct parScoreViagens));
		psv->score=score;
		psv->num_viagens=1;
		g_hash_table_insert(d->scorecidade->score, city, psv);
	}
}

void printSc(gpointer key, gpointer value, gpointer userdata){
	ParScoreViagens p = (ParScoreViagens) value;
	printf("Cidade: %s, Avaliação Média: %.3f;", (char*) key, p->score/p->num_viagens);
}

void printScoreViagem(Score s){
	g_hash_table_foreach(s->score, printSc, s);
	printf("\n");
}

char* printDriver(Driver d, int tamanholinha){
	char* infoDriver=malloc(sizeof(char)*(tamanholinha+202));

	sprintf(infoDriver, "ID:%s, Nome:%s, Género:%s, Data de Nascimento:%s, Data de Criação de conta:%s, Cidade:%s, Matrícula:%s,\nClasse Carro:%d, Status da conta:%s, Data da Última Viagem:%s, Avaliação Média:%.3f, Número de Viagens:%d, Total Auferido:%.2f", d->id, d->nome, d->genero, d->data_nascimento, d->data_conta, d->cidade, d->matricula, d->classe_carro, d->status, d->data_ultima_viagem, d->score_medio, d->num_viagens, d->total_auferido);
	return infoDriver;
}

void deleteDriver(Driver d){
	free(d->id);
    free(d->nome);
    free(d->genero);
    free(d->data_nascimento);
    free(d->data_conta);
    free(d->matricula);
    free(d->cidade);
 	free(d->data_ultima_viagem);
    free(d->status);
    destroiScore(d->scorecidade);
    free(d);
}

int contemCidade(Driver d, char* key){
	return (int) g_hash_table_contains(d->scorecidade->score, key);
}

void deleteDriverKey(char* key){
	free(key);
}

void deleteScoreKey(char* key){
	free(key);
}

void deleteParScore(Score ps){
	free(ps);
}

void destroiScore(Score s){
	g_hash_table_destroy(s->score);
}