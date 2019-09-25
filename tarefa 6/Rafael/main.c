/* 21/09/2019. 1) Considere um conjunto de 100 chaves, x, formado pelos 100 primeiros m�ltiplos do n�mero 7 (o 7 � o primeiro
 * elemento do conjunto x). Sendo h(x) = x % m a fun��o de hashing utilizada, onde, m � o tamanho da tabela hash (n�mero de slots).
 * Quantas colis�es, por slot, seriam obtidas com cada valor de m abaixo? (Informe tamb�m em forma de tabela, a destina��o de
 * cada valor do conjunto x) a) m = 7 b) m = 14 c) m = 5.

 * 2) Dada uma tabela hash de tamanho m = 9, fun��o hash h(k) = k % m, com encadeamento separado, mostre a tabela ap�s a inser��o
 * das chaves 4, 23, 29, 15, 21, 43, 11, 5 e 10. Mostre tamb�m como ficaria a tabela ap�s as inser��es se seu tamanho fosse m = 11.

 * 3) Dada uma tabela hash de tamanho m = 11 fun��o hash h(k) = (2k + 5)%m, com encadeamento separado, mostre a tabela ap�s a
 * inser��o das chaves 12, 44, 13, 88, 23, 94, 11, 39, 20, 16 e 5.
 */

    # include <stdio.h>
    # include <stdlib.h>
    # include "estruturasdedados_assinaturas.h"
    # include "estruturasdedados_descritores.h"

    // Assinatura de fun��es
    void cabecalho (char* titulo);
    void exercicio01();
    void exercicio02();
    void exercicio03();

    int main() {

        cabecalho ("ATIVIDADE PRA-AT06");
        printf ("\nAlunos: Lucas Meneghelli Pereira e Rafael de Melo Boeger\n\n");
        exercicio01();
        printf ("\n");
        exercicio02();
        printf("\n");
        exercicio03();

        return (0);
    }

    // ************************************************************************************************************************

    void exercicio01() {

        // Vari�veis
        int x[100];
        int m;
        int i;
        int* slots;
        int item;

        // Cabe�alho
        cabecalho ("Exercicio 01");

        // Enunciado
        printf ("\nConsidere um conjunto de 100 chaves, x, formado pelos 100 primeiros multiplos do numero 7 (o 7 \n"
                "e o primeiro elemento do conjunto x). Sendo h(x) = x %% m a funcao de hashing utilizada, onde, m e o \n"
                "tamanho da tabela hash (numero de slots). Quantas colisoes, por slot, seriam obtidas com cada valor \n"
                "de m abaixo? (Informe tambem em forma de tabela, a destinacao de cada valor do conjunto x) a) m = 7 \n"
                "b) m = 14 c) m = 5.\n" );

        // Preenchendo o vetor x
        for (i=0; i<=99; i++) {
            x[i] = (i + 1) * 7;
        }

        // Definindo os slots dos elementos
        printf ("\nCalculando os slots dos elementos\n\n");

        printf ("Numero\tm = 7\tm = 14\tm = 5\n");
        for (i=0; i<=99; i++) {
            printf ("%d\t", x[i]);
            m = 7;
            printf ("%d\t", x[i] % m);
            m = 14;
            printf ("%d\t", x[i] % m);
            m = 5;
            printf ("%d\n", x[i] % m);
        }

        // Contando a quantidade de colis�es
        printf ("\nExibindo a quantidade de colisoes por slot\n");
        for (item=1; item<=3; item++) {

            // Definindo o tamanho da tabela hash
            switch (item) {
                case 1:
                    m = 7;
                    break;
                case 2:
                    m = 14;
                    break;
                case 3:
                    m = 5;
                    break;
            }

            // Cabe�alho
            printf ("\nSe m = %d:\n\n", m);

            // Inserindo os elementos nos slots
            slots = (int*) calloc (m, sizeof(int));
            for (i=0; i<=99; i++) {
                slots[x[i] % m]++ ;
            }

            // Exibindo o n�mero de elementos em cada slot
            for (i=0; i<=m-1; i++) {
                printf ("Slot %d: %d\n", i, slots[i]);
            }

            // Finalmentes
            free (slots);
        }
    }

    // ************************************************************************************************************************

    void exercicio02() {

        // Vari�veis
        LDDE** slots;
        int m;
        int i, j;
        int k[9];
        int item;
        int aux;

        // Instru��es

        // Cabecalho
        cabecalho ("Exercicio 02");

        // Enunciado
        printf ("\nDada uma tabela hash de tamanho m = 9, funcao hash h(k) = k %% m, com encadeamento separado, mostre a\n"
                "tabela apos a insercao das chaves 4, 23, 29, 15, 21, 43, 11, 5 e 10. Mostre tambem como ficaria a \n"
                "tabela apos as insercoes se seu tamanho fosse m = 11.\n");


        // Preenchendo o vetor das chaves
        k[0] = 4;
        k[1] = 23;
        k[2] = 29;
        k[3] = 15;
        k[4] = 21;
        k[5] = 43;
        k[6] = 11;
        k[7] = 5;
        k[8] = 10;

        // Realizando os itens
        for (item=1; item<=2; item++) {

            // Selecionando o tamanho da tabela hash
            switch (item) {
                case 1:
                    m = 9;
                    break;
                case 2:
                    m = 11;
                    break;
            }
            printf ("\nSe m = %d:\n\n", m);

            // Criando os slots
            slots = (LDDE**) calloc (m, sizeof(LDDE*));
            for (i=0; i<=m-1; i++) {
                criarLDDE (&slots[i], sizeof(int));
            }

            // Inserindo os elementos nos slots
            for (i=0; i<=8; i++) {
                inserirFimLDDE(slots[k[i] % m], &k[i]);
            }

            // Exibindo a tabela hash
            for (i=0; i<=m-1; i++) {
                printf ("Slot %02d: ", i);
                for (j=0; j<=tamanhoLDDE(slots[i])-1; j++) {
                    buscarPosLogLDDE (slots[i], &aux, j);
                    if (j != 0) {
                        printf (",");
                    }
                    printf (" %d", aux);
                }
                printf ("\n");
            }

            // Desalocando a tabela hash
            for (i=0; i<=m-1; i++) {
                destruirLDDE (&slots[i]);
            }
            free (slots);
        }
    }

    // ************************************************************************************************************************

    void exercicio03() {

        // Vari�veis
        LDDE** slots;
        int m = 11;
        int i, j;
        int k[11];
        int aux;

        // Instru��es

        // Cabecalho
        cabecalho ("Exercicio 03");

        // Enunciado
        printf ("\nDada uma tabela hash de tamanho m = 11, funcao hash h(k) = (2k + 5) %% m, com encadeamento separado, \n"
                "mostre a tabela apos a insercao das chaves 12, 44, 13, 88, 23, 94, 11, 39, 20, 16 e 5.\n");

        // Preenchendo o vetor das chaves
        k[0] = 12;
        k[1] = 44;
        k[2] = 13;
        k[3] = 88;
        k[4] = 23;
        k[5] = 94;
        k[6] = 11;
        k[7] = 39;
        k[8] = 20;
        k[9] = 16;
        k[10] = 5;

        printf ("\nUsando m = %d:\n\n", m);

        // Criando os slots
        slots = (LDDE**) calloc (m, sizeof(LDDE*));
        for (i=0; i<=m-1; i++) {
            criarLDDE (&slots[i], sizeof(int));
        }

        // Inserindo os elementos nos slots
        for (i=0; i<=8; i++) {
            inserirFimLDDE(slots[(2*k[i]+5) % m], &k[i]);
        }

        // Exibindo a tabela hash
        for (i=0; i<=m-1; i++) {
            printf ("Slot %02d: ", i);
            for (j=0; j<=tamanhoLDDE(slots[i])-1; j++) {
                buscarPosLogLDDE (slots[i], &aux, j);
                if (j != 0) {
                    printf (",");
                }
                printf (" %d", aux);
            }
            printf ("\n");
        }

        // Desalocando a tabela hash
        for (i=0; i<=m-1; i++) {
            destruirLDDE (&slots[i]);
        }
        free (slots);
    }

    // ************************************************************************************************************************

    void cabecalho (char* titulo) {
        int i;
        for (i=0; i<=99; i++) {
            printf ("-");
        }
        printf ("\n%s\n", titulo);
        for (i=0; i<=99; i++) {
            printf ("-");
        }
        printf ("\n");
    }
