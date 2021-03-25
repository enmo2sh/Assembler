#include "ObjectCode.h"
#include "operations.h"
#include "convert.h"
#include "structures.h"
#include"string"

map<string, symbol_info> SYMTAB;
void ObjectCode::storeRegisters() {
	string labels[9] = { "A","X","L","B","S","T","F","PC","SW" };
	string add[9] = { "0","1","2","3","4","5","6","8","9" };
	for (int i = 0; i < 9; i++) {
		string label = labels[i];
		symbol_info t;
		t.address = add[i];
		SYMTAB.insert(pair<string, symbol_info>(label, t));
	}
	printSymbols();
}

void ObjectCode::Label_is_Found(string label, string address,string flag) {
	if (label == "")
		return;
	if (SYMTAB.find(label) != SYMTAB.end()) {
		cout << "varriable is Found";
		SYMTAB.at(label).address = address;
		SYMTAB.at(label).flag = flag;
		// go to vector
	}
	else {
		symbol_info n;
		n.address = address;
		n.flag = flag;
		SYMTAB.insert(pair<string, symbol_info>(label, n));
	}
}

void ObjectCode::printSymbols() {
	map<string, symbol_info>::iterator itr;
	cout << '\t'<<"NAME    " << "| ADDRESS |   " << "REQUIRED "<<'\n';
	for (itr = SYMTAB.begin(); itr != SYMTAB.end(); ++itr) {
		cout << '\t' << itr->first<<"        | ";
		cout << itr->second.address<<"|   ";
		for (int i = 0; i < itr->second.reff.size(); i++) {
			cout << "    " << itr->second.reff.at(i);
		}
		cout << '\n';
	}
}


string ObjectCode::objectCode(int format, string CurrentLOCCTR, string B, bool BASE, string opCode, vector<string> operand, char typeOfOperand) {
	string ObjectCode = "";
	bool X = false;
	if (format == 2) {
		// if operand is empty return error
		ObjectCode = opCode;
		string TA = getTargetAddress(operand[0], typeOfOperand, CurrentLOCCTR);
		if (TA == "Error")
			return "Error";
		if (TA == "NotFound")
			ObjectCode.append("0");
		else
			ObjectCode.append(TA);
		if (operand.size() > 1) {
			TA = getTargetAddress(operand[1], typeOfOperand, CurrentLOCCTR);
			if (TA == "NotFound")
				ObjectCode.append("0");
			else
				ObjectCode.append(TA);
		}
		else
			ObjectCode.append("0");
	}
	else if (format == 3) {
		opCode = HexToBin(opCode);
		opCode.erase(opCode.size() - 1);
		opCode.erase(opCode.size() - 1);
		string ni = generateNI(typeOfOperand);
		string opni = opCode + ni;
		string opniHex = convertBinToHex(opni, false);
		string TA = generateTA(operand, typeOfOperand, CurrentLOCCTR);
		if (TA == "Error")
			return "Error";
		if (TA != "NotFound") {
			if (typeOfOperand == '#' && is_number(operand.at(0))) {
				string xbpeDisplacementHex = setup(operand.at(0), X, B, BASE, format, CurrentLOCCTR, true);
				ObjectCode = opniHex + xbpeDisplacementHex;
			}
			else {
				string xbpeDisplacementHex = setup(TA, X, B, BASE, format, CurrentLOCCTR, false);
				ObjectCode = opniHex + xbpeDisplacementHex;
			}
		}
		else
			ObjectCode = opniHex.append("0000");
	}
	else if (format == 4) {
		opCode = HexToBin(opCode);
		opCode.erase(opCode.size() - 1);
		opCode.erase(opCode.size() - 1);
		string ni = generateNI(typeOfOperand);
		string opni = opCode + ni;
		string opniHex = convertBinToHex(opni, false);
		string TA = generateTA(operand, typeOfOperand, CurrentLOCCTR);
		if (TA == "Error")
			return "Error";
		if (TA != "NotFound") {
			string xbpeTAHex = setup(TA, X, B, BASE, format, CurrentLOCCTR,false);
			ObjectCode = opniHex + xbpeTAHex;
		}
		else
			// check numbers of zeros if format 4
			ObjectCode = opniHex.append("0000");
	}
	return ObjectCode;
}


vector<string> ObjectCode::split(string exp, char delimiter) {
	vector<string> oper;
	string temp = "";
	for (int i = 0; i < exp.size(); i++) {
		if (exp[i] == delimiter) {
			oper.push_back(temp);
			temp = "";
		}
		else
			temp += exp[i];
	}
	if (temp != "")
		oper.push_back(temp);
	return oper;
}

