# include "estruturasdedados_descritores.h"

# ifndef ESTRUTURASDEDADOS_ASSINATURAS_H_INCLUDED
# define ESTRUTURASDEDADOS_ASSINATURAS_H_INCLUDED

    /// ****************************************************************************************************

    /// PILHA DIN�MICA SIMPLESMENTE ENCADEADA

        // DEFINI��O DE TIPO
        typedef struct descritorPDSE PDSE;

        // FUN��ES
        int criarPDSE (PDSE **pp, unsigned int sizeInfo);
        int inserirElemPDSE (PDSE *p, void *novo);
        int removerElemPDSE (PDSE *p);
        int buscarElemPDSE (PDSE *p, void *reg);
        int reiniciarPDSE (PDSE *p);
        int destruirPDSE (PDSE **p);
        int testeVaziaPDSE (PDSE *p);
        int tamanhoPDSE (PDSE *p);

    /// ****************************************************************************************************

    /// FILA DIN�MICA DUPLAMENTE ENCADEADA

        // DEFINI��O DE TIPO
        typedef struct descritorFDDE FDDE;

        // FUN��ES
        int criarFDDE (FDDE **pp, unsigned int sizeInfo);
        int inserirElemFDDE (FDDE *p, void *novo);
        int removerElemFDDE (FDDE *p);
        int buscarComecoFDDE (FDDE *p, void *reg);
        int buscarFimFDDE (FDDE *p, void *reg);
        int reiniciarFDDE (FDDE *p);
        int destruirFDDE (FDDE **p);
        int testeVaziaFDDE (FDDE *p);
        int tamanhoFDDE (FDDE *p);

    /// ****************************************************************************************************

    /// LISTA DIN�MICA DUPLAMENTE ENCADEADA

        // DEFINI��ES DE TIPO
        typedef struct descritorLDDE LDDE;

        // FUN��ES
        int criarLDDE (LDDE **pp, unsigned int sizeInfo);
        int inserirComecoLDDE (LDDE *p, void *novo);
        int inserirPosLogLDDE (LDDE *p, void *novo, unsigned int posLog);
        int inserirFimLDDE (LDDE *p, void *novo);
        int removerComecoLDDE (LDDE *p);
        int removerPosLogLDDE (LDDE *p, unsigned int posLog);
        int removerFimLDDE (LDDE *p);
        int buscarComecoLDDE (LDDE *p, void *reg);
        int buscarPosLogLDDE (LDDE *p, void *reg, unsigned int posLog);
        int buscarFimLDDE (LDDE *p, void *reg);
        int reiniciarLDDE (LDDE *p);
        int destruirLDDE (LDDE **p);
        int testeVaziaLDDE (LDDE *p);
        int tamanhoLDDE (LDDE *p);

# endif // ESTRUTURASDEDADOS_ASSINATURAS_H_INCLUDED
