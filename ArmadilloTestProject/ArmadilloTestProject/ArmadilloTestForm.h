#pragma once

#include "Test1.h"
#include "Test2.h"
#include "Test3.h"
#include "TwodParticleInBox.h"
#include "TwodHarmonicOscillator.h"
#include "ThreeDHamiltonianClass.h"
#include "ThreeDParticleInBox.h"
#include "ThreeDHarmonicOscillator.h"



//What I had to do to get this to work

//First Configure a C++ Form Application

//I do not have a template for Windows Form Application in C++
//But I can create a C++ Form Application by following the instructions below
//Go Here http://www.bogotobogo.com/cplusplus/application_visual_studio_2013.php
//Create a new project...
//Select Visual C++ CLR type with CLR Empty Project
//Project->Add New Item
//Select UI under Visual C++
//Change form name or leave it same
//Click Add
//Need to create an entry point in a .cpp file
//Here is the code that belongs in the entry point
//See ArmadilloTestForm.cpp for how I created entry point in this project
//Here is example code.
/*
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	RandomNumberGenerator::MyForm form;
	Application::Run(%form);
}
*/

//After the above you have to change the Project Properties
//Under Configuration Properties->LInker->System
// Select Window(/SUBSYSTEM:Windows) **Note that I subsequently changed this to Console(/SUBSYSTEM:CONSOLE) in order to get both a form window and a command prompt window
// Under Configuration Properties->Linker->Advanced->Entry Point type Main.
//Ok that is what I had to do to configure C++ Form app.
//But I had to make a few other changes to be able to use Armadillo
// Had to copy blas_win64_MT.dll and lapack_win64_MT.dll to the ArmadilloTestProject folder (the same folder that has all the .cpp and .h files for the project)
//Under Project Properties
//Had to add ...Documents/Visual Studio 2013/Common/armadillo/include under C/C++->Genearl->Additional Include Directories
//Had to add ...Documents/Visual Studio 2013/Common/armadillo/lib_win64 uner Linker->General->Additional Library Dependencies
//Had to add lapack_win64_MT.lib and blas_win64_MT.lib to Linker->Input->Additional Dependencies



