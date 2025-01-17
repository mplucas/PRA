#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Registro{
  char nome[50];
  char marca[50];
  char ean13[13];
  float valor;
}registro;

// Cria o arquivo que conterá o valor do topo da
// pilha da abordagem dinâmica caso não exista
void createTopo(){

    FILE *fp;
    int topo = -1;

    // se topo.bin não existir, o cria
    if ((fp = fopen("topo.bin", "r")) == NULL){

      if ((fp = fopen("topo.bin", "w")) == NULL)
      {
        printf("Erro na abertura do topo 1");
        exit(1);
      }

      if (fwrite( &topo, sizeof(int), 1, fp ) != 1) {
        printf("Erro na escrita do arquivo\n");
      }

    }

    fclose(fp);

}

// Cria o arquivo que conterá os registros caso não exista
void createArq(){

    FILE *fp;

    // se arquivo.bin não existir, o cria
    if ((fp = fopen("arquivo.bin", "r")) == NULL){

      if ((fp = fopen("arquivo.bin", "w")) == NULL)
      {
        printf("Erro na abertura do arquivo 0");
        exit(1);
      }

    }

    fclose(fp);

}

// Retorna o valor do topo da pilha utilizada na
// abordagem dinâmica
int getTopo(){

    FILE *fp;
    int topo;

    if ((fp = fopen("topo.bin", "r")) == NULL)
    {
      printf("Erro na abertura do topo 2");
      exit(1);
    }

    fread(&topo, sizeof(int), 1,fp);

    fclose(fp);

    return topo;

}

// Atualiza o arquivo que guarda o valor do topo da pilha
// utilizada na abordagem dinâmica
void setTopo( int topo ){

    FILE *fp;

    if ((fp = fopen("topo.bin", "w")) == NULL)
    {
      printf("Erro na abertura do topo 3");
      exit(1);
    }

    if (fwrite(&topo,sizeof(int),1,fp) != 1) {
      printf("Erro na escrita do arquivo\n");
    }

    fclose(fp);

}

// Conta todos os registros do arquivo
int countReg(){

  FILE *fp;
  int count;

  if ((fp = fopen("arquivo.bin", "r")) == NULL)
  {
    printf("Erro na abertura do arquivo 1");
    exit(1);
  }

  fseek(fp, 0L, SEEK_END);
  count = ftell(fp) / sizeof(registro);

  fclose(fp);

  return count;

}

// adiciona novos registros no arquivo utilizando abordagem
// dinâmica
void writeFile(){

  int flag = 1, topo = getTopo(), novoTopo;
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

    if( topo == -1 ){

        if((fp = fopen("arquivo.bin", "a+")) == NULL) {
            printf("Erro na abertura do arquivo 2\n");
            exit(1);
        }

        if (fwrite(&r,sizeof(registro),1,fp) != 1) {
            printf("Erro na escrita do arquivo\n");
        }
        fclose(fp);

        printf("\n1\n");

    }else{

        if((fp = fopen("arquivo.bin", "r+")) == NULL) {
            printf("Erro na abertura do arquivo 3\n");
            exit(1);
        }

        // atualizando topo
        fseek(fp, topo * sizeof(registro) + 1, SEEK_SET);
        fread(&novoTopo, sizeof(int), 1,fp);
        setTopo( novoTopo );

        // atualizando registro
        fseek(fp, topo * sizeof(registro), SEEK_SET);
        if (fwrite(&r,sizeof(registro),1,fp) != 1) {
            printf("Erro na escrita do arquivo\n");
        }else{
          printf("Registro inserido.\n");
        }
        fclose(fp);

    }

    printf("Inserir outro registro? (S/N)\n");
    scanf(" %c", &simounao);

    if ((simounao == 'N') || (simounao == 'n')) {
      flag = 0;
    }

  }

}

// mostra todos os registros não excluidos do arquivo
int readFile(){

  int i = 0, count, rrn = 0;
  FILE *fp;
  registro reg;

  count = countReg();

  if( count == 0 ){
    printf("Arquivo vazio\n");
    return 0;
  }

  if((fp = fopen("arquivo.bin", "r")) == NULL)  {
    printf("Erro na abertura do arquivo 4");
    exit(1);
  }

  for( i = 0; i < count; i++ ){

    fseek(fp, i * sizeof(registro), SEEK_SET);
    fread(&reg, sizeof(registro), 1,fp);

    if( reg.nome[0] != '*' ){

        printf("\nRRN: %i", rrn);
        printf("\nO nome: %s", reg.nome);
        printf("\nA marca: %s", reg.marca);
        printf("\nO ean13: %s", reg.ean13);
        printf("\nO valor: %f\n\n", reg.valor);
        rrn++;

    }

  }

  fclose(fp);
  return 1;

}


