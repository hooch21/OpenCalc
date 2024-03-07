#include "TwodHamiltonianClass.h"

using namespace System;
using namespace System::Collections::Generic;
//using System.Linq;
using namespace System::Text;
//using System.Threading.Tasks;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace EigenSpace;


TwodHamiltonianClass::TwodHamiltonianClass(int Nx, int Ny, double Lx, double Ly)
{
	this->Nx = Nx;
	this->Ny = Ny;
	this->Lx = Lx;
	this->Ly = Ly;

	this->dx = Lx / Nx;
	this->dy = Ly / Ny;

	this->dxDiv2 = this->dx / 2.0;
	this->dyDiv2 = this->dy / 2.0;
}

TwodHamiltonianClass::TwodHamiltonianClass(int Nx, int Ny, double Lx, double Ly, bool useSparseMatrix, int numEigenvalsToCalc)
{
	this->Nx = Nx;
	this->Ny = Ny;
	this->Lx = Lx;
	this->Ly = Ly;

	this->dx = Lx / Nx;
	this->dy = Ly / Ny;

	this->dxDiv2 = this->dx / 2.0;
	this->dyDiv2 = this->dy / 2.0;

	this->useSparseMatrix = useSparseMatrix;
	this->numEigenvalsToCalc = numEigenvalsToCalc;
}

void
TwodHamiltonianClass::Delete()
{
	eigenClass->Delete();
}

sp_mat
TwodHamiltonianClass::CreateSparseMatrix()
{
	mat *M = CreateMatrix();

	//Convert M to sparse sp_mat
	sp_mat B(*M);

	//B.print("Sparse:");

	//B.print("M sparse");
	double density = (double)(B).n_nonzero / (double)(B).n_elem;
	cout << "B.nzero " <<  (B).n_nonzero << " density " << density << endl;

	cout << "M nrows "<< (*M).n_rows << " ncols " << (*M).n_cols << endl;

	delete M;
	cout << "Deleteing M matrix after creating sparse matrix " << endl;

	return B;
}


void 
TwodHamiltonianClass::Solve()
{
	if (useSparseMatrix)
	{
		sp_mat sparseH = CreateSparseMatrix();
		eigenClass = gcnew EigenClass(sparseH,numEigenvalsToCalc);
	}
	else
	{
		mat* H = CreateMatrix();
		eigenClass = gcnew EigenClass(*H);
	}
}

EigenClass^
TwodHamiltonianClass::GetEigenClass()
{
	return eigenClass;
}

void
TwodHamiltonianClass::WriteToFile(String^ outputFile, int nstate)
{
	StreamWriter^ sw = gcnew StreamWriter(outputFile);

	int index;

	double xval, yval, zval;

	String^ precision = "N7";

	try
	{
		sw->WriteLine(String::Format("Eigenstate\t{0}", nstate.ToString()));
		sw->WriteLine(String::Format("Lx\t{0}\tLy\t{1}", Lx.ToString(), Ly.ToString()));
		sw->WriteLine(String::Format("Nx\t{0}\tNy\t{1}", Nx.ToString(), Ny.ToString()));

		String^ str = "Xaxis";

		for (int i = 0; i < 1; i++)
		{
			str += "\tValue";
		}

		sw->WriteLine(String::Format("DX\t{0}\tDY\t{1}", dx.ToString(), dy.ToString()));

		//Each eigenrec vector has Nx*Ny values.
		//want to print them as rows.

		CXEigenRec^ er = eigenClass->GetCXEigenRec(nstate);

		//how many points are in an eigenvector?
		int numPtsInEigenvector = er->vector->Length;

		cout << "Num pts in Eigenvector in WriteToFile() " << numPtsInEigenvector << endl;

		//Calculate the number of rows
		//normally nRows will equal Ny, but may not if I am sending in a non-standard matrix
		//nRows is the number of points in an eigenvector divided Nx
		int nRows = numPtsInEigenvector / Nx;

		//Calc the xaxis values
		str = "\r\nyaxis";
		//Write a bunch of tabs to center the x-axis label
		for (int i = 0; i < Nx / 2; i++)
			str += "\t";
		str += "x-axis\r\n\t";

		//There are Nx cells. The calculated values are at the center of each cell
		double dxDiv2 = dx / 2.0;
		double dyDiv2 = dy / 2.0;
	
		//for (int j = 0; j<Nx + 2; j++)
		for (int j = 0; j<Nx; j++)
		{
			//str += (dx * (j - 1)).ToString();
			//str += (dx*j).ToString();
			str += (dxDiv2 + dx*j).ToString(precision);
			if (j != Nx + 1)
				str += "\t";
		}

		//write the x-axis values
		sw->WriteLine(str);

		double a, b, c, d;

		a = 0.0;
		b = 0.0;
		c = 0.0;
		d = 0.0;

		//probability
		double prob;
		cx_double cx_probAmp;

		cout << " Ny " << Ny << " nRows " << nRows << endl;

		//There are Ny rows in a layer
		//There are Nz layers

		int Nxy = Nx*Ny;

		double zval = 0.0;

		cout << "Nxy " << Nxy << endl;

		//sw->Write("\r\ny-axis");
		//for (int k = 0; k < Nz; k++)
		//{
		//	//zval = k*dz;
		//	zval = dzDiv2 + k*dz;

		//	//if ( k == 0 )
		//	//	sw->WriteLine("\r\ny-axis\tZ={0}\r\n", zval.ToString());
		//	//else
		//	sw->WriteLine("\r\n\tz=\t{0}\r\n", zval.ToString(precision));

			//sw->WriteLine("\r\ny-axis\tZ={0}\r\n", zval.ToString());
			//There are nRow(formerly Ny) rows in a layer
			for (int j = 0; j < Ny; j++)
			{
				//yval = j*dy;
				yval = dyDiv2 + j*dy;

				str = yval.ToString("N3") + "\t";
				//There are Nx columns
				for (int i = 0; i < Nx; i++)
				{
					//cx_z is complex
					index = j * Nx + i;
					cx_probAmp = *(er->vector[index]);

					//z is real
					prob = System::Math::Sqrt(norm(cx_probAmp));

					str += prob.ToString(precision);
					if (i != Nx - 1)
						str += "\t";
				}

				//str += b.ToString();

				sw->WriteLine(String::Format("{0}", str));
			}
		/*}*/

	}//try
	catch (Exception^ e)
	{
		MessageBox::Show("ThreeDHamiltonianClass: exception in WriteFile() : " + e->Message + " " + index.ToString());
	}
	finally
	{
		sw->Close();
	}
}

