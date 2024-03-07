#include "Test2.h"
#include <armadillo>

using namespace System::Windows::Forms;

// This is for armadillo
using namespace std;
using namespace arma;


Test2::Test2()
{
}

void Test2::CreateTestMatrix()
{
	//CONFIRMED!

	//This implements
	//http://www.ms.uky.edu/~lee/amspekulin/eigenvectors.pdf
	//Result Lambda = -2, lambda = 1;
	//eigenvector for lambda = -2 is {3,2}
	//eigenvector for lambda =  1 is {2,1}

	mat A(2, 2);

	A(0, 0) = 10.0;
	A(0, 1) = -18.0;
	A(1, 0) = 6.0;
	A(1, 1) = -11.0;

	A.print("A:");

	//A is a dense, non-symmetric matrix. 
	//Must use eig_gen, not eig_sym. eig_sym is for a dense symmetric/hermitian matrix
	cx_vec eigval;
	cx_mat eigvec;

	eig_gen(eigval, eigvec, A);

	//eig_sym(eigval, eigvec, A);

	eigval.print("Eigenvalues:");

	eigvec.print("Eigenvectors:");

}
