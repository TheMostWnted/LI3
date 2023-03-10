#include "../include/user.h"

struct user{
    char* username;
	char* nome;
	char* genero;
	char* data_nascimento;
	char* data_conta;
	char* metodo_pagamento;
	char* status;
	double score_medio;			
	double score_total;				
	int num_viagens;			
	double total_gasto;				
	char* data_ultima_viagem;		
	double kms_percorridos;
};

char* getUserUName(User u){
	return strdup(u->username);
}

char* getUserNome(User u){
	return strdup(u->nome);
}
char* getUserGenero(User u){
	return strdup(u->genero);
}
char* getUserDataNascimento(User u){
	return strdup(u->data_nascimento);
}

char* getUserDataConta(User u){
	return strdup(u->data_conta);
}

char* getUserMetodoPag(User u){
	return strdup(u->metodo_pagamento);
}
char* getUserStatus(User u){
	return strdup(u->status);
}

double getUserScoreMedio(User u){
	return u->score_medio;
}

double getUserScoreTotal(User u){
    return u->score_total;
}

int getUserNumViag(User u){
    return u->num_viagens;
}

double getUserTotalGasto(User u){
    return u->total_gasto;
}
char* getUserDataUltViag(User u){
	return strdup(u->data_ultima_viagem);
}

double getUserKmPerc(User u){
    return u->kms_percorridos;
}

void updateUserAvalicaoMedia(User u){
	u->score_medio=u->score_total/u->num_viagens;
}

void updateUserScoreTotal(User u, double score){
	u->score_total+=score;
}

void updateUserNumViagens(User u){
	u->num_viagens++;
}

void updateTotalGasto(User u, double gasto, double gorjeta){
	u->total_gasto+=gasto+gorjeta;
}

void updateKmsPercorridos(User u, double kms){
	u->kms_percorridos+=kms;
}

void mudarDataUser(User u, char* data){
	updateUserDataUltimaViagem(&u->data_ultima_viagem, data);
}

void updateUserDataUltimaViagem(char** u, char* data){
	if((*u==NULL) || (comparaDatas(*u, data)>0))
		*u=data;
	else
		free(data);
}

int validaUser(User user){
	int valido=1;

	if(strcasecmp(user->genero, "M")!=0 && strcmp(user->genero, "F")!=0)
		return 0;

	if(strcasecmp(user->metodo_pagamento, "cash")!=0 && strcasecmp(user->metodo_pagamento, "credit_card")!=0 && strcasecmp(user->metodo_pagamento, "debit_card")!=0)
		return 0;

	if(strcasecmp(user->status, "active")!=0 && strcasecmp(user->status, "inactive")!=0)
		return 0;

	if(strcmp(user->username, "")==0 ||strcmp(user->nome, "")==0)
		valido=0;
	return valido;
}

char* printUser(User u, int tamanholinha){
	char* infoUser=malloc(sizeof(char)*(tamanholinha+216));
	
	sprintf(infoUser, "Username:%s, Nome:%s, Género:%s, Data de Nascimento:%s, Data de Criação de conta:%s,\nMétodo de Pagamento:%s, Status da conta:%s, Data da Última Viagem:%s, Avaliação Média:%.2f, Número de Viagens:%d, Total Gasto:%.2f, Quilómetros Percorridos:%.2f", u->username, u->nome, u->genero,u->data_nascimento, u->data_conta, u->metodo_pagamento, u->status, u->data_ultima_viagem, u->score_medio, u->num_viagens, u->total_gasto, u->kms_percorridos);
	return infoUser;
}

User novoUser(char* line, char* sep){

	char* linha=strdup(line);
	char* tmp = linha;

	int valido=1;
	User user=malloc(sizeof(struct user));
	
	user->username=strdup(strsep(&linha, sep));
	user->nome=strdup(strsep(&linha, sep));
    user->genero=strdup(strsep(&linha, sep));

    char* dob = strdup(strsep(&linha, sep));
	valido=stringdatavalida(dob, "/");
	if(valido==0){
		free(dob);
		return NULL;
	}
	user->data_nascimento=dob;

	char* doc = strdup(strsep(&linha, sep));
	valido=stringdatavalida(doc, "/");
	if(valido==0){
		free(doc);
		return NULL;
	}
	user->data_conta=doc;

	user->metodo_pagamento=strdup(strsep(&linha, sep));
    user->status=strdup(strsep(&linha, sep));


	if(!validaUser(user))
		return NULL;

    user->score_medio=0.0;
	user->num_viagens=0;
	user->total_gasto=0.0;
	user->data_ultima_viagem=NULL;
    user->kms_percorridos=0.0;

    linha=tmp;
    free(linha);

	return user;
}

void deleteUser(User u){
    free(u->username);
    free(u->nome);
    free(u->genero);
    free(u->data_nascimento);
    free(u->data_conta);
    free(u->metodo_pagamento);
    free(u->status);
    free(u->data_ultima_viagem);

    free(u);
}
void deleteUserKey(char* key){
	free(key);
}
