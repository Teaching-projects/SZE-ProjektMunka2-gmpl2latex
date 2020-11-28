/*c++ libraries include*/
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <stdarg.h>
#include <list>
/*Rapidjson includes*/
#include "filereadstream.h"
#include "document.h"
#include "filewritestream.h"
#include "prettywriter.h"
#include "Variable.hpp"
typedef std::list<Variable> STLCONTAINER;

void objectParser(rapidjson::Value::ConstObject o, std::map<std::string, std::string>&eredmenyMap) {

	for (rapidjson::Value::ConstMemberIterator it = o.MemberBegin(); it != o.MemberEnd(); ++it)
	{
		if (it->value.IsObject())
		{
			objectParser(it->value.GetObject(), eredmenyMap);
		}
		else
		{
			eredmenyMap.emplace(std::make_pair<std::string, std::string>(it->name.GetString(), it->value.GetString()));
		}
	}
}
std::map<std::string, std::string>jsonToMap(const char* fname, const char*mod)
{
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
		if (it->value.IsObject())
		{
			objectParser(it->value.GetObject(), eredmenyMap);
		}
		else
		{
			eredmenyMap.emplace(std::make_pair<std::string, std::string>(it->name.GetString(), it->value.GetString()));
		}

	}
	return eredmenyMap;

}
rapidjson::Value objectCreator(const STLCONTAINER& next, rapidjson::Document&output) {
	rapidjson::Value ret(rapidjson::kObjectType);
	rapidjson::Value name(rapidjson::kStringType);
	rapidjson::Value val(rapidjson::kObjectType);
	rapidjson::Document::AllocatorType& allocator = output.GetAllocator();
	for (auto it: next) {
		Variable tmp = it;
		val.SetString(it.getInTex().c_str(), static_cast<rapidjson::SizeType>(it.getInTex().length()), allocator);
		name.SetString(tmp.getID().c_str(), allocator);
		ret.AddMember(name, val, allocator);
	}
	return ret;
}

rapidjson::Document createJson(int componentsCount, const STLCONTAINER& tmpVector) {

	rapidjson::Document output;
	output.SetObject();
	va_list components;
	if (componentsCount == 1) {
		output.AddMember("Variables", objectCreator(tmpVector, output), output.GetAllocator());
	}
	else
	{
		std::cerr << "The program doesn't support a complex example at the moment" << std::endl;
	}
	va_end(components);
	return output;
}
void writeToFile(const char*fname, const char*mod, rapidjson::Document&output) {
	FILE* fileCreator = fopen(fname, "ab+");
	fclose(fileCreator);
	FILE* fp = fopen(fname, mod); // non-Windows use "w"
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	rapidjson::PrettyWriter<rapidjson::FileWriteStream> pwriter(os);
	output.Accept(pwriter);
	fclose(fp);
}