#include <iostream>
#include "SparseMatrix.h"

using namespace std;

void showMenu() {
    cout << "\n===== Menu de Operações =====\n";
    cout << "1 - Criar Matrizes\n";
    cout << "2 - Inserir Valor em Matrizes\n";  // Modificado para 'Inserir Valor em Matrizes'
    cout << "3 - Obter Valor\n";
    cout << "4 - Exibir Matrizes\n";
    cout << "5 - Somar Matrizes\n";
    cout << "6 - Multiplicar Matrizes\n";
    cout << "7 - Ler Matrizes de Arquivo\n";
    cout << "0 - Sair\n";
    cout << "Escolha uma opção: ";
}

int main() {
    SparseMatrix* matriz1 = nullptr;
    SparseMatrix* matriz2 = nullptr;
    SparseMatrix* resultado = nullptr;
    
    int opcao;
    do {
        showMenu();
        cin >> opcao;

        switch (opcao) {
            case 1: { // Criar matrizes
                int linhas, colunas;
                cout << "Digite o número de linhas e colunas para a matriz 1: ";
                cin >> linhas >> colunas;
                matriz1 = new SparseMatrix(linhas, colunas);

                cout << "Digite o número de linhas e colunas para a matriz 2: ";
                cin >> linhas >> colunas;
                matriz2 = new SparseMatrix(linhas, colunas);

                cout << "Matrizes criadas com sucesso!\n";
                break;
            }
            case 2: { // Inserir valor em matrizes
                if (!matriz1 || !matriz2) {
                    cout << "Crie as duas matrizes primeiro!\n";
                    break;
                }
                int matrizEscolhida, i, j;
                double valor;
                cout << "Escolha em qual matriz inserir o valor (1 - Matriz 1, 2 - Matriz 2): ";
                cin >> matrizEscolhida;

                if (matrizEscolhida == 1) {
                    cout << "Digite a linha, coluna e o valor para a matriz 1: ";
                    cin >> i >> j >> valor;
                    matriz1->insert(i, j, valor);
                    cout << "Valor inserido na matriz 1!\n";
                } else if (matrizEscolhida == 2) {
                    cout << "Digite a linha, coluna e o valor para a matriz 2: ";
                    cin >> i >> j >> valor;
                    matriz2->insert(i, j, valor);
                    cout << "Valor inserido na matriz 2!\n";
                } else {
                    cout << "Opção inválida! Escolha 1 ou 2.\n";
                }
                break;
            }
            case 3: { // Obter valor
                if (!matriz1) {
                    cout << "Crie a matriz 1 primeiro!\n";
                    break;
                }
                int i, j;
                cout << "Digite a linha e coluna para a matriz 1: ";
                cin >> i >> j;
                cout << "Valor na posição (" << i << ", " << j << ") da matriz 1: " << matriz1->getValue(i, j) << "\n";
                break;
            }
            case 4: { // Exibir matrizes
                if (!matriz1 || !matriz2) {
                    cout << "Crie as duas matrizes primeiro!\n";
                    break;
                }
                cout << "Matriz 1 atual:\n";
                matriz1->print();
                cout << "\nMatriz 2 atual:\n";
                matriz2->print();
                break;
            }
            case 5: { // Somar matrizes
                if (!matriz1 || !matriz2) {
                    cout << "Crie as duas matrizes primeiro!\n";
                    break;
                }
                resultado = new SparseMatrix(sum(*matriz1, *matriz2));
                cout << "Resultado da soma:\n";
                resultado->print();
                break;
            }
            case 6: { // Multiplicar matrizes
                if (!matriz1 || !matriz2) {
                    cout << "Crie as duas matrizes primeiro!\n";
                    break;
                }
                resultado = new SparseMatrix(multiply(*matriz1, *matriz2));
                cout << "Resultado da multiplicação:\n";
                resultado->print();
                break;
            }
            case 7: { // Ler matrizes de arquivo
                if (!matriz1 || !matriz2) {
                    cout << "Crie as duas matrizes primeiro!\n";
                    break;
                }
                string fileName;
                cout << "Digite o nome do arquivo para a matriz 1: ";
                cin >> fileName;
                try {
                    readSparseMatrix(*matriz1, fileName);
                    cout << "Matriz 1 carregada com sucesso!\n";
                } catch (const exception& e) {
                    cout << "Erro ao carregar matriz 1: " << e.what() << endl;
                }
                
                cout << "Digite o nome do arquivo para a matriz 2: ";
                cin >> fileName;
                try {
                    readSparseMatrix(*matriz2, fileName);
                    cout << "Matriz 2 carregada com sucesso!\n";
                } catch (const exception& e) {
                    cout << "Erro ao carregar matriz 2: " << e.what() << endl;
                }
                break;
            }
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida! Tente novamente.\n";
                break;
        }
    } while (opcao != 0);

    // Liberar memória
    if (matriz1) delete matriz1;
    if (matriz2) delete matriz2;
    if (resultado) delete resultado;

    return 0;
}
