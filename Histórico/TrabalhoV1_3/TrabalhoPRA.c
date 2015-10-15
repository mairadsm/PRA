#include "bibliotecapra.h"

int main()
{
    printf("\033[32;1m");
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
    printf("\033[m");
    return 0;
}


