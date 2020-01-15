#include "Socket_Chat_GUI.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThreadAttribute]
int main(array<String^>^ args) {
    // MyForm init
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    //WinformCDemo is your project name
    SocketChatGUI::Socket_Chat_GUI form;
    Application::Run(% form);
    return 0;
}