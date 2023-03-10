#include"funcAux.h"
#include"catalogoRides.h"
#include"catalogoUsers.h"
#include"catalogoDrivers.h"

#define TAMANHO_QUERY1 68

typedef struct arrayQuery* ArrayQuery;

typedef struct viagens* Viagens;

typedef struct catalogos * Catalogos;

/**
\brief Aloca espaço para uma instância de catálogos
@returns Um apontador para uma instância de catálogos já alocada
*/
Catalogos initCatalogos();

/**
\brief Inicializa os campos de um catálogo, nomeadamente os condutores e os utilizadores
@param ct Um apontador para uma instância de Catálogos já inicializada
@param u Um apontador para uma hashtable de utilizadores
@param d Um apontador para uma hashtable de condutores
*/
void setCatalogos(Catalogos ct, CatUsers u, CatDrivers d);

/**
\brief Devolve o top n pedido
*/
int getArrayQuerySize(ArrayQuery array);

/**
\brief Devolve o tamanho efectivo do ArrayQuery
*/
int getArrayQueryLength(ArrayQuery array);
/**
\brief Devolve o array com a ordem dos indíces pelo quais a estrutura ArrayQuery deve ser impressa
*/
int* getArrayQueryOrder(ArrayQuery array);
/**
\brief Devolve um Condutor na posição i do ArrayQuery
*/
Driver getArrayQueryDriver(ArrayQuery array, int i);

/**
\brief Devolve um Utilizador na posição i do ArrayQuery
*/
User getArrayQueryUser(ArrayQuery array, int i);

/**
\brief Devolve a info do ArrayQuery
*/
char* getArrayQueryInfo(ArrayQuery array);

/**
\brief Destrói e liberta o espaço ocupado por um ArrayQuery
*/
void deleteArrayQuery(ArrayQuery a, int query);

GList* getListaViagens(Catalogos ct);

CatDrivers getDrivers(Catalogos ct);

CatUsers getUsers(Catalogos ct);




/**
\brief Calcula os índices pelos quais a estrutura ArrayQuery gerada pela query 2 tem que ser impressa
@param q Um apontador para uma estrutura ArrayQuery
@returns Um apontador para um array de inteiros com a ordem dos índices pelos quais a estrutura deve ser impressa
*/
int* returnIndexesQuery2(ArrayQuery q);

/**
\brief Calcula os índices pelos quais a estrutura ArrayQuery gerada pela query 3 tem que ser impressa
@param q Um apontador para uma estrutura ArrayQuery
@returns Um apontador para um array de inteiros com a ordem dos índices pelos quais a estrutura deve ser impressa
*/
int* returnIndexesQuery3(ArrayQuery q);

/**
\brief Calcula os índices pelos quais a estrutura ArrayQuery gerada pela query 7 tem que ser impressa
@param q Um apontador para uma estrutura ArrayQuery
@returns Um apontador para um array de inteiros com a ordem dos índices pelos quais a estrutura deve ser impressa
*/
int* returnIndexesQuery7(ArrayQuery q);

/**
\brief Função auxiliar a ser chamada por comparaViagens
*/
int compareRides(char* datad1, char* datad2, char* datau1, char* datau2, char* idviagem1, char* idviagem2);

/**
\brief Compara entre duas viagens r1 e r2 de acordo com a forma estipulada no enunciado da query8.
@param r1 Um apontador para uma viagem
@param r2 Um apontador para uma viagem
@param drivers Um apontador para uma hashtable de condutores
@param users Um apontador para uma uma hashtable de utilizadores
@returns Um inteiro que determina se a viagem r1 deve vir antes da viagem r2 na lista resultado (returns 1) ou vice versa (returns -1)
*/
int comparaViagens(Ride r1, Ride r2, CatDrivers drivers, CatUsers users);

/**
\brief Determina qual o índice da lista viagens, a Ride r deve ser inserida
@param viagens Um apontador para uma instância de viagens
@param r Um apontador para uma viagem
@param drivers Um apontador para uma hashtable de condutores
@param users Um apontador para uma uma hashtable de utilizadores
@param query inteiro que identifica qual a query na qual esta função será usada
@returns Um inteiro que determina qual o índice em que r deve ser inserido em viagens
*/
int indexainserir(Viagens viagens, Ride r, CatDrivers drivers, CatUsers users, int query);

