#pragma once
#include<bits/stdc++.h>

using namespace std;

//The number of dimensions
#define DIMENSION 2

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define sqr(x) ((x) * (x))

//type of floating points
typedef double db;

//relative floating point error
const db eps = 1e-10;

//compare function of floating point
//input: float point value x
//output: 0: x is zero | 1: x > 0 |-1: x < 0 
int dcmp(const db &x);