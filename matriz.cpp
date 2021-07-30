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
    std::cout << "apagou";
}
