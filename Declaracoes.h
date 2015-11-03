#define MAX 4
#define MIN 2

#define VERMELHO "\033[31m"
#define RESETA "\033[0m"

typedef struct btreeNode {
      int val[MAX + 1], count;
      char *data[MAX + 1];
      struct btreeNode *link[MAX + 1];
} btreeNode;

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
  struct Tabela *tabela; // tabela a que esse tipo pertence (ignore para INT e CHAR)
} Tipo;

typedef struct Coluna {
  char *nome; // nome da coluna
  // salva espaco
  union {
    char *nome_do_tipo; // nome do tipo (string)
    Tipo *tipo; // ponteiro para o tipo
  };
  int tamanho; // quantidade de items (ignore se chave estrangeira)
  int distancia; // distancia na memoria para esse item
} Coluna;

typedef struct Tabela {
  Tipo tipo;
  int versao;
  char *nome;
  int quantidade_colunas;
  Coluna *colunas;
  int tamanho_binario;
  int ultimo_id;
  btreeNode *items;
} Tabela;

typedef struct CabecalhoTabela {
  int versao;
  int tamanho;
  int itens;
  int ultimo_id;
} CabecalhoTabela;

void createFiles();//FUNCAO QUE CRIA OS ARQUIVOS
void writeEntity(char *nome);//FUNCAO QUE GRAVA ENTIDADES NOS ARQUIVOS
void readFiles();//FUNCAO QUE LE TODO O ARQUIVO E PRINTA NA TELA
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
int lerCabecalho(Tabela *, CabecalhoTabela *);
void criarTabela(Tabela *);
void mostrarMenu();
void menuCRUD(Tabela *nome);
void inserirElemento(Tabela *);
void listarElementos(Tabela *);
void alterarElemento(Tabela *);
void removerElemento(Tabela *);

//
void inserirNaArvore(Tabela *, int, char *);
