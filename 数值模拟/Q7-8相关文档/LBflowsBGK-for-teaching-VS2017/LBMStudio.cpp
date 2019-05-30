//========================================================//
//              MRT LBM code                              //
//========================================================//
// Author      : SUN DongKe                               //
// Copyright   : All rights reserved.                     //
// Description : C++, Ansi-style                          //
// Last updated: 2012.10.07 by SUN DongKe                 //
//========================================================//
// SUN DongKe, Ph.D                                       //
// Website     : http://www.calcflows.com                 //
// E-Mail      : sundongke@gmail.com                      //
//========================================================//

#ifndef LBMSTUDIO_CPP 
#define LBMSTUDIO_CPP

#include "LBMStudio.h"

int error;//.....error flag

CSpaceMeshes::CSpaceMeshes()
{	
	ReadPara(error);
}

CSpaceMeshes::~CSpaceMeshes()
{
}


void  CSpaceMeshes::ReadPara(int & error)
{
	string	 line;
	istringstream  stream_temp;
	string   fname("ParaSpaceMeshes.par");
	ifstream infile;
	infile.open(fname.c_str());

	if (infile.fail())
	{
		std::cout << "The file ParaSpaceMeshes.par does NOT exist!" << std::endl;
		system("pause");
		exit(0);
	}	

//..Head line 1: parameters from Real world
	getline(infile, line);
	
	//line 1.1: length_x
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> length_x;
	cout << setiosflags(ios::fixed);
	cout << setprecision(5) << "length_x=" << length_x << "\n";
	
	//line 1.2: length_y
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> length_y;
	cout << setiosflags(ios::fixed);
	cout << setprecision(5) << "length_y=" << length_y << "\n";

//..Head line 2: parameters for the grids
	getline(infile, line);
	
	//line 2.1: Nx
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> Nx;
	cout << setiosflags(ios::fixed);
	cout << setprecision(5) << "Nx=" << Nx << "\n";
	
	//line 2.2:  Ny	
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> Ny;
	cout << setiosflags(ios::fixed);
	cout << setprecision(5) << "Ny=" << Ny << "\n";

	//.....close parameter file
	infile.close();
    return;
}


double dist(double x1,double y1,double x2,double y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void Error(int iter)
{
	cout<<"!!! error: program stop during iteration = "<< iter <<"\n";
	cout << "!!!\n";
}

void Information()
{

cout<<"________________________________\
____________________________________\n\
c.....fluid densities\n\
c     a 9-speed lattice is used here, other geometries are possible\n\
c.....the densities are numbered as follows:";

cout << "\n\
c                          \n\
c              6   2   5   \n\
c                \\ | /    \n\
c              3 - 0 - 1   \n\
c                / | \\    \n\
c              7   4   8   \n\
c \n";

cout << "\
c.....the lattice nodes are numbered as follows:\n\
c			\n\
c   ^		\n\
c   |		\n\
c   y		\n\
c			\n\
c   :    :    :    :		\n\
c							\n\
c   3    *    *    *  ..	\n\
c							\n\
c   2    *    *    *  ..	\n\
c							\n\
c   1    *    *    *  ..	\n\
c                         	\n\
c   0    1    2    3  ..  x ->	\n\
c								\n\
__________________________________\
__________________________________\n";

}


void  ReadPara(int & error,int& iterMax,int &frameMax)
{
	string	 line;
	istringstream  stream_temp;
	string   fname("ParaCtrlOutput.par");
	ifstream infile;
	infile.open(fname.c_str());

	if (infile.fail())
	{
		std::cout << "The file ParaCtrlOutput.par does NOT exist!" << std::endl;
		system("pause");
		exit(0);
	}

	//..Head line 5: control the iteration
	getline(infile, line);

	//line 5.1: number of iterations
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> iterMax;
	cout << setiosflags(ios::fixed) << setprecision(5) << "iterMax=" << iterMax << "\n";
	
	//line 5.2:  frame	
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> frameMax;
	cout << setiosflags(ios::fixed) << setprecision(5) << "frameMax=" << frameMax << "\n";
	
	//.....close parameter file
	infile.close();
	
	//.....information message
	cout << "******************************************************\n";	
	cout << "*** maximum itertation step    iterMax = %-9d ***\n",iterMax;
	cout << "*** maximum number of frames  frameMax = %-9d ***\n",frameMax;
	cout << "******************************************************\n";
	
    return;
}

#endif