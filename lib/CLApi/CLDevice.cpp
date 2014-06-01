#include "../../include/CLApi/CLDevice.h"
#include "../../include/CLApi/CLException.h"

CLDevice::CLDevice()
{
    std::vector<cl::Platform> platforms;
    std::vector<cl::Device>   devices;

    // Can ignore return value, checking the vector size instead
    cl::Platform::get(&platforms);

    if (platforms.size() > 0)
    {
        cl::Platform default_platform = platforms[0];

        // Can ignore the return value, checking the vector size instead
        default_platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);

        if (devices.size() > 0)
        {
            default_device = devices[0];
            return;
        }

        throw CLException("No devices found\n");
    }

    throw CLException("No platforms found\n");
}

CLDevice::~CLDevice()
{
}

cl::Device& CLDevice::get_default_device()
{
    return default_device;
}