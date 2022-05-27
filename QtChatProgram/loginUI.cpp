
#include <QDebug>

#include "loginUI.h"


//LoginInUI���캯��
//parameter��
//			ComPtr��ָ�����ComponentClient��ָ��
LoginInUI::LoginInUI(ComponentClient* ComPtr,QDialog* parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	clientComponetPtr = ComPtr;

	QObject::connect(ui.loginButton, &QPushButton::clicked, this, &LoginInUI::getInputUserName);
}


//���login in,��ȡ������û�����
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

