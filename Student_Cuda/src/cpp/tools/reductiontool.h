
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

	__device__ static void reduceInterBloc(T* tabSM, T* ptrDevResultatGM)
	    {
	    if(Indice2D::tidBlock() == 0)
		{
		atomicAdd(ptrDevResultatGM, tabSM[0]);
		}
	    }

	__device__ static void reduceIntraBloc(T* tabSM)
	    {
	    const int nSm = Indice2D::nbThreadLocal();
	    int moitie = nSm/2; //moitié
	    while (moitie >= 1)
		{
		ecrasement(tabSM, moitie);
		__syncthreads();
		moitie = moitie / 2;
		}
	    }

	__device__ static void ecrasement(T* tabSM, int moitie)
	    {
	    int s = Indice2D::tidBlock();

	    while(s < moitie)
		{
		tabSM[s] = tabSM[s] + tabSM[s + moitie];
		s += Indice2D::nbThreadBlock();
		}
	    }
    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

