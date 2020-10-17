/*
 * anomaly_detection_util.cpp
 *
 * Author: 311319099
 */

#include <math.h>
#include "anomaly_detection_util.h"


float avg(float* x, int size){
	float temp_avg = 0.0;
    for(int i = 0; i < size; i++) {
        temp_avg += (x[i] / size);
    }
    return temp_avg;
}


// returns the variance of X and Y
float var(float* x, int size){
	float average = avg(x, size);
    float tempVariance = 0.0;
    for(int i = 0; i < size; i++) {
        tempVariance += pow(x[i] - average, 2) / size;
    }
    return tempVariance;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
	float xAverage = avg(x, size);
    float yAverage = avg(y, size);
    float tempCovariance = 0.0;
    for(int i = 0; i < size; i++) {
        tempCovariance += (x[i] - xAverage)*(y[i] - yAverage) / size;
    }
    return tempCovariance;
}

/* Return the deviation */
float deviation(float* x, int size) {
    return sqrt(var(x, size));
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
	return cov(x, y, size) / (deviation(x, size) * deviation(y, size));
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){
	float arrX[size];
    float arrY[size];
    for(int i = 0; i < size; i++) {
        arrX[i] = points[i]->x;
        arrY[i] = points[i]->y;
    }
    float a = cov(arrX, arrY, size) / var(arrX, size);
    float b = avg(arrY, size) - a * avg(arrX, size);
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
	Line linearRegLine = linear_reg(points, size);
    return dev(p, linearRegLine);
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	return fabs((l.a * p.x + l.b) - p.y);
	}
