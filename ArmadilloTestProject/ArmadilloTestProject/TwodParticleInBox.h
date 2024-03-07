#pragma once
#include "TwodHamiltonianClass.h"

using namespace std;
using namespace arma;

ref class TwodParticleInBox : public TwodHamiltonianClass
{
	public:
		TwodParticleInBox(int Nx, int Ny, double Lx, double Ly);
		TwodParticleInBox(int Nx, int Ny, double Lx, double Ly, bool useSparseMatrix, int numEigenvalsToCalc);

		virtual mat* CreateMatrix() override;
		
};

