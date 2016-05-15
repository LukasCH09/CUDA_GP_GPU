#pragma once

#include "cudaTools.h"
#include "curand_kernel.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MonteCarlo
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/**
	 * update w by v1+v2
	 */
	MonteCarlo(float M, int nbFlechettes);

	virtual ~MonteCarlo(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void run();
	float getPI();


	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	float M;
	int nbFlechettes;

	// Outputs
	float pi;

	// Tools
	dim3 dg;
	dim3 db;
	int* ptrDevN0;  // result
	int n0;
	curandState* ptrTabDevGeneratorGM;
	size_t sizeOctetN0;  // compte le nombre de fléchettes en dessous de la courbe
	size_t sizeOctetTabGenerator; // compte le nombre de générateurs
	size_t sizeSM;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
