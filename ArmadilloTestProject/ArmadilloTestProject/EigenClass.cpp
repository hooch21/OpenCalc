#include "EigenClass.h"


using namespace System;
using namespace System::Collections::Generic;
//using namespace System::Linq;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;
using namespace System::Collections;


using namespace EigenSpace;

EigenClass::EigenClass(mat A)
{
	cx_vec eigenvalues;
	cx_mat eigenvectors;

	eig_gen(eigenvalues, eigenvectors, A);

	numEigenValues = eigenvalues.n_elem;

	cout << "Num Eigenvalues " << numEigenValues << endl;

	eigenvalues.print("Eigenvalues");

	int numEigenvectors = eigenvectors.n_cols;

	if (numEigenValues != numEigenvectors)
		cout << "Uh oh. The number of eigenvalue does not equal number of eigenvectors. And they should." << endl;

	cout << "EigenClass dense matrix. Num eigenvectors " << numEigenvectors << endl;

	//create an array of CXEigenRec
	cxrecs = gcnew cli::array<CXEigenRec^> (numEigenValues);

	int nRows = numEigenValues;
	int nCols = numEigenValues;
	for (int j = 0; j < nCols; j++)
	{
		cxrecs[j] = gcnew CXEigenRec;
		cxrecs[j]->value = new cx_double(eigenvalues[j]);
		cxrecs[j]->vector = gcnew cli::array<cx_double*>(numEigenValues);

		//eigenvectors are stored in columns
		for (int i = 0; i < nRows; i++)
		{
			cxrecs[j]->vector[i] = new cx_double(eigenvectors.at(i, j));

			//MessageBox::Show(cxrecs[j]->vector[i]->real().ToString() + " " + cxrecs[j]->vector[i]->imag().ToString());
		}
	}
	CXEigenvalueComparer^ eigenvalComparer = gcnew CXEigenvalueComparer();

	Array::Sort(cxrecs, eigenvalComparer);

#ifdef DEBUG
	for (int i = 0; i < numEigenValues; i++)
	{
		//String^ str = "";
		cout << endl;
		for (int j = 0; j < numEigenValues; j++)
		{
			//str += cxrecs[i]->vector[j]->real().ToString() + "\t";
			//MessageBox::Show(cxrecs[i]->vector[j]->real().ToString() + " " + cxrecs[i]->vector[j]->imag().ToString());
			cout << cxrecs[i]->vector[j]->real() << " " << cxrecs[i]->vector[j]->imag() << endl;

		}
	}
#endif
}

EigenClass::EigenClass(sp_mat A,int numEigenvalsToCalc)
{
	cx_vec eigenvalues;
	cx_mat eigenvectors;

	cout << "Calculating " << numEigenvalsToCalc << " eigenvalues" << endl;

	//double tol = 1.0E-5;

	//This works with cx_vec and cx_mat. eigs_sym only works with vec and mat
	eigs_gen(eigenvalues, eigenvectors, A, numEigenvalsToCalc, "sm");//, tol);

	eigenvalues.print("Eigenvalue array:");

	numEigenValues = eigenvalues.n_elem;

	int numEigenvectors = eigenvectors.n_cols;

	int numPtsInEigenvector = eigenvectors.n_rows;

	cout << "EigenClass for sparse matrix. Num eigenvectors " << numEigenvectors << endl;

	cout << "EigenClass for sparse matrix. Num Points In Eigenvector " << numPtsInEigenvector << endl;

	//create an array of EigenRec

	cxrecs = gcnew cli::array<CXEigenRec^>(numEigenValues);

	for (int j = 0; j < numEigenvectors; j++)
	{
		cxrecs[j] = gcnew CXEigenRec;
		cxrecs[j]->value = new cx_double(eigenvalues[j]);
		cxrecs[j]->vector = gcnew cli::array<cx_double*>(numPtsInEigenvector);

		//eigenvectors are stored in columns
		for (int i = 0; i < numPtsInEigenvector; i++)
		{
			cxrecs[j]->vector[i] = new cx_double(eigenvectors.at(i, j));
		}
	}

	//Do not think I have to sort
	CXEigenvalueComparer^ eigenvalComparer = gcnew CXEigenvalueComparer();

	cout << "Before sort:" << endl;
	for (int i = 0; i < numEigenvectors; i++)
	{

		cout << cxrecs[i]->value->real() << " " << cxrecs[i]->value->imag() << endl;
		//String^ str = "";
		//for (int j = 0; j < numPtsInEigenvector; j++)
		//{
		//	//str += cxrecs[i]->vector[j]->real().ToString() + "\t";
		//	MessageBox::Show(cxrecs[i]->vector[j]->real().ToString() + " " + cxrecs[i]->vector[j]->imag().ToString());

		//}
	}

	Array::Sort(cxrecs, eigenvalComparer);

	cout << "After sort:" << endl;

	for (int i = 0; i < numEigenvectors; i++)
	{

		cout << cxrecs[i]->value->real() << " " << cxrecs[i]->value->imag() << endl;
		//String^ str = "";
		//for (int j = 0; j < numPtsInEigenvector; j++)
		//{
		//	//str += cxrecs[i]->vector[j]->real().ToString() + "\t";
		//	MessageBox::Show(cxrecs[i]->vector[j]->real().ToString() + " " + cxrecs[i]->vector[j]->imag().ToString());

		//}
	}
}

void
EigenClass::Delete()
{
	//Delete all the unmanaged memory
	for (int i = 0; i < cxrecs->Length; i++)
	{
		CXEigenRec^ er = cxrecs[i];

		delete er->value;

		for (int j = 0; j < er->vector->Length; j++)
			delete er->vector[j];

	}

	cout << "EigenClass: Deleted memory on heap" << endl;
}

CXEigenRec^ 
EigenClass::GetCXEigenRec(int i)
{
	return cxrecs[i];
}

bool
EigenClass::IsCloseToZero(double val)
{
	//arma has a Math namespace so have to specify System::Math
	if ( System::Math::Abs(val) < 1.0E-12)
		return true;
	else
		return false;
}

