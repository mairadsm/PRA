typedef struct{
    char nome_entidade[100];
    int qtd_campos;
    char **campos;
    int *tamanhos;
    char **tipos;
    int tamanho_header;
} tabela;

typedef struct{
    int id;
    int pos;
} heap;

typedef struct Tipo {
  struct Tabela *tabela;
} Tipo;

typedef struct Coluna {
  char *nome;
  // salva espaco
  union {
    char *nome_do_tipo;
    Tipo *tipo;
  };
  int tamanho;
} Coluna;

typedef struct Tabela {
  Tipo tipo;
  
  char *nome;
  int quantidade_colunas;
  Coluna *colunas;
  
} Tabela;

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

void leiaTabelas();
void leiaTabela(FILE *, Tabela *);
void leiaColunas(FILE *, Tabela *);
void checarConsistencia();
void ordenarTabelas();
Tabela *procuraTabela(const char *);
