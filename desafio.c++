#include <iostream>
#include <algorithm>

class No {
public:
    int chave;
    No* esquerda;
    No* direita;
    int altura;

    No(int chave) : chave(chave), esquerda(nullptr), direita(nullptr), altura(1) {}
};

class ArvoreAVL {
private:
    No* raiz;

    int altura(No* no) {
        if (no == nullptr) return 0;
        return no->altura;
    }

    int fatorBalanceamento(No* no) {
        if (no == nullptr) return 0;
        return altura(no->esquerda) - altura(no->direita);
    }

    No* rotacaoDireita(No* y) {
        No* x = y->esquerda;
        No* T2 = x->direita;

        x->direita = y;
        y->esquerda = T2;

        y->altura = std::max(altura(y->esquerda), altura(y->direita)) + 1;
        x->altura = std::max(altura(x->esquerda), altura(x->direita)) + 1;

        return x;
    }

    No* rotacaoEsquerda(No* x) {
        No* y = x->direita;
        No* T2 = y->esquerda;

        y->esquerda = x;
        x->direita = T2;

        x->altura = std::max(altura(x->esquerda), altura(x->direita)) + 1;
        y->altura = std::max(altura(y->esquerda), altura(y->direita)) + 1;

        return y;
    }

    No* inserir(No* no, int chave) {
        if (no == nullptr) return new No(chave);

        if (chave < no->chave)
            no->esquerda = inserir(no->esquerda, chave);
        else if (chave > no->chave)
            no->direita = inserir(no->direita, chave);
        else
            return no; // Chaves iguais não são permitidas na árvore AVL

        no->altura = 1 + std::max(altura(no->esquerda), altura(no->direita));

        int balanceamento = fatorBalanceamento(no);

        // Casos de desbalanceamento

        // Rotação simples à direita
        if (balanceamento > 1 && chave < no->esquerda->chave)
            return rotacaoDireita(no);

        // Rotação simples à esquerda
        if (balanceamento < -1 && chave > no->direita->chave)
            return rotacaoEsquerda(no);

        // Rotação dupla à direita (esquerda-direita)
        if (balanceamento > 1 && chave > no->esquerda->chave) {
            no->esquerda = rotacaoEsquerda(no->esquerda);
            return rotacaoDireita(no);
        }

        // Rotação dupla à esquerda (direita-esquerda)
        if (balanceamento < -1 && chave < no->direita->chave) {
            no->direita = rotacaoDireita(no->direita);
            return rotacaoEsquerda(no);
        }

        return no;
    }

    void emOrdem(No* no) {
        if (no != nullptr) {
            emOrdem(no->esquerda);
            std::cout << no->chave << " ";
            emOrdem(no->direita);
        }
    }

public:
    ArvoreAVL() : raiz(nullptr) {}

    void inserir(int chave) {
        raiz = inserir(raiz, chave);
    }

    void emOrdem() {
        emOrdem(raiz);
        std::cout << std::endl;
    }
};

int main() {
    ArvoreAVL arvore;

    // Insere chaves na árvore
    arvore.inserir(10);
    arvore.inserir(20);
    arvore.inserir(30);

    // Imprime a árvore em ordem
    std::cout << "Arvore AVL em Ordem: ";
    arvore.emOrdem();

    return 0;
}
