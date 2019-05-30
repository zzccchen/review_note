#include "NSflows.h"

/* ----- 1 DIMENSIONAL float MALLOC ----- */
float *m1dfloat(int nl, int nh)
{
	float *v;
	v = (float *)malloc((unsigned)(nh - nl + 1) * sizeof(float));
	if (!v) std::cout << "allocation failure in float 1D matrix ";
	return v - nl;
}

/* ----- 2 DIMENSIONAL float MALLOC ----- */
float **m2dfloat(int nrl, int nrh, int ncl, int nch)
{
	int i;
	float **m;

	m = (float **)malloc((unsigned)(nrh - nrl + 1) * sizeof(float*));
	if (!m) std::cout << "allocation failure in float 2D matrix (1)";
	m -= ncl;

	for (i = nrl; i <= nrh; i++) {
		m[i] = (float *)malloc((unsigned)(nch - ncl + 1) * sizeof(float));
		if (!m[i]) std::cout << "allocation failure in float 2D matrix (2)";
		m[i] -= ncl;
	}
	return m;
}

/* ----- 3 DIMENSIONAL float MALLOC ----- */
float ***m3dfloat(int is, int ie, int js, int je, int ks, int ke)
{
	float ***m;
	int   i, j;

	m = (float ***)malloc((unsigned)(ie - is + 1) * sizeof(float**));
	if (!m) std::cout << "allocation failure in float 3D matrix (*,,)";
	m -= is;

	for (i = is; i <= ie; i++) {
		m[i] = (float **)malloc((unsigned)(je - js + 1) * sizeof(float*));
		if (!m[i]) std::cout << "allocation failure in float 3D matrix (,*,)";
		m[i] -= js;
	}
	for (i = is; i <= ie; i++) {
		for (j = js; j <= je; j++) {
			m[i][j] = (float *)malloc((unsigned)(ke - ks + 1) * sizeof(float));
			if (!m[i][j])
				std::cout << "allocation failure in float 3D matrix (,,*)";
			m[i][j] -= ks;
		}
	}
	return(m);
}

/* ----- 1 DIMENSIONAL double MALLOC ----- */
double *m1ddouble(int nl, int nh)
{
	double *v;
	v = (double *)malloc((unsigned)(nh - nl + 1) * sizeof(double));
	if (!v) std::cout << "allocation failure in double 1D matrix ";
	return v - nl;
}

/* ----- 2 DIMENSIONAL double MALLOC ----- */
double **m2ddouble(int nrl, int nrh, int ncl, int nch)
{
	int i;
	double **m;

	m = (double **)malloc((unsigned)(nrh - nrl + 1) * sizeof(double*));
	if (!m) std::cout << "allocation failure in double 2D matrix (1)";
	m -= ncl;

	for (i = nrl; i <= nrh; i++) {
		m[i] = (double *)malloc((unsigned)(nch - ncl + 1) * sizeof(double));
		if (!m[i]) std::cout << "allocation failure in double 2D matrix (2)";
		m[i] -= ncl;
	}
	return m;
}

/* ----- 3 DIMENSIONAL double MALLOC ----- */
double ***m3ddouble(int is, int ie, int js, int je, int ks, int ke)
{
	double ***m;
	int   i, j;

	m = (double ***)malloc((unsigned)(ie - is + 1) * sizeof(double**));
	if (!m) std::cout << "allocation failure in double 3D matrix (*,,)";
	m -= is;

	for (i = is; i <= ie; i++) {
		m[i] = (double **)malloc((unsigned)(je - js + 1) * sizeof(double*));
		if (!m[i]) std::cout << "allocation failure in double 3D matrix (,*,)";
		m[i] -= js;
	}
	for (i = is; i <= ie; i++) {
		for (j = js; j <= je; j++) {
			m[i][j] = (double *)malloc((unsigned)(ke - ks + 1) * sizeof(double));
			if (!m[i][j])
				std::cout << "allocation failure in double 3D matrix (,,*)";
			m[i][j] -= ks;
		}
	}
	return(m);
}

/* ----- 1 DIMENSIONAL int MALLOC ----- */
int   *m1dint(int nl, int nh)
{
	int *v;
	v = (int *)malloc((unsigned)(nh - nl + 1) * sizeof(int));
	if (!v) std::cout << "allocation failure in int 1D matrix ";
	return v - nl;
}

/* ----- 2 DIMENSIONAL int MALLOC ----- */
int   **m2dint(int nrl, int nrh, int ncl, int nch)
{
	int i;
	int **m;

	m = (int **)malloc((unsigned)(nrh - nrl + 1) * sizeof(int*));
	if (!m) std::cout << "allocation failure in int 2D matrix (1)";
	m -= ncl;

	for (i = nrl; i <= nrh; i++) {
		m[i] = (int *)malloc((unsigned)(nch - ncl + 1) * sizeof(int));
		if (!m[i]) std::cout << "allocation failure in int 2D matrix (2)";
		m[i] -= ncl;
	}
	return m;
}

/* ----- 2 DIMENSIONAL char MALLOC ----- */
char  **m2dchar(int nrl, int nrh, int ncl, int nch)
{
	int  i;
	char **m;

	m = (char **)malloc((unsigned)(nrh - nrl + 1) * sizeof(char*));
	if (!m) std::cout << "allocation failure in char 2D matrix (1)";
	m -= ncl;

	for (i = nrl; i <= nrh; i++) {
		m[i] = (char *)malloc((unsigned)(nch - ncl + 1) * sizeof(char));
		if (!m[i]) std::cout << "allocation failure in char 2D matrix (2)";
		m[i] -= ncl;
	}
	return m;
}

