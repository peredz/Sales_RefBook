#pragma once

#include <Windows.h>
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

namespace SalesRefBook
{

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class LoadParametersDialog : public System::Windows::Forms::Form
    {
    public:
        LoadParametersDialog(void)
        {
            InitializeComponent();
            this->btnOK->Click += gcnew System::EventHandler(this, &LoadParametersDialog::btnOK_Click);

            // Подписываемся на события проверки ввода
            this->numericTableSize->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &LoadParametersDialog::Numeric_Validating);
            this->numericElementsCount->Validating += gcnew System::ComponentModel::CancelEventHandler(this, &LoadParametersDialog::Numeric_Validating);
        }

        property int TableSize {
            int get() { return Convert::ToInt32(numericTableSize->Value); }
        }

        property int ElementsCount {
            int get() { return Convert::ToInt32(numericElementsCount->Value); }
        }

    protected:
        ~LoadParametersDialog()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::NumericUpDown^ numericTableSize;
        System::Windows::Forms::NumericUpDown^ numericElementsCount;
        System::Windows::Forms::Button^ btnOK;
        System::Windows::Forms::Button^ btnCancel;
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->numericTableSize = (gcnew System::Windows::Forms::NumericUpDown());
            this->numericElementsCount = (gcnew System::Windows::Forms::NumericUpDown());
            this->btnOK = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericTableSize))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericElementsCount))->BeginInit();
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(12, 15);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(149, 13);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Начальный размер таблицы:";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(12, 41);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(218, 13);
            this->label2->TabIndex = 1;
            this->label2->Text = L"Количество элементов для обработки:";
            // 
            // numericTableSize
            // 
            this->numericTableSize->Location = System::Drawing::Point(236, 13);
            this->numericTableSize->Minimum = 1;
            this->numericTableSize->Maximum = 10000;
            this->numericTableSize->DecimalPlaces = 0;
            this->numericTableSize->ThousandsSeparator = true;
            this->numericTableSize->Name = L"numericTableSize";
            this->numericTableSize->Size = System::Drawing::Size(120, 20);
            this->numericTableSize->TabIndex = 2;
            this->numericTableSize->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
            // 
            // numericElementsCount
            // 
            this->numericElementsCount->Location = System::Drawing::Point(236, 39);
            this->numericElementsCount->Minimum = 1;
            this->numericElementsCount->Maximum = 10000;
            this->numericTableSize->DecimalPlaces = 0;
            this->numericTableSize->ThousandsSeparator = true;
            this->numericElementsCount->Name = L"numericElementsCount";
            this->numericElementsCount->Size = System::Drawing::Size(120, 20);
            this->numericElementsCount->TabIndex = 3;
            this->numericElementsCount->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
            // 
            // btnOK
            // 
            this->btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->btnOK->Location = System::Drawing::Point(95, 75);
            this->btnOK->Name = L"btnOK";
            this->btnOK->Size = System::Drawing::Size(75, 23);
            this->btnOK->TabIndex = 4;
            this->btnOK->Text = L"OK";
            this->btnOK->UseVisualStyleBackColor = true;
            // 
            // btnCancel
            // 
            this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->btnCancel->Location = System::Drawing::Point(176, 75);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(75, 23);
            this->btnCancel->TabIndex = 5;
            this->btnCancel->Text = L"Отмена";
            this->btnCancel->UseVisualStyleBackColor = true;
            // 
            // LoadParametersDialog
            // 
            this->AcceptButton = this->btnOK;
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->CancelButton = this->btnCancel;
            this->ClientSize = System::Drawing::Size(368, 110);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnOK);
            this->Controls->Add(this->numericElementsCount);
            this->Controls->Add(this->numericTableSize);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"LoadParametersDialog";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Параметры загрузки";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericTableSize))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericElementsCount))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }

        System::Void Numeric_Validating(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
        {
            NumericUpDown^ numericBox = (NumericUpDown^)sender;

            try
            {
                Decimal value = Decimal::Parse(numericBox->Text);

                if (value < numericBox->Minimum)
                {
                    MessageBox::Show(String::Format("Значение не может быть меньше {0}", numericBox->Minimum),
                        "Ошибка ввода",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error);
                    e->Cancel = true;
                    numericBox->Select(0, numericBox->Text->Length);
                }
                else if (value > numericBox->Maximum)
                {
                    MessageBox::Show(String::Format("Значение не может быть больше {0}", numericBox->Maximum),
                        "Ошибка ввода",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error);
                    e->Cancel = true;
                    numericBox->Select(0, numericBox->Text->Length);
                }
            }
            catch (FormatException^)
            {
                MessageBox::Show("Введите корректное числовое значение",
                    "Ошибка ввода",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Error);
                e->Cancel = true;
                numericBox->Select(0, numericBox->Text->Length);
            }
        }

        // Обработчик кнопки OK
        System::Void btnOK_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Принудительно вызываем валидацию
            if (!this->ValidateChildren())
            {
                MessageBox::Show("Исправьте ошибки ввода",
                    "Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Error);
                return;
            }

            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }
    };
}