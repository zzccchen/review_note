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
#include"LBMStudio.h"

CLBFlowBGK::CLBFlowBGK()// : CSpace(), CRealWorld(), CLBMWorld()
{
	nFlags = new int[Nx*Ny];
	idSolids= new int[Nx*Ny];
	ReadFlowPara();     //读入参数	
	CalcFlowPara();		//计算参数
}

CLBFlowBGK::~CLBFlowBGK()
{		
	delete []nFlags;
	delete []idSolids;
}

void CLBFlowBGK::CalcNeighbor(int &nx, int &ny, int x, int y, int i)
{
	int	ex[QF], ey[QF];

	ex[0]=0; ey[0]=0; 
	ex[1]=1; ex[2]=0; ex[3]=-1; ex[4]= 0;
	ey[1]=0; ey[2]=1; ey[3]= 0; ey[4]=-1;
	ex[5]=1; ex[6]=-1;ex[7]=-1;	ex[8]= 1;
	ey[5]=1; ey[6]= 1;ey[7]=-1;	ey[8]=-1;

	nx=x+ex[i];
	ny=y+ey[i];
	
	if(nx<0) nx=Nx-1;
	if(nx>(Nx-1))	nx=0;
	
	if(ny<0) ny=Ny-1;
	if(ny>(Ny-1))	ny=0;	
}


void CLBFlowBGK::ReadFlowPara()
{	
	string	 line;
	istringstream  stream_temp;
	string   fname("ParaInitialFlow.par");
	ifstream infile;
	infile.open(fname.c_str());

	if (infile.fail())
	{
		std::cout << "The file ParaInitialFlow.par does NOT exist!" << std::endl;
		system("pause");
		exit(0);
	}

//..information message
	cout<<"\n* Paramters read from file ParaInitialFlow.par. *\n";
//..Head line 1: dimensionless ParaLBM
	getline(infile, line);

	//.......line 1.1: density redistribution //	infile>>uxInital;//
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> delta_x;	
	cout << setiosflags(ios::fixed) << setprecision(15) << "delta_x=" << delta_x << "\n";

	//.......line 4: density redistribution //	infile>>uyInital;//
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> delta_t;
	cout << setiosflags(ios::fixed) << setprecision(15) << "delta_t=" << delta_t << "\n";
		
//..Head line 4: dimensionless ParaLBM
	getline(infile, line);

	//.......line 3: density redistribution //	infile>>uxInital;//
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> u_0;
	cout << setiosflags(ios::fixed)<< setprecision(15) << "u_0=" << u_0 << "\n";

	//.......line 4: density redistribution //	infile>>uyInital;//
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> v_0;
	cout << setiosflags(ios::fixed) << setprecision(5) << "v_0=" << v_0 << "\n";

//..Head line 3: boundary condition type selection
	getline(infile, line);

	//.......line 5: boundary condition type selection
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> bdyType;
	cout << setiosflags(ios::fixed) << setprecision(15) << "bdyType=" << bdyType << "\n";

	//.......line 5: fluid density per link	//infile>>u_in;
	getline(infile, line);
	stream_temp.clear();
	stream_temp.str(line);
	stream_temp >> u_in;
	cout << setiosflags(ios::fixed) << setprecision(15) << "u_in=" << u_in <<"\n";
	
	//.....close parameter file
	infile.close();
	return;
}


