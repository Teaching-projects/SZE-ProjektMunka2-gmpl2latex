# Documentation

## Prerequisite
- Clone this repository: https://github.com/Tencent/rapidjson/tree/master
- Follow instructions under Installation
- Copy the rapidjson source directory and json_parser_project.h file to your source directory.
- Include json_parser_project.h where you want to use those functions which implemented in it.

## Using
### Create JSON file from STL container:
1. Create a document object 
~~~cpp
/*Example code*/
rapidjson::Document output;
~~~
2. Call createJson function with the following arrguments:
  * componentsCount: represent how many STLCONTAINER passed to the function
  * If componentsCount not equal to 1 then use the following order of stl containers Sets,Parameters,Variables
~~~cpp
/*Example code*/
output=createJson(3,sets,parameters,variables);
~~~
3. Call writeToFile function with the following arguments:
  * fname: a json file name where you want to write json output.
  * mode: file open mode. It's value is "r" on Linux and "rb" on Windows
  * output: a document object which created in 1 step.
~~~cpp
/*Example code*/
writeToFile("dictonary.json","w"output);
~~~
### Parse json file to STL container
1. Create a suitable STL:
~~~cpp
/*Example code*/
std::map<std::string,std::string>keyValuePairs;
~~~
2. Call jsonToMap function with the next two arguments:
  * fname: a correct json file,
  * mode: file open mode. It's value is "r" on Linux and "rb" on Windows
~~~cpp
/*Example code*/
keyValuePairs=jsonToMap("dictionary.json","r");
~~~