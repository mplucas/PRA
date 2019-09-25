# ifndef ESTRUTURASDEDADOS_DESCRITORES_H_INCLUDED
# define ESTRUTURASDEDADOS_DESCRITORES_H_INCLUDED

    /// ****************************************************************************************************

    // DEFINES

    # define FRACASSO 0
    # define SUCESSO 1

    /// ****************************************************************************************************

    /// ESTRUTURAS B�SICAS PARA PILHA DIN�MICA SIMPLESMENTE ENCADEADA

    // N� da pilha
    struct NoPDSE {
        void *dados;
        struct NoPDSE *abaixo;
    };
    typedef struct NoPDSE noPDSE;

    // Descritor da pilha
    struct descritorPDSE {
        struct NoPDSE *topo;
        unsigned int tamInfo;
    };
    typedef struct descritorPDSE PDSE;

    /// ****************************************************************************************************

    /// ESTRUTURAS B�SICAS PARA FILA DIN�MICA DUPLAMENTE ENCADEADA

    // N� da fila
    struct NoFDDE {
        void *dados;
        struct NoFDDE *frente;
        struct NoFDDE *tras;
    };
    typedef struct NoFDDE noFDDE;

    // Descritor da fila
    struct descritorFDDE {
        struct NoFDDE *primeiro;
        struct NoFDDE *ultimo;
        unsigned int tamInfo;
    };
    typedef struct descritorFDDE FDDE;

    /// ****************************************************************************************************

    /// ESTRUTURAS B�SICAS PARA LISTA DIN�MICA DUPLAMENTE ENCADEADA

    // N� da fila
    struct NoLDDE {
        void *dados;
        struct NoLDDE *frente;
        struct NoLDDE *tras;
    };
    typedef struct NoLDDE noLDDE;

    // Descritor da fila
    struct descritorLDDE {
        struct NoLDDE *primeiro;
        struct NoLDDE *ultimo;
        unsigned int tamInfo;
    };
    typedef struct descritorLDDE LDDE;

# endif // ESTRUTURASDEDADOS_DESCRITORES_H_INCLUDED

