#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"

namespace sdds {
    Menu::Menu() {
        m_menuContent = nullptr;
        m_noOfOptions = 0;
    }

    Menu::Menu(const char* menuContent) {
        if (menuContent) {
            m_menuContent = new char[strlen(menuContent) + 1];
            strcpy(m_menuContent, menuContent);
        } else {
            m_menuContent = nullptr;
        }
        m_noOfOptions = 0;
    }

    Menu::Menu(unsigned int noOfOptions, const char* menuContent) {
        if (noOfOptions <= MAX_NUM_OPT && menuContent) {
            m_noOfOptions = noOfOptions;
            m_menuContent = new char[strlen(menuContent) + 1];
            strcpy(m_menuContent, menuContent);
        } else {
            m_noOfOptions = 0;
            m_menuContent = nullptr;
        }
    }

    Menu::~Menu() {
        delete[] m_menuContent;
        m_menuContent = nullptr;
    }

    unsigned int Menu::run() const {
        if (m_noOfOptions == 0) {
            std::cout << "Invalid Menu!" << std::endl;
            return 0;
        }
        
        std::cout << m_menuContent << "0- Exit" << std::endl;
        return ut.getint(0, m_noOfOptions, "> ");
    }
}
