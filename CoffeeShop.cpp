#include <iostream>
using namespace std;

// --- Phase 2: Plan the classes, data records, program menu, and basic linked-list structures. ---

// Class Menu
class Menu {
    // Menu members
    private:
        string drink;
        char size;
        double price;
        string type;

    // Constructors
    public:
        Menu() {
            drink = "N/A";
            size = 'M';
            price = 0.00;
            type = "N/A";
        }

        Menu(string drink) {
            this->drink = drink;
            size = 'M';
            price = 0.00;
            type = "Ice";
        }

        Menu(string drink, char size) {
            this->drink = drink;

            if (size == 'S' || size == 'M' || size == 'L') {
                this->size = size;
            } else {
                size = 'M';
            }

            if (type == "Hot" || type == "Ice" || type == "Frappe") {
                this->type = type;
            } else {
                type = "Ice";
            }

            price = 0.00;
        }

        Menu(string drink, char size, double price) {
            this->drink = drink;
            
            if (size == 'S' || size == 'M' || size == 'L') {
                this->size = size;
            } else {
                size = 'M';
            }

            if (type == "Hot" || type == "Ice" || type == "Frappe") {
                this->type = type;
            } else {
                type = "Ice";
            }

            this->price = price;
        }
};

// Class Inventory
class Inventory {
    // Inventory Members
    private:
        int coffee_pack;
        int tea_pack;
        int matcha_pack;
        int honey_jar;
        int sugar_sachet;
        int milk_bottle;
        int lemon;
    
    // Constructor
    public:
        Inventory() : coffee_pack(0), tea_pack(0),
                      matcha_pack(0), honey_jar(0),
                      sugar_sachet(0), milk_bottle(0),
                      lemon(0)
        {}

    // Method overload: addStock(), useStock(), viewStock(), checkStock() & updateStock()
};

// Please check our proposal description and add more class. Have questions? We can discuss!
// After writing your own algorithm, please don't commit yet. Save the program to test and debug on your compiler first.
// And we will check it together. After succeed and agreed, we will commit it into GitHub!
