#include "../tinyxml2.h"
#include <iostream>
#include <cstring>
using namespace tinyxml2;
using namespace std;

XMLElement* queryUserNodeByName(XMLElement* root){
	XMLElement *userNode = root->FirstChildElement("User");
	while(userNode!=NULL){
		cout << userNode->Attribute("Name")<<endl;
		cout << userNode->Attribute("Password")<<endl;
		char* n ="2";
		if(strcmp(const_cast<char*>(userNode->Attribute("Name")),n) == 0)
		//	cout << "tg" << endl;
			break;
		userNode = userNode->NextSiblingElement();
	}
	return userNode;
}

int main(){
	XMLDocument doc;
	if(doc.LoadFile("query.xml")!=0){
		cout << "load fail" << endl;
	}
	XMLElement *root = doc.RootElement();
	XMLElement* userNode=queryUserNodeByName(root);

	if(userNode!=NULL){
		cout << userNode->Attribute("Name") <<"-" << userNode->Attribute("Password") << endl;
	}
	else{
		cout << "nnn" << endl;
	}
}
