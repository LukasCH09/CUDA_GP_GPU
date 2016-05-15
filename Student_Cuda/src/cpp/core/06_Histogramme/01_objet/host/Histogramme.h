#pragma once

#include "cudaTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Histogramme
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	Histogramme(uchar* tabData, int n);

	virtual ~Histogramme(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	int* run();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int nTabData;
	int nDataRange;

	// Outputs
	int* ptrHisto;

	// Tools
	dim3 dg;
	dim3 db;
	size_t sizeOctetData;
	size_t sizeOctetHisto;
	uchar* tabData;
	uchar* ptrDevTabData;
	int* ptrDevHisto;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
