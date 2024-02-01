#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "iProduct.h"

namespace sdds {
    class Item : public iProduct {
    private:
        double m_price { 0 };
        int m_qty { 0 };
        int m_qtyNeeded { 0 };
        char* m_desc { nullptr };
        bool m_linear { false };
    protected:
        Status m_Status;
        int m_sku { 0 };
        bool linear() const;
    public:
        Item();
        Item(const Item& Item);
        Item& operator=(const Item& Item);
        ~Item();
        virtual int qtyNeeded() const override;
        virtual int qty() const override;
        virtual operator double() const override;
        virtual operator bool() const override;
        virtual int operator-=(int qty) override;
        virtual int operator+=(int qty) override;
        virtual void linear(bool linear) override;
        void clear();
        virtual bool operator==(int sku) const override;
        virtual bool operator==(const char* desc) const override;
        virtual std::ofstream& save(std::ofstream& ofs) const override;
        virtual std::ifstream& load(std::ifstream& ifs) override;
        virtual std::ostream& display(std::ostream& os) const override;
        virtual std::istream& read(std::istream& is) override;
        virtual int readSku(std::istream& is) override;
    };
}

#endif // !SDDS_ITEM_H
