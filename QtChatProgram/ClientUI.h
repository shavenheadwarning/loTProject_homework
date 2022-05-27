#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ClientUI.h"


#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <qmessagebox.h>


#include "components.h"
#include <QStringListModel>

class ClientUI :public QMainWindow
{
	Q_OBJECT

public:
	
	ClientUI(QWidget* parent = Q_NULLPTR);
	ClientUI(ComponentClient*, QWidget* parent = Q_NULLPTR);
	
	
	

	QStringList selectUserList;
	ComponentClient *clientComponetPtr;
	QStringListModel usrListModel;
	QVector<QStandardItem> usrNameItems;
public slots:
	void ShowClientUI();

signals:
	void updateBrowser();
	void updateOnlineUserlistView(const QString);
	


private:

	void GetselectUserList();
	void GenerateBuffToServer(const QString&, QStringList*);

	Ui::ChatClient ui;
private slots:
	void InitiateClientSocket();
	void ClickedSendMsgToServer();
	void GetOnlineUsers();
	void UpdateTextBrowser();
	void UpdateOnlineUserlist(const QString);





};

