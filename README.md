# Disaster and Emergency Aid Management

The Disaster and Emergency Aid Management project efficiently manages the list of items required for shipping to areas affected by disasters. It tracks the quantity of each item needed, the number of items on hand, facilitates the shipping process, and stores data in a file for future use.

## Features

- **Management of non-perishable and perishable items:** Efficiently categorize and handle different types of items.
- **Quantity tracking for needed and available items:** Keep track of the quantity of items required and available in real-time.
- **Efficient shipping process:** Facilitate the shipping process for timely and effective delivery.
- **Data storage in a file for future reference:** Ensure data is securely stored for future analysis and reporting.

## Project Structure

### Core Classes

- [AidMan.cpp](main/AidMan.cpp), [AidMan.h](main/AidMan.h)
- [Date.cpp](main/Date.cpp), [Date.h](main/Date.h)
- [Item.cpp](main/Item.cpp), [Item.h](main/Item.h)
- [Perishable.cpp](main/Perishable.cpp), [Perishable.h](main/Perishable.h)
- [Status.cpp](main/Status.cpp), [Status.h](main/Status.h)

### Utility and Interface

- [Utils.cpp](main/Utils.cpp), [Utils.h](main/Utils.h)
- [Menu.cpp](main/Menu.cpp), [Menu.h](main/Menu.h)

### Interfaces

- [iProduct.cpp](main/iProduct.cpp), [iProduct.h](main/iProduct.h)

### Main Program

- [main.cpp](main/main.cpp)

### Testing

- [test/](test/)

## Usage Instructions

- **Designed an intuitive and user-friendly interface menu system.**
- **Implemented advanced features** such as item search by description, dynamic quantity updates, and item sorting based on need and availability.
- **Ensured data integrity through a robust file handling system,** allowing for efficient data storage and retrieval.
- **Maintained high standards of code documentation and organization** for effective collaboration.
