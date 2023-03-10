#ifndef ___FUNCAUX_H___
#define ___FUNCAUX_H___

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void printascii(char* line);

/**
*\brief Verifica se uma string contém apenas numeros.
*@param s com a string a ser verificada
*@returns 1 caso seja uma string válida, 0 caso contrário
*/
int isNumber(char s[]);

/**
*\brief Verifica se uma string contém um numero decimal.
*@param s com a string a ser verificada
*@returns 1 caso seja uma string válida, 0 caso contrário
*/
int isDouble(char s[]);

/**
*\brief Converte uma string para uma data numa struct tm
*@param string com a data a ser guardada
*@param apontador para uma estrutura struct tm para conter uma data
*@returns 1 caso tenha sido uma data válida, 0 caso contrário (seja uma data inválida)
*/
int converte_string_data(char* string, struct tm* data);

/**
*\brief Verifica se uma string está bem formatada
*@param string com a data a ser verificada
*@param sep apontador para uma string que contém os caracteres de separação da data
*@returns 1 caso tenha sido uma data válida, 0 caso contrário (seja uma data inválida)
*/
int stringdatavalida(char* string, char* sep);

/**
*\brief Compara duas datas e verifica qual a mais antiga
*@param dt1 com a primeira data a comparar
*@param dt2 com a segunda data a comparar
*@returns 1 caso a dt2 venha depois da dt1, -1 caso a dt2 venha antes da dt1, 0 caso sejam iguais
*/
int comparaDatas(char* dt1, char* dt2);

/**
*\brief Calcula a idade de uma pessoa
*@param data_nascimento com a data de nascimento da pessoa a calcular
*@returns a idade calculada
*/
int calculaIdade(char* data_nascimento);

/**
*\brief Imprime uma stuct tm data.
*@param apontador para uma struct tm que contém a data a ser impressa
*/
void printData(struct tm* data);

/**
*\brief Imprime uma struct tm data para uma string que é retornada.
*@param apontador para uma struct tm que contém a data a ser impressa
*@returns a string com a data
*/
char* printDatatoString(struct tm* data);

/**
*\brief Transforma um float numa string
*@param f float a transformar
*@returns a string com o float
*/
char* printFloatToString(float f);

#endif
