#pragma once

#include <math.h>
#include "MathTools.h"
#include <iostream>

#include "../../../../../../BilatTools_CPP/src/core/tools/header/namespace_cpu/cudaType_CPU.h"
#include "../../../../../../BilatTools_CPP/src/core/tools/header/namespace_cpu/Calibreur_CPU.h"
#include "../../../../../../BilatTools_CPP/src/core/tools/header/namespace_cpu/ColorTools_CPU.h"
#include "../../../../../../BilatTools_CPP/src/core/tools/header/namespace_cpu/Interval_CPU.h"

using namespace cpu;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	MandelbrotMath(uint n) :
		calibreur(Interval<float>(0, n), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	MandelbrotMath
	// 	calibreur
	// 	IntervalF

	virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, float x, float y)
	    {
	    int z = f(x, y);

	    if(z < n)
		{
		float hue01 = z;
		calibreur.calibrer(hue01);
		ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
		}
	    else
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->w = 0;
		}

	    ptrColor->w = 255; // opaque
	    }

    private:

	int f(float x, float y)
	    {
	    float a = 0;
	    float b = 0;
	    int k = 0;
	    float aCopy;

	    while ((a * a + b * b) <= 4 && k <= n)
		{
		aCopy = a;
		a = (a * a - b * b) + x;
		b = 2 * aCopy * b + y;
		k++;
		}

	return k;
	    }


	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	uint n;

	// Tools
	Calibreur<float> calibreur;

    };
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
