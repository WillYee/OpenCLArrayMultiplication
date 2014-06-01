#pragma once
#ifndef CLDEVICE_H
#define CLDEVICE_H

#include <vector>
#include "../cl.hpp"

class CLDevice
{
public:
    CLDevice();
    ~CLDevice();

    cl::Device& get_default_device(void);
    
private:
    
    cl::Device default_device;

    CLDevice(const CLDevice&); // Disable copy constructor
    CLDevice& operator=(const CLDevice&); // Disable assignment operator

};

#endif

