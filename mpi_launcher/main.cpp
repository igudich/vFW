// vWF.cpp: определяет точку входа для консольного приложения.
//

#include "time.h"
#include "ctime"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <sstream>

#include "omp.h"

using namespace std;

inline bool file_exists(const std::string& name)
{
    ifstream f(name.c_str());
    return f.good();
}

struct parameters
{
	long ns;
	long nsf;
	double nfac;
	int N;
	double uvdw;
	double alfa;

	void read(string filename);
};

void parameters::read(string filename)
{
	ifstream ifstr;
	stringstream sstr;
	string s;

	ifstr.open(filename);

	getline(ifstr, s);
	sstr<<s;
	sstr>>ns;
	sstr.str("");

	getline(ifstr, s);
	sstr<<s;
	sstr>>nsf;
	sstr.str("");

	getline(ifstr, s);
	sstr<<s;
	sstr>>nfac;
	sstr.str("");

	getline(ifstr, s);
	sstr<<s;
	sstr>>N;
	sstr.str("");

	getline(ifstr, s);
	sstr<<s;
	sstr>>uvdw;
	sstr.str("");

	getline(ifstr, s);
	sstr<<s;
	sstr>>alfa;
	sstr.str("");

	ifstr.close();
}

int main(int argc, char* argv[])
{
	string fname("conf.dat");
	if(argc > 1)
		fname = string(argv[1]);

	if(!file_exists(fname))
	{
		cout<<"No file found: "<<fname<<endl;
		return 1;
	}

	parameters par;
	par.read(fname);

	srand (time(NULL));
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::default_random_engine generator (seed);
	std::normal_distribution<double> distribution(0,1.0);

	long ns = par.ns;
	long nsf = par.nsf;
	double nfac = par.nfac;
	int N = par.N;
	double uvdw = par.uvdw;                            // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	double alfa = par.alfa;                        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	cout<<ns<<" "<<nsf<<" "<<nfac<<" "<<N<<" "<<uvdw<<" "<<alfa<<endl;
	return 0;


		double uspr=300;


		double srat=4800;

		double erat=100;




		erat=erat/10000;
		srat=srat/10000;


		double dt=0.002;

		const double kT=1.38*300;

		double R=5;

		double d=2*R;
		const double nu=1;   // viscosity (plasma)

		double gama=6*3.1415*nu*R;

		double D=kT/gama;


		// printf ("Diffusion constant: %lf \n\n",D);

		double mno=sqrt(2*gama*kT/dt);

		double kspr=(uspr/(R*R*2))*kT;
		double kvdw=uvdw*kT;





		double r[3][N];
		double r0[3][N];


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

			FILE *our=fopen ("asddd.txt", "r");


			for (int j=0;j<N;j++)
			{
				for (int i=0;i<3;i++)
				{
					fscanf (our,"%lf",&r[i][j]);
					r0[i][j]=r[i][j];
				}
			}

			fclose (our);

			FILE *ourr=fopen ("outp_x.txt", "r");
			const int nrows=55;
			double masx[nrows];

			for (int i=0;i<nrows;i++)
			{
				fscanf (ourr,"%lf",&masx[i]);
				masx[i]=masx[i]*100000000;
			}

			for (int i=1;i<nrows;i++)
			{

				masx[i]-=masx[0];
			}

			fclose(ourr);




			FILE *ourrr=fopen ("outp_1_1.txt", "r");

			double veldat[nrows];

			for (int i=0;i<nrows;i++)
			{
				fscanf (ourrr,"%lf",&veldat[i]);
				veldat[i]=veldat[i]*10000;
			}


			fclose(ourrr);


			double maserate[nrows];

			for (int i=0;i<nrows-1;i++)
			{
				maserate[i]=(veldat[i+1]-veldat[i])/(masx[1]);
			}
			maserate[nrows-1]=0;


			FILE *ourrrr=fopen ("outp_srate_0.txt", "r");

			double massrate[nrows];

			for (int i=0;i<nrows;i++)
			{
				fscanf (ourrrr,"%lf",&massrate[i]);
				massrate[i]=massrate[i]/10000;
			}

			fclose(ourrrr);






			printf ("%lf %lf %lf  \n", masx[1],maserate[1],massrate[1]);




		//	printf ("%lf \n",r[0][1]);

		double dr[3];
		dr[0]=0;dr[1]=0;dr[2]=0;

		double fpr[3];
		fpr[0]=0;fpr[1]=0;fpr[2]=0;


		double spmno=dt/gama;
		double l=0;

		double dx=0;
		double dy=0;
		double dz=0;
		double u=0;
		double u2=0;

		double dxflow=0;


		double rs[3];
		double srten[3][3];

		srten[0][0]=erat;
		srten[0][1]=0;
		srten[0][2]=srat;
		srten[1][0]=0;
		srten[1][1]=-erat;
		srten[1][2]=0;
		srten[2][0]=0;
		srten[2][1]=0;
		srten[2][2]=0;



		FILE *out=fopen ("Dat_vWF_test_40_4,0_1_mcm_test_3,5_full_1.txt", "a");

		printf ("Started calculation.. ");


		int chkk=0;
		int jcur=0;
		double vcur=0;



		rs[0]=0;
		rs[1]=0;
		rs[2]=0;


		for (int i=0;i<N;i++)
		  {
		  rs[0]+=r[0][i];
		  rs[1]+=r[1][i];
		  rs[2]+=r[2][i];
		  }

		  rs[0]=rs[0]/double(N);
		  rs[1]=rs[1]/double(N);
		  rs[2]=rs[2]/double(N);

	for (int i=0;i<N;i++)
		  {
		  r[0][i]-=rs[0]-1;
		  r[1][i]-=rs[1];
		  r[2][i]-=rs[2];
		  }


	vcur=veldat[0];
	double facttt=10000;

	  for (long s=0;s<nsf;s++)
	  {
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

			chkk=0;
			jcur=-1;

			for (int j=1;j<nrows;j++)
				if (((rs[0]-masx[j])<0) && (chkk==0))
				{
					jcur=j;
					chkk=1;
				}

				if (jcur<0)
				{
					jcur=nrows;
				//	printf ("ooooooops!..\n" );
				}

				erat=maserate[jcur-1];
				srat=massrate[jcur-1];
		if (s>ns)
		{
				erat=0;
				srat=4500/facttt;
		}

	srten[0][0]=erat;
	srten[0][2]=srat;
	srten[1][1]=-erat;


			if (s==0)
				 printf ("\n %lf %lf %lf \n", rs[0],rs[1],rs[2]);


			  for (int i=0;i<N;i++)
			  {
				  dx=r[0][i]-rs[0];
				  dy=r[1][i]-rs[1];
				  dz=r[2][i]-rs[2];

				  if (s>1000)
				  {
				  dr[0]=(dx*srten[0][0]) + (dy*srten[0][1]) + (dz*srten[0][2]);
				  dr[1]=(dx*srten[1][0]) + (dy*srten[1][1]) + (dz*srten[1][2]);
				  dr[2]=(dx*srten[2][0]) + (dy*srten[2][1]) + (dz*srten[2][2]);
				  }

				  if (i==0)
				  {
					  vcur+=(erat*vcur*dt);
					  dxflow=vcur*dt;

				  }

		r[0][i]+=((f1[0][i]*spmno) + (dr[0]*dt) + dxflow);
		r[1][i]+=((f1[1][i]*spmno) + (dr[1]*dt));
		r[2][i]+=((f1[2][i]*spmno) + (dr[2]*dt));

		  }

		  for (int i=0;i<N;i++)
			for (int j=0;j<3;j++)
			{
				f1[j][i]=0;

			}


			// INTERACTION

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
