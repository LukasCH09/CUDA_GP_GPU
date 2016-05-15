#include "ReduceTools.h"
#include "cudaTools.h"

#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__global__ void pi(float* ptrDevpi, int nbSlice);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reductionIntraThread(float* ptrDevPi,int n);
static __device__ float aireRectangle(int s);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void pi(float* ptrDevPi, int nbSlice)
    {
    extern __shared__ float tabSM[];
    reductionIntraThread(tabSM, nbSlice); // pas necessaire, just for fun
    __syncthreads();

    CONST INT NB_THREAD_PAR_BLOCK = Indice2D::nbThreadBlock();

    Reducetools reduceTools = new ReduceTools(NB_THREAD_PAR_BLOCK);
    reduceTools.reductionIntraBloc(tabSM);
    reduceTools.reductionIntrerBloc(tabSM, ptrDevPi);
    __syncthreads();

    //work(ptrDevPi);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void reductionIntraThread(float* ptrDevPi, int nbSlice)
    {
    float sumThread = 0;
    const int NB_THREAD = Indice2D::nbThread();
    const int TID_LOCAL = Indice2D::tidLocal();
    const int TID = Indice2D::tid();

    // Debug
    if (TID == 0)
	{
	printf("Coucou from device tid%d", TID); //required   Device::synchronize(); after the call of kernel
	}

    //TODO pattern entrelacement

    int s = TID;
    while (s < nbSlice)
	{
	sumThread += aireRectangle(s);
	s += NB_THREAD;
	}
    ptrDevPi[TID_LOCAL] = sumThread;
    }

__device__ float aireRectangle(int s)
    {
    return 1 / (1 + s * s);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
