#include <iostream>
#include <fstream>
#include <cstring>
#include "AidMan.h"
#include "Utils.h"
#include "Date.h"

namespace sdds {
    unsigned int AidMan::menu() const {
        std::cout << "Aid Management System" << std::endl
                  << "Date: " << Date() << std::endl
                  << "Data file: " << (m_fileName ? m_fileName : "No file") << std::endl;
        return m_mainMenu.run();
    }

    int AidMan::search(int sku) const {
        for (int i = 0; i < m_noOfIproduct; i++) {
            if (*m_iProduct[i] == sku) {
                return i;
            }
        }
        return -1;
    }

    void AidMan::remove(int index) {
        delete m_iProduct[index];
        m_iProduct[index] = nullptr;

        for (int i = index; i < m_noOfIproduct - 1; i++) {
            m_iProduct[i] = m_iProduct[i + 1];
        }

        m_iProduct[m_noOfIproduct - 1] = nullptr;
        m_noOfIproduct--;
    }

    void AidMan::update() {
        std::cout << "Item description: ";
        char temp[1000]{};
        std::cin.getline(temp, 1000, '\n');

        if (list(temp) > 0) {
            std::cout << "Enter SKU: ";
            int sku = ut.getInt(10000, 99999);
            int index = search(sku);

            if (index != -1) {
                std::cout << "1- Add\n"
                             "2- Reduce\n"
                             "0- Exit\n"
                             "> ";

                int option = ut.getInt(0, 2);

                if (option == 0) {
                    std::cout << "Aborted!" << std::endl;
                } else {
                    int available = m_iProduct[index]->qtyNeeded() - m_iProduct[index]->qty();
                    int quantity = 0;

                    if (option == 1 && m_iProduct[index]->qty() < m_iProduct[index]->qtyNeeded()) {
                        std::cout << "Quantity to add: ";
                        quantity = ut.getInt(1, available);
                        *m_iProduct[index] += quantity;
                        std::cout << quantity << " items added!" << std::endl;
                    } else if (option == 2 && m_iProduct[index]->qty() > 0) {
                        std::cout << "Quantity to reduce: ";
                        quantity = ut.getInt(1, m_iProduct[index]->qty());
                        *m_iProduct[index] -= quantity;
                        std::cout << quantity << " items removed!" << std::endl;
                    } else {
                        std::cout << (option == 1 ? "Quantity Needed already fulfilled!" : "Quantity on hand is zero!") << std::endl;
                    }
                }
            } else {
                std::cout << "Item with SKU number " << sku << " not found." << std::endl;
            }
        } else {
            std::cout << "No matches found" << std::endl;
        }
        std::cout << std::endl;
    }

    void AidMan::sort() {
        iProduct* temp {};

        for (int i = 0; i < m_noOfIproduct; i++) {
            for (int j = 0; j < m_noOfIproduct - 1; j++) {
                int qtyDifferenceJ = m_iProduct[j]->qtyNeeded() - m_iProduct[j]->qty();
                int qtyDifferenceJ1 = m_iProduct[j + 1]->qtyNeeded() - m_iProduct[j + 1]->qty();

                if (qtyDifferenceJ < qtyDifferenceJ1) {
                    temp = m_iProduct[j];
                    m_iProduct[j] = m_iProduct[j + 1];
                    m_iProduct[j + 1] = temp;
                }
            }
        }
        std::cout << "Sort completed!" << std::endl << std::endl;
    }

    void AidMan::ship() {
        std::ofstream ofstr("shipping-order.txt");
        Date date {};
        int shipped {};

        ofstr << "Shipping Order, Date: " << date << std::endl
              << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << std::endl
              << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;

        for (int i = 0; i < m_noOfIproduct; ++i) {
            if (m_iProduct[i]->qty() == m_iProduct[i]->qtyNeeded()) {
                m_iProduct[i]->linear(true);
                ofstr << std::setw(4) << std::setfill(' ') << shipped + 1 << " | " << *m_iProduct[i] << std::endl;
                ++shipped;
                remove(i);
                --i;
            }
        }
        ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;

        std::cout << "Shipping Order for " << shipped << " times saved!" << std::endl << std::endl;
    }