//void
//TwodHamiltonianClass::WriteToFile(String^ outputFile, int nstate)
//{
//	StreamWriter^ sw = gcnew StreamWriter(outputFile);
//
//	try
//	{
//		String^ str = "Xaxis";
//
//		for (int i = 0; i < 1; i++)
//		{
//			str += "\tValue";
//		}
//
//		sw->WriteLine(String::Format("DX\t{0}\tDY\t{1} Eigenstate {2}", dx.ToString(), dy.ToString(), nstate.ToString()));
//
//		//Each eigenrec vector has Nx*Ny values.
//		//want to print them as rows.
//
//		CXEigenRec^ er = eigenClass->GetCXEigenRec(nstate);
//
//		//how many points are in an eigenvector?
//		int numPtsInEigenvector = er->vector->Length;
//
//		cout << "Num pts in Eigenvector in WriteToFile() " << numPtsInEigenvector << endl;
//
//		//Calculate the number of rows
//		//normally nRows will equal Ny, but may not if I am sending in a non-standard matrix
//		int nRows = numPtsInEigenvector / Nx;
//
//		str = "\t";
//		for (int j = 0; j<Nx + 2; j++)
//		{
//			str += (dx * (j - 1)).ToString();
//			if (j != Nx + 1)
//				str += "\t";
//		}
//
//		sw->WriteLine(str);
//
//		double a, b, c, d;
//
//		a = 0.0;
//		b = 0.0;
//		c = 0.0;
//		d = 0.0;
//
//		cx_double cx_z;
//		double		z;
//
//		cout << " Ny " << Ny << " nRows " << nRows <<endl;
//
//		//There are nRows
//		for (int i = 0; i < nRows + 2; i++)
//		{
//
//			//First row is boundary condition row
//			if (i == 0)
//			{
//				str = (dy * (i - 1)).ToString() + "\t";
//				str += c.ToString() + "\t";
//				//There are Nx columns
//				for (int j = 0; j < Nx; j++)
//				{
//					z = a;
//					//z *= z;
//					str += a.ToString("N3");
//					//if (j != Nx - 1)
//					str += "\t";
//				}
//				str += c.ToString();
//
//				sw->WriteLine(String::Format("{0}", str));
//			}
//			
//			//last row is boundary condition row
//			else if (i == (nRows + 1))
//			{
//				str = (dy * (i - 1)).ToString() + "\t";
//				str += d.ToString() + "\t";
//				//There are Nx columns
//				for (int j = 0; j < Nx; j++)
//				{
//					
//					z = b;
//					//z *= z;
//					str += b.ToString("N3");
//					//if (j != Nx - 1)
//					str += "\t";
//				}
//				str += d.ToString();
//
//				sw->WriteLine(String::Format("{0}", str));
//
//			}
//			else
//			{
//
//				str = (dy*(i - 1)).ToString() + "\t";
//
//				str += a.ToString() + "\t";
//
//				//There are Nx columns
//				for (int j = 0; j < Nx; j++)
//				{
//					//cx_z is complex
//					cx_z = *(er->vector[(i - 1) * Nx + j]);
//
//					//z is real
//					z = System::Math::Sqrt(norm(cx_z));
//
//					str += z.ToString("N3");
//					//if (j != Nx - 1)
//					str += "\t";
//				}
//
//				str += b.ToString();
//
//				sw->WriteLine(String::Format("{0}", str));
//			}
//
//		}
//
//	}
//	catch (Exception^ e)
//	{
//		MessageBox::Show("TwodHamiltonianClass: exception in WriteFile() : " + e->Message);
//	}
//	finally
//	{
//		sw->Close();
//	}
//}

mat*
TwodHamiltonianClass::ReadMatrixFromFile(String^ inputFile)
{
	StreamReader^ sr = gcnew StreamReader(inputFile);

	System::String^ line;
	
	cli::array<System::String^>^ words;

	int nRows = 13;
	int nCols = 13;

	mat* M = new mat(nRows,nCols);

	int i;

	double val;

	try
	{
		System::String^ delimStr = ",";
		cli::array<Char>^ delimeters = delimStr->ToCharArray();

		i = 0;
		while (line = sr->ReadLine())
		{
			words = line->Split(delimeters, System::StringSplitOptions::RemoveEmptyEntries);
			
			String^ str = "";
			
			for (int j= 0; j < words->Length; j++ )
			{
				val = Double::Parse(words[j]);
				(*M)(i, j) = val;
				
			}
			i++;
		}

		(*M).print("M from file:");
		
	}
	catch (Exception^ e)
	{

	}
	finally
	{
		sr->Close();
	}

	return M;
}
