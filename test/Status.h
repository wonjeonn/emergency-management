#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

namespace sdds {
    class Status {
        char* m_desc = nullptr;
        int m_code;
    public:
        Status();
        Status(const char* desc);
        Status(const Status& Status);
        ~Status();
        Status& operator=(const char* desc);
        Status& operator=(int code);
        Status& operator=(const Status& Status);   
        operator int() const;
        operator const char*() const;
        operator bool() const;
        Status& clear();
    };
    std::ostream& operator<<(std::ostream& os, const Status& Status);
}

#endif // !SDDS_STATUS_H