/* ----- 3 DIMENSIONAL int MALLOC ----- */
int   ***m3dint(int is, int ie, int js, int je, int ks, int ke)
{
	int ***m;
	int   i, j;

	m = (int ***)malloc((unsigned)(ie - is + 1) * sizeof(int**));
	if (!m) std::cout << "allocation failure in int 3D matrix (*,,)";
	m -= is;

	for (i = is; i <= ie; i++) {
		m[i] = (int **)malloc((unsigned)(je - js + 1) * sizeof(int*));
		if (!m[i]) std::cout << "allocation failure in int 3D matrix (,*,)";
		m[i] -= js;
	}
	for (i = is; i <= ie; i++) {
		for (j = js; j <= je; j++) {
			m[i][j] = (int *)malloc((unsigned)(ke - ks + 1) * sizeof(int));
			if (!m[i][j]) std::cout << "allocation failure in int 3D matrix (,,*)";
			m[i][j] -= ks;
		}
	}
	return(m);
}

/* ----- 1 DIMENSIONAL float MALLOC FREE ----- */
void free_m1dfloat(float *v, int nl, int nh)
{
	free((char *)(v + nl));
}

/* ----- 2 DIMENSIONAL float MALLOC FREE ----- */
void free_m2dfloat(float **m, int nrl, int nrh, int ncl, int nch)
{
	int i;

	for (i = nrh; i >= nrl; i--) free((char*)(m[i] + ncl));
	free((char*)(m + nrl));
}

/* ----- 3 DIMENSIONAL float MALLOC FREE ----- */
void free_m3dfloat(float ***m, int is, int ie, int js, int je, int ks, int ke)
{
	int i, j;

	for (i = ie; i >= is; i--) {
		for (j = je; j > js; j--) {
			free((char*)(m[i][j] + ks));
		}
	}
	for (i = ie; i >= is; i--) free((char*)(m[i] + js));
	free((char*)(m + is));
}

/* ----- 1 DIMENSIONAL double MALLOC FREE ----- */
void free_m1ddouble(double *v, int nl, int nh)
{
	free((char *)(v + nl));
}

/* ----- 2 DIMENSIONAL double MALLOC FREE ----- */
void free_m2ddouble(double **m, int nrl, int nrh, int ncl, int nch)
{
	int i;

	for (i = nrh; i >= nrl; i--) free((char*)(m[i] + ncl));
	free((char*)(m + nrl));
}

/* ----- 3 DIMENSIONAL double MALLOC FREE ----- */
void free_m3ddouble(double ***m, int is, int ie, int js, int je, int ks, int ke)
{
	int i, j;

	for (i = ie; i >= is; i--) {
		for (j = je; j > js; j--) {
			free((char*)(m[i][j] + ks));
		}
	}
	for (i = ie; i >= is; i--) free((char*)(m[i] + js));
	free((char*)(m + is));
}

/* ----- 1 DIMENSIONAL int MALLOC FREE ----- */
void free_m1dint(int *v, int nl, int nh)
{
	free((char *)(v + nl));
}

/* ----- 2 DIMENSIONAL int MALLOC FREE ----- */
void free_m2dint(int **m, int nrl, int nrh, int ncl, int nch)
{
	int i;

	for (i = nrh; i >= nrl; i--) free((char*)(m[i] + ncl));
	free((char*)(m + nrl));
}

/* ----- 3 DIMENSIONAL int MALLOC FREE ----- */
void free_m3dint(int ***m, int is, int ie, int js, int je, int ks, int ke)
{
	int i, j;

	for (i = ie; i >= is; i--) {
		for (j = je; j > js; j--) {
			free((char*)(m[i][j] + ks));
		}
	}
	for (i = ie; i >= is; i--) free((char*)(m[i] + js));
	free((char*)(m + is));
}

/* ----- 1 DIMENSIONAL char MALLOC FREE ----- */
void free_m1dchar(char *v, int nl, int nh)
{
	free((char *)(v + nl));
}

/* ----- 2 DIMENSIONAL char MALLOC FREE ----- */
void free_m2dchar(char **m, int nrl, int nrh, int ncl, int nch)
{
	int i;

	for (i = nrh; i >= nrl; i--) free((char*)(m[i] + ncl));
	free((char*)(m + nrl));
}

/* ----- 3 DIMENSIONAL char MALLOC FREE ----- */
void free_m3dchar(char ***m, int is, int ie, int js, int je, int ks, int ke)
{
	int i, j;

	for (i = ie; i >= is; i--) {
		for (j = je; j > js; j--) {
			free((char*)(m[i][j] + ks));
		}
	}
	for (i = ie; i >= is; i--) free((char*)(m[i] + js));
	free((char*)(m + is));
}



void mem_alloc_solid()
{
	fs = m2ddouble(0, Nxp1, 0, Nyp1);
}

void mem_free_solid()
{
	free_m2ddouble(fs, 0, Nxp1, 0, Nyp1);
}

void grid_generation()
{
	Ngx = 20;
	Ngy = 20;
	ncx = 10;
	ncy = 10;
	ye = 0.8e-4;
	xe = 0.8e-4;
	dcx = 0.4e-6;
	dcy = 0.4e-6;
	tnx = Ngx * ncx + 1;			// total cell number of x axis
	tny = Ngy * ncy + 1;			// total cell number of y axis
	tnxy = tnx * tny;
	hncx = ncx / 2;				// half of ncx 
	hncy = ncy / 2;				// half of ncy

	dtmax = dcx * dcy / 3.0e-9;	// stability codition of the explicit FDM for solutal diffusion

	Vc = dcx * dcy;			// cell volume
	Acx = dcy;				// cell boundary area normal to x axis
	Acy = dcx;				//

	nlayer = 1;
	BB = 1. + 2.*nlayer;
	AA = BB * nlayer;
	CC = BB * BB;
	BCn = nlayer * nlayer;
	BCx = CC - BCn;

	scxi = hncx + 1;			// starting grid index on x direction
	ecxi = tnx + hncx;			// ending grid index on x direction
	scyi = hncy + 1;			// starting grid index on y direction
	ecyi = tny + hncy;			// ending grid index on y direction
	Nxp1 = tnx + 2 * hncx + 2;		// total mesh number of x axis
	Nyp1 = tny + 2 * hncy + 2;		// total mesh number of y axis
}

