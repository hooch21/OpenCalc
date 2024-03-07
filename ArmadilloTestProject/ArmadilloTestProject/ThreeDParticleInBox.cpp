#include "ThreeDParticleInBox.h"



ThreeDParticleInBox::ThreeDParticleInBox(int Nx, int Ny, int Nz, double Lx, double Ly, double Lz) : ThreeDHamiltonianClass(Nx, Ny, Nz, Lx, Ly, Lz)
{
}

ThreeDParticleInBox::ThreeDParticleInBox(int Nx, int Ny, int Nz, double Lx, double Ly, double Lz, bool useSparseMatrix, int numEigenvalsToCalc) : ThreeDHamiltonianClass(Nx, Ny, Nz, Lx, Ly, Lz, useSparseMatrix, numEigenvalsToCalc)
{
}
