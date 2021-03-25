#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <vector>
#include <functional>
#include <cctype>
#include "ObjectCode.h"
#include "convert.h"
#include "operations.h"
#include "structures.h"
#include <cstring>
#include <cstdlib>
#include <string>
#include "Conversions.h"
#include "WriteFile.h"
#include "ObjectCode.h"
using namespace std;

vector <preobj> table;
string locctr = "0";
string name = "";
string oldLocctr = "0";
class pass1 :public ObjectCode {
    int end = 0;
    bool error;
private:
    map<string, int> format;
    map<string, string> opcode;
    map<string, int> numOPerands;
public:
    pass1() {
        format = getformat();
        opcode = getopcode();
        numOPerands = getNumOperands();
        storeRegisters();
    }
    bool handleLine(string line) {
        vector<string> data = noSpace(line);
        struct preobj info = extract(data);
        if (info.Operator == "")
            return false;

        //check if END
        if (info.Operator == "START") {
            locctr = info.Operand;
            if (info.Label != "")
                name = info.Label;
            info.locctr = locctr;
            table.push_back(info);
            return true;
        }
        calcObjectCode(info);
        return true;
    }


    void calcObjectCode(preobj info) {
        bool base = false;
        string B = "";
        if (info.Operator == "WORD") {
            info.objectCode = toHex(StringToInt(info.Operand));
            map<string, symbol_info> symbols = getSymbolTable();
            if (symbols.find(info.Label) != symbols.end()) {
                if (symbols.at(info.Label).address != "*") {
                    cout << "ERROR! redefined Label" << '\n';
                    end = 1;
                    return;
                }
            }
            while (size(info.objectCode) < 6) {
                string temp = info.objectCode;
                info.objectCode = "0" + temp;
            }
            info.locctr = locctr;
            table.push_back(info);
            Label_is_Found(info.Label, locctr, "R");
            locctr = toHex(toDec(locctr) + 3);
        }
        else if (info.Operator == "RESW") {
            map<string, symbol_info> symbols = getSymbolTable();
            if (symbols.find(info.Label) != symbols.end()) {
                if (symbols.at(info.Label).address != "*") {
                    cout << "ERROR! redefined Label" << '\n';
                    end = 1;
                    return;
                }
            }
            info.locctr = locctr;
            table.push_back(info);
            Label_is_Found(info.Label, locctr, "R");
            locctr = toHex(toDec(locctr) + 3 * StringToInt(info.Operand));
        }
        else if (info.Operator == "RESB") {
            map<string, symbol_info> symbols = getSymbolTable();
            if (symbols.find(info.Label) != symbols.end()) {
                if (symbols.at(info.Label).address != "*") {
                    cout << "ERROR! redefined Label" << '\n';
                    end = 1;
                    return;
                }
            }
            info.locctr = locctr;
            table.push_back(info);
            Label_is_Found(info.Label, locctr, "R");
           // cout << toDec(locctr) << endl;
           // cout << StringToInt(info.Operand) << endl;
            locctr = toHex(toDec(locctr) + StringToInt(info.Operand));
            //cout << locctr << endl;
        }
        else if (info.Operator == "BYTE") {
            map<string, symbol_info> symbols = getSymbolTable();
            if (symbols.find(info.Label) != symbols.end()) {
                if (symbols.at(info.Label).address != "*") {
                    cout << "ERROR! redefined Label" << '\n';
                    end = 1;
                    return;
                }
            }
            int len = info.Operand.size() - 3;
            if (info.Operand[0] == 'X') {
                len /= 2;
                for (int i = 2; i < info.Operand.size() - 1; i++) {
                    info.objectCode += (info.Operand[i]);
                }
            }
            else if (info.Operand[0] == 'C') {
                for (int i = 0; i < len; i++) {
                    char temp = info.Operand[i + 2];
                    info.objectCode.append(toHex((int)temp));
                }
            }
            info.locctr = locctr;
            table.push_back(info);
            Label_is_Found(info.Label, locctr, "R");
            locctr = toHex(toDec(locctr) + len);
        }
        else if (info.Operator == "EQU") {
            char type = char(0);
            if (info.Operand[0] == '#' || info.Operand[0] == '@') {
                type = info.Operand[0];
                info.Operand.erase(0, 1);
            }
            vector<string> operand = split(info.Operand, ',');
            if (is_number(operand[0])) {
                locctr = getTargetAddress(operand[0], type, locctr);
                info.locctr = locctr;
                table.push_back(info);
                Label_is_Found(info.Label, operand[0], "A");
            }
            else if (operand[0] == "*") {
                info.locctr = locctr;
                table.push_back(info);
                Label_is_Found(info.Label, locctr, "R");
            }
            else if (getTargetAddress(operand[0], type, locctr) != "NotFound") {
                if (getTargetAddress(operand[0], type, locctr) == "Error") {
                    cout << "Error in calculating the expression";
                    end = 1;
                    return;
                }
                locctr = getTargetAddress(operand[0], type, locctr);
                cout << "loctr =   " << locctr << '\n';
                info.locctr = locctr;
                table.push_back(info);
                Label_is_Found(info.Label, locctr, "R");
            }
        }
        else if (info.Operator == "ORG") {
            char type = char(0);
            if (info.Operand[0] == '#' || info.Operand[0] == '@') {
                type = info.Operand[0];
                info.Operand.erase(0, 1);
            }
            if (is_number(info.Operand)) {
                oldLocctr = locctr;
                locctr = info.Operand;
            }
            else if (info.Operand == "") {
                locctr = oldLocctr;
            }
            else {
                string value = getTargetAddress(info.Operand, type, locctr);
                if (value != "NotFound") {
                    if (getTargetAddress(info.Operand, type, locctr) == "Error") {
                        cout << "Error in calculating the expression";
                        end = 1;
                        return;
                    }
                    oldLocctr = locctr;
                    locctr = value;
                }
            }
        }
        else if (info.Operator == "BASE") {
            char type = char(0);
            if (info.Operand[0] == '#' || info.Operand[0] == '@') {
                type = info.Operand[0];
                info.Operand.erase(0, 1);
            }
            string value = getTargetAddress(info.Operand, type, locctr);
            if (value != "NotFound") {
                if (getTargetAddress(info.Operand, type, locctr) == "Error") {
                    cout << "Error in calculating the expression";
                    end = 1;
                    return;
                }
                base = true;
                B = value;
            }
        }
        else if (info.Operator == "NOBASE") {
            base = false;
        }
        else if (info.Operator == "END") {
            info.locctr = locctr;
            table.push_back(info);
        }
        else {
            string Operator2 = info.Operator;
            if (Operator2[0] == '+')
                Operator2.erase(0, 1);
            if (format.find(Operator2) == format.end())//Wrong Operator
                info.Operator = "";
            // message wrong
            //return
            else {
                int Format = format.at(Operator2);
                if (Format == 3) {
                    if (info.Operator[0] == '+')
                        Format = 4;
                }
                string Opcode = opcode.at(Operator2);
                info.Format = Format;
                info.Opcode = Opcode;
                char type = char(0);
                if (info.Operand[0] == '#' || info.Operand[0] == '@') {
                    type = info.Operand[0];
                    info.Operand.erase(0, 1);
                }
                info.objectCode = objectCode(Format, locctr, B, base, Opcode, split(info.Operand, ','), type);
                if (info.objectCode == "Error") {
                    cout << "Error calculating the expression";
                    end = 1;
                    return;
                }
                if (type == '#' && is_number(info.Operand))
                    Label_is_Found(info.Label, locctr, "A");
                else
                    Label_is_Found(info.Label, locctr, "R");
                info.locctr = locctr;
                table.push_back(info);
                locctr = toHex(toDec(locctr) + Format);
            }
        }
        printSymbols();
        cout << "-----------------------------------------" << '\n';
    }

