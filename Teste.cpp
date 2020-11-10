#include <cstdio>
#include "ArvoreRubroNegra.hpp"

int main() {
	ArvoreRubroNegra arvore;
	arvore.inserir(2);
	arvore.inserir(1);
	arvore.inserir(4);
	arvore.inserir(3);
	arvore.inserir(5);
	arvore.inserir(6);
	arvore.preOrdem();
	printf("\n");
	arvore.emOrdem();
	printf("\n\n");
	arvore.inserir(7);
	arvore.preOrdem();
	printf("\n");
	arvore.emOrdem();
	printf("\n");
}

