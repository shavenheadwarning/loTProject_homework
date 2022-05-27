
#include "ClientUI.h"


#include "utils.h"
#include "client.h"
#include "threadFunction.h"
#include <QDebug>



//构造函数
ClientUI::ClientUI(ComponentClient* ComPtr,QWidget* parent)
	:QMainWindow(parent) 
{	
	ui.setupUi(this);

	//bind button with event
	QObject::connect(ui.connectToServerButton, &QPushButton::clicked, this, &ClientUI::InitiateClientSocket);
	QObject::connect(ui.sendMessageButton, &QPushButton::clicked, this, &ClientUI::ClickedSendMsgToServer);
	QObject::connect(ui.getOnlineUsers, &QPushButton::clicked, this, &ClientUI::GetOnlineUsers);
	QObject::connect(this, SIGNAL(updateBrowser()), this, SLOT(UpdateTextBrowser()));
	QObject::connect(this, SIGNAL(updateOnlineUserlistView(const QString)), this, SLOT(UpdateOnlineUserlist(const QString)));


	clientComponetPtr = ComPtr;

}


void ClientUI::ShowClientUI() {
	this->show();
	ui.myUsrName->setText(QString("my usr name: ") + QString(clientComponetPtr->clientUserName.c_str()));
}



//if clicked connect to server,get user name and send to server
//and start some threads
void ClientUI::InitiateClientSocket() {
	// connect to server
	InitializeWinsock();
	
	SOCKET tSocket = ConnectToServer();
	clientComponetPtr->SetServerSocket(tSocket);

	
	//create thread for recv msg from server
	if (tSocket == INVALID_SOCKET) {
		QMessageBox alarm(QMessageBox::NoIcon, "ERROR", "connect to server failed");
		alarm.exec();
		return;
	}
	//show msg if connect successfully
	QMessageBox alarm(QMessageBox::NoIcon, "ERROR", "connect to server successfully");
	alarm.exec();
	

	//偷偷把 username 发给 服务端
	auto _userName ="3"+this->clientComponetPtr->clientUserName;
	send(tSocket, _userName.c_str(), _userName.size(), 0);


		//extern RecvThreadData recvdata;
		RecvThreadData* recvdata = new RecvThreadData;
		recvdata->msgQueuePtr = &(clientComponetPtr->msgQueue);
		recvdata->recvSockt = clientComponetPtr->GetServerSocket();
		recvdata->usrlistSet= &(clientComponetPtr->usrnameSet);
		recvdata->window = this;
		
		UpdateUsrListData* updateData = new UpdateUsrListData;
		updateData->recvSockt = clientComponetPtr->GetServerSocket();

		HANDLE recvThread = CreateThread(NULL, 1024, RecvMessageFromServer, recvdata, 0, NULL);

	
	
	return;
}


//发送信息到服务端
//send buffer format: "1,ToWho,From Who,content"
void ClientUI::ClickedSendMsgToServer() {
	QString textContent=ui.inputMessageText->toPlainText();
	
	auto bufferList = new QStringList;
	GetselectUserList();
	GenerateBuffToServer(textContent, bufferList);


	auto textLength = textContent.size();
	if (textLength != 0){
		for (auto buff : *bufferList) {
			
			send(clientComponetPtr->GetServerSocket(),buff.toLatin1().data(), buff.size(), 0);
		}
		delete bufferList;
		ui.inputMessageText->clear();
	}
}



//发送获取当前在线的usersd的请求
//format :2,myusrname
void ClientUI::GetOnlineUsers() {

	auto msgStr="2,"+clientComponetPtr->clientUserName;
	send(clientComponetPtr->sockerToServer, msgStr.c_str(), msgStr.size(), 0);
	return;
}


//更新聊天框 
//buffer format: "1,name,content"
void ClientUI::UpdateTextBrowser() {
	//qDebug() << QString((int)this->clientComponet.msgQueue.size());
	if (this->clientComponetPtr->msgQueue.size() != 0) {
		auto msgStr = this->clientComponetPtr->msgQueue.front();
		printf("%s", msgStr);
		auto msgbuff = msgStr.split(',');
		ui.messageBrowser->append(QString("from ")+msgbuff[1]+QString(": "));
		ui.messageBrowser->append(msgbuff[2]);
		this->clientComponetPtr->msgQueue.dequeue();
	}

}


//更新在线用户列表
//parameter：
//	buffer：buffer recv from server (format "0,name1,name2,name3")
void ClientUI::UpdateOnlineUserlist(const QString buffer) {
	qDebug() << buffer;
	QStringList nameList = buffer.split(',');
	nameList.removeFirst();
	usrListModel.setStringList(nameList);
	ui.onlineUserList->setModel(&usrListModel);
	
	
	return;
}



//获取用户选择发送消息的用户列表
void ClientUI::GetselectUserList() {
	auto selected= ui.onlineUserList->selectionModel()->selectedIndexes();
	selectUserList.clear();
	for (const auto usr : selected) {
		
		selectUserList.append(usr.data().toString());
	}
	
	//qDebug() << "here";
	//selectUserList = selectedtUsers.value<QList<QString>>();
	return;
}


//按照约定的格式发送消息buffer给server
//format: "1,toWho,fromWho,content"
void ClientUI::GenerateBuffToServer(const QString& msg, QStringList* QbufferList) {
	for (auto name : this->selectUserList) {
		QbufferList->append(QString("1,")+name+QString(",") + QString(clientComponetPtr->clientUserName.c_str())+ QString(",") + msg);
	}
	return;
}
