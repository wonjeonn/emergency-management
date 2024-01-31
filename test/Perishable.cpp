#include <iostream>
#include <fstream>
#include <cstring>
#include "Perishable.h"
#include "Utils.h"

namespace sdds {
    Perishable::Perishable(const Perishable& P) : Item(P) {
        ut.aloCpy(m_instruction, P.m_instruction);
        m_expDate = P.m_expDate;
    }

    Perishable& Perishable::operator=(const Perishable& Perishable) {
        if (this != &Perishable) {
            Item::operator=(Perishable);
            m_expDate = Perishable.m_expDate;
            if (Perishable.m_instruction) {
                ut.aloCpy(m_instruction, Perishable.m_instruction);
            }
        }
        return *this;
    }

    Perishable::~Perishable() {
        delete[] m_instruction;
        m_instruction = nullptr;
    }

    const Date& Perishable::expiry() const {
        return m_expDate;
    }

    Perishable::operator bool() const {
        return (m_sku >= 10000 && m_sku <= 39999) && m_Status;
    }

    int Perishable::readSku(std::istream& is) {
        m_sku = ut.getInt(10000, 39999, "SKU: ");
        return m_sku;
    }

    std::ofstream& Perishable::save(std::ofstream& ofs) const {
        if (*this) {
            Item::save(ofs);
            ofs << "\t";
            if (m_instruction) {
                ofs << m_instruction;
            }
            ofs << "\t";
            Date temp;
            temp = m_expDate;
            temp.formatted(false);
            ofs << temp;
        }
        return ofs;
    }

    std::ifstream& Perishable::load(std::ifstream& ifs) {
        Item::load(ifs);
        char value[1000];
        ifs.getline(value, 1000, '\t');
        ut.aloCpy(m_instruction, value);
        m_expDate.read(ifs);
        ifs.ignore(1000, '\n');
        
        if (ifs.fail()) {
            m_Status = "Input file stream read (perishable) failed!";
        }
        return ifs;
    }

    std::ostream& Perishable::display(std::ostream& os) const {
        if (Item::linear()) {
            Item::display(os);
            os << (m_instruction && m_instruction[0] != '\0' ? "*" : " ");
            os << m_expDate;
        } else {
            os << "Perishable ";
            Item::display(os);
            os << "Expiry date: " << m_expDate << std::endl;
            if (m_instruction && m_instruction[0] != '\0') {
                os << "Handling Instructions: " << m_instruction << std::endl;
            }
        }
        return os;
    }

    std::istream& Perishable::read(std::istream& is) {
        Item::read(is);
        delete[] m_instruction;
        m_instruction = nullptr;
        std::cout << "Expiry date (YYMMDD): ";
        is >> m_expDate;
        is.ignore(1000, '\n');
        std::cout << "Handling Instructions, ENTER to skip: ";
        if (is.peek() != '\n') {
            char value[1000];
            is.getline(value, 1000, '\n');
            m_instruction = new char[strlen(value) + 1];
            ut.aloCpy(m_instruction, value);
        }
        
        if (is.fail()) {
            m_Status = "Perishable console date entry failed!";
        }
        return is;
    }
}
