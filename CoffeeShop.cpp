#include <iostream>
using namespace std;

// --- Phase 2: Plan the classes, data records, program menu, and basic linked-list structures. ---

// Class Menu
class Menu {
    // Menu members
    private:
        string drink_id;
        string drink;
        char size;
        double price;
        string type;

    // Constructors
    public:
        Menu() {
            drink_id = "N/A";
            drink = "N/A";
            size = 'M';
            price = 0.00;
            type = "N/A";
        }

        Menu(string drink_id) {
            this->drink_id = drink_id;
            drink = "N/A";
            size = 'M';
            price = 0.00;
            type = "N/A";
        }

        Menu(string drink_id, string drink) {
            this->drink_id = drink_id;
            this->drink = drink;
            size = 'M';
            price = 0.00;
            type = "N/A";
        }

        Menu(string drink_id, string drink, char size) {
            this->drink_id = drink_id;
            this->drink = drink;

            if (size == 'S' || size == 'M' || size == 'L') {
                this->size = size;
            } else {
                size = 'M';
            }
            
            type = "N/A";
            price = 0.00;
        }

        Menu(string drink_id, string drink, char size, double price) {
            this->drink_id = drink_id;
            this->drink = drink;
            
            if (size == 'S' || size == 'M' || size == 'L') {
                this->size = size;
            } else {
                size = 'M';
            }
            
            this->price = price;
            type = "N/A";
        }

        Menu(string drink_id, string drink, char size, double price, string type) {
            this->drink_id = drink_id;
            this->drink = drink;
            
            if (size == 'S' || size == 'M' || size == 'L') {
                this->size = size;
            } else {
                size = 'M';
            }

            this->price = price;

            if (type == "Hot" || type == "Ice" || type == "Frappe") {
                this->type = type;
            } else {
                type = "Ice";
            }
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

    // Method overload: addInventory(), useInventory(), viewInventory(), checkInventory() & updateInventory()
};

// Class OrderItem
class OrderItem {
    private:
        string drink;
        string size;
        int quantity;
        double unit_price;

    public:
        // Constructors
        // Getters and setters
        // Calculate subtotal
};

class Order {
    private:
        int order_id;
        double total_price;

        // Linked list of OrderItem objects

    public:
        // Constructor

        void addItem();
        void removeItem();
        double calculateTotal();
        void displayOrder();
        void confirmOrder();
};

// Class Staff
class Staff {
    private:
        string staff_id;
        string staff_name;
        string working_time;
}

// Class Sales Report
class SalesReport {
    private:
        double totalRevenue;
        int totalOrders;

    public:
        void calculateRevenue();
        void calculateTotalOrders();
        void displayDailyReport();
};

// Class CoffeeShop
class CoffeeShop {
    private:
        // Menu
        // Inventory
        // Staff
        // Order history

    public:
        void manageMenu();
        void manageInventory();
        void takeOrder();
        void manageStaff();
        void viewOrderHistory();
        void displayMainMenu();
};
// Please check our proposal description and add more class. Have questions? We can discuss!
// After writing your own algorithm, please don't commit yet. Save the program to test and debug on your compiler first.
// And we will check it together. After succeed and agreed, we will commit it into GitHub!
