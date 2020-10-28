


/*c++ libraries include*/
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <stdarg.h>
/*Rapidjson includes*/
#include "rapidjson/include/rapidjson/filereadstream.h"
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/filewritestream.h"
using namespace rapidjson;
using namespace std;


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
void createJSON(const char* fname, int componentsCount...) {
	FILE* fileCreator = fopen(fname, "ab+");
	fclose(fileCreator);
	std::vector<std::string> tmpVector;
	Document output;
	output.SetObject();
	Document::AllocatorType& allocator = output.GetAllocator();
	Value mainObject(kObjectType);
	Value setObject(kObjectType);
	Value underSetObject(kObjectType);
	Value parameters(kObjectType);
	Value variables(kObjectType);
	Value tmpVal(kObjectType);

	va_list components;
	va_start(components, componentsCount);
	for (int i = 0; i < componentsCount; i++)
	{
		if (componentsCount == 1) {
			tmpVector = va_arg(components, std::vector<std::string>);
			for (int j = 0; j < tmpVector.size(); j++)
			{
				Value name((tmpVector[j]).c_str(), allocator);
				tmpVal.SetString((tmpVector[j]).c_str(), static_cast<SizeType>(tmpVector[j].length()), allocator);
				variables.AddMember(name, tmpVal, allocator);
			}
			output.AddMember("Variables", variables, allocator);

		}
	}
	va_end(components);
	FILE* fp = fopen(fname, "wb"); // non-Windows use "w"

	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	Writer<FileWriteStream> writer(os);
	output.Accept(writer);

	fclose(fp);
}
void test() {
	std::vector<std::string> vars;
	std::map<std::string, std::string>eredmenymap;
	vars.push_back("var1");
	vars.push_back("var2");
	vars.push_back("x");
	createJSON("example.json", 1, vars);
	eredmenymap = JSON_TO_MAP("example.json", "rb");

	for (std::map<std::string, std::string>::iterator it = eredmenymap.begin(); it != eredmenymap.end(); ++it)
	{
		std::cout << it->first << '\t' << it->second << '\n';
	}
}