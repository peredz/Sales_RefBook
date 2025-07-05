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
	/// Сводка для MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{

	public:
		// ПОЗЖЕ ЗДЕСЬ ИНИЦАЛИЗИРУЕМ ВСЕ ДАННЫЕ ТАКИЕ КАК ДЕРЕВО tree::AVLTree* appointsTree
		// ТАБЛИЦЫ, КАКИЕ-ТО КОНСАНТЫ
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


	private: System::Windows::Forms::ToolStripMenuItem^ загрузитьПродажиToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ сохранитьВФайлToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ печатьХешТаблицыToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ печатьДереваToolStripMenuItem;


	public:
		MainWindow(void)
		// сюда в конструктор допиливаем иницализацию переменных по типу дерево = nullplt
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^ menuStrip;

	private: System::Windows::Forms::ToolStripMenuItem^ оПрограммеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ сформироватьОтчётToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ справочникПродуктыToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ справочникПродажиToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ загрузитьПродуктыToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ сохранитьВФайлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ добавитьПродуктToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ удалитьПродуктToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ найтиПродуктToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ файлToolStripMenuItem1;

	private: System::Windows::Forms::ToolStripMenuItem^ добавитьПродажуToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ удалитьПродажуToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ найтиПродажуToolStripMenuItem;
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
		/// Обязательная переменная конструктора.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->справочникПродуктыToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->загрузитьПродуктыToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьВФайлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->добавитьПродуктToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->удалитьПродуктToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->найтиПродуктToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->печатьХешТаблицыToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->справочникПродажиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->файлToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->загрузитьПродажиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьВФайлToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->добавитьПродажуToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->удалитьПродажуToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->найтиПродажуToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->печатьДереваToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сформироватьОтчётToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
				this->справочникПродуктыToolStripMenuItem,
					this->справочникПродажиToolStripMenuItem, this->сформироватьОтчётToolStripMenuItem, this->оПрограммеToolStripMenuItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(1184, 24);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip";
			this->menuStrip->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &MainWindow::menuStrip1_ItemClicked);
			// 
			// справочникПродуктыToolStripMenuItem
			// 
			this->справочникПродуктыToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->файлToolStripMenuItem,
					this->добавитьПродуктToolStripMenuItem, this->удалитьПродуктToolStripMenuItem, this->найтиПродуктToolStripMenuItem, this->печатьХешТаблицыToolStripMenuItem
			});
			this->справочникПродуктыToolStripMenuItem->Name = L"справочникПродуктыToolStripMenuItem";
			this->справочникПродуктыToolStripMenuItem->Size = System::Drawing::Size(156, 20);
			this->справочникПродуктыToolStripMenuItem->Text = L"Справочник \"Продукты\"";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->загрузитьПродуктыToolStripMenuItem,
					this->сохранитьВФайлToolStripMenuItem
			});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->файлToolStripMenuItem->Text = L"Файл";
			// 
			// загрузитьПродуктыToolStripMenuItem
			// 
			this->загрузитьПродуктыToolStripMenuItem->Name = L"загрузитьПродуктыToolStripMenuItem";
			this->загрузитьПродуктыToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->загрузитьПродуктыToolStripMenuItem->Text = L"Загрузить продукты";
			this->загрузитьПродуктыToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::загрузитьПродуктыToolStripMenuItem_Click_1);
			// 
			// сохранитьВФайлToolStripMenuItem
			// 
			this->сохранитьВФайлToolStripMenuItem->Name = L"сохранитьВФайлToolStripMenuItem";
			this->сохранитьВФайлToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->сохранитьВФайлToolStripMenuItem->Text = L"Сохранить в файл";
			this->сохранитьВФайлToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::сохранитьВФайлХТToolStripMenuItem_Click);
			// 
			// добавитьПродуктToolStripMenuItem
			// 
			this->добавитьПродуктToolStripMenuItem->Name = L"добавитьПродуктToolStripMenuItem";
			this->добавитьПродуктToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->добавитьПродуктToolStripMenuItem->Text = L"Добавить продукт";
			this->добавитьПродуктToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::добавитьПродуктToolStripMenuItem_Click);
			// 
			// удалитьПродуктToolStripMenuItem
			// 
			this->удалитьПродуктToolStripMenuItem->Name = L"удалитьПродуктToolStripMenuItem";
			this->удалитьПродуктToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->удалитьПродуктToolStripMenuItem->Text = L"Удалить продукт";
			this->удалитьПродуктToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::удалитьПродуктToolStripMenuItem_Click);
			// 
			// найтиПродуктToolStripMenuItem
			// 
			this->найтиПродуктToolStripMenuItem->Name = L"найтиПродуктToolStripMenuItem";
			this->найтиПродуктToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->найтиПродуктToolStripMenuItem->Text = L"Найти продукт";
			this->найтиПродуктToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::найтиПродуктToolStripMenuItem_Click);
			// 
			// печатьХешТаблицыToolStripMenuItem
			// 
			this->печатьХешТаблицыToolStripMenuItem->Name = L"печатьХешТаблицыToolStripMenuItem";
			this->печатьХешТаблицыToolStripMenuItem->Size = System::Drawing::Size(189, 22);
			this->печатьХешТаблицыToolStripMenuItem->Text = L"Печать хеш таблицы";
			this->печатьХешТаблицыToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::печатьХешТаблицыToolStripMenuItem_Click);
			// 
			// справочникПродажиToolStripMenuItem
			// 
			this->справочникПродажиToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->файлToolStripMenuItem1,
					this->добавитьПродажуToolStripMenuItem, this->удалитьПродажуToolStripMenuItem, this->найтиПродажуToolStripMenuItem, this->печатьДереваToolStripMenuItem
			});
			this->справочникПродажиToolStripMenuItem->Name = L"справочникПродажиToolStripMenuItem";
			this->справочникПродажиToolStripMenuItem->Size = System::Drawing::Size(147, 20);
			this->справочникПродажиToolStripMenuItem->Text = L"Справочник \"Продажи\"";
			// 
			// файлToolStripMenuItem1
			// 
			this->файлToolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->загрузитьПродажиToolStripMenuItem,
					this->сохранитьВФайлToolStripMenuItem1
			});
			this->файлToolStripMenuItem1->Name = L"файлToolStripMenuItem1";
			this->файлToolStripMenuItem1->Size = System::Drawing::Size(180, 22);
			this->файлToolStripMenuItem1->Text = L"Файл";
			// 
			// загрузитьПродажиToolStripMenuItem
			// 
			this->загрузитьПродажиToolStripMenuItem->Name = L"загрузитьПродажиToolStripMenuItem";
			this->загрузитьПродажиToolStripMenuItem->Size = System::Drawing::Size(176, 22);
			this->загрузитьПродажиToolStripMenuItem->Text = L"Загрузить продажи";
			this->загрузитьПродажиToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::загрузитьПродажиToolStripMenuItem_Click);
			// 
			// сохранитьВФайлToolStripMenuItem1
			// 
			this->сохранитьВФайлToolStripMenuItem1->Name = L"сохранитьВФайлToolStripMenuItem1";
			this->сохранитьВФайлToolStripMenuItem1->Size = System::Drawing::Size(176, 22);
			this->сохранитьВФайлToolStripMenuItem1->Text = L"Сохранить в файл";
			this->сохранитьВФайлToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainWindow::сохранитьВФайлДеревоToolStripMenuItem1_Click);
			// 
			// добавитьПродажуToolStripMenuItem
			// 
			this->добавитьПродажуToolStripMenuItem->Name = L"добавитьПродажуToolStripMenuItem";
			this->добавитьПродажуToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->добавитьПродажуToolStripMenuItem->Text = L"Добавить продажу";
			this->добавитьПродажуToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::добавитьПродажуToolStripMenuItem_Click);
			// 
			// удалитьПродажуToolStripMenuItem
			// 
			this->удалитьПродажуToolStripMenuItem->Name = L"удалитьПродажуToolStripMenuItem";
			this->удалитьПродажуToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->удалитьПродажуToolStripMenuItem->Text = L"Удалить продажу";
			this->удалитьПродажуToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::удалитьПродажуToolStripMenuItem_Click);
			// 
			// найтиПродажуToolStripMenuItem
			// 
			this->найтиПродажуToolStripMenuItem->Name = L"найтиПродажуToolStripMenuItem";
			this->найтиПродажуToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->найтиПродажуToolStripMenuItem->Text = L"Найти продажу";
			this->найтиПродажуToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::найтиПродажуToolStripMenuItem_Click);
			// 
			// печатьДереваToolStripMenuItem
			// 
			this->печатьДереваToolStripMenuItem->Name = L"печатьДереваToolStripMenuItem";
			this->печатьДереваToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->печатьДереваToolStripMenuItem->Text = L"Печать дерева";
			this->печатьДереваToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::печатьДереваToolStripMenuItem_Click);
			// 
			// сформироватьОтчётToolStripMenuItem
			// 
			this->сформироватьОтчётToolStripMenuItem->Name = L"сформироватьОтчётToolStripMenuItem";
			this->сформироватьОтчётToolStripMenuItem->Size = System::Drawing::Size(136, 20);
			this->сформироватьОтчётToolStripMenuItem->Text = L"Сформировать отчёт";
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(94, 20);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
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
			this->barcode->HeaderText = L"Штрих-код";
			this->barcode->Name = L"barcode";
			// 
			// productName
			// 
			this->productName->HeaderText = L"Название";
			this->productName->Name = L"productName";
			// 
			// price
			// 
			this->price->HeaderText = L"Цена";
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
			this->salesBarcode->HeaderText = L"Штрих-код";
			this->salesBarcode->Name = L"salesBarcode";
			// 
			// cashRegister
			// 
			this->cashRegister->HeaderText = L"Касса";
			this->cashRegister->Name = L"cashRegister";
			// 
			// amount
			// 
			this->amount->HeaderText = L"Количество";
			this->amount->Name = L"amount";
			// 
			// saleDate
			// 
			this->saleDate->HeaderText = L"Дата продажи";
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
			this->patientLabel->Text = L"ПРОДУКТЫ";
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
			this->appointLable->Text = L"ПРОДАЖИ";
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
			this->Text = L"КП - Справочники";
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private:
			// Поля класса (добавьте в начало класса)
			/*
			tree::AVLTree* appointsTree;         // AVL-дерево для хранения записей о приемах
			hashTable::HashTable<hashTable::HashStruct>* patientHash; // Хеш-таблица пациентов
			hashTable::Patient* patientMas;           // Массив пациентов
			tree::Appointment* appointMas;       // Массив записей на прием
			int patientsCount;                   // Количество пациентов
			int appointmentsCount;               // Количество записей на прием
			bool h;                              // Флаг для балансировки AVL-дерева
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


			// Загрузка продукты из файла
			System::Void загрузитьПродуктыToolStripMenuItem_Click_1(System::Object^ sender, System::EventArgs^ e) {
				/*
				1. Открыть диалог выбора файла (OpenFileDialog)
				2. Прочитать файл с помощью support::fillPatientMas()
				3. Обновить dataGridView1 с новыми данными
				4. Обработать возможные ошибки (файл не выбран, неверный формат)
				*/
				LoadParametersDialog^ paramsDialog = gcnew LoadParametersDialog();
				if (paramsDialog->ShowDialog(this) != System::Windows::Forms::DialogResult::OK)
				{
					return;
				}

				if (paramsDialog->TableSize <= 0 || paramsDialog->ElementsCount <= 0)
				{
					MessageBox::Show("Параметры загрузки должны быть положительными числами",
						"Ошибка",
						MessageBoxButtons::OK,
						MessageBoxIcon::Error);
					return;
				}

				int initialSize = paramsDialog->TableSize;
				int elementsToProcess = paramsDialog->ElementsCount;

				OpenFileDialog^ ofd = gcnew OpenFileDialog();
				ofd->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
				ofd->Title = "Выберите файл с продуктами";

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
							throw gcnew Exception("Ошибка при чтении файла с продуктами");
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
							String::Format("Успешно загружено {0} продуктов.\nРазмер таблицы: {1}",
								productsRealCount, productsHashTable->getCapacity()),
							"Успех",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);
					}
					catch (Exception^ ex)
					{
						MessageBox::Show(
							"Ошибка при загрузке: " + ex->Message,
							"Ошибка",
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
			

			// Сохранение пациентов в файл
			System::Void сохранитьВФайлХТToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
				/*
				1. Открыть диалог сохранения файла (SaveFileDialog)
				2. Записать данные из patientMas в файл
				3. Формат записи должен соответствовать формату чтения
				4. Обработать ошибки (нет данных для сохранения)
				*/
				throw gcnew System::NotImplementedException();
			}

			// Добавление нового пациента
			System::Void добавитьПродуктToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
			{
				if (productsHashTable == nullptr)
				{
					productsHashTable = new hashTable::HashTable<hashTable::PrimaryHashFunction,
						hashTable::QuadraticProbingFunction>(8);
				}

				ProductForm^ form = gcnew ProductForm("Добавление продукта");
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
							MessageBox::Show("Продукт с таким штри-кодом уже существует!",
								"Ошибка",
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
						MessageBox::Show("Продукт успешно добавлен!",
							"Успех",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);
						break;
					}
					catch (Exception^ ex)
					{
						MessageBox::Show("Ошибка при добавлении продукта! ",
							"Ошибка",
							MessageBoxButtons::OK,
							MessageBoxIcon::Error);
					}
				}
			}

			// Удаление пациента
			System::Void удалитьПродуктToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
			{
				if (productsHashTable == nullptr)
				{
					productsHashTable = new hashTable::HashTable<hashTable::PrimaryHashFunction,
						hashTable::QuadraticProbingFunction>(8);
				}

				ProductForm^ form = gcnew ProductForm("Удаление продукта");
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
							MessageBox::Show("Продукт с таким штри-кодом не существует!",
								"Ошибка",
								MessageBoxButtons::OK,
								MessageBoxIcon::Error);
							break;
						}

						if (!(productArray[indexOfProduct] == newProduct))
						{
							MessageBox::Show("Штри-код не соответствует товару!",
								"Ошибка",
								MessageBoxButtons::OK,
								MessageBoxIcon::Error);
							break;
						}

						tree::BarcodeKey key;
						key.barcode = newProduct.barcode;
						tree::printTree(root);
						if ((tree::search(root, key) != nullptr) && (!tree::search(root, key)->data->isEmpty()))
						{
							MessageBox::Show("Невозможно удалить!\n Есть продажи с таким продуктом",
								"Ошибка",
								MessageBoxButtons::OK,
								MessageBoxIcon::Error);
							break;
						}

						String^ confirmMessage = String::Format("Вы действительно хотите удалить продукт:\n\nШтри-код: {0}\nНазвание: {1}\nЦена: {2}",
							gcnew String(form->Barcode),
							gcnew String(form->Name),
							gcnew String(form->Price));

						if (MessageBox::Show(confirmMessage, "Подтверждение удаления",
							MessageBoxButtons::YesNo, MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::Yes)
						{
							return;
						}

						productsHashTable->removeByBarcode(newProduct.barcode);

						UpdatePatientDataGridView();
						MessageBox::Show("Продукт успешно удален!",
							"Успех",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);
						break;
					}
					catch (Exception^ ex)
					{
						MessageBox::Show("Ошибка при удалении продукта! ",
							"Ошибка",
							MessageBoxButtons::OK,
							MessageBoxIcon::Error);
					}
				}
			}

			// Поиск пациента
			System::Void найтиПродуктToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
			{
				if (productsHashTable == nullptr)
				{
					MessageBox::Show("Хеш-таблица не инициализирована!\n Сначала загрузите продукты.",
						"Ошибка",
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
							MessageBox::Show("Продукт с указаным штрих-кодом не найдена",
								"Результат поиска",
								MessageBoxButtons::OK,
								MessageBoxIcon::Information);
							break;
						}

						dataTypes::Product product = productArray[hashIndex];

						String^ info = String::Format(
							"Найден продукт:\n\nШтрих-код: {0}\nНазвание: {1}\nЦена: {2}\nКол-во шагов: {3}",
							gcnew String(std::to_string(product.barcode).c_str()),
							gcnew String(product.name.c_str()),
							gcnew String(std::to_string(product.price).c_str()),
							gcnew String(std::to_string(steps).c_str()));

						MessageBox::Show(info, "Результат поиска",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);

						HighlightProduct(std::to_string(product.barcode));
						break;
					}
					catch (Exception^ ex)
					{
						MessageBox::Show("Ошибка при поиске: " + ex->Message,
							"Ошибка",
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

			// Печать хеш-таблицы (уже реализовано в вашем примере)
			System::Void печатьХешТаблицыToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
				/*DebugForm^ debugForm = gcnew DebugForm();
				debugForm->AddDebugText("=== Печать хеш-таблицы пациентов ===");

				if (patientHash != nullptr) {
					std::string hashTableStr = patientHash->printString<hashTable::Patient>(patientMas);
					debugForm->AddDebugText(gcnew System::String(hashTableStr.c_str()));
				}
				else {
					debugForm->AddDebugText("Хеш-таблица не загружена!");
				}

				debugForm->ShowDialog();*/
				throw gcnew System::NotImplementedException();

			}

			// Загрузка записей на прием из файла
			private: System::Void загрузитьПродажиToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
			{

				LoadParametersDialog^ paramsDialog = gcnew LoadParametersDialog();

				int elementsToProcess = paramsDialog->ElementsCount;

				OpenFileDialog^ ofd = gcnew OpenFileDialog();
				ofd->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
				ofd->Title = "Выберите файл с продажами";

				if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					try {
						// Очистка старых данных, если есть
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

						// Заполнение массива продаж из файла
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
						//	// Заполняем дерево по штрих-коду
							int hashIndex = productsHashTable->findByBarcode(salesArray[i].barcode);
							if (hashIndex == -1)
							{
								MessageBox::Show(String::Format("Товара с таким штрих-кодом {0} не существует!", salesArray[i].barcode),
									"Ошибка",
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


						// Заполняем дерево по дате продажи
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
							String::Format("Успешно загружено {0} продаж.", SalesCount),
							"Успех",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);
					}
					catch (Exception^ ex) {
						MessageBox::Show(
							"Ошибка при загрузке: " + ex->Message,
							"Ошибка",
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


			// Сохранение записей на прием в файл
			System::Void сохранитьВФайлДеревоToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
				/*
				1. Открыть диалог сохранения файла
				2. Записать данные из appointMas в файл
				3. Сохранить в том же формате, что и при чтении
				*/
				throw gcnew System::NotImplementedException();
			}

			// Добавление записи на прием
			System::Void добавитьПродажуToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

				{
					if (productsHashTable == nullptr)
					{
						MessageBox::Show("Хеш-таблица не инициализирована!\nСначала загрузите продукты.",
							"Ошибка",
							MessageBoxButtons::OK,
							MessageBoxIcon::Error);
						return;
					}

					SellForm^ form = gcnew SellForm("Добавление продажи");
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
									MessageBox::Show("Товара с таким штрих-кодом не существует!",
										"Ошибка",
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
								MessageBox::Show("Продажа успешно добавлена!",
									"Успех",
									MessageBoxButtons::OK,
									MessageBoxIcon::Information);
								break;
							}
							catch (Exception^ ex)
							{
								MessageBox::Show("Ошибка при добавлении продажи! ",
									"Ошибка",
									MessageBoxButtons::OK,
									MessageBoxIcon::Error);
							}
						}
					}
				}
			}

			// Удаление продажи
			System::Void удалитьПродажуToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
			{
				if (salesArray == nullptr || productsHashTable == nullptr)
				{
					MessageBox::Show("Данные отсутствуют.",
						"Ошибка",
						MessageBoxButtons::OK,
						MessageBoxIcon::Error);
					return;
				}

				SellForm^ form = gcnew SellForm("Удаление продажи");
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
								MessageBox::Show("Невозможно удалить!\n Нет продажи с таким штрих-кодом",
									"Ошибка",
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
							//	MessageBox::Show("Товара с таким штрих-кодом не существует!",
							//		"Ошибка",
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
							MessageBox::Show("Продажа успешно удалена!",
								"Успех",
								MessageBoxButtons::OK,
								MessageBoxIcon::Information);
							break;
						}
						catch (Exception^ ex)
						{
							MessageBox::Show("Ошибка при удалении продажи! ",
								"Ошибка",
								MessageBoxButtons::OK,
								MessageBoxIcon::Error);
						}
					}
				}
			}

			// Поиск записей на прием по номеру ОМС
			System::Void найтиПродажуToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
			{
				if (productsHashTable == nullptr)
				{
					MessageBox::Show("Хеш-таблица продуктов не инициализирована!\nСначала загрузите пациентов.",
						"Ошибка",
						MessageBoxButtons::OK,
						MessageBoxIcon::Error);
					return;
				}

				if (root == nullptr)
				{
					MessageBox::Show("Дерево продаж не инициализировано!\nСначала загрузите приёмы.",
						"Ошибка",
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
							MessageBox::Show("Нет продуктов с указаным штрих-кодом",
								"Результат поиска",
								MessageBoxButtons::OK,
								MessageBoxIcon::Information);
							break;
						}

						dataTypes::Product product = productArray[hashIndex];

						String^ info = String::Format(
							"Найден продукт:\n\nШтрих-код: {0}\nНазвание: {1}\nЦена: {2}\nКол-во шагов: {3}",
							gcnew String(std::to_string(product.barcode).c_str()),
							gcnew String(product.name.c_str()),
							gcnew String(std::to_string(product.price).c_str()),
							gcnew String(std::to_string(steps).c_str()));

						MessageBox::Show(info, "Результат поиска",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);

						HighlightProduct(std::to_string(product.barcode));
						break;
					}
					catch (Exception^ ex)
					{
						MessageBox::Show("Ошибка при поиске: " + ex->Message,
							"Ошибка",
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

			// Печать дерева
			System::Void печатьДереваToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
				/*
				1. Создать DebugForm
				2. Получить текстовое представление дерева
				3. Вывести в DebugForm
				4. Обработать случай, когда дерево пустое
				*/
				throw gcnew System::NotImplementedException();
			}

			// Обработчик кликов по меню (если оставили)
			System::Void menuStrip1_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
				///*
				//1. Можно использовать для общей обработки меню
				//2. Или удалить, если не нужен
				//*/
				//throw gcnew System::NotImplementedException();
			}
	};
}
