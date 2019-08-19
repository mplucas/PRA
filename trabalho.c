#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Registro{
  char nome[50];
  char marca[50];
  char ean13[13];
  float valor;
}registro;

void createTopo(){

    FILE *fp;
    int topo = -1;

    if ((fp = fopen("topo.bin", "w")) == NULL)
    {
      printf("Erro na abertura do arquivo");
      exit(1);
    }

    if (fwrite(&topo,sizeof(int),1,fp) != 1) {
      printf("Erro na escrita do arquivo\n");
    }

}

int getTopo(){

    FILE *fp;
    int topo;

    if ((fp = fopen("topo.bin", "r")) == NULL)
    {
      printf("Erro na abertura do arquivo");
      exit(1);
    }

    fread(&topo, sizeof(int), 1,fp);

    return topo;

}

void setTopo( int topo ){

    FILE *fp;

    if ((fp = fopen("topo.bin", "w")) == NULL)
    {
      printf("Erro na abertura do arquivo");
      exit(1);
    }

    if (fwrite(&topo,sizeof(int),1,fp) != 1) {
      printf("Erro na escrita do arquivo\n");
    }

}

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

  int i = 0, count, rrn = 0;
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

    if( arq.nome[0] != '*' ){

        printf("\nRRN: %i", rrn);
        printf("\nO nome: %s", arq.nome);
        printf("\nO marca: %s", arq.marca);
        printf("\nO ean13: %s", arq.ean13);
        printf("\nO valor: %f\n\n", arq.valor);
        rrn++;

    }

  }

  fclose(fp);
  return 1;

}

int searchRRN(int rrn_search){

  FILE *fp;
  int count, i, rrn = 0;
  registro arq;
  int achou = 0;

  count = countReg();

  if((fp = fopen("arquivo.bin", "r")) == NULL)  {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  for( i = 0; i < count; i++ ){

    fseek(fp, i * sizeof(registro), SEEK_SET);
    fread(&arq, sizeof(registro), 1,fp);

    if( arq.nome[0] != '*' ){

        if( rrn_search == rrn ){
            achou = 1;
            break;
        }
        rrn++;
    }

  }

  if( !achou ) {
    i = -1;
  }

  fclose(fp);

  return i;

}

void readFileRRN(int rrn_search){

    FILE *fp;
    int pos = searchRRN( rrn_search );
    registro arq;

    if( pos == -1 ){
        printf("O RRN não existe\n\n");
    }else{

        if((fp = fopen("arquivo.bin", "r")) == NULL)  {
          printf("Erro na abertura do arquivo");
          exit(1);
        }

        fseek(fp, pos * sizeof(registro), SEEK_SET);
        fread(&arq, sizeof(registro), 1,fp);

        printf("\nRRN: %i", rrn_search);
        printf("\nO nome: %s", arq.nome);
        printf("\nO marca: %s", arq.marca);
        printf("\nO ean13: %s", arq.ean13);
        printf("\nO valor: %f\n\n", arq.valor);

        fclose(fp);

    }

}

void delByRRN(int rrn)
{

  FILE *fp;
  int topo, rrnReal = searchRRN( rrn );
  char aux = '*';

  if ((fp = fopen("arquivo.bin", "r+")) == NULL)
  {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  if (rrnReal != -1) {

    fseek(fp, rrnReal * sizeof(registro), SEEK_SET);

    if (fwrite(&aux, sizeof(char), 1, fp) != 1)
    {
      printf("Erro na escrita do arquivo\n");
    }

    topo = getTopo();

    fseek(fp, rrnReal * sizeof(registro) + sizeof(char), SEEK_SET);

    if (fwrite(&topo, sizeof(int), 1, fp) != 1)
    {
      printf("Erro na escrita do arquivo\n");
    }

    setTopo( rrnReal );

  } else {
    printf("O RRN não existe\n\n");
  }

  fclose(fp);
}

int main(int argc, char const *argv[]) {

  int opc,rrn;
  //117 bytes tamanho registro

  createTopo();

  do{
    printf("PROGRAMA DE MANIPULAÇÃO DE ARQUIVO\n\n");
    printf("Escolha a ação:\n 0 - Sair\n 1 - Inserir\n 2 - Ler Todos\n 3 - Ler por RRN\n 4 - Excluir por RRN\n");
    scanf("%i", &opc);

    switch( opc ){

      case 1:
        writeFile();
      break;

      case 2:
        readFile();
      break;

      case 3:
        printf("Qual o RRN: ");
        scanf("%i",&rrn);
        readFileRRN(rrn);
      break;

      case 4:
        printf("Qual o RRN: ");
        scanf("%i", &rrn);
        delByRRN(rrn);
        break;

      default:
        printf( "Opcao nao existente." );
      break;

    }

  }while( opc != 0 );

  return 0;
}
