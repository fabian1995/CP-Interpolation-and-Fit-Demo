/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utils.h
 * Author: fabian
 *
 * Created on 25. Oktober 2018, 20:41
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

