#include <QVector>
#include <cmath>
#include <iostream>

#include "utils.h"

/**
 * Solves a trigonal system of equations using the Thomas Algorithm
 * @param a Lower diagonal of the matrix
 * @param b Main diagonal of the matrix
 * @param c Upper diagonal of the matrix
 * @param f Right side of the equation
 * @return Solution to the equation
 */
QVector<double> triSolve(QVector<double> a, QVector<double> b, QVector<double> c, QVector<double> f) {
    const int size = b.size();

    QVector<double> beta(size);
    QVector<double> rho(size);
    QVector<double> result(size);
    
    beta[0] = b[0];
    rho[0] = f[0];
    
    for(int i = 1; i < size; i++) {
        beta[i] = b[i] - a[i-1]*c[i-1]/beta[i-1];
        rho[i] = f[i] - a[i-1]*rho[i-1]/beta[i-1];
    }
    
    result[size-1] = rho[size-1] / beta[size-1];
    
    for(int i = size-2; i >= 0; i--) {
        result[i] = (rho[i] - c[i] * result[i+1]) / beta[i];
    }
    
    return result;
}

/**
 * Compares two double precision floating point numbers
 * @param n1 input number
 * @param n2 input number
 * @param epsilon tolerance for comparison
 * @return true, if difference between n1 and n2 is less than epsilon
 */
bool almostEqual(double n1, double n2, double epsilon) {
    return std::abs(n1-n2) < epsilon;
}

/**
 * Tests the function "triSolve" for a specific case
 * @return true, if test has been passed
 */
bool testTrisolve() {
    QVector<double> a { 1,1,1 };
    QVector<double> b { 1,2,3,4 };
    QVector<double> c { 3,2,1 };
    QVector<double> f { 2,2,2,2 };
    
    QVector<double> result(4);
    QVector<double> exactResult {
        0.1052631578949,
        0.63157894736842,
        0.3157894736842,
        0.42105263157894
    };
    
    result = triSolve(a, b, c, f);
    
    for (int i = 0; i < result.size(); i++) {
        if (!almostEqual(result[i], exactResult[i],1e-10))
            return false;
    }
    
    return true;
}

/**
 * Searches for the interval of values that the given parameter xValue lies within.
 * Returns the lower index of the interval.
 * @param xValue value that should be in one of the intervals
 * @param x Vector of index boundaries
 * @return Index of the left interval boundarx. 0 if xValue is below the lowest
 * interval. Returns last index if xValue is greater than the highest interval 
 * border.
 */
int lowerBoundsBinarySearch(double xValue, QVector<double> x) {
    int lowerIndex = 0;
    int upperIndex = x.size()-2;
    int midIndex = (upperIndex + lowerIndex) / 2;
    
    // Check if we are looking for boundary values
    if (xValue <= x.at(lowerIndex)) {
        return lowerIndex;
    }
    else if (xValue >= x.at(upperIndex)) {
        return upperIndex;
    }
    
    // Searches for lower index of the interval that encloses xValue
    while (midIndex != lowerIndex) {
        if (xValue > x.at(midIndex)) {
            lowerIndex = midIndex;
        }
        else if (xValue < x.at(midIndex)) {
            upperIndex = midIndex;
        }
        else {
            return midIndex;
        }
        midIndex = (upperIndex + lowerIndex) / 2;
    }
    
    // Result index of this search is lowerIndex if not found in previous steps
    return lowerIndex;
}

/**
 * Tests the function "lowerBoundsBinarySearch" for specific cases.
 * @return true, if the test has been passed.
 */
bool testLBBinarySearch() {
    QVector<double> xIntervals {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    QVector<double> input    {0, 0.1, 3.2, 4.5, 8.99, 9.19, 9.99, 10};
    QVector<double> expected {0, 0,   3,   4,   8,    9,    9,     9};
    
    for (int i = 0; i < input.size(); i++) {
        double res = lowerBoundsBinarySearch(input[i], xIntervals);
        if (!almostEqual(expected[i], res))
            return false;
    }
    
    return true;
}

/**
 * Prints size and contents of a QVector.
 * @param vec QVector to be printed
 */
void printQVector(QVector<double> vec) {
    std::cout << "[size " << vec.size() << "]: ";
    
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << ", ";
    }
    std::cout << std::endl;
}

/**
 * Prints the contents of a matrix made of QVectors.
 * @param mat QVector of QVectors representing a matrix where each inner QVector
 * is one column.
 */
