#include "Projeto.h"

Matriz::Matriz(int linhas, int colunas) {
    Ltam = linhas;
    Ctam = colunas;
    head = new Node(-1, -1, 0, nullptr, nullptr);
    head->abaixo = head;
    head->direita = head;
  
    Node *aux = head;
    for(int i = 1; i <= linhas; i++) { //Cria todos os "heads" de cada linhas
        Node *head_Line = new Node(i, -1, 0, nullptr, nullptr);
        head_Line->direita = head_Line;
        aux->abaixo = head_Line;
        aux = head_Line;
    }
    aux->abaixo = head;
    aux = head;
    for(int j = 1; j <= colunas; j++) { //Cria todos os "heads" de cada coluna
        Node *head_Col = new Node(-1, j, 0, nullptr, nullptr);
        head_Col->abaixo = head_Col;
        aux->direita = head_Col;
        aux = head_Col;
    }
    aux->direita = head;
}

void Matriz::insert(int i, int j, double value) {
        //impossível inserir fora da matriz
        if(i > Ltam || j > Ctam)
            return;
        //cria o novo nó e insere ele na coluna correta
        Node *aux = head->direita;
        while(aux->coluna != j)
            aux = aux->direita;
        //cout << "morreu";
        Node *it = aux;
        while(it->abaixo->linha != -1 && it->abaixo->linha < i)
            it = it->abaixo;
        Node *novo = new Node(i, j, value, nullptr, it->abaixo); //nodes???????
        //cout << it->linha << "->" << novo->linha << "->" << it->abaixo->linha << endl;
        it->abaixo = novo;
        
        //coloca o novo nó na linha correta
        aux = head->abaixo;
        while(aux->linha != i)
            aux = aux->abaixo;;
        it = aux;
        while(it->direita->coluna != -1 && it->direita->coluna < j)
            it = it->direita;
        novo->direita = it->direita;
        //cout << it->coluna << "->" << novo->coluna << "->" << it->direita->coluna << endl;
        it->direita = novo;
    }

int Matriz::getTamLinhas() {
    return Ltam;
}

int Matriz::getTamCols() {
    return Ctam;
}

Node* Matriz::getHead() {
    return head;
}

Matriz::~Matriz() {
    Node *it_heads = head->direita;
        Node *it_elems;
        for(int j = 0; j < Ctam; j++) { //deleta as colunas e os elementos armazenados na matriz
            it_elems = it_heads->abaixo;
            while(it_elems != it_heads) {
                Node *aux = it_elems;
                it_elems = it_elems->abaixo;
                delete aux;
            }
            it_heads = it_heads->direita;
            delete it_elems;
        }
        it_heads = head->abaixo;
        for(int i = 0; i < Ltam; i++) { //deleta as linhas
            it_elems = it_heads;
            it_heads = it_heads->abaixo;
            delete it_elems;
        }
}
