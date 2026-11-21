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
                  int quantity, double unit_price){
                        this->drink_id = drink_id;
                        this->size = size;
                        this->quantity = quantity;
                        this->unit_price = unit_price;
                  };
        // Getters 
        string getDrinkID() {
            return drink_id;
        };

        char getSize() {
            return size;
        };

        int getQuantity() {
            return quantity;
        };

        double getUnitPrice() {
            return unit_price;
        };

        // Setters
        void setQuantity(int quantity) {
            if (quantity > 0) {
                this->quantity = quantity;
            } else {
                cout << "Invalid quantity. Quantity must be more than 0.";
            }
        };

        // Calculate subtotal
        double calculateSubtotal() {
            return quantity * unit_price;
        };

        // Displayer
        void displayItem() {
            cout << "Drink ID : " << drink_id << endl;
            cout << "Size : " << size << endl;
            cout << "Quantity : " << quantity << endl;
            cout << "Price : " << unit_price << endl;
            cout << "Subtotal : " << calculateSubtotal() << endl;
        };
};

// Struct OrderItemNode
struct OrderItemNode {
    OrderItem data;
    OrderItemNode* next;
    // Add
    OrderItemNode (OrderItem item) {
        data = item;
        next = nullptr;
    };
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
        };

        Order(int order_id, string order_date, string order_time, string staff_id){
            this->order_id = order_id;
            this->order_date = order_date;
            this->order_time = order_time;
            this->staff_id = staff_id;
            total_price = 0.00;
            status = "Pending";
            itemHead = nullptr;
        };

        // Destructor
        ~Order() {
            OrderItemNode* current = itemHead;

            while (current != nullptr) {
                OrderItemNode* temp = current;
                current = current->next;
                delete temp;
            }
        };

      // Getters
        int getOrderID() {
            return order_id;
        };
        string getOrderDate() {
            return order_date;
        };
        string getOrderTime() {
            return order_time;
        };
        string getStaffID() {
            return staff_id;
        };
        string getStatus() {
            return status;
        }

        // Methods
        void addItem() {
            
            if (status != "pending") {
                cout << "Items can't be added. An order is " << status << "." << endl;
                return;
            }
            
            string drink_id;
            char size;
            int quantity;
            double unit_price;

            cout << "Enter drink ID: ";
            cin >> drink_id;
            cout << "Enter size(S,M,L): ";
            cin >> size;
            cout << "Enter quantity: ";
            cin >> quantity;
            cout << "Enter unit price: ";
            cin >> unit_price;
            
            if (unit_price <= 0) {
                cout << "Invalid unit price." << endl;
                return;
            }
            
            if (quantity < 0) {
                cout << "Invalid quantity." << endl;
                return;
            }
            
            OrderItemNode *newNode = new OrderItemNode(OrderItem(drink_id, size, quantity, unit_price));
            
            if (itemHead == nullptr) {
                itemHead = newNode;
            } else {
                OrderItemNode *current = itemHead;
                while (current->next!=nullptr) {
                    current = current->next;
                }
                current->next = newNode;
            }
            cout << "Item added successfully." << endl;
        };

        void removeItem() {
            if (status != "pending") {
                cout << "Cannot remove item. Order is " << status << "." << endl;
                return;
            }
            
            if (itemHead == nullptr) {
                cout << "There is not any item to delete." << endl;
                return;
            }
            
            string drink_id;
            char size;
            cout << "Enter Drink ID: ";
            cin >> drink_id;
            cout << "Enter the size: ";
            cin >> size;
            
            OrderItemNode *current = itemHead;
            OrderItemNode *previous = nullptr;
            
            while (current!=nullptr) {
                
                if (
                    current->data.getDrinkID() == drink_id 
                    && 
                    current->data.getSize() == size
                    ) {
                    
                    if (previous == nullptr) {
                        itemHead = current->next;
                    } else {
                        previous->next = current->next;
                    }
                    delete current;
                    cout << "Remove item successfully." << endl;
                    return;
                }
                previous = current;
                current = current->next;
                cout << "Item not found." << endl;
            }
        };

        void updateItem() {
            
            if (status != "pending") {
                cout << "Cannot update item. Order is " << status << "." << endl;
                return;
            }
            
            if (itemHead == nullptr) {
                cout << "There is not any item to update." << endl;
                return;
            }
            
            string drink_id;
            char size;
            int newQuantity;

            OrderItemNode *current = itemHead;
            
            while (current != nullptr)  {
                
                if (
                    current->data.getDrinkID() == drink_id
                    &&
                    current->data.getSize() == size
                    ) {
                    
                    cout << "Enter new stock quantity: ";
                    cin >> newQuantity;
                    current->data.setQuantity(newQuantity);
                    cout << "Item updated successfully." << endl;
                    return;
                }
                current = current->next;
                cout << "Item not found." << endl;
            }
        };

        double calculateTotal() {
            
            total_price = 0.0;
            OrderItemNode *current = itemHead;
            
            while (current != nullptr) {
                total_price += current->data.calculateSubtotal();
                current = current->next;
            }
            return total_price;
        };

        void displayOrder() {
            cout << "============Display Order============" << endl;
            cout << "Order ID: " << order_id << endl;
            cout << "Date    : " << order_date << endl;
            cout << "Time    : " << order_time << endl;
            cout << "Staff     :" << staff_id << endl;
            cout << "Status     :" << status << endl;

        if (itemHead == nullptr) {
            cout << "No Item to display." << endl;
        } else {
            int num = 1;
            OrderItemNode *current = itemHead;
            
            while (current != nullptr) {
                    cout << "Item " << num++ << ":";
                    current->data.displayItem();
                    current = current->next;
                }
            }
            cout << "===============Display Total===============" << endl;
            cout << "Total: "<< calculateTotal() << endl;
        };

        void confirmOrder() {
            
            if (status != "pending") {
                cout << "Order is already " << status << "." << endl;
                return;
            }
            
            if (itemHead == nullptr) {
                cout << "Cannot confirm an empty order." << endl;
                return;
            }
            
            status = "confirmed";
            cout << "Order" << order_id << " confirmed" << endl;
        };

        void cancelOrder() {
            if (status == "cancelled") {
                cout << "Order is already cancelled." << endl;
                return;
            }
            
            status = "cancelled";
            cout << "Order #" << order_id << ": " << status << endl;
        }
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
