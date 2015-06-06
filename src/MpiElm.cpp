/*
 ============================================================================
 Name        : MpiElm.c
 Author      : bierla
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include <math.h> 
#include "mpi.h" 
#include <iostream>
#include "elman.h"
#include <vector>
using namespace std;
 
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

int main(int argc, char *argv[]) {
	int n, rank, size, i;
	double PI25DT = 3.141592653589793238462643;
	double mypi, pi, h, sum, x;

	int numnerOfProcesses=2;
	int dlugscSekwencjiDoPrzewidzenia=3;
	int inputNeurons=6;

	static double mpiWejscie[2][3][6] = {{{0.0, 0.0, 0.0, 1.0, 0.0, 0.0},{0.0, 0.0, 0.0, 0.0, 0.0, 1.0},{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}},	{{0.0, 0.0, 0.0, 1.0, 0.0, 0.0},{0.0, 0.0, 0.0, 0.0, 0.0, 1.0},{0.0, 0.0, 1.0, 0.0, 0.0, 0.0}}};

	MPI::Init(argc, argv);
	size = MPI::COMM_WORLD.Get_size();
	rank = MPI::COMM_WORLD.Get_rank();

	cout << "size" << size <<endl;
	n=1000; // number of intervals

	MPI::COMM_WORLD.Bcast(&(mpiWejscie[0][0][0]),numnerOfProcesses*dlugscSekwencjiDoPrzewidzenia*inputNeurons, MPI::DOUBLE, 0);


	double **wej = new double*[3];

	for(int i=0; i<3; i++)
	{
		wej[i] = new double[6];

	}

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<6; j++)
		{
			wej[i][j]=mpiWejscie[0][i][j];

		}
	}

	elman* e = new elman(10000,inputNeurons,1,0.5,wej);

//	MPI::COMM_WORLD.Reduce(&mypi, &pi, 1, MPI::DOUBLE, MPI::SUM, 0);
	if (rank == 0){
		cout << "pi is approximately " << pi << ", Error is "
				<< fabs(pi - PI25DT) << endl;



	cout<<"elman\n";
	e->elmanNetwork();

	cout<<"test2\n";
	e->testNetwork();

	cout<<"Wcisnij klawisz aby kontynuowac...";

	//delete e;
	}
	MPI::Finalize();
	return 0;
}