void CLBFlowBGK::CalcFlowPara()
{	
	nu=mu/density;//动力黏度转换成运动黏度

	double nuLB=(1.0/omega-0.5)/3.0;//LB流体的黏度

	if(delta_x>0)//space step
	{
		length_x = Nx*delta_x;
	}
	else
	{
		delta_x = length_x/Nx;//m_dx=实际长度/格子长度;
	}	

	if(delta_t>0)
	{
		omega=3*nu*delta_t/delta_x/delta_x + 0.5;//9-bit
		omega=1.0/omega;
	}
	else
	{
		delta_t = delta_x*delta_x/(nu/nuLB);//
	}

	u_in /= delta_x/delta_t;

	//..information message
	cout<<"\n* Paramters after Unit Conversion. *\n";
	cout<<"omega="<<omega<<endl;
	cout<<"delta_x="<<delta_x << endl;
	cout<<"delta_t="<<delta_t << endl;
	cout<<"u_in(LB)="<<u_in << endl;

	if(fabs(u_in)>0.1)
	{
		cout<<"!!!Attention, low Mach number limit!!!\n";
		system("pause");
		exit(0);
	}
}

void CLBFlowBGK::Initialize()//const CParticles *particles
{	
	//UpdateFlags(particles);
	int x=0;
	int y=0;
	int i=0;

#pragma omp parallel for private(x,y)
	for(x = 0; x < Nx; x++)
	{	
		for(y = 0; y < Ny; y++)
		{	
			int temp=x*Ny+y;
			nFlags[temp]=isFluid;
			idSolids[temp]=-1;//-1表示流体
			if((x-Nx/2)*(x-Nx/2) + (y-Ny/2)*(y-Ny/2) < Nx*Nx/36)
			{
				nFlags[temp]=isSolid;
				idSolids[temp]=1;//-1表示流体
			}
		}
	}
//..完成界面Flags的赋值
#pragma omp parallel for private(i,x,y)
	for(x=0;x<Nx;x++)
	{
		for(y=0;y<Ny;y++)
		{			
			if(nFlags[x*Ny+y]==isFluid)
			{
				for(i=1;i<9;i++)	
				{
					int nx,ny;
					CalcNeighbor(nx,ny,x,y,i);					

					if(nFlags[nx*Ny+ny]==isSolid)
					{	
						//第id个固体的临位界面节点也被赋值为id
						if(idSolids[nx*Ny+ny]>=0)
						{
							idSolids[x*Ny+y]=idSolids[nx*Ny+ny];
						}
						nFlags[x*Ny+y]=isInter;
						break; 
					}		
				}
			}
		}
	}
	switch(bdyType)
	{
	case 1:
		xStart=1;
		xEnd  =Nx-1;
		yStart=1;
		yEnd =Ny-1;
		break;
	case 2:
		xStart=0;
		xEnd  =Nx;
		yStart=1;
		yEnd =Ny-1;
		break;
	case 3:
		xStart=1;
		xEnd  =Nx-1;
		yStart=1;
		yEnd =Ny-1;
		break;
	default:
		xStart=0;
		xEnd  =Nx;
		yStart=0;
		yEnd =Ny;
		break;
	}

//	u_in*=delta_t/delta_x;
//	u_0 *=delta_t/delta_x;
//	v_0 *=delta_t/delta_x;

	double vel=sqrt(u_0*u_0+v_0*v_0);
	vel = __max(fabs(u_in),vel);

	if(vel>0.1)
	{
		cout<<"!!!Attention, low Mach number limit!!!\n";
		system("pause");
		exit(0);
	}


	for(x = 0; x<Nx; x++)
	{
		for(y = 0; y<Ny; y++)
		{
			int temp = (x*Ny+y)*QF;
			CalcEquilibrium(f_out+temp,u_0,v_0,density);			
			CalcEquilibrium(f_hlp+temp,u_0,v_0,density);	
		} 
	}	

	for(y = 0;y<Ny;y++)
	{
		for(x = 0;x<Nx;x++)
		{	
			int help=x*Ny+y;
			if (nFlags[help]==isFluid)
			{
				int temp=help*QF;
				
				rho[help] = GetDensity(f_hlp+temp,QF);					
				u_x[help] = GetUx(f_hlp+temp,rho[help],density);
				u_y[help] = GetUy(f_hlp+temp,rho[help],density);
			}
			else
			{
				rho[help] = density;
				u_x[help] = 0;
				u_y[help] = 0;
			}
		}
	} 
//.....information message
	cout<<"\n* WELL DONE! Successful in Initializing the Flow Field. *\n\n";
}


