#include <qt5/QtCore/qvector.h>
#include <cmath>

#include "utils.h"

void triSolve(QVector<double>& result, QVector<double>& a, QVector<double>& b, QVector<double>& c, QVector<double>& f) {
    const int size = b.size();

    QVector<double> beta(size);
    QVector<double> rho(size);
    
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
}

inline bool almostEqual(double n1, double n2, double epsilon = 1e-10) {
    return std::abs(n1-n2) < epsilon;
}

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
    
    triSolve(result, a, b, c, f);
    
    for (int i = 0; i < result.size(); i++) {
        if (!almostEqual(result[i], exactResult[i],1e-10))
            return false;
    }
    
    return true;
}

int lowerBoundsBinarySearch(double xValue, QVector<double>& x) {
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