/**
\brief Compara entre duas viagens r1 e r2 de acordo com a forma estipulada no enunciado da query9.
@param r1 Um apontador para uma viagem
@param r2 Um apontador para uma viagem
@returns Um inteiro que determina se a viagem r1 deve vir antes da viagem r2 na lista resultado (returns 1) ou vice versa (returns -1)
*/
int compareRidesQ9(Ride a, Ride b);






/**
\brief Imprime a informação de um utilizador ou condutor cujo ID seja igual a chave
@param chave id a procurar nos Catálogos de Condutores ou Utilizadores
@param drivers Catálogo de Condutores onde vai procurar
@param users Catálogo de Utilizadores onde vai procurar
@returns string devidamente formatada com a informação pedida ou com string vazia caso a chave não exista
*/
char* query1(char* chave, CatDrivers drivers, CatUsers users);

/**
\brief Uma função auxiliar chamada pela função 'query2' que para cada condutor de um Catálogo, verifica se ele deve ser inserido no ArrayQuery resultado
@param key Apontador com a chave da Hashtable de condutores - neste caso, o seu ID
@param value Apontador com o valor da Hashtable de condutores - neste caso o próprio condutor
@param data Apontador para a estrutura ArrayQuery a preencher
*/
void query2aux(gpointer key, gpointer value, gpointer data);

/**
\brief Procura no Catálogo de Condutores pelo top N condutores com a avaliação média mais alta
@param n inteiro com o número para fazer o top
@param drivers Catálogo de Condutores onde vai procurar
@returns Um ArrayQuery com os seus campos devidamente preenchidos, nomeadamente o campo array com os n condutores com avaliação mais alta
*/
ArrayQuery query2(int n, CatDrivers drivers);

/**
\brief Uma função auxiliar chamada pela função 'query3' que para cada utilizador de um Catálogo, verifica se ele deve ser inserido no ArrayQuery resultado
@param key Apontador com a chave da Hashtable de utilizadores - neste caso, o seu ID
@param value Apontador com o valor da Hashtable de utilizadores - neste caso o próprio utilizador
@param data Apontador para a estrutura ArrayQuery a preencher
*/
void query3aux(gpointer key, gpointer value, gpointer data);

/**
\brief Procura no Catálogo de Utilizadores pelo top N utilizadores com maior distância viajada
@param n inteiro com o número para fazer o top
@param users Catálogo de Utilizadores onde vai procurar
@returns Um ArrayQuery com os seus campos devidamente preenchidos, nomeadamente o campo array com os n utilizadores com maior distância viajada
*/
ArrayQuery query3 (int n, CatUsers users);

/**
\brief Uma função auxiliar chamada pela função 'query4' que para cada Ride de um Catálogo, verifica se o seu custo deve ser adicionado ao acumulador
@param key Apontador com a chave da Ride - neste caso, o seu ID
@param value Apontador com o valor da Ride - neste caso a própria ride
@param data Apontador para a estrutura ArrayQuery a preencher
*/
void query4aux(gpointer key, gpointer value, gpointer data);

/**
\brief Imprime o preço médio das viagens numa determinada cidade passada por referência
@param city cidade a procurar no Catálogo de Viagens
@param r Catálogo de viagens onde vai procurar
@returns string devidamente formatada com a informação pedida ou com string vazia caso a cidade não exista
*/
char* query4(char *city, CatRides r);

/**
\brief Uma função auxiliar chamada pela função 'query5' que para cada Ride de um Catálogo, verifica se o seu custo deve ser adicionado ao acumulador
@param key Apontador com a chave da Ride - neste caso, o seu ID
@param value Apontador com o valor da Ride - neste caso a própria ride
@param data Apontador para a estrutura ArrayQuery a preencher
*/
void query5aux(gpointer key, gpointer value, gpointer data);

/**
\brief Imprime o preço médio das viagens entre duas datas
@param data_inicial data inicial da procura das viagens no Catálogo de Viagens
@param data_final data final da procura das viagens no Catálogo de Viagens
@param rides Catálogo de viagens onde vai procurar
@returns string devidamente formatada com a informação pedida ou com string vazia caso as datas sejam inválidas
*/
char* query5(char* data_inicial, char* data_final, CatRides rides);

