#include <iostream>
#include <ctime>
#include <cstring>
#include "Utils.h"

using namespace std;
namespace sdds {
    Utils ut;
    void Utils::testMode(bool testmode) {
        m_testMode = testmode;
    }

    void Utils::getSystemDate(int* year, int* mon, int* day) {
        if (m_testMode) {
            if(day) *day = sdds_testDay;
            if(mon) *mon = sdds_testMon;
            if(year) *year = sdds_testYear;
        } else {
            time_t t = std::time(NULL);
            tm lt = *localtime(&t);
            if (day) *day = lt.tm_mday;
            if (mon) *mon = lt.tm_mon + 1;
            if (year) *year = lt.tm_year + 1900;
        }
    }

    int Utils::daysOfMon(int month, int year)const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = (month >= 1 && month <= 12 ? month : 13)-1;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    void Utils::aloCpy(char*& destination, const char* source) {
        delete[] destination;
        destination = nullptr;
        if (source) {
            destination = new char[strlen(source) + 1];
            strcpy(destination, source);
        }
    }

    int Utils::getInt(const char* prompt) {
        int value = 0;
        bool isInt = false;
        
        if (prompt && prompt[0]) {
            cout << prompt;
        }
        
        while (!isInt) {
            cin >> value;
            
            if (cin.fail()) {
                cin.clear();
                cout << "Invalid Integer, retry: ";
                cin.ignore(10000, '\n');
            } else {
                if (cin.get() != '\n') {
                    cout << "Enter an integer only please, retry: ";
                    cin.ignore(10000, '\n');
                } else {
                    isInt = true;
                }
            }
        }
        return value;
    }

    int Utils::getInt(int min, int max, const char* prompt, const char* errMes) {
        int value = 0;
        bool isRange = false;
        
        while (!isRange) {
            value = getInt(prompt);
            if (value < min || value > max) {
                if (errMes) {
                    cout << errMes << ", retry: ";
                } else {
                    cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
                    prompt = nullptr;
                }
            } else {
                isRange = true;
            }
        }
        return value;
    }

    double Utils::getDouble(const char* prompt) {
        double value = 0;
        bool isDouble = false;
        
        if (prompt && prompt[0]) {
            cout << prompt;
        }
        
        while (!isDouble) {
            cin >> value;
            
            if (cin.fail()) {
                cin.clear();
                cout << "Invalid number, retry: ";
                cin.ignore(10000, '\n');
            } else {
                if (cin.get() != '\n') {
                    cout << "Enter a double only please, retry: ";
                    cin.ignore(10000, '\n');
                } else {
                    isDouble = true;
                }
            }
        }
        return value;
    }

    double Utils::getDouble(double min, double max, const char* prompt, const char* errMes) {
        double value = 0;
        bool isRange = false;
        
        while (!isRange) {
            value = getDouble(prompt);
            if (value < min || value > max) {
                if (errMes) {
                    cout << errMes << ", retry: ";
                } else {
                    cout.precision(2);
                    cout.setf(ios::fixed);
                    cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
                    prompt = nullptr;
                }
            } else {
                isRange = true;
            }
        }
        return value;
    }
}