void CLBFlowBGK::Propagate()
{
	//c.....local variables
	int  i,x,y,nx,ny;

#pragma omp parallel for private(i,x,y,nx,ny)
	for(x = 0; x<Nx; x++)
	{
		for(y = 0; y<Ny; y++)
		{			
			for(i=0; i<QF; i++)
			{		
				CalcNeighbor(nx,ny,x,y,i);
				int temp1=(x*Ny+y)*QF+i;
				int temp2=(nx*Ny+ny)*QF+i;
				f_hlp[temp2] = f_out[temp1];
			}
		}
	}			
}
void CLBFlowBGK::Bounceback()//适合处理静止不动的固体
{
//c.....local variables
	int  i,x,y;	

	int	inv[QF];

	inv[0]=0; 	inv[1]=3;	inv[2]=4;	inv[3]=1;	inv[4]=2;
				inv[5]=7;	inv[6]=8;	inv[7]=5;	inv[8]=6;
	
	for(x = xStart; x<xEnd; x++)
	{
		for(y = yStart; y<yEnd; y++)
		{
			int help=x*Ny+y;
			int temp=help*QF;
			//..按照非平衡外推法处理流固界面无滑移边界条件
			if(nFlags[help]==isInter)//如果遇到界面
			{					
				for(i=1;i<QF;i++)
				{
					int nx,ny;
					CalcNeighbor(nx,ny,x,y,i);

					int nhelp=nx*Ny+ny;
					int ntemp=nhelp*QF;

					if(nFlags[nhelp]==isSolid)//the neighbor node
					{
						f_out[temp+inv[i]] = f_out[temp+i]; 
					}					
				}
				rho[help] = density;
				u_x[help] = 0;
				u_y[help] = 0;
			}
		}
	}
}

void CLBFlowBGK::Interface()//适合处理静止不动的固体
{
//c.....local variables
	int  i,x,y;	

	double equF[QF];  //流体节点之PDFs
	double equI[QF];  //界面节点之PDFs
	double u_loc,v_loc,d_loc;

	int	inv[QF];

	inv[0]=0; 	inv[1]=3;	inv[2]=4;	inv[3]=1;	inv[4]=2;
				inv[5]=7;	inv[6]=8;	inv[7]=5;	inv[8]=6;
	
	for(x = xStart; x<xEnd; x++)
	{
		for(y = yStart; y<yEnd; y++)
		{
			int help=x*Ny+y;
			int temp=help*QF;
			
			//..按照非平衡外推法处理流固界面无滑移边界条件
			if(nFlags[help]==isInter)//如果遇到界面
			{
				for(i=1;i<QF;i++)
				{
					int nx,ny;
					CalcNeighbor(nx,ny,x,y,i);
					int nhelp=nx*Ny+ny;
					int ntemp=nhelp*QF;
					if(nFlags[nhelp]==isFluid)//the neighbor node
					{
						d_loc=rho[nhelp];
						u_loc=u_x[nhelp];
						v_loc=u_y[nhelp];
						CalcEquilibrium(equF, u_loc, v_loc, d_loc);

						u_loc=0;
						v_loc=0;
						CalcEquilibrium(equI, u_loc, v_loc, d_loc);

						f_out[temp+i] = equI[i] + (f_out[ntemp+i]-equF[i]);
					}					
				}
				rho[help] = density;
				u_x[help] = 0;
				u_y[help] = 0;
			}
		}
	}
}

