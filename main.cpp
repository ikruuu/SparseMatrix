#include "SparseMatrix.h"

using namespace std;

int main() {
    SparseMatrix matrix(4, 4);

    matrix.insert(1, 1, 50.0);
    matrix.insert(2, 1, 10.0);
    matrix.insert(2, 3, 20.0);
    matrix.insert(4, 1, -30.0);
    matrix.insert(4, 3, -60.0);
    matrix.insert(4, 4, 5.0);

    matrix.print();

    SparseMatrix outra(4, 4);
    outra.insert(1, 1, 10.0);
    outra.insert(2, 1, 5.0);
    outra.insert(2, 3, 15.0);
    outra.insert(4, 1, -20.0);
    outra.insert(4, 3, -50.0);
    outra.insert(4, 4, 10.0);

    outra.print();

    

    return 0;
}