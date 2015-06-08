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

std::vector<std::string> &split(const std::string &s, char delim,
		std::vector<std::string> &elems) {
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
	srand(static_cast<unsigned>(time(0)));
	int size = 0;
	int rank = 0;
	int iloscIteracji=10000;
	int dlugscSekwencjiDoPrzewidzenia = 3;
	int inputNeurons = 6;

	static double mpiWejscie[2][3][6] = { { { 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 }, {
			0.0, 0.0, 0.0, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 } },
			{ { 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 },
					{ 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 1.0, 0.0,
							0.0 } } };

	MPI::Init(argc, argv);
	size = MPI::COMM_WORLD.Get_size();
	rank = MPI::COMM_WORLD.Get_rank();
	int numnerOfProcesses = size;
	double ***wejTab = new double**[numnerOfProcesses];
	for (int i = 0; i < numnerOfProcesses; i++) {
		wejTab[i] = new double*[dlugscSekwencjiDoPrzewidzenia];

	}
	for (int i = 0; i < numnerOfProcesses; i++) {
		for (int j = 0; j < dlugscSekwencjiDoPrzewidzenia; j++) {
			wejTab[i][j] = new double[inputNeurons];

		}

	}
	int dltestowejTablicy = iloscIteracji+1;
	int* testowaTablica = new int[dltestowejTablicy];
	if (rank == 0) {

		for (int i = 0; i < dltestowejTablicy; i++) {
			testowaTablica[i] = rand() % inputNeurons;
		}
		cout << "testowaTablica[0]:" << testowaTablica[0] << endl;
	}

	MPI::COMM_WORLD.Bcast(&(testowaTablica[0]), dltestowejTablicy, MPI::INT, 0);

	cout << "size" << size << endl;

	MPI::COMM_WORLD.Bcast(&(mpiWejscie[0][0][0]),
			numnerOfProcesses * dlugscSekwencjiDoPrzewidzenia * inputNeurons,
			MPI::DOUBLE, 0);

	elman** eTab = new elman*[numnerOfProcesses];
	for (int s = 0; s < size; s++) {
		if (rank == s) {

			for (int i = 0; i < dlugscSekwencjiDoPrzewidzenia; i++) {
				for (int j = 0; j < inputNeurons; j++) {
					wejTab[s][i][j] = mpiWejscie[s][i][j];

				}
			}
			eTab[s] = new elman(iloscIteracji, inputNeurons, 3, 0.5, wejTab[s]);
//			cout << "rank: " << rank << "  :" << testowaTablica[0] << endl;
			eTab[s]->elmanNetwork();
			eTab[s]->testNetwork(testowaTablica);
		}
	}

	//delete e;

	MPI::Finalize();
	cout << "Wcisnij klawisz aby kontynuowac...";
	return 0;
}

