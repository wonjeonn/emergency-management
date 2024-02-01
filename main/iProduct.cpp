#include <iostream>
#include "iProduct.h"

namespace sdds {
    std::ostream& operator<<(std::ostream& os, const iProduct& iProduct) {
        return iProduct.display(os);
    }

    std::istream& operator>>(std::istream& is, iProduct& iProduct) {
        return iProduct.read(is);
    }
}
