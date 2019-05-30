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
#include "LBMStudio.h"

CLBMWorld::CLBMWorld() : CSpaceMeshes()
{
	int error=FALSE;	

	ReadPara(error);

	f_out = new double[Nx*Ny*QF];//f_out=Define3DArray(Nx,Ny,QF);	
	f_hlp = new double[Nx*Ny*QF];//f_hlp=Define3DArray(Nx,Ny,QF);
}

CLBMWorld::~CLBMWorld()
{
	delete []f_out;//Delete3DArray(f_out,Nx,Ny);	
	delete []f_hlp;//Delete3DArray(f_hlp,Nx,Ny);
}


//������CLBMWorld�Ĳ���
void  CLBMWorld::ReadPara(int & error)
{
	string	 line;
	istringstream  stream_temp;
	string   fname("ParaLBMWorld.par");
	ifstream infile;
	infile.open(fname.c_str());

	if (infile.fail())
	{
		std::cout << "The file ParaLBMWorld.par does NOT exist!" << std::endl;
		system("pause");
		exit(0);
	}
	

//..information message
	cout<<"\n* Paramters read from file ParaLBMWorld.par. *\n";
//......ParaLBM of the LBM world
	getline(infile, line);
	
	//line 1.1: lattice speed
	getline(infile, line);	
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> cLB;
	cout << setiosflags(ios::fixed) << setprecision(15) << "cLB=" << cLB << "\n";


	//line 1.2: relaxation parameter omega
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> omega;
	cout << setiosflags(ios::fixed) << setprecision(15) << "omega=" << omega << "\n";
	
	//.....close parameter file
	infile.close();
	
	return;
}


double CLBMWorld::GetUx(double *f, double d_loc, double cLB)
{
	//c.....local variables
	double u_x;				
	//c...........x-, velocity components				
	u_x = (f[1] + f[5] + f[8] - (f[3] + f[6] + f[7]));///d_loc;
	return cLB*u_x;	
}

double CLBMWorld::GetUy(double *f, double d_loc, double cLB)
{
	//c.....local variables
	double u_y;
	//c...........y-, velocity components				
	u_y = (f[2] + f[5] + f[6] - (f[4] + f[8] + f[7]));///d_loc;	
	return cLB*u_y;	
}

double CLBMWorld::GetDensity(double *f, int Q)
{
	//c.....local variables
	int  i;
	double d_loc=0;
	
	for(i=0;i<Q;i++)				
	{					
		d_loc += f[i];				
	}
	return d_loc;
}

//..����������ʽ�ķֲ���������֮Ϊ��׼��ʽ��
//..�����֮���Բ���������ʽ������Ϊ��ʽ�Ҳ��������������֣�
//..�����������ų���d_loc���Ŵ󣬴�����һ�������ʱ����������
//..���Բο�Luo��PRE��2000���һƪ�����е����ģ���He X.Y.1997��J.Stat.Phys.�ϵ����¡�
//..���d_loc��1���Ͳ�����̫��������ˡ�
//..�����������������ʱ�򣬱�׼��ʽ��ƽ��ֲ��������Ǳ�����ˡ�
void CLBMWorld::CalcEquilibrium(double *equ, double u_x,double u_y, double d_loc)
{
	double u_n[9];//c.....local variables

	//..����ƽ��ֲ�����ʱ�Ĳ���
	double c1;
	double c2;
	double c3;

	c1 = 3.0 / cLB;		
	c2 = 4.5 / (cLB*cLB); 
	c3 = 1.5 / (cLB*cLB);

	u_n[0] =   u_x * u_x + u_y * u_y;	
	u_n[1] =   u_x;
	u_n[2] =             u_y;
	u_n[3] = - u_x;
	u_n[4] =           - u_y;
	u_n[5] =   u_x + u_y;
	u_n[6] = - u_x + u_y;
	u_n[7] = - u_x - u_y;
	u_n[8] =   u_x - u_y;

	double weight[QF];
	weight[0] = 4.0/9.0;		//weight coefficients	
	weight[1] =	weight[2] =	weight[3] =	weight[4] = 1.0/9.0;
	weight[5] =	weight[6] =	weight[7] = weight[8] = 1.0/36.0;
		
	double su[9];
	int i=0;
	su[0] = - weight[0] * c3 * u_n[0];
	for(i=1; i<9; i++)
	{
		su[i] = weight[i] * (c1*u_n[i] + c2*u_n[i]*u_n[i] - c3*u_n[0]);
	}
	
	for(i=0; i<QF; i++)
	{
		//equ[i] = d_loc * (weight[i] + su[i]);//��׼��ʽ
		equ[i] = weight[i] * d_loc + su[i];    //����ѹ��ʽ��He X.Y.
	}
}



CRealWorld::CRealWorld() :  CSpaceMeshes() 
{
	ReadPara(error); //�������

	u_x = new double[Nx*Ny];
	u_y = new double[Nx*Ny];
	rho = new double[Nx*Ny];
}


CRealWorld::~CRealWorld()
{		
	delete []u_x;
	delete []u_y;
	delete []rho;
}

//���������
void  CRealWorld::ReadPara(int & error)
{
	string	 line;
	istringstream  stream_temp;
	string   fname("ParaRealWorld.par");
	ifstream infile;
	infile.open(fname.c_str());

	if (infile.fail())
	{
		std::cout << "The file ParaRealWorld.par does NOT exist!" << std::endl;
		system("pause");
		exit(0);
	}

//..information message
	cout<<"\n* Paramters read from file ParaRealWorld.par. *\n";	

//..head line 1
	getline(infile, line);
	//.......line 1: fluid density per link//	infile>>density;
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> density;
	cout << setiosflags(ios::fixed) << setprecision(5) << "density=" << density << "\n";
	
	//.......line 2: density redistribution //������ϵ��mu
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> mu;
	cout << setiosflags(ios::fixed) << setprecision(15) << "mu=" << mu << "\n";

	//.....close parameter file
	infile.close();
	return;
}
