/**
	This is a complete HOWTO, on how to do GPGPU programming with OpenCL. For further information, refer to my personal 
	blog: http://opencl.blogs.ua.sapo.pt/

	Feel free to use my code, as long as you put a reference to where it came from (http://opencl.blogs.ua.sapo.pt/)

	@author Francisco Xavier
    @date   21 Jan 2014
    @email  xavier@informatik.uni-bremen.de
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <cassert>
#include "1-openClUtilities.h"

#ifdef __APPLE__
	#include <OpenCL/opencl.h>
#else
	#include <CL/cl.h>
#endif

using namespace std;

/**
	This method queries the different devices of a Platform (Host), and get the specific hardware attributes of GPUs
	that are OpenCL enabled. In the following web page, it is found the datatypes and specific keywords that can be 
	used to query the device:
	https://www.khronos.org/registry/cl/sdk/1.0/docs/man/xhtml/clGetDeviceInfo.html

	@param	typeOfDevice	either it is CL_DEVICE_TYPE_GPU or CL_DEVICE_TYPE_CPU (depends on which device we want to query)
	@param platform 		Platform ID, to explore the devices
*/
void deviceInfo(cl_device_type typeOfDevice, cl_platform_id platform)
{
	// get number of devices
	cl_uint numDevices;	cl_int clErr;
	int i;
	clErr = clGetDeviceIDs(platform,typeOfDevice,0,NULL,&numDevices);
	if (clErr != CL_SUCCESS) { cout << "clGetDeviceIDs Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	if (typeOfDevice == CL_DEVICE_TYPE_GPU)
		cout << "GPUs:  " << numDevices << "  (OpenCL Enabled)" << endl;
	else if (typeOfDevice == CL_DEVICE_TYPE_CPU)
		cout << "CPUs:  " << numDevices << endl;
	else cout << "The Hardware Type is either CL_DEVICE_TYPE_ACCELERATOR or CL_DEVICE_TYPE_DEFAULT (NON CPU OR GPU). Trying to get specifications either way." << endl;

	// get device IDs
	cl_device_id devices[numDevices];
	clErr = clGetDeviceIDs(platform,typeOfDevice,numDevices,devices,NULL);
	if (clErr != CL_SUCCESS) { cout << "clGetDeviceIDs Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	// get device info
	for (i = 0; i < (signed) numDevices; i++)
	{
	    size_t size;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_NAME,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	    char name[size];
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_NAME,size,name,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_VENDOR,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	    char vendor[size];
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_VENDOR,size,vendor,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	    clErr = clGetDeviceInfo(devices[i],CL_DRIVER_VERSION,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	    char driverVersion[size];
	    clErr = clGetDeviceInfo(devices[i],CL_DRIVER_VERSION,size,driverVersion,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	    cl_ulong localMemSize;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_LOCAL_MEM_SIZE,sizeof(cl_ulong),&localMemSize,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	    cl_uint maxComputeUnits;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(cl_uint),&maxComputeUnits,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	    cl_uint maxWorkItemDimentions;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,sizeof(cl_uint),&maxWorkItemDimentions,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	    size_t maxWorkItemSizes[maxWorkItemDimentions];
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_WORK_ITEM_SIZES,sizeof(size_t) * CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
	    						&maxWorkItemSizes,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	    size_t threadBlockSize;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_WORK_GROUP_SIZE,sizeof(size_t),&threadBlockSize,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	    cl_ulong globalMemSize;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_GLOBAL_MEM_SIZE,sizeof(cl_ulong),&globalMemSize,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	    cl_ulong constantBufferSize;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,sizeof(cl_ulong),&constantBufferSize,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_PROFILE,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	    char deviceProfile[size];
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_PROFILE,size,deviceProfile,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetDeviceInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	    if (typeOfDevice == CL_DEVICE_TYPE_GPU)
	    {
		    cout << "GPU " << i + 1<< " : " << name << " , from  " << vendor << endl;
		    cout << "Specs:" << endl;
		    cout << "\tLocal Memory Size:\t\t" << localMemSize << endl;
		    cout << "\tMax Compute Units:\t\t" << maxComputeUnits << endl;
		    cout << "\tMAX Work Item Dimentions:\t" << maxWorkItemDimentions << "  [ ";
	    	for (int j = 0; j < (signed) maxWorkItemDimentions - 1; j++)
		    	cout << maxWorkItemSizes[j] << " | ";
		    cout << maxWorkItemSizes[maxWorkItemDimentions - 1] << " ]" << endl;
			cout << "\tWork Group Size:\t\t" << threadBlockSize << endl;
			if (globalMemSize > 1073741824)
				cout << "\tGlobal Memory Size:\t\t" << globalMemSize / 1073741824 << " GigaBytes" << endl;
			else if (globalMemSize > 1048576)
				cout << "\tGlobal Memory Size:\t\t" << globalMemSize / 1048576 << " MegaBytes" << endl;
			else if (globalMemSize > 1024)
				cout << "\tGlobal Memory Size:\t\t" << globalMemSize / 1048576 << " KBytes" << endl;
			else cout << "\tGlobal Memory Size:\t\t" << globalMemSize << " Bytes" << endl;
			cout << "\tConstant Buffer Size:\t\t" << constantBufferSize << " Bytes" << endl;
			if (strcmp(deviceProfile, "FULL_PROFILE") == 0)
				cout << "\tDevice Profile:\t\t\t" << "Device Supports FULL OpenCL specification";
			else cout << "\tDevice Profile:\t\t\t" << "Device Supports EMBEDDED OpenCL specification ONLY";
			cout << "\t( OpenCL version: " << driverVersion << " )" << endl;
	    }
	    else
	    	cout << "\t" << name << " , from  " << vendor << endl << endl;
	}

}

/**
	This method queries the different Platforms (Hosts), and then asks for the specs of the CPU and several GPUs 
	the system might have.

*/
void platformInfo(cl_uint numPlatforms, cl_platform_id *platforms)
{
    cl_int clErr;
    int i;

	// get platform info (Name of operating system and OpenCL version installed in the host)
	for (i = 0; i < (signed) numPlatforms; i++)
	{
	    size_t size;
	    clErr = clGetPlatformInfo(platforms[i],CL_PLATFORM_VENDOR,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "clGetPlatformInfo Error  : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	    char vendor[size];	// size is the memory length of the string being stored (ex.: "Apple", size 6) 
	    clErr = clGetPlatformInfo(platforms[i],CL_PLATFORM_VENDOR,size,vendor,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetPlatformInfo Error  : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	    
	    clErr = clGetPlatformInfo(platforms[i],CL_PLATFORM_PROFILE,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "clGetPlatformInfo Error  : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	    char profile[size];	
	    clErr = clGetPlatformInfo(platforms[i],CL_PLATFORM_PROFILE,size,profile,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetPlatformInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	    
	    clErr = clGetPlatformInfo(platforms[i],CL_PLATFORM_VERSION,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "clGetPlatformInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	    char clVersion[size];	
	    clErr = clGetPlatformInfo(platforms[i],CL_PLATFORM_VERSION,size,clVersion,NULL);
	    if (clErr != CL_SUCCESS) { cout << "clGetPlatformInfo Error : " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	    cout  << endl << "HOSTs: " << i + 1 << ""  << endl << "\t"<< vendor << "  -  " << profile << "  -  "  << clVersion << endl;

	    // Now I get the different specs from both the CPU and the several GPUs in the current Host
	    deviceInfo(CL_DEVICE_TYPE_CPU, platforms[i]);
	    deviceInfo(CL_DEVICE_TYPE_GPU, platforms[i]);
	}
}

/**
	To use the GPU/CPU through OpenCL, I need:
	-> A context 		(linked to a device)
	-> A Program 		(I need to create a program to host Kernels, that will be compiled for different devices)
	-> A Kernel			(method runing in the device)
	-> A Command Queue	(to operate a device, either with FIFO or Events)
	-> A Buffer 		(Sized allocation inside the Global Memory of a Device -- Linked to a context and a device)
	-> Write to Buffer 	(passing parameters/arguments into the Global Memory of the Device)
	-> Execute Kernel 	(enqueueing the parallel execution in the GPU/CPU)
	-> Read from buffer (reading the result of the computation of the device back into the HOST program)
	
	This example works with one GPU at least (I don't have hardware to test differently, but should work for every GPU)
*/
int main(int argc, char *argv[])
{
	cl_int clErr;
	cl_uint numPlatforms, numDevices;
	int MAX_SOURCE_SIZE = 8192;
	int numberOfElements = 8192*4096;	// maximum of elements that I can allocate (8192 * 8192 is already 512MB in the GPU)
	int sizeOfEachElement = sizeof(int);

	// creating the data to send to the GPU
	int *vectorA = new int[numberOfElements]; memset(vectorA, 0, numberOfElements * sizeof(int)); 
	int *vectorB = new int[numberOfElements]; memset(vectorB, 0, numberOfElements * sizeof(int));
	for (int i=0; i < numberOfElements; i++) vectorA[i] = i;

	

	// *********************************************************************************************************************
	// *********************** SETTING UP PLATFORM, DEVICES, CONTEXT, KERNEL COMPILATION, COMMAND QUEUE ********************
	// *********************************************************************************************************************

	// Read the Kernel with the parallel function
	char src[MAX_SOURCE_SIZE];			// buffer to read the file
    FILE *ficheiro;
    if ((ficheiro = fopen("zeroValuesKernel.cl","r")) == NULL)	
    	{cout << "Didn't find the Kernel File. Quitting..." << endl; exit(EXIT_FAILURE);}
    size_t srcsize  = fread(src, 1, MAX_SOURCE_SIZE, ficheiro);    fclose(ficheiro);
    const char *sourceptr[]={src};	

	// Getting the platforms, to create a context
	clErr = clGetPlatformIDs( 0, NULL, &numPlatforms);
	if (clErr != CL_SUCCESS) { cout << "clGetPlatformIDs Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	assert (numPlatforms <= 1);	// if numPlatforms is higher than 1, code needs an extra loop cycle for each platform
	
	cl_platform_id platforms[numPlatforms];
	clErr = clGetPlatformIDs(numPlatforms,platforms,NULL);	// get platform IDs
	if (clErr != CL_SUCCESS) { cout << "clGetPlatformIDs Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	platformInfo(numPlatforms, platforms);
	
	// finding the number of GPUs
	clErr = clGetDeviceIDs(platforms[0],CL_DEVICE_TYPE_GPU,0,NULL,&numDevices);
	if (clErr != CL_SUCCESS) { cout << "clGetDeviceIDs Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	cl_device_id devices[numDevices];

	// create context (getting the devices IDs, to create the properties for the context)
	clErr = clGetDeviceIDs(platforms[0],CL_DEVICE_TYPE_GPU,numDevices,&devices[0],NULL);
	if (clErr != CL_SUCCESS) { cout << "clGetDeviceIDs Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	cl_context_properties properties[] = {CL_CONTEXT_PLATFORM,	(cl_context_properties) platforms[0], 0};
	cl_context context = clCreateContext(properties,1,&devices[0],NULL,NULL,&clErr); 
	if (clErr != CL_SUCCESS) { cout << "clCreateContext Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

    // create program from source
	cl_program program = clCreateProgramWithSource(context,1,sourceptr,&srcsize,&clErr);
	if (clErr != CL_SUCCESS) { cout << "clCreateProgramWithSource Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}		

	// compile program Kernel
	clErr = clBuildProgram(program, 1, &devices[0],"",NULL,NULL);
	if (clErr != CL_SUCCESS) 
	{ 
		cout << "clBuildProgram Error: " << checkError(clErr) << ". Log:" << endl; 
		// print build log
		size_t errorsize; 
		clErr = clGetProgramBuildInfo(program,devices[0],CL_PROGRAM_BUILD_LOG,0,NULL,&errorsize);
		if (clErr != CL_SUCCESS) { cout << "clGetProgramBuildInfo Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}		
		char build_log[errorsize];
		clErr = clGetProgramBuildInfo(program,devices[0],CL_PROGRAM_BUILD_LOG,errorsize,build_log,NULL);
		if (clErr != CL_SUCCESS) { cout << "clGetProgramBuildInfo Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}			

		cout << endl << build_log << endl;
		exit(EXIT_FAILURE);	
	}
	// create kernel
	cl_kernel kernel = clCreateKernel(program,"zeroValues",&clErr);
	if (clErr != CL_SUCCESS) { cout << "clCreateKernel Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}	

	// create command queue
    cl_command_queue queue = clCreateCommandQueue(context,devices[0],CL_QUEUE_PROFILING_ENABLE,&clErr);
    if (clErr != CL_SUCCESS) { cout << "clCreateCommandQueue Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}



    // *********************************************************************************************************************
	// ********************************** ALLOCATE SPACE AND SET UP ARGS IN GPU. RUN KERNEL ********************************
	// *********************************************************************************************************************
    
    size_t bufferSize = numberOfElements * sizeOfEachElement;		// creating space for numberOfElements integers (CL_MEM_READ_WRITE)
    cl_mem memoryBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY, bufferSize, NULL, &clErr);
    if (clErr != CL_SUCCESS) { cout << "clCreateBuffer Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
    cl_mem memoryBuffer2 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, bufferSize, NULL, &clErr);
    if (clErr != CL_SUCCESS) { cout << "clCreateBuffer Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	// set kernel arguments
	clErr = clSetKernelArg(kernel,0,sizeof(cl_mem),&memoryBuffer);
	if (clErr != CL_SUCCESS) { cout << "clSetKernelArg Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	clErr = clSetKernelArg(kernel,1,sizeof(cl_mem),&memoryBuffer2);
	if (clErr != CL_SUCCESS) { cout << "clSetKernelArg Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	clErr = clSetKernelArg(kernel,2,sizeof(int),&numberOfElements);
	if (clErr != CL_SUCCESS) { cout << "clSetKernelArg Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	// write vectorA to device buffer
	clErr = clEnqueueWriteBuffer(queue, memoryBuffer, CL_TRUE, 0, bufferSize, (void*) vectorA, 0, NULL, NULL);
	if (clErr != CL_SUCCESS) { cout << "clEnqueueWriteBuffer Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}

	// enqueue kernel
	cl_uint dim = 1;
	size_t offset = 0;
	size_t local_size = 256;
	size_t global_size = 4*7*local_size;
	clErr = clEnqueueNDRangeKernel(queue, kernel, dim, &offset, &global_size, &local_size, 0, NULL, NULL);
	if (clErr != CL_SUCCESS) { cout << "clEnqueueNDRangeKernel Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}



	// *********************************************************************************************************************
	// ************************************** COLLECT RESULTS AND DEALLOCATE MEMORY ****************************************
	// *********************************************************************************************************************

	// reading back the computation of the device
	clErr = clEnqueueReadBuffer(queue, memoryBuffer2, CL_TRUE, 0, bufferSize, (void*) vectorB, 0, NULL, NULL);
	if (clErr != CL_SUCCESS) { cout << "clEnqueueReadBuffer Error: " << checkError(clErr) << endl; exit(EXIT_FAILURE);}
	cout << endl << "Result:  ";
	//for (int i = 0; i < 10; i++) cout << vectorB[i] << "   ";
	 for (int i = 0; i < numberOfElements; i++) cout << vectorB[i] << "   ";	 // in case you want to print everything
	cout << endl;

    
	clErr = clReleaseKernel(kernel);			// release kernel
	clErr = clReleaseProgram(program);			// release program
	clErr = clReleaseMemObject(memoryBuffer);	// release device buffer
    clErr = clReleaseCommandQueue(queue);		// release command queue
    clErr = clReleaseContext(context);			// release context
    
	


	return 0;
}