#include "ThreeDHamiltonianClass.h"

using namespace System::IO;
using namespace System::Windows::Forms;


ThreeDHamiltonianClass::ThreeDHamiltonianClass(int Nx, int Ny, int Nz, double Lx, double Ly,double Lz) : TwodHamiltonianClass(Nx,Ny,Lx,Ly)
{
	this->Nz = Nz;
	this->Lz = Lz;
	this->dz = Lz / Nz;
	this->dzDiv2 = this->dz / 2.0;
}

ThreeDHamiltonianClass::ThreeDHamiltonianClass(int Nx, int Ny, int Nz, double Lx, double Ly, double Lz,bool useSparseMatrix, int numEigenvalsToCalc) : TwodHamiltonianClass(Nx,Ny,Lx,Ly,useSparseMatrix,numEigenvalsToCalc)
{
	this->Nz = Nz;
	this->Lz = Lz;
	this->dz = Lz / Nz;
	this->dzDiv2 = this->dz / 2.0;
}

mat*
ThreeDHamiltonianClass::CreateMatrix()
{

	int num = Nx * Ny * Nz;

	mat* M = new mat(num, num, fill::zeros);

	double dxSqrd = System::Math::Pow(dx, 2);
	double dySqrd = System::Math::Pow(dy, 2);
	double dzSqrd = System::Math::Pow(dz, 2);

	double dxFactor = 1.0 / dxSqrd;
	double dyFactor = 1.0 / dySqrd;
	double dzFactor = 1.0 / dzSqrd;

	//cout <<" dssqrd "<< dxSqrd << " " << dySqrd << " " << dzSqrd << endl;

	//There is one equation for each cell in the Nx by Ny grid
	//cellNum is a linear count of the cells in the grid
	//Using a natural ordering for the cells in the grid.

	int Nxy = Nx*Ny;

	int cellNum = 0;

	umat locations;
	vec  values;

	//// batch insertion of two values at (5, 6) and (9, 9)
	//umat locations;
	//locations << 5 << 9 << endr
	//	<< 6 << 9 << endr;

	//vec values;
	//values << 1.5 << 3.2 << endr;

	//sp_mat X(locations, values);

	for (int i = 0; i < num; i++)
	{
		cellNum = i;

		//This is the equation for each cell
		//Each cell equation is a vector of Nx*Ny components, most of which are zero.
		for (int j = 0; j < num; j++)
		{
			//(*M)(i, j) = 0.0;

			//Diagonal element
			if (j == cellNum)
			{
				(*M)(i, j) = 2.0 *dxFactor + 2.0*dyFactor + 2.0*dzFactor;
				//locations << i << j << endr;
				//values << 10.0 << endr;
			}

			//Elements correspoinding to z-cells above and below current cell
			if (j == cellNum - Nxy || j == cellNum + Nxy)
			{
				(*M)(i, j) = -1.0*dzFactor;
			}

			//Elements correspoinding to y-cells above and below current cell
			if (j == cellNum - Nx || j == cellNum + Nx)
			{
				(*M)(i, j) = -1.0 *dyFactor;
			}

			//Element corresponding to x-cell before current cell. 
			//If current cell is first cell in a row, it does not have a before cell.
			if (cellNum % Nx != 0 && j == cellNum - 1)
			{
				(*M)(i, j) = -1.0 * dxFactor;
			}

			//Element corresponding to x-cell after current cell
			//If current cell is last cell in a row it does not have an after cell.
			if ((cellNum + 1) % Nx != 0 && j == cellNum + 1)
			{
				(*M)(i, j) = -1.0 *dxFactor;
			}
		}
	}

	cout << "ThreeDHamiltonianClass CreateMatrix() finished" << endl;

	cout << "Nx " << Nx << " Ny " << Ny << " Nz " << Nz << endl;

	/*double val;
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			val = (*M)(i, j);

			if (val != 0)
				val = 1.0;
			
			cout << val << " ";
		}

		cout << endl;
	}*/
	return M;
}

