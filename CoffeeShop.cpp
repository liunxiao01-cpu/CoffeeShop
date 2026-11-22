#include <iostream>
#include <string>
#include <fstream>  // CSV file handling
#include <sstream>  // Parsing CSV records
#include <cctype>  // Character conversion
using namespace std;

// --- Phase 2: Plan the classes, data records, program menu, and basic linked-list structures. ---

// Class Menu
// Class Menu
class Menu {
private:
    string drink_id;
    string drink;
    char size;
    double price;
    string type;

public:
    // Default Constructor
    Menu() {
        drink_id = "N/A";
        drink = "N/A";
        size = 'M';
        price = 0.00;
        type = "Ice";
    }

    // Parameterized Constructor
    Menu(string id, string name, char s = 'M',
         double p = 0.00, string t = "Ice") {

        drink_id = id;
        drink = name;

        if (s == 'S' || s == 'M' || s == 'L')
            size = s;
        else
            size = 'M';

        price = (p >= 0) ? p : 0.00;

        if (t == "Hot" || t == "Ice" || t == "Frappe")
            type = t;
        else
            type = "Ice";
    }

    // Getters
    string getDrinkID() { return drink_id; }
    string getDrink() { return drink; }
    char getSize() { return size; }
    double getPrice() { return price; }
    string getType() { return type; }

    // Setters
    void setDrink(string newDrink) {
        drink = newDrink;
    }

    void setSize(char newSize) {
        if (newSize == 'S' || newSize == 'M' || newSize == 'L')
            size = newSize;
        else
            cout << "Invalid size! Use S, M, or L.\n";
    }

    void setPrice(double newPrice) {
        if (newPrice >= 0)
            price = newPrice;
        else
            cout << "Price cannot be negative!\n";
    }

    void setType(string newType) {
        if (newType == "Hot" || newType == "Ice" || newType == "Frappe")
            type = newType;
        else
            cout << "Invalid type! Use Hot, Ice, or Frappe.\n";
    }

    // Display Menu Item
    void displayMenu() {
        cout << "------------------------\n";
        cout << "Drink ID : " << drink_id << endl;
        cout << "Drink    : " << drink << endl;
        cout << "Size     : " << size << endl;
        cout << "Price    : $" << price << endl;
        cout << "Type     : " << type << endl;
        cout << "------------------------\n";
    }

    // Update Menu Item
    void updateMenu() {
        string newDrink, newType;
        char newSize;
        double newPrice;

        cout << "Enter New Drink Name: ";
        getline(cin >> ws, newDrink);

        cout << "Enter New Size (S/M/L): ";
        cin >> newSize;

        cout << "Enter New Price: ";
        cin >> newPrice;

        cout << "Enter New Type (Hot/Ice/Frappe): ";
        cin >> newType;

        setDrink(newDrink);
        setSize(newSize);
        setPrice(newPrice);
        setType(newType);

        cout << "Menu item updated!\n";
    }
};

// Struct MenuNode
struct MenuNode {
    Menu data;
    MenuNode* next;

    MenuNode(Menu menu) {
        data = menu;
        next = nullptr;
    }
};

// Class Inventory

class Inventory {
private:
    int coffee_pack;
    int tea_pack;
    int matcha_pack;
    int honey_jar;
    int sugar_sachet;
    int milk_bottle;
    int lemon;

public:
    // Constructor
    Inventory() : coffee_pack(0), tea_pack(0),
                  matcha_pack(0), honey_jar(0),
                  sugar_sachet(0), milk_bottle(0),
                  lemon(0) {}

    // Check Valid Item
    bool isValidItem(string item) {
        return item == "coffee" || item == "tea" ||
               item == "matcha" || item == "honey" ||
               item == "sugar" || item == "milk" ||
               item == "lemon";
    }

    // Get Stock
    int getStock(string item) {
        if (item == "coffee") return coffee_pack;
        else if (item == "tea") return tea_pack;
        else if (item == "matcha") return matcha_pack;
        else if (item == "honey") return honey_jar;
        else if (item == "sugar") return sugar_sachet;
        else if (item == "milk") return milk_bottle;
        else if (item == "lemon") return lemon;

        return 0;
    }

