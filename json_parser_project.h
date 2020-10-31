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
#include "filewritestream.h"
#include "prettywriter.h"

typedef std::vector<std::string> STLCONTAINER;

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
Value objectCreator(STLCONTAINER next, Document&output) {
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
Value setOfSetsCreator(STLCONTAINER next, Document&output) {
	Value ret(kObjectType);
	Value name(kStringType);
	Value val(kObjectType);
	Document::AllocatorType& allocator = output.GetAllocator();
	for (STLCONTAINER::iterator it = next.begin(); it != next.end(); ++it) {
		Value tmpSet(kObjectType);
		std::string tmp = *it;
		std::string tmpVal = tmp;
		std::string tmpName = tmp + "_name";
		tmpVal = toupper(tmp[0]);
		val.SetString(tmpVal.c_str(), static_cast<SizeType>(tmpVal.length()), allocator);
		name.SetString(tmpName.c_str(), allocator);
		tmpSet.AddMember(name, val, allocator);
		tmpName = tmp + "_default-index";
		tmpVal = tolower(tmp[0]);
		val.SetString(tmpVal.c_str(), static_cast<SizeType>(tmpVal.length()), allocator);
		name.SetString(tmpName.c_str(), allocator);
		tmpSet.AddMember(name, val, allocator);
		ret.AddMember(Value(tmp.c_str(), static_cast<SizeType>(tmp.length()), allocator), tmpSet, allocator);
	}
	return ret;
}

Document createJson(int componentsCount...) {

	STLCONTAINER tmpVector;
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
			if (i == 0) { output.AddMember("Sets", setOfSetsCreator(tmpVector, output), output.GetAllocator()); }
			else if (i == 1) { output.AddMember("Parameters", objectCreator(tmpVector, output), output.GetAllocator()); }
			else if (i == 2) { output.AddMember("Variables", objectCreator(tmpVector, output), output.GetAllocator()); }
		}
	}
	va_end(components);
	return output;
}
void writeToFile(const char*fname,const char*mod, Document&output) {
	FILE* fileCreator = fopen(fname, "ab+");
	fclose(fileCreator);
	FILE* fp = fopen(fname, mod); // non-Windows use "w"
	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	PrettyWriter<FileWriteStream> pwriter(os);
	output.Accept(pwriter);
	fclose(fp);
}