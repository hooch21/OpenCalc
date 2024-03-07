#include "TwodHarmonicOscillator.h"

using namespace System;
using namespace System::Collections::Generic;
//using System.Linq;
using namespace System::Text;
//using System.Threading.Tasks;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace EigenSpace;

using namespace std;
using namespace arma;

TwodHarmonicOscillator::TwodHarmonicOscillator(int Nx, int Ny, double Lx, double Ly, double Kx, double Ky) : TwodHamiltonianClass(Nx,Ny,Lx,Ly)
{
	x0 = Lx / 2.0;
	y0 = Ly / 2.0;

	this->Kx = Kx;
	this->Ky = Ky;
}

TwodHarmonicOscillator::TwodHarmonicOscillator(int Nx, int Ny, double Lx, double Ly, double Kx, double Ky,bool useSparseMatrix, int numEigenvalsToCalc) : TwodHamiltonianClass(Nx, Ny, Lx, Ly,useSparseMatrix, numEigenvalsToCalc)
{
	x0 = Lx / 2.0;
	y0 = Ly / 2.0;

	this->Kx = Kx;
	this->Ky = Ky;
}

mat*
TwodHarmonicOscillator::CreateMatrix()
{

	//infinite two dimensional square well problem

	int num = Nx * Ny;

	mat* M = new mat(num, num, fill::zeros);

	double dxSqrd = System::Math::Pow(dx, 2);
	double dySqrd = System::Math::Pow(dy, 2);

	//There is one equation for each cell in the Nx by Ny grid
	//cellNum is a linear count of the cells in the grid
	//Using a natural ordering for the cells in the grid.

	V = gcnew cli::array<double>(num);

	double x, y;

	double yDiff, VyDiff;
	double xDiff;

	int cnt = 0;

	//There are Ny rows in the grid
	for (int j = 0; j < Ny; j++)
	{
		y = j * dy;

		yDiff = (y - y0);

		VyDiff = Ky * yDiff * yDiff;

		//Each row has Nx elements
		//The matrix below(M) is ordered using the "natural order" for the grid.
		//See page 84 http://www4.ncsu.edu/~zhilin/TEACHING/MA402/chapt5.pdf
		for (int i = 0; i < Nx; i++)
		{
			x = i * dx;
			xDiff = x - x0;

			V[cnt++] = VyDiff + Kx * xDiff * xDiff;

		}
	}

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
			//(*M)(i, j) = 0.0;

			//Diagonal element
			if (i == j) (*M)(i, j) = V[cellNum] + 2.0 / dxSqrd + 2.0 / dySqrd;

			//Elements correspoinding to y-cells above and below current cell
			if (j == i - Nx || j == i + Nx) (*M)(i, j) = -1.0 / dySqrd;

			//Element corresponding to x-cell before current cell. 
			//If current cell is first cell in a row, it does not have a before cell.
			if (cellNum % Nx != 0 && j == i - 1) (*M)(i, j) = -1.0 / dxSqrd;

			//Element corresponding to x-cell after current cell
			//If current cell is last cell in a row it does not have an after cell.
			if ((cellNum + 1) % Nx != 0 && j == i + 1) (*M)(i, j) = -1.0 / dxSqrd;

		}

	}

	/*
	//This works!
	//Convert M to sparse sp_mat
	sp_mat B(*M);

	//B.print("M sparse");

	double density = (double)B.n_nonzero / (double)B.n_elem;

	cout << B.n_nonzero << " "<< density << endl;
	*/

	return M;
}

void
TwodHarmonicOscillator::WriteToFile(String^ outputFile, int nstate)
{
	StreamWriter^ sw = gcnew StreamWriter(outputFile);

	try
	{
		String^ str = "Xaxis";

		for (int i = 0; i < 1; i++)
		{
			str += "\tValue";
		}

		sw->WriteLine(String::Format("DX\t{0}\tDY\t{1} Eigenstate {2}", dx.ToString(), dy.ToString(), nstate.ToString()));

		//Each eigenrec vector has Nx*Ny values.
		//want to print them as rows.

		CXEigenRec^ er = eigenClass->GetCXEigenRec(nstate);

		//how many points are in an eigenvector?
		int numPtsInEigenvector = er->vector->Length;

		cout << "Num pts in Eigenvector in WriteToFile() " << numPtsInEigenvector << endl;

		//Calculate the number of rows
		//normally nRows will equal Ny, but may not if I am sending in a non-standard matrix
		int nRows = numPtsInEigenvector / Nx;

		double xaxis, yaxis;

		str = "\t";
		for (int j = 0; j<Nx + 2; j++)
		{
			xaxis = dx*(j - 1) - x0;

			str += xaxis.ToString();
			if (j != Nx + 1)
				str += "\t";
		}

		sw->WriteLine(str);

		double a, b, c, d;

		a = 0.0;
		b = 0.0;
		c = 0.0;
		d = 0.0;

		cx_double cx_z;
		double z;
		//There are nRows
		for (int i = 0; i < nRows + 2; i++)
		{
			yaxis = dy*(i - 1) - y0;
			str = yaxis.ToString() + "\t";

			//First row is boundary condition row
			if (i == 0)
			{
				
				str += c.ToString() + "\t";
				//There are Nx columns
				for (int j = 0; j < Nx; j++)
				{
					//negate the vector values
					z = a;
					//z *= z;
					str += a.ToString("N3");
					//if (j != Nx - 1)
					str += "\t";
				}
				str += c.ToString();

				sw->WriteLine(String::Format("{0}", str));
			}

			//last row is boundary condition row
			else if (i == (nRows + 1))
			{
				str += d.ToString() + "\t";
				//There are Nx columns
				for (int j = 0; j < Nx; j++)
				{
					//negate the vector values
					z = b;
					//z *= z;
					str += z.ToString("N3");
					//if (j != Nx - 1)
					str += "\t";
				}
				str += d.ToString();

				sw->WriteLine(String::Format("{0}", str));

			}
			else
			{

				str += a.ToString() + "\t";

				//There are Nx columns
				for (int j = 0; j < Nx; j++)
				{
					//cx_z is complex
					cx_z = *(er->vector[(i - 1) * Nx + j]);

					//z is real
					z = System::Math::Sqrt(norm(cx_z));

					str += z.ToString("N3");
					//if (j != Nx - 1)
					str += "\t";
				}

				str += b.ToString();

				sw->WriteLine(String::Format("{0}", str));
			}

		}

	}
	catch (Exception^ e)
	{
		MessageBox::Show("TwodHarmonicOscillator: exception in WriteFile() : " + e->Message);
	}
	finally
	{
		sw->Close();
	}
}

void 
TwodHarmonicOscillator::WritePotentialEnergy(String^ outputFile)
{
	StreamWriter^ sw = gcnew StreamWriter(outputFile);

	int num = Nx * Ny;

	double pe;

	String^ str = "";

	try
	{
		for (int i = 0; i < Ny; i++)
		{
			str = "";
			for (int j = 0; j < Nx; j++)
			{
				pe = V[i * Nx + j];
				
				str += pe.ToString("0.00");
				if (j != Nx - 1)
					str += "\t";
			}

			sw->WriteLine(str);
		}
	}
	catch (Exception^ e)
	{

	}
	finally
	{
		MessageBox::Show("Finished writing Potential Energy");
		sw->Close();
	}
}
