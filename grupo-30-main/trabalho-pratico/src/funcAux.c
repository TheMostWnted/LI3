#include"../include/funcAux.h"
#include <stdlib.h>

char* ref = "09/10/2022";

void printascii(char* line){
	for(int i=0;i<strlen(line);i++){
		printf("%d\n", line[i]);
	}
}

int stringdatavalida(char* string, char* sep){
	if(strlen(string)!=10) return 0;

	if(string[2]!='/' || string[5]!='/')
		return 0;

	int res = 1;
	int d = 0;
	int m = 0;
	int a = 0;

	char* linha=strdup(string);
	char* tmp = linha;
	char* dia = NULL;
	char* mes = NULL;
	char* ano = NULL;

	dia=strdup(strsep(&linha, sep));
	mes=strdup(strsep(&linha, sep));
	ano=strdup(strsep(&linha, sep));

	if(isNumber(dia)==0 || isNumber(mes)==0 || isNumber(ano)==0)
		res = 0;
	else{
		d = atoi(dia);
		m = atoi(mes);
		a = atoi(ano);

		if(a < 0)
			res = 0;

		if(m<1 || m>12)
			res = 0;
	}

	if(res == 1){
		int leap;
		int mon_days[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
		if(((a%4==0) && (a%100!=0)) || (a%400==0))
			leap=1;
		else
			leap=0;
	
		mon_days[1]+=leap;
	
		if(d>mon_days[m-1] || d<1)
			res = 0;
	}

	linha=tmp;
	free(linha);
	free(dia);
	free(ano);
	free(mes);
	return res;

}

int converte_string_data(char* string, struct tm* data){
	
	int ano=0, mes=0, dia=0;

	if(sscanf(string, "%2d/%2d/%4d", &dia, &mes, &ano) == 3){
		data->tm_year=ano-1900;

		data->tm_mon=mes-1;
		data->tm_mday=dia;
		
		data->tm_hour = 0;
		data->tm_min = 0;
		data->tm_sec = 0;
	}
	else return 0;

	return 1;
}

int comparaDatas(char* dt1, char* dt2){

	struct tm data1 = {0};
	struct tm data2 = {0};

	converte_string_data(dt1, &data1);
	converte_string_data(dt2, &data2);

	if(difftime(timegm(&data1), timegm(&data2))<0.0)
		return 1;
	if(difftime(timegm(&data1), timegm(&data2))==0.0)
		return 0;
	else
		return -1;
}

int calculaIdade(char* data_nascimento){

	struct tm dt = {0};
	struct tm data_ref={0};
	converte_string_data(data_nascimento, &dt);
	converte_string_data(ref, &data_ref);
	double idade1=difftime(timegm(&data_ref), timegm(&dt));
	int idade=idade1/31556952;
	
	return idade;
}

int isNumber(char s[])
{
    for (int i = 0; s[i]!= '\0'; i++)
    {
        if (isdigit(s[i]) == 0){
            return 0;
        }
    }
    return 1;
}

int isDouble(char s[])
{
	int counter=0;
    for (int i = 0; s[i]!= '\0'; i++)
    {
    	if(s[0]=='.')
    		return 0;

    	if(s[i]=='.'){
    		counter++;
    		if(counter>1)
    			return 0;
    	}
    	else{
    		if(isdigit(s[i])==0)
    			return 0;
    	}
    }
    return 1;
}


void printData(struct tm* data){

	char teste[10];

	strftime(teste, 11, "%d/%m/%Y",(data));

	printf("%s\n", teste);
}

char* printDatatoString(struct tm* data){
	char *teste=malloc(sizeof(char)*11);
	strftime(teste, 11, "%d/%m/%Y",(data));
	return teste;
}

char* printFloatToString(float f) { //print sempre com duas casas depois da virgula porque é um preço
	int int_part = (int) f;
	int count = 0;
	while (int_part != 0){
		count++;
		int_part = int_part/10;
	}
	char* res = malloc(sizeof(char) * (count+3+4)); //+3 por causa do ponto, sinal e \0

	sprintf(res, "%.3f\n", f);

	return res;
}