void init_fields()
{
	int ii, jj, ns;

	ns = 0;

	ii = hncx + ncx * Ngx / 2 + 1;	// i index of the center cell
	jj = hncy + ncy * Ngy / 2 + 1;    // j index of the center cell

	for (i = 1;i < Nxp1;i++)
	{
		for (j = 1;j < Nyp1;j++)
		{
			fs[i][j] = 0.0;
		}
	}

	for (int ilayer = -10; ilayer < 10; ilayer++)
	{
		for (int jlayer = -10; jlayer < 10; jlayer++)
		{
			fs[ii + ilayer][jj + jlayer] = 1.;
		}
	}
}



int main(int argc, char ** argv)
{
	double xmonin, arden;

	double sorce;

	int i;
	int	j;
	int niter;

	grid_generation();
	mem_alloc_solid(); //Memoy Allocation
	mem_alloc_flow();  //Memoy Allocation
	init_fields();
	init_velocity();
	set_grid();
	init_geo();
	init_output();

	///Initial Condition
	for (j = scyi; j <= ecyi; j++)
	{
		u[scxi][j] = ubulk;
	}

	for (i = scxi + 1; i <= ecxi; i++)
	{
		for (j = scyi; j <= ecyi; j++)
		{
			if (fs[i][j] >= SolPhi)
			{
				u[i][j] = u[i + 1][j] = 0.0;
			}
			u[i][j] = ubulk;
		}
	}
	for (i = scxi + 1; i <= ecxi; i++)
	{
		for (j = scyi; j <= ecyi; j++)
		{
			v[i][j] = 0.0;
		}
	}

	for (i = 0; i <= Nxp1; i++)
	{
		for (j = 0; j <= Nyp1; j++)
		{
			uold[i][j] = u[i][j];
			vold[i][j] = v[i][j];
		}
	}

	///CALCULATE RESIDUAL SOURCES NORMALIZATION FACTORS
	flowin = 0.0;
	xmonin = 0.0;
	for (j = scyi; j <= ecyi; j++)
	{
		arden = densit * sns[j];
		flowin = flowin + arden * u[scxi][j];
		xmonin = xmonin + arden * u[scxi][j] * u[scxi][j];
	}

	if (ubulk == 0.)
	{
		for (i = scxi; i <= ecxi; i++)
		{
			for (j = scyi; j <= ecyi; j++)
			{
				arden = densit * sns[j];
			}
		}
	}

	///Transient Prob.
	time_f = 0.0;

	///ITERATION LOOP 
	cycles_perframe = 100;
	dt = dtmax / 5.0;

	for (ncycle = 0; ncycle < 5000; ncycle++)
	{
		if (ncycle%cycles_perframe == 0)
		{
			file_prn(m);
			m++;
		}

		time_f += dt;
		for (niter = 1; niter <= maxit; niter++)
		{
			if (fabs(ubulk) > 0.)
			{
				calc_u();
				calc_v();
				calc_p();
			}

			if (niter % 10 == 0)
			{
				std::cout << "TIME("<< time_f<<"): "<< niter<<"\t"<< u_resor <<"\t"<< v_resor <<"\t"<< m_resor<< "\n";
			}
			u_resor /= xmonin;
			v_resor /= xmonin;
			m_resor /= flowin;

			sorce = m_resor;  /// TERMINATION CRITATION

			if (sorce < sormax)
			{
				break;
			}
			else
			{
				if (niter < 10)
				{
					continue;
				}
			}

			if (sorce > 1.0e50*sormax || niter == maxit)
			{
				std::cout << " **** SOLUTION DIVERGES OR NEEDS MORE ITERATIONS ****\n\n\n";
				system("pause");
				exit(EXIT_FAILURE);
			}

		}
		update_velocity();
	}
	/// End of Iteration at time step t 

	mem_free_solid(); 	//Memoy Allocation

	mem_free_flow();
	std::cout<<"\n\n";
	std::cout<<" **** SOLUTION SUCCESSFULLY CONVERGED ****\n\n\n";

	///FINAL OPERATIONS AND OUTPUT 
	std::cout << "* PROGRAM IS SUCCESSFULLY FINISHED ......\n\n\a\a";
	return 0;
}


void mem_alloc_flow(void)
{
	std::cout << "\n* MEMORY ALLOCATION 1D, 2D, 3D ------------\n\n";

	/* FOR GEOMETRY */
	x = m1ddouble(0, Nxp1);
	y = m1ddouble(0, Nyp1);
	dxep = m1ddouble(0, Nxp1);
	dxpw = m1ddouble(0, Nxp1);
	dynp = m1ddouble(0, Nyp1);
	dyps = m1ddouble(0, Nyp1);
	sns = m1ddouble(0, Nyp1);
	sew = m1ddouble(0, Nxp1);
	xu = m1ddouble(0, Nxp1);
	yv = m1ddouble(0, Nyp1);

	/* FOR U-VELOCITY */
	dxepu = m1ddouble(0, Nxp1);
	dxpwu = m1ddouble(0, Nxp1);
	sewu = m1ddouble(0, Nxp1);

	/* FOR V-VELOCITY */
	dynpv = m1ddouble(0, Nyp1);
	dypsv = m1ddouble(0, Nyp1);
	snsv = m1ddouble(0, Nyp1);

	/* FOR P-CORRECTNESS */
	du = m2ddouble(0, Nxp1, 0, Nyp1);
	dv = m2ddouble(0, Nxp1, 0, Nyp1);

	/* FOR VARIABLE */
	u = m2ddouble(0, Nxp1, 0, Nyp1);
	v = m2ddouble(0, Nxp1, 0, Nyp1);
	p = m2ddouble(0, Nxp1, 0, Nyp1);
	pp = m2ddouble(0, Nxp1, 0, Nyp1);

	/* FOR A-FORMAT COEFFICIENT */
	ap = m2ddouble(0, Nxp1, 0, Nyp1);
	an = m2ddouble(0, Nxp1, 0, Nyp1);
	as = m2ddouble(0, Nxp1, 0, Nyp1);
	ae = m2ddouble(0, Nxp1, 0, Nyp1);
	aw = m2ddouble(0, Nxp1, 0, Nyp1);
	su = m2ddouble(0, Nxp1, 0, Nyp1);
	sp = m2ddouble(0, Nxp1, 0, Nyp1);

	/* FOR TRANSIENT */
	uold = m2ddouble(0, Nxp1, 0, Nyp1);
	vold = m2ddouble(0, Nxp1, 0, Nyp1);

	// FOR FILE PRINT
	xprn = m1ddouble(0, Nxp1);
	yprn = m1ddouble(0, Nyp1);
	uprn = m2ddouble(0, Nxp1, 0, Nyp1);
	vprn = m2ddouble(0, Nxp1, 0, Nyp1);
	pprn = m2ddouble(0, Nxp1, 0, Nyp1);
	cprn = m2ddouble(0, Nxp1, 0, Nyp1);

	std::cout << "\n* MEMORY ALLOCATION 1D, 2D, 3D FINISHED \n\n";
}


