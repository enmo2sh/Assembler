#include "WriteFile.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include<sstream>
#include "convert.h"
#include<vector>

void  writefile(vector<preobj> Map, map<string, symbol_info>modification) {    //object file
    bool flag = false;
    ofstream file_;
    file_.open("output.txt");
    //vector< preobj>::iterator it;
    vector<string> arr;
    int i = 0; int index;
    for (index = 0; index < Map.size(); index++) {
        if (i == 0) {
            i++;
        }
        else {
            arr.push_back(Map.at(index).locctr);
            i++;
        }
    }

    for (index = 0; index < Map.size(); index++) {     //Header record
        if (Map.at(index).Operator == "START") {
            file_ << "H ";        //printing location counter
            file_ << Map.at(index).Label;
            file_ << " 00";
            file_ << Map.at(index).Operand;
            file_ << " 00";
            int num1, num2;
            std::stringstream str_strm1(arr.at(0));     //calculate length of the program
            std::stringstream str_strm2(arr.at(Map.size() - 2));
            std::stringstream str_hex1;
            std::stringstream str_hex2;
            str_strm1 >> std::hex >> num2;
            str_strm2 >> std::hex >> num1;
            int num = num1 - num2 + 1;
            string s = decTohexa(num);
            for (i = 0; i < 4 - s.size(); i++) {
                file_ << "0";
            }
            file_ << s;
            file_ << "\n";
        }
    }



    index = 0;
    while (index < Map.size()&& Map.at(index).Operator!="END") {      //Text records
        if (Map.at(index).Operator != "START") {
            int counter = 0; int length = 0;
            int save = index;
            while (save < Map.size() && Map.at(save).Operator != "START" && Map.at(save).Operator != "END" && (counter + (Map.at(save).objectCode.size() / 2)) <= 30) {
                if (Map.at(save).Label != "" && modification[Map.at(save).Label].reff.size() != 0) {
                    save = Map.size();
                }
                else {
                    counter += Map.at(save).objectCode.size() / 2;
                    save++;
                }
            }
            if (counter == 0 && flag == false) {
                vector<string>modify = modification[Map.at(index).Label].reff;
                for (i = 0; i < modify.size(); i++) {
                    file_ << "T 00";
                    file_ << modify.at(i);
                    file_ << " 02 ";
                    file_ << modification[Map.at(index).Label].address;
                    file_ << "\n";

                }
                //index++;
                modification[Map.at(index).Label].reff.clear();
                flag = true;
            }
            else {
                flag = false;
                length = counter;
                counter = 0;
                if (index < Map.size() && Map.at(index).Operator != "START" && Map.at(index).Operator != "END" && (counter + (Map.at(index).objectCode.size() / 2)) <= length) {
                    file_ << "T 00";
                    file_ << Map.at(index).locctr;
                    file_ << " ";
                    if (decTohexa(length).size() < 2) {
                        file_ << "0";
                    }
                    file_ << decTohexa(length);
                    file_ << " ";
                    if (Map.at(index).objectCode != "") {
                        file_ << Map.at(index).objectCode;
                        counter += Map.at(index).objectCode.size() / 2;

                    }
                    index++;

                }
                while (index < Map.size() && Map.at(index).Operator != "START" && Map.at(index).Operator != "END" && (counter + (Map.at(index).objectCode.size() / 2)) <= length) {
                    if (Map.at(index).objectCode != "") {
                        file_ << " ";
                        file_ << Map.at(index).objectCode;
                        counter += Map.at(index).objectCode.size() / 2;

                    }
                    index++;
                }
                file_ << "\n";
            }

        }
        else {
            index++;
        }

    }
    index = 0;
    string raddr = Map.at(0).locctr;
    while (index < Map.size()) {        //end record
        if (Map.at(index).Operator == "END") {
            file_ << "E 00";
            if (Map.at(index).Operand == "") {
                file_ << raddr;
            }
            else {
                file_ << Map.at(index).Operand;
            }
            break;
        }
        else {
            index++;
        }

    }
}