sp_mat
ThreeDHamiltonianClass::CreateSparseMatrix()
{

	//cout << "ThreeDHamiltonian CreateSparseMatrix()" << endl;

	int num = Nx * Ny * Nz;

	double dxSqrd = System::Math::Pow(dx, 2);
	double dySqrd = System::Math::Pow(dy, 2);
	double dzSqrd = System::Math::Pow(dz, 2);

	double dxFactor = 1.0 / dxSqrd;
	double dyFactor = 1.0 / dySqrd;
	double dzFactor = 1.0 / dzSqrd;

	//cout <<" dssqrd "<< dxSqrd << " " << dySqrd << " " << dzSqrd << endl;

	//There is one equation for each cell in the Nx by Ny grid
	//cellNum is a linear count of the cells in the grid
	//Using a natural ordering for the cells in the grid.

	int Nxy = Nx*Ny;

	int cellNum = 0;

	//// batch insertion of two values at (5, 6) and (9, 9)
	//umat locations;
	//locations << 5 << 9 << endr
	//	<< 6 << 9 << endr;

	//vec values;
	//values << 1.5 << 3.2 << endr;

	//sp_mat X(locations, values);

	double val;

	int ptCnt = 0;

	cout << "Before store locations." << endl;

	for (int i = 0; i < num; i++)
	{
		cellNum = i;

		//This is the equation for each cell
		//Each cell equation is a vector of Nx*Ny components, most of which are zero.
		for (int j = 0; j < num; j++)
		{
			//Diagonal element
			if (j == cellNum)
			{
				ptCnt++;
			}

			//Elements correspoinding to z-cells above and below current cell
			if (j == cellNum - Nxy || j == cellNum + Nxy)
			{
				ptCnt++;
			}

			//Elements correspoinding to y-cells above and below current cell
			if (j == cellNum - Nx || j == cellNum + Nx)
			{
				ptCnt++;
			}

			//Element corresponding to x-cell before current cell. 
			//If current cell is first cell in a row, it does not have a before cell.
			if (cellNum % Nx != 0 && j == cellNum - 1)
			{
				ptCnt++;
			}

			//Element corresponding to x-cell after current cell
			//If current cell is last cell in a row it does not have an after cell.
			if ((cellNum + 1) % Nx != 0 && j == cellNum + 1)
			{
				ptCnt++;
			}
		}
	}

	umat locations(2, ptCnt);
	vec values(ptCnt);

	ptCnt = 0;
	for (int i = 0; i < num; i++)
	{
		cellNum = i;

		//This is the equation for each cell
		//Each cell equation is a vector of Nx*Ny components, most of which are zero.
		for (int j = 0; j < num; j++)
		{
			//Diagonal element
			if (j == cellNum)
			{
				values(ptCnt) = 2.0 *dxFactor + 2.0*dyFactor + 2.0*dzFactor;
				locations(0, ptCnt) = i;
				locations(1, ptCnt) = j;
				ptCnt++;
			}

			//Elements correspoinding to z-cells above and below current cell
			if (j == cellNum - Nxy || j == cellNum + Nxy)
			{
				values(ptCnt) = -1.0*dzFactor;
				locations(0, ptCnt) = i;
				locations(1, ptCnt) = j;
				ptCnt++;
			}

			//Elements correspoinding to y-cells above and below current cell
			if (j == cellNum - Nx || j == cellNum + Nx)
			{
				values(ptCnt)= -1.0 *dyFactor;
				locations(0, ptCnt) = i;
				locations(1, ptCnt) = j;
				ptCnt++;
			}

			//Element corresponding to x-cell before current cell. 
			//If current cell is first cell in a row, it does not have a before cell.
			if (cellNum % Nx != 0 && j == cellNum - 1)
			{
				values(ptCnt) = -1.0 * dxFactor;
				locations(0, ptCnt) = i;
				locations(1, ptCnt) = j;
				ptCnt++;
			}

			//Element corresponding to x-cell after current cell
			//If current cell is last cell in a row it does not have an after cell.
			if ((cellNum + 1) % Nx != 0 && j == cellNum + 1)
			{
				values(ptCnt) = -1.0 *dxFactor;
				locations(0, ptCnt) = i;
				locations(1, ptCnt) = j;
				ptCnt++;
			}
		}
	}

	//locations.print("Locations:");

	//values.print("Values:");

	cout << "After store locations " << endl;

	sp_mat M(locations, values);

	//M.print("SparseM:");

	cout << "ThreeDHamiltonianClass CreateSparseMatrix() finished" << endl;

	cout << "Nx " << Nx << " Ny " << Ny << " Nz " << Nz << endl;

	return M;
}