string ObjectCode::generateNI(char typeOfOperand) {
	string ni;
	if (typeOfOperand == '#')
	{
		ni += "0";
		ni += "1";
	}
	else if (typeOfOperand == char(0))
	{
		ni += "1";
		ni += "1";
	}
	else if (typeOfOperand == '@')
	{
		ni += "1";
		ni += "0";
	}
	return ni;
}

string ObjectCode::generateTA(vector<string> operand, char type, string loc) {
	string TA = getTargetAddress(operand.at(0), type, loc);;
	int size = operand.size();
	if (size > 2) {
		X = true;
	}
	else {
		X = false;
	}

	return TA;
}

string ObjectCode::getTargetAddress(string var, char type, string loc) {
	if (type == '#' && is_number(var))//immediate number
		return toHex(toDec(var));
	string var1="";
	string var2="";
	string flag1;
	string flag2;
	if (var.find("+") != std::string::npos) {
		vector<string> temp = split(var, '+');
		if (is_number(temp.at(0))) {
			flag1 = "A";
			var1 = temp.at(0);
		}
		if (is_number(temp.at(1))) {
			flag2 = "A";
			var2 = temp.at(1);
		}
		if (var1 == "") {
			var1 = getValue(temp.at(0), loc);
			if (var1 == "NotFound")
				return "NotFound";
			else
				flag1 = SYMTAB.at(temp.at(0)).flag;
			
		}
		if (var2 == "") {
			var2 = getValue(temp.at(1), loc);
			if (var2 == "NotFound")
				return "NotFound";
			else
				flag2= SYMTAB.at(temp.at(1)).flag;
		}
		if (flag1 == "R" && flag2 == "R")
			return "Error";
		return toHex(HexToDecimal(var1) + HexToDecimal(var2));
	}
	else if (var.find("-") != std::string::npos) {
		vector<string> temp = split(var, '-');
		if (is_number(temp.at(0))) {
			flag1 = "A";
			var1 = temp.at(0);
		}
		if (is_number(temp.at(1))) {
			flag2 = "A";
			var2 = temp.at(1);
		}
		if (var1 == "") {
			var1 = getValue(temp.at(0), loc);
			if (var1 == "NotFound")
				return "NotFound";
			else
				flag1 = SYMTAB.at(temp.at(0)).flag;

		}
		if (var2 == "") {
			var2 = getValue(temp.at(1), loc);
			if (var2 == "NotFound")
				return "NotFound";
			else
				flag2 = SYMTAB.at(temp.at(1)).flag;
		}
		if (flag1 == "A" && flag2 == "R")
			return "Error";
		return toHex(HexToDecimal(var1) - HexToDecimal(var2));
	}
	else if (var.find("*") != std::string::npos) {
		vector<string> temp = split(var, '*');
		if (is_number(temp.at(0)) && is_number(temp.at(1))) {
			var1 = StringToInt(temp.at(0));
			var2 = StringToInt(temp.at(1));
		}
		else
			return "Error";
		return toHex(HexToDecimal(var1) * HexToDecimal(var2));
	}
	else if (var.find("/") != std::string::npos) {
		vector<string> temp = split(var, '/');
		if (is_number(temp.at(0)) && is_number(temp.at(1))) {
			var1 = StringToInt(temp.at(0));
			var2 = StringToInt(temp.at(1));
		}
		else
			return "Error";
		return toHex(HexToDecimal(var1) / HexToDecimal(var2));
	}
	else
		return getValue(var, loc);

}

string ObjectCode::getValue(string var, string loc) {
	if (SYMTAB.find(var) != SYMTAB.end()) {// varriable exists
		if (SYMTAB.at(var).address != "*") {// varriable has an address
			return SYMTAB.at(var).address;
		}
		else { // varriable hasn't an address
			SYMTAB.at(var).reff.push_back(loc);
			return "NotFound";
		}
	}
	else {//varriable doesnt exist
		symbol_info n;
		n.address = "*";
		n.reff.push_back(loc);
		SYMTAB.insert(pair<string, symbol_info>(var, n));
		return "NotFound";
	}
}
bool ObjectCode::is_number(const std::string& s)
{
	return(strspn(s.c_str(), "-.0123456789") == s.size());
}
bool ObjectCode::checkAllLabelsAreFound() {
	map<string, symbol_info>::iterator itr;
	for (itr = SYMTAB.begin(); itr != SYMTAB.end(); ++itr) {
		if (itr->second.address == "*")
			return false;
	}
	return true;

}
map<string, symbol_info> ObjectCode::getSymbolTable() {
	return SYMTAB;
}