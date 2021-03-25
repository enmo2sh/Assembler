#include "operations.h"
#include <iostream>
#include <map>
#include <vector>
using namespace std;

map<string, int> getformat()
{
    map<string, int> format ;
    format.clear();
    format.insert(pair<string, int>("ADD", 3));
    format.insert(pair<string, int>("ADDF", 3));
    format.insert(pair<string, int>("ADDR", 2));
    format.insert(pair<string, int>("AND", 3));
    format.insert(pair<string, int>("CLEAR", 2));
    format.insert(pair<string, int>("COMP", 3));
    format.insert(pair<string, int>("COMPF", 3));
    format.insert(pair<string, int>("COMPR", 2));
    format.insert(pair<string, int>("DIV", 3));
    format.insert(pair<string, int>("DIVF", 3));
    format.insert(pair<string, int>("DIVR", 2));
    format.insert(pair<string, int>("FIX", 1));
    format.insert(pair<string, int>("FLOAT", 1));
    format.insert(pair<string, int>("HIO", 1));
    format.insert(pair<string, int>("J", 3));
    format.insert(pair<string, int>("JEQ", 3));
    format.insert(pair<string, int>("JGT", 3));
    format.insert(pair<string, int>("JLT", 3));
    format.insert(pair<string, int>("JSUB", 3));
    format.insert(pair<string, int>("LDA", 3));
    format.insert(pair<string, int>("LDB", 3));
    format.insert(pair<string, int>("LDCH", 3));
    format.insert(pair<string, int>("LDF", 3));
    format.insert(pair<string, int>("LDL", 3));
    format.insert(pair<string, int>("LDS", 3));
    format.insert(pair<string, int>("LDT", 3));
    format.insert(pair<string, int>("LDX", 3));
    format.insert(pair<string, int>("LPS", 3));
    format.insert(pair<string, int>("MUL", 3));
    format.insert(pair<string, int>("MULF", 3));
    format.insert(pair<string, int>("MULR", 2));
    format.insert(pair<string, int>("NORM", 1));
    format.insert(pair<string, int>("OR", 3));
    format.insert(pair<string, int>("RD", 3));
    format.insert(pair<string, int>("RMO", 2));
    format.insert(pair<string, int>("RSUB", 3));
    format.insert(pair<string, int>("SHIFTL", 2));
    format.insert(pair<string, int>("SHIFTR", 2));
    format.insert(pair<string, int>("SIO", 1));
    format.insert(pair<string, int>("SSK", 3));
    format.insert(pair<string, int>("STA", 3));
    format.insert(pair<string, int>("STB", 3));
    format.insert(pair<string, int>("STCH", 3));
    format.insert(pair<string, int>("STF", 3));
    format.insert(pair<string, int>("STI", 3));
    format.insert(pair<string, int>("STL", 3));
    format.insert(pair<string, int>("STS", 3));
    format.insert(pair<string, int>("STSW", 2));
    format.insert(pair<string, int>("STT", 2));
    format.insert(pair<string, int>("STX", 1));
    format.insert(pair<string, int>("SUB", 3));
    format.insert(pair<string, int>("SUBF", 3));
    format.insert(pair<string, int>("SUBR", 2));
    format.insert(pair<string, int>("SVC", 2));
    format.insert(pair<string, int>("TD", 3));
    format.insert(pair<string, int>("TIO", 1));
    format.insert(pair<string, int>("TIX", 3));
    format.insert(pair<string, int>("TIXR", 2));
    format.insert(pair<string, int>("WD", 3));
    return format;
}