void mem_free_flow() {
	free_m1ddouble(x, 0, Nxp1);
	free_m1ddouble(y, 0, Nyp1);
	free_m1ddouble(dxep, 0, Nxp1);
	free_m1ddouble(dxpw, 0, Nxp1);
	free_m1ddouble(dynp, 0, Nyp1);
	free_m1ddouble(dyps, 0, Nyp1);
	free_m1ddouble(sns, 0, Nyp1);
	free_m1ddouble(sew, 0, Nxp1);
	free_m1ddouble(xu, 0, Nxp1);
	free_m1ddouble(yv, 0, Nyp1);

	/* FOR U-VELOCITY */
	free_m1ddouble(dxepu, 0, Nxp1);
	free_m1ddouble(dxpwu, 0, Nxp1);
	free_m1ddouble(sewu, 0, Nxp1);

	/* FOR V-VELOCITY */
	free_m1ddouble(dynpv, 0, Nyp1);
	free_m1ddouble(dypsv, 0, Nyp1);
	free_m1ddouble(snsv, 0, Nyp1);

	/* FOR P-CORRECTNESS */
	free_m2ddouble(du, 0, Nxp1, 0, Nyp1);
	free_m2ddouble(dv, 0, Nxp1, 0, Nyp1);

	/* FOR VARIABLE */
	free_m2ddouble(u, 0, Nxp1, 0, Nyp1);
	free_m2ddouble(v, 0, Nxp1, 0, Nyp1);
	free_m2ddouble(p, 0, Nxp1, 0, Nyp1);
	free_m2ddouble(pp, 0, Nxp1, 0, Nyp1);

	/* FOR A-FORMAT COEFFICIENT */
	free_m2ddouble(ap, 0, Nxp1, 0, Nyp1);
	free_m2ddouble(an, 0, Nxp1, 0, Nyp1);
	free_m2ddouble(as, 0, Nxp1, 0, Nyp1);
	free_m2ddouble(ae, 0, Nxp1, 0, Nyp1);
	free_m2ddouble(aw, 0, Nxp1, 0, Nyp1);
	free_m2ddouble(su, 0, Nxp1, 0, Nyp1);
	free_m2ddouble(sp, 0, Nxp1, 0, Nyp1);
	free_m2ddouble(uold, 0, Nxp1, 0, Nyp1);
	free_m2ddouble(vold, 0, Nxp1, 0, Nyp1);

	// FOR FILE PRINT
	free_m1ddouble(xprn, 0, Nxp1);
	free_m1ddouble(yprn, 0, Nxp1);

}

void init_velocity(void)
{
	/* PARAMETERS AND CONTROL INDICES */
	nswpu = 1;
	nswpv = 1;
	nswpp = 1;
	nswpc = 1;


	/* FLUID PROPERTIES */
	densit = 2.475E3;
	viscos = 0.00014;

	/* BOUNDARY VALUES */
	ubulk = 0.03;
	ymax = 1.0;
	xmax = 5.0;

	/* PRESSURE CALCULATION */
	ipref = 2;
	jpref = 2;

	/* PROGRAM CONTROL AND MONITOR */
	imon = scxi + 3;
	jmon = scyi + 3;
	urfu = 0.5;
	urfv = 0.5;
	urfp = 0.8;

}


void set_grid(void)
{
	int     i, j;
	double  dx, dy;

	/* X-DIRECTION MESH DEFINITION */
	dx = dcx;
	x[scxi - 1] = -0.5*dx;
	x[scxi] = -x[scxi - 1];
	for (i = scxi + 1; i <= ecxi + 1; i++)
	{
		x[i] = x[i - 1] + dx;
	}

	/* Y-DIRECTION MESH DEFINITION */
	dy = dcy;
	y[scyi - 1] = -0.5*dy;
	y[scyi] = -y[scyi - 1];
	for (j = scyi + 1; j <= ecyi + 1; j++)
	{
		y[j] = y[j - 1] + dy;
	}
}


