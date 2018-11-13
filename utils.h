/*
 * CP Interpolation & Fit Demo
 * Copyright (C) 2018 Fabian Hummer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef UTILS_H
#define UTILS_H

QVector<double> triSolve(QVector<double> a, QVector<double> b, QVector<double> c, QVector<double> f);

bool testTrisolve();

bool almostEqual(double n1, double n2, double epsilon = 1e-10);

int lowerBoundsBinarySearch(double xValue, QVector<double> x);

bool testLBBinarySearch();

void printQVector(QVector<double> vec);

void printQMatrix(QVector<QVector<double>> mat);

double determinant(QVector<QVector<double>> matrix);

void testLinAlgFunctions();

QVector<double> linSolve(QVector<QVector<double>> mat, QVector<double> f, bool invertSign = false);

#endif /* UTILS_H */

