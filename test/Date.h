#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include "Status.h"

namespace sdds {
    const int MAX_YEAR_VAL = 2030;

    class Date {
        int m_year;
        int m_month;
        int m_day;
        Status m_status;
        bool m_format;
        bool validate();
        int uniqueDateVal() const;
    public:
        Date();
        Date(int year, int month, int day);
        bool operator==(const Date& Date);
        bool operator!=(const Date& Date);
        bool operator<(const Date& Date);
        bool operator>(const Date& Date);
        bool operator<=(const Date& Date);
        bool operator>=(const Date& Date);
        const Status& state();
        Date& formatted(bool format);
        operator bool() const;
        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);
    };
    std::ostream& operator<<(std::ostream& os, const Date& other);
    std::istream& operator>>(std::istream& is, Date& other);
}

#endif // !SDDS_DATE_H
