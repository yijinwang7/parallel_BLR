
#ifndef LINEARSYSTEMSOLVER_PARALLLHY_H
#define LINEARSYSTEMSOLVER_PARALLLHY_H
#include"randomPermutation.h"
#include <Eigen/Dense>
#include <vector>
#include <omp.h>
#include "CO2_ordering_new.h"
#include "LLLZ.h"
#include <iomanip>
#include <fplll.h>
#include "utils.h"
#include "lllmatrix.h"
#include <iostream>

LLLMatrix paraLLLHy(LLLMatrix B, int p, int fre, int b_size);
#endif //LINEARSYSTEMSOLVER_PARALLLHY_H
