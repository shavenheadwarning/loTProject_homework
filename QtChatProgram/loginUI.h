#pragma once

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>


#include "ui_LoginIn.h"
#include "components.h"


class LoginInUI :public QDialog {

	Q_OBJECT
public:
	LoginInUI(QDialog* parent = Q_NULLPTR);
	LoginInUI(ComponentClient*,QDialog* parent = Q_NULLPTR);
	ComponentClient* clientComponetPtr;


	QString userName;

signals:
	void showmain();


private:
	Ui::loginIn ui;
private slots:
	void getInputUserName();



};
