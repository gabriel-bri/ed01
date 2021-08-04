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
        
		if(tokens[0] == "cria") {
            string arq = tokens[1];
            Matriz *m = lerMatrizDeArquivo(arq);
			matrizes.push_back(m);
		}

		else if(tokens[0] == "imprime") {
			int k = stoi(tokens[1]);
			matrizes[k]->print();
		}

		// soma [p] [q] 
		else if(tokens[0] == "soma") {
            int fst = std::stoi(tokens[1]);
            int snd = std::stoi(tokens[2]);
			Matriz *C = soma(matrizes[fst],matrizes[snd]);
			if(C == nullptr) 
                cout << "nao foi possivel somar\n" << endl;
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

		else if(tokens[0] == "libera" || tokens[0] == "sair") {
			for(int i = 0; i < matrizes.size(); ++i) {
				delete matrizes[i];
				matrizes[i] = nullptr;
			}
			matrizes.clear();
			break;

			if(tokens[0] == "libera") {
				cout << "Matrizes limpas\n";
			}

			if(tokens[0] == "sair") {
				exit(1);
			}
		}

		else {
			cout << "Comando nao encontrado! \n";
		}
	}
	return 0;
}
