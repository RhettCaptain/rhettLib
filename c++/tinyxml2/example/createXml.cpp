#include "../tinyxml2.h"

using namespace tinyxml2;

int createXML(const char* xmlPath){
	const char* dec1 = "<im dec>";
	XMLDocument doc;
	doc.Parse(dec1);

	XMLDeclaration* dec2 = doc.NewDeclaration();
	doc.InsertFirstChild(dec2);
	
	XMLElement* root= doc.NewElement("im ele");
	doc.InsertEndChild(root);

	return doc.SaveFile(xmlPath);
}

int insertXMLNode(const char* xmlPath){
	XML
}
int main(){
	createXML("create.xml");
}
