#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "iProduct.h"

namespace sdds {
    class Item : public iProduct {
    private:
        double m_price;
        int m_qty;
        int m_qtyNeeded;
        char* m_desc;
        bool m_linear;
    protected:
        Status m_Status;
        int m_sku;
        bool linear() const;
    public:
        Item();
        Item(const Item& Item);
        Item& operator=(const Item& Item);
        ~Item();
        int qtyNeeded() const;
        int qty() const;
        operator double() const;
        operator bool() const;
        virtual int operator-=(int qty);
        virtual int operator+=(int qty);
        virtual void linear(bool linear);
        void clear();
        virtual bool operator==(int sku) const;
        virtual bool operator==(const char* desc) const;
        virtual std::ofstream& save(std::ofstream& ofs) const;
        virtual std::ifstream& load(std::ifstream& ifs);
        virtual std::ostream& display(std::ostream& os) const;
        virtual std::istream& read(std::istream& is);
        virtual int readSku(std::istream& is);
    };
}

#endif // !SDDS_ITEM_H
