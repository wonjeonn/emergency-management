#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"
#include "iProduct.h"
#include "Perishable.h"
#include "Item.h"

namespace sdds {
    const int sdds_max_num_items = 100;
    class AidMan {
        char* m_fileName {};
        Menu m_mainMenu {};
        unsigned int menu() const;
        iProduct* m_iProduct[sdds_max_num_items] {};
        int m_noOfIproduct {};
        void save();
        void deallocate();
        bool load();
        int list(const char* sub_desc = nullptr);
        int search(int sku) const;
        void remove(int index);
        void update();
        void sort();
        void ship();
    public:
        AidMan();
        AidMan(const char* fileName);
        ~AidMan();
        AidMan(const AidMan& AidMan) = delete;
        AidMan& operator=(const AidMan& AidMan) = delete;
        void run();
    };
}

#endif // !SDDS_AIDMAN_H
