

#include "user.h"

//��ȡʵ���洢��usr name ,תΪԼ���ĸ�ʽ�����ڷ��͸�client
std::string Users::GetUserNameList() {
	std::string result="0";
	for (auto usr : usrMap) {
		result += "," + (usr.first);
	}
	return result;
}