    void readFile(string filename) {
        ifstream myfile;
        myfile.open(filename.c_str());
        string line;
        while ((getline(myfile, line)) && (end == 0)) {
            if (!(strchr(line.c_str(), '.')))
                error = handleLine(line);

        }

        myfile.close();
        bool e = checkAllLabelsAreFound();
        //if e is true then write to object file
        if (e == false)
            cout << "you shouldnt use any label not declared";
        else {
            if (end == 0) {
                for (int i = 0;i < table.size();i++)
                    cout << "   " << table.at(i).locctr << "               |" << table.at(i).Label << "                |" << table.at(i).Operator << "                |" << table.at(i).Operand << "                  |" << table.at(i).objectCode << '\n';
                writefile(table, getSymbolTable());
            }

        }

    }

    struct preobj extract(vector<string> data) {
        struct preobj info;
        string Label, Operator, Operand;
        std::map<string, string>::iterator it;
        if ((data.size() == 1 && data.at(0) != "END" && data.at(0) != "") || (data.size() == 2 && (data.at(1) == "FIX" || data.at(1) == "FLOAT" || data.at(1) == "HIO" || data.at(1) == "NORM" || data.at(1) == "SIO" || data.at(1) == "TIO"))) {
            cout << "Format 1 not supported\n";
            end = 1;
            return info;

        }
        if (data.at(0) != "START" && data.size() > 1 && data.at(1) != "START") {

            if (data.size() >= 3 && data.at(2) != "") {
                std::transform(data.at(0).begin(), data.at(0).end(), data.at(0).begin(), std::ptr_fun<int, int>(std::toupper));
                std::transform(data.at(1).begin(), data.at(1).end(), data.at(1).begin(), std::ptr_fun<int, int>(std::toupper));
                std::transform(data.at(2).begin(), data.at(2).end(), data.at(2).begin(), std::ptr_fun<int, int>(std::toupper));
                std::map<string, string>::iterator it = opcode.find(data.at(1));


                if ((it != opcode.end() && numOPerands[data.at(1)] == 0)
                    || (numOPerands[data.at(1)] == 2 && data.at(2).find(",") == string::npos)
                    || (numOPerands[data.at(1)] == 1 && strchr(data.at(2).c_str(), ',') && !(strstr(data.at(2).c_str(), ",X")))
                    || ((strchr(data.at(2).c_str(), '@') || strchr(data.at(2).c_str(), '#')) && strchr(data.at(2).c_str(), ','))) {
                    cout << "error in operand\n";
                    cout << "operator  \" " << data.at(1) << " \" doen't match with operand \" " << data.at(2) << " \"" << '\n';
                    end = 1;
                    return info;
                }
            }
            else if (data.size() >= 2 && data.at(1) != "") {
                std::transform(data.at(0).begin(), data.at(0).end(), data.at(0).begin(), std::ptr_fun<int, int>(std::toupper));
                std::transform(data.at(1).begin(), data.at(1).end(), data.at(1).begin(), std::ptr_fun<int, int>(std::toupper));
                std::map<string, string>::iterator it = opcode.find(data.at(1));
                std::map<string, string>::iterator it1 = opcode.find(data.at(0));
                if ((it != opcode.end() && numOPerands[data.at(1)] != 0)
                    || (it1 != opcode.end() && numOPerands[data.at(0)] == 0)

                    || (numOPerands[data.at(0)] == 2 && data.at(1).find(",") == string::npos)

                    || (numOPerands[data.at(0)] == 1 && strchr(data.at(1).c_str(), ',') && !(strchr(data.at(1).c_str(), 'X')))
                    || ((strchr(data.at(1).c_str(), '@') || strchr(data.at(1).c_str(), '#')) && strstr(data.at(1).c_str(), ",X"))) {
                    cout << "error in operand\n";

                    cout << "operator  \" " << data.at(0) << " \" doen't match with operand \" " << data.at(1) << " \" " << '\n';


                    end = 1;
                    return info;
                }

            }
            else {
                std::map<string, string>::iterator it = opcode.find(data.at(0));
                if ((it != opcode.end() && numOPerands[data.at(1)] != 0))
                    cout << "error in operand\n";

            }
        }

        if (data.size() == 3) {
            Label = data.at(0);
            Operator = data.at(1);
            Operand = data.at(2);
        }
        else if (data.size() == 2) {
            Label = "";
            Operator = data.at(0);
            Operand = data.at(1);
        }




        /*
          it = opcode.find(Operator);
        if (Operator!="START"&&it == opcode.end()) {
            cout << "Not valid operator\n";
            end = 1;
            return info;

        }
        */



        info.Label = Label;
        info.Operand = Operand;
        info.Operator = Operator;
        return info;
    }

};


int main() {
    pass1 e;
    e.readFile("assembler.txt");
    return 0;
}