namespace ArmadilloTestProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ArmadilloTestForm
	/// </summary>
	public ref class ArmadilloTestForm : public System::Windows::Forms::Form
	{

		//My Local Variables
		String^ folder = "C:\\users\\jill\\Desktop\\QM\\excel";
		String^ inputFolder = "C:\\users\\jill\\Desktop\\";

		int n_state = 0;

		int Nx = 31;
		int Ny = 31;
		int Nz = 31;

		bool useSparseMatrix = true;
		int numEigenvalsToCalc = 10; //only used if useSparseMatrix = true;

		int dummy = 0;

		double Lx = 30.0;// 600.0;
		double Ly = 30.0;// 600.0;
		double Lz = 30.0;//600.0;
		
		//These k's work for 600 x 600 x 600 box
		double k600 = 1.0E-8;

		//These k's work for a 30 x 30 x 30 box
		//The smaller the box the greater the required restoring force of the harmonic oscillator
		double k30 = .005;

		double KxDefault = k30;
		double KyDefault = k30;
		double KzDefault = k30;

		double Kx = KxDefault;
		double Ky = KyDefault;
		double Kz = KzDefault;

	private: System::Windows::Forms::Button^  sparseMatBtn;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::NumericUpDown^  numEigenvalsToCalcNumUpDn;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Button^  threedParticleInBoxBtn;
	private: System::Windows::Forms::NumericUpDown^  nzNumUpDn;
	private: System::Windows::Forms::NumericUpDown^  lzNumUpDn;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::NumericUpDown^  kzNumUpDn;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Button^  threedHarmonicOscBtn;
	private: System::Windows::Forms::CheckBox^  twoDCheckBox;
	private: System::Windows::Forms::CheckBox^  writeAllFilesCheckBox;
	private: System::Windows::Forms::Button^  writeEigenstateFileBtn;





	private: System::Windows::Forms::CheckBox^  sparseMatrixCheckBox;
			
	public:
		ArmadilloTestForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ArmadilloTestForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  exitBtn;
	private: System::Windows::Forms::Button^  testBtn;
	private: System::Windows::Forms::Button^  test2Btn;
	private: System::Windows::Forms::Button^  test3Btn;
	private: System::Windows::Forms::Button^  twodParticleInBoxBtn;

	private: System::Windows::Forms::Button^  twodHarmonicOscBtn;
	private: System::Windows::Forms::NumericUpDown^  nxNumUpDn;
	private: System::Windows::Forms::NumericUpDown^  nyNumUpDn;
	private: System::Windows::Forms::NumericUpDown^  lxNumUpDn;
	private: System::Windows::Forms::NumericUpDown^  lyNumUpDn;
	private: System::Windows::Forms::NumericUpDown^  nstateNumUpDn;
	private: System::Windows::Forms::NumericUpDown^  kxNumUpDn;
	protected:






	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::NumericUpDown^  kyNumUpDn;

	private: System::Windows::Forms::Label^  label7;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->exitBtn = (gcnew System::Windows::Forms::Button());
			this->testBtn = (gcnew System::Windows::Forms::Button());
			this->test2Btn = (gcnew System::Windows::Forms::Button());
			this->test3Btn = (gcnew System::Windows::Forms::Button());
			this->twodParticleInBoxBtn = (gcnew System::Windows::Forms::Button());
			this->twodHarmonicOscBtn = (gcnew System::Windows::Forms::Button());
			this->nxNumUpDn = (gcnew System::Windows::Forms::NumericUpDown());
			this->nyNumUpDn = (gcnew System::Windows::Forms::NumericUpDown());
			this->lxNumUpDn = (gcnew System::Windows::Forms::NumericUpDown());
			this->lyNumUpDn = (gcnew System::Windows::Forms::NumericUpDown());
			this->nstateNumUpDn = (gcnew System::Windows::Forms::NumericUpDown());
			this->kxNumUpDn = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->kyNumUpDn = (gcnew System::Windows::Forms::NumericUpDown());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->sparseMatBtn = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->numEigenvalsToCalcNumUpDn = (gcnew System::Windows::Forms::NumericUpDown());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->sparseMatrixCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->threedParticleInBoxBtn = (gcnew System::Windows::Forms::Button());
			this->nzNumUpDn = (gcnew System::Windows::Forms::NumericUpDown());
			this->lzNumUpDn = (gcnew System::Windows::Forms::NumericUpDown());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->kzNumUpDn = (gcnew System::Windows::Forms::NumericUpDown());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->threedHarmonicOscBtn = (gcnew System::Windows::Forms::Button());
			this->twoDCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->writeAllFilesCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->writeEigenstateFileBtn = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nxNumUpDn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nyNumUpDn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lxNumUpDn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lyNumUpDn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nstateNumUpDn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kxNumUpDn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kyNumUpDn))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numEigenvalsToCalcNumUpDn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nzNumUpDn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lzNumUpDn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kzNumUpDn))->BeginInit();
			this->SuspendLayout();
			// 
			// exitBtn
			// 
			this->exitBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->exitBtn->Location = System::Drawing::Point(497, 365);
			this->exitBtn->Name = L"exitBtn";
			this->exitBtn->Size = System::Drawing::Size(75, 23);
			this->exitBtn->TabIndex = 0;
			this->exitBtn->Text = L"Exit";
			this->exitBtn->UseVisualStyleBackColor = true;
			this->exitBtn->Click += gcnew System::EventHandler(this, &ArmadilloTestForm::button1_Click);
			// 
			// testBtn
			// 
			this->testBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->testBtn->Location = System::Drawing::Point(457, 11);
			this->testBtn->Name = L"testBtn";
			this->testBtn->Size = System::Drawing::Size(115, 23);
			this->testBtn->TabIndex = 1;
			this->testBtn->Text = L"Test1";
			this->testBtn->UseVisualStyleBackColor = true;
			this->testBtn->Click += gcnew System::EventHandler(this, &ArmadilloTestForm::testBtn_Click);
			// 
			// test2Btn
			// 
			this->test2Btn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->test2Btn->Location = System::Drawing::Point(457, 40);
			this->test2Btn->Name = L"test2Btn";
			this->test2Btn->Size = System::Drawing::Size(115, 23);
			this->test2Btn->TabIndex = 2;
			this->test2Btn->Text = L"Test2";
			this->test2Btn->UseVisualStyleBackColor = true;
			this->test2Btn->Click += gcnew System::EventHandler(this, &ArmadilloTestForm::test2Btn_Click);
			// 
			// test3Btn
			// 
			this->test3Btn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->test3Btn->Location = System::Drawing::Point(457, 69);
			this->test3Btn->Name = L"test3Btn";
			this->test3Btn->Size = System::Drawing::Size(115, 23);
			this->test3Btn->TabIndex = 3;
			this->test3Btn->Text = L"Test3";
			this->test3Btn->UseVisualStyleBackColor = true;
			this->test3Btn->Click += gcnew System::EventHandler(this, &ArmadilloTestForm::test3Btn_Click);
			// 
			// twodParticleInBoxBtn
			// 
			this->twodParticleInBoxBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->twodParticleInBoxBtn->Location = System::Drawing::Point(439, 116);
			this->twodParticleInBoxBtn->Name = L"twodParticleInBoxBtn";
			this->twodParticleInBoxBtn->Size = System::Drawing::Size(133, 23);
			this->twodParticleInBoxBtn->TabIndex = 4;
			this->twodParticleInBoxBtn->Text = L"TwoDParticleInBox";
			this->twodParticleInBoxBtn->UseVisualStyleBackColor = true;
			this->twodParticleInBoxBtn->Click += gcnew System::EventHandler(this, &ArmadilloTestForm::twodParticleInBoxBtn_Click);
			// 
			// twodHarmonicOscBtn
			// 
			this->twodHarmonicOscBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->twodHarmonicOscBtn->Location = System::Drawing::Point(439, 162);
			this->twodHarmonicOscBtn->Name = L"twodHarmonicOscBtn";
			this->twodHarmonicOscBtn->Size = System::Drawing::Size(133, 23);
			this->twodHarmonicOscBtn->TabIndex = 5;
			this->twodHarmonicOscBtn->Text = L"TwodHarmonicOscillator";
			this->twodHarmonicOscBtn->UseVisualStyleBackColor = true;
			this->twodHarmonicOscBtn->Click += gcnew System::EventHandler(this, &ArmadilloTestForm::twodHarmonicOscBtn_Click);
			// 
			// nxNumUpDn
			// 
			this->nxNumUpDn->Location = System::Drawing::Point(84, 13);
			this->nxNumUpDn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->nxNumUpDn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->nxNumUpDn->Name = L"nxNumUpDn";
			this->nxNumUpDn->Size = System::Drawing::Size(120, 20);
			this->nxNumUpDn->TabIndex = 6;
			this->nxNumUpDn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->nxNumUpDn->ValueChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::nxNumUpDn_ValueChanged);
			// 
			// nyNumUpDn
			// 
			this->nyNumUpDn->Location = System::Drawing::Point(84, 43);
			this->nyNumUpDn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->nyNumUpDn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->nyNumUpDn->Name = L"nyNumUpDn";
			this->nyNumUpDn->Size = System::Drawing::Size(120, 20);
			this->nyNumUpDn->TabIndex = 7;
			this->nyNumUpDn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->nyNumUpDn->ValueChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::nyNumUpDn_ValueChanged);
			// 
			// lxNumUpDn
			// 
			this->lxNumUpDn->Location = System::Drawing::Point(84, 107);
			this->lxNumUpDn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->lxNumUpDn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->lxNumUpDn->Name = L"lxNumUpDn";
			this->lxNumUpDn->Size = System::Drawing::Size(120, 20);
			this->lxNumUpDn->TabIndex = 8;
			this->lxNumUpDn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
			this->lxNumUpDn->ValueChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::lxNumUpDn_ValueChanged);
			// 
			// lyNumUpDn
			// 
			this->lyNumUpDn->Location = System::Drawing::Point(84, 143);
			this->lyNumUpDn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->lyNumUpDn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->lyNumUpDn->Name = L"lyNumUpDn";
			this->lyNumUpDn->Size = System::Drawing::Size(120, 20);
			this->lyNumUpDn->TabIndex = 9;
			this->lyNumUpDn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
			this->lyNumUpDn->ValueChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::lyNumUpDn_ValueChanged);
			// 
			// nstateNumUpDn
			// 
			this->nstateNumUpDn->Location = System::Drawing::Point(84, 215);
			this->nstateNumUpDn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->nstateNumUpDn->Name = L"nstateNumUpDn";
			this->nstateNumUpDn->Size = System::Drawing::Size(120, 20);
			this->nstateNumUpDn->TabIndex = 10;
			this->nstateNumUpDn->ValueChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::nstateNumUpDn_ValueChanged);
			// 
			// kxNumUpDn
			// 
			this->kxNumUpDn->DecimalPlaces = 8;
			this->kxNumUpDn->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 524288 });
			this->kxNumUpDn->Location = System::Drawing::Point(84, 254);
			this->kxNumUpDn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->kxNumUpDn->Name = L"kxNumUpDn";
			this->kxNumUpDn->Size = System::Drawing::Size(120, 20);
			this->kxNumUpDn->TabIndex = 11;
			this->kxNumUpDn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 196608 });
			this->kxNumUpDn->ValueChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::kxNumUpDn_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(28, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(20, 13);
			this->label1->TabIndex = 12;
			this->label1->Text = L"Nx";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(28, 50);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(20, 13);
			this->label2->TabIndex = 13;
			this->label2->Text = L"Ny";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(28, 107);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(18, 13);
			this->label3->TabIndex = 14;
			this->label3->Text = L"Lx";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(26, 143);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(18, 13);
			this->label4->TabIndex = 15;
			this->label4->Text = L"Ly";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(12, 217);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(57, 13);
			this->label5->TabIndex = 16;
			this->label5->Text = L"Eigenstate";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(29, 254);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(19, 13);
			this->label6->TabIndex = 17;
			this->label6->Text = L"Kx";
			// 
			// kyNumUpDn
			// 
			this->kyNumUpDn->DecimalPlaces = 8;
			this->kyNumUpDn->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 589824 });
			this->kyNumUpDn->Location = System::Drawing::Point(84, 290);
			this->kyNumUpDn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->kyNumUpDn->Name = L"kyNumUpDn";
			this->kyNumUpDn->Size = System::Drawing::Size(120, 20);
			this->kyNumUpDn->TabIndex = 18;
			this->kyNumUpDn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 196608 });
			this->kyNumUpDn->ValueChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::kyNumUpDn_ValueChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(27, 292);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(19, 13);
			this->label7->TabIndex = 19;
			this->label7->Text = L"Ky";
			// 
			// sparseMatBtn
			// 
			this->sparseMatBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->sparseMatBtn->Location = System::Drawing::Point(16, 365);
			this->sparseMatBtn->Name = L"sparseMatBtn";
			this->sparseMatBtn->Size = System::Drawing::Size(109, 23);
			this->sparseMatBtn->TabIndex = 20;
			this->sparseMatBtn->Text = L"SparseMatrixText";
			this->sparseMatBtn->UseVisualStyleBackColor = true;
			this->sparseMatBtn->Click += gcnew System::EventHandler(this, &ArmadilloTestForm::sparseMatBtn_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->numEigenvalsToCalcNumUpDn);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->sparseMatrixCheckBox);
			this->groupBox1->Location = System::Drawing::Point(243, 20);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(150, 124);
			this->groupBox1->TabIndex = 21;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Sparse Matrix";
			// 
			// numEigenvalsToCalcNumUpDn
			// 
			this->numEigenvalsToCalcNumUpDn->Location = System::Drawing::Point(21, 87);
			this->numEigenvalsToCalcNumUpDn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->numEigenvalsToCalcNumUpDn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numEigenvalsToCalcNumUpDn->Name = L"numEigenvalsToCalcNumUpDn";
			this->numEigenvalsToCalcNumUpDn->Size = System::Drawing::Size(52, 20);
			this->numEigenvalsToCalcNumUpDn->TabIndex = 2;
			this->numEigenvalsToCalcNumUpDn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->numEigenvalsToCalcNumUpDn->ValueChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::numEigenvalsToCalcNumUpDn_ValueChanged);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(19, 49);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(89, 26);
			this->label8->TabIndex = 1;
			this->label8->Text = L"Num eigenvalues\r\nto calculate";
			// 
			// sparseMatrixCheckBox
			// 
			this->sparseMatrixCheckBox->AutoSize = true;
			this->sparseMatrixCheckBox->Checked = true;
			this->sparseMatrixCheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->sparseMatrixCheckBox->Location = System::Drawing::Point(21, 20);
			this->sparseMatrixCheckBox->Name = L"sparseMatrixCheckBox";
			this->sparseMatrixCheckBox->Size = System::Drawing::Size(112, 17);
			this->sparseMatrixCheckBox->TabIndex = 0;
			this->sparseMatrixCheckBox->Text = L"Use Sparse Matrix";
			this->sparseMatrixCheckBox->UseVisualStyleBackColor = true;
			this->sparseMatrixCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::sparseMatrixCheckBox_CheckedChanged);
			// 
			// threedParticleInBoxBtn
			// 
			this->threedParticleInBoxBtn->Location = System::Drawing::Point(439, 229);
			this->threedParticleInBoxBtn->Name = L"threedParticleInBoxBtn";
			this->threedParticleInBoxBtn->Size = System::Drawing::Size(133, 23);
			this->threedParticleInBoxBtn->TabIndex = 22;
			this->threedParticleInBoxBtn->Text = L"ThreeDParticleInBox";
			this->threedParticleInBoxBtn->UseVisualStyleBackColor = true;
			this->threedParticleInBoxBtn->Click += gcnew System::EventHandler(this, &ArmadilloTestForm::threedParticleInBoxBtn_Click);
			// 
			// nzNumUpDn
			// 
			this->nzNumUpDn->Location = System::Drawing::Point(84, 75);
			this->nzNumUpDn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->nzNumUpDn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->nzNumUpDn->Name = L"nzNumUpDn";
			this->nzNumUpDn->Size = System::Drawing::Size(120, 20);
			this->nzNumUpDn->TabIndex = 23;
			this->nzNumUpDn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->nzNumUpDn->ValueChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::nzNumUpDn_ValueChanged);
			// 
			// lzNumUpDn
			// 
			this->lzNumUpDn->Location = System::Drawing::Point(84, 176);
			this->lzNumUpDn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->lzNumUpDn->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->lzNumUpDn->Name = L"lzNumUpDn";
			this->lzNumUpDn->Size = System::Drawing::Size(120, 20);
			this->lzNumUpDn->TabIndex = 24;
			this->lzNumUpDn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
			this->lzNumUpDn->ValueChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::lzNumUpDn_ValueChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(29, 75);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(20, 13);
			this->label9->TabIndex = 25;
			this->label9->Text = L"Nz";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(26, 183);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(18, 13);
			this->label10->TabIndex = 26;
			this->label10->Text = L"Lz";
			// 
			// kzNumUpDn
			// 
			this->kzNumUpDn->DecimalPlaces = 8;
			this->kzNumUpDn->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 589824 });
			this->kzNumUpDn->Location = System::Drawing::Point(84, 328);
			this->kzNumUpDn->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			this->kzNumUpDn->Name = L"kzNumUpDn";
			this->kzNumUpDn->Size = System::Drawing::Size(120, 20);
			this->kzNumUpDn->TabIndex = 27;
			this->kzNumUpDn->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 196608 });
			this->kzNumUpDn->ValueChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::kzNumUpDn_ValueChanged);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(30, 328);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(19, 13);
			this->label11->TabIndex = 28;
			this->label11->Text = L"Kz";
			// 
			// threedHarmonicOscBtn
			// 
			this->threedHarmonicOscBtn->Location = System::Drawing::Point(439, 274);
			this->threedHarmonicOscBtn->Name = L"threedHarmonicOscBtn";
			this->threedHarmonicOscBtn->Size = System::Drawing::Size(133, 23);
			this->threedHarmonicOscBtn->TabIndex = 29;
			this->threedHarmonicOscBtn->Text = L"ThreeDHarmonicOscillator";
			this->threedHarmonicOscBtn->UseVisualStyleBackColor = true;
			this->threedHarmonicOscBtn->Click += gcnew System::EventHandler(this, &ArmadilloTestForm::threedHarmonicOscBtn_Click);
			// 
			// twoDCheckBox
			// 
			this->twoDCheckBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->twoDCheckBox->AutoSize = true;
			this->twoDCheckBox->Location = System::Drawing::Point(264, 162);
			this->twoDCheckBox->Name = L"twoDCheckBox";
			this->twoDCheckBox->Size = System::Drawing::Size(40, 17);
			this->twoDCheckBox->TabIndex = 30;
			this->twoDCheckBox->Text = L"2D";
			this->twoDCheckBox->UseVisualStyleBackColor = true;
			this->twoDCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::twoDCheckBox_CheckedChanged);
			// 
			// writeAllFilesCheckBox
			// 
			this->writeAllFilesCheckBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->writeAllFilesCheckBox->AutoSize = true;
			this->writeAllFilesCheckBox->Location = System::Drawing::Point(262, 196);
			this->writeAllFilesCheckBox->Name = L"writeAllFilesCheckBox";
			this->writeAllFilesCheckBox->Size = System::Drawing::Size(89, 17);
			this->writeAllFilesCheckBox->TabIndex = 31;
			this->writeAllFilesCheckBox->Text = L"Write All Files";
			this->writeAllFilesCheckBox->UseVisualStyleBackColor = true;
			this->writeAllFilesCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ArmadilloTestForm::writeAllFilesCheckBox_CheckedChanged);
			// 
			// writeEigenstateFileBtn
			// 
			this->writeEigenstateFileBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->writeEigenstateFileBtn->Enabled = false;
			this->writeEigenstateFileBtn->Location = System::Drawing::Point(261, 244);
			this->writeEigenstateFileBtn->Name = L"writeEigenstateFileBtn";
			this->writeEigenstateFileBtn->Size = System::Drawing::Size(115, 23);
			this->writeEigenstateFileBtn->TabIndex = 32;
			this->writeEigenstateFileBtn->Text = L"Write Eigenstate File";
			this->writeEigenstateFileBtn->UseVisualStyleBackColor = true;
			this->writeEigenstateFileBtn->Click += gcnew System::EventHandler(this, &ArmadilloTestForm::printEigenstateFileBtn_Click);
			// 
			// ArmadilloTestForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 400);
			this->Controls->Add(this->writeEigenstateFileBtn);
			this->Controls->Add(this->writeAllFilesCheckBox);
			this->Controls->Add(this->twoDCheckBox);
			this->Controls->Add(this->threedHarmonicOscBtn);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->kzNumUpDn);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->lzNumUpDn);
			this->Controls->Add(this->nzNumUpDn);
			this->Controls->Add(this->threedParticleInBoxBtn);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->sparseMatBtn);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->kyNumUpDn);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->kxNumUpDn);
			this->Controls->Add(this->nstateNumUpDn);
			this->Controls->Add(this->lyNumUpDn);
			this->Controls->Add(this->lxNumUpDn);
			this->Controls->Add(this->nyNumUpDn);
			this->Controls->Add(this->nxNumUpDn);
			this->Controls->Add(this->twodHarmonicOscBtn);
			this->Controls->Add(this->twodParticleInBoxBtn);
			this->Controls->Add(this->test3Btn);
			this->Controls->Add(this->test2Btn);
			this->Controls->Add(this->testBtn);
			this->Controls->Add(this->exitBtn);
			this->Name = L"ArmadilloTestForm";
			this->Text = L"ArmadilloTestForm";
			this->Load += gcnew System::EventHandler(this, &ArmadilloTestForm::ArmadilloTestForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nxNumUpDn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nyNumUpDn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lxNumUpDn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lyNumUpDn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nstateNumUpDn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kxNumUpDn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kyNumUpDn))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numEigenvalsToCalcNumUpDn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nzNumUpDn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lzNumUpDn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kzNumUpDn))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma region MyCode

		//double CalcKFromL(double L)
		//{
		//	double result = klSlope*(L - 30) + k30;

		//	return result;
		//}

		bool writeAllFiles = false;

		String^ _filenamePrefix = nullptr;

		ThreeDHamiltonianClass^ _pib = nullptr;

