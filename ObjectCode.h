#pragma once
#include "Formats.h"
#include <iostream>
#include "Conversions.h"
#include "structures.h"
using namespace std;


class ObjectCode : public Formats
{
public:
    void storeRegisters();
    void Label_is_Found(string label, string address,string flag);
    void printSymbols();
    string objectCode(int format, string CurrentLOCCTR, string B, bool BASE, string opCode, vector<string> operand, char typeOfOperand);
    vector<string> split(string exp, char delimiter);
    string generateNI(char typeOfOperand);
    string generateTA(vector<string> operand, char type, string loc);
    string getTargetAddress(string var, char type, string loc);
    string getValue(string var, string loc);
    bool is_number(const std::string& s);
    bool checkAllLabelsAreFound();
    map<string, symbol_info> getSymbolTable();
private:
    bool X;

};