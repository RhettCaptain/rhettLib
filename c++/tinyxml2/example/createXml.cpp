#include "../tinyxml2.h"
#include <iostream>

using namespace tinyxml2;
using namespace std;
int createXML(const char* xmlPath){
	const char* dec1 = "<im dec>";
	XMLDocument doc;
	doc.Parse(dec1);

	XMLDeclaration* dec2 = doc.NewDeclaration();
	doc.InsertFirstChild(dec2);
	
	XMLElement* root= doc.NewElement("imele");
	doc.InsertEndChild(root);

	return doc.SaveFile(xmlPath);
}

int insertXMLNode(const char* xmlPath){
	XMLDocument doc;
	int res=doc.LoadFile(xmlPath);
	if(res!=0){
		cout << "load file failed" << endl;
		return res;
	}
	XMLElement* root = doc.RootElement();
	XMLElement* userNode = doc.NewElement("User");
	userNode->SetAttribute("Name","rhett");
	userNode->SetAttribute("Password","123");
	root->InsertEndChild(userNode);
		
	XMLElement* r = doc.NewElement("rr");
	doc.InsertEndChild(r);
	return doc.SaveFile(xmlPath);
}
int main(){
	createXML("create.xml");
	insertXMLNode("create.xml");
}
