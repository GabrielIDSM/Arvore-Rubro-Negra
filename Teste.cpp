#include <cstdio>
#include "ArvoreRubroNegra.hpp"

int main() {
	ArvoreRubroNegra arv1, arv2;
	for (int i = 0; i < 30; i += 5) {
		arv1.inserir(i);
		arv2.inserir(i);
	}
	arv1.emOrdem();
	printf("\n");
	arv1.preOrdem();
	printf("\n");
	arv2.emOrdem();
	printf("\n");
	arv2.preOrdem();
	printf("\n");
	for (int i = 0; i < 10; i += 5) {
		arv1.deletar(i);
		arv2.deletar(i);
	}
	arv1.emOrdem();
	printf("\n");
	arv1.preOrdem();
	printf("\n");
	arv2.emOrdem();
	printf("\n");
	arv2.preOrdem();
	printf("\n");
	return 0;
}