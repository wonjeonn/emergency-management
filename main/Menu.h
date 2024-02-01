#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>
#include <cstring>

namespace sdds {
    const int MAX_NUM_OPT = 15;
    class Menu {
        char* m_menuContent {};
        unsigned int m_noOfOptions {};
    public:
        Menu();
        Menu(const char* menuContent);
        Menu(const Menu& Menu) = delete;
        Menu& operator=(const Menu& Menu) = delete;
        ~Menu();
        unsigned int run() const;
    };
}

#endif // !SDDS_MENU_H
