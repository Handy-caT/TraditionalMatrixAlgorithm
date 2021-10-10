//
//  main.cpp
//  TraditionalMatrixAlgorithm
//
//  Created by Максим on 9.10.21.
//

#include <iostream>
#include <ctime>
#include <iomanip>

void RandomSet() {
    srand(static_cast<unsigned int>(time(0)));
}

int Random(int min, int max) {
    return rand() % (max- min + 1) + min;
}

void ArrayShow(double* arr,int lenght) {
    
    int i = 0;
    while( i < lenght ) {
        std::cout << std::setprecision(24) << arr[i] << std::endl;
        i++;
    }
}

double* randomArray(int lenght) {
    
    int i = 0;
    double* arr = new double[lenght];
    
    while( i < lenght) {
        arr[i] = Random(-100, 100);
        i++;
    }
    return arr;
    
}

double* makeC( double* a, double* b, int lenght) {
    
    double* c = new double[lenght];
    c[0] = Random(abs(b[0]) + 1, abs(b[0]) + 2);
    
    int i = 1;
    while( i < lenght - 1) {
        c[i] = Random(abs(a[i]) + abs(b[i]) + 1, abs(a[i]) + abs(b[i]) + 2);
        i++;
    }
    
    c[lenght - 1] = Random(abs(a[lenght - 1]) + 1, abs(a[lenght - 1]) + 2);
    return c;
    
}

double* makeY( int lenght ) {
    
    double* y = new double[lenght];
    int i = 0;
    
    while( i < lenght ) {
        y[i] = i + 1;
        i++;
    }
    
    return y;
    
}

double* makeF( double* a, double* b, double* c, double* y, int lenght ) {
    
    double* f = new double[lenght];
    f[0] = c[0]*y[0] + b[0]*y[1];
    
    int i  = 1;
    while( i < lenght - 1 ) {
        f[i] = a[i]*y[i-1] + c[i]*y[i] + b[i]*y[i+1];
        i++;
    }
    
    f[lenght - 1] = a[lenght - 1]*y[lenght - 2] + c[lenght - 1]*y[lenght - 1];
    return f;
    
}

double* ArrayResidual( double* left, double* right, int lenght) {
    
    double* residual = new double[lenght];
    int i = 0;
    
    while( i < lenght ) {
        residual[i] = left[i] - right[i];
        i++;
    }
    
    return residual;
    
}

double MaxInArray( double* arr, int lenght) {
    
    int i = 0;
    double max = abs(arr[0]);
    
    while( i < lenght) {
        if( abs(arr[i]) > max ) max = abs(arr[i]);
        i++;
    }
    
    return max;
    
}

double* TraditionalMatrixAlgorithm(double* a, double* b, double* c, double* f, int lenght) {
    
    double* alpha = new double[lenght+1];
    double* beta = new double[lenght+1];
    double* y = new double[lenght];
    
    alpha[1] = -b[0]/c[0];
    beta[1] = f[0]/c[0];
    
    int i = 1;
    double temp;
    while( i < lenght - 1 ) {
        temp = c[i] + a[i]*alpha[i];
        alpha[i+1] = -b[i]/temp;
        beta[i+1] = (f[i] - a[i]*beta[i])/temp;
        i++;
    }
    
    temp = c[lenght-1] + a[lenght-1]*alpha[lenght-1];
    beta[lenght] = (f[lenght-1] - a[lenght-1]*beta[lenght-1])/temp;
    
    y[lenght-1] = beta[lenght];
    i = lenght - 2;
    while( i > -1) {
        y[i] = alpha[i+1]*y[i+1] + beta[i+1];
        i--;
    }
    
    return y;
}

void Task() {
    
    double* a = randomArray(10);
    std::cout << "a:" << std::endl;
    ArrayShow(a, 10);
    std::cout << std::endl;
    double* b = randomArray(10);
    std::cout << "b:" << std::endl;
    ArrayShow(b, 10);
    std::cout << std::endl;
    double* c = makeC(a ,b ,10);
    std::cout << "c:" << std::endl;
    ArrayShow(c, 10);
    std::cout << std::endl;
    
    double* y = makeY(10);
    std::cout << "y:" << std::endl;
    ArrayShow(y, 10);
    std::cout << std::endl;
    double* f = makeF(a, b, c, y, 10);
    std::cout << "f:" << std::endl;
    ArrayShow(f, 10);
    std::cout << std::endl;
    double* y1 = TraditionalMatrixAlgorithm(a, b, c, f, 10);
    std::cout << "y1:" << std::endl;
    ArrayShow(y1, 10);
    std::cout << std::endl;
    
    double* residual = ArrayResidual(y, y1, 10);
    double inaccuracy = MaxInArray(residual, 10)/10.0;
    std::cout << std::setprecision(2) << inaccuracy << std::endl;
    
}

int main(int argc, const char * argv[]) {
 
    RandomSet();
    Task();
    
}
