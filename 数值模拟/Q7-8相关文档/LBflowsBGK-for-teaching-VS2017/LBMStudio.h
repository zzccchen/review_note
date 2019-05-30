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

/******************************************************************
c.....fluid densities
c     a 9-speed lattice is used here, other geometries are possible
c
c     the densities are numbered as follows:
c
c              6   2   5
c                \ | /
c              3 - 0 - 1
c                / | \
c              7   4   8
c
c    the lattice f_outs are numbered as follows:
c
c
c     ^
c     |
c     y
c
c        :    :    :
c  
c   3    *    *    *  ..
c      
c   2    *    *    *  ..
c      
c   1    *    *    *  ..
c                         x ->
c   0    1    2    3 
c
******************************************************************/


#ifndef		LBMSTUDIO_H
#define		LBMSTUDIO_H

//#include<cstdio>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <cstddef>
#include <ctime>
#include <conio.h> 
#include <minmax.h>

#include <iostream> // for the use of 'cout'
#include <fstream>  // file streams
#include <sstream>  // string streams
#include <iomanip>

using namespace std;

const int TRUE	= 1;
const int FALSE	= 0;
const double GRAVITY=9.8;
const double PI=3.1415926535897931;

const int QF=9;

const int isFluid=-1;
const int isInter= 0;
const int isSolid= 1;

extern int error;//.....error flag

void Error(int iter);
void Information();
void ReadPara(int & error,int& iterMax,int &frameMax);

double dist(double x1,double y1,double x2,double y2);//求两点间距离


class CSpaceMeshes
{
public:

	CSpaceMeshes();
	~CSpaceMeshes();
//..计算区域网格规模.
	int Nx;	
	int Ny;
//..计算区域大小.
	double length_x;
	double length_y;
protected:
	void ReadPara(int & error);	
};

//LB world
class CLBMWorld : virtual public CSpaceMeshes
{
public:
	CLBMWorld();
	~CLBMWorld();

protected:
//.....计算密度
	double GetDensity(double *f,int Q);	

//.....计算x,y方向速度
	double GetUx(double *f, double d_loc, double cLB);
	double GetUy(double *f, double d_loc, double cLB);

//.....平衡分布函数
	void CalcEquilibrium(double *equ, double u_x, double u_y, double d_loc);
	
//..三维数组, 表示节点
//..流场计算用到
	double  *f_out;//
	double  *f_hlp;//.....help array for temporare storage of fluid densities

//..relaxation parameter
	double omega;

	double cLB;

//读入参数
	void ReadPara(int & error);

	
};

class CRealWorld : virtual public CSpaceMeshes
{
public:
	CRealWorld();
	~CRealWorld();
	
protected:
	double *u_x;
	double *u_y;
	double *rho;
	
//.....fluid density per link
	double density;
	
//..dynamic viscosity
	double mu;

//..kinematics viscosity
	double nu;	
private:
	void ReadPara(int & error);
};

class CLBFlowBGK : virtual public CRealWorld, virtual public CLBMWorld
{
public:
	CLBFlowBGK();
	~CLBFlowBGK();

	void CalcFlowPara();

	void Initialize();//const CParticles *particles

	void Propagate(); //...迁移
	void Bounceback();//...反弹
	void Interface(); //...界面
	void Relaxation();//...松弛		
	void Boundary();  // Boundary Treatment

	void CheckFlow(int time); 
	void WriteFlow(int frame); 

protected:
	void CalcNeighbor(int &nx,int &ny,int x,int y,int i);

	double delta_x;
	double delta_t;
//..节点类型，流体or固体or界面 et. al.
	int *nFlags;
//..区分不同的固体，同一个固体所占据的网格被赋予同一个数值，该数值就是固体的id
	int *idSolids;
//..velocity at the inlet of the domain
	double u_in; 
//..流场初始速度
	double u_0, v_0;
//..流场区域大小
	int xStart, xEnd;	
	int yStart, yEnd;
	int bdyType;

	void ReadFlowPara();
};




#endif




