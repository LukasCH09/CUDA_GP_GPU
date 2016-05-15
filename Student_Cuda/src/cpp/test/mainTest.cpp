#include <stdlib.h>
#include <iostream>
#include <string>

#include "cppTest+.h"
#include "Device.h"
#include "StringTools.h"
#include "cudaTools.h"

#include "TestVector.h"
#include "TestHello.h"
#include "TestSlice.h"
#include "TestHisto.h"


using std::string;
using std::cout;
using std::endl;

using Test::Suite;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static bool testALL();

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainTest();

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainTest()
    {
    bool isOk = testALL();

    cout << "\nisOK = " << isOk << endl;

    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

bool testALL()
    {
    int deviceId=Device::getDeviceId();

    Suite testSuite;

    testSuite.add(std::auto_ptr < Suite > (new TestHello(deviceId)));
    testSuite.add(std::auto_ptr < Suite > (new TestVector(deviceId)));
    testSuite.add(std::auto_ptr < Suite > (new TestSlice(deviceId)));
    testSuite.add(std::auto_ptr < Suite > (new TestHisto(deviceId)));

    string titre = "deviceId_" + StringTools::toString(deviceId);

    return runTestHtml(titre, testSuite); // Attention: html create in working directory!!
    //return runTestConsole(titre, testSuite);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

