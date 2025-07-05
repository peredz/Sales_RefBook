#pragma once
#include <Windows.h>
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include "HashTable.h"
#include "DataValidation.h"

namespace SalesRefBook
{
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace DataValidation;

    public ref class ProductForm : public Form
    {

    public:
        property String^ Barcode { String^ get() { return textBoxBarcode->Text; } }
        property String^ Name { String^ get() { return textBoxName->Text; } }
        property String^ Price { String^ get() { return textBoxPrice->Text; } }

        ProductForm(String^ title)
        {
            InitializeComponent();
            this->Text = title;
        }

    protected:
        ~ProductForm() { if (components) delete components; }

    private:
        Label^ labelBarcode;
        Label^ labelName;
        Label^ labelPrice;
        TextBox^ textBoxBarcode;
        TextBox^ textBoxName;
        TextBox^ textBoxPrice;
        Button^ buttonOK;
        Button^ buttonCancel;
        System::ComponentModel::Container^ components;

        void InitializeComponent()
        {
            this->components = gcnew System::ComponentModel::Container();
            this->labelBarcode = gcnew System::Windows::Forms::Label();
            this->labelName = gcnew System::Windows::Forms::Label();
            this->labelPrice = gcnew System::Windows::Forms::Label();
            this->textBoxBarcode = gcnew System::Windows::Forms::TextBox();
            this->textBoxName = gcnew System::Windows::Forms::TextBox();
            this->textBoxPrice = gcnew System::Windows::Forms::TextBox();
            this->buttonOK = gcnew System::Windows::Forms::Button();
            this->buttonCancel = gcnew System::Windows::Forms::Button();
            this->SuspendLayout();

            // 
            // labelBarcode
            // 
            this->labelBarcode->AutoSize = true;
            this->labelBarcode->Location = System::Drawing::Point(12, 15);
            this->labelBarcode->Name = L"labelBarcode";
            this->labelBarcode->Size = System::Drawing::Size(110, 13);
            this->labelBarcode->TabIndex = 0;
            this->labelBarcode->Text = L"Штрих-код (13 цифр):";

            // 
            // labelName
            // 
            this->labelName->AutoSize = true;
            this->labelName->Location = System::Drawing::Point(12, 67);
            this->labelName->Name = L"labelName";
            this->labelName->Size = System::Drawing::Size(32, 13);
            this->labelName->TabIndex = 2;
            this->labelName->Text = L"Название:";
            // 
            // labelPrice
            // 
            this->labelPrice->AutoSize = true;
            this->labelPrice->Location = System::Drawing::Point(12, 93);
            this->labelPrice->Name = L"labelPrice";
            this->labelPrice->Size = System::Drawing::Size(57, 13);
            this->labelPrice->TabIndex = 3;
            this->labelPrice->Text = L"Цена:";
            // 
            // textBoxBarcode
            // 
            this->textBoxBarcode->Location = System::Drawing::Point(128, 12);
            this->textBoxBarcode->Name = L"textBoxBarcode";
            this->textBoxBarcode->Size = System::Drawing::Size(200, 20);
            this->textBoxBarcode->TabIndex = 5;
            this->textBoxBarcode->MaxLength = 19; // "XXXX XXX XXX XXXXXXX"
            // 
            // textBoxName
            // 
            this->textBoxName->Location = System::Drawing::Point(128, 64);
            this->textBoxName->Name = L"textBoxName";
            this->textBoxName->Size = System::Drawing::Size(200, 20);
            this->textBoxName->TabIndex = 7;
            // 
            // textBoxPrice
            // 
            this->textBoxPrice->Location = System::Drawing::Point(128, 90);
            this->textBoxPrice->Name = L"textBoxPrice";
            this->textBoxPrice->Size = System::Drawing::Size(200, 20);
            this->textBoxPrice->TabIndex = 8;
            // 
            // buttonOK
            // 
            this->buttonOK->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->buttonOK->Location = System::Drawing::Point(128, 150);
            this->buttonOK->Name = L"buttonOK";
            this->buttonOK->Size = System::Drawing::Size(90, 25);
            this->buttonOK->TabIndex = 10;
            this->buttonOK->Text = L"OK";
            this->buttonOK->UseVisualStyleBackColor = true;
            this->buttonOK->Click += gcnew System::EventHandler(this, &ProductForm::buttonOK_Click);
            // 
            // buttonCancel
            // 
            this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->buttonCancel->Location = System::Drawing::Point(238, 150);
            this->buttonCancel->Name = L"buttonCancel";
            this->buttonCancel->Size = System::Drawing::Size(90, 25);
            this->buttonCancel->TabIndex = 11;
            this->buttonCancel->Text = L"Отмена";
            this->buttonCancel->UseVisualStyleBackColor = true;
            // 
            // ProductForm
            // 
            this->AcceptButton = this->buttonOK;
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->CancelButton = this->buttonCancel;
            this->ClientSize = System::Drawing::Size(340, 185);
            this->Controls->Add(this->buttonCancel);
            this->Controls->Add(this->buttonOK);
            this->Controls->Add(this->textBoxPrice);
            this->Controls->Add(this->textBoxName);
            this->Controls->Add(this->textBoxBarcode);
            this->Controls->Add(this->labelPrice);
            this->Controls->Add(this->labelName);
            this->Controls->Add(this->labelBarcode);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"ProductForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->ResumeLayout(false);
            this->PerformLayout();
        }


    private: System::Void buttonOK_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // 1. Сначала проверяем валидность данных
        if (!ValidateInput())
        {
            // Не закрываем форму, просто выходим из обработчика
            return;
        }

        // 2. Только если данные валидны - закрываем форму с OK
        this->DialogResult = Windows::Forms::DialogResult::OK;
        this->Close();
    }

           bool ValidateInput()
           {

               std::string barcodeStr = msclr::interop::marshal_as<std::string>(textBoxBarcode->Text);
               std::string name = msclr::interop::marshal_as<std::string>(textBoxName->Text);
               std::string priceStr = msclr::interop::marshal_as<std::string>(textBoxPrice->Text);

               // Валидация штрих-кода
               if (!validateBarcode(barcodeStr))
               {
                   return false;
               }

               long long barcode = stoll(barcodeStr);
               std::cout << "5\n";

               // Валидация названия
               if (!validateProductName(name))
               {
                   return false;
               }
               std::cout << "6\n";

               // Валидация цены
               double price;
               try
               {
                   price = stod(priceStr);
               }

               catch (...)
               {
                   return false;
               }

               if (!validatePrice(price))
               {
                   return false;
               }
           }

    private: System::Void buttonCancel_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // Просто закрываем форму с результатом Cancel
        this->DialogResult = Windows::Forms::DialogResult::Cancel;
        this->Close();
    }

    public:
        void SetReadOnlyFields(bool readOnly)
        {
            textBoxBarcode->ReadOnly = readOnly;
            textBoxName->ReadOnly = readOnly;
            textBoxPrice->ReadOnly = readOnly;
        }
    };
}