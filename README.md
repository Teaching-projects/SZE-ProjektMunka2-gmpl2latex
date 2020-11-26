# SZE-ProjektMunka2-gmpl2latex

The program can read a GMPL language .mod file, then list the variables in a json file, in which the user can modify the value of the keys when needed.
After that, by running the program with the correct flags, it generates a latex document from the .mod file with appropriate formatting and using the optionally modified variable names.

## Usage:
### To generate the json file:
gmpl2latex [input.mod] --createjson [vars.mod]

### To generate the latex file:
gmpl2latex [input.mod] --readjson [vars.mod] --outputtex [example.tex]

<br>

Only .l and .y files, use Flex-Bison to generate .c files.
