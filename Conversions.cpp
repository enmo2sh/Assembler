#include "Conversions.h"


void Conversions::createMap(map<string, char>* um)
{
    (*um)["0000"] = '0';
    (*um)["0001"] = '1';
    (*um)["0010"] = '2';
    (*um)["0011"] = '3';
    (*um)["0100"] = '4';
    (*um)["0101"] = '5';
    (*um)["0110"] = '6';
    (*um)["0111"] = '7';
    (*um)["1000"] = '8';
    (*um)["1001"] = '9';
    (*um)["1010"] = 'A';
    (*um)["1011"] = 'B';
    (*um)["1100"] = 'C';
    (*um)["1101"] = 'D';
    (*um)["1110"] = 'E';
    (*um)["1111"] = 'F';
}

string Conversions::convertBinToHex(string bin, bool add)
{
    if (add) {
        string add = "";
        int size = bin.size() % 4;
        if (size != 0) {
            for (int i = 0; i < size; i++) {
                add += "0";
            }

        }
        bin = add + bin;
        add = "";
        if (bin.size() == 4) {
            for (int i = 0; i < 8; i++) {
                add += "0";
            }
        }
        else if (bin.size() == 8) {
            for (int i = 0; i < 4; i++) {
                add += "0";
            }
        }
        bin = add + bin;
    }
    int l = bin.size();
    int t = bin.find_first_of('.');
    int len_left = t != -1 ? t : l;
    for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
        bin = '0' + bin;
    if (t != -1)
    {
        int len_right = l - len_left - 1;
        for (int i = 1; i <= (4 - len_right % 4) % 4; i++)
            bin = bin + '0';
    }
    map<string, char> bin_hex_map;
    createMap(&bin_hex_map);
    int i = 0;
    string hex = "";
    while (1)
    {
        hex += bin_hex_map[bin.substr(i, 4)];
        i += 4;
        if (i == bin.size())
            break;
        if (bin.at(i) == '.')
        {
            hex += '.';
            i++;
        }
    }
    return hex;
}

string Conversions::DecToHex(int num, bool add)
{
    map<int, char> m;
    char digit = '0';
    char c = 'A';
    for (int i = 0; i <= 15; i++) {
        if (i < 10) {
            m[i] = digit++;
        }
        else {
            m[i] = c++;
        }
    }
    string res = "";
    if (!num) {
        return "0";
    }
    if (num > 0) {
        while (num) {
            res = m[num % 16] + res;
            num /= 16;
        }
    }
    else {
        long n = num;
        while (n) {
            res = m[n % 16] + res;
            n /= 16;
        }
    }
    if (res.length() != 3 && add) {
        string addd = "";
        for (int i = res.length(); i < 3; i++) {
            addd += "0";
        }
        res = addd+ res;
    }
    return res;
}


int Conversions::HexToDecimal(string hexVal)
{
    int len = hexVal.length();
    int base = 1;
    int dec_val = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (hexVal[i] >= '0' && hexVal[i] <= '9')
        {
            dec_val += (hexVal[i] - 48) * base;
                base = base * 16;
        }
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F')
        {
            dec_val += (hexVal[i] - 55) * base;
            base = base * 16;
        }
    }
    return dec_val;
}


char* Conversions::StringToChar(string s)
{
    int n = s.length();
    char str[100];
    int i;
    for (i = 0; i < n; i++) {
        str[i] = s[i];
    }
    return str;
}

string Conversions::CharToString(char* a)
{
    int size = strlen(a);
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}


char flip(char c) { return (c == '0') ? '1' : '0'; }

string Conversions::neg(string bin)
{
    int n = bin.length();
    int i;
    string ones, twos;
    ones = twos = "";
    for (i = 0; i < n; i++)
        ones += flip(bin[i]);
    twos = ones;
    for (i = n - 1; i >= 0; i--)
    {
        if (ones[i] == '1')
            twos[i] = '0';
        else
        {
            twos[i] = '1';
            break;
        }
    }
    if (i == -1)
        twos = '1' + twos;

    return twos;
}

string Conversions::HexToBin(string hexdec)
{
    long int i = 0;
    string out = "";
    while (hexdec[i]) {
        switch (hexdec[i]) {
        case '0':
            out += "0000";
            break;
        case '1':
            out += "0001";
            break;
        case '2':
            out += "0010";
            break;
        case '3':
            out += "0011";
            break;
        case '4':
            out += "0100";
            break;
        case '5':
            out += "0101";
            break;
        case '6':
            out += "0110";
            break;
        case '7':
            out += "0111";
            break;
        case '8':
            out += "1000";
            break;
        case '9':
            out += "1001";
            break;
        case 'A':
        case 'a':
            out += "1010";
            break;
        case 'B':
        case 'b':
            out += "1011";
            break;
        case 'C':
        case 'c':
            out += "1100";
            break;
        case 'D':
        case 'd':
            out += "1101";
            break;
        case 'E':
        case 'e':
            out += "1110";
            break;
        case 'F':
        case 'f':
            out += "1111";
            break;
        default:
            cout << "\nInvalid hexadecimal digit "
                << hexdec[i];
        }
        i++;
    }

    return out;
}

string Conversions::decimal_to_binary(int n) {
    if (n < 0) { // check if negative and alter the number
        n = 256 + n;
    }
    string result = "";
    while (n > 0) {
        result = string(1, (char)(n % 2 + 48)) + result;
        n = n / 2;
    }
    return result;
}

string Conversions::Format4Hex(string TAOpeanrd)
{
    string add = "";
    int k = TAOpeanrd.length();
    if (k >= 5) {
        return TAOpeanrd;
    }
    int check = TAOpeanrd.length() % 5;
    check = 5 - check;
    while (check != 0) {
        check--;
        add += "0";
    }
    TAOpeanrd = add + TAOpeanrd;
    return TAOpeanrd;
}


int Conversions::StringToInt(string num) {
    int i;
    istringstream(num) >> i;
    return i;
}