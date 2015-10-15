#include <stdio.h>
#include <stdlib.h>

void limpa(){
    system("clear");
}


typedef struct LIVRO{
    int idLivro;  //auto incremento //chave primaria
    int anoPublicacao;
    char titulo[30]; //naonulo
    char editora[30];
    char isbn[20]; //naonulo
}LIVRO;

typedef struct LEITOR{
    int idLeitor;  //auto incremento //chave primaria
    char nome[30]; //naonulo
    char fone[20];  //naonulo
    int endereco;
    int cidade;
    int estado;
}LEITOR;

typedef struct AUTOR{
    int idAutor;  //auto incremento
    char nomeAutor[20];
    char sobrenomeAutor[20];
}AUTOR;

typedef struct AUTORDOLIVRO{
    int autorID; //naonulo
    int livroID; //naonulo
    int sequence; //naonulo
}AUTORDOLIVRO;

void LendoArquivo(char nome[],char tipo[])
{
	char ch;
	FILE *fp = fopen(nome,"r");
	if(!fp){//Caso o arquivo nao tenha sido aberto corretamente
    printf("Erro na abertura do arquivo de entrada\n");
        return;
	}
	else{
        while((ch=fgetc(fp))!=EOF)
            printf("%c",ch);
        //if(ch==EOF){ //se encontrou o final do arquivo
		    //printf("\nChegou ao final");
        //}
    }
	getchar();
	fclose(fp);
}

void CriaArquivo(char nome[], char tipo[])
{
	AUTOR autor;
	LIVRO livro;
	LEITOR leitor;
	AUTORDOLIVRO autordolivro;

    FILE *fp = fopen(nome,"a");
	if(!fp){//Caso o arquivo nao tenha sido aberto corretamente
        printf("\nErro em abrir o arquivo para se gravar dados nele, APPEND.\n");
        return;
    }
	else{
        printf("Digite as informações do %s\n",tipo);
        if(strcmp(tipo,"Autor")==0){
            printf("\nDigite o ID-AUTOR: \n");
            scanf("%i",&autor.idAutor);
            printf("\nDigite o Nome Do Autor: \n");
            scanf("%s",autor.nomeAutor);
            printf("\nDigite o Sobrenome do Autor: \n");
            scanf("%s",autor.sobrenomeAutor);
            fprintf(fp,"%d\n%s\n%s\n",autor.idAutor,autor.nomeAutor,autor.sobrenomeAutor);
        }
		else if(strcmp(tipo,"Livro")==0){
            printf("\nDigite o ID-LIVRO: \n");
            scanf("%i",&livro.idLivro);
            printf("\nDigite o Ano de publicação Do Livro: \n");
            scanf("%i",&livro.anoPublicacao);
            printf("\nDigite o Titulo do Livro: \n");
            scanf("%s",livro.titulo);
            printf("\nDigite a Editora do Livro: \n");
            scanf("%s",livro.editora);
            printf("\nDigite o ISBN do Livro: \n");
            scanf("%s",livro.isbn);
            fprintf(fp,"%d\n%d\n%s\n%s\n%s\n",livro.idLivro,livro.anoPublicacao,livro.titulo,livro.editora,livro.isbn);
        }
		else if(strcmp(tipo,"Leitor")==0){
            printf("\nDigite o ID-LEITOR: \n");
            scanf("%i",&leitor.idLeitor);
            printf("\nDigite o Nome do Leitor: \n");
            scanf("%s",leitor.nome);
            printf("\nDigite o Fone Do Leitor: \n");
            scanf("%s",leitor.fone);
            printf("\nDigite o Endereço (int): \n");
            scanf("%i",&leitor.endereco);
            printf("\nDigite a Cidade (int): \n");
            scanf("%i",&leitor.cidade);
            printf("\nDigite o Estado (int): \n");
            scanf("%i",&leitor.estado);
            fprintf(fp,"%d\n%s\n%s\n%d\n%d\n%d\n",leitor.idLeitor,leitor.nome,leitor.fone,leitor.endereco,leitor.cidade,leitor.estado);
        }
		else if(strcmp(tipo,"Autor Do Livro")==0){
            printf("\nDigite o ID DO AUTOR,NO AUTOR DO LIVRO: \n");
            scanf("%i",&autordolivro.autorID);
            printf("\nDigite O ID DO LIVRO, NO AUTOR DO LIVRO: \n");
            scanf("%i",&autordolivro.livroID);
            printf("\nDigite O NUMERO DE SEQUENCIA: \n");
            scanf("%i",&autordolivro.sequence);
            fprintf(fp,"%d\n%d\n%d\n",autordolivro.autorID,autordolivro.livroID,autordolivro.sequence);
        }
        else{
            printf("Nenhuma dessas opçoes de tipo, ERRO>>\n");
            return;
        }
        fclose(fp);
    }
    LendoNaMemoria(nome,tipo);
}