#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	private: System::Void testBtn_Click(System::Object^  sender, System::EventArgs^  e) {

		Test1^ test = gcnew Test1();
		test->CreateTestMatrix();

		//test->ArmadilloTest();

	}
	private: System::Void ArmadilloTestForm_Load(System::Object^  sender, System::EventArgs^  e) {

		nxNumUpDn->Value = Nx;
		nyNumUpDn->Value = Ny;
		nzNumUpDn->Value = Nz;

		lxNumUpDn->Value = (int) Lx;
		lyNumUpDn->Value = (int) Ly;
		lzNumUpDn->Value = (int) Lz;

		kxNumUpDn->Value = (Decimal)Kx;
		kyNumUpDn->Value = (Decimal)Ky;
		kzNumUpDn->Value = (Decimal)Kz;

	}
	private: System::Void test2Btn_Click(System::Object^  sender, System::EventArgs^  e) {
		Test2^ test = gcnew Test2();

		test->CreateTestMatrix();
	}

	private: System::Void test3Btn_Click(System::Object^  sender, System::EventArgs^  e) {
		Test3^ test = gcnew Test3();

		test->CreateTestMatrix();
	}

	private: System::Void twodParticleInBoxBtn_Click(System::Object^  sender, System::EventArgs^  e) {

		cout << "Start TwodParticleInBox " << endl;

		TwodParticleInBox^ pib = gcnew TwodParticleInBox(Nx, Ny, Lx, Ly,useSparseMatrix,numEigenvalsToCalc);

		pib->Solve();

#if DEBUG
		EigenClass^ ec = pib->GetEigenClass();

		array<CXEigenRec^>^ eigenRecs = ec->CXEigenRecs;

		int numEigenRecs = eigenRecs->Length;

		//Find out if any eigenvalues were complex
		for (int i = 0; i < numEigenRecs; i++)
		{
			if (eigenRecs[i]->value->imag() != 0)
				cout << i << " " << eigenRecs[i]->value->real() << " " << eigenRecs[i]->value->imag() << endl;
		}
#endif
		String^ fileName = "TwodParticleInBoxArmadilloOutput.txt";

		String^ outputFile = String::Format("{0}\\{1}", folder, fileName);

		pib->WriteToFile(outputFile, n_state);

		/*
		//pibClass.WriteMatrix(outputFile);

		//Write the potential function
		fileName = "HarmonicOscillator2DPotential.txt";
		outputFile = String.Format("{0}\\{1}", folder, fileName);
		pibClass.WritePotentialEnergy(outputFile);
		*/

		//Free unmanaged memory
		pib->Delete();
		cout << "End TwodParticleInBox " << endl;
	}

	private: System::Void nxNumUpDn_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		Nx = (int)nxNumUpDn->Value;

	}

	private: System::Void nyNumUpDn_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

		Ny = (int)nyNumUpDn->Value;

	}

	private: System::Void lxNumUpDn_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

		Lx = (double)lxNumUpDn->Value;

	}

	private: System::Void lyNumUpDn_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

		Ly = (double)lyNumUpDn->Value;
	
	}

	private: System::Void nstateNumUpDn_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

		n_state = (int)nstateNumUpDn->Value;
	}

	private: System::Void kxNumUpDn_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

		Kx = (double)kxNumUpDn->Value;
		kyNumUpDn->Value = (Decimal)Kx;
		kzNumUpDn->Value = (Decimal)Kx;

	}

	private: System::Void kyNumUpDn_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

		Ky = (double)kyNumUpDn->Value;


	}

	private: System::Void twodHarmonicOscBtn_Click(System::Object^  sender, System::EventArgs^  e) {

		cout << "Start TwodHarmonicOscillator" << endl;
		TwodHarmonicOscillator^ pib = gcnew TwodHarmonicOscillator(Nx, Ny, Lx, Ly,Kx,Ky,useSparseMatrix,numEigenvalsToCalc);
	
		pib->Solve();

#if DEBUG
		EigenClass^ ec = pib->GetEigenClass();

		array<CXEigenRec^>^ eigenRecs = ec->CXEigenRecs;

		int numEigenRecs = eigenRecs->Length;

		//Find out if any eigenvalues were complex
		for (int i = 0; i < numEigenRecs; i++)
		{
			if (eigenRecs[i]->value->imag() != 0)
				cout << i << " " << eigenRecs[i]->value->real() << " " << eigenRecs[i]->value->imag() << endl;
		}
#endif

		String^ fileName = "TwodHarmonicOscillatorArmadilloOutput.txt";

		String^ outputFile = String::Format("{0}\\{1}", folder, fileName);

		pib->WriteToFile(outputFile, n_state);

		/*
		//pibClass.WriteMatrix(outputFile);*/

		//Write the potential function
		fileName = "TwodHarmonicOscillatorArmadilloPotential.txt";
		outputFile = String::Format("{0}\\{1}", folder, fileName);
		pib->WritePotentialEnergy(outputFile);
		
		//Free unmanaged memory
		pib->Delete();
		cout << "End TwodHarmonicOscillator" << endl;
	}

