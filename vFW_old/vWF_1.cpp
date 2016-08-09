// vWF.cpp: определяет точку входа для консольного приложения.
//

// program units:
// 1 = 10^-8 meter ( 10 nm )
// 1 = 10^-4 sec
// 1 = 10^-15 kg


#include "stdafx.h"
#include "time.h"
#include "ctime"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>  
#include <chrono>
#include <iostream>
#include <random>

#include "omp.h"

int _tmain(int argc, _TCHAR* argv[])
{
	srand (time(NULL)); 
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  std::default_random_engine generator (seed);
  std::normal_distribution<double> distribution(0,1.0);
	
  FILE *out=fopen ("Dat_vWF_test_40_1,5_sr_4000_er_20_new_test.txt", "w"); 

// solver

double dt=0.002;         // Time step (ns?)
long ns=5000000;  	 // number of iteractions to calculate   
double nfac=1000;	 // data saving rate (to file)

// Particles and environment 

const int N=40;		    // Number of interacting spheres
const double kT=1.38*310;   // Termal energy at 310 K or 37 C
double R=5;	            // Radius of spheres in 10^-8 meter
double d=2*R;

// Interaction between spheres

double uvdw=2.5;	    // sphere-sphere interaction potential depth
double uspr=300;	    // stiffness of springs connecting spheres
double alfa=5.5; 	    // How fast do forces decrease with distance between 2 interacting spheres	

// Hydrodynamics
double srat=4000;   // shear rate
double erat=20;     // elongation rate    

erat=erat/10000;
srat=srat/10000;

// Interaction of sphere with solution (blood plasma)

const double nu=1;                // viscosity of blood plasma
double gama=6*3.1415*nu*R;	// Friction coefficient for sphere (dimer) in plasma
double D=kT/gama;               // Diffusion constant



// INNER PARAMETERS DEFINED BY CONSTANTS
	
double mno=sqrt(2*gama*kT/dt);
double kspr=(uspr/(R*R*2))*kT;
double kvdw=uvdw*kT;


// VARIABLES

double r[3][N];
double f1[3][N];
double f2[3][N];
	
	for (int i=0;i<N;i++)
		for (int j=0;j<3;j++)
		{
			r[j][i]=0;
			f1[j][i]=0;
			f2[j][i]=0;
		}

		//	for (int i=0;i<N;i++)
		//	r[0][i]=double(i)*d;
			

// reading initial coordinates from the file

FILE *our=fopen ("initial_coordinates_40.txt", "r"); 

		for (int j=0;j<N;j++)
		{
			for (int i=0;i<3;i++)
			{
				fscanf (our,"%lf",&r[i][j]);
			}
		}

		fclose (our);

	//	printf ("%lf \n",r[0][1]);

double dv[3];
dv[0]=0;dv[1]=0;dv[2]=0;

double fpr[3];
fpr[0]=0;fpr[1]=0;fpr[2]=0;


	double spmno=dt/gama;
	double l=0;

	double dx=0;
	double dy=0;
	double dz=0;
	double u=0;
	double u2=0;


	double rs[3];
	double srten[3][3];

	srten[0][0]=erat;			 // how velocity changes in space
	srten[0][1]=0;
	srten[0][2]=srat;
	srten[1][0]=0;
	srten[1][1]=-erat;
	srten[1][2]=0;
	srten[2][0]=0;
	srten[2][1]=0;
	srten[2][2]=0;
	


	printf ("Started calculation.. ");

  for (long s=0;s<ns;s++)
  {


  for (int i=0;i<N;i++)
		for (int j=0;j<3;j++)
		{
			f1[j][i]=0;
			
		}

for (int i=0;i<N;i++)
			for (int j=i+1;j<N;j++)
			{
				dx=r[0][i]-r[0][j];
				dy=r[1][i]-r[1][j];
				dz=r[2][i]-r[2][j];

				l=sqrt ( (dx*dx) + (dy*dy) + (dz*dz) );
				if (l==0) printf ("a");

				if ( (j-i==1) || (l<d) )
				{
					fpr[0]=kspr*(l-d)*dx/l;
					fpr[1]=kspr*(l-d)*dy/l;
					fpr[2]=kspr*(l-d)*dz/l;

					f1[0][i]-=fpr[0];
				    f1[1][i]-=fpr[1];
					f1[2][i]-=fpr[2];

					f1[0][j]+=fpr[0];
				    f1[1][j]+=fpr[1];
					f1[2][j]+=fpr[2];
				}

				if ((l<2*d) & (l>d) & (j>i+1) )
				{
					u=exp(-((l-d)/d)*alfa );
					u2=2*alfa*kvdw*(u*(1-u)/(l*d));

				    fpr[0]=u2*dx;
					fpr[1]=u2*dy;
					fpr[2]=u2*dz;

				    f1[0][i]-=fpr[0];
				    f1[1][i]-=fpr[1];
					f1[2][i]-=fpr[2];

					f1[0][j]+=fpr[0];
				    f1[1][j]+=fpr[1];
					f1[2][j]+=fpr[2];
				}
		
			}


    	rs[0]=0;
	rs[1]=0;
	rs[2]=0;

	  for (int i=0;i<N;i++)
	  {
	  f1[0][i]+= distribution(generator)*mno;
	  f1[1][i]+= distribution(generator)*mno;
	  f1[2][i]+= distribution(generator)*mno;

	  rs[0]+=r[0][i];
	  rs[1]+=r[1][i];
	  rs[2]+=r[2][i];
	  }

	  rs[0]=rs[0]/double(N);
	   rs[1]=rs[1]/double(N);
	    rs[2]=rs[2]/double(N);

		if (s==0)
             printf ("\n %lf %lf %lf \n", rs[0],rs[1],rs[2]);


		  for (int i=0;i<N;i++)
		  {
			  dx=r[0][i]-rs[0];
			  dy=r[1][i]-rs[1];
			  dz=r[2][i]-rs[2];

			  if (s>1000)
			  {
			  dv[0]=(dx*srten[0][0]) + (dy*srten[0][1]) + (dz*srten[0][2]);
			  dv[1]=(dx*srten[1][0]) + (dy*srten[1][1]) + (dz*srten[1][2]);
			  dv[2]=(dx*srten[2][0]) + (dy*srten[2][1]) + (dz*srten[2][2]);
			  }

	r[0][i]+=((f1[0][i]*spmno) + (dv[0]*dt));
	r[1][i]+=((f1[1][i]*spmno) + (dv[1]*dt));
	r[2][i]+=((f1[2][i]*spmno) + (dv[2]*dt));

	  }
	
	


		// INTERACTION

		

			if ( fmod (double(s),double(nfac))==0)
			{

				fprintf (out,"* %i \n",int(double(s)/double(nfac)) );

			for (int i=0;i<N;i++)	
				{
					fprintf (out,"%lf %lf %lf \n",r[0][i],r[1][i],r[2][i]);
					

				}
			}



}


  printf ("Done \n");

}
