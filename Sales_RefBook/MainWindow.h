#pragma once

#include "LoadParametersDialog.h"
#include "DebugForm.h"
#include "HashTable.h"
#include "data.h"
#include "RBTree.h"
#include "FilterRBTree.h"
#include "SellForm.h"
#include "ProcessData.h"
#include "ProductForm.h"
#include "List.h"
#include "DateTree.h"
#include "ProductSearchForm.h"


namespace SalesRefBook {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	//using namespace hash;
	//using namespace dataProcess;

	/// <summary>
	/// ������ ��� MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{

	public:
		// ����� ����� ������������� ��� ������ ����� ��� ������ tree::AVLTree* appointsTree
		// �������, �����-�� ��������
		//hashTable::HashTable<hashTable::HashStruct>* patientHash;
		hashTable::HashTable<hashTable::PrimaryHashFunction, hashTable::QuadraticProbingFunction>* productsHashTable;
		tree::tNode<long long>* root;
		dataTypes::Product* productArray;
		dataTypes::Sale* salesArray;
		int productsRealCount;
		int salesRealCount;
		bool h;

		dateTree::DateNode * filterRootDate;
		//filterTree::tNode<filterTree::Date, filterTree::KeyType>* filterRootDate;
		filterTree::tNode<string,           filterTree::KeyType>* filterRootName;
		filterTree::tNode<int,              filterTree::KeyType>* filterRootAmount;


	private: System::Windows::Forms::ToolStripMenuItem^ ����������������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ��������������ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ ����������������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ������������ToolStripMenuItem;


	public:
		MainWindow(void)
		// ���� � ����������� ���������� ������������ ���������� �� ���� ������ = nullplt
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^ menuStrip;

	private: System::Windows::Forms::ToolStripMenuItem^ ����������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ �����������������ToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ ������������������ToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ �����������������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ����ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ �����������������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ��������������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ���������������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ��������������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ������������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ����ToolStripMenuItem1;