private: System::Void sparseMatBtn_Click(System::Object^  sender, System::EventArgs^  e) {

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

	
	sp_mat B(A);// = sprandu<sp_mat>(100, 200, 0.1);// speye<sp_mat>(5, 5);

	B.print("Sparse A");

	cout << B.n_elem << " " << B.n_nonzero << endl;
}
private: System::Void sparseMatrixCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	useSparseMatrix = sparseMatrixCheckBox->Checked;
}
private: System::Void numEigenvalsToCalcNumUpDn_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

	numEigenvalsToCalc = (int) numEigenvalsToCalcNumUpDn->Value;
}
private: System::Void threedParticleInBoxBtn_Click(System::Object^  sender, System::EventArgs^  e) {

	cout << "Start ThreedParticleInBox" << endl;

	if (_pib != nullptr)
		_pib->Delete();

	_pib = gcnew ThreeDParticleInBox(Nx, Ny, Nz, Lx, Ly, Lz,useSparseMatrix, numEigenvalsToCalc);
	
	_pib->Solve();

	_filenamePrefix = "ThreeDParticleInBoxNstate_";

	if (writeAllFiles)
	{
		int limit = System::Math::Min(numEigenvalsToCalc, 10);
		for (int i = 0; i < limit; i++)
		{
			String^ fileName = _filenamePrefix + i.ToString() + ".txt";

			String^ outputFile = String::Format("{0}\\{1}", folder, fileName);

			_pib->WriteToFile(outputFile, i);
		}
	}
	else
	{
		String^ fileName = _filenamePrefix + n_state.ToString() + ".txt";

		String^ outputFile = String::Format("{0}\\{1}", folder, fileName);

		_pib->WriteToFile(outputFile, n_state);
	}

	//String^ fileName = "ThreeDParticleInBoxNstate_" + n_state.ToString() + ".txt";

	//String^ outputFile = String::Format("{0}\\{1}", folder, fileName);
	//pib->WriteToFile(outputFile, n_state);
	////pib->WriteToTestFile(outputFile, n_state);


	//Free unmanaged memory
	//_pib->Delete();
	cout << "End ThreeDParticleInBox" << endl;

	writeEigenstateFileBtn->Enabled = true;

}
private: System::Void nzNumUpDn_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	Nz = (int)nzNumUpDn->Value;
}
private: System::Void lzNumUpDn_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	Lz = (double)lzNumUpDn->Value;
	
}
private: System::Void kzNumUpDn_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	Kz = (double)kzNumUpDn->Value;
}
private: System::Void threedHarmonicOscBtn_Click(System::Object^  sender, System::EventArgs^  e) {

	/*
	The following parameters work good for the 3D harmonic oscillator
	Set Kx=Ky=Kz = .001
	Set Lx=Ly=Lz = 60
	Then change the camera location in the Simple3DViewer to zoom in

	Or
	Set Kx=Ky=Kz = .00000001
	Set Lx=Ly=Lz = 600.
	Then change the camera location in Simple3DViewer to zoom out.
	*/
	cout << "Start ThreedHarmonicOscillator" << endl;

	if (_pib != nullptr)
		_pib->Delete();
	
	_pib = gcnew ThreeDHarmonicOscillator(Nx, Ny, Nz, Lx, Ly, Lz, Kx,Ky,Kz,useSparseMatrix, numEigenvalsToCalc);

	_pib->Solve();

	_filenamePrefix = "ThreeDHarmonicOscillatorNstate_";

	if (writeAllFiles)
	{
		int limit = System::Math::Min(numEigenvalsToCalc, 10);
		for (int i = 0; i < limit; i++)
		{
			String^ fileName = _filenamePrefix + i.ToString() + ".txt";

			String^ outputFile = String::Format("{0}\\{1}", folder, fileName);

			_pib->WriteToFile(outputFile, i);
		}
	}
	else
	{
		String^ fileName = _filenamePrefix + n_state.ToString() + ".txt";

		String^ outputFile = String::Format("{0}\\{1}", folder, fileName);

		_pib->WriteToFile(outputFile, n_state);
	}


	//Free unmanaged memory
	//_pib->Delete();
	cout << "End ThreeDHarmonicOscillator" << endl;
	writeEigenstateFileBtn->Enabled = true;
}
private: System::Void twoDCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (twoDCheckBox->Checked)
		nzNumUpDn->Value = 1;
	else
		nzNumUpDn->Value = nxNumUpDn->Value;
}
private: System::Void writeAllFilesCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	writeAllFiles = writeAllFilesCheckBox->Checked;
}
private: System::Void printEigenstateFileBtn_Click(System::Object^  sender, System::EventArgs^  e) {

	String^ fileName = _filenamePrefix + n_state.ToString() + ".txt";

	String^ outputFile = String::Format("{0}\\{1}", folder, fileName);

	_pib->WriteToFile(outputFile, n_state);
}
};//class
}//namespace