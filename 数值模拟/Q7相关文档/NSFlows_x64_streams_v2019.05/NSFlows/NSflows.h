#include <cmath>

#include <iostream> // for the use of 'cout'
#include <fstream>  // file streams
#include <sstream>  // string streams
#include <iomanip>

#define     maxit   (10000)
#define     sormax  (1.0e-1)
#define     GREAT   (10e20)

#define     SolPhi  (0.5)
#define     max2(x,y)       ((x)>(y)?(x):(y))
#define     max3(x,y,z)     ( max2( (max2(x,y)),(z) ) )

int Ngx = 10; // grid number of x axis
int Ngy = 10; // grid number of y axis
int ncx = 10; // cell number of x axis in a CV grid (it must be a even number)
int ncy = 10; // cell number of y axis in a CV grid (it must be a even number)

// Data for Calculation Domain
double xs = 0.;		// starting coordinate of x axis;
double xe = 1.e-4;  // ending coordinate of x axis;
double ys = 0.;		// starting coordinate of y axis;
double ye = 1.e-4;  // ending coordinate of y axis;

double Pi, Vc, Acx, Acy, dcx, dcy, dtmax;

double **fs;
double dt, tmax, tout, dtout, k1, k2, A1, A2, B, tC, BCn, BCx, AA, BB, CC, RC0, VV;
int i, j, tnx, tny, tnxy, hncx, hncy, scxi, scyi, Nxp1, Nyp1, nlayer, clayer, m = 0, it = 0, lay2;

int     nx, ny, ni, nj, ecxi, ecyi, nswpu, nswpv, nswpp, nswpc, ipref, jpref, imon, jmon, kx, ky;

double  u_resor, urfu, m_resor;
double  v_resor, urfv, resorc;
double	urfp, urfc, viscos, densit, xmax, ymax, ubulk, flowin;

double  *x, *y, *dxep, *dxpw, *dynp, *dyps, *sns, *sew, *xu, *yv;
double  *dxepu, *dxpwu, *sewu, *dynpv, *dypsv, *snsv;
double  **du, **dv, **u, **v, **p, **pp;
double  **ap, **an,**as, **ae, **aw, **su, **sp;
double  **uold, **vold, time_f;
double  *xprn, *yprn, **uprn, **vprn, **pprn, **cprn;
int     ncycle, cycles_perframe;

///Subroutine 
void init_fields();
void init_velocity(void);
void mem_alloc_flow(void);
void mem_free_flow(void);
void set_grid(void);
void init_geo(void);
void init_output(void);
void calc_u(void);
void calc_v(void);
void calc_p(void);

void lisolv(int, int, double **);
void update_velocity(void);
void prn_output(void);
void file_prn(int);