#ifndef ___USER_H___
#define ___USER_H___

#include <stdlib.h>
#include"funcAux.h"
#include "../libs/glibWarningAvoid.h"

typedef struct user* User;

/**
\brief Várias funções de gets para obter a informação de um User
*/
char* getUserUName(User u);
char* getUserNome(User u);
char* getUserGenero(User u);
char* getUserDataNascimento(User u);
char* getUserDataConta(User u);
char* getUserMetodoPag(User u);
char* getUserStatus(User u);
double getUserScoreMedio(User u);
double getUserScoreTotal(User u);
int getUserNumViag(User u);
double getUserTotalGasto(User u);
char* getUserDataUltViag(User u);
double getUserKmPerc(User u);

/**
\brief Várias funções para actualizar a informação de um User
*/
void updateUserAvalicaoMedia(User u);
void updateUserScoreTotal(User u, double score);
void updateUserNumViagens(User u);
void updateTotalGasto(User u, double gasto, double gorjeta);
void mudarDataUser(User u, char* data);
void updateUserDataUltimaViagem(char** u, char* data);
void updateKmsPercorridos(User u, double kms);

int validaUser(User user);
char* printUser(User u, int tamanholinha);
User novoUser(char* line, char* sep);
void deleteUser(User u);
void deleteUserKey(char* key);

#endif //___USER_H___