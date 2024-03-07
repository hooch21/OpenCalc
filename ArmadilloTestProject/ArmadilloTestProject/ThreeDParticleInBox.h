#pragma once
#include "ThreeDHamiltonianClass.h"
ref class ThreeDParticleInBox : public ThreeDHamiltonianClass
{
	public:
		ThreeDParticleInBox(int Nx, int Ny, int Nz, double Lx, double Ly, double Lz);
		ThreeDParticleInBox(int Nx, int Ny, int Nz, double Lx, double Ly, double Lz, bool useSparseMatrix, int numEigenvalsToCalc);
};