void init_geo(void)
{
	int     i, j;

	/* CALCULATE GEOMETRICAL QUANTITIES */
	dxpw[scxi - 1] = 0.0;
	dxep[ecxi + 1] = 0.0;

	for (i = scxi - 1; i <= ecxi; i++)
	{
		dxep[i] = x[i + 1] - x[i];
		dxpw[i + 1] = dxep[i];
	}

	dyps[scyi - 1] = 0.0;
	dynp[ecyi + 1] = 0.0;
	for (j = scyi - 1; j <= ecyi; j++)
	{
		dynp[j] = y[j + 1] - y[j];
		dyps[j + 1] = dynp[j];
	}

	sew[scxi - 1] = 0.0;
	sew[ecxi + 1] = 0.0;
	for (i = scxi; i <= ecxi; i++)
		sew[i] = 0.5 * (dxep[i] + dxpw[i]);

	sns[scyi - 1] = 0.0;
	sns[ecyi + 1] = 0.0;
	for (j = scyi; j <= ecyi; j++)
		sns[j] = 0.5 * (dynp[j] + dyps[j]);

	xu[scxi - 1] = 0.0;
	for (i = scxi; i <= ecxi + 1; i++)
		xu[i] = 0.5 * (x[i] + x[i - 1]);

	dxpwu[scxi - 1] = 0.0;
	dxpwu[scxi] = 0.0;
	dxepu[scxi - 1] = 0.0;
	dxepu[ecxi + 1] = 0.0;
	for (i = scxi; i <= ecxi; i++)
	{
		dxepu[i] = xu[i + 1] - xu[i];
		dxpwu[i + 1] = dxepu[i];
	}

	sewu[scxi - 1] = 0.0;
	for (i = scxi; i <= ecxi + 1; i++)
		sewu[i] = x[i] - x[i - 1];

	yv[scyi - 1] = 0.0;
	for (j = scyi; j <= ecyi + 1; j++)
		yv[j] = 0.5 * (y[j] + y[j - 1]);

	dypsv[scyi - 1] = 0.0;
	dypsv[scyi] = 0.0;
	dynpv[scyi - 1] = 0.0;
	dynpv[ecyi + 1] = 0.0;
	for (j = scyi; j <= ecyi; j++)
	{
		dynpv[j] = yv[j + 1] - yv[j];
		dypsv[j + 1] = dynpv[j];
	}

	snsv[scyi - 1] = 0.0;
	for (j = scyi; j <= ecyi + 1; j++)
		snsv[j] = y[j] - y[j - 1];

	for (i = 0; i <= Nxp1; i++)
	{
		for (j = 0; j <= Nyp1; j++)
		{
			u[i][j] = 0.0;
			v[i][j] = 0.0;
			p[i][j] = 0.0;
			pp[i][j] = 0.0;
			su[i][j] = 0.0;
			sp[i][j] = 0.0;
			du[i][j] = 0.0;
			dv[i][j] = 0.0;
		}
	}
}

void init_output(void)
{
	double re;

	std::cout << "***** LAMINAR FLOW IN A LID DRIVEN CAVITY *****\n\n";
	std::cout << "* VELOCITY AT INLET         =   "<< ubulk <<"\n\n";

	re = ubulk * densit*ymax / viscos;

	std::cout << "* REYNOLDS NUMBER           =   "<< re  <<"\n\n";
	std::cout << "* FLUID DENSITY             =   "<< densit <<"\n\n";
	std::cout << "* LAMINAR VISCOCITY         =   "<< viscos <<"\n\n";

	std::cout << "* ITER  ABSOLUTE RESIDUAL SOURCE SUM  FIELD VALUE AT LOCATION ("<< imon<<", "<< jmon <<")\n";
	std::cout << "   NO.   UMON      VMON        MASS            U          V          P\n";
}


void calc_u(void)
{
	int     i, j, n;
	double  gn, gnw, gs, gsw, ge, gp, gw, cn, cs,
		ce, cw, dn, ds, de, dw, resor;
	double  arden, ardent, flow, uinc;
	double  apo = 0.0;

	/* --- For Transient Prob.(Boundary Condition) --- */
	for (i = scxi - 1; i <= ecxi + 1; i++)
	{
		for (j = scyi - 1; j <= ecyi + 1; j++)
		{
			an[i][j] = as[i][j] = ae[i][j] = aw[i][j] = ap[i][j] = 0.0;
			su[i][j] = sp[i][j] = 0.0;
		}
	}

	/*********** ASSEMBLY OF COEFFICIENT ***********/
	for (i = scxi + 1; i <= ecxi; i++)
	{
		for (j = scyi; j <= ecyi; j++)
		{

			/* CALCULATE CONVECTION COEFFICIENTS */
			gn = densit * v[i][j + 1];
			gnw = densit * v[i - 1][j + 1];
			gs = densit * v[i][j];
			gsw = densit * v[i - 1][j];

			ge = densit * u[i + 1][j];
			gp = densit * u[i][j];
			gw = densit * u[i - 1][j];

			cn = 0.5*(gn + gnw)*sewu[i];
			cs = 0.5*(gs + gsw)*sewu[i];
			ce = 0.5*(ge + gp)*sns[j];
			cw = 0.5*(gp + gw)*sns[j];

			/*CALCULATE CONVECTION COEFFICIENTS */
			dn = viscos * sewu[i] / dynp[j];
			ds = viscos * sewu[i] / dyps[j];
			de = viscos * sns[j] / dxepu[i];
			dw = viscos * sns[j] / dxpwu[i];

			/* ASSEBLE MAIN COEFFICIENTS */
			an[i][j] = max2(fabs(0.5*cn), dn) - 0.5*cn;
			as[i][j] = max2(fabs(0.5*cs), ds) + 0.5*cs;
			ae[i][j] = max2(fabs(0.5*ce), de) - 0.5*ce;
			aw[i][j] = max2(fabs(0.5*cw), dw) + 0.5*cw;
			du[i][j] = sns[j];
			su[i][j] = du[i][j] * (p[i - 1][j] - p[i][j]);
			sp[i][j] = 0.0;

			/* --- For Transient Problem --- */
			apo = ((dxepu[i] + dxpwu[i]) / 2)*densit*sns[j] / dt;
			su[i][j] += apo * uold[i][j];
			sp[i][j] -= apo;
		}
	}


	/*********** PROBLEM MODIFICATION ************/
	for (i = scxi - 1; i <= ecxi + 1; i++)
	{
		u[i][ecyi + 1] = u[i][ecyi];
		an[i][ecyi] = 0.0;
	}

	for (i = scxi - 1; i <= ecxi + 1; i++)
	{
		u[i][scyi - 1] = u[i][scyi];
		as[i][scyi] = 0.0;
	}

	for (j = scyi; j <= ecyi; j++)
	{
		aw[scxi + 1][j] = 0.0;
	}

	ardent = 0.0;
	flow = 0.0;
	for (j = scyi; j <= ecyi; j++)
	{
		arden = densit * sns[j];
		ardent += arden;
		flow += arden * u[ecxi][j];
	}
	uinc = (flowin - flow) / ardent;
	for (j = scyi; j <= ecyi; j++)
	{
		u[ecxi + 1][j] = u[ecxi][j];//
		ae[ecxi][j] = 0.0;//
	}


	/*********** SOLUTION OF DIFFERENCE EQUATION ************/
	resor = 0.0;
	u_resor = 0.0;

	for (i = scxi + 1; i <= ecxi; i++)
	{
		for (j = scyi; j <= ecyi; j++)
		{
			if (fs[i][j] >= SolPhi)
			{
				su[i][j] = 0.0;
				sp[i][j] = -GREAT;
				su[i + 1][j] = 0.0;
				sp[i + 1][j] = -GREAT;

				resor = 0.0;
			}

			ap[i][j] = an[i][j] + as[i][j] + ae[i][j] + aw[i][j] - sp[i][j];

			du[i][j] = du[i][j] / ap[i][j];
			resor = an[i][j] * u[i][j + 1] + as[i][j] * u[i][j - 1] + ae[i][j] * u[i + 1][j]
				+ aw[i][j] * u[i - 1][j] - ap[i][j] * u[i][j] + su[i][j];

			u_resor = u_resor + fabs(resor);
			/* UNDER-RELAXATION */
			ap[i][j] = ap[i][j] / urfu;
			su[i][j] = su[i][j] + (1.0 - urfu)*ap[i][j] * u[i][j];
			du[i][j] = du[i][j] * urfu;
		}
	}


	///*********** SOLUTION OF DIFFERENCE EQUATION ************/
	for (n = 1; n <= nswpu; n++)
	{
		lisolv(scxi + 1, scyi, u);
	}
}


