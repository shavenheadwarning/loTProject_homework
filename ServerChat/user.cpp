

#include "user.h"

//获取实例存储的usr name ,转为约定的格式，用于发送给client
std::string Users::GetUserNameList() {
	std::string result="0";
	for (auto usr : usrMap) {
		result += "," + (usr.first);
	}
	return result;
}