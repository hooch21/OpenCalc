#include "Test3.h"
#include <armadillo>
#include "EigenClass.h"

using namespace System::Windows::Forms;

// This is for armadillo
using namespace std;
using namespace arma;

using namespace EigenSpace;

Test3::Test3()
{
}

void Test3::CreateTestMatrix()
{

	//CONFIRMED!

	//implements
	// http://www.sosmath.com/matrix/eigen2/eigen2.html
	//eigenvalues = -4,0,3
	//eigenvectors = {-1,2,1}, {1,6,-13}, {2,3,-2}

	//MessageBox.Show("Test3Class override CreateTestMatrix()");

	mat A(3, 3);

	A(0, 0) = 1.0;
	A(0, 1) = 2.0;
	A(0, 2) = 1.0;

	A(1, 0) = 6.0;
	A(1, 1) = -1.0;
	A(1, 2) = 0.0;

	A(2, 0) = -1.0;
	A(2, 1) = -2.0;
	A(2, 2) = -1.0;
	
	A.print("A:");

	//A is a dense, non-symmetric matrix. 
	//Must use eig_gen, not eig_sym. eig_sym is for a dense symmetric/hermitian matrix
	cx_vec eigval;
	cx_mat eigvec;

	eig_gen(eigval, eigvec, A);

	eigval.print("Eigenvalues:");

	eigvec.print("Eigenvectors:");

	//sparse matrix test
	sp_mat B(A);

	EigenClass^ ec = gcnew EigenClass(B, 1);

	B.print("Sparse A:");

	eigs_gen(eigval, eigvec, B,1,"sm");

	eigval.print("Eigenvalues:");

	eigvec.print("Eigenvectors:");
}