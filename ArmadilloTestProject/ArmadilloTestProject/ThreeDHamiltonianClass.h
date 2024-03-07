#pragma once

#include "TwodHamiltonianClass.h"

ref class ThreeDHamiltonianClass : public TwodHamiltonianClass
{
	protected:
		int Nz = 20;

		double Lz = 6.0;

		double dz;
		double dzDiv2;

	public:
		ThreeDHamiltonianClass(int Nx, int Ny, int Nz, double Lx, double Ly, double Lz);
		ThreeDHamiltonianClass(int Nx, int Ny, int Nz, double Lx, double Ly, double Lz, bool useSparseMatric, int numEigenvalsToCalc);

		virtual mat* CreateMatrix() override;
		virtual sp_mat CreateSparseMatrix() override;

		virtual void WriteToFile(String^ outputFile, int nstate) override;

		void WriteToTestFile(String^ outputFile, int nstate);
};

