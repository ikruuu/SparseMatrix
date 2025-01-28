//DEFINES
#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

//INCLUDES
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>


// Criando o nó
struct Node {
    Node* right;
    Node* down;
    int line;
    int colun;
    double value;

    Node(int line, int colun, double value) : right(this), down(this), line(line), colun(colun), value(value) {}
};

// Criando a classe referente a matriz
class SparseMatrix {
private:
    int lines;
    int coluns;
    Node** LineHeaders;
    Node** ColunHeaders;

    // Método que libera a memória alocada
    void freeMemory();

public:
    // Construtor e Destrutor
    SparseMatrix(int m, int n);
    ~SparseMatrix();

    // Criando funções-membro
    void insert(int i, int j, double value);
    double getValue(int i, int j);
    void print();

    int getLines() const;
    int getColuns() const;
    Node* getLineHeader(int i) const;
    Node* getColunHeader(int j) const;

    SparseMatrix sum(SparseMatrix& A, SparseMatrix& B);
    SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B);
};

#endif

