
#include <QtWidgets/QApplication>
#include <QTextCodec>

#include "loginUi.h"
#include "ClientUI.h"
#include "components.h"

int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    //QtChatProgram w;
    ComponentClient Components;
    ClientUI c_window(&Components);
    LoginInUI l_window(&Components);
    


    l_window.show();
    //登录页面跳转聊天页面
    QObject::connect(&l_window, SIGNAL(showmain()), &c_window, SLOT(ShowClientUI()));
    
    
    return a.exec();
}