void LendoNaMemoria(char nome[],char tipo[])
{
	AUTOR *autor;
	//LIVRO livro[cont];
	//LEITOR leitor[cont];
	//AUTORDOLIVRO autordolivro[cont];

	char ch,*p_ch,str[40];
	p_ch=&str;
	int cont=0,i=0,valores=0,mem,stopstr=0,flag=0;
	FILE *fp = fopen(nome,"r");
	if(!fp){//Caso o arquivo nao tenha sido aberto corretamente
        printf("Erro na abertura do arquivo de entrada\n");
        return;
	}
	else{
        while((ch=fgetc(fp))!=EOF)
        {
            if(ch=='\n'){//Caso encontre uma nova linha
                cont++;
            }
		 }
        printf("\nValor da contagem: %d\n",cont);
        fclose(fp);
	}
	if(strcmp(tipo,"Autor")==0){
        autor = (AUTOR *) calloc (cont/3,sizeof(AUTOR));
        /*printf("Alocação de autor feita com sucesso");
		for(i=0;i<cont/3;i++){
            printf("Valor de ID autor: %d",autor[i].idAutor);
            printf("Valor de nome autor: %s",autor[i].nomeAutor);
            printf("Valor de sobrenome autor: %s",autor[i].sobrenomeAutor);
		}*/
	}
	fp=fopen(nome,"r");
	while((ch=fgetc(fp))!=EOF){
        if(ch!=' ' && ch!='\n')
            str[stopstr]=ch;
        else
            str[stopstr]='\0';
        stopstr++;
        if(ch=='\n'){//Caso encontre uma nova linha
            if(valores==3)
                valores=0;
            stopstr=0;
            valores++;
            flag=1;
        }
        if(flag==1){
            if(valores==1){ //para ler o id
                mem=atoi(p_ch);
                autor[i].idAutor=mem;
               str[0]="\0";
                flag=0;
            }
            else if(valores==2){ //para ler o Nome
                //str[stopstr+1]="\0";
                strcpy(autor[i].nomeAutor,str);
                str[0]="\0";
                flag=0;
            }
            else if(valores==3){ //para ler o Sobrenome
                //str[stopstr+1]="\0";
                strcpy(autor[i].sobrenomeAutor,str);
                i++;
                strcpy(str,"\0");
                flag=0;
            }
        }
    }
    fclose(fp);
	if(strcmp(tipo,"Autor")==0){
        for(i=0;i<cont/3;i++){
            printf("Valor de ID autor: %d\n",autor[i].idAutor);
            printf("Valor de Nome autor: %s\n",autor[i].nomeAutor);
            printf("Valor de Sobrenoome autor: %s\n",autor[i].sobrenomeAutor);
        }
	}
}

void CriaTodosArquivos()
{

//pode-se fazer mais generico que isso usando um fopen com R,(read), e verificando se o arquivo ja existe, pois assim, caso ele exista
//voce o mantem para os dados contidos neles nao serem perdidos, mas pelo momento cada vez que o codigo for reexecutado os arquivos
//irao iniciar vazio.
FILE *fp;

fp=fopen("autor.txt","w");
//fprintf(fp,"Entidade=autor");
fclose(fp);

fp=fopen("leitor.txt","w");
//fprintf(fp,"Entidade=leitor");
fclose(fp);

fp=fopen("livro.txt","w");
//fprintf(fp,"Entidade=livro");
fclose(fp);

fp=fopen("autordolivro.txt","w");
//fprintf(fp,"Entidade=autordolivro");
fclose(fp);


}

