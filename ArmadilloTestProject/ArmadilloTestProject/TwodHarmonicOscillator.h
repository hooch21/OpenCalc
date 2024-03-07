#pragma once

using namespace System;

#include "TwodHamiltonianClass.h"
ref class TwodHarmonicOscillator : public TwodHamiltonianClass
{
	private:
		double Kx, Ky;

		double x0, y0;

		cli::array<double>^ V;

	public:
		TwodHarmonicOscillator(int Nx, int Ny, double Lx, double Ly, double Kx, double Ky);
		TwodHarmonicOscillator(int Nx, int Ny, double Lx, double Ly, double Kx, double Ky, bool useSparseMatrix, int numEigenvalsToCalc);

		virtual mat* CreateMatrix() override;
		

		virtual void WriteToFile(String^ outputFile, int n_state) override;

		void WritePotentialEnergy(String^ outputFile);
};

