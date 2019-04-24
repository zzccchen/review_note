//============================================================================
// Name        : LBM_FSI_MP.cpp
// Author      : Dongke Sun
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//
#include "LBFlows.h"

int     N_max; //total amount of nodes
double *T_new; //record new temperature at t+1
double *T_old; //record old temperature at t
double  alpha; //dimensional thermal diffusion coefficient
double  alpha_dimless; //dimensionaless thermal diffusion coefficient

double  delta_x;
double  delta_t;

void initialization(int Lx, int Ly, double T_ini)
{
	N_max = Lx* Ly;
	T_new = new double [N_max];
	T_old = new double [N_max];

	for (int i = 0;i < N_max;i++)
	{
		T_old[i] = T_ini;
		T_new[i] = T_ini;
	}
	//setup spatial and time steps, unit:(m), unit:(s)
	delta_x = 0.5;
	delta_t = 0.1;
	//setup thermal diffusivity, unit:(m/s^2)
	alpha   = 0.0005;

	//dimesionless treatment
	//It should satisfy the stability condition of explicit scheme
	//i.e. alpha_dimless < 1.0
	alpha_dimless = alpha/(delta_x * delta_x / delta_t); 
}


void thermal_conductivity(int Lx, int Ly)
{	
	//main 
	for (int i = 0; i < N_max; i++)
	{
		int x = (i) / Ly;
		int y = (i) % Ly;
			   		 
		int x_e = (x + 1) % Lx;
		int x_w = Lx - (Lx - x) % Lx - 1;
		int y_n = (y + 1) % Ly;
		int y_s = Ly - (Ly - y) % Ly - 1;

		int i_e = x_e*Ly + y;
		int i_w = x_w*Ly + y;
		int i_n = x*Ly + y_n;
		int i_s = x*Ly + y_s;

		//if (y != 0 && y != Ly - 1)
		{
			T_new[i] = T_old[i] \
				+ alpha_dimless * (T_old[i_e] - T_old[i]) \
				+ alpha_dimless * (T_old[i_w] - T_old[i]) \
				+ alpha_dimless * (T_old[i_n] - T_old[i]) \
				+ alpha_dimless * (T_old[i_s] - T_old[i]);
		}
	}

	for (int i = 0; i < N_max; i++)
	{
		int x = (i) / Ly;
		int y = (i) % Ly;

		//Left boundary temperature is 100.
		if (y == 0)
		{
			T_new[i] = 100;
		}
		// Right boundary condition: partial T / partial x = 0;		
		else if (y == Ly - 1)
		{
			T_new[x*Ly + y] = T_old[(x)*Ly + y - 1];
		}
	}

	for (int i = 0; i < N_max; i++)
	{
		T_old[i] = T_new[i];
	}
}

void termination()
{
	delete [] T_new;
	delete [] T_old;
}

void write_pltfile(int Lx, int Ly, int frame)
{
	//c.....local variables
	int x, y;
	FILE *out;
	char fn[256];
	sprintf(fn, "./Res2D%05d.plt", frame); //..\\results\\  //
	out = fopen(fn, "wt");
	fprintf(out, "TITLE     = \" Temperature \"\n");
	fprintf(out, "VARIABLES = \"X\", \"Y\", \"T\" ");
	fprintf(out, "\n");
	fprintf(out, "ZONE I=%d , J=%d, F=POINT\n", Lx, Ly);
	
	for (int y = 0; y < Ly; y++)
	{
		for (int x = 0; x < Lx; x++)
		{
			fprintf(out, "%d\t%d\t%g\t", x, y, T_new[x * Ly + y]);
			fprintf(out, "\n");
		}
	}
	fclose(out);
}


int main(int argc, char *argv[])
{
	FILE *out;
	char fn[512], fd[512];
	sprintf(fn, "document.txt"); //
	out = fopen(fn, "wt");
	fprintf(out, "TITLE     = \" document \"\n");
	fclose(out);

	int maxLoops(60000);
	int maxFrame(100);

	int loops(0);
	int frame(0);

	//information
	printf("%20s= %d \n", "maxLoops ", maxLoops);
	printf("%20s= %d \n\n", "maxFrame ", maxFrame);
	printf("Well done! Initialized successfully. ");
	printf("Now, the main loops are starting... \n\n");

	//start write record's titles (before main loops)
	printf("frame\n");
	printf("informations: a,b,c,d,e......\n");

	out = fopen(fn, "a+");
	fprintf(out, "frame\t");
	fprintf(out, "\n");
	fclose(out);
	//end write record's titles (before main loops)
	

	int Lx(30);
	int Ly(50);

	double T_ini(20.0);

	initialization(Lx, Ly, T_ini);
	
	//for(loops=0;TRUE;loops++)
	for (loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			out = fopen(fn, "a+");
			fprintf(out, "%6d\t", frame);
			fprintf(out, "\n");
			fclose(out);	

			sprintf(fd, "t_%05d.plt", loops); //
			out = fopen(fd, "wt");
			for (int i = 0; i < N_max; i++)
			{
				fprintf(out, "%d\t%g\n",i, T_new[i]);
			}

			printf("%6d\n", frame);
			write_pltfile(Lx, Ly, frame++);

			fprintf(out, "\n");
			fclose(out);
		}

		//start the calculation
		{
			//thermal_conductivity_1D();
			thermal_conductivity(Lx, Ly);
		}
		//end the calculation
	}
	termination();
	system("pause");
	return 0;
}