	private: System::Windows::Forms::ToolStripMenuItem^ ���������������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ��������������ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ������������ToolStripMenuItem;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridView^ dataGridView2;
	private: System::Windows::Forms::Label^ patientLabel;
	private: System::Windows::Forms::Label^ appointLable;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ barcode;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ productName;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ price;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ salesBarcode;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ cashRegister;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ amount;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ saleDate;
	private: System::ComponentModel::Container^ components;


	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->������������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�����������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�����������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��������������ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->���������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->��������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->�����������������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->����������ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->barcode = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->productName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->price = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->salesBarcode = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->cashRegister = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->amount = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->saleDate = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->patientLabel = (gcnew System::Windows::Forms::Label());
			this->appointLable = (gcnew System::Windows::Forms::Label());
			this->menuStrip->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->������������������ToolStripMenuItem,
					this->�����������������ToolStripMenuItem, this->�����������������ToolStripMenuItem, this->����������ToolStripMenuItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(1184, 24);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip";
			this->menuStrip->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &MainWindow::menuStrip1_ItemClicked);
			// 
			// ������������������ToolStripMenuItem
			// 
			this->������������������ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->����ToolStripMenuItem,
					this->���������������ToolStripMenuItem, this->��������������ToolStripMenuItem, this->������������ToolStripMenuItem, this->����������������ToolStripMenuItem
			});
			this->������������������ToolStripMenuItem->Name = L"������������������ToolStripMenuItem";
			this->������������������ToolStripMenuItem->Size = System::Drawing::Size(156, 20);
			this->������������������ToolStripMenuItem->Text = L"���������� \"��������\"";
			// 
			// ����ToolStripMenuItem
			// 
			this->����ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->�����������������ToolStripMenuItem,
					this->��������������ToolStripMenuItem
			});
			this->����ToolStripMenuItem->Name = L"����ToolStripMenuItem";
			this->����ToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->����ToolStripMenuItem->Text = L"����";
			// 
			// �����������������ToolStripMenuItem
			// 
			this->�����������������ToolStripMenuItem->Name = L"�����������������ToolStripMenuItem";
			this->�����������������ToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->�����������������ToolStripMenuItem->Text = L"��������� ��������";
			this->�����������������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::�����������������ToolStripMenuItem_Click_1);
			// 
			// ��������������ToolStripMenuItem
			// 
			this->��������������ToolStripMenuItem->Name = L"��������������ToolStripMenuItem";
			this->��������������ToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->��������������ToolStripMenuItem->Text = L"��������� � ����";
			this->��������������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::����������������ToolStripMenuItem_Click);
			// 
			// ���������������ToolStripMenuItem
			// 
			this->���������������ToolStripMenuItem->Name = L"���������������ToolStripMenuItem";
			this->���������������ToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->���������������ToolStripMenuItem->Text = L"�������� �������";
			this->���������������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::���������������ToolStripMenuItem_Click);
			// 
			// ��������������ToolStripMenuItem
			// 
			this->��������������ToolStripMenuItem->Name = L"��������������ToolStripMenuItem";
			this->��������������ToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->��������������ToolStripMenuItem->Text = L"������� �������";
			this->��������������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::��������������ToolStripMenuItem_Click);
			// 
			// ������������ToolStripMenuItem
			// 
			this->������������ToolStripMenuItem->Name = L"������������ToolStripMenuItem";
			this->������������ToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->������������ToolStripMenuItem->Text = L"����� �������";
			this->������������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::������������ToolStripMenuItem_Click);
			// 
			// ����������������ToolStripMenuItem
			// 
			this->����������������ToolStripMenuItem->Name = L"����������������ToolStripMenuItem";
			this->����������������ToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->����������������ToolStripMenuItem->Text = L"������ ��� �������";
			this->����������������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::����������������ToolStripMenuItem_Click);
			// 
			// �����������������ToolStripMenuItem
			// 
			this->�����������������ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->����ToolStripMenuItem1,
					this->���������������ToolStripMenuItem, this->��������������ToolStripMenuItem, this->������������ToolStripMenuItem, this->������������ToolStripMenuItem
			});
			this->�����������������ToolStripMenuItem->Name = L"�����������������ToolStripMenuItem";
			this->�����������������ToolStripMenuItem->Size = System::Drawing::Size(147, 20);
			this->�����������������ToolStripMenuItem->Text = L"���������� \"�������\"";
			// 
			// ����ToolStripMenuItem1
			// 
			this->����ToolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->����������������ToolStripMenuItem,
					this->��������������ToolStripMenuItem1
			});
			this->����ToolStripMenuItem1->Name = L"����ToolStripMenuItem1";
			this->����ToolStripMenuItem1->Size = System::Drawing::Size(180, 22);
			this->����ToolStripMenuItem1->Text = L"����";
			// 
			// ����������������ToolStripMenuItem
			// 
			this->����������������ToolStripMenuItem->Name = L"����������������ToolStripMenuItem";
			this->����������������ToolStripMenuItem->Size = System::Drawing::Size(176, 22);
			this->����������������ToolStripMenuItem->Text = L"��������� �������";
			this->����������������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::����������������ToolStripMenuItem_Click);
			// 
			// ��������������ToolStripMenuItem1
			// 
			this->��������������ToolStripMenuItem1->Name = L"��������������ToolStripMenuItem1";
			this->��������������ToolStripMenuItem1->Size = System::Drawing::Size(176, 22);
			this->��������������ToolStripMenuItem1->Text = L"��������� � ����";
			this->��������������ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainWindow::��������������������ToolStripMenuItem1_Click);
			// 
			// ���������������ToolStripMenuItem
			// 
			this->���������������ToolStripMenuItem->Name = L"���������������ToolStripMenuItem";
			this->���������������ToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->���������������ToolStripMenuItem->Text = L"�������� �������";
			this->���������������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::���������������ToolStripMenuItem_Click);
			// 
			// ��������������ToolStripMenuItem
			// 
			this->��������������ToolStripMenuItem->Name = L"��������������ToolStripMenuItem";
			this->��������������ToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->��������������ToolStripMenuItem->Text = L"������� �������";
			this->��������������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::��������������ToolStripMenuItem_Click);
			// 
			// ������������ToolStripMenuItem
			// 
			this->������������ToolStripMenuItem->Name = L"������������ToolStripMenuItem";
			this->������������ToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->������������ToolStripMenuItem->Text = L"����� �������";
			this->������������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::������������ToolStripMenuItem_Click);
			// 
			// ������������ToolStripMenuItem
			// 
			this->������������ToolStripMenuItem->Name = L"������������ToolStripMenuItem";
			this->������������ToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->������������ToolStripMenuItem->Text = L"������ ������";
			this->������������ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::������������ToolStripMenuItem_Click);
			// 
			// �����������������ToolStripMenuItem
			// 
			this->�����������������ToolStripMenuItem->Name = L"�����������������ToolStripMenuItem";
			this->�����������������ToolStripMenuItem->Size = System::Drawing::Size(136, 20);
			this->�����������������ToolStripMenuItem->Text = L"������������ �����";
			// 
			// ����������ToolStripMenuItem
			// 
			this->����������ToolStripMenuItem->Name = L"����������ToolStripMenuItem";
			this->����������ToolStripMenuItem->Size = System::Drawing::Size(94, 20);
			this->����������ToolStripMenuItem->Text = L"� ���������";
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::ButtonFace;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->barcode,
					this->productName, this->price
			});
			this->dataGridView1->EditMode = System::Windows::Forms::DataGridViewEditMode::EditProgrammatically;
			this->dataGridView1->Location = System::Drawing::Point(12, 134);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGridView1->Size = System::Drawing::Size(561, 471);
			this->dataGridView1->TabIndex = 1;
			// 
			// policy
			// 
			this->barcode->HeaderText = L"�����-���";
			this->barcode->Name = L"barcode";
			// 
			// productName
			// 
			this->productName->HeaderText = L"��������";
			this->productName->Name = L"productName";
			// 
			// price
			// 
			this->price->HeaderText = L"����";
			this->price->Name = L"price";
			// 
			// dataGridView2
			// 
			this->dataGridView2->AllowUserToAddRows = false;
			this->dataGridView2->AllowUserToDeleteRows = false;
			this->dataGridView2->AllowUserToResizeRows = false;
			this->dataGridView2->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView2->BackgroundColor = System::Drawing::SystemColors::Control;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->salesBarcode,
					this->cashRegister, this->amount, this->saleDate
			});
			this->dataGridView2->EditMode = System::Windows::Forms::DataGridViewEditMode::EditProgrammatically;
			this->dataGridView2->Location = System::Drawing::Point(611, 134);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->Size = System::Drawing::Size(561, 471);
			this->dataGridView2->TabIndex = 2;
			// 
			// salesBarcode
			// 
			this->salesBarcode->HeaderText = L"�����-���";
			this->salesBarcode->Name = L"salesBarcode";
			// 
			// cashRegister
			// 
			this->cashRegister->HeaderText = L"�����";
			this->cashRegister->Name = L"cashRegister";
			// 
			// amount
			// 
			this->amount->HeaderText = L"����������";
			this->amount->Name = L"amount";
			// 
			// saleDate
			// 
			this->saleDate->HeaderText = L"���� �������";
			this->saleDate->Name = L"saleDate";
			// 
			// patientLabel
			// 
			this->patientLabel->AutoSize = true;
			this->patientLabel->Font = (gcnew System::Drawing::Font(L"Arial", 50, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(254)));
			this->patientLabel->Location = System::Drawing::Point(79, 53);
			this->patientLabel->Name = L"patientLabel";
			this->patientLabel->Size = System::Drawing::Size(422, 78);
			this->patientLabel->TabIndex = 3;
			this->patientLabel->Text = L"��������";
			// 
			// appointLable
			// 
			this->appointLable->AutoSize = true;
			this->appointLable->Font = (gcnew System::Drawing::Font(L"Arial", 50, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(254)));
			this->appointLable->Location = System::Drawing::Point(725, 53);
			this->appointLable->Name = L"appointLable";
			this->appointLable->Size = System::Drawing::Size(342, 78);
			this->appointLable->TabIndex = 4;
			this->appointLable->Text = L"�������";
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 14);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(125)), static_cast<System::Int32>(static_cast<System::Byte>(117)),
				static_cast<System::Int32>(static_cast<System::Byte>(111)));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(1184, 661);
			this->Controls->Add(this->appointLable);
			this->Controls->Add(this->patientLabel);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->menuStrip);
			this->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(254)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip;
			this->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->Name = L"MainWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"�� - �����������";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private:
			// ���� ������ (�������� � ������ ������)
			/*
			tree::AVLTree* appointsTree;         // AVL-������ ��� �������� ������� � �������
			hashTable::HashTable<hashTable::HashStruct>* patientHash; // ���-������� ���������
			hashTable::Patient* patientMas;           // ������ ���������
			tree::Appointment* appointMas;       // ������ ������� �� �����
			int patientsCount;                   // ���������� ���������
			int appointmentsCount;               // ���������� ������� �� �����
			bool h;                              // ���� ��� ������������ AVL-������
			*/

			void UpdateSelesDataGridView()
			{
				dataGridView2->Rows->Clear();

				if (salesArray == nullptr) return;

				int uniqueCount = tree::countBarcodes(root);

				long long* barcodesArray = new long long[uniqueCount];
				int currentIndex = 0;

				tree::fillBarcodes(root, barcodesArray, currentIndex);

				for (int i = 0; i < uniqueCount; i++) {
					tree::BarcodeKey key;
					key.barcode = barcodesArray[i];

					auto searchResult = tree::searchData(root, key);

					if (searchResult.second != -1) {
						for (int j = 0; j < searchResult.second; j++) {
							int index = searchResult.first[j];

							dataGridView2->Rows->Add(
								gcnew String(std::to_string(salesArray[index].barcode).c_str()),
								gcnew String(std::to_string(salesArray[index].cashRegister).c_str()),
								gcnew String(std::to_string(salesArray[index].quantity).c_str()),
								gcnew String(salesArray[index].saleDate.toString().c_str())
							);
						}
					}
				}

				delete[] barcodesArray;
			}


			// �������� �������� �� �����
			System::Void �����������������ToolStripMenuItem_Click_1(System::Object^ sender, System::EventArgs^ e) {
				/*
				1. ������� ������ ������ ����� (OpenFileDialog)
				2. ��������� ���� � ������� support::fillPatientMas()
				3. �������� dataGridView1 � ������ �������
				4. ���������� ��������� ������ (���� �� ������, �������� ������)
				*/
				LoadParametersDialog^ paramsDialog = gcnew LoadParametersDialog();
				if (paramsDialog->ShowDialog(this) != System::Windows::Forms::DialogResult::OK)
				{
					return;
				}

				if (paramsDialog->TableSize <= 0 || paramsDialog->ElementsCount <= 0)
				{
					MessageBox::Show("��������� �������� ������ ���� �������������� �������",
						"������",
						MessageBoxButtons::OK,
						MessageBoxIcon::Error);
					return;
				}

				int initialSize = paramsDialog->TableSize;
				int elementsToProcess = paramsDialog->ElementsCount;

				OpenFileDialog^ ofd = gcnew OpenFileDialog();
				ofd->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
				ofd->Title = "�������� ���� � ����������";

				if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					try
					{

						if (productsHashTable != nullptr) {
							delete productsHashTable;
							productsHashTable = nullptr;
						}
						if (productArray != nullptr) {
							delete[] productArray;
							productArray = nullptr;
						}

						productsHashTable = new hashTable::HashTable<hashTable::PrimaryHashFunction, hashTable::QuadraticProbingFunction>(initialSize);

						std::string filename = msclr::interop::marshal_as<std::string>(ofd->FileName);
						dataTypes::Product* tempProbuctArray = nullptr;
						int tempRealCount = 0;
						if (!dataProcess::downloadDataFromFileToArrayOfProducts(filename, tempProbuctArray, tempRealCount, elementsToProcess))
						{
							throw gcnew Exception("������ ��� ������ ����� � ����������");
						}
						//patientFioFilterTree = nullptr;
						//filterTree::AVLTree<filterTree::patientFioFilter>* newTree = nullptr;
						//bool newFilterH = false;
						//patientFilterH = false;
						productArray = tempProbuctArray;
						productsRealCount = tempRealCount;

						productsHashTable->load_data(productArray, productsRealCount);
						/*for (int i = 0; i < productsRealCount; i++)
						{
							hashTable::HashStruct hs;
							hs.policy = patientMas[i].policy;
							hs.index = i;
							patientHash->add(hs);

							filterTree::patientFioFilter pat;
							pat.fio = patientMas[i].fio;
							pat.index = i;
							filterTree::add<filterTree::patientFioFilter>(newTree, pat, newFilterH);
						}
						patientFioFilterTree = newTree;
						patientFilterH = newFilterH;*/

						UpdatePatientDataGridView();

						MessageBox::Show(
							String::Format("������� ��������� {0} ���������.\n������ �������: {1}",
								productsRealCount, productsHashTable->getCapacity()),
							"�����",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);
					}
					catch (Exception^ ex)
					{
						MessageBox::Show(
							"������ ��� ��������: " + ex->Message,
							"������",
							MessageBoxButtons::OK,
							MessageBoxIcon::Error);

						if (productArray != nullptr) {
							delete[] productArray;
							productArray = nullptr;
						}
						if (productsHashTable != nullptr) {
							delete productsHashTable;
							productsHashTable = nullptr;
						}
					}
				}
			}

			void UpdatePatientDataGridView()
			{
				dataGridView1->Rows->Clear();
				
				if (productsHashTable == nullptr || productArray == nullptr) return;
				for (int i = 0; i < productsRealCount; i++)
				{
					if (productsHashTable->find(productArray[i].getKey(), i) != -1)
					{
						dataGridView1->Rows->Add(
							gcnew String(std::to_string(productArray[i].barcode).c_str()),
							gcnew String(productArray[i].name.c_str()),
							gcnew String(std::to_string(productArray[i].price).c_str())
						);
					}
				}
			}
			

			// ���������� ��������� � ����
			System::Void ����������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
				/*
				1. ������� ������ ���������� ����� (SaveFileDialog)
				2. �������� ������ �� patientMas � ����
				3. ������ ������ ������ ��������������� ������� ������
				4. ���������� ������ (��� ������ ��� ����������)
				*/
				throw gcnew System::NotImplementedException();
			}

			// ���������� ������ ��������
			System::Void ���������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
			{
				if (productsHashTable == nullptr)
				{
					productsHashTable = new hashTable::HashTable<hashTable::PrimaryHashFunction,
						hashTable::QuadraticProbingFunction>(8);
				}

				ProductForm^ form = gcnew ProductForm("���������� ��������");
				form->SetReadOnlyFields(false);

				while (true)
				{
					if (form->ShowDialog() != Windows::Forms::DialogResult::OK)
					{
						return;
					}

					try
					{

						dataTypes::Product newProduct;
						newProduct.barcode = stoll(msclr::interop::marshal_as<std::string>(form->Barcode));
						newProduct.name = (msclr::interop::marshal_as<std::string>(form->Name));
						newProduct.price = stod(msclr::interop::marshal_as<std::string>(form->Price));


						int indexOfProduct = productsHashTable->findByBarcode(newProduct.barcode);

						if (indexOfProduct != -1)
						{
							MessageBox::Show("������� � ����� ����-����� ��� ����������!",
								"������",
								MessageBoxButtons::OK,
								MessageBoxIcon::Error);
							break;
						}

						dataTypes::Product* tempProductArray = productArray;
						hashTable::HashTable<hashTable::PrimaryHashFunction,
							hashTable::QuadraticProbingFunction>* newHash = productsHashTable;
						int tempRealCount = productsRealCount;
						dataProcess::addElementToArrayAndHashTable(tempProductArray, tempRealCount, newHash, newProduct);

						productArray = tempProductArray;
						productsHashTable = newHash;
						productsRealCount++;


						UpdatePatientDataGridView();
						MessageBox::Show("������� ������� ��������!",
							"�����",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);
						break;
					}
					catch (Exception^ ex)
					{
						MessageBox::Show("������ ��� ���������� ��������! ",
							"������",
							MessageBoxButtons::OK,
							MessageBoxIcon::Error);
					}
				}
			}

			// �������� ��������
			System::Void ��������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
			{
				if (productsHashTable == nullptr)
				{
					productsHashTable = new hashTable::HashTable<hashTable::PrimaryHashFunction,
						hashTable::QuadraticProbingFunction>(8);
				}

				ProductForm^ form = gcnew ProductForm("�������� ��������");
				form->SetReadOnlyFields(false);

				while (true)
				{
					if (form->ShowDialog() != Windows::Forms::DialogResult::OK)
					{
						return;
					}

					try
					{

						dataTypes::Product newProduct;
						newProduct.barcode = stoll(msclr::interop::marshal_as<std::string>(form->Barcode));
						newProduct.name = (msclr::interop::marshal_as<std::string>(form->Name));
						newProduct.price = stod(msclr::interop::marshal_as<std::string>(form->Price));


						int steps;
						int indexOfProduct = productsHashTable->findByBarcode(newProduct.barcode);

						if (indexOfProduct == -1)
						{
							MessageBox::Show("������� � ����� ����-����� �� ����������!",
								"������",
								MessageBoxButtons::OK,
								MessageBoxIcon::Error);
							break;
						}

						if (!(productArray[indexOfProduct] == newProduct))
						{
							MessageBox::Show("����-��� �� ������������� ������!",
								"������",
								MessageBoxButtons::OK,
								MessageBoxIcon::Error);
							break;
						}

						tree::BarcodeKey key;
						key.barcode = newProduct.barcode;
						tree::printTree(root);
						if ((tree::search(root, key) != nullptr) && (!tree::search(root, key)->data->isEmpty()))
						{
							MessageBox::Show("���������� �������!\n ���� ������� � ����� ���������",
								"������",
								MessageBoxButtons::OK,
								MessageBoxIcon::Error);
							break;
						}

						String^ confirmMessage = String::Format("�� ������������� ������ ������� �������:\n\n����-���: {0}\n��������: {1}\n����: {2}",
							gcnew String(form->Barcode),
							gcnew String(form->Name),
							gcnew String(form->Price));

						if (MessageBox::Show(confirmMessage, "������������� ��������",
							MessageBoxButtons::YesNo, MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::Yes)
						{
							return;
						}

						productsHashTable->removeByBarcode(newProduct.barcode);

						UpdatePatientDataGridView();
						MessageBox::Show("������� ������� ������!",
							"�����",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);
						break;
					}
					catch (Exception^ ex)
					{
						MessageBox::Show("������ ��� �������� ��������! ",
							"������",
							MessageBoxButtons::OK,
							MessageBoxIcon::Error);
					}
				}
			}

			// ����� ��������
			System::Void ������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
			{
				if (productsHashTable == nullptr)
				{
					MessageBox::Show("���-������� �� ����������������!\n ������� ��������� ��������.",
						"������",
						MessageBoxButtons::OK,
						MessageBoxIcon::Error);
					return;
				}

				SearchPatientForm^ searchForm = gcnew SearchPatientForm();

				while (true)
				{
					if (searchForm->ShowDialog() != Windows::Forms::DialogResult::OK)
						return;

					String^ searchBarCodeString = searchForm->BarCode;

					try
					{
						int steps = 0;
						long long barcode = stoll(msclr::interop::marshal_as<std::string>(searchBarCodeString));

						int hashIndex = productsHashTable->findByBarcodeWithSteps(barcode, steps);

						if (hashIndex == -1)
						{
							MessageBox::Show("������� � �������� �����-����� �� �������",
								"��������� ������",
								MessageBoxButtons::OK,
								MessageBoxIcon::Information);
							break;
						}

						dataTypes::Product product = productArray[hashIndex];

						String^ info = String::Format(
							"������ �������:\n\n�����-���: {0}\n��������: {1}\n����: {2}\n���-�� �����: {3}",
							gcnew String(std::to_string(product.barcode).c_str()),
							gcnew String(product.name.c_str()),
							gcnew String(std::to_string(product.price).c_str()),
							gcnew String(std::to_string(steps).c_str()));

						MessageBox::Show(info, "��������� ������",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);

						HighlightProduct(std::to_string(product.barcode));
						break;
					}
					catch (Exception^ ex)
					{
						MessageBox::Show("������ ��� ������: " + ex->Message,
							"������",
							MessageBoxButtons::OK,
							MessageBoxIcon::Error);
					}
				}
			}

			void HighlightProduct(const std::string & barcode)
			{
				for (int i = 0; i < dataGridView1->Rows->Count; i++)
				{
					String^ rowProduct = (String^)dataGridView1->Rows[i]->Cells["barcode"]->Value;
					if (rowProduct->Equals(gcnew String(barcode.c_str())))
					{
						dataGridView1->ClearSelection();
						dataGridView1->Rows[i]->Selected = true;
						dataGridView1->FirstDisplayedScrollingRowIndex = i;
						break;
					}
				}
			}

			// ������ ���-������� (��� ����������� � ����� �������)
			System::Void ����������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
				/*DebugForm^ debugForm = gcnew DebugForm();
				debugForm->AddDebugText("=== ������ ���-������� ��������� ===");

				if (patientHash != nullptr) {
					std::string hashTableStr = patientHash->printString<hashTable::Patient>(patientMas);
					debugForm->AddDebugText(gcnew System::String(hashTableStr.c_str()));
				}
				else {
					debugForm->AddDebugText("���-������� �� ���������!");
				}

				debugForm->ShowDialog();*/
				throw gcnew System::NotImplementedException();

			}

			// �������� ������� �� ����� �� �����
			private: System::Void ����������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
			{

				LoadParametersDialog^ paramsDialog = gcnew LoadParametersDialog();

				int elementsToProcess = paramsDialog->ElementsCount;

				OpenFileDialog^ ofd = gcnew OpenFileDialog();
				ofd->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
				ofd->Title = "�������� ���� � ���������";

				if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					try {
						// ������� ������ ������, ���� ����
						if (root != nullptr) {
							delete root;
							root = nullptr;
						}
						if (salesArray != nullptr) {
							delete[] salesArray;
							salesArray = nullptr;
						}

						root = nullptr;

						std::string filename = msclr::interop::marshal_as<std::string>(ofd->FileName);
						dataTypes::Sale* tempSalesArray = nullptr;
						int tempRealCount = 0;
						bool newH = false;

						// ���������� ������� ������ �� �����
						dataProcess::downloadDataFromFileToArray(filename, tempSalesArray, tempRealCount);

						salesArray = tempSalesArray;
						salesRealCount = tempRealCount;


						tree::tNode<long long>* newTree = root;

						//dateTree::DateNode* newFilterRootDate = filterRootDate;
						//filterTree::tNode<filterTree::Date, filterTree::KeyType>* newFilterRootDate = filterRootDate;
						//filterTree::tNode<string, filterTree::KeyType>* newFilterRootName = filterRootName;
						//filterTree::tNode<int, filterTree::KeyType>* newFilterRootAmount = filterRootAmount;

						//barcodeFilterTree = nullptr;
						//saleDateFilterTree = nullptr;
						//barcodeFilterH = false;
						//saleDateFilterH = false;

						//tNode<tree::BarcodeKey>* newBarcodeTree = nullptr;
						//tNode<tree::SaleDateKey>* newDateTree = nullptr;
						//bool barcodeH = false;
						bool dateH = false;
						int SalesCount = 0;

						for (int i = 0; i < salesRealCount; i++) {
						//	// ��������� ������ �� �����-����
							int hashIndex = productsHashTable->findByBarcode(salesArray[i].barcode);
							if (hashIndex == -1)
							{
								MessageBox::Show(String::Format("������ � ����� �����-����� {0} �� ����������!", salesArray[i].barcode),
									"������",
									MessageBoxButtons::OK,
									MessageBoxIcon::Error);
								continue;
							}
							SalesCount++;
							tree::BarcodeKey barcodeKey;
							barcodeKey.barcode = salesArray[i].barcode;
							tree::addElement(newTree, barcodeKey, i);

							//filterTree::NameKey productNameKey(productArray[hashIndex].name);
							//filterTree::addElement(newFilterRootName, productNameKey, i);

							//filterTree::AmountKey saleAmountKey(salesArray[i].quantity);
							//filterTree::addElement(newFilterRootAmount, saleAmountKey, i);

							//dataTypes::Date saleDate = salesArray[i].saleDate;

							//dateTree::Date saleDateKey(saleDate.day, saleDate.month, saleDate.year);
							//dateTree::addElement(newFilterRootDate, saleDateKey, i);


						// ��������� ������ �� ���� �������
							/*tree::SaleDateKey dateKey;
							dateKey.date = salesArray[i].saleDate;
							dateKey.index = i;
							tree::add(newDateTree, dateKey, dateH);*/
						}

						root = newTree;

						//filterRootName = newFilterRootName;
						//filterRootAmount = newFilterRootAmount;
						//filterRootDate = newFilterRootDate;

						//std::cout << "\n\n";
						//filterTree::printTree(newFilterRootName);
						//std::cout << "\n\n";
						//filterTree::printTree(newFilterRootAmount);
						//std::cout << "\n\n";
						//dateTree::printTree(newFilterRootDate);


						/*barcodeFilterTree = newBarcodeTree;
						saleDateFilterTree = newDateTree;
						barcodeFilterH = barcodeH;
						saleDateFilterH = dateH;*/

						UpdateSelesDataGridView(); 

						MessageBox::Show(
							String::Format("������� ��������� {0} ������.", SalesCount),
							"�����",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);
					}
					catch (Exception^ ex) {
						MessageBox::Show(
							"������ ��� ��������: " + ex->Message,
							"������",
							MessageBoxButtons::OK,
							MessageBoxIcon::Error);

						if (salesArray != nullptr) {
							delete[] salesArray;
							salesArray = nullptr;
						}
						if (root != nullptr) {
							delete root;
							root = nullptr;
						}
					}
				}
			}


			// ���������� ������� �� ����� � ����
			System::Void ��������������������ToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
				/*
				1. ������� ������ ���������� �����
				2. �������� ������ �� appointMas � ����
				3. ��������� � ��� �� �������, ��� � ��� ������
				*/
				throw gcnew System::NotImplementedException();
			}

			// ���������� ������ �� �����
			System::Void ���������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

				{
					if (productsHashTable == nullptr)
					{
						MessageBox::Show("���-������� �� ����������������!\n������� ��������� ��������.",
							"������",
							MessageBoxButtons::OK,
							MessageBoxIcon::Error);
						return;
					}

					SellForm^ form = gcnew SellForm("���������� �������");
					form->SetReadOnlyFields(false);

					while (true)
					{
						if (form->ShowDialog() != Windows::Forms::DialogResult::OK)
						{
							return;
						}
						else
						{
							try
							{
								dataTypes::Sale newSale;
								newSale.barcode = stoll(msclr::interop::marshal_as<std::string>(form->Barcode));
								newSale.cashRegister = stoi(msclr::interop::marshal_as<std::string>(form->CashRegister));
								newSale.quantity = stoi(msclr::interop::marshal_as<std::string>(form->ProductAmount));
								dataTypes::Date date;
								date = date.parseDate(msclr::interop::marshal_as<std::string>(form->SellDate));
								newSale.saleDate = date;
								
								int hashIndex = productsHashTable->findByBarcode(newSale.barcode);
								if (hashIndex == -1)
								{
									MessageBox::Show("������ � ����� �����-����� �� ����������!",
										"������",
										MessageBoxButtons::OK,
										MessageBoxIcon::Error);
									break;
								}

								dataTypes::Sale* tempSalesArray = salesArray;
								tree::tNode<long long>* newTree = root;

								dateTree::DateNode* newFilterRootDate = filterRootDate;
								filterTree::tNode<string, filterTree::KeyType>* newFilterRootName = filterRootName;
								filterTree::tNode<int, filterTree::KeyType>* newFilterRootAmount = filterRootAmount;

								int tempRealCount = salesRealCount;
								
								dataProcess::addElementToTheTreeAndArray<dataTypes::Sale, long long, tree::BarcodeKey>(newSale, tempSalesArray, tempRealCount, newTree);

								filterTree::NameKey productNameKey(productArray[hashIndex].name);
								filterTree::addElement(newFilterRootName, productNameKey, salesRealCount - 1);

								filterTree::AmountKey saleAmountKey(salesArray[salesRealCount - 1].quantity);
								filterTree::addElement(newFilterRootAmount, saleAmountKey, salesRealCount - 1);

								dataTypes::Date saleDate = salesArray[salesRealCount - 1].saleDate;
								dateTree::Date saleDateKey(saleDate.day, saleDate.month, saleDate.year);
								dateTree::addElement(newFilterRootDate, saleDateKey, salesRealCount - 1);

								root = newTree;
								filterRootName = newFilterRootName;
								filterRootAmount = newFilterRootAmount;
								filterRootDate = newFilterRootDate;

								salesArray = tempSalesArray;
								salesRealCount = tempRealCount;

								UpdateSelesDataGridView();
								MessageBox::Show("������� ������� ���������!",
									"�����",
									MessageBoxButtons::OK,
									MessageBoxIcon::Information);
								break;
							}
							catch (Exception^ ex)
							{
								MessageBox::Show("������ ��� ���������� �������! ",
									"������",
									MessageBoxButtons::OK,
									MessageBoxIcon::Error);
							}
						}
					}
				}
			}

			// �������� �������
			System::Void ��������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
			{
				if (salesArray == nullptr || productsHashTable == nullptr)
				{
					MessageBox::Show("������ �����������.",
						"������",
						MessageBoxButtons::OK,
						MessageBoxIcon::Error);
					return;
				}

				SellForm^ form = gcnew SellForm("�������� �������");
				form->SetReadOnlyFields(false);

				while (true)
				{
					if (form->ShowDialog() != Windows::Forms::DialogResult::OK)
					{
						return;
					}
					else
					{
						try
						{
							dataTypes::Sale newSale;
							newSale.barcode = stoll(msclr::interop::marshal_as<std::string>(form->Barcode));
							newSale.cashRegister = stoi(msclr::interop::marshal_as<std::string>(form->CashRegister));
							newSale.quantity = stoi(msclr::interop::marshal_as<std::string>(form->ProductAmount));
							dataTypes::Date date;
							date = date.parseDate(msclr::interop::marshal_as<std::string>(form->SellDate));
							newSale.saleDate = date;


							tree::BarcodeKey key;
							key.barcode = newSale.barcode;
							list::List* ListOfSalesByBarcode = tree::search(root, key)->data;

							if (ListOfSalesByBarcode == nullptr || ListOfSalesByBarcode->isEmpty())
							{
								MessageBox::Show("���������� �������!\n ��� ������� � ����� �����-�����",
									"������",
									MessageBoxButtons::OK,
									MessageBoxIcon::Error);
								break;
							}

							list::List* ListOfSalesToDelete = new list::List();

							int deletedCount = 0;

							int hashIndex = productsHashTable->findByBarcode(newSale.barcode);

							for (typename list::List::Iterator it = ListOfSalesByBarcode->begin(); it != ListOfSalesByBarcode->end(); ++it)
							{
								int index = *it;
								if (index >= 0 && index < salesRealCount)
								{
									if (salesArray[index] == newSale)
									{
										ListOfSalesToDelete->add(index);
									}
								}
							}


							for (typename list::List::Iterator it = ListOfSalesToDelete->begin(); it != ListOfSalesToDelete->end(); ++it)
							{
								int index = *it;
								if (index >= 0 && index < salesRealCount)
								{
									if (salesArray[index] == newSale)
									{
										cout << salesArray[index].printStruct() << "\n";
										tree::BarcodeKey tempKey(newSale.barcode);
										tree::tNode<long long>* tempRoot = root;
										tree::removeElement<long long>(tempRoot, tempKey, index);
										root = tempRoot;

										//filterTree::NameKey productNameKey(productArray[hashIndex].name);
										//filterTree::removeElementByName(filterRootName, productNameKey, index);

										//filterTree::AmountKey saleAmountKey(salesArray[index].quantity);
										//filterTree::removeElementByAmount(filterRootAmount, saleAmountKey, index);

										//dataTypes::Date tempDate = salesArray[index].saleDate;
										//dateTree::Date saleDate = dateTree::Date(tempDate.day, tempDate.month, tempDate.year);
										////filterTree::DateKey saleDateKey(saleDate.day, saleDate.month, saleDate.year);
										//dateTree::removeElement(filterRootDate, saleDate, index);

										deletedCount++;
									}
								}
							}

							//std::cout << "\n\n";
							//filterTree::printTree(filterRootName);
							//std::cout << "\n\n";
							//filterTree::printTree(filterRootAmount);
							//std::cout << "\n\n";
							//dateTree::printTree(filterRootDate);
							
							delete ListOfSalesToDelete;
							tree::printTree(root);
							
							////////////////////////////////////////////////////////////
							//int hashIndex = productsHashTable->findByBarcode(newSale.barcode);
							//if (hashIndex == -1)
							//{
							//	MessageBox::Show("������ � ����� �����-����� �� ����������!",
							//		"������",
							//		MessageBoxButtons::OK,
							//		MessageBoxIcon::Error);
							//	break;
							//}

							//dataTypes::Sale* tempSalesArray = salesArray;
							//tree::tNode<long long>* newTree = root;

							//filterTree::tNode<filterTree::Date, filterTree::KeyType>* newFilterRootDate = filterRootDate;
							//filterTree::tNode<string, filterTree::KeyType>* newFilterRootName = filterRootName;
							//filterTree::tNode<int, filterTree::KeyType>* newFilterRootAmount = filterRootAmount;
							////////////////////////////////////////////////////////////

							/*int tempRealCount = salesRealCount;

							filterTree::NameKey productNameKey(productArray[hashIndex].name);
							filterTree::addElement(newFilterRootName, productNameKey, salesRealCount - 1);

							filterTree::AmountKey saleAmountKey(salesArray[salesRealCount - 1].quantity);
							filterTree::addElement(newFilterRootAmount, saleAmountKey, salesRealCount - 1);

							dataTypes::Date saleDate = salesArray[salesRealCount - 1].saleDate;
							filterTree::DateKey saleDateKey(saleDate.day, saleDate.month, saleDate.year);
							filterTree::addElement(newFilterRootDate, saleDateKey, salesRealCount - 1);

							root = newTree;
							filterRootName = newFilterRootName;
							filterRootAmount = newFilterRootAmount;
							filterRootDate = newFilterRootDate;

							salesArray = tempSalesArray;
							salesRealCount = tempRealCount;*/

							UpdateSelesDataGridView();
							MessageBox::Show("������� ������� �������!",
								"�����",
								MessageBoxButtons::OK,
								MessageBoxIcon::Information);
							break;
						}
						catch (Exception^ ex)
						{
							MessageBox::Show("������ ��� �������� �������! ",
								"������",
								MessageBoxButtons::OK,
								MessageBoxIcon::Error);
						}
					}
				}
			}

			// ����� ������� �� ����� �� ������ ���
			System::Void ������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
			{
				if (productsHashTable == nullptr)
				{
					MessageBox::Show("���-������� ��������� �� ����������������!\n������� ��������� ���������.",
						"������",
						MessageBoxButtons::OK,
						MessageBoxIcon::Error);
					return;
				}

				if (root == nullptr)
				{
					MessageBox::Show("������ ������ �� ����������������!\n������� ��������� �����.",
						"������",
						MessageBoxButtons::OK,
						MessageBoxIcon::Error);
					return;
				}

				SearchPatientForm^ searchForm = gcnew SearchPatientForm();

				while (true)
				{
					if (searchForm->ShowDialog() != Windows::Forms::DialogResult::OK)
						return;

					String^ searchBarCodeString = searchForm->BarCode;

					try
					{
						int steps = 0;
						long long barcode = stoll(msclr::interop::marshal_as<std::string>(searchBarCodeString));

						int hashIndex = productsHashTable->findByBarcodeWithSteps(barcode, steps);

						if (hashIndex == -1)
						{
							MessageBox::Show("��� ��������� � �������� �����-�����",
								"��������� ������",
								MessageBoxButtons::OK,
								MessageBoxIcon::Information);
							break;
						}

						dataTypes::Product product = productArray[hashIndex];

						String^ info = String::Format(
							"������ �������:\n\n�����-���: {0}\n��������: {1}\n����: {2}\n���-�� �����: {3}",
							gcnew String(std::to_string(product.barcode).c_str()),
							gcnew String(product.name.c_str()),
							gcnew String(std::to_string(product.price).c_str()),
							gcnew String(std::to_string(steps).c_str()));

						MessageBox::Show(info, "��������� ������",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);

						HighlightProduct(std::to_string(product.barcode));
						break;
					}
					catch (Exception^ ex)
					{
						MessageBox::Show("������ ��� ������: " + ex->Message,
							"������",
							MessageBoxButtons::OK,
							MessageBoxIcon::Error);
					}
				}
			}

			void HighlightProduct(const std::string & barcode)
			{
				for (int i = 0; i < dataGridView1->Rows->Count; i++)
				{
					String^ rowProduct = (String^)dataGridView1->Rows[i]->Cells["barcode"]->Value;
					if (rowProduct->Equals(gcnew String(barcode.c_str())))
					{
						dataGridView1->ClearSelection();
						dataGridView1->Rows[i]->Selected = true;
						dataGridView1->FirstDisplayedScrollingRowIndex = i;
						break;
					}
				}
			}

			// ������ ������
			System::Void ������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
				/*
				1. ������� DebugForm
				2. �������� ��������� ������������� ������
				3. ������� � DebugForm
				4. ���������� ������, ����� ������ ������
				*/
				throw gcnew System::NotImplementedException();
			}

			// ���������� ������ �� ���� (���� ��������)
			System::Void menuStrip1_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
				///*
				//1. ����� ������������ ��� ����� ��������� ����
				//2. ��� �������, ���� �� �����
				//*/
				//throw gcnew System::NotImplementedException();
			}
	};
}
