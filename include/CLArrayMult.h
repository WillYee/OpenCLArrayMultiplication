#pragma once
#ifndef CLARRAYMULT_H
#define CLARRAYMULT_H

// Exceptions are enabled, can ignore cl return values
#define __CL_ENABLE_EXCEPTIONS

#include <omp.h>
#include <iostream>

#include "cl.hpp"
#include "CLApi/CLDevice.h"
#include "CLApi/CLKernel.h"

template <typename TYPE>
class CLArrayMult
{
public:
    CLArrayMult(const int num_elements,
                const int l_size,
                TYPE* pOper_a,
                TYPE* pOper_b,
                TYPE* pRes)
                : data_size(num_elements * sizeof(TYPE))
                , global_size(num_elements)
                , local_size(l_size)
                , pOperand_a(pOper_a)
                , pOperand_b(pOper_b)
                , pResult(pRes)
    { }

    ~CLArrayMult() { }

    // This function will do the actual array multiplication
    double compute()
    {
        // Initialize our devices and queues
        CLDevice         device;
        cl::Context      context({ device.get_default_device() });
        cl::CommandQueue queue(context, device.get_default_device());

        // Initialize the CL buffers for read/write operations
        cl::Buffer operand_a = cl::Buffer(context, CL_MEM_READ_ONLY, data_size);
        cl::Buffer operand_b = cl::Buffer(context, CL_MEM_READ_ONLY, data_size);

        cl::Buffer result    = cl::Buffer(context, CL_MEM_WRITE_ONLY, data_size);

        // Write out our two operands to the CL Buffer
        queue.enqueueWriteBuffer(operand_a, CL_FALSE, 0, data_size, pOperand_a);
        queue.enqueueWriteBuffer(operand_b, CL_FALSE, 0, data_size, pOperand_b);

        // Set up the kernel object to run ArrayMult in the CL device
        CLKernel kernel_config(FUNCTION_NAME, FILE_NAME, context, device.get_default_device());
     
        // Set the arguments for the two operands and the result buffers
        kernel_config.set_kernel_arg(0, operand_a);
        kernel_config.set_kernel_arg(1, operand_b);
        kernel_config.set_kernel_arg(2, result);

        cl::NDRange global_work_size(global_size, 1, 1);
        cl::NDRange local_work_size(local_size, 1, 1);

        queue.enqueueBarrier();

        double time0 = omp_get_wtime();

        queue.enqueueNDRangeKernel(kernel_config.get_kernel(), cl::NullRange, global_work_size, local_work_size);
        queue.enqueueBarrier();

        double time1 = omp_get_wtime();

        // Write the results back out to the result buffer pointed to by the pointer passed in
        queue.enqueueReadBuffer(result, CL_TRUE, 0, data_size, pResult);

        return time1 - time0;
    }

private:

    TYPE* pOperand_a;
    TYPE* pOperand_b;
    TYPE* pResult;

    size_t   data_size;
    int      global_size;
    int      local_size;

    const std::string FUNCTION_NAME = "ArrayMult";
    const std::string FILE_NAME     = "ArrayMult.cl";

    CLArrayMult(const CLArrayMult&); // Disable copy constructor
    CLArrayMult& operator=(const CLArrayMult&); // Disable assignment operator
};

#endif