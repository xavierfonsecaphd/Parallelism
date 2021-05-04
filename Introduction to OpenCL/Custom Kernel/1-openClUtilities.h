/**
    This method provides a readable error message, given one OpenCL code error.
	The several types of errors this function expects are bellow.
	
	@author Francisco Xavier
    @date	21 Jan 2014
    @email  xavier@informatik.uni-bremen.de
*/

#ifndef OPENCLUTILITIES_H
#define OPENCLUTILITIES_H

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
char* checkError(cl_uint errorCode);


/**
	Parameter codes are:

    CL_SUCCESS
    CL_DEVICE_NOT_FOUND
    CL_DEVICE_NOT_AVAILABLE
    CL_COMPILER_NOT_AVAILABLE
    CL_MEM_OBJECT_ALLOCATION_FAILURE
    CL_OUT_OF_RESOURCES
    CL_OUT_OF_HOST_MEMORY
    CL_PROFILING_INFO_NOT_AVAILABLE
    CL_MEM_COPY_OVERLAP
    CL_IMAGE_FORMAT_MISMATCH
    CL_IMAGE_FORMAT_NOT_SUPPORTED
    CL_BUILD_PROGRAM_FAILURE
    CL_MAP_FAILURE
    CL_INVALID_VALUE
    CL_INVALID_DEVICE_TYPE
    CL_INVALID_PLATFORM
    CL_INVALID_DEVICE
    CL_INVALID_CONTEXT
    CL_INVALID_QUEUE_PROPERTIES
    CL_INVALID_COMMAND_QUEUE
    CL_INVALID_HOST_PTR
    CL_INVALID_MEM_OBJECT
    CL_INVALID_IMAGE_FORMAT_DESCRIPTOR
    CL_INVALID_IMAGE_SIZE
    CL_INVALID_SAMPLER
    CL_INVALID_BINARY
    CL_INVALID_BUILD_OPTIONS
    CL_INVALID_PROGRAM
    CL_INVALID_PROGRAM_EXECUTABLE
    CL_INVALID_KERNEL_NAME
    CL_INVALID_KERNEL_DEFINITION
    CL_INVALID_KERNEL
    CL_INVALID_ARG_INDEX
    CL_INVALID_ARG_VALUE
    CL_INVALID_ARG_SIZE
    CL_INVALID_KERNEL_ARGS
    CL_INVALID_WORK_DIMENSION
    CL_INVALID_WORK_GROUP_SIZE
    CL_INVALID_WORK_ITEM_SIZE
    CL_INVALID_GLOBAL_OFFSET
    CL_INVALID_EVENT_WAIT_LIST
    CL_INVALID_EVENT
    CL_INVALID_OPERATION
    CL_INVALID_GL_OBJECT
    CL_INVALID_BUFFER_SIZE
    CL_INVALID_MIP_LEVEL

*/

#endif