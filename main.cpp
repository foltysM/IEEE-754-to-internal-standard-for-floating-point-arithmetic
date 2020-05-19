#include <QCoreApplication>
#include <iostream>
#include <cmath>

using namespace std;

float bin2dec(string bin)
{
    float suma = 0;
    int dlugosc = bin.length();
    int kropka = 0;
    bool ob_kropka = 0;
    int w = 0;
    for(int i = 0; i < dlugosc; i++)
    {
        if(bin[i] == '.') ob_kropka = 1;
    }
    for(int i = dlugosc-1;i>=0;i--)
    {

        if(ob_kropka == 1)
        {
            if(bin[i] == '.')
            {
                int k = -1;
                for(int j = i+1; j < dlugosc; j++)
                {
                   if(bin[j]=='1')
                   {
                        suma = suma + pow(2, (k));
                   }
                   k--;
                }
                kropka = 1;
                w = i - 1;
            }

            if(bin[i]=='1' && kropka == 1)
            {
                suma = suma + pow(2, (w-i));
            }
        }

        if(ob_kropka == 0)
        {
            if(bin[i]=='1')
            {
                suma = suma + pow(2, (dlugosc-1-i));
            }
        }
    }
    return suma;
}

string dec2bin(float input1)
{
    string ret = "";
    string ret3 = "";
    int input = floor(input1);
    float dec = input1-floor(input1);
    if(dec!=0)ret.push_back('.');
    while(dec!=0||ret.length()>20)
    {
        float result = dec*2;

        if(result>=1)
        {
            ret3.push_back('1');
            dec = result - 1;
        }else
        {
            ret3.push_back('0');
            dec = result;
        }
    }

    while(input>0)
    {
        int result = input%2;
        input = input/2;
        if(result==1)
        {
            ret.push_back('1');
        }else
        {
            ret.push_back('0');
        }
    }

    string ret2 = ret;
    int j = ret.length()-1;
    for(int i = 0;i<(int)ret.length();i++)
    {
        ret2[i] = ret[j];
        j--;
    }
    ret2 = ret2 + ret3;
    return ret2;
}

int IEEEbin2dec(string w)
{
    int s;
    switch(w[0])
    {
    case '0':
        s = 0;
        break;
    case '1':
        s = 1;
        break;
    }
    string mantysa = "";
    string wykladnik = "";
    float mantysa_dec;
    int wykladnik_dec;
    for(int i = 1;i<9;i++)
    {
        wykladnik.push_back(w[i]);
    }
    for(int i = 9;i<=31;i++)
    {
        mantysa.push_back(w[i]);
    }
    wykladnik_dec = bin2dec(wykladnik);
    int e = wykladnik_dec - 127;

    for(int i = 1;i<24;i++)
    {
        if(mantysa[i-1]=='1')
        {
            mantysa_dec = mantysa_dec + pow(2, -i);
        }
    }

    float wynik = pow(-1,s)*(1+mantysa_dec)*pow(2,e);
    return wynik;
}

float WEWbin2dec(string w)
{
    int s;
    switch(w[0])
    {
    case '0':
        s = 0;
        break;
    case '1':
        s = 1;
        break;
    }

    int z;
    switch(w[8])
    {
    case '0':
        z = 0;
        break;
    case '1':
        z = 1;
        break;
    }

    string mantysa = "";
    string wykladnik = "";
    float mantysa_dec;
    int wykladnik_dec;
    for(int i = 1;i<8;i++)
    {
        wykladnik.push_back(w[i]);
    }
    for(int i = 9;i<=31;i++)
    {
        mantysa.push_back(w[i]);
    }
    wykladnik_dec = bin2dec(wykladnik);
    int e = wykladnik_dec;

    for(int i = 1;i<24;i++)
    {
        if(mantysa[i-1]=='1')
        {
            mantysa_dec = mantysa_dec + pow(2, -i);
        }
    }
    float wynik = pow(-1,1-s)*(1+mantysa_dec)*pow(2,e*pow(-1,z));
    return wynik;
}


string dec2IEEEbin(double number)
{
    long wholePart = (long) number;
    double fractionalPart = number - wholePart;

    string sign = "";
    string mantisa = "";
    string exponent = "";
    if (number>=0)
        sign.push_back('0');
    else
        sign.push_back('1');

    string whole_bin = dec2bin(wholePart);
    string fractional_bin = dec2bin(fractionalPart);
    string number_bin = whole_bin+fractional_bin;
        for(int i = 0;i<(int)number_bin.length()-1;i++)
        {
            mantisa.push_back(number_bin[i+1]);
        }
    int e = whole_bin.length()-1;
    int exponent_dec = e+127;
    exponent = dec2bin(exponent_dec);
    string exp2 = "";
    if(exponent.length()!=8)
    {
        for(int i = 0; i<8-(int)exponent.length();i++)
        {
            exp2.push_back('0');
        }
        exp2 = exp2 + exponent;
    }else{
        exp2 = exponent;
    }

    string res = sign+exp2+mantisa;

    for(int j = (int)res.length();j<32;j++)
    {
        res.push_back('0');
    }
    return res;
}

string dec2WEWbin(float input)
{
    string ret = "";
    string wykladnik = "";
    string mantysa = "";
    string binput = dec2bin(input);
    int binput_l = binput.length();
    int e = 0;
    int sign = 0;

    if (input<0)
    {
        input = abs(input);
        sign = 1;
    }

    for(int i =0; i < binput_l; i++)
    {
        if(binput[i] == '.')
        {
            e = i-1;
        }
    }
    if(e==0) e = binput.length()-1;

    string wykladnik2 = dec2bin(e);
    if(wykladnik2.length()<7)
    {
        for(int i = 0; i <7 - int(wykladnik2.length()); i++)
            wykladnik.push_back('0');
    }
    wykladnik = wykladnik + wykladnik2;

    for(int i = 1; i <= 23; i++)
    {
        if(i < binput_l)
        {
            mantysa.push_back(binput[i]);
        }
        else
        {
            mantysa.push_back('0');
        }

    }

    if(sign == 0) ret.push_back('1');
    if(sign == 1) ret.push_back('0');
    ret += wykladnik;
    ret.push_back('0');
    ret += mantysa;
    return  ret;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout<<"W ktora strone chcesz przekonwertowac liczbe?\n\t";
    cout<<"1. IEEE 754 ==> wewnetrzny\n\t";
    cout<<"2. Wewnetrzny ==> IEEE 754\n";
    int in = 0;
    string in2;
    cin>>in;
    switch(in)
    {
    case 1:
        cout<<"Podaj liczbe binarna w formacie IEEE 754"<<endl;
        cin>>in2;
        cout<<dec2WEWbin(IEEEbin2dec(in2))<<endl;
        break;
    case 2:
        cout<<"Podaj liczbe binarna w formacie wewnetrznym"<<endl;
        cin>>in2;
        cout<<dec2IEEEbin(WEWbin2dec(in2))<<endl;
        break;
    }

    return 0;
}
