#include "Formats.h"

int x = 0;
int b = 0;
int p = 0;
int e = 0;

string Formats::XBPE()
{
    string xbpe = "";
    xbpe += to_string(x);
    xbpe += to_string(b);
    xbpe += to_string(p);
    xbpe += to_string(e);
    return xbpe;
}


string Formats::Displacement(string TAOpeanrd, bool X, string Bcontent, bool BASE, string CurrentLOCCTR, bool immediate)
{
    int TA = HexToDecimal(TAOpeanrd);
    x = 0;
    if (X) {
        x = 1;
    }
    if (immediate) {
        b = 0;
        p = 0;
        int i;
        std::istringstream(TAOpeanrd) >> i;
        string displacement = DecToHex(i,true);
        return displacement;
    }
    int locctr = HexToDecimal(CurrentLOCCTR);
    int PC = locctr + 3;
    int displ = TA - PC;
    p = 1;
    b = 0;
    if (displ > 2047 || displ < -2048) {
        if (BASE) {
            int B = HexToDecimal(Bcontent);
            displ = TA - B;
            p = 0;
            b = 1;
            if (displ > 4095 || displ < 0) {
                throw "Displacement out of range!!";
            }
        }
        else {
            throw "Displacement out of range!!";
        }
    }
    string displa = decimal_to_binary(displ);
    //  string displac = HexToBin(displa);
    //  string displace = neg(displac);
    string displacement = convertBinToHex(displa, true);
    return displacement;
}


string Formats::Format3(string TAOpeanrd, bool X, string Bcontent, bool BASE, string CurrentLOCCTR, bool immediate)
{
    string displacement = Displacement(TAOpeanrd, X, Bcontent, BASE, CurrentLOCCTR, immediate);
    string xbpe = XBPE();
    string xbpeHex = convertBinToHex(xbpe, false);
    string xbpeDisplacement = xbpeHex + displacement;
    return xbpeDisplacement;
}

string Formats::Format4(string TAOpeanrd)
{
    string TA = Format4Hex(TAOpeanrd);
    string xbpe = XBPE();
    string xbpeHex = convertBinToHex(xbpe, false);
    string xbpeTA = xbpeHex + TA;
    return xbpeTA;
}


string Formats::setup(string TAOpeanrd, bool X, string Bcontent, bool BASE, int format, string CurrentLOCCTR, bool immediate)
{
   
    if (format == 3)
    {
        e = 0;
        return Format3(TAOpeanrd, X, Bcontent, BASE, CurrentLOCCTR, immediate);
    }
    else if (format == 4) {
        e = 1;
        x = 0;
        b = 0;
        p = 0;
        if (X) {
            x = 1;
        }
        return Format4(TAOpeanrd);
    }
}