void calc_v(void)
{
	int     i, j, n;
	double  gn, gp, gs, ge, gse, gw, gsw, xp, cn,
		cs, ce, cw, dn, ds, de, dw, tmult, resor;
	double  apo = 0.0;

	/* --- For Transient Prob.(Boundary Condition) --- */
	for (i = scxi - 1; i <= ecxi + 1; i++)
	{
		for (j = scyi - 1; j <= ecyi + 1; j++)
		{
			an[i][j] = as[i][j] = ae[i][j] = aw[i][j] = ap[i][j] = 0.0;
			su[i][j] = sp[i][j] = 0.0;
		}
	}

	/*********** ASSEMBLY OF COEFFICIENT ***********/
	for (i = scxi; i <= ecxi; i++)
	{
		for (j = scyi + 1; j <= ecyi; j++)
		{

			/*CALCULATE CONVECTION COEFFICIENTS */
			gn = densit * v[i][j + 1];
			gp = densit * v[i][j];
			gs = densit * v[i][j - 1];

			ge = densit * u[i + 1][j];
			gse = densit * u[i + 1][j - 1];
			gw = densit * u[i][j];
			gsw = densit * u[i][j - 1];

			cn = 0.5*(gn + gp)*sew[i];
			cs = 0.5*(gp + gs)*sew[i];
			ce = 0.5*(ge + gse)*snsv[j];
			cw = 0.5*(gw + gsw)*snsv[j];

			/*CALCULATE CONVECTION COEFFICIENTS */
			dn = viscos * sew[i] / dynpv[j];
			ds = viscos * sew[i] / dypsv[j];
			de = viscos * snsv[j] / dxep[i];
			dw = viscos * snsv[j] / dxpw[i];

			/* ASSEBLE MAIN COEFFICIENTS */
			an[i][j] = max2(fabs(0.5*cn), dn) - 0.5*cn;
			as[i][j] = max2(fabs(0.5*cs), ds) + 0.5*cs;
			ae[i][j] = max2(fabs(0.5*ce), de) - 0.5*ce;
			aw[i][j] = max2(fabs(0.5*cw), dw) + 0.5*cw;
			dv[i][j] = sew[i];
			su[i][j] = dv[i][j] * (p[i][j - 1] - p[i][j]);
			sp[i][j] = 0.0;

			/* --- For Transient Problem --- */
			//apo = densit*sew[i]*dynpv[j]/dt +densit*sew[i]*dypsv[j]/dt;
			apo = ((dynpv[j] + dypsv[j]) / 2)*densit*sew[i] / dt;

			su[i][j] += apo * vold[i][j];
			sp[i][j] -= apo;
		}
	}


	/*********** PROBLEM MODIFICATION ************/
	/* WEST WALL */
	xp = x[scxi] - xu[scxi];
	i = scxi;

	for (j = scyi + 1; j <= ecyi; j++)
	{
		tmult = viscos / xp;
		aw[i][j] = 0.0;
	}

	/* EAST WALL */
	xp = xu[ecxi + 1] - x[ecxi];
	i = ecxi;

	for (j = scyi + 1; j <= ecyi; j++)
	{
		tmult = viscos / xp;
		ae[i][j] = 0.0;
	}

	/* TOP, BOTTOM WALL */
	for (i = scxi; i <= ecxi; i++)
	{
		as[i][scyi + 1] = 0.0;
		an[i][ecyi] = 0.0;
	}


	/*********** SOLUTION OF DIFFERENCE EQUATION ************/
	resor = 0.0;
	v_resor = 0.0;

	for (i = scxi; i <= ecxi; i++)
	{
		for (j = scyi + 1; j <= ecyi; j++)
		{
			if (fs[i][j] >= SolPhi)
			{
				su[i][j] = 0.0;
				sp[i][j] = -GREAT;
				su[i][j + 1] = 0.0;
				sp[i][j + 1] = -GREAT;

				resor = 0.0;
			}

			ap[i][j] = an[i][j] + as[i][j] + ae[i][j] + aw[i][j] - sp[i][j];

			dv[i][j] = dv[i][j] / ap[i][j];
			resor = an[i][j] * v[i][j + 1] + as[i][j] * v[i][j - 1] +
				ae[i][j] * v[i + 1][j] + aw[i][j] * v[i - 1][j] -
				ap[i][j] * v[i][j] + su[i][j];

			v_resor = v_resor + fabs(resor);
			/* UNDER-RELAXATION */
			ap[i][j] = ap[i][j] / urfv;
			su[i][j] = su[i][j] + (1.0 - urfv)*ap[i][j] * v[i][j];
			dv[i][j] = dv[i][j] * urfv;
		}
	}


	/*********** SOLUTION OF DIFFERENCE EQUATION ************/
	for (n = 1; n <= nswpv; n++)
	{
		lisolv(scxi, scyi + 1, v);
	}
}


