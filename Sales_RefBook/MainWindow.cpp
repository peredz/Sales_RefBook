#include "MainWindow.h"
#include <locale.h>

using namespace System;
using namespace System::Windows::Forms;

// Аттрибут отдельного потока данных
[STAThreadAttribute]
int main(cli::array<System::String^>^ args)
{
    setlocale(LC_ALL, "Russian");
    Application::SetCompatibleTextRenderingDefault(false);
    Application::EnableVisualStyles();

    SalesRefBook::MainWindow window;
    Application::Run(% window);

    return 0;
}