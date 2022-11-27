#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "converter.h"

int main(int argc, char** argv) {
    std::string KEY = "7f901f5db2084e6d9f2fdbe72ec3b551";
    std::string URL = "https://api.currencyfreaks.com/latest?apikey=";
    URL+=KEY;
    URL+="&format=json";

    cpr::Response r = cpr::Get(cpr::Url{URL});
   std::cout << "Status code: " << r.status_code << '\n';
    std::string response = r.text;

    map<string,double> conversionRates;
    conversionRates = parseString(response);
    giveConversion("INR","AUD",100.000,conversionRates);
}
