#include <QCoreApplication>
#include <iostream>
#include <cmath>

using namespace std;

int bin2dec(string bin)
{
    int suma = 0;
    int dlugosc = bin.length();
    for(int i = dlugosc-1;i>=0;i--)
    {
        if(bin[i]=='1')
        {
            suma = suma + pow(2, (dlugosc-1-i));
        }
    }
    return suma;
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
    cout<<wykladnik<<endl;
    for(int i = 9;i<=31;i++)
    {
        mantysa.push_back(w[i]);
    }
    cout<<mantysa<<endl;
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



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    string w;
    cout << "Podaj IEEE"<<endl;
    string sss;
    cin>>sss;
    cout<<IEEEbin2dec(sss);




    return 0;
}
