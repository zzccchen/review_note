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

double  delta_x;
double  delta_t;

void initialization(int n_max, double T_ini)
{
	N_max = n_max;
	T_new = new double [N_max];
	T_old = new double [N_max];

	for (int i = 0;i < N_max;i++)
	{
		T_old[i] = T_ini;
		T_new[i] = T_ini;
	}
	delta_x = 0.5;
	delta_t = 0.1;
	alpha   = 0.001;

	alpha /= (delta_x * delta_x / delta_t);

}

void thermal_conductivity()
{
	T_new[0] = 100;
	for (int i = 1;i < N_max-1;i++)
	{
		T_new[i] = T_old[i] + alpha * (T_old[i + 1] - 2 * T_old[i] + T_old[i - 1]);
	}
	T_new[N_max - 1] = T_new[N_max - 2];

	for (int i = 0;i < N_max;i++)
	{
		T_old[i] = T_new[i];
	}
	
}

void termination()
{
	delete [] T_new;
	delete [] T_old;
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
	
	initialization(60, 36.8);
	
	//for(loops=0;TRUE;loops++)
	for (loops = 0; loops <= maxLoops; loops++)
	{
		//start recording the results
		if (loops >= 0 && loops % (maxLoops / maxFrame) == 0)
		{
			out = fopen(fn, "a+");
			fprintf(out, "%6d\t", frame++);
			fprintf(out, "\n");
			fclose(out);	

			sprintf(fd, "t_%05d.plt", loops); //
			out = fopen(fd, "wt");
			for (int i = 0;i < N_max;i++)
			{
				fprintf(out, "%d\t%g\n",i,T_new[i]);
			}
			fprintf(out, "\n");
			fclose(out);

		}

		//start the calculation
		{
			thermal_conductivity();
		}
		//end the calculation
	}
	termination();
	system("pause");
	return 0;
}