    // Set Stock
    void setStock(string item, int quantity) {
        if (item == "coffee") coffee_pack = quantity;
        else if (item == "tea") tea_pack = quantity;
        else if (item == "matcha") matcha_pack = quantity;
        else if (item == "honey") honey_jar = quantity;
        else if (item == "sugar") sugar_sachet = quantity;
        else if (item == "milk") milk_bottle = quantity;
        else if (item == "lemon") lemon = quantity;
    }

    // Print Stock Status
    void printStatus(int stock) {
        if (stock == 0) {
            cout << "OUT OF STOCK";
        }
        else if (stock <= 5) {
            cout << "LOW STOCK";
        }
        else {
            cout << "OK";
        }
    }

    // Add Inventory
    void addInventory() {
        string item;
        int quantity;

        cout << "\nEnter item (coffee/tea/matcha/honey/sugar/milk/lemon): ";
        cin >> item;

        if (!isValidItem(item)) {
            cout << "Item not found.\n";
            return;
        }

        cout << "Enter quantity to add: ";

        if (!(cin >> quantity)) {
            cout << "Invalid quantity.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }

        if (quantity <= 0) {
            cout << "Quantity must be greater than zero.\n";
            return;
        }

        setStock(item, getStock(item) + quantity);

        cout << "Inventory updated successfully!\n";
        cout << "Current stock: " << getStock(item) << endl;
    }

    // Update Inventory
    void updateInventory() {
        string item;
        int quantity;

        cout << "\nEnter item to update: ";
        cin >> item;

        if (!isValidItem(item)) {
            cout << "Item not found.\n";
            return;
        }

        cout << "Enter new quantity: ";

        if (!(cin >> quantity)) {
            cout << "Invalid quantity.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }

        if (quantity < 0) {
            cout << "Quantity cannot be negative.\n";
            return;
        }

        setStock(item, quantity);

        cout << "Stock updated successfully!\n";
    }

    // View Inventory
    void viewInventory() {
        cout << "\n========== INVENTORY ==========\n";

        cout << "Coffee : " << coffee_pack << " | ";
        printStatus(coffee_pack);
        cout << endl;

        cout << "Tea    : " << tea_pack << " | ";
        printStatus(tea_pack);
        cout << endl;

        cout << "Matcha : " << matcha_pack << " | ";
        printStatus(matcha_pack);
        cout << endl;

        cout << "Honey  : " << honey_jar << " | ";
        printStatus(honey_jar);
        cout << endl;

        cout << "Sugar  : " << sugar_sachet << " | ";
        printStatus(sugar_sachet);
        cout << endl;

        cout << "Milk   : " << milk_bottle << " | ";
        printStatus(milk_bottle);
        cout << endl;

        cout << "Lemon  : " << lemon << " | ";
        printStatus(lemon);
        cout << endl;

        cout << "================================\n";
    }
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

// ================= STAFF CLASS =================

class Staff {
private:
    string staff_id;
    string staff_name;
    string position;
    string working_time;

public:
    // Default Constructor
    Staff() : staff_id("N/A"), staff_name("N/A"),
              position("N/A"), working_time("N/A") {}

    // Parameterized Constructor
    Staff(string id, string name, string pos, string time)
        : staff_id(id), staff_name(name),
          position(pos), working_time(time) {}

    // Getters
    string getStaffID() {
        return staff_id;
    }

    string getStaffName() {
        return staff_name;
    }

    // Setters
    void setStaffName(string name) {
        staff_name = name;
    }

    void setPosition(string pos) {
        position = pos;
    }

    void setWorkingTime(string time) {
        working_time = time;
    }

    // Display One Staff Member
    void displayStaff() {
        cout << "------------------------\n"
             << "Staff ID    : " << staff_id << "\n"
             << "Name        : " << staff_name << "\n"
             << "Position    : " << position << "\n"
             << "Working Time: " << working_time << "\n"
             << "------------------------\n";
    }

    // Update Staff Information
    void updateStaff() {
        cout << "Enter New Staff Name: ";
        getline(cin >> ws, staff_name);

        cout << "Enter New Position: ";
        getline(cin, position);

        cout << "Enter New Working Time: ";
        getline(cin, working_time);

        cout << "Staff information updated!\n";
    }
};

// ================= STAFF NODE =================

struct StaffNode {
    Staff data;
    StaffNode* next;

    StaffNode(Staff staff)
        : data(staff), next(nullptr) {}
};

// Class Sales Report
class SalesReport {
private:
    double totalRevenue;
    int totalOrders;

public:
    // Constructor
    SalesReport() : totalRevenue(0.0), totalOrders(0) {}

    // Getters
    double getTotalRevenue() {
        return totalRevenue;
    }

    int getTotalOrders() {
        return totalOrders;
    }

    // Calculate Revenue
    void calculateRevenue(OrderNode* orderHead) {
        totalRevenue = 0.0;

        OrderNode* current = orderHead;

        while (current != nullptr) {

            if (current->data.getStatus() == "Completed") {
                totalRevenue += current->data.getTotalPrice();
            }

            current = current->next;
        }
    }

    // Calculate Total Orders
    void calculateTotalOrders(OrderNode* orderHead) {
        totalOrders = 0;

        OrderNode* current = orderHead;

        while (current != nullptr) {

            if (current->data.getStatus() == "Completed") {
                totalOrders++;
            }

            current = current->next;
        }
    }

    // Display Daily Report
    void displayDailyReport() {
        cout << "\n====== DAILY SALES REPORT ======\n";

        cout << "Total Orders  : " << totalOrders << endl;
        cout << "Total Revenue : $" << totalRevenue << endl;

        cout << "================================\n";
    }

    // Display Best-Selling Drink
    void displayBestSellingDrink(OrderNode* orderHead) {
        string bestDrinkID = "N/A";
        int maxQuantity = 0;

        OrderNode* currentOrder = orderHead;

        while (currentOrder != nullptr) {

            if (currentOrder->data.getStatus() == "Completed") {

                OrderItemNode* currentItem =
                    currentOrder->data.getItemHead();

                while (currentItem != nullptr) {

                    string drinkID = currentItem->data.getDrinkID();
                    int totalQuantity = 0;

                    OrderNode* searchOrder = orderHead;

                    while (searchOrder != nullptr) {

                        if (searchOrder->data.getStatus() == "Completed") {

                            OrderItemNode* searchItem =
                                searchOrder->data.getItemHead();

                            while (searchItem != nullptr) {

                                if (searchItem->data.getDrinkID() == drinkID) {
                                    totalQuantity +=
                                        searchItem->data.getQuantity();
                                }

                                searchItem = searchItem->next;
                            }
                        }

                        searchOrder = searchOrder->next;
                    }

                    if (totalQuantity > maxQuantity) {
                        maxQuantity = totalQuantity;
                        bestDrinkID = drinkID;
                    }

                    currentItem = currentItem->next;
                }
            }

            currentOrder = currentOrder->next;
        }

        cout << "\n====== BEST-SELLING DRINK ======\n";

        if (maxQuantity == 0) {
            cout << "No completed orders found.\n";
        }
        else {
            cout << "Drink ID      : " << bestDrinkID << endl;
            cout << "Quantity Sold : " << maxQuantity << endl;
        }

        cout << "================================\n";
    }

    // Display Sales By Date
    void displaySalesByDate(OrderNode* orderHead, string date) {
        double revenue = 0.0;
        int count = 0;

        OrderNode* current = orderHead;

        while (current != nullptr) {

            if (current->data.getOrderDate() == date &&
                current->data.getStatus() == "Completed") {

                revenue += current->data.getTotalPrice();
                count++;
            }

            current = current->next;
        }

        cout << "\n====== SALES BY DATE ======\n";
        cout << "Date          : " << date << endl;
        cout << "Total Orders  : " << count << endl;
        cout << "Total Revenue : $" << revenue << endl;
        cout << "===========================\n";
    }
};

// Class CoffeeShop

class CoffeeShop {
private:
    Inventory inventory;

    // Linked List Head Pointers
    MenuNode* menuHead;
    StaffNode* staffHead;
    OrderNode* orderHead;

    // Staff Helper Methods
    void addStaff();
    void removeStaff();
    void viewStaff();
    void updateStaffRecord();

public:
    // Constructor
    CoffeeShop() : menuHead(nullptr),
                   staffHead(nullptr),
                   orderHead(nullptr) {}

    // Prevent unsafe copying
    CoffeeShop(const CoffeeShop&) = delete;
    CoffeeShop& operator=(const CoffeeShop&) = delete;

    // Destructor
    
~CoffeeShop() {

    // Delete Menu Linked List
    MenuNode* currentMenu = menuHead;

    while (currentMenu != nullptr) {
        MenuNode* temp = currentMenu;
        currentMenu = currentMenu->next;
        delete temp;
    }

    // Delete Staff Linked List
    StaffNode* currentStaff = staffHead;

    while (currentStaff != nullptr) {
        StaffNode* temp = currentStaff;
        currentStaff = currentStaff->next;
        delete temp;
    }

    // Delete Order Linked List
    OrderNode* currentOrder = orderHead;

    while (currentOrder != nullptr) {
        OrderNode* temp = currentOrder;
        currentOrder = currentOrder->next;
        delete temp;
    }

    cout << "CoffeeShop memory released.\n";
}

// General Method
void addStaff() {
    string id, name, pos, time;

    cout << "\nEnter Staff ID: ";
    cin >> id;

    // Check duplicate ID
    StaffNode* check = staffHead;

    while (check != nullptr) {
        if (check->data.getStaffID() == id) {
            cout << "Staff ID already exists!\n";
            return;
        }
        check = check->next;
    }

    cout << "Enter Staff Name: ";
    getline(cin >> ws, name);

    cout << "Enter Position: ";
    getline(cin, pos);

    cout << "Enter Working Time: ";
    getline(cin, time);

    Staff newStaff(id, name, pos, time);

    StaffNode* newNode = new StaffNode(newStaff);

    newNode->next = staffHead;
    staffHead = newNode;

    cout << "Staff added successfully!\n";
}


void viewStaff() {
    StaffNode* current = staffHead;

    if (current == nullptr) {
        cout << "No staff records found.\n";
        return;
    }

    while (current != nullptr) {
        current->data.displayStaff();
        current = current->next;
    }
}


void updateStaffRecord() {
    string id;

    cout << "Enter Staff ID to update: ";
    cin >> id;

    StaffNode* current = staffHead;

    while (current != nullptr) {

        if (current->data.getStaffID() == id) {
            current->data.updateStaff();
            return;
        }

        current = current->next;
    }

    cout << "Staff ID not found!\n";
}


void removeStaff() {
    string id;

    cout << "Enter Staff ID to remove: ";
    cin >> id;

    StaffNode* current = staffHead;
    StaffNode* previous = nullptr;

    while (current != nullptr) {

        if (current->data.getStaffID() == id) {

            if (previous == nullptr) {
                staffHead = current->next;
            }
            else {
                previous->next = current->next;
            }

            delete current;

            cout << "Staff removed successfully!\n";
            return;
        }

        previous = current;
        current = current->next;
    }

    cout << "Staff ID not found!\n";
}


void manageStaff() {
    int choice;

    do {
        cout << "\n====== STAFF MANAGEMENT ======\n";
        cout << "1. Add Staff\n";
        cout << "2. Remove Staff\n";
        cout << "3. Update Staff\n";
        cout << "4. View Staff\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter Choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                addStaff();
                break;

            case 2:
                removeStaff();
                break;

            case 3:
                updateStaffRecord();
                break;

            case 4:
                viewStaff();
                break;

            case 0:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}


void viewOrderHistory() {
    OrderNode* current = orderHead;

    if (current == nullptr) {
        cout << "No order history found.\n";
        return;
    }

    while (current != nullptr) {
        current->data.displayOrder();
        current = current->next;
    }
}


void generateSalesReport() {
    SalesReport report;

    // Calculate revenue and total orders
    report.calculateRevenue(orderHead);
    report.calculateTotalOrders(orderHead);

    // Display daily report summary
    report.displayDailyReport();

    // Display best-selling drink
    report.displayBestSellingDrink(orderHead);

    // Display sales by date
    string date;

    cout << "\nEnter Date (YYYY-MM-DD): ";
    cin >> date;

    report.displaySalesByDate(orderHead, date);
}

void manageInventory() {
    int choice;

    do {
        cout << "\n====== INVENTORY MANAGEMENT ======\n";
        cout << "1. View Inventory\n";
        cout << "2. Add Inventory\n";
        cout << "3. Update Inventory\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter Choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                inventory.viewInventory();
                break;

            case 2:
                inventory.addInventory();
                break;

            case 3:
                inventory.updateInventory();
                break;

            case 0:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}
void loadAllData() {
    cout << "\nLoading Coffee Shop Data...\n";

    inventory.loadInventory();

    // TODO: Load Menu linked list from menu.csv
    // TODO: Load Staff linked list from staff.csv
    // TODO: Load Order history from order.csv

    cout << "Data loading completed.\n";
}

void saveAllData() {
    cout << "\nSaving Coffee Shop Data...\n";

    inventory.saveInventory();

    // TODO: Save Menu linked list to menu.csv
    // TODO: Save Staff linked list to staff.csv
    // TODO: Save Order history to order.csv

    cout << "Data saving completed.\n";
}

void addMenu() {
    string id, name, type;
    char size;
    double price;

    cout << "\nEnter Drink ID: ";
    cin >> id;

    // Check duplicate ID
    MenuNode* check = menuHead;

    while (check != nullptr) {
        if (check->data.getDrinkID() == id) {
            cout << "Drink ID already exists!\n";
            return;
        }
        check = check->next;
    }

    cout << "Enter Drink Name: ";
    getline(cin >> ws, name);

    cout << "Enter Size (S/M/L): ";
    cin >> size;

    cout << "Enter Price: ";
    cin >> price;

    cout << "Enter Type (Hot/Ice/Frappe): ";
    cin >> type;

    Menu newMenu(id, name, size, price, type);

    MenuNode* newNode = new MenuNode(newMenu);
    newNode->next = menuHead;
    menuHead = newNode;

    cout << "Menu item added successfully!\n";
}

void displayMainMenu() {
    int choice;

    // Load saved data before starting
    loadAllData();

    do {
        cout << "\n================================\n";
        cout << "       COFFEE SHOP SYSTEM       \n";
        cout << "================================\n";
        cout << "1. Manage Menu\n";
        cout << "2. Manage Inventory\n";
        cout << "3. Take New Order\n";
        cout << "4. Manage Staff\n";
        cout << "5. View Order History\n";
        cout << "6. Sales Report\n";
        cout << "7. Save Data\n";
        cout << "0. Exit\n";
        cout << "================================\n";
        cout << "Enter Choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                manageMenu();
                break;

            case 2:
                manageInventory();
                break;

            case 3:
                takeOrder();
                break;

            case 4:
                manageStaff();
                break;

            case 5:
                viewOrderHistory();
                break;

            case 6:
                generateSalesReport();
                break;

            case 7:
                saveAllData();
                break;

            case 0:
                saveAllData();
                cout << "Thank you for using Coffee Shop System!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 0);
}
};


// Please check our proposal description and add more class. Have questions? We can discuss!
// After writing your own algorithm, please don't commit yet. Save the program to test and debug on your compiler first.
// And we will check it together. After succeed and agreed, we will commit it into GitHub!
