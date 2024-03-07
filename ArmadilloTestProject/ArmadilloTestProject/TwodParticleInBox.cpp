#include "TwodParticleInBox.h"

using namespace System;

TwodParticleInBox::TwodParticleInBox(int Nx, int Ny, double Lx, double Ly) : TwodHamiltonianClass(Nx, Ny, Lx, Ly)
{
}

TwodParticleInBox::TwodParticleInBox(int Nx, int Ny, double Lx, double Ly,bool useSparseMatrix, int numEigenvalsToCalc) : TwodHamiltonianClass(Nx, Ny, Lx, Ly, useSparseMatrix, numEigenvalsToCalc)
{
}

mat*
TwodParticleInBox::CreateMatrix()
{

	//infinite two dimensional square well problem

	int num = Nx * Ny;

	mat* M = new mat(num, num, fill::zeros);
	

	double dxSqrd = System::Math::Pow(dx, 2);
	double dySqrd = System::Math::Pow(dy, 2);
	
	//There is one equation for each cell in the Nx by Ny grid
	//cellNum is a linear count of the cells in the grid
	//Using a natural ordering for the cells in the grid.

	int cellNum = 0;

	for (int i = 0; i < num; i++)
	{
		cellNum = i;

		//This is the equation for each cell
		//Each cell equation is a vector of Nx*Ny components, most of which are zero.
		for (int j = 0; j < num; j++)
		{
			//(*M)(i,j) = 0.0;

			//Diagonal element
			if (i == j) (*M)(i,j) = 2.0 / dxSqrd + 2.0 / dySqrd;

			//Elements correspoinding to y-cells above and below current cell
			if (j == i - Nx || j == i + Nx) (*M)(i,j) = -1.0 / dySqrd;

			//Element corresponding to x-cell before current cell. 
			//If current cell is first cell in a row, it does not have a before cell.
			if (cellNum % Nx != 0 && j == i - 1) (*M)(i,j) = -1.0 / dxSqrd;

			//Element corresponding to x-cell after current cell
			//If current cell is last cell in a row it does not have an after cell.
			if ((cellNum + 1) % Nx != 0 && j == i + 1) (*M)(i,j) = -1.0 / dxSqrd;

		}

	}
	
	return M;
}
