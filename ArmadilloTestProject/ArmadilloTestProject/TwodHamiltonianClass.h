#pragma once
#include <armadillo>
#include "EigenClass.h"

using namespace System;
using namespace EigenSpace;

using namespace std;
using namespace arma;

ref class TwodHamiltonianClass abstract
{
	protected:
		int Nx, Ny;

		double Lx, Ly, dx, dy;

		double dxDiv2, dyDiv2;

		EigenClass^ eigenClass;

		bool useSparseMatrix = true;

		//This is only used if sparseMatrix is true
		int numEigenvalsToCalc = 10;

		cli::array<double>^ V = nullptr;

	public:
		TwodHamiltonianClass(int Nx, int Ny, double Lx, double Ly);
		TwodHamiltonianClass(int Nx, int Ny, double Lx, double Ly, bool useSparseMatric, int numEigenvalsToCalc);

		void Delete();

		virtual mat* CreateMatrix() = 0;
		virtual sp_mat CreateSparseMatrix();

		mat* ReadMatrixFromFile(String^ inputFile);
		
		virtual void PopulatePotentialEnergyArray() {};

		virtual void WriteToFile(String^ outputFile, int nstate);

		void Solve();

		EigenClass^ GetEigenClass();

		property bool UseSparseMatrix
		{
			bool get() { return useSparseMatrix; }

			void set(bool val) { useSparseMatrix = val;  }
		}

		property int NumEigenvalsToCalc
		{
			int get() { return numEigenvalsToCalc; }

			void set(int val) { numEigenvalsToCalc = val; }
		}
};

