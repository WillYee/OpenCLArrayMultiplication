#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <iostream>
#include <string>

#include "include/cl.hpp"
#include "include/ArguementParser.h"
#include "include/CLArrayMult.h"
#include "include/FileIOException.h"
#include "include/ParseException.h"
#include "include/CLApi/CLException.h"

const float TOL = 0.50f;

int main(int argc, char *argv[])
{
    double compute_time = -1;

    ArgumentParser parser(argc, (const char**)argv);

    try
    {
        parser.Validate();
    }
    catch (ParseException& e)
    {
        std::cerr << e.what();
        return 1;
    }

    int num_elements = parser.get_num_elements();
    int local_size   = parser.get_local_size();

    float *hA = new float[num_elements];
    float *hB = new float[num_elements];
    float *hC = new float[num_elements];

    // fill the host memory buffers:
    for (int i = 0; i < num_elements; i++)
    {
        hA[i] = hB[i] = sqrt((float)i);
    }

    CLArrayMult<float> array_mult(num_elements, local_size, hA, hB, hC);
    
    try
    {
	    compute_time = array_mult.compute();
    }
    catch (std::runtime_error& e)
    {
        std::cerr << e.what();
        return 1;
    }

    for (int i = 0; i < num_elements; i++)
    {
        if (fabs(hC[i] - (float)i) > TOL)
        {
            std::cout << i << ": " << hA[i] << " * " << hB[i] << " wrongly produced " << hC[i] << " " << "(" << (float)i << ")" << std::endl;
        }
    }

    std::cout << num_elements << "\t" << local_size << "\t" << (float)num_elements / (compute_time) / 1000000000. << " GigaMultsPerSecond" << std::endl;

    // Clean up allocations
    delete[] hA;
    delete[] hB;
    delete[] hC;

    return 0;
}
