#pragma once
#include <Windows.h>
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include "DataValidation.h"
#include <cctype>

namespace SalesRefBook
{
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class SellForm : public Form
    {
    public:
        property String^ Barcode { String^ get() { return textBoxBarcode->Text; } }
        property String^ CashRegister { String^ get() { return textBoxCashRegister->Text; } }
        property String^ ProductAmount { String^ get() { return textBoxProductAmount->Text; } }
        property String^ SellDate { String^ get() { return textBoxSellDate->Text; } }

        SellForm(String^ title)
        {
            InitializeComponent();
            this->Text = title;
        }

    protected:
        ~SellForm() { if (components) delete components; }

    private:
        Label^ labelBarcode;
        Label^ labelCashRegister;
        Label^ labelProductAmount;


        Label^ labelSellDate;
        TextBox^ textBoxBarcode;
        TextBox^ textBoxCashRegister;
        TextBox^ textBoxProductAmount;

        TextBox^ textBoxSellDate;
        Button^ buttonOK;
        Button^ buttonCancel;
        System::ComponentModel::Container^ components;

        void InitializeComponent()
        {
            this->components = gcnew System::ComponentModel::Container();
            this->labelBarcode = gcnew Label();
            this->labelCashRegister = gcnew Label();
            this->labelProductAmount = gcnew Label();
            this->labelSellDate = gcnew Label();
            this->textBoxBarcode = gcnew TextBox();
            this->textBoxCashRegister = gcnew TextBox();
            this->textBoxProductAmount = gcnew TextBox();
            this->textBoxSellDate = gcnew TextBox();
            this->buttonOK = gcnew Button();
            this->buttonCancel = gcnew Button();
            this->SuspendLayout();

            // Настройка элементов формы
            // labelBarcode
            this->labelBarcode->AutoSize = true;
            this->labelBarcode->Location = Point(12, 15);
            this->labelBarcode->Text = L"ШТрих-код (13 цифр):";

            // labelCashRegister
            this->labelCashRegister->AutoSize = true;
            this->labelCashRegister->Location = Point(12, 41);
            this->labelCashRegister->Text = L"Номер кассы:";

            // labelProductAmount
            this->labelProductAmount->AutoSize = true;
            this->labelProductAmount->Location = Point(12, 67);
            this->labelProductAmount->Text = L"Количество:";

            // labelSellDate
            this->labelSellDate->AutoSize = true;
            this->labelSellDate->Location = Point(12, 145);
            this->labelSellDate->Text = L"Дата покупки:";

            // textBoxBarcode
            this->textBoxBarcode->Location = Point(150, 12);
            this->textBoxBarcode->Size = Drawing::Size(200, 20);
            this->textBoxBarcode->MaxLength = 19;

            // textBoxCashRegister
            this->textBoxCashRegister->Location = Point(150, 38);
            this->textBoxCashRegister->Size = Drawing::Size(200, 20);

            // textBoxProductAmount
            this->textBoxProductAmount->Location = Point(150, 64);
            this->textBoxProductAmount->Size = Drawing::Size(200, 20);

            // textBoxSellDate
            this->textBoxSellDate->Location = Point(150, 142);
            this->textBoxSellDate->Size = Drawing::Size(200, 20);
            this->textBoxSellDate->Text = L"дд.мм.гггг";

            // buttonOK
            this->buttonOK->Location = Point(150, 175);
            this->buttonOK->Size = Drawing::Size(90, 25);
            this->buttonOK->Text = L"OK";
            this->buttonOK->Click += gcnew EventHandler(this, &SellForm::buttonOK_Click);

            // buttonCancel
            this->buttonCancel->Location = Point(260, 175);
            this->buttonCancel->Size = Drawing::Size(90, 25);
            this->buttonCancel->Text = L"Отмена";
            this->buttonCancel->DialogResult = Windows::Forms::DialogResult::Cancel;

            // AppointmentForm
            this->AcceptButton = this->buttonOK;
            this->CancelButton = this->buttonCancel;
            this->ClientSize = Drawing::Size(370, 210);
            this->Controls->Add(this->labelBarcode);
            this->Controls->Add(this->labelCashRegister);
            this->Controls->Add(this->labelProductAmount);
            this->Controls->Add(this->labelSellDate);
            this->Controls->Add(this->textBoxBarcode);
            this->Controls->Add(this->textBoxCashRegister);
            this->Controls->Add(this->textBoxProductAmount);
            this->Controls->Add(this->textBoxSellDate);
            this->Controls->Add(this->buttonOK);
            this->Controls->Add(this->buttonCancel);
            this->FormBorderStyle = Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->StartPosition = FormStartPosition::CenterParent;
            this->ResumeLayout(false);
            this->PerformLayout();
        }

    private:
        System::Void buttonOK_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (!ValidateInput())
            {
                return;
            }
            this->DialogResult = Windows::Forms::DialogResult::OK;
            this->Close();
        }

        bool ValidateInput()
        {
            // Проверка полиса ОМС
            std::string barcode = msclr::interop::marshal_as<std::string>(textBoxBarcode->Text);
            if (!DataValidation::validateBarcode(barcode))
            {
                MessageBox::Show("Неверный формат штрих-кода!\n Должно быть 13 цифр.",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return false;
            }

            // Проверка диагноза
            std::string CashRegister = msclr::interop::marshal_as<std::string>(textBoxCashRegister->Text);
            if (!DataValidation::isStingNum(CashRegister))
            {
                MessageBox::Show("Номер кассы - число!",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return false;
            }

            // Проверка ФИО врача
            if (!DataValidation::isStingNum(msclr::interop::marshal_as<std::string>(textBoxProductAmount->Text)))
            {
                MessageBox::Show("Количество - число!",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return false;
            }

            // Проверка даты приёма
            if (!DataValidation::validateDate(msclr::interop::marshal_as<std::string>(textBoxSellDate->Text)))
            {
                MessageBox::Show("Дата должна быть в формате\n ДД мес ГГГГ и быть корректной!",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return false;
            }

            return true;
        }

    public:
        void SetReadOnlyFields(bool readOnly)
        {
            textBoxBarcode->ReadOnly = readOnly;
            textBoxCashRegister->ReadOnly = readOnly;
            textBoxProductAmount->ReadOnly = readOnly;
            textBoxSellDate->ReadOnly = readOnly;
        }

        //void FillFormData(const tree::Appointment& appoint)
        //{
        //    textBoxBarcode->Text = gcnew String(appoint.Barcode.c_str());
        //    textBoxCashRegister->Text = gcnew String(appoint.CashRegister.c_str());
        //    textBoxProductAmount->Text = gcnew String(appoint.doctorFIO.surname.c_str());
        //    textBoxDoctorName->Text = gcnew String(appoint.doctorFIO.name.c_str());
        //    textBoxDoctorPatronymic->Text = gcnew String(appoint.doctorFIO.patronimyc.c_str());
        //    textBoxSellDate->Text = gcnew String(appoint.SellDate.toString().c_str());
        //}
    };
}