#include <iostream>
#include <ctime>
#include <cstring>
#include "Status.h"
#include "Utils.h"

namespace sdds {
    Status::Status(const char* desc) {
        ut.aloCpy(m_desc, desc);
    }

    Status::Status(const Status& Status) {
        ut.aloCpy(m_desc, Status.m_desc);
        m_code = Status.m_code;
    }

    Status::~Status() {
        clear();
    }

    Status& Status::operator=(const char* desc) {
        ut.aloCpy(m_desc, desc);
        return *this;
    }

    Status& Status::operator=(int code) {
        m_code = code;
        return *this;
    }

    Status& Status::operator=(const Status& Status) {
        if (this != &Status) {
            m_code = Status.m_code;
            ut.aloCpy(m_desc, Status.m_desc);
        }
        return *this;
    }

    Status::operator int() const {
        return m_code;
    }

    Status::operator const char* () const {
        return m_desc;
    }

    Status::operator bool() const {
        return m_desc == nullptr;
    }

    Status& Status::clear() {
        if (m_desc != nullptr) {
            delete[] m_desc;
            m_desc = nullptr;
        }
        m_code = 0;
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const Status& Status) {
        if ((int)Status != 0) {
            os << "ERR#" << (int)Status << ": ";
        }
        os << (const char*)Status;
        return os;
    }
}
