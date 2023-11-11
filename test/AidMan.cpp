#include <iostream>
#include <cstring>
#include "AidMan.h"
#include "Utils.h"
#include "Date.h"

namespace sdds {
    unsigned int AidMan::menu() const {
        std::cout << "Aid Management System" << std::endl
        << "Date: " << Date() << std::endl;
        if (m_fileName) {
            std::cout << "Data file: " << m_fileName << std::endl;
        } else {
            std::cout << "Data file: No file" << std::endl;
        }
        std::cout << std::endl;
        return m_mainMenu.run();
    }

    AidMan::AidMan(const char* fileName) : m_mainMenu { 7,
        "1- List Items\n"
        "2- Add Item\n"
        "3- Remove Item\n"
        "4- Update Quantity\n"
        "5- Sort\n"
        "6- Ship Items\n"
        "7- New/Open Aid Database\n"
        "---------------------------------\n"} {
            if (fileName) {
                m_fileName = new char[strlen(fileName) + 1];
                strcpy(m_fileName, fileName);
            } else {
                m_fileName = nullptr;
            }
        }

    AidMan::~AidMan() {
        delete[] m_fileName;
        m_fileName = nullptr;
    }

    void AidMan::run() {
        unsigned int selection;
        do {
            selection = menu();
            switch (selection) {
                case 1:
                    std::cout << std::endl << "****List Items****" << std::endl << std::endl;
                    break;
                case 2:
                    std::cout << std::endl << "****Add Item****" << std::endl << std::endl;
                    break;
                case 3:
                    std::cout << std::endl << "****Remove Item****" << std::endl << std::endl;
                    break;
                case 4:
                    std::cout << std::endl << "****Update Quantity****" << std::endl << std::endl;
                    break;
                case 5:
                    std::cout << std::endl << "****Sort****" << std::endl << std::endl;
                    break;
                case 6:
                    std::cout << std::endl << "****Ship Items****" << std::endl << std::endl;
                    break;
                case 7:
                    std::cout << std::endl << "****New/Open Aid Database****" << std::endl << std::endl;
                    break;
                default:
                    std::cout << "Exiting Program!" << std::endl;
                    break;
            }
        } while (selection != 0);
    }
}
