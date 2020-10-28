# Prerequisite
- Clone this repository: https://github.com/Tencent/rapidjson/tree/master
- Follow instructions under Installation
- Copy the rapidjson source directory and json_parser_project.h file to your source directory.
- Include json_parser_project.h where you want to use those functions which implemented in it.

# How to use

Call JSON_TO_MAP function with the next two arguments:

fname: a correct json file,
mode: file open mode. It's value is "r" on Linux and "rb" on Windows