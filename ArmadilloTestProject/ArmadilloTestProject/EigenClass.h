#pragma once
#include <armadillo>

using namespace System;
using namespace std;
using namespace arma;

namespace EigenSpace
{ 
	ref struct EigenRec
	{
		double value;
		double norm;
		cli::array<double>^ vector;

	};

	ref struct CXEigenRec
	{
		cx_double* value;
		double norm;
		cli::array<cx_double*>^ vector;

	};

	ref class CXEigenvalueComparer : System::Collections::IComparer
	{
		public:
			virtual int Compare(Object^ obj1, Object^ obj2)
			{
				CXEigenRec^ er1 = (CXEigenRec^)obj1;
				CXEigenRec^ er2 = (CXEigenRec^)obj2;

				double r1 = er1->value->real();
				double r2 = er2->value->real();

				if (r1 < r2)
					return -1;
				else if (r1 > r2)
					return 1;
				else
					return 0;
			}
	};

	ref class EigenClass
	{
		private:
		
			cli::array<CXEigenRec^>^ cxrecs;

			int numEigenValues = 0;

		public:
			
			EigenClass(mat A);
			EigenClass(sp_mat A, int numEigenvalsToCalc);

			//Need this to delete unmanaged memory allocated on heap
			void Delete();
			

			CXEigenRec^ GetCXEigenRec(int i);


		//property
		property int NumEigenValues
		{
			int get() { return numEigenValues; }
		}

		property cli::array<CXEigenRec^>^  CXEigenRecs
		{
			cli::array<CXEigenRec^>^  get() { return cxrecs; }
		}

		private:
			bool	IsCloseToZero(double val);

	};
}

