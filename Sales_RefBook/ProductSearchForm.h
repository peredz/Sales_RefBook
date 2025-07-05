#pragma once

#include <Windows.h>
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include "DataValidation.h"


namespace SalesRefBook
{
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace DataValidation;


    public ref class SearchPatientForm : public Form
    {
    public:
        property String^ BarCode { String^ get() { return textBoxBarCode->Text; } };

        SearchPatientForm()
        {
            InitializeComponent();
            this->Text = "Ввод штрих-код";
        }

    protected:
        ~SearchPatientForm() { if (components) delete components; }

    private:
        Label^ labelBarCode;
        TextBox^ textBoxBarCode;
        Button^ buttonOK;
        Button^ buttonCancel;
        System::ComponentModel::Container^ components;

        void InitializeComponent()
        {
            this->components = gcnew System::ComponentModel::Container();
            this->labelBarCode = gcnew System::Windows::Forms::Label();
            this->textBoxBarCode = gcnew System::Windows::Forms::TextBox();
            this->buttonOK = gcnew System::Windows::Forms::Button();
            this->buttonCancel = gcnew System::Windows::Forms::Button();
            this->SuspendLayout();

            // labelBarCode
            this->labelBarCode->AutoSize = true;
            this->labelBarCode->Location = System::Drawing::Point(12, 15);
            this->labelBarCode->Name = L"labelBarCode";
            this->labelBarCode->Size = System::Drawing::Size(110, 13);
            this->labelBarCode->TabIndex = 0;
            this->labelBarCode->Text = L"Штрих-код (13 цифр):";

            // textBoxBarCode
            this->textBoxBarCode->Location = System::Drawing::Point(128, 12);
            this->textBoxBarCode->Name = L"textBoxBarCode";
            this->textBoxBarCode->Size = System::Drawing::Size(200, 20);
            this->textBoxBarCode->TabIndex = 1;
            this->textBoxBarCode->MaxLength = 19;

            // buttonOK
            //this->buttonOK->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->buttonOK->Location = System::Drawing::Point(128, 45);
            this->buttonOK->Name = L"buttonOK";
            this->buttonOK->Size = System::Drawing::Size(90, 25);
            this->buttonOK->TabIndex = 2;
            this->buttonOK->Text = L"Найти";
            this->buttonOK->UseVisualStyleBackColor = true;
            this->buttonOK->Click += gcnew System::EventHandler(this, &SearchPatientForm::buttonOK_Click);

            // buttonCancel
            this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->buttonCancel->Location = System::Drawing::Point(238, 45);
            this->buttonCancel->Name = L"buttonCancel";
            this->buttonCancel->Size = System::Drawing::Size(90, 25);
            this->buttonCancel->TabIndex = 3;
            this->buttonCancel->Text = L"Отмена";
            this->buttonCancel->UseVisualStyleBackColor = true;

            // SearchPatientForm
            this->AcceptButton = this->buttonOK;
            this->CancelButton = this->buttonCancel;
            this->ClientSize = System::Drawing::Size(340, 80);
            this->Controls->Add(this->buttonCancel);
            this->Controls->Add(this->buttonOK);
            this->Controls->Add(this->textBoxBarCode);
            this->Controls->Add(this->labelBarCode);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"SearchPatientForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->ResumeLayout(false);
            this->PerformLayout();
        }

    private:
    private: System::Void buttonOK_Click(System::Object^ sender, System::EventArgs^ e)
    {
        std::string barCode = msclr::interop::marshal_as<std::string>(textBoxBarCode->Text);

        if (!validateBarcode(barCode))
        {
            MessageBox::Show("Неверный формат штрих-кода!",
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        this->DialogResult = Windows::Forms::DialogResult::OK;
        this->Close();
    }
    };
}