// retorna o 'rrn real' do registro, ex: registro 1 foi excluido
// logo o registro 2 tem rrn 1, mas seu rrn real é 2
int searchRRN(int rrn_search){

  FILE *fp;
  int count, i, rrn = 0;
  registro reg;
  int achou = 0;

  count = countReg();

  if((fp = fopen("arquivo.bin", "r")) == NULL)  {
    printf("Erro na abertura do arquivo 5");
    exit(1);
  }

  for( i = 0; i < count; i++ ){

    fseek(fp, i * sizeof(registro), SEEK_SET);
    fread(&reg, sizeof(registro), 1,fp);

    if( reg.nome[0] != '*' ){

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

// mostra o registro segundo o rrn
void readFileRRN(int rrn_search){

    FILE *fp;
    int pos = searchRRN( rrn_search );
    registro reg;

    if( pos == -1 ){
        printf("O RRN não existe\n\n");
    }else{

        if((fp = fopen("arquivo.bin", "r")) == NULL)  {
          printf("Erro na abertura do arquivo 6");
          exit(1);
        }

        fseek(fp, pos * sizeof(registro), SEEK_SET);
        fread(&reg, sizeof(registro), 1,fp);

        printf("\nRRN: %i", rrn_search);
        printf("\nO nome: %s", reg.nome);
        printf("\nO marca: %s", reg.marca);
        printf("\nO ean13: %s", reg.ean13);
        printf("\nO valor: %f\n\n", reg.valor);

        fclose(fp);

    }

}

// exclui logicamente um registro do arquivo
void delByRRN(int rrn)
{

  FILE *fp;
  int topo, rrnReal = searchRRN( rrn );
  char aux = '*';

  if ((fp = fopen("arquivo.bin", "r+")) == NULL){
    printf("Erro na abertura do arquivo 7");
    exit(1);
  }

  if (rrnReal != -1) {

    // marcando registro excluido
    fseek(fp, rrnReal * sizeof(registro), SEEK_SET);
    if (fwrite(&aux, sizeof(char), 1, fp) != 1){
      printf("Erro na escrita do arquivo\n");
    }

    // adicionando topo no registro excluido para criação da pilha
    topo = getTopo();
    fseek(fp, rrnReal * sizeof(registro) + sizeof(char), SEEK_SET);
    if (fwrite(&topo, sizeof(int), 1, fp) != 1){
      printf("Erro na escrita do arquivo\n");
    }else{
      printf("Registro excluido.\n");
    }

    // atualizando topo
    setTopo( rrnReal );

  } else {
    printf("O RRN não existe\n\n");
  }

  fclose(fp);
}

// Cria o arquivo auxiliar para limpar arquivo
void createArqAux(){

    FILE *fp;

    if ((fp = fopen("arquivoAux.bin", "w")) == NULL)
    {
      printf("Erro na abertura do arquivo aux");
      exit(1);
    }

    fclose(fp);

}

// função para fazer a remoção fisica de registros
// do arquivo
void cleanFile(){

  FILE *fp, *fpAux;
  int count, i;
  registro reg;

  createArqAux();

  count = countReg();

  if((fpAux = fopen("arquivoAux.bin", "a+")) == NULL)  {
    printf("Erro na abertura do arquivo auxiliar 2");
    exit(1);
  }

  if((fp = fopen("arquivo.bin", "r")) == NULL)  {
    printf("Erro na abertura do arquivo 5");
    exit(1);
  }

  for( i = 0; i < count; i++ ){

    fseek(fp, i * sizeof(registro), SEEK_SET);
    fread(&reg, sizeof(registro), 1,fp);

    if( reg.nome[0] != '*' ){
      if (fwrite(&reg, sizeof(registro), 1, fpAux) != 1){
        printf("Erro na escrita do arquivo\n");
      }
    }

  }

  fclose(fp);
  fclose(fpAux);

  // exclui o arquivo anterior e renomeia o auxiliar
  if (remove( "arquivo.bin" ) != 0){
    printf("arquivo.bin nao deletado\n");
    perror("Erro");
  }

  if (rename("arquivoAux.bin", "arquivo.bin") != 0){
    printf("Erro na renomeacao do arquivo\n");
  }else{
    printf("Arquivo limpo\n");
  }

  // Atualiza topo para -1
  setTopo(-1);

}

int main(int argc, char const *argv[]) {

  int opc,rrn;
  //117 bytes tamanho registro

  createTopo();
  createArq();

  do{
    printf("PROGRAMA DE MANIPULAÇÃO DE ARQUIVO\n\n");
    printf("Escolha a ação:\n 0 - Sair\n 1 - Inserir\n 2 - Ler Todos\n 3 - Ler por RRN\n 4 - Excluir por RRN\n 5 - Limpar arquivo\n");
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

      case 5:
        cleanFile();
        break;

      default:
        printf( "Opcao nao existente." );
      break;

    }

  }while( opc != 0 );

  return 0;
}