/**
\brief Uma função auxiliar chamada pela função 'query6' que para cada Ride de um Catálogo, verifica se a sua distancia deve ser adicionado ao acumulador
@param key Apontador com a chave da Ride - neste caso, o seu ID
@param value Apontador com o valor da Ride - neste caso a própria ride
@param data Apontador para a estrutura ArrayQuery a preencher
*/
void query6aux(gpointer key, gpointer value, gpointer data);

/**
\brief Imprime a distância média das viagens entre duas datas numa determinada cidade
@param data_inicial data inicial da procura das viagens no Catálogo de Viagens
@param data_final data final da procura das viagens no Catálogo de Viagens
@param city cidade a procurar as viagens no Catálogo de Viagens
@param r Catálogo de viagens onde vai procurar
@returns string devidamente formatada com a informação pedida ou com string vazia caso as datas ou a cidade sejam inválidas
*/
char* query6(char* data_inicial, char* data_final,char *city, CatRides r);

/**
\brief Procura no Catálogo de Condutores pelo top N condutores na cidade 'cidade' com a avaliação média mais alta
@param n inteiro com o número para fazer o top
@param cidade cidade a procurar os condutores no Catálogo de Condutores
@param drivers Catálogo de Condutores onde vai procurar
@returns Um ArrayQuery com os seus campos devidamente preenchidos, nomeadamente o campo array com os n condutores com avaliação mais alto na cidade pretendida
*/
ArrayQuery query7(int n, char* cidade, CatDrivers drivers);

/**
\brief Uma função auxiliar chamada pela função 'query7' que para cada condutor de um Catálogo, verifica se ele deve ser inserido no QueryArray resultado
@param key Apontador com a chave da Hashtable de condutores - neste caso, o seu ID
@param value Apontador com o valor da Hashtable de condutores - neste caso o próprio condutor
@param data Apontador para a estrutura ArrayQuery a preencher
*/
void query7aux(gpointer key, gpointer value, gpointer data);

/**
\brief Lista todas as viagens nas quais o condutor e o utilizador são do género passado e têm perfis com mais do que 'anos' anos
@param genero género que o condutor e o utilizador têm que ter
@param anos número de anos que os perfis têm que ter
@param drivers Catálogo de Condutores onde vai procurar
@param rides Catálogo de Viagens onde vai procurar
@param users Catálogo de Utilizadores onde vai procurar
@returns Uma instância de catálogos com o campo viagens devidamente preenchido com todas as viagens que obedecem aos critérios passados como parâmetro
*/
Catalogos query8(char* genero, int anos, CatDrivers drivers, CatRides rides, CatUsers users);

/**
\brief Uma função auxiliar chamada pela função 'query8' que para cada viagem de um Catálogo, verifica se deve inserir essa viagem em catalogos->viagens
@param key Apontador com a chave da Viagem na Hashtable de viagens - neste caso, o seu ID
@param value Apontador com o valor da viagem na Hashtable de viagens - neste caso a própria viagem
@param data Apontador para a estrutura Catalogos a preencher
*/
void query8aux(gpointer key, gpointer value, gpointer data);

/**
\brief Lista todas as viagens nas quais passageiro deu gorjeta e a data da mesma foi no intervalo de tempo passado
@param data_inicial data inicial do intervalo de tempo a procurar
@param data_final data final do intervalo de tempo a procurar
@param rides Catálogo de Viagens onde vai procurar
@param drivers Catálogo de Condutores onde vai procurar
@param users Catálogo de Utilizadores onde vai procurar
@returns Uma instância de catálogos com o campo viagens devidamente preenchido com todas as viagens que obedecem aos critérios passados como parâmetro
*/
Catalogos query9(char* data_inicial, char* data_final, CatRides rides, CatDrivers drivers, CatUsers users);

/**
\brief Uma função auxiliar chamada pela função 'query9' que para cada viagem de um Catálogo, verifica se deve inserir essa viagem em catalogos->viagens
@param key Apontador com a chave da Viagem na Hashtable de viagens - neste caso, o seu ID
@param value Apontador com o valor da viagem na Hashtable de viagens - neste caso a própria viagem
@param data Apontador para a estrutura Catalogos a preencher
*/
void query9aux(gpointer key, gpointer value, gpointer data);