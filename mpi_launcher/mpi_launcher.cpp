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

int main()
{
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
  conf_name = string("../") + string("conf_") + s + string(".dat");
  folder_name = string("out_") + s;
  
  mkdir(folder_name.c_str(), 0777);
  chdir(folder_name.c_str());
 
  
  pid_t pid = fork();
  int exec_time;
  if(pid == 0)
  {
	 execl("../vWF", "../vWF", conf_name.c_str(), NULL);
	 cout<<"r = "<< world_rank<< " pid = " << pid << endl;
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
