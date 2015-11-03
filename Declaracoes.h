void createFiles();//FUNCAO QUE CRIA OS ARQUIVOS
void writeEntity(char *nome);//FUNCAO QUE GRAVA ENTIDADES NOS ARQUIVOS
void readFiles();//FUNCAO QUE LE TODO O ARQUIVO E PRINTA NA TELA
void menuCRUD(char *nome); //SUBMENU
void carrega_entidadeGeral(char *nome); //CARREGA A ENTIDADE GERAL DE ACORDO COM O HEADER DO ARQUIVO
tabela findOne(char *nome, int ID);//FUNCAO QUE RETORNA A ENTIDADE CASO ACHE A CHAVE PRIMARIA
tabela *chargeEntity(char *nome);//FUNCAO QUE CARREGA O VETOR DE ENTIDADES
void changeEntity(char *nome); //FUNCAO QUE ALTERA O VALOR DO ID DE UM ELEMENTO
void removeEntity(char *nome);//FUNCAO QUE DELETA UMA ENTIDADE ATRAVES DO ID
// ja existe uma funcao heapsort no Mac
void heapsort2(heap a[], int n);//ORDENA OS ELEMENTOS ATRAVES DO INDICE
void ordena(char *nome);
void mostraIndex(char *nome);
void leiaTabela(FILE *);
void leiaColunas(FILE *, const char *);
void checarConsistencia();
