#include <cstdio>
#include "ArvoreRubroNegra.hpp"

No::No(int dado) {
	this->dado = dado;
	cor = VERMELHO;
	esq = dir = pai = nullptr;
}

ArvoreRubroNegra::ArvoreRubroNegra() {
	raiz = nullptr;
}

int ArvoreRubroNegra::obterCor(No*& no) {
	if (no == nullptr)
		return PRETO;

	return no->cor;
}

void ArvoreRubroNegra::modificarCor(No*& no, int cor) {
	if (no == nullptr)
		return;

	no->cor = cor;
}

void ArvoreRubroNegra::girarEsq(No*& ptr) {
    No* filhoDireito = ptr->dir;
    ptr->dir = filhoDireito->esq;

    if (ptr->dir != nullptr)
        ptr->dir->pai = ptr;

    filhoDireito->pai = ptr->pai;

    if (ptr->pai == nullptr)
        raiz = filhoDireito;
    else if (ptr == ptr->pai->esq)
        ptr->pai->esq = filhoDireito;
    else
        ptr->pai->dir = filhoDireito;

    filhoDireito->esq = ptr;
    ptr->pai = filhoDireito;
}

void ArvoreRubroNegra::girarDir(No*& ptr) {
    No* filhoEsquerdo = ptr->esq;
    ptr->esq = filhoEsquerdo->dir;

    if (ptr->esq != nullptr)
        ptr->esq->pai = ptr;

    filhoEsquerdo->pai = ptr->pai;

    if (ptr->pai == nullptr)
        raiz = filhoEsquerdo;
    else if (ptr == ptr->pai->esq)
        ptr->pai->esq = filhoEsquerdo;
    else
        ptr->pai->dir = filhoEsquerdo;

    filhoEsquerdo->dir = ptr;
    ptr->pai = filhoEsquerdo;
}


void ArvoreRubroNegra::inserir(int n) {
    No* no = new No(n);
    raiz = inserirArvore(raiz, no);
    corrigirInserir(no);
}

void ArvoreRubroNegra::deletar(int dado) {
    No* no = deletarArvore(raiz, dado);
    corrigirDeletar(no);
}

int ArvoreRubroNegra::obterAlturaNegra(No* no) {
    int altura = 0;
    while (no != nullptr) {
        if (obterCor(no) == PRETO)
            altura++;
        no = no->esq;
    }
    return altura;
}

No* ArvoreRubroNegra::menorValor(No*& no) {

	No* ptr = no;

	while (ptr->esq != nullptr)
		ptr = ptr->esq;

	return ptr;
}

No* ArvoreRubroNegra::maiorValor(No*& no) {
    No* ptr = no;

    while (ptr->dir != nullptr)
        ptr = ptr->dir;

    return ptr;
}

No* ArvoreRubroNegra::inserirArvore(No*& raiz, No*& ptr) {
	if (raiz == nullptr)
		return ptr;

	if (ptr->dado < raiz->dado) {
		raiz->esq = inserirArvore(raiz->esq, ptr);
		raiz->esq->pai = raiz;
	}
	else if (ptr->dado > raiz->dado) {
		raiz->dir = inserirArvore(raiz->dir, ptr);
		raiz->dir->pai = raiz;
	}

	return raiz;
}

void ArvoreRubroNegra::corrigirInserir(No*& ptr) {
    No* pai = nullptr;
    No* avo = nullptr;
    while (ptr != raiz && obterCor(ptr) == VERMELHO && obterCor(ptr->pai) == VERMELHO) {
        pai = ptr->pai;
        avo = pai->pai;
        if (pai == avo->esq) {
            No* tio = avo->dir;
            if (obterCor(tio) == VERMELHO) {
                modificarCor(tio, PRETO);
                modificarCor(pai, PRETO);
                modificarCor(avo, VERMELHO);
                ptr = avo;
            }
            else {
                if (ptr == pai->dir) {
                    girarEsq(pai);
                    ptr = pai;
                    pai = ptr->pai;
                }
                girarDir(avo);
                No* aux = pai;
                aux->cor = pai->cor;
                avo->cor = pai->cor;
                pai->cor = aux->cor;
                ptr = pai;
            }
        }
        else {
            No* tio = avo->esq;
            if (obterCor(tio) == VERMELHO) {
                modificarCor(tio, PRETO);
                modificarCor(pai, PRETO);
                modificarCor(avo, VERMELHO);
                ptr = avo;
            }
            else {
                if (ptr == pai->esq) {
                    girarDir(pai);
                    ptr = pai;
                    pai = ptr->pai;
                }
                girarEsq(avo);
                No* aux = pai;
                aux->cor = pai->cor;
                avo->cor = pai->cor;
                pai->cor = aux->cor;
                ptr = pai;
            }
        }
    }
    modificarCor(raiz, PRETO);
}

