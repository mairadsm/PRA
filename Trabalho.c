/*********************************/
/* Aluna: Maira da Silva Machado */
/*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CuTest.h"
#include "Declaracoes.h"

FILE *arqGeral;
FILE *arqIndice;

tabela entidadeGeral;

// limpa buffer do teclado
void purge() {
  // descobre o sistem usando o preprocessador
  #if defined(_WIN32) || defined(__WIN32__)
    fflush(stdin);
    //#warning Estou no Windows!
  #elif defined(__MACH__) || defined(__APPLE__)
    fpurge(stdin);
    //#warning Estou num Mac OS X!
  #elif defined(__GNUC__)
    __fpurge(stdin);
    //#warning Estou no Linux!
  #else
    #error em que sistema voce esta compilando???
  #endif
}

int main(){
  
  leiaTabelas();
  
  createFiles();

  while(1){
    mostrarMenu();
  }
  return 0;
}

void writeEntity(char *nome){
    char *string,aux[100];
    int numero,i;
    tabela auxTabela;
    string=aux;
    arqGeral=fopen(nome,"ab");
    for(i=0;i<entidadeGeral.qtd_campos;i++){
        printf("Digite o %s:\n",entidadeGeral.campos[i]);
        if(strcmp(entidadeGeral.tipos[i],"int")==0){
            purge();
            gets(string);
            //fwrite(entidadeGeral.campos[i],sizeof(entidadeGeral.campos[i]),1,arqGeral);
            if(strcmp(entidadeGeral.campos[i],"id")==0){
                fclose(arqGeral);
                auxTabela=findOne(nome,atoi(string));
                arqGeral=fopen(nome,"ab");
                if(auxTabela.qtd_campos!=-1){
                    puts("Entidade com este ID ja existe!\nProcure digitar outro ID\n");
                    return;
                }
            }
            fwrite(string,entidadeGeral.tamanhos[i],1,arqGeral);
            string[0]='\0';
        }
        else if(strcmp(entidadeGeral.tipos[i],"char")==0){
            purge();
            gets(string);
            if(strcmp(entidadeGeral.campos[i],"id")==0){
                auxTabela=findOne(nome,atoi(string));
                if(auxTabela.qtd_campos!=-1){
                    puts("Entidade com este ID ja existe!\nProcure digitar outro ID\n");
                }
                return;
            }
            //fwrite(entidadeGeral.campos[i],sizeof(entidadeGeral.campos[i]),1,arqGeral);
            fwrite(string,entidadeGeral.tamanhos[i],1,arqGeral);
            string[0]='\0';
        }
    }
    fclose(arqGeral);
    ordena(nome);
}

void readFiles(char *nome){
    char string[1000]="\0";
    int tam_arq=0,i,j,numero;
    arqGeral=fopen(nome,"rb");
    fseek(arqGeral,0,SEEK_END);
    tam_arq=ftell(arqGeral);
    rewind(arqGeral);
    tam_arq-=entidadeGeral.tamanho_header;
    fseek(arqGeral,entidadeGeral.tamanho_header,SEEK_CUR);
    if(tam_arq==0){
        puts("Arquivo Nao contem Entidades!");
    }
    else{
        while(tam_arq!=0){
            for(i=0;i<entidadeGeral.qtd_campos;i++){
                if(strcmp(entidadeGeral.tipos[i],"int")==0){
                    fread(string,sizeof(char),entidadeGeral.tamanhos[i],arqGeral);
                    printf("\t%s:\t%i",entidadeGeral.campos[i],atoi(string));
                }
                else if(strcmp(entidadeGeral.tipos[i],"char")==0){
                    fread(string,sizeof(char),entidadeGeral.tamanhos[i],arqGeral);
                    printf("\t%s:\t%s",entidadeGeral.campos[i],string);
                }
                tam_arq-=entidadeGeral.tamanhos[i];
            }
            puts("");
        }
    }
    fclose(arqGeral);
}

tabela findOne(char *nome,int ID){
    tabela aux;
    char string[1000]="\0";
    int tam_arq=0,i,j,numero;
    aux.campos=(char **)malloc(sizeof(char *)*entidadeGeral.qtd_campos);
    aux.tipos=(char **)malloc(sizeof(char *)*entidadeGeral.qtd_campos);
    aux.tamanhos=(int *)malloc(sizeof(int)*entidadeGeral.qtd_campos);
    for(i=0;i<entidadeGeral.qtd_campos;i++){
        aux.campos[i]=(char *)malloc(sizeof(char)*100);
        aux.tipos[i]=(char *)malloc(sizeof(char)*100);
    }
    arqGeral=fopen(nome,"rb");
    fseek(arqGeral,0,SEEK_END);
    tam_arq=ftell(arqGeral);
    rewind(arqGeral);
    tam_arq-=entidadeGeral.tamanho_header;
    fseek(arqGeral,entidadeGeral.tamanho_header,SEEK_CUR);
    if(tam_arq!=0){
        while(tam_arq!=0){
            for(i=0;i<entidadeGeral.qtd_campos;i++){
                if(strcmp(entidadeGeral.tipos[i],"int")==0){
                    fread(string,sizeof(char),entidadeGeral.tamanhos[i],arqGeral);
                    strcpy(aux.campos[i],string);
                    strcpy(aux.tipos[i],entidadeGeral.tipos[i]);
                    aux.tamanhos[i]=entidadeGeral.tamanhos[i];
                    //printf("\t%s:\t%i",entidadeGeral.campos[i],atoi(string));
                }
                else if(strcmp(entidadeGeral.tipos[i],"char")==0){
                    fread(string,sizeof(char),entidadeGeral.tamanhos[i],arqGeral);
                    strcpy(aux.tipos[i],entidadeGeral.tipos[i]);
                    strcpy(aux.campos[i],string);
                    aux.tamanhos[i]=entidadeGeral.tamanhos[i];
                    //printf("\t%s:\t%s",entidadeGeral.campos[i],string);
                }
                tam_arq-=entidadeGeral.tamanhos[i];
            }
            //puts("");
            for(i=0;i<entidadeGeral.qtd_campos;i++){
                //printf("AAA: %i %s %i\n",atoi(aux.campos[i]),entidadeGeral.campos[i],ID);
                if(atoi(aux.campos[i])==ID && strcmp("id",entidadeGeral.campos[i])==0){
                    aux.qtd_campos=entidadeGeral.qtd_campos;
                    strcpy(aux.nome_entidade,entidadeGeral.nome_entidade);
                    aux.tamanho_header=entidadeGeral.tamanho_header;
                    fclose(arqGeral);
                    return aux;
                }
            }
        }
    }
    //printf("Entidade Nao Encontrada!\n");
    fclose(arqGeral);
    aux.qtd_campos=-1;
    return aux;
}

tabela *chargeEntity(char *nome){
    tabela *vet;
    char string[1000]="\0";
    int tam_arq=0,i,j,numero,cont=0;
    vet=(tabela *)malloc(sizeof(tabela));
    arqGeral=fopen(nome,"rb");
    fseek(arqGeral,0,SEEK_END);
    tam_arq=ftell(arqGeral);
    rewind(arqGeral);
    tam_arq-=entidadeGeral.tamanho_header;
    fseek(arqGeral,entidadeGeral.tamanho_header,SEEK_CUR);
    if(tam_arq==0){
        puts("Arquivo Nao contem Entidades!");
    }
    else{
        while(tam_arq!=0){
            cont++;
            vet=(tabela *)realloc(vet,sizeof(tabela)*cont);
            vet[cont-1].campos=(char **)malloc(sizeof(char *)*entidadeGeral.qtd_campos);
            vet[cont-1].tipos=(char **)malloc(sizeof(char *)*entidadeGeral.qtd_campos);
            vet[cont-1].tamanhos=(int *)malloc(sizeof(int)*entidadeGeral.qtd_campos);
            for(i=0;i<entidadeGeral.qtd_campos;i++){
                vet[cont-1].campos[i]=(char *)malloc(sizeof(char)*100);
                vet[cont-1].tipos[i]=(char *)malloc(sizeof(char)*100);
            }
            for(i=0;i<entidadeGeral.qtd_campos;i++){
                fread(string,sizeof(char),entidadeGeral.tamanhos[i],arqGeral);
                strcpy(vet[cont-1].tipos[i],entidadeGeral.tipos[i]);
                strcpy(vet[cont-1].campos[i],string);
                vet[cont-1].tamanhos[i]=entidadeGeral.tamanhos[i];
                tam_arq-=entidadeGeral.tamanhos[i];
            }
            vet[cont-1].qtd_campos=entidadeGeral.qtd_campos;
        }
    }
    fclose(arqGeral);
    cont++;
    vet=(tabela *)realloc(vet,sizeof(tabela)*cont);
    vet[cont-1].qtd_campos=-1;
    return vet;
}

void changeEntity(char *nome){
    int ID,qnt_elementos=0,i,j,flag=0;
    tabela *vet;
    char novo[100];
    puts("Digite o ID do elemento que deseja alterar");
    scanf("%i",&ID);
    vet=chargeEntity(nome);
    i=0;
    while(vet[i].qtd_campos!=-1){
        qnt_elementos++;
        i++;
    }
    for(i=0;i<qnt_elementos;i++){
        if(ID==atoi(vet[i].campos[0])){
            for(j=1;j<entidadeGeral.qtd_campos;j++){
                purge();
                printf("Digite o novo %s\n",entidadeGeral.campos[j]);
                scanf("%s",novo);
                strcpy(vet[i].campos[j],novo);
                novo[0]='\0';
            }
            flag=1;
            break;
        }
    }
    if(flag==0){
        puts("ID da entidade nao encontrado!");
        return;
    }
    else{
        arqGeral=fopen(nome,"wb");
        if(strcmp(nome,"Autor")==0){
            fwrite("qnt=107,entidade=[Autor],qnt_campos=[3],campos=[id,nome,sobrenome],tamanho=[6,20,20],tipo=[int,char,char]",sizeof(char),107,arqGeral);
        }
        else if(strcmp(nome,"Leitor")==0){
            fwrite("qnt=145,entidade=[Leitor],qnt_campos=[6],campos=[id,nome,fone,endereco,cidade,estado],tamanho=[6,30,20,40,40,2],tipo=[int,char,char,int,int,int]",sizeof(char),145,arqGeral);
        }
        else if(strcmp(nome,"Livro")==0){
            fwrite("qnt=140,entidade=[Livro],qnt_campos=[5],campos=[id,titulo,editora,anoPublicacao,isbn],tamanho=[6,30,30,11,20],tipo=[int,char,char,int,char]",sizeof(char),140,arqGeral);
        }
        else if(strcmp(nome,"AutorDoLivro")==0){
            fwrite("qnt=116,entidade=[AutorDoLivro],qnt_campos=[3],campos=[autorId,livroId,sequence],tamanho=[4,6,2],tipo=[int,int,int]",sizeof(char),116,arqGeral);
        }
        for(i=0;i<qnt_elementos;i++){
            for(j=0;j<entidadeGeral.qtd_campos;j++){
                fwrite(vet[i].campos[j],entidadeGeral.tamanhos[j],1,arqGeral);
            }
        }
    }
    fclose(arqGeral);
}

void removeEntity(char *nome){
    int ID,qnt_elementos=0,i,j,flag=0;
    tabela *vet;
    char novo[100];
    puts("Digite o ID do elemento que deseja remover");
    scanf("%i",&ID);
    vet=chargeEntity(nome);
    i=0;
    while(vet[i].qtd_campos!=-1){
        qnt_elementos++;
        i++;
    }
    for(i=0;i<qnt_elementos;i++){
        if(ID==atoi(vet[i].campos[0])){
            flag=1;
            break;
        }
    }
    if(flag==0){
        puts("ID da entidade nao encontrado!");
        return;
    }
    else{
        arqGeral=fopen(nome,"wb");
        if(strcmp(nome,"Autor")==0){
            fwrite("qnt=107,entidade=[Autor],qnt_campos=[3],campos=[id,nome,sobrenome],tamanho=[6,20,20],tipo=[int,char,char]",sizeof(char),107,arqGeral);
        }
        else if(strcmp(nome,"Leitor")==0){
            fwrite("qnt=145,entidade=[Leitor],qnt_campos=[6],campos=[id,nome,fone,endereco,cidade,estado],tamanho=[6,30,20,40,40,2],tipo=[int,char,char,int,int,int]",sizeof(char),145,arqGeral);
        }
        else if(strcmp(nome,"Livro")==0){
            fwrite("qnt=140,entidade=[Livro],qnt_campos=[5],campos=[id,titulo,editora,anoPublicacao,isbn],tamanho=[6,30,30,11,20],tipo=[int,char,char,int,char]",sizeof(char),140,arqGeral);
        }
        else if(strcmp(nome,"AutorDoLivro")==0){
            fwrite("qnt=116,entidade=[AutorDoLivro],qnt_campos=[3],campos=[autorId,livroId,sequence],tamanho=[4,6,2],tipo=[int,int,int]",sizeof(char),116,arqGeral);
        }
        for(i=0;i<qnt_elementos;i++){
            for(j=0;j<entidadeGeral.qtd_campos;j++){
                if(ID!=atoi(vet[i].campos[0]))
                    fwrite(vet[i].campos[j],entidadeGeral.tamanhos[j],1,arqGeral);
            }
        }
    }
    puts("Entidade Removida com Sucesso!");
    fclose(arqGeral);
}


void carrega_entidadeGeral(char *nome){
    char buffer[200],auxiliar[50];
    int tamanho,i,j,k,cont=0,cont_campos,cont_tamanhos,cont_tipos;
    if(arqGeral=fopen(nome,"rb")){
        fseek(arqGeral,4,SEEK_SET);//andamos para pegar os valores do total do header
        fread(&buffer,sizeof(char),3,arqGeral);//lemos o valor
        buffer[3]='\0';//fechamos a string
        tamanho=atoi(buffer);
        entidadeGeral.tamanho_header=tamanho;
        tamanho-=8;
        fseek(arqGeral,8,SEEK_SET);
        fread(&buffer,sizeof(char),tamanho,arqGeral);
        fclose(arqGeral);//como ja temos o header salvo no buffer, fechamos o arquivo
        for(i=0;i<tamanho;i++){
            j=0;
            cont_campos=0;
            cont_tipos=0;
            cont_tamanhos=0;
            if(buffer[i]=='['){
                auxiliar[0]='\0';
                i++;
                cont++;
                while(buffer[i]!=']'){
                    if(buffer[i]==','){
                        if(cont==3){
                            entidadeGeral.campos[cont_campos]=(char *)malloc(sizeof(char)*100);
                            for(k=0;auxiliar[k]!='\0';k++){
                                entidadeGeral.campos[cont_campos][k]=auxiliar[k];
                                entidadeGeral.campos[cont_campos][k+1]='\0';
                            }
                            cont_campos++;
                            j=0;
                            auxiliar[0]='\0';
                        }
                        else if(cont==4){
                            entidadeGeral.tamanhos[cont_tamanhos]=atoi(auxiliar);
                            cont_tamanhos++;
                            j=0;
                            auxiliar[0]='\0';
                        }
                        else if(cont==5){
                            entidadeGeral.tipos[cont_tipos]=(char *)malloc(sizeof(char)*100);
                            for(k=0;auxiliar[k]!='\0';k++){
                                entidadeGeral.tipos[cont_tipos][k]=auxiliar[k];
                                entidadeGeral.tipos[cont_tipos][k+1]='\0';
                            }
                            cont_tipos++;
                            j=0;
                            auxiliar[0]='\0';
                        }
                    }
                    else{
                        auxiliar[j]=buffer[i];
                        j++;
                        auxiliar[j]='\0';
                    }
                    i++;
                }
                if(cont==1){
                    strcpy(entidadeGeral.nome_entidade,auxiliar);
                    auxiliar[0]='\0';
                }
                else if(cont==2){
                    entidadeGeral.qtd_campos=atoi(auxiliar);
                    entidadeGeral.campos=(char **)malloc(sizeof(char *)*entidadeGeral.qtd_campos);
                    entidadeGeral.tipos=(char **)malloc(sizeof(char *)*entidadeGeral.qtd_campos);
                    entidadeGeral.tamanhos=(int *)malloc(sizeof(int)*entidadeGeral.qtd_campos);
                    auxiliar[0]='\0';
                }
                else if(cont==3){
                    entidadeGeral.campos[cont_campos]=(char *)malloc(sizeof(char)*100);
                    for(k=0;auxiliar[k]!='\0';k++){
                        entidadeGeral.campos[cont_campos][k]=auxiliar[k];
                        entidadeGeral.campos[cont_campos][k+1]='\0';
                    }
                    auxiliar[0]='\0';
                }
                else if(cont==4){
                    entidadeGeral.tamanhos[cont_tamanhos]=atoi(auxiliar);
                    auxiliar[0]='\0';
                }
                else if(cont==5){
                    entidadeGeral.tipos[cont_tipos]=(char *)malloc(sizeof(char)*100);
                    for(k=0;auxiliar[k]!='\0';k++){
                        entidadeGeral.tipos[cont_tipos][k]=auxiliar[k];
                        entidadeGeral.tipos[cont_tipos][k+1]='\0';
                    }
                    auxiliar[0]='\0';
                }
            }
        }
    }
}

void ordena(char *nome){
    char string[1000]="\0", index[100]="\0";
    int tam_arq=0, tam_arq_aux=0,i,j,numero, count=0, ii=0, pos, v;
    arqGeral=fopen(nome,"rb");
    fseek(arqGeral,0,SEEK_END);
    tam_arq=ftell(arqGeral);
    rewind(arqGeral);
    tam_arq-=entidadeGeral.tamanho_header;
    tam_arq_aux = tam_arq;
    fseek(arqGeral,entidadeGeral.tamanho_header,SEEK_CUR);
    if(tam_arq==0){
        puts("Arquivo Nao contem Entidades!");
    }
    else{
        while(tam_arq!=0){
            for(i=0;i<entidadeGeral.qtd_campos;i++){
                fread(string,sizeof(char),entidadeGeral.tamanhos[i],arqGeral);
                tam_arq-=entidadeGeral.tamanhos[i];
            }
	        count++;
        }
        heap vet[count];

        fseek(arqGeral,entidadeGeral.tamanho_header,SEEK_SET);

        pos = entidadeGeral.tamanho_header;

        while(tam_arq_aux!=0){
            for(i=0;i<entidadeGeral.qtd_campos;i++){
                fread(string,sizeof(char),entidadeGeral.tamanhos[i],arqGeral);
                if(strcmp(entidadeGeral.tipos[i],"int")==0){
                        if((strcmp(entidadeGeral.campos[i],"id")==0)){
                         vet[ii].id = atoi(string);
                    }
                }
                tam_arq_aux-=entidadeGeral.tamanhos[i];
            }
            vet[ii].pos = pos;
            pos = ftell(arqGeral);
            ii++;
        }
        fclose(arqGeral);

        for(i=0;i<count;i++){
            printf("\nid - %d, pos - %d", vet[i].id, vet[i].pos);
        }

        heapsort2(vet, count);


        strcpy(index, nome);
        strcat(index, "Index");
        arqIndice = fopen(index,"wb");

        for(i=0;i<count;i++){
            fwrite(&vet[i],sizeof(heap),1,arqIndice);
        }
        fclose(arqIndice);
    }
}

void heapsort2(heap a[], int n){

   int i = n / 2, pai, filho, t, k;


   for (;;) {
      if (i > 0) {
          i--;
          t = a[i].id;
          k = a[i].pos;
      } else {
          n--;
          if (n == 0)
            return;
          t = a[n].id;
          k = a[n].pos;
          a[n].id = a[0].id;
          a[n].pos = a[0].pos;
      }

      pai = i;

      //Primeiro será feita a comparação com o filho da esquerda.
      filho = i * 2 + 1;

      while (filho < n) {

         //Se o filho da esquerda for menor do que o filho da direita,então será feita a troca do filho que será comparado.
          if ((filho + 1 < n)  &&  (a[filho + 1].id > a[filho].id))
              filho++;
          if (a[filho].id > t){
             a[pai].id = a[filho].id;
             a[pai].pos = a[filho].pos;
             pai = filho;
             filho = pai * 2 + 1;
          }else
             break;
          }
            a[pai].id = t;
            a[pai].pos = k;
        }
   }

void mostraIndex(char *nome){
    char nomea[100];
    heap aux;
    int tam = 0;
    strcpy(nomea,nome);
    strcat(nomea,"Index");
    arqIndice = fopen(nomea, "rb");
    while(!feof(arqIndice)){
        fread(&aux,sizeof(heap),1,arqIndice);
        printf("\nid: %d, pos: %d", aux.id, aux.pos);
    }
    purge();
    
    fclose(arqIndice);
}

//----------------------------------------------------------------------------//

int quantidade_tabelas = 0;
Tabela *tabelas = NULL;

Tipo INT;
Tipo CHAR;

void leiaTabelas() {
  FILE *arquivo = fopen("Tabelas", "r");
  if(arquivo) {
    
    // enquanto o arquivo nao estiver vazio
    while(!feof(arquivo)) {
      
      quantidade_tabelas++;
      
      tabelas = realloc(tabelas, quantidade_tabelas * sizeof(Tabela));
      
      leiaTabela(arquivo, &tabelas[quantidade_tabelas - 1]);
      
    }
    
    fclose(arquivo);
    
  } else {
    printf("O arquivo de tabelas não existe!\n");
    exit(1);
  }
  
  checarConsistencia();
  
}

int fpeek(FILE *arquivo) {
  int c = fgetc(arquivo);
  ungetc(c, arquivo);
  return c;
};


void leiaTabela(FILE *arquivo, Tabela *tabela) {
  int versao;
  char nome[256] = "";
  int resultado = fscanf(arquivo, "%[^() ]%d(", nome, &versao);
  nome[sizeof(nome) - 1] = 0;
  
  if(resultado == 0 || resultado == EOF) {
    printf("Erro ao ler o arquivo de tabelas!\n");
    exit(1);
  }
  
  tabela->versao = versao;
  tabela->nome = malloc(strlen(nome) + 1);
  strcpy(tabela->nome, nome);
  
  leiaColunas(arquivo, tabela);
  
}

void leiaColunas(FILE *arquivo, Tabela *tabela) {
  char nome_coluna[256] = "";
  char tipo[256] = "";
  int tamanho = 0;
  
  tabela->colunas = NULL;
  tabela->quantidade_colunas = 0;
  
  while(1) {
    
    // vamos ignorar espaços em branco dentro da tabela ;)
    fscanf(arquivo, "%[ \r\n\t]", nome_coluna); // < variável auxiliar
    
    // limpa os buffers
    nome_coluna[0] = 0;
    tipo[0] = 0;
    tamanho = 0;
    
    // ve se terminou a tabela
    if(fpeek(arquivo) == ')') {
      // pula uma linha
      int resultado = fscanf(arquivo, ")%[\r\n]", nome_coluna); // < variável auxiliar
      
      if(resultado == 0 || resultado == EOF) {
        printf("Erro ao ler o arquivo de tabelas!\n");
        exit(1);
      }
      break;
    }
    
    int resultado = fscanf(arquivo, "%[^, \r\n\t] %[^,[ \r\n\t]", nome_coluna, tipo);
    
    if(resultado == 0 || resultado == EOF) {
      printf("Erro ao ler o arquivo de tabelas!\n");
      exit(1);
    }
    
    if(strcmp(tipo, "int") == 0 || strcmp(tipo, "char") == 0) {
      
      resultado = fscanf(arquivo, "[%d]", &tamanho);
      
      if(resultado == 0 || resultado == EOF) {
        printf("Erro ao ler o arquivo de tabelas!\n");
        exit(1);
      }
    } else {
      //
    }
    
    if(fpeek(arquivo) == ',') {
      fgetc(arquivo);
    }
    
    nome_coluna[sizeof(nome_coluna) - 1] = 0;
    tipo[sizeof(tipo) - 1] = 0;
    
    // salvar coluna na tabela!
    tabela->quantidade_colunas++;
    tabela->colunas = realloc(tabela->colunas, tabela->quantidade_colunas * sizeof(Coluna));
    
    Coluna *coluna = &tabela->colunas[tabela->quantidade_colunas - 1];
    
    coluna->nome = malloc(strlen(nome_coluna) + 1);
    strcpy(coluna->nome, nome_coluna);
    
    coluna->tamanho = tamanho;
    
    coluna->nome_do_tipo = malloc(strlen(tipo) + 1);
    strcpy(coluna->nome_do_tipo, tipo);
    
  };
  
  
};

int compara_tabelas(Tabela *tabela1, Tabela *tabela2) {
  return strcmp(tabela1->nome, tabela2->nome);
}

int compara_colunas(Coluna *coluna1, Coluna *coluna2) {
  return strcmp(coluna1->nome, coluna2->nome);
}

void checarConsistencia() {
  
  ordenarTabelas();
  
  int i;
  for(i = 0; i < quantidade_tabelas; i++) {
    
    Tabela *tabela = &tabelas[i];
    
    int distancia = 0;
    
    int j;
    for(j = 0; j < tabela->quantidade_colunas; j++) {
      Coluna *coluna = &tabela->colunas[j];
      
      coluna->distancia = distancia;
      
      const char *nome_do_tipo = coluna->nome_do_tipo;
      
      if(strcmp(nome_do_tipo, "int") == 0) {
        coluna->tipo = &INT;
        distancia += coluna->tamanho;
      } else if(strcmp(nome_do_tipo, "char") == 0) {
        coluna->tipo = &CHAR;
        distancia += coluna->tamanho;
      } else {
        
        Tabela *novo_tipo = procuraTabela(nome_do_tipo);
        
        if(novo_tipo == NULL) {
          printf("Relacionamento de chave estrangeira na tabela %s: tabela %s não existe!\n", tabela->nome, nome_do_tipo);
          exit(1);
        }
        
        distancia += sizeof(Tabela *);
        coluna->tipo = &novo_tipo->tipo;
        novo_tipo->tipo.tabela = novo_tipo;
        
      }
      
      // libera memoria que nao vai mais ser usada
      free(nome_do_tipo);
      
    }
    
    // a distancia final e o tamanho do item na memoria
    tabela->tamanho_binario = distancia;
  }
  
}

void ordenarTabelas() {
  // ordena tabelas
  qsort(tabelas, quantidade_tabelas, sizeof(Tabela), &compara_tabelas);
  
  // ordena colunas
  int i;
  for(i = 0; i < quantidade_tabelas; i++) {
    //qsort(tabelas[i].colunas, tabelas[i].quantidade_colunas, sizeof(Coluna), &compara_colunas);
  }
}

Tabela *procuraTabela(const char *nome) {
  // tabela falsa
  Tabela ficticia;
  ficticia.nome = nome;
  
  // como ordenamos, podemos usar pesquisa binaria
  return bsearch(&ficticia, tabelas, quantidade_tabelas, sizeof(Tabela), &compara_tabelas);
}

void createFiles(){
  int i;
  for(i = 0; i < quantidade_tabelas; i++) {
    Tabela *tabela = &tabelas[i];
    
    CabecalhoTabela cabecalho;
    
    if(lerCabecalho(tabela, &cabecalho)) {
      if(tabela->versao < cabecalho.versao) {
        printf("Erro, versão no arquivo de tabelas para %s é menor que a do banco de dados!\n", tabela->nome);
        exit(1);
      }
      if(tabela->versao > cabecalho.versao) {
        criarTabela(tabela);
      }
    } else {
      // cria o arquivo
      criarTabela(tabela);
    }
    
  }
}

int lerCabecalho(Tabela *tabela, CabecalhoTabela *cabecalho) {
  
  FILE *arquivo = fopen(tabela->nome, "rb");
  if(arquivo) {
    
    fread(cabecalho, sizeof(CabecalhoTabela), 1, arquivo);
    
    fclose(arquivo);
    return 1;
  }
  
  return 0;
}

void criarTabela(Tabela *tabela) {
  
  FILE *arquivo = fopen(tabela->nome, "wb");
  
  CabecalhoTabela cabecalho;
  
  cabecalho.versao = tabela->versao;
  cabecalho.tamanho = tabela->tamanho_binario;
  cabecalho.itens = 0;
  
  fwrite(&cabecalho, sizeof(CabecalhoTabela), 1, arquivo);
  
  fclose(arquivo);
  
}

void mostrarMenu() {
  puts("Escolha uma tabela:");
  puts("");
  puts("+- [MENU] ------------------------------------+");
  
  int i;
  for(i = 0; i < quantidade_tabelas; i++) {
    printf("| (%d) %-40s|\n", i + 1, tabelas[i].nome);
  }
  puts("| (0) Sair                                    |");
  puts("+---------------------------------------------+");
  
  printf("> ");
  int opcao;
  scanf("%d", &opcao);
  purge();
  
  if(opcao == 0) {
    puts("Adeus!");
    exit(0);
  }
  
  if(opcao < quantidade_tabelas) {
    menuCRUD(&tabelas[opcao - 1]);
    return;
  }
  
  puts(VERMELHO "Opcao invalida!!!" RESETA);
}

void menuCRUD(Tabela *tabela){
  printf("+- [%s] ", tabela->nome);
  
  int i;
  for(i = 0; i < 40 - strlen(tabela->nome); i++) {
    printf("-");
  }
  
  puts("+");
  puts("| (1) Inserir novo elemento                   |");
  puts("| (2) Mostrar todos os elementos da entidade  |");
  puts("| (3) Alterar um elemento                     |");
  puts("| (4) Remover um elemento                     |");
  puts("| (0) Voltar                                  |");
  puts("+---------------------------------------------+");
  
  printf("> ");
  int opcao;
  scanf("%d", &opcao);
  purge();
  
  switch(opcao) {
    case 0:
      return;
    case 1:
      inserirElemento(tabela);
      menuCRUD(tabela);
      break;
    case 2:
      listarElementos(tabela);
      menuCRUD(tabela);
      break;
    case 3:
      alterarElemento(tabela);
      menuCRUD(tabela);
      break;
    case 4:
      removerElemento(tabela);
      menuCRUD(tabela);
      break;
    default:
      puts(VERMELHO "Opcao invalida!!!" RESETA);
      menuCRUD(tabela);
  };
}

void inserirElemento(Tabela *tabela) {
  
}

void listarElementos(Tabela *tabela) {
  
}

void alterarElemento(Tabela *tabela) {
  
}

void removerElemento(Tabela *tabela) {
  
}
