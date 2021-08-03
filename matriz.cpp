#include "Projeto.h"
#include <fstream>
using namespace std;

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
    
    double Matriz::getValue(int i,int j) {
        Node *aux = head->direita;
        while(aux->coluna != j)
            aux = aux->direita;
        Node *it = aux->abaixo;
        while(it != aux || i == it->linha)
            it = it->abaixo;
        return it->valor;
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

    void Matriz::print() {
        /*Node *aux = head->abaixo; // olhar como foi inserido os nós
        Node *it = aux->direita;
        while(aux != head) {
            while(it != aux) {
                cout << "linha: " << it->linha << " coluna: " << it->coluna << " -> ";
                it = it->direita;
            }
            cout << endl;
            aux = aux->abaixo;
            it = aux->direita;
        }*/

        Node *aux = head;
        Node *it = aux;
        for(int i = 1; i <= Ltam; i++) {
            aux = aux->abaixo;
            it = aux;
            for(int j = 1; j <= Ctam; j++) {
                if(it->direita->linha == -1)
                    cout << 0 << " ";
                else if(it->direita->coluna == j) {
                    it = it->direita;
                    cout << it->valor << " ";
                }
                else
                    cout << 0 << " ";
            }
            cout << endl;
        }
    }

    Matriz *soma (Matriz *A, Matriz *B) {
        int linhas = A->getTamLinhas();
        int colunas = A->getTamCols();
        if(linhas != B->getTamLinhas() || colunas != B->getTamCols())
            return nullptr;
        
        Node *auxA = A->getHead();
        Node *itA = auxA->direita;
        Node *auxB = B->getHead();
        Node *itB = auxB->direita;
        Matriz *C = new Matriz(linhas, colunas);
        
        for(int i = 1; i <= linhas; i++) {
            auxA = auxA->abaixo;
            itA = auxA->direita;
            auxB = auxB->abaixo;
            itB = auxB->direita;
            while(itA->coluna != -1 || itB->coluna != -1) {
                //cout << "A: " << itA->coluna << " B: " << itB->coluna << endl;
                if(itA->coluna == itB->coluna) {
                    C->insert(i, itA->coluna, itA->valor+itB->valor);
                    itA = itA->direita;
                    itB = itB->direita;
                } else if (itA->coluna < itB->coluna && itA->coluna != -1 || itB->coluna == -1) {
                    C->insert(i, itA->coluna, itA->valor);
                    itA = itA->direita;
                } else {
                    C->insert(i, itB->coluna, itB->valor);
                    itB = itB->direita;
                }
            }
        }
        //cout << "end";
        return C;
    }
    
    Matriz *multiplica(Matriz *A, Matriz *B) {
        int linhasA = A->getTamLinhas();
        int linhasB = B->getTamLinhas();
        int colunasA = A->getTamCols();
        int colunasB = B->getTamCols();

        if(colunasA != linhasB)
            return nullptr;
        
        Node *auxA = A->getHead();
        Node *itA;
        Node *auxB;
        Node *itB;
        Matriz *C = new Matriz(linhasA, colunasB);
        int valor = 0, valorA = 0, valorB = 0;
        for(int i = 1; i <= linhasA; i++) {
            auxA = auxA->abaixo;
            auxB = B->getHead();
            for(int j = 1; j <= colunasB; j++) {
                auxB = auxB->direita;
                itB = auxB;
                itA = auxA;
                valor = 0;
                for(int k = 1; k <= colunasA; k++) {
                    if(k != 1 && itA->linha == -1 && itB->coluna == -1)
                        break;
                    valorA = valorB = 0;
                    if(itA->direita->coluna == k)
                        itA = itA->direita;
                    if(itB->abaixo->linha == k)
                        itB = itB->abaixo;
                    if(itA->coluna == k)
                        valorA = itA->valor;
                    if(itB->linha == k)
                        valorB = itB->valor;
                    cout << valorA << " * " << valorB << " + ";
                    valor += valorA*valorB;
                }
                //auxB = auxB->direita;
                cout << " = " << valor << endl;
                C->insert(i, j, valor);
            }
        }
        return C;
        /*
        Matriz *retorno = nullptr;
	    if(this->_c != B->_l)
		    return retorno;
	    else {
		    int valor;
		    retorno = new Matriz(this->_l, B->_c);
		    for(int i = 0; i < _l; i++)
			    for(int j = 0; j < B->_c; j++)	{
				    int valor = 0;
				    for(int k = 0; k < _c; k++) {
					    valor += this->_M[i][k]*B->_M[k][j];
				    }
				    retorno->_M[i][j] = valor;
			    }
		    return retorno;
	    }
        */
        
    }

    Matriz *lerMatrizDeArquivo(std::string arq) {
        ifstream arquivo;
        arquivo.open(arq);
        int linha, coluna;
        double valor;
        arquivo >> linha;
        arquivo >> coluna;
        Matriz *nova = new Matriz(linha, coluna);
        while(arquivo >> linha) {
            arquivo >> coluna;
            arquivo >> valor;
            nova->insert(linha, coluna, valor);
        }
        arquivo.close();
        return nova;
    }