void UpdateArquivo(char nome[])
{
   /* char ch;
    FILE *fp = fopen(nome,"w");

	if(!fp)
	{//Caso o arquivo nao tenha sido aberto corretamente
    	printf("Erro na abertura do arquivo de entrada\n");
	}
	else
	{
        fprintf(fp,"Escreve que somos ULALA");
	}
	fclose(fp);*/

	printf("\nFuncao UPDATE ainda nao criada");
}


void DeletaArquivo(char nome[]){
return;
}

void menu_CRUD(char nome[])
{
	limpa();
	int opc=-1;
	char *tipo;
	if(strcmp(nome,"autor.txt")==0)
        tipo="Autor";
	if(strcmp(nome,"livro.txt")==0)
        tipo="Livro";
	if(strcmp(nome,"leitor.txt")==0)
        tipo="Leitor";
	if(strcmp(nome,"autordolivro.txt")==0)
        tipo="Autor Do Livro";
	while((opc<=0) || (opc>4))
	{
        printf("\n---------------------------------CRUD---------------------------\n");
        printf("\nDigite 1 - Para CRIAR o Arquivo da Entidade %s",tipo);
        printf("\nDigite 2 - Para LER o arquivo da Entidade %s",tipo);
        printf("\nDigite 3 - Para dar UPDATE no arquivo  da Entidade %s",tipo);
        printf("\nDigite 4 - Para DELETAR o arquivo, da Entidade %s,  (você perderá todos os dados)",tipo);
        printf("\nDigite 0 - para SAIR\n");
        scanf("%i",&opc);
        limpa();
        if(opc==1)
            CriaArquivo(nome,tipo);
        else if(opc==2)
            LendoArquivo(nome,tipo);
        else if(opc==3)
            UpdateArquivo(nome);
        else if(opc==4)
            DeletaArquivo(nome);
        else if(opc==0)
            return;
        else
            printf("\nOpção Inválida, Digite algo para continuar\n");
	}
}

int menu_entidade()
{
    //limpa();
	int opc=-1;


	while((opc<0) || (opc>4))
	{
        printf("\n---------------------------------ENTIDADES--------------------------------\n");
        printf("\nDigite 1 - Para Mexer com a Entidade AUTOR");
        printf("\nDigite 2 - Para Mexer com a Entidade LEITOR");
        printf("\nDigite 3 - Para Mexer com a Entidade LIVRO");
        printf("\nDigite 4 - Para Mexer com a Entidade AUTOR DO LIVRO");
        printf("\nDigite 0 - para SAIR\n");
        scanf("%i",&opc);
        if(opc==1)
            menu_CRUD("autor.txt");
        else if(opc==2)
            menu_CRUD("leitor.txt");
        else if(opc==3)
            menu_CRUD("livro.txt");
        else if(opc==4)
            menu_CRUD("autordolivro.txt");
        else if(opc==0)
            return 0;
        else
            printf("\nOpção Inválida, Digite algo para continuar\n");
	}
    return opc;
}

int main()
{
    //printf("\033[32;1m");
    CriaTodosArquivos();
    while(1){
        //char *c;
        int escolha;
       // int crud=10;
        //c="\0";
        escolha = menu_entidade();  //escolha, SE FOR 1 = AUTOR; SE FOR 2 = LEITOR; SE FOR 3 = LIVRO; SE FOR 4 = AUTOR DO LIVRO;
       /* if(escolha==1)
            c="autor.txt";
        if(escolha==2)
            c="leitor.txt";
        if(escolha==3)
            c="livro.txt";
        if(escolha==4)
            c="autordolivro.txt"; */
        if(escolha==0)
            break;

        //POR ENQUANTO TEMOS APENAS A FUNCAO DE LEITURA
    }
    //CriaArquivo("novoarquivo.txt");
    //printf("\033[m");
    return 0;
}
