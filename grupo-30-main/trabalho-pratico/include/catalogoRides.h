#ifndef ___CAT_RIDES_H___
#define ___CAT_RIDES_H___
#include "rides.h"

/**
*\brief Estrutura para armazenar um Catálogo de Viagens
*/
typedef struct catRides* CatRides;

/**
*\brief Inicializa uma estutura para armazenar um Catálogo de Viagens
*@return um Catálogo de Viagens inicializado a vazio
*/
CatRides initCatRides();

/**
*\brief Elimina os dados de um Catálogo de Viagens
*@param rides Catálogo de Viagens a eliminar
*/
void destroiCatRides(CatRides rides);

/**
*\brief Insere uma Viagem num Catálogo de Viagens
*@param rides Catálogo de Viagens onde vai inserir
*@param r Viagem a inserir
*/
void insereRide(CatRides rides, Ride r);

/**
*\brief Verifica se uma dada viagem com id "key" esta no Catálogo de Viagens
*@param rides um Catálogo de Viagens inicializado
*@param key id de uma Viagem a procurar
*@return TRUE caso pertença, FALSE caso contrário
*/
int contemRide(CatRides rides, char* key);

/**
*\brief Procura se uma dada viagem com id "key" esta no Catálogo de Viagens e devolve um apontador para ela
*@param rides um Catálogo de Viagens inicializado
*@param key id de uma Viagem a procurar
*@return A Viagem identificada pela key, NULL caso a key não exista
*/
Ride procuraRide(CatRides rides, char* key);

/**
*\brief Aplica uma função a todos os elementos de um Catálogo de Viagens
*@param rides um Catálogo de Viagens inicializado
*@param func Função a ser realizada por todos os elementos
*@param info Estrutura auxilar para guardar dados, comparar,etc
*/
void foreachRide(CatRides rides, GHFunc func, gpointer info);

#endif