void printQMatrix(QVector<QVector<double>> mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat.size(); j++) {
            std::cout << mat[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * Calculates the submatrix of a given matrix
 * @param mat QVector of QVectors representing a matrix where each inner QVector
 * is one column.
 * @param iInd Index of the LINE to be removed.
 * @param jInd Index of the COLUMN to be removed.
 * @return Submatrix as QVector of QVectors
 */
QVector<QVector<double>> subMatrix(QVector<QVector<double>> mat, int iInd, int jInd) {
    QVector<QVector<double>> sub;
    
    for(int j = 0; j < mat.size(); j++) {
        if (j == jInd) {
            continue;
        }
        mat[j].remove(iInd);
        sub.append(mat[j]);
    }
    
    return sub;
}

/**
 * Calculates the determinant of a given matrix
 * @param mat QVector of QVectors representing a matrix where each inner QVector
 * is one column.
 * @return The determinant of the matrix.
 * @throw "Invalid matrix dimension", e.g. if matrix size is 0.
 */
double determinant(QVector<QVector<double>> mat) {
    if (mat.size() == 1) {
        return mat[0][0];
    }
    else if (mat.size() == 2) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }
    else if (mat.size() == 3) {
        return mat[0][0]*mat[1][1]*mat[2][2] + mat[0][1]*mat[1][2]*mat[2][0] + mat[0][2]*mat[1][0]*mat[2][1]
                - mat[0][2]*mat[1][1]*mat[2][0] - mat[0][1]*mat[1][0]*mat[2][2] - mat[0][0]*mat[1][2]*mat[2][1];
    }
    else if (mat.size() > 3) {
        int i = 0;
        double sum = 0;
        for (int j = 0; j < mat.size(); j++) {
            sum += mat[j][i] * determinant(subMatrix(mat, i, j)) * ((i+j) % 2 == 0 ? 1 : (-1));
        }
        return sum;
    }
    throw "Invalid matrix dimension";
}

/**
 * Tests the functions "determinant" and "linSolve" for specific cases and
 * additionally prints the result of the function "subMatrix" for a specific case.
 * Prints test results to std::out.
 */
void testLinAlgFunctions() {
    using namespace std;
    
    cout << " --- testing determinant ---" << endl;
    
    QVector<QVector<double>> mat2 = {{1,2},{3,4}};
    cout << "Dim 2: " << (almostEqual(determinant(mat2), -2) ? "[OK]" : "[FAIL]") << endl;
    
    QVector<QVector<double>> mat3 = {{2,5,6},{1,9,2},{3,3,5}};
    cout << "Dim 3: " << (almostEqual(determinant(mat3), -61) ? "[OK]" : "[FAIL]") << endl;
    
    QVector<QVector<double>> mat4 = {{2,5,6,0},{1,9,2,2},{3,3,5,6},{1,2,3,1}};
    cout << "Dim 4: " << (almostEqual(determinant(mat4), -63) ? "[OK]" : "[FAIL]") << endl;
    
    printQMatrix(mat3);
    QVector<QVector<double>> sub = subMatrix(mat3, 0, 0);
    cout << "Taking out col 0, line 0: " << endl;
    printQMatrix(sub);
    
    cout << "Equation test: ";
    
    QVector<double> f {1,1,1,-1};
    QVector<double> solution = linSolve(mat4, f);
    QVector<double> correct {1.73016, -0.15873, 0.539683, -3.92063};
    bool solRes = true;
    
    for (int i = 0; i < solution.size(); i++) {
        if (!almostEqual(solution[i], correct[i], 1e-5)) {
            solRes = false;
            break;
        }
    }
    
    if (solRes)
        cout << "[OK]" << endl;
    else
        cout << "[FAIL]" << endl;
    
    cout << " --- finished determinant test ---" << endl;
}

/**
 * Solves a quadratic system of linear equations using Cramer's Rule.
 * @param mat Matrix of the equation, represented as QVector of QVectors.
 * @param f Right side of the equation.
 * @param invertSign If true, the sign of every result is inverted. This flag is
 * set to false by default and is used by the nonlinear fit methods in "fit.cpp"
 * @see fit.cpp
 * @return The result vector that solves the given system of equations.
 */
QVector<double> linSolve(QVector<QVector<double>> mat, QVector<double> f, bool invertSign) {
    double deta = determinant(mat);
    if (invertSign)
        deta *= -1;
    
    QVector<double> x (f.size());
    
    for (int j = 0; j < f.size(); j++) {
        QVector<QVector<double>> mCopy = mat;
        mCopy[j] = f;
        x[j] = determinant(mCopy) / deta;
    }
    
    return x;
}
