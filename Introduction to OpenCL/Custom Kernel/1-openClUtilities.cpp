/**
    This method provides a readable error message, given one OpenCL code error.
    The several types of errors this function expects are bellow.

    @author Francisco Xavier
    @date   21 Jan 2014
    @email  xavier@informatik.uni-bremen.de
*/

#ifdef __APPLE__
    #include <OpenCL/opencl.h>
#else
    #include <CL/cl.h>
#endif

/**
    checkError converts an openGL related error code into a c string, for a readable print out of the problem.
    @param      errorCode       error code, as cl_uint
    @return     message         c string contaiting the error, correspondent to the provided code
*/
char* checkError(cl_uint errorCode)
{
    switch (errorCode) {
        case CL_SUCCESS:                            return (char*) "SUCCESS";
        case CL_DEVICE_NOT_FOUND:                   return (char*) "DEVICE NOT FOUND";
        case CL_DEVICE_NOT_AVAILABLE:               return (char*) "DEVICE NOT AVAILABLE";
        case CL_COMPILER_NOT_AVAILABLE:             return (char*) "COMPILER NOT AVAILABLE";
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:      return (char*) "MEMORY OBJECT ALLOCATION FAILURE";
        case CL_OUT_OF_RESOURCES:                   return (char*) "OUT OF RESOURCES";
        case CL_OUT_OF_HOST_MEMORY:                 return (char*) "OUT OF HOST MEMORY";
        case CL_PROFILING_INFO_NOT_AVAILABLE:       return (char*) "PROFILING INFORMATION NOT AVAILABLE";
        case CL_MEM_COPY_OVERLAP:                   return (char*) "MEMORY COPY OVERLAP";
        case CL_IMAGE_FORMAT_MISMATCH:              return (char*) "IMAGE FORMAT MISMATCH";
        case CL_IMAGE_FORMAT_NOT_SUPPORTED:         return (char*) "IMAGE FORMAT NOT SUPPORTED";
        case CL_BUILD_PROGRAM_FAILURE:              return (char*) "PROGRAM BUILD FAILURE";
        case CL_MAP_FAILURE:                        return (char*) "MAP FAILURE";
        case CL_INVALID_VALUE:                      return (char*) "INVALID VALUE";
        case CL_INVALID_DEVICE_TYPE:                return (char*) "INVALID DEVICE TYPE";
        case CL_INVALID_PLATFORM:                   return (char*) "INVALID PLATFORM";
        case CL_INVALID_DEVICE:                     return (char*) "INVALID DEVICE";
        case CL_INVALID_CONTEXT:                    return (char*) "INVALID CONTEXT";
        case CL_INVALID_QUEUE_PROPERTIES:           return (char*) "INVALID QUEUE PROPERTIES";
        case CL_INVALID_COMMAND_QUEUE:              return (char*) "INVALID COMMAND QUEUE";
        case CL_INVALID_HOST_PTR:                   return (char*) "INVALID HOST POINTER";
        case CL_INVALID_MEM_OBJECT:                 return (char*) "INVALID MEMORY OBJECT";
        case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:    return (char*) "INVALID IMAGE FORMAT DESCRIPTOR";
        case CL_INVALID_IMAGE_SIZE:                 return (char*) "INVALID IMAGE SIZE";
        case CL_INVALID_SAMPLER:                    return (char*) "INVALID SAMPLER";
        case CL_INVALID_BINARY:                     return (char*) "INVALID BINARY";
        case CL_INVALID_BUILD_OPTIONS:              return (char*) "INVALID BUILD OPTIONS";
        case CL_INVALID_PROGRAM:                    return (char*) "INVALID PROGRAM";
        case CL_INVALID_PROGRAM_EXECUTABLE:         return (char*) "INVALID PROGRAM EXECUTABLE";
        case CL_INVALID_KERNEL_NAME:                return (char*) "INVALID KERNEL NAME";
        case CL_INVALID_KERNEL_DEFINITION:          return (char*) "INVALID KERNEL DEFINITION";
        case CL_INVALID_KERNEL:                     return (char*) "INVALID KERNEL";
        case CL_INVALID_ARG_INDEX:                  return (char*) "INVALID ARGUMENT INDEX";
        case CL_INVALID_ARG_VALUE:                  return (char*) "INVALID ARGUMENT VALUE";
        case CL_INVALID_ARG_SIZE:                   return (char*) "INVALID ARGUMENT SIZE";
        case CL_INVALID_KERNEL_ARGS:                return (char*) "INVALID KERNEL ARGUMENTS";
        case CL_INVALID_WORK_DIMENSION:             return (char*) "INVALID WORK DIMENSION";
        case CL_INVALID_WORK_GROUP_SIZE:            return (char*) "INVALID WORK GROUP SIZE";
        case CL_INVALID_WORK_ITEM_SIZE:             return (char*) "INVALID WORK ITEM SIZE";
        case CL_INVALID_GLOBAL_OFFSET:              return (char*) "INVALID GLOBAL OFFSET";
        case CL_INVALID_EVENT_WAIT_LIST:            return (char*) "INVALID EVENT WAIT LIST";
        case CL_INVALID_EVENT:                      return (char*) "INVALID EVENT";
        case CL_INVALID_OPERATION:                  return (char*) "INVALID OPERATION";
        case CL_INVALID_GL_OBJECT:                  return (char*) "INVALID OPENGL OBJECT";
        case CL_INVALID_BUFFER_SIZE:                return (char*) "INVALID BUFFER SIZE";
        case CL_INVALID_MIP_LEVEL:                  return (char*) "INVALID MIP-MAP LEVEL";
    }
    return (char*) "UNKNOWN";
}