// Boundary Treatment
void CLBFlowBGK::Boundary()
{
	int x,y,i;
	double equ[QF];
	double equBdy[QF];
	double u_loc,v_loc,d_loc;

	int help,helpBdy,temp,tempBdy;//中间变量
	
	switch(bdyType)
	{
	case 1:
		//下入上出,左右固壁
		for(x = 0; x<Nx; x++)
		{		
			//for the bottom wall;
			y=yStart;
			help=x*Ny+y;
			d_loc=rho[help];					
			u_loc=u_x[help];
			v_loc=u_y[help];
			CalcEquilibrium(equ, u_loc, v_loc, d_loc);

			y = 0; 		
			helpBdy=x*Ny+y;
			d_loc=rho[helpBdy] = rho[help];					
			u_loc=u_x[helpBdy] = 0.00;
			v_loc=u_y[helpBdy] = 0.00;

			CalcEquilibrium(equBdy, u_loc, v_loc, d_loc);

			for(i=0;i<QF;i++)
			{
				temp=help*QF;
				tempBdy=helpBdy*QF;

				f_out[tempBdy+i] = equBdy[i] + (f_out[temp+i]-equ[i]);
			}

			//for the top wall;
			y=Ny-2;
			help=x*Ny+y;
			d_loc=rho[help];					
			u_loc=u_x[help];
			v_loc=u_y[help];
			CalcEquilibrium(equ, u_loc, v_loc, d_loc);

			y=yEnd; 		
			helpBdy=x*Ny+y;
			d_loc=rho[helpBdy] = rho[help];				
			u_loc=u_x[helpBdy] = 0.00;
			v_loc=u_y[helpBdy] = 0.00;

			CalcEquilibrium(equBdy, u_loc, v_loc, d_loc);

			for(i=0;i<QF;i++)
			{
				temp=help*QF;
				tempBdy=helpBdy*QF;

				f_out[tempBdy+i] = equBdy[i] + (f_out[temp+i]-equ[i]);
			}
		}
		for(y = 0; y<Ny; y++)
		{		
			//for the left wall;
			x=xStart;
			help=x*Ny+y;
			d_loc=rho[help];					
			u_loc=u_x[help];
			v_loc=u_y[help];
			CalcEquilibrium(equ, u_loc, v_loc, d_loc);

			x = 0; 		
			helpBdy=x*Ny+y;
			d_loc=rho[helpBdy] = rho[help];					
			u_loc=u_x[helpBdy] = 0.00;
			v_loc=u_y[helpBdy] = 0.00;

			CalcEquilibrium(equBdy, u_loc, v_loc, d_loc);

			for(i=0;i<QF;i++)
			{
				temp=help*QF;
				tempBdy=helpBdy*QF;

				f_out[tempBdy+i] = equBdy[i] + (f_out[temp+i]-equ[i]);
			}

			//for the right wall;
			x=Nx-2;
			help=x*Ny+y;
			d_loc=rho[help];					
			u_loc=u_x[help];
			v_loc=u_y[help];
			CalcEquilibrium(equ, u_loc, v_loc, d_loc);

			x=xEnd; 		
			helpBdy=x*Ny+y;
			d_loc=rho[helpBdy] = rho[help];						
			u_loc=u_x[helpBdy] = 0.00;
			v_loc=u_y[helpBdy] = 0.00;

			CalcEquilibrium(equBdy, u_loc, v_loc, d_loc);

			for(i=0;i<QF;i++)
			{
				temp=help*QF;
				tempBdy=helpBdy*QF;

				f_out[tempBdy+i] = equBdy[i] + (f_out[temp+i]-equ[i]);
			}
		}
		return;
	case 2:
		//下入上出，左右周期
		for(x = 0; x<Nx; x++)
		{		
			//for the bottom wall;
			y=yStart;
			help=x*Ny+y;
			d_loc=rho[help];					
			u_loc=u_x[help];
			v_loc=u_y[help];
			CalcEquilibrium(equ, u_loc, v_loc, d_loc);

			y = 0; 		
			helpBdy=x*Ny+y;
			d_loc=rho[helpBdy] = rho[help];					
			u_loc=u_x[helpBdy] = 0.00;
			v_loc=u_y[helpBdy] = u_in;

			CalcEquilibrium(equBdy, u_loc, v_loc, d_loc);

			for(i=0;i<QF;i++)
			{
				temp=help*QF;
				tempBdy=helpBdy*QF;

				f_out[tempBdy+i] = equBdy[i] + (f_out[temp+i]-equ[i]);
			}

			//for the top wall;
			y=Ny-2;
			help=x*Ny+y;
			d_loc=rho[help];					
			u_loc=u_x[help];
			v_loc=u_y[help];
			CalcEquilibrium(equ, u_loc, v_loc, d_loc);

			y=yEnd; 		
			helpBdy=x*Ny+y;
			d_loc=rho[helpBdy] = density;					
			u_loc=u_x[helpBdy] = u_x[help];
			v_loc=u_y[helpBdy] = u_y[help];;

			CalcEquilibrium(equBdy, u_loc, v_loc, d_loc);

			for(i=0;i<QF;i++)
			{
				temp=help*QF;
				tempBdy=helpBdy*QF;

				f_out[tempBdy+i] = equBdy[i] + (f_out[temp+i]-equ[i]);
			}
		}
		return;
	case 3:
		//下入上出,左右固壁
		for(x = 0; x<Nx; x++)
		{		
			//for the bottom wall;
			y=yStart;
			help=x*Ny+y;
			d_loc=rho[help];					
			u_loc=u_x[help];
			v_loc=u_y[help];
			CalcEquilibrium(equ, u_loc, v_loc, d_loc);

			y = 0; 		
			helpBdy=x*Ny+y;
			d_loc=rho[helpBdy] = rho[help];					
			u_loc=u_x[helpBdy] = 0.00;
			v_loc=u_y[helpBdy] = u_in;

			CalcEquilibrium(equBdy, u_loc, v_loc, d_loc);

			for(i=0;i<QF;i++)
			{
				temp=help*QF;
				tempBdy=helpBdy*QF;

				f_out[tempBdy+i] = equBdy[i] + (f_out[temp+i]-equ[i]);
			}

			//for the top wall;
			y=Ny-2;
			help=x*Ny+y;
			d_loc=rho[help];					
			u_loc=u_x[help];
			v_loc=u_y[help];
			CalcEquilibrium(equ, u_loc, v_loc, d_loc);

			y=yEnd; 		
			helpBdy=x*Ny+y;
			d_loc=rho[helpBdy] = density;					
			u_loc=u_x[helpBdy] = u_x[help];
			v_loc=u_y[helpBdy] = u_y[help];

			CalcEquilibrium(equBdy, u_loc, v_loc, d_loc);

			for(i=0;i<QF;i++)
			{
				temp=help*QF;
				tempBdy=helpBdy*QF;

				f_out[tempBdy+i] = equBdy[i] + (f_out[temp+i]-equ[i]);
			}
		}
		for(y = 0; y<Ny; y++)
		{		
			//for the left wall;
			x=xStart;
			help=x*Ny+y;
			d_loc=rho[help];					
			u_loc=u_x[help];
			v_loc=u_y[help];
			CalcEquilibrium(equ, u_loc, v_loc, d_loc);

			x = 0; 		
			helpBdy=x*Ny+y;
			d_loc=rho[helpBdy] = rho[help];					
			u_loc=u_x[helpBdy] = 0.00;
			v_loc=u_y[helpBdy] = 0.00;

			CalcEquilibrium(equBdy, u_loc, v_loc, d_loc);

			for(i=0;i<QF;i++)
			{
				temp=help*QF;
				tempBdy=helpBdy*QF;

				f_out[tempBdy+i] = equBdy[i] + (f_out[temp+i]-equ[i]);
			}

			//for the right wall;
			x=Nx-2;
			help=x*Ny+y;
			d_loc=rho[help];					
			u_loc=u_x[help];
			v_loc=u_y[help];
			CalcEquilibrium(equ, u_loc, v_loc, d_loc);

			x=xEnd; 		
			helpBdy=x*Ny+y;
			d_loc=rho[helpBdy] = rho[help];						
			u_loc=u_x[helpBdy] = 0.00;
			v_loc=u_y[helpBdy] = 0.00;

			CalcEquilibrium(equBdy, u_loc, v_loc, d_loc);

			for(i=0;i<QF;i++)
			{
				temp=help*QF;
				tempBdy=helpBdy*QF;

				f_out[tempBdy+i] = equBdy[i] + (f_out[temp+i]-equ[i]);
			}
		}
		return;
	default:
		return;
	}	
}


