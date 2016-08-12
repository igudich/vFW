#include <mpi.h>
#include <iostream>
#include <sstream> 
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char* argv[])
{

  string ex_name("../vWFnew");
  if(argc > 1)
    ex_name = string(argv[1]);
	
  stringstream sstr;
  string conf_name, folder_name, s;
  
  MPI_Init(NULL, NULL);

  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  sstr<<world_rank;
  sstr>>s;
  conf_name = string("../") + string("params_") + s + string(".txt");
  folder_name = string("out_") + s;
  
  mkdir(folder_name.c_str(), 0777);
  if(chdir(folder_name.c_str()) != 0)
	return 1;
  cout<<"r = "<< world_rank<<"; folder: "<<folder_name.c_str()<< endl;
  
  pid_t pid = fork();
  if(pid == 0)
  {
	 cout<<"r = "<< world_rank<< " pid = " << pid << endl;
	 cout<<ex_name.c_str()<<" "<<conf_name.c_str()<<endl;
	 execl(ex_name.c_str(), ex_name.c_str(), conf_name.c_str(), NULL);
  } 
  else 
  {
    int status;
    if(waitpid(pid, &status, 0) == -1)
    {
	    cout<<"error in process rank "<< world_rank<< " pid = " << pid << endl;
    }
  }

  // Finalize the MPI environment.
  MPI_Finalize();
}
