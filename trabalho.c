#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Registro{
  char nome[50];
  char marca[50];
  char ean13[13];
  float valor;
}registro;

void writeFile(){

  int flag = 1;
  char simounao;
  FILE *fp;
  registro r;

  while (flag == 1) {

    printf("Inserindo novo registro!\n\nQual o nome?\n");
    scanf("%s", r.nome);
    printf("Qual a marca?\n");
    scanf("%s", r.marca);
    printf("Qual o ean13?\n");
    scanf("%s", r.ean13);
    printf("Qual o valor?\n");
    scanf("%f", &r.valor);

    if((fp = fopen("arquivo.bin", "a+")) == NULL) {
      printf("Erro na abertura do arquivo\n");
      exit(1);
    }

    if(fwrite(r.nome, sizeof(char), 50,fp) !=  50)
      printf("Erro na escrita do arquivo\n");
    if(fwrite(r.marca, sizeof(char), 50,fp) !=  50)
      printf("Erro na escrita do arquivo\n");
    if(fwrite(r.ean13, sizeof(char), 13,fp) !=  13)
      printf("Erro na escrita do arquivo\n");
    if(fwrite(&r.valor, sizeof(float), 1,fp) !=  1)
      printf("Erro na escrita do arquivo\n");
    fclose(fp);

    printf("Inserir outro registro? (S/N)\n");
    scanf(" %c", &simounao);

    if ((simounao == 'N') || (simounao == 'n')) {
      flag = 0;
    }

  }

}

void readFile(){

  int i = 0;
  FILE *fp;
  registro arq;

  if((fp = fopen("arquivo.bin", "r")) == NULL)  {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  while( !feof(fp) ){

    printf("\nRNN: %i", i++);

    if(fread(&arq.nome, sizeof(char), 50,fp) != 50)
      printf("Erro na leitura do arquivo");
    printf("\nO nome: %s", arq.nome);

    if(fread(&arq.marca, sizeof(char), 50,fp) != 50)
      printf("Erro na leitura do arquivo");
    printf("\nO marca: %s", arq.marca);

    if(fread(&arq.ean13, sizeof(char), 13,fp) != 13)
      printf("Erro na leitura do arquivo");
    printf("\nO ean13: %s", arq.ean13);

    if(fread(&arq.valor, sizeof(float), 1,fp) != 1)
      printf("Erro na leitura do arquivo");
    printf("\nO valor: %f\n\n", arq.valor);

    fseek(fp, 117, SEEK_CUR);

  }

  fclose(fp);

}

int main(int argc, char const *argv[]) {
  
  int opc;
  //117 bytes tamanho registro

  do{

    printf("PROGRAMA DE MANIPULAÇÃO DE ARQUIVO\n\n");
    printf("Escolha a ação:\n 0 - Sair\n 1 - Inserir\n 2 - Ler Todos\n 3 - Ler por RNN\n");
    scanf("%i", &opc);
    
    switch( opc ){
      
      case 1:
        writeFile();
      break;

      case 2:
        readFile();
      break;

    }

  }while( opc != 0 );

  return 0;
}