void CLBFlowBGK::Relaxation()
{
	int x,y,i;

	double equ[QF];
	double F_c[QF];

	double u_loc;
	double v_loc;
	double d_loc;
 
	for(x = xStart; x<xEnd; x++)
	{
		for(y = yStart; y<yEnd; y++)
		{
			int help=x*Ny+y;
			if(nFlags[help]==isFluid)//流体节点松弛
			{		
				int temp=help*QF;

				d_loc = rho[help] = GetDensity(f_hlp+temp,QF);					
				u_loc = u_x[help] = GetUx(f_hlp+temp,d_loc,cLB);
				v_loc = u_y[help] = GetUy(f_hlp+temp,d_loc,cLB);

				CalcEquilibrium(equ, u_loc, v_loc, d_loc);
				
				for(i=0;i<QF;i++)
				{			
					F_c[i]=equ[i] - f_hlp[temp+i]; 
					
					f_out[temp+i] = f_hlp[temp+i] + omega*F_c[i];//SRT
				}
			}
		} 
	}		
}

void CLBFlowBGK::CheckFlow(int time)  
{
//c.....local variables

	int  x,y,i;
	double n_sum = 0.0;

	//c.....loop over computational domain	  	
	for(y = 0; y< Ny; y++)
	{
		for(x = 0; x< Nx; x++)
		{
			for(i = 0; i<QF ;i++)
			{
				n_sum = n_sum + f_out[(x*Ny+y)*QF+i];//n_sum = n_sum + f_out[x][y][i];
			}
		}
	}
	n_sum/=Nx*Ny;

	cout << "time=" << time << "\t rho=" << n_sum << "\n\n";

}