void calc_p(void)
{
	int     i, j, n;
	double  cn, cs, ce, cw, smp, ppref;

	/* --- For Transient Prob.(Boundary Condition) --- */
	for (i = scxi - 1; i <= ecxi + 1; i++)
	{
		for (j = scyi - 1; j <= ecyi + 1; j++)
		{
			an[i][j] = as[i][j] = ae[i][j] = aw[i][j] = ap[i][j] = 0.0;
			su[i][j] = sp[i][j] = 0.0;
		}
	}

	m_resor = 0.0;
	/*********** ASSEMBLY OF COEFFICIENT ***********/
	for (i = scxi; i <= ecxi; i++)
	{
		for (j = scyi; j <= ecyi; j++)
		{
			/*CALCULATE COEFFICIENTS */
			an[i][j] = densit * sew[i] * dv[i][j + 1];
			as[i][j] = densit * sew[i] * dv[i][j];
			ae[i][j] = densit * sns[j] * du[i + 1][j];
			aw[i][j] = densit * sns[j] * du[i][j];

			/* CALCULATE SOURCE TERM */
			cn = densit * v[i][j + 1] * sew[i];
			cs = densit * v[i][j] * sew[i];
			ce = densit * u[i + 1][j] * sns[j];
			cw = densit * u[i][j] * sns[j];

			smp = cn - cs + ce - cw;
			sp[i][j] = 0.0;
			su[i][j] = -smp;

			/* COMPUTE SURM OF ABSOLUTE MASS SOURCES */
			m_resor = m_resor + fabs(smp);
		}
	}

	/*********** FINAL COEFFICIENT ASSEMBLY ************/
	for (i = scxi; i <= ecxi; i++)
	{
		for (j = scyi; j <= ecyi; j++)
		{
			ap[i][j] = an[i][j] + as[i][j] + ae[i][j] + aw[i][j] - sp[i][j];
		}
	}

	///*********** SOLUTION OF DIFFERENCE EQUATION ************/
	for (n = 1; n <= nswpp; n++)
	{
		lisolv(scxi, scyi, pp);
	}

	/*********** CORRECT VELOCITIES AND PRESSURE ************/
	/* FOR VELOCITIES */
	for (i = scxi; i <= ecxi; i++)
	{
		for (j = scyi; j <= ecyi; j++)
		{
			if (i != scxi)  u[i][j] = u[i][j] + du[i][j] * (pp[i - 1][j] - pp[i][j]);
			if (j != scyi)  v[i][j] = v[i][j] + dv[i][j] * (pp[i][j - 1] - pp[i][j]);
		}
	}

	/*********** PRESSURES WITH PROVISION FOR UNDER-RELAXATION  ************/
	ppref = pp[ipref][jpref];
	for (i = scxi; i <= ecxi; i++)
	{
		for (j = scyi; j <= ecyi; j++)
		{
			p[i][j] = p[i][j] + urfp * (pp[i][j] - ppref);
			pp[i][j] = 0.0;
		}
	}
}


void update_velocity(void)
{
	int i, j;
	for (i = scxi + 1; i <= ecxi; i++)
	{
		for (j = scyi; j <= ecyi; j++)
		{
			uold[i][j] = u[i][j];
		}
	}

	for (i = scxi; i <= ecxi; i++)
	{
		for (j = scyi + 1; j <= ecyi; j++)
		{
			vold[i][j] = v[i][j];
		}
	}
}

void lisolv(int istart, int jstart, double **phi)
{
	double  *a, *b, *c, *d, term;
	int     jstm1, i, j;

	a = m1ddouble(0, Nyp1);
	b = m1ddouble(0, Nyp1);
	c = m1ddouble(0, Nyp1);
	d = m1ddouble(0, Nyp1);
	//for(i=1;i<=ny;i++)
	for (i = scxi - 1;i <= scxi + 1;i++)
	{
		a[i] = b[i] = c[i] = d[i] = 0.0;
	}

	jstm1 = jstart - 1;
	a[jstm1] = 0.0;

	/* COMMENCE W-E SWEEP */
	for (i = istart; i <= ecxi; i++)
	{
		c[jstm1] = phi[i][jstm1];

		/* COMMENCE S-N SWEEP */
		for (j = jstart; j <= ecyi; j++)
		{
			/* ASSEMBLE TDMA COEFFICIENTS */
			a[j] = an[i][j];
			b[j] = as[i][j];
			c[j] = ae[i][j] * phi[i + 1][j] + aw[i][j] * phi[i - 1][j] + su[i][j];
			d[j] = ap[i][j];

			/* CALCULATE COEFFICIENTS OF RESURRENCES FORMULA */
			term = 1.0 / (d[j] - b[j] * a[j - 1]);
			a[j] = a[j] * term;
			c[j] = (c[j] + b[j] * c[j - 1])*term;
		}

		/* OBTAIN NEW PHI'S VALUES */
		for (j = ecyi; j >= jstart; j--)
		{
			phi[i][j] = a[j] * phi[i][j + 1] + c[j];
		}
	}
}


