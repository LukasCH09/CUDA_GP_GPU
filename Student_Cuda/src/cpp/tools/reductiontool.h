
#include "Indice2D.h"
#include "cudaTools.h"

#pragma once

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

template<typename T>
class ReductionTool
    {
    public:
	__device__ static void reduce(T* tabSM, T* ptrDevResultatGM)
	    {
	    reduceIntraBloc(tabSM);
	    reduceInterBloc(tabSM, ptrDevResultatGM);
	    }

    private:


	__device__ static void reduceIntraBloc(T* tabSM)
	    {
	    const int nSM = Indice2D::nbThreadLocal();
	    int moitie = nSM/2;
	    while (moitie >= 1)
		{
		ecrasement(tabSM, moitie);
		__syncthreads();
		moitie = moitie / 2;
		}
	    }

	__device__ static void ecrasement(T* tabSM, int moitie)
	    {
	    int NB_THREAD_LOCAL = Indice2D::nbThreadBlock();
	    int s = Indice2D::tidBlock();

	    while(s < moitie)
		{
		tabSM[s] = tabSM[s] + tabSM[s + moitie];
		s += NB_THREAD_LOCAL;
		}
	    }

	__device__ static void reduceInterBloc(T* tabSM, T* ptrDevResultatGM)
	    {
	    if(Indice2D::tidBlock() == 0)
		{
		atomicAdd(ptrDevResultatGM, tabSM[0]);
		}
	    }

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

