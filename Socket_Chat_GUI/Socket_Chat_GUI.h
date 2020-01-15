#pragma once

namespace SocketChatGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Net::Sockets;
	using namespace System::Net;
	using namespace System::Diagnostics;
	using namespace System::Threading;
	using namespace System::Text;

	/// <summary>
	/// Summary for Socket_Chat_GUI
	/// </summary>
	public ref class Socket_Chat_GUI : public System::Windows::Forms::Form
	{
	public: 
		static String^ s;
	public:
		Socket_Chat_GUI(void)
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
		~Socket_Chat_GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btn_connect;
	protected:

	protected:
	public:
		SocketType serverType = SocketType::Stream;
		ProtocolType severProtocol = ProtocolType::Tcp;
		AddressFamily serverFamily = AddressFamily::InterNetwork;
	public:
		Socket^ serverSocket = gcnew Socket(serverFamily, serverType, severProtocol);
		//System::Threading::Thread RecvTask(RecvFunc);
	private: System::Windows::Forms::TextBox^ txt_IP_Server;
	public:


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ txt_recv;

	private: System::Windows::Forms::Button^ btn_send;
	private: System::Windows::Forms::TextBox^ txt_send;


	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->btn_connect = (gcnew System::Windows::Forms::Button());
			this->txt_IP_Server = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txt_recv = (gcnew System::Windows::Forms::TextBox());
			this->btn_send = (gcnew System::Windows::Forms::Button());
			this->txt_send = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// btn_connect
			// 
			this->btn_connect->Location = System::Drawing::Point(371, 23);
			this->btn_connect->Name = L"btn_connect";
			this->btn_connect->Size = System::Drawing::Size(75, 23);
			this->btn_connect->TabIndex = 0;
			this->btn_connect->Text = L"Connect";
			this->btn_connect->UseVisualStyleBackColor = true;
			this->btn_connect->Click += gcnew System::EventHandler(this, &Socket_Chat_GUI::btn_connect_Click);
			// 
			// txt_IP_Server
			// 
			this->txt_IP_Server->Location = System::Drawing::Point(110, 26);
			this->txt_IP_Server->Name = L"txt_IP_Server";
			this->txt_IP_Server->Size = System::Drawing::Size(233, 20);
			this->txt_IP_Server->TabIndex = 1;
			this->txt_IP_Server->Text = L"192.168.5.107";
			this->txt_IP_Server->TextChanged += gcnew System::EventHandler(this, &Socket_Chat_GUI::txt_IP_Server_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(35, 29);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Connect to";
			// 
			// txt_recv
			// 
			this->txt_recv->Location = System::Drawing::Point(26, 74);
			this->txt_recv->Multiline = true;
			this->txt_recv->Name = L"txt_recv";
			this->txt_recv->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txt_recv->Size = System::Drawing::Size(420, 199);
			this->txt_recv->TabIndex = 3;
			// 
			// btn_send
			// 
			this->btn_send->Location = System::Drawing::Point(26, 300);
			this->btn_send->Name = L"btn_send";
			this->btn_send->Size = System::Drawing::Size(75, 23);
			this->btn_send->TabIndex = 0;
			this->btn_send->Text = L"Send";
			this->btn_send->UseVisualStyleBackColor = true;
			this->btn_send->Click += gcnew System::EventHandler(this, &Socket_Chat_GUI::btn_send_Click);
			// 
			// txt_send
			// 
			this->txt_send->Location = System::Drawing::Point(124, 302);
			this->txt_send->Name = L"txt_send";
			this->txt_send->Size = System::Drawing::Size(322, 20);
			this->txt_send->TabIndex = 1;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &Socket_Chat_GUI::timer1_Tick);
			// 
			// Socket_Chat_GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(470, 335);
			this->Controls->Add(this->txt_recv);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txt_send);
			this->Controls->Add(this->txt_IP_Server);
			this->Controls->Add(this->btn_send);
			this->Controls->Add(this->btn_connect);
			this->Name = L"Socket_Chat_GUI";
			this->Text = L"Socket_Chat_GUI";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: static void connectFunc()
{
	SocketType serverType = SocketType::Stream;
	ProtocolType severProtocol = ProtocolType::Tcp;
	AddressFamily serverFamily = AddressFamily::InterNetwork;
	Socket^ sendSocket = gcnew Socket(serverFamily, serverType, severProtocol);

	System::Net::EndPoint^ RecvEP = gcnew System::Net::IPEndPoint(System::Net::IPAddress::Parse("192.168.5.107"), 1234);
	sendSocket->Bind(RecvEP);
	sendSocket->Listen(5);
	while (true)
	{
		Socket^ clientSock = sendSocket->Accept();
		Debug::WriteLine("have request connection");
		Debug::WriteLine("client: " + clientSock->RemoteEndPoint->ToString());
		array<unsigned char>^ buff = gcnew array<unsigned char>(1024);
		while (true)
		{
			int byteSend = clientSock->Receive(buff);
			if (byteSend > 0)
			{
				Debug::WriteLine(Encoding::UTF8->GetString(buff));
				s = "Recv: " + Encoding::UTF8->GetString(buff) + "\r\n";
				clientSock->Close();
				break;
			}
		}
	}

}
private: System::Void btn_connect_Click(System::Object^ sender, System::EventArgs^ e) {
	ThreadStart^ RecvFunc = gcnew ThreadStart(connectFunc);
	Thread^ th1 = gcnew Thread(RecvFunc);
	th1->Start();
}
private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
	txt_recv->Text += s;
	s = "";
}
private: System::Void btn_send_Click(System::Object^ sender, System::EventArgs^ e) {
	SocketType serverType = SocketType::Stream;
	ProtocolType severProtocol = ProtocolType::Tcp;
	AddressFamily serverFamily = AddressFamily::InterNetwork;
	Socket^ sendSocket = gcnew Socket(serverFamily, serverType, severProtocol);

	/*sendSocket->Connect(this->IPServerTXT->Text, 1234);*/
	System::Net::EndPoint^ RecvEP = gcnew System::Net::IPEndPoint(System::Net::IPAddress::Parse(txt_IP_Server->Text), 3333);
	sendSocket->Connect(RecvEP);

	try
	{
		array<unsigned char>^ msgToSend = gcnew array<unsigned char>(1024);
		System::Text::ASCIIEncoding^ ascii = gcnew System::Text::ASCIIEncoding();
		ascii->GetBytes(txt_send->Text, 0, txt_send->Text->Length, msgToSend, 0);
		System::Net::Sockets::SocketFlags flag = System::Net::Sockets::SocketFlags::None;
		sendSocket->Send(msgToSend, txt_send->Text->Length, flag);
		s = "send: " + txt_send->Text + "\r\n";

	}
	catch (...)
	{
		Debug::WriteLine("Send fales");
	}
	sendSocket->Disconnect(false);
	sendSocket->Close();
}
private: System::Void txt_IP_Server_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