map<string, int> getNumOperands()
{
    map<string, int> NumOperands ;
    NumOperands.clear();
    NumOperands.insert(pair<string, int>("ADD", 1));
    NumOperands.insert(pair<string, int>("ADDF", 1));
    NumOperands.insert(pair<string, int>("ADDR", 2));
    NumOperands.insert(pair<string, int>("AND", 1));
    NumOperands.insert(pair<string, int>("CLEAR", 1));
    NumOperands.insert(pair<string, int>("COMP", 1));
    NumOperands.insert(pair<string, int>("COMPF", 1));
    NumOperands.insert(pair<string, int>("COMPR", 2));
    NumOperands.insert(pair<string, int>("DIV", 1));
    NumOperands.insert(pair<string, int>("DIVF", 1));
    NumOperands.insert(pair<string, int>("DIVR", 2));
    NumOperands.insert(pair<string, int>("FIX", 0));
    NumOperands.insert(pair<string, int>("FLOAT", 0));
    NumOperands.insert(pair<string, int>("HIO", 0));
    NumOperands.insert(pair<string, int>("J", 1));
    NumOperands.insert(pair<string, int>("JEQ", 1));
    NumOperands.insert(pair<string, int>("JGT", 1));
    NumOperands.insert(pair<string, int>("JLT", 1));
    NumOperands.insert(pair<string, int>("JSUB", 1));
    NumOperands.insert(pair<string, int>("LDA", 1));
    NumOperands.insert(pair<string, int>("LDB", 1));
    NumOperands.insert(pair<string, int>("LDCH", 1));
    NumOperands.insert(pair<string, int>("LDF", 1));
    NumOperands.insert(pair<string, int>("LDL", 1));
    NumOperands.insert(pair<string, int>("LDS", 1));
    NumOperands.insert(pair<string, int>("LDT", 1));
    NumOperands.insert(pair<string, int>("LDX", 1));
    NumOperands.insert(pair<string, int>("LPS", 1));
    NumOperands.insert(pair<string, int>("MUL", 1));
    NumOperands.insert(pair<string, int>("MULF", 1));
    NumOperands.insert(pair<string, int>("MULR", 2));
    NumOperands.insert(pair<string, int>("NORM", 0));
    NumOperands.insert(pair<string, int>("OR", 1));
    NumOperands.insert(pair<string, int>("RD", 1));
    NumOperands.insert(pair<string, int>("RMO", 2));
    NumOperands.insert(pair<string, int>("RSUB", 0));
    NumOperands.insert(pair<string, int>("SHIFTL", 2));
    NumOperands.insert(pair<string, int>("SHIFTR", 2));
    NumOperands.insert(pair<string, int>("SIO", 0));
    NumOperands.insert(pair<string, int>("SSK", 1));
    NumOperands.insert(pair<string, int>("STA", 1));
    NumOperands.insert(pair<string, int>("STB", 1));
    NumOperands.insert(pair<string, int>("STCH", 1));
    NumOperands.insert(pair<string, int>("STF", 1));
    NumOperands.insert(pair<string, int>("STI", 1));
    NumOperands.insert(pair<string, int>("STL", 1));
    NumOperands.insert(pair<string, int>("STS", 1));
    NumOperands.insert(pair<string, int>("STSW", 1));
    NumOperands.insert(pair<string, int>("STT", 1));
    NumOperands.insert(pair<string, int>("STX", 1));
    NumOperands.insert(pair<string, int>("SUB", 1));
    NumOperands.insert(pair<string, int>("SUBF", 1));
    NumOperands.insert(pair<string, int>("SUBR", 2));
    NumOperands.insert(pair<string, int>("SVC", 1));
    NumOperands.insert(pair<string, int>("TD", 1));
    NumOperands.insert(pair<string, int>("TIO", 0));
    NumOperands.insert(pair<string, int>("TIX", 1));
    NumOperands.insert(pair<string, int>("TIXR", 1));
    NumOperands.insert(pair<string, int>("WD", 1));
    return NumOperands;
}


