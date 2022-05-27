
#include <QDebug>

#include "loginUI.h"


//LoginInUI构造函数
//parameter：
//			ComPtr：指向存在ComponentClient的指针
LoginInUI::LoginInUI(ComponentClient* ComPtr,QDialog* parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	clientComponetPtr = ComPtr;

	QObject::connect(ui.loginButton, &QPushButton::clicked, this, &LoginInUI::getInputUserName);
}


//点击login in,读取输入的用户名。
void LoginInUI::getInputUserName() {
	auto _userName = ui.lineEdit->text();
	if (_userName.size() == 0) {
		QMessageBox alarm(QMessageBox::NoIcon, "ERROR", "user name can't be empty!");
		alarm.exec();
		
	}
	else {
		this->clientComponetPtr->clientUserName = _userName.toStdString();
		//qDebug() << this ->userName;
		this->hide();
		emit showmain();
	}
}

