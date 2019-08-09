#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Registro{
  char nome[50];
  char marca[50];
  char ean13[13];
  float valor;
}registro;

int main(int argc, char const *argv[]) {
  int flag = 1;
  FILE *fp;
  char simounao;
  registro r;
  registro arq;
  //121 bytes tamanho registro

  while (flag == 1) {
    printf("Qual o nome?\n");
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

    if((fp = fopen("arquivo.bin", "r")) == NULL)  {
      printf("Erro na abertura do arquivo");
      exit(1);
    }

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
    printf("\nO valor: %f", arq.valor);
    fclose(fp);

    printf("Inserir outro registro? (S/N)\n");
    scanf(" %c", &simounao);
    if ((simounao == 'N') || (simounao == 'n')) {
      flag = 0;
    }
  }

  return 0;
}
