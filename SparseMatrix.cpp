//INCLUDES
#include "SparseMatrix.h"

using namespace std;

// Construtor padrão
SparseMatrix::SparseMatrix(int m, int n) : lines(m), coluns(n) {
    if (m <= 0 || n <= 0) {
        throw invalid_argument("Inserir dimensões válidas");
    }
    LineHeaders = new Node*[m + 1];
    ColunHeaders = new Node*[n + 1];

    for (int i = 1; i <= m; ++i) {
        LineHeaders[i] = new Node(i, 0, 0.0);
        ColunHeaders[i]->right = LineHeaders[i];
    }
    for (int j = 1; j <= n; ++j) {
        ColunHeaders[j] = new Node(0, j, 0.0);
        ColunHeaders[j]->down = ColunHeaders[j];
    }
}

// Destrutor
SparseMatrix::~SparseMatrix() {
    freeMemory();
}

// Método destrutor
void SparseMatrix::freeMemory() {
    for (int i = 1; i <= lines; ++i) {
        Node* current = LineHeaders[i];
        while (current->right != LineHeaders[i]) {
            Node* toDelete = current;
            current = current->right;
            delete toDelete;
        }
        delete current;
    }
    delete[] LineHeaders;
    delete[] ColunHeaders;
}

// Método para inserir ou atualizar um elemento
void SparseMatrix::insert(int i, int j, double value) {
    if (i < 1 || i > lines || j < 1 || j > coluns) {
        throw out_of_range("Valor fora do limite da matriz");
    }
    if (value == 0) return;

    Node* LineHead = LineHeaders[i];
    Node* ColunHead = ColunHeaders[j];

    Node* current = LineHead;
    while (current->right != LineHead && current->right->colun < j) {
        current = current->right;
    }

    if (current->right != LineHead && current->right->colun == j) {
        current->right->value = value;
        return;
    }

    Node* newNode = new Node(i, j, value);
    newNode->right = current->right;
    current->right = newNode;

    current = ColunHead;
    while (current->down != ColunHead && current->down->line < i) {
        current = current->down;
    }

    newNode->down = current->down;
    current->down = newNode;
}

// Pega um valor armazenado na posição (i, j), caso não exista, retorna 0
double SparseMatrix::getValue(int i, int j) {
    if (i < 1 || i > lines || j < 1 || j > coluns) {
        throw out_of_range("Valor fora do limite da matriz");
    }

    Node* current = LineHeaders[i]->right;
    while (current != LineHeaders[i]) {
        if (current->colun == j) {
            return current->value;
        }
        current = current->right;
    }
    return 0;
}

// Printa a matriz
void SparseMatrix::print() {
    for (int i = 1; i <= lines; ++i) {
        for (int j = 1; j <= coluns; ++j) {
            cout << getValue(i, j) << " ";
        }
            cout << "\n";
    }
}

int SparseMatrix::getLines() const { return lines; }
int SparseMatrix::getColuns() const { return coluns; }

Node* SparseMatrix::getLineHeader(int i) const {
    if (i < 1 || i > lines) {
        throw std::out_of_range("Índice de linha fora dos limites.");
    }
    return LineHeaders[i];
}

Node* SparseMatrix::getColunHeader(int j) const {
    if (j < 1 || j > coluns) {
        throw out_of_range("Índice de coluna fora dos limites.");
    }
    return ColunHeaders[j];
}


// Soma de matrizes
SparseMatrix sum(SparseMatrix& A, SparseMatrix& B) {
    if (A.getLines() != B.getLines() || A.getColuns() != B.getColuns()) {
        throw std::invalid_argument("As matrizes devem ter as mesmas dimensões para soma-las");
    }

    SparseMatrix result(A.getLines(), A.getColuns());

    for (int i = 1; i <= A.getLines(); ++i) {
    Node* currentA = A.getLineHeader(i)->right;
    Node* currentB = B.getLineHeader(i)->right;

    while (currentA != A.getLineHeader(i) || currentB != B.getLineHeader(i)) {
        if (currentA != A.getLineHeader(i) && (currentB == B.getLineHeader(i) || currentA->colun < currentB->colun)) {
            result.insert(i, currentA->colun, currentA->value);
            currentA = currentA->right;
        } else if (currentB != B.getLineHeader(i) && (currentA == A.getLineHeader(i) || currentB->colun < currentA->colun)) {
            result.insert(i, currentB->colun, currentB->value);
            currentB = currentB->right;
        } else {
            result.insert(i, currentA->colun, currentA->value + currentB->value);
            currentA = currentA->right;
            currentB = currentB->right;
        }
    }
}


    return result;
}
// Multiplicação de matrizes
SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B) {
    if (A.getColuns() != B.getLines()) {
        throw invalid_argument("As matrizes devem ter as mesmas dimensões para multiplica-las");
    }
    
    SparseMatrix result(A.getLines(), B.getColuns());

    for (int i = 1; i <= A.getLines(); ++i) {
        for (int j = 1; j <= B.getColuns(); ++j) {
            double sum = 0.0;

            Node* currentA = A.getLineHeader(i)->right;
            while (currentA != A.getLineHeader(i)) {
                double valueB = B.getValue(currentA->colun, j);
                sum += currentA->value * valueB;
                currentA = currentA->right;
            }

            if (sum != 0.0) {
                result.insert(i, j, sum);
            }
        }
    }

    return result;
}
