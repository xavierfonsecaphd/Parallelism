/**
	Testing Kernel. Adds 10 to each element of a given array
*/
__kernel void zeroValues(__global int* values, __global int* ret, int imax) 
{
	// thread index and total
	int idx = get_global_id(0);
	int idtotal = get_global_size(0);
	
	// zero values
	int i; 
	for( i = idx; i < imax; i += idtotal) 
	{
		ret[i] = values[i] + 10 ;
	}

}