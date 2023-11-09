#include <iostream>
#include <ctime>
#include <iomanip>
#include "Date.h"
#include "Utils.h"

namespace sdds {
    Date::Date() {
        m_format = true;
        ut.getSystemDate(&m_year, &m_month, &m_day);
        m_status.clear();
    }

    Date::Date(int year, int month, int day) {
        m_format = true;
        m_year = year;
        m_month = month;
        m_day = day;
    }

    bool Date::validate() {
        int year, month, day;
        ut.getSystemDate(&year, &month, &day);
        m_status.clear();

        if (m_year < year || m_year > MAX_YEAR_VAL) {
            m_status = "Invalid year in date";
            m_status = 1;
            return false;
        }
        if (m_month < 1 || m_month > 12) {
            m_status = "Invalid month in date";
            m_status = 2;
            return false;
        }
        if (m_day < 1 || m_day > ut.daysOfMon(m_month, m_year)) {
            m_status = "Invalid day in date";
            m_status = 3;
            return false;
        }
        return true;
    }

    int Date::uniqueDateVal() const {
        return m_year * 372 + m_month * 31 + m_day;
    }

    bool Date::operator==(const Date& Date) {
        return uniqueDateVal() == Date.uniqueDateVal();
    }

    bool Date::operator!=(const Date& Date) {
        return uniqueDateVal() != Date.uniqueDateVal();
    }

    bool Date::operator<(const Date& Date) {
        return uniqueDateVal() < Date.uniqueDateVal();
    }

    bool Date::operator>(const Date& Date) {
        return uniqueDateVal() > Date.uniqueDateVal();
    }

    bool Date::operator<=(const Date& Date) {
        return uniqueDateVal() <= Date.uniqueDateVal();
    }

    bool Date::operator>=(const Date& Date) {
        return uniqueDateVal() >= Date.uniqueDateVal();
    }

    const Status& Date::state() {
        return m_status;
    }

    Date& Date::formatted(bool format) {
        m_format = format;
        return *this;
    }

    Date::operator bool() const {
        return m_status;
    }

    std::ostream& Date::write(std::ostream& os) const {
        if (m_format) {
            os << m_year << "/" << std::setw(2) << std::setfill('0') << m_month << "/" << std::setw(2) << m_day;
        } else {
            os << m_year % 100 << std::setw(2) << std::setfill('0') << m_month << std::setw(2) << m_day;
        }
        return os;
    }

    std::istream& Date::read(std::istream& is) {
        int value;
        int year, month, day;
        ut.getSystemDate(&year, &month, &day);

        is >> value;
        m_status.clear();

        if (is) {
            m_year = value / 10000;
            m_month = (value / 100) % 100;
            m_day = value % 100;

            if (m_year == 0) {
                m_year = year;
            } else {
                m_year += 2000;
            }

            if (!validate()) {
                is.setstate(std::ios_base::badbit);
            }
        } else {
            m_status = "Invalid date value";
        }
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const Date& date) {
        return date.write(os);
    }

    std::istream& operator>>(std::istream& is, Date& date) {
        return date.read(is);
    }
}