    AidMan::AidMan() : m_mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
        m_fileName = nullptr;
    }

    AidMan::AidMan(const char* fileName) : m_mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
        if (fileName) {
            m_fileName = new char[strlen(fileName) + 1];
            strcpy(m_fileName, fileName);
        }
    }

    AidMan::~AidMan() {
        delete[] m_fileName;
        m_fileName = nullptr;
    }

    void AidMan::save() {
        if (!m_fileName) {
            return;
        }
        
        std::ofstream ofs(m_fileName);
        if (ofs.is_open()) {
            for (int i = 0; i < m_noOfIproduct; i++) {
                m_iProduct[i]->save(ofs);
                ofs << std::endl;
            }
            ofs.close();
        }
    }

    void AidMan::deallocate() {
        for (int i = 0; i < m_noOfIproduct; i++) {
            delete m_iProduct[i];
        }
        m_noOfIproduct = 0;
        
        if (m_fileName) {
            delete[] m_fileName;
        }
        m_fileName = nullptr;
    }

    bool AidMan::load() {
        char fileName[1000] {};
        
        save();
        deallocate();
        
        std::cout << "Enter file name: ";
        std::cin.getline(fileName, 1000, '\n');
        
        if (m_fileName) {
            delete[] m_fileName;
        }

        m_fileName = new char[strlen(fileName) + 1];
        strcpy(m_fileName, fileName);
        
        std::ifstream ifs(m_fileName);
        
        if (!ifs.is_open()) {
            std::cout << "Failed to open " << m_fileName << " for reading!" << std::endl
                      << "Would you like to create a new data file?" << std::endl
                      << "1- Yes!" << std::endl
                      << "0- Exit" << std::endl
                      << "> ";
            int selection = ut.getInt(0, 1);
            std::cout << std::endl;
            
            if (selection == 1) {
                std::ofstream newFile(m_fileName);
                if (newFile.is_open()) {
                    newFile.close();
                }
            }
            return false;
        }

        while (!ifs.eof()) {
            char next = ifs.peek();
            
            if (next == '\n' || next == '\t') {
                ifs.ignore(1000, '\n');
                next = ifs.peek();
            }
            
            if ((next >= '1' && next <= '3') || (next >= '4' && next <= '9')) {
                if (next >= '1' && next <= '3') {
                    m_iProduct[m_noOfIproduct] = new Perishable;
                } else {
                    m_iProduct[m_noOfIproduct] = new Item;
                }
                
                m_iProduct[m_noOfIproduct]->load(ifs);
                
                if (!m_iProduct[m_noOfIproduct]) {
                    delete m_iProduct[m_noOfIproduct];
                } else {
                    m_noOfIproduct++;
                }
            } else {
                ifs.setstate(std::ios::failbit);
            }
        }

        std::cout << m_noOfIproduct << " records loaded!" << std::endl << std::endl;
        ifs.close();
        return true;
    }

    int AidMan::list(const char* sub_desc) {
        int num = 0;
        
        if (m_noOfIproduct > 0) {
            std::cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << std::endl
                      << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;
            
            for (int i = 0; i < m_noOfIproduct; i++) {
                m_iProduct[i]->linear(true);
                
                if (sub_desc == nullptr || *m_iProduct[i] == sub_desc) {
                    std::cout << std::setw(4) << std::setfill(' ') << i + 1 << " | ";
                    std::cout << *m_iProduct[i] << std::endl;
                    num++;
                }
            }
            std::cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;
        } else {
            std::cout << "The list is empty!" << std::endl;
        }
        return num;
    }

    void AidMan::run() {
        unsigned int selection;
        int num = 0;

        do {
            selection = menu();
            std::cin.ignore(1000, '\n');
            if (selection != 0 && m_fileName == nullptr && selection != 7) {
                selection = 7;
            }

            switch (selection) {
                case 1:
                    std::cout << std::endl << "****List Items****" << std::endl;
                    num = list();
                    if (num > 0) {
                        std::cout << "Enter row number to display details or <ENTER> to continue:" << std::endl << "> ";
                        if (std::cin.peek() != '\n') {
                            int row = ut.getInt(1, num);
                            m_iProduct[row - 1]->linear(false);
                            std::cout << *m_iProduct[row - 1] << std::endl << std::endl;
                        } else {
                            std::cout << std::endl;
                        }
                    }
                    break;
                case 2:
                    std::cout << std::endl << "****Add Item****" << std::endl;
                    if (m_noOfIproduct == sdds_max_num_items) {
                        std::cout << "Database full!";
                    } else {
                        std::cout << "1- Perishable" << std::endl
                                  << "2- Non-Perishable" << std::endl
                                  << "-----------------" << std::endl
                                  << "0- Exit" << std::endl
                                  << "> ";
                        
                        int option = ut.getInt(0, 2);
                        if (option == 0) {
                            std::cout << "Aborted" << std::endl;
                        } else {
                            m_iProduct[m_noOfIproduct] = (option == 1) ? new Perishable : new Item;

                            int sku = m_iProduct[m_noOfIproduct]->readSku(std::cin);

                            if (search(sku) == -1) {
                                m_iProduct[m_noOfIproduct]->read(std::cin);
                                std::cout << std::endl;

                                if (*m_iProduct[m_noOfIproduct]) {
                                    m_noOfIproduct++;
                                }
                            } else {
                                std::cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << std::endl << std::endl;
                                delete m_iProduct[m_noOfIproduct];
                            }
                        }
                    }
                    break;
                case 3:
                    std::cout << std::endl << "****Remove Item****" << std::endl;
                    char temp[1000];
                    std::cout << "Item description: ";
                    std::cin.getline(temp, 1000, '\n');
                    num = list(temp);

                    if (num > 0) {
                        std::cout << "Enter SKU: ";
                        int sku = ut.getInt(10000, 99999);
                        int index = search(sku);

                        if (index == -1) {
                            std::cout << "SKU not found";
                        } else {
                            std::cout << "Following item will be removed:" << std::endl;
                            m_iProduct[index]->linear(false);
                            m_iProduct[index]->display(std::cout);

                            std::cout << "\nAre you sure?" << std::endl
                                      << "1- Yes!" << std::endl
                                      << "0- Exit" << std::endl
                                      << "> ";
                            int option = ut.getInt(0, 1);

                            if (option == 1) {
                                remove(index);
                                std::cout << "Item removed!" << std::endl;
                            } else {
                                std::cout << "Aborted!" << std::endl;
                            }
                        }
                    } else {
                        std::cout << "Item with " << temp << " not found!" << std::endl;
                    }
                    std::cout << std::endl;
                    break;
                case 4:
                    std::cout << std::endl << "****Update Quantity****" << std::endl;
                    update();
                    break;
                case 5:
                    std::cout << std::endl << "****Sort****" << std::endl;
                    sort();
                    break;
                case 6:
                    std::cout << std::endl << "****Ship Items****" << std::endl;
                    ship();
                    break;
                case 7:
                    std::cout << std::endl << "****New/Open Aid Database****" << std::endl;
                    load();
                    break;
                default:
                    std::cout << "Exiting Program!" << std::endl;
                    save();
                    deallocate();
                    break;
            }
        } while (selection != 0);
    }
}
