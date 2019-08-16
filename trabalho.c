#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Registro{
  char nome[50];
  char marca[50];
  char ean13[13];
  float valor;
}registro;

int countReg(){

  FILE *fp;
  int count;

  if ((fp = fopen("arquivo.bin", "r")) == NULL)
  {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  fseek(fp, 0L, SEEK_END);
  count = ftell(fp) / sizeof(registro);

  return count;

}

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

  int i = 0, count;;
  FILE *fp;
  registro arq;

  count = countReg();

  if( count == 0 ){
    printf("Arquivo vazio");
    return 0;
  }

  if((fp = fopen("arquivo.bin", "r")) == NULL)  {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  for( i = 0; i < count; i++ ){

    fseek(fp, i * sizeof(registro), SEEK_SET);
    fread(&arq, sizeof(registro), 1,fp);

    printf("\nRNN: %i", i);
    printf("\nO nome: %s", arq.nome);
    printf("\nO marca: %s", arq.marca);
    printf("\nO ean13: %s", arq.ean13);
    printf("\nO valor: %f\n\n", arq.valor);

  }

  fclose(fp);
  return 1;

}

void readFileRNN(int rnn){

  FILE *fp;
  int count;
  registro arq;


  count = countReg();

  if((fp = fopen("arquivo.bin", "r")) == NULL)  {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  if(count >= rnn+1) {

    fseek(fp, rnn*sizeof(registro), SEEK_SET);
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

void delByRNN(int rnn)
{

  FILE *fp;
  int count;
  registro arq;

  count = countReg();
  printf("\n count: %i\n", count);

  if ((fp = fopen("arquivo.bin", "r+")) == NULL)
  {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  if (count >= rnn + 1)
  {

    fseek(fp, rnn * sizeof(registro), SEEK_SET);
    fread(&arq, sizeof(arq), 1, fp);

    arq.nome[0] = '*';

    fseek(fp, rnn * sizeof(registro), SEEK_SET);
    if (fwrite(&arq, sizeof(registro), 1, fp) != 1)
    {
      printf("Erro na escrita do arquivo\n");
    }

  }
  else
  {
    printf("O RNN não existe\n\n");
  }

  fclose(fp);
}

int main(int argc, char const *argv[]) {
  
  int opc,rnn;
  //117 bytes tamanho registro

  do{
    printf("PROGRAMA DE MANIPULAÇÃO DE ARQUIVO\n\n");
    printf("Escolha a ação:\n 0 - Sair\n 1 - Inserir\n 2 - Ler Todos\n 3 - Ler por RNN\n 4 - Excluir por RNN\n");
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

      case 4:
        printf("Qual o RNN: ");
        scanf("%i", &rnn);
        delByRNN(rnn);
        break;

      default:
        printf( "Opcao nao existente." );
      break;

    }

  }while( opc != 0 );

  return 0;
}