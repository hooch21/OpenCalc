#pragma once

namespace DiCube {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DiCubeForm
	/// </summary>
	public ref class DiCubeForm : public System::Windows::Forms::Form
	{
	public:
		DiCubeForm(void)
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
		~DiCubeForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  exitBtn;
	private: System::Windows::Forms::Button^  zRotateRightBtn;
	private: System::Windows::Forms::Button^  yRotateRightBtn;
	private: System::Windows::Forms::Button^  xRotateRightBtn;
	private: System::Windows::Forms::Button^  xRotateLeftBtn;
	private: System::Windows::Forms::Label^  zAngLabel;
	private: System::Windows::Forms::Label^  yAngLabel;
	private: System::Windows::Forms::Label^  xAngLabel;
	private: System::Windows::Forms::Button^  zRotateLeftBtn;
	private: System::Windows::Forms::Button^  yRotateLeftBtn;
	private: System::Windows::Forms::Button^  drawCubeBtn;

	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  fileNameLabel;
	protected:

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(DiCubeForm::typeid));
			this->exitBtn = (gcnew System::Windows::Forms::Button());
			this->zRotateRightBtn = (gcnew System::Windows::Forms::Button());
			this->yRotateRightBtn = (gcnew System::Windows::Forms::Button());
			this->xRotateRightBtn = (gcnew System::Windows::Forms::Button());
			this->xRotateLeftBtn = (gcnew System::Windows::Forms::Button());
			this->zAngLabel = (gcnew System::Windows::Forms::Label());
			this->yAngLabel = (gcnew System::Windows::Forms::Label());
			this->xAngLabel = (gcnew System::Windows::Forms::Label());
			this->zRotateLeftBtn = (gcnew System::Windows::Forms::Button());
			this->yRotateLeftBtn = (gcnew System::Windows::Forms::Button());
			this->drawCubeBtn = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->fileNameLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// exitBtn
			// 
			this->exitBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->exitBtn->Location = System::Drawing::Point(791, 636);
			this->exitBtn->Name = L"exitBtn";
			this->exitBtn->Size = System::Drawing::Size(75, 23);
			this->exitBtn->TabIndex = 0;
			this->exitBtn->Text = L"Exit";
			this->exitBtn->UseVisualStyleBackColor = true;
			this->exitBtn->Click += gcnew System::EventHandler(this, &DiCubeForm::exitBtn_Click);
			// 
			// zRotateRightBtn
			// 
			this->zRotateRightBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->zRotateRightBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"zRotateRightBtn.BackgroundImage")));
			this->zRotateRightBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->zRotateRightBtn->Location = System::Drawing::Point(835, 179);
			this->zRotateRightBtn->Name = L"zRotateRightBtn";
			this->zRotateRightBtn->Size = System::Drawing::Size(31, 23);
			this->zRotateRightBtn->TabIndex = 21;
			this->zRotateRightBtn->UseVisualStyleBackColor = true;
			// 
			// yRotateRightBtn
			// 
			this->yRotateRightBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->yRotateRightBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"yRotateRightBtn.BackgroundImage")));
			this->yRotateRightBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->yRotateRightBtn->Location = System::Drawing::Point(835, 127);
			this->yRotateRightBtn->Name = L"yRotateRightBtn";
			this->yRotateRightBtn->Size = System::Drawing::Size(31, 23);
			this->yRotateRightBtn->TabIndex = 20;
			this->yRotateRightBtn->UseVisualStyleBackColor = true;
			// 
			// xRotateRightBtn
			// 
			this->xRotateRightBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->xRotateRightBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"xRotateRightBtn.BackgroundImage")));
			this->xRotateRightBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->xRotateRightBtn->Location = System::Drawing::Point(835, 84);
			this->xRotateRightBtn->Name = L"xRotateRightBtn";
			this->xRotateRightBtn->Size = System::Drawing::Size(31, 23);
			this->xRotateRightBtn->TabIndex = 19;
			this->xRotateRightBtn->UseVisualStyleBackColor = true;
			// 
			// xRotateLeftBtn
			// 
			this->xRotateLeftBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->xRotateLeftBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"xRotateLeftBtn.BackgroundImage")));
			this->xRotateLeftBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->xRotateLeftBtn->Location = System::Drawing::Point(791, 84);
			this->xRotateLeftBtn->Name = L"xRotateLeftBtn";
			this->xRotateLeftBtn->Size = System::Drawing::Size(31, 23);
			this->xRotateLeftBtn->TabIndex = 13;
			this->xRotateLeftBtn->UseVisualStyleBackColor = true;
			// 
			// zAngLabel
			// 
			this->zAngLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->zAngLabel->AutoSize = true;
			this->zAngLabel->Location = System::Drawing::Point(712, 189);
			this->zAngLabel->Name = L"zAngLabel";
			this->zAngLabel->Size = System::Drawing::Size(35, 13);
			this->zAngLabel->TabIndex = 18;
			this->zAngLabel->Text = L"label3";
			// 
			// yAngLabel
			// 
			this->yAngLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->yAngLabel->AutoSize = true;
			this->yAngLabel->Location = System::Drawing::Point(712, 137);
			this->yAngLabel->Name = L"yAngLabel";
			this->yAngLabel->Size = System::Drawing::Size(35, 13);
			this->yAngLabel->TabIndex = 17;
			this->yAngLabel->Text = L"label2";
			// 
			// xAngLabel
			// 
			this->xAngLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->xAngLabel->AutoSize = true;
			this->xAngLabel->Location = System::Drawing::Point(712, 89);
			this->xAngLabel->Name = L"xAngLabel";
			this->xAngLabel->Size = System::Drawing::Size(35, 13);
			this->xAngLabel->TabIndex = 16;
			this->xAngLabel->Text = L"label1";
			// 
			// zRotateLeftBtn
			// 
			this->zRotateLeftBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->zRotateLeftBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"zRotateLeftBtn.BackgroundImage")));
			this->zRotateLeftBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->zRotateLeftBtn->Location = System::Drawing::Point(791, 179);
			this->zRotateLeftBtn->Name = L"zRotateLeftBtn";
			this->zRotateLeftBtn->Size = System::Drawing::Size(31, 23);
			this->zRotateLeftBtn->TabIndex = 15;
			this->zRotateLeftBtn->UseVisualStyleBackColor = true;
			// 
			// yRotateLeftBtn
			// 
			this->yRotateLeftBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->yRotateLeftBtn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"yRotateLeftBtn.BackgroundImage")));
			this->yRotateLeftBtn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->yRotateLeftBtn->Location = System::Drawing::Point(791, 127);
			this->yRotateLeftBtn->Name = L"yRotateLeftBtn";
			this->yRotateLeftBtn->Size = System::Drawing::Size(31, 23);
			this->yRotateLeftBtn->TabIndex = 14;
			this->yRotateLeftBtn->UseVisualStyleBackColor = true;
			// 
			// drawCubeBtn
			// 
			this->drawCubeBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->drawCubeBtn->Location = System::Drawing::Point(791, 24);
			this->drawCubeBtn->Name = L"drawCubeBtn";
			this->drawCubeBtn->Size = System::Drawing::Size(75, 23);
			this->drawCubeBtn->TabIndex = 22;
			this->drawCubeBtn->Text = L"Draw Cube";
			this->drawCubeBtn->UseVisualStyleBackColor = true;
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Location = System::Drawing::Point(30, 24);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(645, 608);
			this->panel1->TabIndex = 23;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(30, 641);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 23);
			this->label1->TabIndex = 24;
			this->label1->Text = L"File:";
			// 
			// fileNameLabel
			// 
			this->fileNameLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->fileNameLabel->AutoSize = true;
			this->fileNameLabel->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->fileNameLabel->Location = System::Drawing::Point(77, 641);
			this->fileNameLabel->Name = L"fileNameLabel";
			this->fileNameLabel->Size = System::Drawing::Size(41, 23);
			this->fileNameLabel->TabIndex = 25;
			this->fileNameLabel->Text = L"File:";
			// 
			// DiCubeForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(878, 671);
			this->Controls->Add(this->fileNameLabel);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->drawCubeBtn);
			this->Controls->Add(this->zRotateRightBtn);
			this->Controls->Add(this->yRotateRightBtn);
			this->Controls->Add(this->xRotateRightBtn);
			this->Controls->Add(this->xRotateLeftBtn);
			this->Controls->Add(this->zAngLabel);
			this->Controls->Add(this->yAngLabel);
			this->Controls->Add(this->xAngLabel);
			this->Controls->Add(this->zRotateLeftBtn);
			this->Controls->Add(this->yRotateLeftBtn);
			this->Controls->Add(this->exitBtn);
			this->Name = L"DiCubeForm";
			this->Text = L"DiCubeForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void exitBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	};
}