void prn_output(void)
{
	int     i, j;

	std::cout << " ----------------------------------- THE RESULT ---------------------------------------- \n";
	std::cout << " -- I -- J ---- X --------- Y --------- U --------- V ---------  P --------------------- \n";
	for (j = 1; j <= nj; j++) 
	{
		for (i = 1; i <= ni; i++) 
		{
			std::cout << i<<"\t"<< j<<"\t"<< x[i]<<"\t"<< y[j]<<"\t"\
				<< u[i][j]<<"\t"<< v[i][j]<<"\t"<<p[i][j]<<"\n";
		}
	}
	std::cout << " --------------------------------------------------------------------------------------- \n";
}

void file_prn(int iteration)
{
	FILE    *out;
	char    fn[256];

	// Create filename
	std::stringstream output_filename;
	std::ofstream     output_file;

	int     i, j;

	/* FOR X, Y COORDINATE */
	yprn[scyi - 1] = (y[scyi - 1] + y[scyi]) / 2.0;
	yprn[ecyi + 1] = (y[ecyi + 1] + y[ecyi]) / 2.0;
	for (j = 2; j <= ecyi; j++)
	{
		yprn[j] = y[j];
	}		

	xprn[scxi - 1] = (x[scxi] + x[scxi - 1]) / 2.0;
	xprn[ecxi + 1] = (x[ecxi + 1] + x[ecxi]) / 2.0;
	for (i = scxi; i <= ecxi; i++)
	{
		xprn[i] = x[i];
	}		

	/* FOR U-VELOCITY */
	for (j = scyi - 1;j <= ecyi + 1;j++)
	{
		uprn[scxi - 1][j] = u[scxi][j];
		uprn[ecxi + 1][j] = u[ecxi + 1][j];
	}
	for (i = scxi;i <= ecyi;i++)
	{
		for (j = scyi - 1;j <= ecyi + 1;j++)
		{
			uprn[i][j] = (u[i][j] + u[i + 1][j]) / 2.0;
		}
	}

	/* FOR V-VELOCITY */
	for (i = scxi - 1;i <= ecyi + 1;i++)
	{
		vprn[i][scyi - 1] = v[i][scyi];
		vprn[i][ecyi + 1] = v[i][ecyi + 1];
	}
	for (i = scxi - 1;i <= ecyi + 1;i++)
	{
		for (j = scyi;j <= ecyi;j++)
		{
			vprn[i][j] = (v[i][j] + v[i][j + 1]) / 2.0;
		}
	}

	/* FOR PRESSURE */
	for (i = scxi;i <= ecyi;i++)
	{
		pprn[i][scyi - 1] = p[i][scyi];
		pprn[i][ecyi + 1] = p[i][ecyi];
	}

	for (j = scyi - 1; j <= ecyi + 1; j++)
	{
		pprn[scxi - 1][j] = p[scxi][j];
		pprn[ecxi + 1][j] = p[ecxi][j];
	}
	for (i = scxi; i <= ecxi; i++)
	{
		for (j = scyi; j <= ecyi; j++)
		{
			pprn[i][j] = p[i][j];
		}
	}


	// Set file name
	output_filename.clear();
	output_filename.str("");
	output_filename << "Res_iter_" << iteration << ".plt";
	// Open file
	output_file.open(output_filename.str().c_str(), std::ios::trunc);

	output_file << "TITLE     = \" U,V velocity & Pressure \"\n";
	output_file << "VARIABLES = \"X\",\"Y\",\"U\",\"V\",\"Velo\",\"P\",\"Fs\"\n";
	output_file << "ZONE , T = \"ZONE "<< iteration <<"\", J="<< tnx + 2  <<", I="<< tny + 2 <<", F=POINT\n";
	
	for (i = scxi - 1; i <= ecxi + 1; i++)
	{
		for (j = scyi - 1; j <= ecyi + 1; j++)
		{
			output_file<< xprn[i]<<"\t"<< yprn[j] << "\t" << uprn[i][j] << "\t" << vprn[i][j]<<"\t" \
				<< sqrt(uprn[i][j] * uprn[i][j] + vprn[i][j] * vprn[i][j]) << "\t" << pprn[i][j] << "\t"\
				<< fs[i][j] <<"\n";

		}
	}
	output_file.close();


	// Set file name
	output_filename.clear();
	output_filename.str("");
	output_filename << "Res_iter_" << iteration << ".txt";
	// Open file
	output_file.open(output_filename.str().c_str(), std::ios::trunc);
	output_file << "TITLE     = \" U,V velocity & Pressure \"\n";
	output_file << "VARIABLES = \"X\",\"Y\",\"U\",\"V\",\"Velo\",\"P\",\"Fs\"\n";
	output_file << "ZONE , T = \"ZONE " << iteration << "\", J=" << tnx + 2 << ", I=" << tny + 2 << ", F=POINT\n";

	for (i = scxi - 1; i <= ecxi + 1; i++)
	{
		for (j = scyi - 1; j <= ecyi + 1; j++)
		{
			output_file << xprn[i] << "\t" << yprn[j] << "\t" << uprn[i][j] << "\t" << vprn[i][j] << "\t" \
				<< sqrt(uprn[i][j] * uprn[i][j] + vprn[i][j] * vprn[i][j]) << "\t" << pprn[i][j] << "\t"\
				<< fs[i][j] << "\n";
		}
	}
	output_file.close();
}
