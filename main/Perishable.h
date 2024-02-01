#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h"

namespace sdds {
    class Perishable : public Item {
        Date m_expDate;
        char* m_instruction { nullptr };
    public:
        Perishable() = default;
        Perishable(const Perishable&  P);
        Perishable& operator=(const Perishable& Perishable);
        ~Perishable();
        const Date& expiry() const;
        virtual operator bool() const override;
        virtual int readSku(std::istream& is) override;
        virtual std::ofstream& save(std::ofstream& ofs) const override;
        virtual std::ifstream& load(std::ifstream& ifs) override;
        virtual std::ostream& display(std::ostream& os) const override;
        virtual std::istream& read(std::istream& is) override;
    };
}

#endif // !SDDS_PERISHABLE_H
