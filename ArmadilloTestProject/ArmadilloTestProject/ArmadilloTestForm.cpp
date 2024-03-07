#include "ArmadilloTestForm.h"

using namespace System;
using namespace System::Windows::Forms;

//armadillo linear algebra
//http://arma.sourceforge.net/

//http://www.bogotobogo.com/cplusplus/application_visual_studio_2013.php

[STAThread]
void Main(cli::array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	ArmadilloTestProject::ArmadilloTestForm  form;
	Application::Run(%form);
}