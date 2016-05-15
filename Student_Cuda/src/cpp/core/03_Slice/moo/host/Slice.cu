#include "Slice.h"

#include <iostream>

#include "Device.h"

using std::cout;
using std::endl;
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void piDevice(float* ptrDevPi, int nbSlice);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Slice::Slice(int n) : nbSlice(n), piRes(0)
    {
    sizeOctetGM = 1 * sizeof(float); // Pi est sur un float

        // MM
    	{
    	// MM (malloc Device)
    	    {
    	    HANDLE_ERROR(cudaMalloc(&ptrDevGM, sizeOctetGM));
    	    }

    	// MM (memset Device)
    	    {
    	    HANDLE_ERROR(cudaMemset(ptrDevGM, 0, sizeOctetGM));
    	    }

    	Device::lastCudaError("Slice MM (end allocation)"); // temp debug
    	}

        // Grid
    	{
    	dg = dim3(16, 2, 1); // disons, a optimiser selon le gpu
    	db = dim3(32, 4, 1); // Contrainte puissance de deux

    	Device::gridHeuristic(dg, db);
    	}

    sizeOctetSM = db.x * db.y * db.z * sizeof(float); // octet
    }

Slice::~Slice()
    {
    //MM (device free)
	{
	HANDLE_ERROR(cudaFree(ptrDevGM));

	Device::lastCudaError("Slice MM (end deallocation)"); // temp debug
	}

    }

void Slice::run()
    {
	Device::lastCudaError("Slice-kernel (before)"); // temp debug
	piDevice<<<dg, db, sizeOctetSM>>>(ptrDevGM, nbSlice); // assynchrone
        Device::lastCudaError("Slice-kernel (after)"); // temp debug

        Device::synchronize(); // Temp, only for printf in  GPU

        // MM (Device -> Host)
    	{
    	HANDLE_ERROR(cudaMemcpy(&piRes, ptrDevGM, sizeOctetGM, cudaMemcpyDeviceToHost)); // barriere synchronisation implicite
    	}
    }

float Slice::result()
    {
    return piRes;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

