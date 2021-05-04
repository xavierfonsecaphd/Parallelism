#include <iostream>
#include <cmath>
#include <cstring>

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
	if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceIDs" << endl; exit(EXIT_FAILURE);}
	if (typeOfDevice == CL_DEVICE_TYPE_GPU)
		cout << "GPUs:  " << numDevices << "  (OpenCL Enabled)" << endl;
	else if (typeOfDevice == CL_DEVICE_TYPE_CPU)
		cout << "CPUs:  " << numDevices << endl;
	else cout << "The Hardware Type is either CL_DEVICE_TYPE_ACCELERATOR or CL_DEVICE_TYPE_DEFAULT (NON CPU OR GPU). Trying to get specifications either way." << endl;

	// get device IDs
	cl_device_id devices[numDevices];
	clErr = clGetDeviceIDs(platform,typeOfDevice,numDevices,devices,NULL);
	if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceIDs" << endl; exit(EXIT_FAILURE);}

	// get device info
	for (i = 0; i < (signed) numDevices; i++)
	{
	    size_t size;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_NAME,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}
	    char name[size];
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_NAME,size,name,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}

	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_VENDOR,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}
	    char vendor[size];
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_VENDOR,size,vendor,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}

	    clErr = clGetDeviceInfo(devices[i],CL_DRIVER_VERSION,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}
	    char driverVersion[size];
	    clErr = clGetDeviceInfo(devices[i],CL_DRIVER_VERSION,size,driverVersion,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}

	    cl_ulong localMemSize;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_LOCAL_MEM_SIZE,sizeof(cl_ulong),&localMemSize,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}

	    cl_uint maxComputeUnits;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(cl_uint),&maxComputeUnits,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}

	    cl_uint maxWorkItemDimentions;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,sizeof(cl_uint),&maxWorkItemDimentions,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}

	    size_t maxWorkItemSizes[maxWorkItemDimentions];
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_WORK_ITEM_SIZES,sizeof(size_t) * CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
	    						&maxWorkItemSizes,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}

	    size_t threadBlockSize;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_WORK_GROUP_SIZE,sizeof(size_t),&threadBlockSize,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}

	    cl_ulong globalMemSize;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_GLOBAL_MEM_SIZE,sizeof(cl_ulong),&globalMemSize,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}

	    cl_ulong constantBufferSize;
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,sizeof(cl_ulong),&constantBufferSize,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}

	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_PROFILE,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}
	    char deviceProfile[size];
	    clErr = clGetDeviceInfo(devices[i],CL_DEVICE_PROFILE,size,deviceProfile,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetDeviceInfo" << endl; exit(EXIT_FAILURE);}

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
void platformInfo()
{
    cl_uint numPlatforms; cl_int clErr;
    int i;

    clErr = clGetPlatformIDs( 0, NULL, &numPlatforms);
	if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetPlatformIDs" << endl; exit(EXIT_FAILURE);}

	// get platform IDs. this is essencially querying about the host (how many there are)
	cl_platform_id platforms[numPlatforms];
	clErr = clGetPlatformIDs(numPlatforms,platforms,NULL);
	if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetPlatformIDs" << endl; exit(EXIT_FAILURE);}

	// get platform info (Name of operating system and OpenCL version installed in the host)
	for (i = 0; i < (signed) numPlatforms; i++)
	{
	    size_t size;
	    clErr = clGetPlatformInfo(platforms[i],CL_PLATFORM_VENDOR,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetPlatformInfo, device " << i << endl; exit(EXIT_FAILURE);}
	    char vendor[size];	// size is the memory length of the string being stored (ex.: "Apple", size 6) 
	    clErr = clGetPlatformInfo(platforms[i],CL_PLATFORM_VENDOR,size,vendor,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetPlatformInfo, device " << i << endl; exit(EXIT_FAILURE);}
	    
	    clErr = clGetPlatformInfo(platforms[i],CL_PLATFORM_PROFILE,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetPlatformInfo, device " << i << endl; exit(EXIT_FAILURE);}
	    char profile[size];	
	    clErr = clGetPlatformInfo(platforms[i],CL_PLATFORM_PROFILE,size,profile,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetPlatformInfo, device " << i << endl; exit(EXIT_FAILURE);}
	    
	    clErr = clGetPlatformInfo(platforms[i],CL_PLATFORM_VERSION,0,NULL,&size);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetPlatformInfo, device " << i << endl; exit(EXIT_FAILURE);}
	    char clVersion[size];	
	    clErr = clGetPlatformInfo(platforms[i],CL_PLATFORM_VERSION,size,clVersion,NULL);
	    if (clErr != CL_SUCCESS) { cout << "OpenCL related Error, in clGetPlatformInfo, device " << i << endl; exit(EXIT_FAILURE);}

	    cout  << endl << "HOSTs: " << i + 1 << ""  << endl << "\t"<< vendor << "  -  " << profile << "  -  "  << clVersion << endl;

	    // Now I get the different specs from both the CPU and the several GPUs in the current Host
	    deviceInfo(CL_DEVICE_TYPE_CPU, platforms[i]);
	    deviceInfo(CL_DEVICE_TYPE_GPU, platforms[i]);
	}

}


int main(int argc, char *argv[])
{
	
	platformInfo();

    


	return 0;
}