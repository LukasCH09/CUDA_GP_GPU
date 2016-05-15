#include "Indice2D.h"
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
__global__ void histogramme(uchar* ptrDevTabData, int nTabData, int* ptrDevHisto);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reductionIntraThread(uchar* ptrDevTabData, int nTabData, int* ptrDevHisto);
static __device__ void reductionInterBloc(int* tabSM, int* ptrDevHisto, int nDataRange);
static __device__ void initTabSM(int* tabSM, int nDataRange);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void histogramme(uchar* ptrDevTabData, int nTabData, int* ptrDevHisto, int nDataRange)
    {
    extern __shared__ int tabSM[];

    //TODO init tabSM
    // initSM -> pattern d'entrelacement
    initTabSM(tabSM, nDataRange);
    reductionIntraThread(ptrDevTabData, nTabData, tabSM);
    __syncthreads();
    reductionInterBloc(tabSM, ptrDevHisto, nDataRange);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void initTabSM(int* tabSM, int nDataRange)
    {
    const int NB_THREAD_LOCAL = Indice2D::nbThreadLocal();
    const int TID_LOCAL = Indice2D::tidLocal();

    int s = TID_LOCAL;

    while (s < nDataRange)
	{
	tabSM[s] = 0;
	s += NB_THREAD_LOCAL;
	}
    }

__device__ void reductionIntraThread(uchar* ptrDevTabData, int nTabData, int* tabSM)
    {
    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();

    // Debug
    if (TID == 0)
	{
	printf("Coucou from device tid %d \n", TID); //required   Device::synchronize(); after the call of kernel
	}

    // pattern entrelacement

    int s = TID;
    while (s < nTabData)
	{
	atomicAdd(&tabSM[ptrDevTabData[s]], 1);

	s += NB_THREAD;
	}
    }

__device__ void reductionInterBloc(int* tabSM, int* ptrDevHisto, int nDataRange)
    {
    int s = Indice2D::tidLocal();
    int NB_THREAD_LOCAL = Indice2D::nbThreadLocal();

    if (s == 0)
	{
	for (int i = 0; i < nDataRange; i++)
	    {
	    atomicAdd(&ptrDevHisto[i], tabSM[i]);
	    }
	}
    }

/*while(s < 256){

 atomicAdd(&ptrDevHisto[tabSM[s]], 1);
 s += 1;
 }
 }*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