void  CLBFlowBGK::WriteFlow(int frame)  
{

	// Create filename
	std::stringstream output_filename;
	std::ofstream     output_file;

	// Set file name
	output_filename.clear();
	output_filename.str("");
	output_filename << "ResFrame_" << frame << ".plt";
	// Open file
	output_file.open(output_filename.str().c_str(), ios::trunc);


	//c.....local variables
	int  x,y;
	int  id,help;
	double  u_loc,v_loc,d_loc;//浓度
	double  veloc;  // 


	output_file << "TITLE     = \" U,V velocity & Pressure \"\n";
	output_file << "VARIABLES = \"X\", \"Y\", \"U\", \"V\", \"VELOC\", \"FLAGS\", \"idSolids\" ";
	output_file << "\n";
	output_file << "ZONE I=" << Nx << ", J=" << Ny << ", F=POINT\n";


	for(y=0; y<Ny; y++)
	{
		for(x=0; x<Nx; x++)
		{
			help=x*Ny+y;
			u_loc = u_x[help];
			v_loc = u_y[help];
			veloc=sqrt(u_loc*u_loc + v_loc*v_loc);

			d_loc = rho[help];
			id=idSolids[help];

			//输出的速度是真实世界的速度，而不是无量纲的
			output_file << x << "\t" << y << "\t" << u_loc << "\t" << v_loc << "\t" << veloc << "\t";
			output_file << nFlags[help] << "\t" << id << endl;
		}
	}
	output_file.close();
}
