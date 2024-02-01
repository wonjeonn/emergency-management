#include "Menu.h"

namespace sdds {
    Menu::Menu() : m_menuContent(nullptr), m_noOfOptions(0) {}

    Menu::Menu(const char* menuContent) {
        int num = 0;
        if (menuContent) {
            for (unsigned int i = 0; i < strlen(menuContent); i++) {
                if (menuContent[i] == '\t') {
                    num++;
                }
            }
            if (num + 1 <= MAX_NUM_OPT) {
                m_menuContent = new char[strlen(menuContent) + 1];
                strcpy(m_menuContent, menuContent);
                m_noOfOptions = num + 1;
            }
        }
    }

    Menu::~Menu() {
        if (m_menuContent) {
            delete[] m_menuContent;
        }
    }

    unsigned int Menu::run() const {
        unsigned int selection = 0;
        
        if (!m_menuContent) {
            std::cout << "Invalid Menu!" << std::endl;
            return selection;
        }
        
        char* temp = new char[strlen(m_menuContent) + 1];
        strcpy(temp, m_menuContent);
        
        char* token = strtok(temp, "\t");
        int i = 1;
        
        std::cout << "---------------------------------" << std::endl;
        while (i <= m_noOfOptions) {
            std::cout << i << "- " << token << std::endl;
            token = strtok(NULL, "\t");
            i++;
        }
        std::cout << "---------------------------------" << std::endl
        << "0- Exit" << std::endl
        << "> ";
        
        delete[] temp;
        
        bool valid = false;
        do {
            std::cin >> selection;
            valid = true;
            if (std::cin.fail()) {
                std::cout << "Invalid Integer, retry: ";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                valid = true;
            } else if (selection < 0 || selection >(unsigned int)m_noOfOptions) {
                std::cout << "Value out of range [0<=val<=" << m_noOfOptions << "]: ";
                std::cin.clear();
                valid = true;
            } else {
                valid = false;
            }
        } while (valid);
        
        return selection;
    }
}
