#include "convert.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <vector>
using namespace std;

string hex_char_to_bin(char c) {
    // TODO handle default / error
    switch (c) {
    case '0': return "0000";
    case '1': return "0001";
    case '2': return "0010";
    case '3': return "0011";
    case '4': return "0100";
    case '5': return "0101";
    case '6': return "0110";
    case '7': return "0111";
    case '8': return "1000";
    case '9': return "1001";
    case 'A': return "1010";
    case 'B': return "1011";
    case 'C': return "1100";
    case 'D': return "1101";
    case 'E': return "1110";
    case 'F': return "1111";
    }
}

string hexToBin(string hex) {
    string bin;
    for (unsigned i = 0; i != hex.length(); ++i)
        bin.append(hex_char_to_bin(hex[i]));
    return bin;
}

string toHex(int a) {
    string lookup = "0123456789ABCDEF";
    string res = "";
    if (a == 0)
        return"0";
    while (a) {
        res.insert(0, 1, lookup[a % 16]);
        a /= 16;
    }
    return res;
}

int toDec(string s) {
    int mul = 1, res = 0;
    for (int n = s.size() - 1; n >= 0; --n) {
        res += toDecimal_digit(s[n]) * mul;
        mul *= 16;
    }
    return res;
}
int toDecimal_digit(char a) {
    if (a == '0') return 0;
    if (a == '1') return 1;
    if (a == '2') return 2;
    if (a == '3') return 3;
    if (a == '4') return 4;
    if (a == '5') return 5;
    if (a == '6') return 6;
    if (a == '7') return 7;
    if (a == '8') return 8;
    if (a == '9') return 9;
    if (a == 'A') return 10;
    if (a == 'B') return 11;
    if (a == 'C') return 12;
    if (a == 'D') return 13;
    if (a == 'E') return 14;
    if (a == 'F') return 15;
}

string decTohexa(int n)
{
    char hexaDeciNum[100];
    string s = "";
    int i = 0;
    while (n != 0)
    {
        int temp = 0;
        temp = n % 16;
        if (temp < 10)
        {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else
        {
            hexaDeciNum[i] = temp + 55;
            i++;
        }

        n = n / 16;
    }

    for (int j = i - 1; j >= 0; j--) {
        s = s + hexaDeciNum[j];
    }
    return s;
}