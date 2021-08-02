#include <iostream>
#include <vector>
#include <sstream>
#include "Projeto.h"
using namespace std;

int main() {
	vector<Matriz*> matrizes; // Vetor de ponteiros para matrizes

    while(true) {
		string cmd;
		getline(cin, cmd);

		std::stringstream ss{ cmd };
		vector<string> tokens;
		string buffer;

		while(ss >> buffer) {
			tokens.push_back(buffer);
		}
        
		if(tokens[0] == "libera" || tokens[0] == "exit") {
			for(int i = 0; i < matrizes.size(); ++i) {
				delete matrizes[i];
				matrizes[i] = nullptr;
			}
			matrizes.clear();
			break;
		}
		// cria [l] [c]
		if(tokens[0] == "cria") {
            string arq = tokens[1];
            Matriz *m = lerMatrizDeArquivo(arq);
			matrizes.push_back(m);
		}
		// imprime [k]
		else if(tokens[0] == "imprime") {
			int k = stoi(tokens[1]);
			matrizes[k]->print();
		}
		// nlinhas [k]
		/*else if(tokens[0] == "nlinhas") {
			int k = std::stoi(tokens[1]);
			cout << "linhas: " << matrizes[k]->linhas() << endl;
		}*/
        // ncolunas [k]
		/*else if(tokens[0] == "ncolunas") {
			int k = std::stoi(tokens[1]);
			cout << "colunas: " << matrizes[k]->colunas() << endl;
		}*/
        // valor [i] [j] [k]
		/*else if(tokens[0] == "valor") {
			int k = std::stoi(tokens[3]);
            int i = std::stoi(tokens[1]);
            int j = std::stoi(tokens[2]);
			cout << "valor: " << matrizes[k]->valor(i,j) << endl;
		}*/
		// soma [p] [q] 
		else if(tokens[0] == "soma") {
            int fst = std::stoi(tokens[1]);
            int snd = std::stoi(tokens[2]);
			Matriz *C = soma(matrizes[fst],matrizes[snd]);
			if(C == nullptr) 
                cout << "nao foi possivel somar" << endl;
            else {
                C->print();
                delete C;
            }
		}
        // multiplica [p] [q] 
		else if(tokens[0] == "multiplica") {
            int fst = std::stoi(tokens[1]);
            int snd = std::stoi(tokens[2]);
			Matriz *C = multiplica(matrizes[fst],matrizes[snd]);
			if(C == nullptr) 
                cout << "nao foi possivel multiplicar" << endl;
            else {
                C->print();
                delete C;
            }
		}
		else {
			cout << "comando inexistente" << endl;
		}
	}
	return 0;
}
