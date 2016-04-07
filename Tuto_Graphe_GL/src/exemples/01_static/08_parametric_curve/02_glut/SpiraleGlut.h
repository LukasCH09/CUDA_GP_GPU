#pragma once

#include "SpiraleGraphe.h"
#include "GLUTGraphWindow.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class SpiraleGlut
    {
    public:
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	SpiraleGlut(int w, int h, int px, int py);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~SpiraleGlut();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    private:


	/*--------------------------------------*\
	|*		Attribut		*|
	\*-------------------------------------*/

    private:

	// Tools
	SpiraleGraphe* ptrGraphe;
	GLUTGraphWindow* ptrGLUTGraphWindow;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/