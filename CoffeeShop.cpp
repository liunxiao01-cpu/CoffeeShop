#include <iostream>
#include <string>
#include <fstream>  // CSV file handling
#include <sstream>  // Parsing CSV records
#include <iomanip>  // Formatting prices and reports
#include <cctype>  // Character conversion
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
            type = "Ice";
        }

        Menu(string drink_id, string drink,
             char size = 'M', double price = 0.00,
             string type = "Ice") {

            this->drink_id = drink_id;
            this->drink = drink;

            if (size == 'S' || size == 'M' || size == 'L') {
                this->size = size;
            } else {
                this->size = 'M';
            }

            if (price >= 0) {
                this->price = price;
            } else {
                this->price = 0.00;
            }

            if (type == "Hot" || type == "Ice" || type == "Frappe") {
                this->type = type;
            } else {
                this->type = "Ice";
            }
        }

// Getters
    string getDrinkID();
    string getDrink();
    char getSize();
    double getPrice();
    string getType();

// Setters
    void setDrink(string drink);
    void setSize(char size);
    void setPrice(double price);
    void setType(string type);

// Displayer
    void displayMenu();
};

// Struct MenuNode
struct MenuNode {
    Menu data;
    MenuNode* next;
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

    // Methods
    void addInventory(string item, int quantity);
    void viewInventory();
    void checkInventory(string item);
    void updateInventory(string item, int quantity);
    void loadInventory();
    void saveInventory();
};

// Class OrderItem
class OrderItem {
    private:
        string drink_id;
        char size;
        int quantity;
        double unit_price;

    public:
        // Constructors
        OrderItem() : drink_id("N/A"), size('M'),
              quantity(0), unit_price(0.00) {}

        OrderItem(string drink_id, char size,
                  int quantity, double unit_price);
        // Getters 
        string getDrinkID();
        char getSize();
        int getQuantity();
        double getUnitPrice();

        // Setters
        void setQuantity(int quantity);

        // Calculate subtotal
        double calculateSubtotal();

        // Displayer
        void displayItem();
};

// Struct OrderItemNode
struct OrderItemNode {
    OrderItem data;
    OrderItemNode* next;
};

class Order {
    private:
        int order_id;
        double total_price;
        string order_date;
        string order_time;
        string staff_id;
        string status;

        // Linked list of OrderItem objects
        OrderItemNode* itemHead;

    public:
        // Constructor
        Order() {
            order_id = 0;
            total_price = 0.00;
            order_date = "N/A";
            order_time = "N/A";
            staff_id = "N/A";
            status = "Pending";
            itemHead = nullptr;
        }

        Order(int order_id, string order_date,
              string order_time, string staff_id);

        // Destructor
        ~Order();

    	// Getters
        int getOrderID();
        string getOrderDate();
        string getOrderTime();
        string getStaffID();
        string getStatus();

        // Methods
        void addItem();
        void removeItem();
        void updateItem();
        double calculateTotal();
        void displayOrder();
        void confirmOrder();
        void cancelOrder();
};

// Struct OrderNode
struct OrderNode {
    Order data;
    OrderNode* next;
};

// Class Staff
class Staff {

    private:
        string staff_id;
        string staff_name;
        string position;
        string working_time;

    public:
    // Constructor
    Staff() : staff_id("N/A"), staff_name("N/A"),
          position("N/A"), working_time("N/A") {}

    // Methods
    void updateStaff();
    void displayStaff();

    // Getters
    string getStaffID();
    string getStaffName();

    // Setters
    void setStaffName(string name);
    void setPosition(string position);
    void setWorkingTime(string working_time);
};

// Struct StaffNode
struct StaffNode {
    Staff data;
    StaffNode* next;
};

// Class Sales Report
class SalesReport {
    private:
        double totalRevenue;
        int totalOrders;

    public:
        // Constructor
        SalesReport() : totalRevenue(0.0), totalOrders(0) {}

        // Methods
        void calculateRevenue();
        void calculateTotalOrders();
        void displayDailyReport();
        void displayBestSellingDrink();
        void displaySalesByDate();
};

// Class CoffeeShop
class CoffeeShop {
    private:
        Inventory inventory;
        MenuNode* menuHead;
        StaffNode* staffHead;
        OrderNode* orderHead;
        // Menu
        // Inventory
        // Staff
        // Order history

    public:

        // Constructor
        CoffeeShop() : menuHead(nullptr),
               staffHead(nullptr),
               orderHead(nullptr) {}

        // Destructor
        ~CoffeeShop();

        // Methods
        void manageMenu();
        void manageInventory();
        void takeOrder();
        void manageStaff();
        void viewOrderHistory();
        void displayMainMenu();
        void generateSalesReport();
        void loadAllData();
        void saveAllData();

};
// Please check our proposal description and add more class. Have questions? We can discuss!
// After writing your own algorithm, please don't commit yet. Save the program to test and debug on your compiler first.
// And we will check it together. After succeed and agreed, we will commit it into GitHub!
