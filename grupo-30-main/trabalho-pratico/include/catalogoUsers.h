#ifndef ___CAT_USERS_H___
#define ___CAT_USERS_H___
#include "user.h"

/**
*\brief Estrutura para armazenar um Catálogo de Utilizadores
*/
typedef struct catUsers* CatUsers;

/**
*\brief Inicializa uma estutura para armazenar um Catálogo de Utilizadores
*@return um Catálogo de Utilizadores inicializado a vazio
*/
CatUsers initCatUsers();

/**
*\brief Elimina os dados de um Catálogo de Utilizadores
*@param users Catálogo de Utilizadores a eliminar
*/
void destroiCatUsers(CatUsers users);

/**
*\brief Insere uma Viagem num Catálogo de Utilizadores
*@param users Catálogo de Utilizadores onde vai inserir
*@param u Utilizador a inserir
*/
void insereUser(CatUsers users, User u);

/**
*\brief Verifica se uma dado Utilizador com username "key" esta no Catálogo de Utilizadores
*@param users um Catálogo de Utilizadores inicializado
*@param key username de um Utilizador a procurar
*@return TRUE caso pertença, FALSE caso contrário
*/
int contemUser(CatUsers users, char* key);

/**
*\brief Procura se um dado Utilizador com username "key" esta no Catálogo de Utilizadores e devolve um apontador para ele
*@param users um Catálogo de Utilizadores inicializado
*@param key username de um Utilizador a procurar
*@return O Utilizador identificado pela key, NULL caso a key não exista
*/
User procuraUser(CatUsers users, char* key);

/**
*\brief Aplica uma função a todos os elementos de um Catálogo de Utilizadores
*@param users um Catálogo de Utilizadores inicializado
*@param func Função a ser realizada por todos os elementos
*@param info Estrutura auxilar para guardar dados, comparar,etc
*/
void foreachUser(CatUsers Users, GHFunc func, gpointer info);

#endif