No* ArvoreRubroNegra::deletarArvore(No*& raiz, int dado) {
    if (raiz == nullptr)
        return raiz;

    if (dado < raiz->dado)
        return deletarArvore(raiz->esq, dado);

    if (dado > raiz->dado)
        return deletarArvore(raiz->dir, dado);

    if (raiz->esq == nullptr || raiz->dir == nullptr)
        return raiz;

    No* temp = menorValor(raiz->dir);
    raiz->dado = temp->dado;
    return deletarArvore(raiz->dir, temp->dado);
}

void ArvoreRubroNegra::corrigirDeletar(No*& no) {
    if (no == nullptr)
        return;

    if (no == raiz) {
        raiz = nullptr;
        return;
    }

    if (obterCor(no) == VERMELHO || obterCor(no->esq) == VERMELHO || obterCor(no->dir) == VERMELHO) {
        No* filho = no->esq != nullptr ? no->esq : no->dir;

        if (no == no->pai->esq) {
            no->pai->esq = filho;
            if (filho != nullptr)
                filho->pai = no->pai;
            modificarCor(filho, PRETO);
            delete (no);
        }
        else {
            no->pai->dir = filho;
            if (filho != nullptr)
                filho->pai = no->pai;
            modificarCor(filho, PRETO);
            delete (no);
        }
    }
    else {
        No* irmao = nullptr;
        No* pai = nullptr;
        No* ptr = no;
        modificarCor(ptr, PRETO_DUPLO);
        while (ptr != raiz && obterCor(ptr) == PRETO_DUPLO) {
            pai = ptr->pai;
            if (ptr == pai->esq) {
                irmao = pai->dir;
                if (obterCor(irmao) == VERMELHO) {
                    modificarCor(irmao, PRETO);
                    modificarCor(pai, VERMELHO);
                    girarEsq(pai);
                }
                else {
                    if (obterCor(irmao->esq) == PRETO && obterCor(irmao->dir) == PRETO) {
                        modificarCor(irmao, VERMELHO);
                        if (obterCor(pai) == VERMELHO)
                            modificarCor(pai, PRETO);
                        else
                            modificarCor(pai, PRETO_DUPLO);
                        ptr = pai;
                    }
                    else {
                        if (obterCor(irmao->dir) == PRETO) {
                            modificarCor(irmao->esq, PRETO);
                            modificarCor(irmao, VERMELHO);
                            girarDir(irmao);
                            irmao = pai->dir;
                        }
                        modificarCor(irmao, pai->cor);
                        modificarCor(pai, PRETO);
                        modificarCor(irmao->dir, PRETO);
                        girarEsq(pai);
                        break;
                    }
                }
            }
            else {
                irmao = pai->esq;
                if (obterCor(irmao) == VERMELHO) {
                    modificarCor(irmao, PRETO);
                    modificarCor(pai, VERMELHO);
                    girarDir(pai);
                }
                else {
                    if (obterCor(irmao->esq) == PRETO && obterCor(irmao->dir) == PRETO) {
                        modificarCor(irmao, VERMELHO);
                        if (obterCor(pai) == VERMELHO)
                            modificarCor(pai, PRETO);
                        else
                            modificarCor(pai, PRETO_DUPLO);
                        ptr = pai;
                    }
                    else {
                        if (obterCor(irmao->esq) == PRETO) {
                            modificarCor(irmao->dir, PRETO);
                            modificarCor(irmao, VERMELHO);
                            girarEsq(irmao);
                            irmao = pai->esq;
                        }
                        modificarCor(irmao, pai->cor);
                        modificarCor(pai, PRETO);
                        modificarCor(irmao->esq, PRETO);
                        girarDir(pai);
                        break;
                    }
                }
            }
        }
        if (no == no->pai->esq)
            no->pai->esq = nullptr;
        else
            no->pai->dir = nullptr;
        delete(no);
        modificarCor(raiz, PRETO);
    }
}

void ArvoreRubroNegra::emOrdemArvore(No*& ptr) {
    if (ptr == nullptr)
        return;

    emOrdemArvore(ptr->esq);
    printf("[%d] ", ptr->dado);
    emOrdemArvore(ptr->dir);
}

void ArvoreRubroNegra::emOrdem() {
    emOrdemArvore(raiz);
}

void ArvoreRubroNegra::preOrdemArvore(No*& ptr) {
    if (ptr == nullptr)
        return;

    printf("[%d] ", ptr->dado);
    emOrdemArvore(ptr->esq);
    emOrdemArvore(ptr->dir);
}

void ArvoreRubroNegra::preOrdem() {
    preOrdemArvore(raiz);
}