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

    if (fwrite(&r,sizeof(registro),1,fp) != 1) {
      printf("Erro na escrita do arquivo\n");
    }
    fclose(fp);

    printf("Inserir outro registro? (S/N)\n");
    scanf(" %c", &simounao);

    if ((simounao == 'N') || (simounao == 'n')) {
      flag = 0;
    }

  }

}

int readFile(){

  int i = 0;
  FILE *fp;
  registro arq;
  char tempEan[13];

  if((fp = fopen("arquivo.bin", "r")) == NULL)  {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  while( !feof(fp) ){
    fseek(fp, i*sizeof(arq), SEEK_SET);
    fread(&arq, sizeof(arq), 1,fp);

    if (i != 0 && strcmp(tempEan,arq.ean13) == 0) {
      return 1;
    }

    printf("\nRNN: %i", i);
    printf("\nO nome: %s", arq.nome);
    printf("\nO marca: %s", arq.marca);
    printf("\nO ean13: %s", arq.ean13);
    printf("\nO valor: %f\n\n", arq.valor);
    i++;
    strncpy(tempEan,arq.ean13 ,sizeof(tempEan));
  }

  fclose(fp);
  return 1;

}

void readFileRNN(int rnn){

  FILE *fp;
  int count;
  registro arq;

  if((fp = fopen("arquivo.bin", "r")) == NULL)  {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  fseek(fp, 0L, SEEK_END);
  count = ftell(fp)/120;

  if(count >= rnn+1) {

    fseek(fp, rnn*sizeof(arq), SEEK_SET);
    fread(&arq, sizeof(arq), 1,fp);

    printf("\nRNN: %i", rnn);
    printf("\nO nome: %s", arq.nome);
    printf("\nO marca: %s", arq.marca);
    printf("\nO ean13: %s", arq.ean13);
    printf("\nO valor: %f\n\n", arq.valor);
  } else {
    printf("O RNN não existe\n\n");
  }

  fclose(fp);

}

int main(int argc, char const *argv[]) {
  
  int opc,rnn;
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

      case 3:
        printf("Qual o RNN: ");
        scanf("%i",&rnn);
        readFileRNN(rnn);
      break;

    }

  }while( opc != 0 );

  return 0;
}