void
ThreeDHamiltonianClass::WriteToFile(String^ outputFile, int nstate)
{
	StreamWriter^ sw = gcnew StreamWriter(outputFile);

	double xval, yval, zval;

	int index = 0;

	String^ precision = "N7";

	try
	{
		cout << "Creating output file..." << endl;

		sw->WriteLine(String::Format("Eigenstate\t{0}",nstate.ToString()));
		sw->WriteLine(String::Format("Lx\t{0}\tLy\t{1}\tLz\t{2}", Lx.ToString(), Ly.ToString(), Lz.ToString()));
		sw->WriteLine(String::Format("Nx\t{0}\tNy\t{1}\tNz\t{2}", Nx.ToString(), Ny.ToString(), Nz.ToString()));

		String^ str = "Xaxis";

		for (int i = 0; i < 1; i++)
		{
			str += "\tValue";
		}
	
		sw->WriteLine(String::Format("DX\t{0}\tDY\t{1}\tDZ\t{2}", dx.ToString(), dy.ToString(), dz.ToString()));

		//Each eigenrec vector has Nx*Ny values.
		//want to print them as rows.

		cout << "nstate " << nstate << endl;

		CXEigenRec^ er = eigenClass->GetCXEigenRec(nstate);

		cout << "Got EigenRec " << endl;

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
		double dzDiv2 = dz / 2.0;

		//for (int j = 0; j<Nx + 2; j++)
		for(int j=0;j<Nx;j++)
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

		cout << "Nxy " << Nxy << endl;

		//sw->Write("\r\ny-axis");
		for (int k = 0; k < Nz; k++)
		{
			//zval = k*dz;
			zval = dzDiv2 + k*dz;

			//if ( k == 0 )
			//	sw->WriteLine("\r\ny-axis\tZ={0}\r\n", zval.ToString());
			//else
			sw->WriteLine("\r\n\tz=\t{0}\r\n", zval.ToString(precision));

			//There are nRow(formerly Ny) rows in a layer
			for (int j = 0; j < Ny; j++)
			{
				//yval = j*dy;
				yval = dyDiv2 + j*dy;

				str = yval.ToString("N3")+"\t";
				//There are Nx columns
				for (int i = 0; i < Nx; i++)
				{
					//cx_z is complex
					//index = k*Nxy + j * Nx + i;
					cx_probAmp = *(er->vector[index++]);

					//z is real
					prob = System::Math::Sqrt(norm(cx_probAmp));

					str += prob.ToString(precision);
					if (i != Nx - 1)
						str += "\t";
				}

				//str += b.ToString();

				sw->WriteLine(String::Format("{0}", str));
			}
		}

	}//try
	catch (Exception^ e)
	{
		MessageBox::Show("ThreeDHamiltonianClass: exception in WriteFile() : " + e->Message+ " "+index.ToString());
	}
	finally
	{
		sw->Close();
	}
}

void
ThreeDHamiltonianClass::WriteToTestFile(String^ outputFile, int nstate)
{
	StreamWriter^ sw = gcnew StreamWriter(outputFile);

	int index;

	double xval, yval, zval;

	String^ precision = "N7";

	try
	{
		sw->WriteLine(String::Format("Eigenstate\t{0}", nstate.ToString()));
		sw->WriteLine(String::Format("Lx\t{0}\tLy\t{1}\tLz\t{2}", Lx.ToString(), Ly.ToString(), Lz.ToString()));
		sw->WriteLine(String::Format("Nx\t{0}\tNy\t{1}\tNz\t{2}", Nx.ToString(), Ny.ToString(), Nz.ToString()));

		String^ str = "Xaxis";

		for (int i = 0; i < 1; i++)
		{
			str += "\tValue";
		}

		sw->WriteLine(String::Format("DX\t{0}\tDY\t{1}\tDZ\t{2}", dx.ToString(), dy.ToString(), dz.ToString()));

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
		double dzDiv2 = dz / 2.0;

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

		int midX = Nx / 2 + 1;
		int midY = Ny / 2 + 1;
		int midZ = Nz / 2 + 1;

		double diffX, diffY, diffZ;
		double dist;

		//There are Ny rows in a layer
		//There are Nz layers

		int Nxy = Nx*Ny;

		cout << "Nxy " << Nxy << endl;

		double MaxProb = .1;

		//sw->Write("\r\ny-axis");
		for (int k = 0; k < Nz; k++)
		{
			diffZ = (k - midZ);
			diffZ *= diffZ;

			//zval = k*dz;
			zval = dzDiv2 + k*dz;

			//if ( k == 0 )
			//	sw->WriteLine("\r\ny-axis\tZ={0}\r\n", zval.ToString());
			//else
			sw->WriteLine("\r\n\tz=\t{0}\r\n", zval.ToString(precision));

			//There are nRow(formerly Ny) rows in a layer
			for (int i = 0; i < Ny; i++)
			{
				diffY = (i - midY);
				diffY *= diffY;

				//yval = i*dy;
				yval = dyDiv2 + i*dy;

				str = yval.ToString("N3") + "\t";
				//There are Nx columns
				for (int j = 0; j < Nx; j++)
				{
					diffX = j - midX;
					diffX *= diffX;

					dist = System::Math::Sqrt(diffX + diffY + diffZ);

					//cx_z is complex
					index = k*Nxy + i * Nx + j;
					//cx_probAmp = *(er->vector[index]);

					//z is real
					//prob = System::Math::Sqrt(norm(cx_probAmp));

					prob = dist == 0 ? MaxProb : MaxProb / dist;

					str += prob.ToString(precision);
					if (j != Nx - 1)
						str += "\t";
				}

				//str += b.ToString();

				sw->WriteLine(String::Format("{0}", str));
			}
		}

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