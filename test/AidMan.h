#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"

namespace sdds {
    class AidMan {
        char* m_fileName;
        Menu m_mainMenu;
        unsigned int menu() const;
    public:
        AidMan(const char* fileName);
        ~AidMan();
        AidMan(const AidMan& AidMan) = delete;
        AidMan& operator=(const AidMan& AidMan) = delete;
        void run();
    };
}

#endif // !SDDS_AIDMAN_H
