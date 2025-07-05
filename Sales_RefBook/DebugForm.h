#pragma once
#include <Windows.h>

namespace ReferenceBookCoursework {
    public ref class DebugForm : public System::Windows::Forms::Form {
    public:
        DebugForm() {
            InitializeComponent();
        }

    private:
        System::Windows::Forms::RichTextBox^ debugTextBox;
        System::ComponentModel::Container^ components;

        void InitializeComponent() {
            this->debugTextBox = gcnew System::Windows::Forms::RichTextBox();
            this->SuspendLayout();

            // Настройка RichTextBox
            this->debugTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
            this->debugTextBox->Font = gcnew System::Drawing::Font("Consolas", 10);
            this->debugTextBox->ReadOnly = true;
            this->debugTextBox->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;

            // Настройка формы
            this->Text = "Отладка";
            this->ClientSize = System::Drawing::Size(800, 600);
            this->Controls->Add(this->debugTextBox);
            this->ResumeLayout(false);
        }

    public:
        void AddDebugText(System::String^ text) {
            this->debugTextBox->AppendText(text + "\n");
        }
    };
}