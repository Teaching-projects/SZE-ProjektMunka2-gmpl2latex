#include <iostream>
/*c++ libraries include*/
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <stdarg.h>
/*Rapidjson includes*/
#include "filereadstream.h"
#include "document.h"
#include "writer.h"
#include "filewritestream.h"
#include "prettywriter.h"
//Header contains declaration
using namespace rapidjson;
using namespace std;

typedef std::vector<std::string> STLCONTAINER;

void ObjectParser(rapidjson::Value::ConstObject o, std::map<std::string, std::string>&eredmenyMap) {

	for (rapidjson::Value::ConstMemberIterator it = o.MemberBegin(); it != o.MemberEnd(); ++it) {

		if (it->value.IsObject()) {
			ObjectParser(it->value.GetObject(), eredmenyMap);
		}
		else
		{
			//printf("Fuggvenyen belul irodik ki %d szinten\n",melyseg);
			//printf("\nNev: %s, Ertek: %s\n", it->name.GetString(), it->value.GetString());

			//pair<std::string, std::string>p = std::make_pair<std::string, std::string>(a, b);
			eredmenyMap.emplace(std::make_pair<std::string, std::string>(it->name.GetString(), it->value.GetString()));
			//std::cout << "A meyseg valtozatlanul a fuggvenyen belul" << melyseg << std::endl;
		}
	}


}
std::map<std::string, std::string>JSON_TO_MAP(const char* fname, const char*mod) {
	std::map<std::string, std::string> eredmenyMap;
	FILE*fp = fopen(fname, mod);
	char buffer[65000];
	rapidjson::FileReadStream is(fp, buffer, sizeof(buffer));
	rapidjson::Document object;
	object.ParseStream(is);
	if (object.IsObject() == false) {
		throw ("File structure isn't suitable");

	}
	for (rapidjson::Value::ConstMemberIterator it = object.MemberBegin(); it != object.MemberEnd(); ++it)
	{
		if (it->value.IsObject()) {

			ObjectParser(it->value.GetObject(), eredmenyMap);
			//eredmenyMap.emplace(std::make_pair<std::string, std::string>(it->name.GetString(), it->value.GetString()));

		}
		/*if (it->value.IsString()) {
							eredmenyMap.emplace(std::make_pair<std::string, std::string>(it->name.GetString(), it->value.GetString()));
					}*/
		else
		{
			//printf("Fuggvenyen kivul irodik ki\n");
			//printf("Nev: %s Ertek: %s\n", it->name.GetString(), it->value.GetString());
			eredmenyMap.emplace(std::make_pair<std::string, std::string>(it->name.GetString(), it->value.GetString()));
		}

	}
	return eredmenyMap;

}
Value ObjectCreator(STLCONTAINER next,Document&output) {
	Value ret(kObjectType);
	Value name(kStringType);
	Value val(kObjectType);
	Document::AllocatorType& allocator = output.GetAllocator();
	for (STLCONTAINER::iterator it = next.begin(); it != next.end(); ++it) {
		std::string tmp = *it;
		val.SetString((*it).c_str(), static_cast<SizeType>((*it).length()), allocator);
		name.SetString(tmp.c_str(), allocator);
		ret.AddMember(name, val, allocator);
	}
	return ret;
}
Value setofSetsCreator(STLCONTAINER next, Document&output) {
	Value ret(kObjectType);
	Value name(kStringType);
	Value val(kObjectType);
	Document::AllocatorType& allocator = output.GetAllocator();
	for (STLCONTAINER::iterator it = next.begin(); it != next.end(); ++it) {
		Value tmpSet(kObjectType);
		std::string tmp = *it;
		std::string tmpVal = tmp;
		std::string tmpName = tmp+"_name";
		tmpVal = toupper(tmp[0]);
		val.SetString(tmpVal.c_str(), static_cast<SizeType>(tmpVal.length()), allocator);
		name.SetString(tmpName.c_str(), allocator);
		tmpSet.AddMember(name, val, allocator);
		tmpName = tmp+"_default-index";
		tmpVal = tolower(tmp[0]);
		val.SetString(tmpVal.c_str(), static_cast<SizeType>(tmpVal.length()), allocator);
		name.SetString(tmpName.c_str(), allocator);
		tmpSet.AddMember(name, val, allocator);
		ret.AddMember(Value(tmp.c_str(), static_cast<SizeType>(tmp.length()), allocator), tmpSet, allocator);
	}
	return ret;
}

Document createJSON(int componentsCount...) {

	std::vector<std::string> tmpVector;
	Document output;
	output.SetObject();
	va_list components;
	va_start(components, componentsCount);
	if (componentsCount == 1) {
		tmpVector = va_arg(components, STLCONTAINER);
		output.AddMember("Variables", ObjectCreator(tmpVector, output), output.GetAllocator());
	}
	else
	{
		for (int i = 0; i < componentsCount; i++)
		{
			tmpVector = va_arg(components, STLCONTAINER);
			if (i == 0) { output.AddMember("Sets", setofSetsCreator(tmpVector, output), output.GetAllocator()); }
			else if (i == 1) { output.AddMember("Parameters", ObjectCreator(tmpVector, output), output.GetAllocator()); }
			else if (i == 2) { output.AddMember("Variables", ObjectCreator(tmpVector, output), output.GetAllocator()); }
			/*{
			case 0:output.AddMember("Sets", setofSetsCreator(tmpVector, output), output.GetAllocator());
				break;
			case 1:output.AddMember("Parameters", ObjectCreator(tmpVector,output), output.GetAllocator());
				break;
			case 2:output.AddMember("Variables", ObjectCreator(tmpVector, output), output.GetAllocator());
				break;
			}*/

		}
	}
	va_end(components);
	return output;
	//output.AddMember("Sets", setObject, output.GetAllocator());


}
void writeToFile(const char*fname, Document&output) {
	FILE* fileCreator = fopen(fname, "ab+");
	fclose(fileCreator);
	FILE* fp = fopen(fname, "wb"); // non-Windows use "w"
	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	PrettyWriter<FileWriteStream> pwriter(os);
	output.Accept(pwriter);
	fclose(fp);
}


int main()
{
	std::vector<std::string> setst;
	std::vector<std::string> params;
	std::vector<std::string> vars;
	std::map<std::string, std::string>eredmenymap;
	Document output;
	vars.push_back("var1");
	vars.push_back("var2");
	vars.push_back("x");
	params.push_back("p1");
	params.push_back("p2");
	setst.push_back("Resources");
	setst.push_back("Products");
	output=createJSON(3,setst,params,vars);
	writeToFile("example.json", output);
	eredmenymap=JSON_TO_MAP("example.json", "rb");

	/*for (std::map<std::string, std::string>::iterator it=eredmenymap.begin();it!=eredmenymap.end();++it)
	{
		std::cout << it->first << '\t' << it->second << '\n';
	}*/
	
}
