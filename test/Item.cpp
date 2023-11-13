#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Item.h"
#include "Utils.h"

namespace sdds {
    bool Item::linear() const {
        return m_linear;
    }

    Item::Item() : iProduct() {
        m_price = m_qty = m_qtyNeeded = m_sku = 0;
        m_desc = nullptr;
        m_linear = false;
        m_Status.clear();
    }

    Item::Item(const Item& Item) {
        operator=(Item);
    }

    Item& Item::operator=(const Item& Item) {
        if (this != &Item) {
            m_price = Item.m_price;
            m_qty = Item.m_qty;
            m_qtyNeeded = Item.m_qtyNeeded;
            ut.alocpy(m_desc, Item.m_desc);
            m_linear = Item.m_linear;
            m_Status = Item.m_Status;
            m_sku = Item.m_sku;
        }
        return *this;
    }

    Item::~Item() {
        delete[] m_desc;
        m_desc = nullptr;
    }

    int Item::qtyNeeded() const {
        return m_qtyNeeded;
    }

    int Item::qty() const {
        return m_qty;
    }

    Item::operator double() const {
        return m_price;
    }

    Item::operator bool() const {
        return m_Status;
    }

    int Item::operator-=(int qty) {
        if (m_qty >= 0) {
            m_qty -= qty;
        }
        return m_qty;
    }

    int Item::operator+=(int qty) {
        return m_qty += qty;
    }

    void Item::linear(bool linear) {
        m_linear = linear;
    }

    void Item::clear() {
        m_Status.clear();
    }

    bool Item::operator==(int sku) const {
        return m_sku == sku;
    }

    bool Item::operator==(const char* desc) const {
        return (m_desc && desc && strstr(m_desc, desc));
    }

    std::ofstream& Item::save(std::ofstream& ofs) const {
        if (m_Status) {
            ofs << m_sku << "\t" << m_desc << "\t" << m_qty << "\t" << m_qtyNeeded << "\t" << std::fixed << std::setprecision(2) << m_price;
        }
        return ofs;
    }

    std::ifstream& Item::load(std::ifstream& ifs) {
        char value[1000];
        
        ifs >> m_sku;
        ifs.clear();
        ifs.ignore(1000, '\t');
        ifs.getline(value, 1000, '\t');
        ut.alocpy(m_desc, value);
        ifs >> m_qty;
        ifs >> m_qtyNeeded;
        ifs >> m_price;
        ifs.get();
        
        if (ifs.fail()) {
            m_Status = "Input file stream read failed!";
        }
        return ifs;
    }

    std::ostream& Item::display(std::ostream& os) const {
        if (m_Status) {
            if (m_linear) {
                os << std::setw(5) << std::setfill(' ') << m_sku << " | ";
                if (strlen(m_desc) > 35) {
                    for (int i = 0; i < 35; i++) {
                        os << std::left << m_desc[i];
                    }
                } else {
                    os << std::setw(35) << std::left << m_desc;
                }
                os << " | " << std::right << std::setw(4) << std::setfill(' ') << m_qty
                << " | " << std::right << std::setw(4) << std::setfill(' ') << m_qtyNeeded
                << " | " << std::right << std::setw(7) << std::setfill(' ') << std::fixed << std::setprecision(2) << m_price << " |";
            } else {
                os << "AMA Item:" << std::endl
                << m_sku << ": " << m_desc << std::endl
                << "Quantity Needed: " << m_qtyNeeded << std::endl
                << "Quantity Available: " << m_qty << std::endl
                << "Unit Price: $" << std::fixed << std::setprecision(2) << m_price << std::endl;
                os << "Needed Purchase Fund: $" << m_price * (m_qtyNeeded - m_qty) << std::endl;
            }
        }
        return os;
    }

    std::istream& Item::read(std::istream& is) {
        char value[1000];
        
        std::cout << "AMA Item:" << std::endl;
        std::cout << "SKU: " << m_sku << std::endl;
        std::cout << "Description: ";
        is.getline(value, 1000, '\n');
        ut.alocpy(m_desc, value);
        m_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: ");
        m_qty = ut.getint(0, m_qtyNeeded, "Quantity On Hand: ");
        m_price = ut.getdouble(0.0, 9999.0, "Unit Price: $");
        m_Status.clear();
        
        if (is.fail()) {
            m_Status = "Console entry failed!";
        } else {
            m_Status.clear();
        }
        return is;
    }

    int Item::readSku(std::istream& is) {
        m_sku = ut.getint(40000, 99999, "SKU: ");
        return m_sku;
    }
}
