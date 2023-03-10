#ifndef ___CAT_DRIVERS_H___
#define ___CAT_DRIVERS_H___
#include "driver.h"

/**
*\brief Estrutura para armazenar um Catálogo de Condutores
*/
typedef struct catDrivers* CatDrivers;

/**
*\brief Inicializa uma estutura para armazenar um Catálogo de Condutores
*@return um Catálogo de Condutores inicializado a vazio
*/
CatDrivers initCatDrivers();

/**
*\brief Elimina os dados de um Catálogo de Condutores
*@param CatDrivers Catálogo de Condutores a eliminar
*/
void destroiCatDrivers(CatDrivers drivers);

/**
*\brief Insere um Condutor num Catálogo de Condutores
*@param CatDrivers Catálogo de Condutores onde vai inserir
*@param d Condutor a inserir
*/
void insereDriver(CatDrivers drivers, Driver d);

/**
*\brief Actualiza um Condutor num Catálogo de Condutores
*@param CatDrivers Catálogo de Condutores onde vai actualizar
*@param d Condutor actualizado para inserir
*/
void updateDriver(CatDrivers drivers, Driver d);

/**
*\brief Verifica se um dado condutor com id "key" esta no Catálogo de Condutores
*@param drivers um Catálogo de Condutores inicializado
*@param key id de um Condutor a procurar
*@return TRUE caso pertença, FALSE caso contrário
*/
int contemDriver(CatDrivers drivers, char* key);

/**
*\brief Procura se um dado condutor com id "key" esta no Catálogo de Condutores e devolve um apontador para ele
*@param drivers um Catálogo de Condutores inicializado
*@param key id de um Condutor a procurar
*@return O Condutor identificado pela key, NULL caso a key não exista
*/
Driver procuraDriver(CatDrivers drivers, char* key);

/**
*\brief Aplica uma função a todos os elementos de um Catálogo de Condutores
*@param drivers um Catálogo de Condutores inicializado
*@param func Função a ser realizada por todos os elementos
*@param info Estrutura auxilar para guardar dados, comparar,etc
*/
void foreachDriver(CatDrivers drivers, GHFunc func, gpointer info);
#endif