map<string, string> getopcode()
{
    map<string, string> opcode ;
    opcode.clear();
    opcode.insert(pair<string, string>("ADD", "18"));
    opcode.insert(pair<string, string>("ADDF", "58"));
    opcode.insert(pair<string, string>("ADDR", "90"));
    opcode.insert(pair<string, string>("AND", "40"));
    opcode.insert(pair<string, string>("CLEAR", "B4"));
    opcode.insert(pair<string, string>("COMP", "28"));
    opcode.insert(pair<string, string>("COMPF", "88"));
    opcode.insert(pair<string, string>("COMPR", "A0"));
    opcode.insert(pair<string, string>("DIV", "24"));
    opcode.insert(pair<string, string>("DIVF", "64"));
    opcode.insert(pair<string, string>("DIVR", "9C"));
    opcode.insert(pair<string, string>("FIX", "C4"));
    opcode.insert(pair<string, string>("FLOAT", "C0"));
    opcode.insert(pair<string, string>("HIO", "F4"));
    opcode.insert(pair<string, string>("J", "3C"));
    opcode.insert(pair<string, string>("JEQ", "30"));
    opcode.insert(pair<string, string>("JGT", "34"));
    opcode.insert(pair<string, string>("JLT", "38"));
    opcode.insert(pair<string, string>("JSUB", "48"));
    opcode.insert(pair<string, string>("LDA", "00"));
    opcode.insert(pair<string, string>("LDB", "68"));
    opcode.insert(pair<string, string>("LDCH", "50"));
    opcode.insert(pair<string, string>("LDF", "70"));
    opcode.insert(pair<string, string>("LDL", "08"));
    opcode.insert(pair<string, string>("LDS", "6C"));
    opcode.insert(pair<string, string>("LDT", "74"));
    opcode.insert(pair<string, string>("LDX", "04"));
    opcode.insert(pair<string, string>("LPS", "D0"));
    opcode.insert(pair<string, string>("MUL", "20"));
    opcode.insert(pair<string, string>("MULF", "60"));
    opcode.insert(pair<string, string>("MULR", "98"));
    opcode.insert(pair<string, string>("NORM", "C8"));
    opcode.insert(pair<string, string>("OR", "44"));
    opcode.insert(pair<string, string>("RD", "D8"));
    opcode.insert(pair<string, string>("RMO", "AC"));
    opcode.insert(pair<string, string>("RSUB", "4C"));
    opcode.insert(pair<string, string>("SHIFTL", "A4"));
    opcode.insert(pair<string, string>("SHIFTR", "A8"));
    opcode.insert(pair<string, string>("SIO", "F0"));
    opcode.insert(pair<string, string>("SSK", "EC"));
    opcode.insert(pair<string, string>("STA", "0C"));
    opcode.insert(pair<string, string>("STB", "78"));
    opcode.insert(pair<string, string>("STCH", "54"));
    opcode.insert(pair<string, string>("STF", "80"));
    opcode.insert(pair<string, string>("STI", "D4"));
    opcode.insert(pair<string, string>("STL", "14"));
    opcode.insert(pair<string, string>("STS", "7C"));
    opcode.insert(pair<string, string>("STSW", "E8"));
    opcode.insert(pair<string, string>("STT", "84"));
    opcode.insert(pair<string, string>("STX", "10"));
    opcode.insert(pair<string, string>("SUB", "1C"));
    opcode.insert(pair<string, string>("SUBF", "5C"));
    opcode.insert(pair<string, string>("SUBR", "94"));
    opcode.insert(pair<string, string>("SVC", "B0"));
    opcode.insert(pair<string, string>("TD", "E0"));
    opcode.insert(pair<string, string>("TIO", "F8"));
    opcode.insert(pair<string, string>("TIX", "2C"));
    opcode.insert(pair<string, string>("TIXR", "B8"));
    opcode.insert(pair<string, string>("WD", "DC"));
    return opcode;
}

vector<string> noSpace(string line){
   vector<string> in;
   string word = "";
   int j = 0;
   while (line[j]==' ')
    j++;
   for (unsigned int i = j; i<=line.length(); i++){
       if ((line[i] == ' ' && i>0 && line[i-1]!=' ') || (line[i] != ' ' && i==line.length())){
           in.push_back(word);
           word = "";
   }
       else if(line[i] != ' ')
           word = word + line[i];
   }
   return in;
}





