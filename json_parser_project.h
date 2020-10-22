


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
//Header contains declaration


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
std::map<std::string, std::string>JSON_TO_MAP(const char* fname,const char*mod) {
	std::map<std::string, std::string> eredmenyMap;
	FILE*fp = fopen(fname, mod);
	char buffer[65000];
	rapidjson::FileReadStream is(fp, buffer, sizeof(buffer));
	rapidjson::Document object;
	object.ParseStream(is);
	if (object.IsObject() == false) {
		throw "File structure isn't suitable";

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
