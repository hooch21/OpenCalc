#pragma once

using namespace System;

#include "ThreeDHamiltonianClass.h"
ref class ThreeDHarmonicOscillator : public ThreeDHamiltonianClass
{
	private:
		double Kx, Ky, Kz;

		double x0, y0, z0;

	public:
		ThreeDHarmonicOscillator(int Nx, int Ny, double Nz, double Lx, double Ly, double Lz, double Kx, double Ky, double Kz);
		ThreeDHarmonicOscillator(int Nx, int Ny, double Nz, double Lx, double Ly, double Lz, double Kx, double Ky, double Kz, bool useSparseMatrix, int numEigenvalsToCalc);

		virtual mat* CreateMatrix() override;
		virtual sp_mat CreateSparseMatrix() override;

		virtual void PopulatePotentialEnergyArray() override;
		

		//virtual void WriteToFile(String^ outputFile, int n_state) override;

		void WritePotentialEnergy(String^ outputFile);
};

