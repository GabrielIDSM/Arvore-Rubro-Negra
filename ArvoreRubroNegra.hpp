enum Cor { VERMELHO, PRETO, PRETO_DUPLO };

struct No
{
    int dado;
    int cor;
    No* esq, * dir, * pai;

    explicit No(int);
};

class ArvoreRubroNegra
{
private:
    No* raiz;
protected:
    void girarEsq(No*&);
    void girarDir(No*&);
    void corrigirInserir(No*&);
    void corrigirDeletar(No*&);
    int obterCor(No*&);
    void modificarCor(No*&, int);
    No* maiorValor(No*&);
    No* menorValor(No*&);
    No* inserirArvore(No*&, No*&);
    No* deletarArvore(No*&, int);
    int obterAlturaNegra(No*);
    void emOrdemArvore(No*&);
    void preOrdemArvore(No*&);
public:
    ArvoreRubroNegra();
    void inserir(int);
    void deletar(int);
    void emOrdem();
    void preOrdem();
};