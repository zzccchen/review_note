//============================================================================
// Name        : LBM_FSI_MP.cpp
// Author      : Dongke Sun
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef MK_LBFLOWS_H
#define MK_LBFLOWS_H

///used in codeblocks
#define MK_EXPORT
#define MK_API

///used in VS2017
////#pragma once
//#ifdef __cplusplus
//#define MK_EXPORT extern "C" __declspec (dllexport)
//#else
//#define MK_EXPORT __declspec (dllexport)
//#endif // __cplusplus
//#ifdef __cplusplus
//#define MK_API _declspec(dllexport)
//#else
//#define MK_API  _declspec(dllimport)
//#endif


#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#include <iostream> // for the use of 'cout'
#include <fstream>  // file streams
#include <sstream>  // string streams
#include <iomanip>


#ifndef MK_RAYLEIGHBERNARD
#define MK_RAYLEIGHBERNARD
#endif

////considering the the moving ball inside the fluids
//#ifndef COUPLED_BALL
//#define COUPLED_BALL
//#endif

////considering the rotation of the moving body
//#ifndef WITH_ROTATION
//#define WITH_ROTATION
//#endif

//#ifndef TWODIMENSIONAL
//#define TWODIMENSIONAL
//#endif
//
//#ifndef TWODIM_COUETTE
//#define TWODIM_COUETTE
//#endif

//#ifndef CURVED_CHANNEL
//#define CURVED_CHANNEL
//#endif

//#ifdef CURVED_CHANNEL
//#ifndef SPIRAL_CHANNEL
//#define SPIRAL_CHANNEL
//#endif
//#endif

using namespace std; // permanently use the standard namespace



extern void readParameters(int & maxLoops, int & maxFrame, bool & error);


//#pragma once
MK_EXPORT extern int Panny(int i, int(*call_back)(int a, int b));

MK_EXPORT extern int Panny_call_back(int a, int b);


MK_EXPORT extern void SystemPause();


#endif
