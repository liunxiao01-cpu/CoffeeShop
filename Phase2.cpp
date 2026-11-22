#include <iostream>
#include <string>
using namespace std;

// ===================== MENU =====================

class Menu {
private:
    string drink_id;
    string drink_name;
    char size;
    double price;
    string type;

public:
    Menu() {
        drink_id = "N/A";
        drink_name = "N/A";
        size = 'M';
        price = 0;
        type = "Ice";
    }

    Menu(string id, string name, char s, double p, string t) {
        drink_id = id;
        drink_name = name;
        size = s;
        price = p;
        type = t;
    }

    string getDrinkID() { return drink_id; }
    string getDrinkName() { return drink_name; }
    char getSize() { return size; }
    double getPrice() { return price; }
    string getType() { return type; }

    void setDrinkName(string name) { drink_name = name; }
    void setSize(char s) { size = s; }
    void setPrice(double p) { price = p; }
    void setType(string t) { type = t; }

    void displayMenu() {
        cout << "ID: " << drink_id
             << " | Drink: " << drink_name
             << " | Size: " << size
             << " | Price: $" << price
             << " | Type: " << type << endl;
    }
};

// One node stores one Menu object.
struct MenuNode {
    Menu data;
    MenuNode* next;

    MenuNode(Menu newMenu) {
        data = newMenu;
        next = nullptr;
    }
};


// ===================== INVENTORY =====================

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
    Inventory() {
        coffee_pack = 0;
        tea_pack = 0;
        matcha_pack = 0;
        honey_jar = 0;
        sugar_sachet = 0;
        milk_bottle = 0;
        lemon = 0;
    }

    bool isValidItem(string item) {
        return item == "coffee" || item == "tea" || item == "matcha" ||
               item == "honey" || item == "sugar" || item == "milk" ||
               item == "lemon";
    }

    int getStock(string item) {
        if (item == "coffee") return coffee_pack;
        if (item == "tea") return tea_pack;
        if (item == "matcha") return matcha_pack;
        if (item == "honey") return honey_jar;
        if (item == "sugar") return sugar_sachet;
        if (item == "milk") return milk_bottle;
        if (item == "lemon") return lemon;

        return -1;
    }

    void setStock(string item, int quantity) {
        if (item == "coffee") coffee_pack = quantity;
        else if (item == "tea") tea_pack = quantity;
        else if (item == "matcha") matcha_pack = quantity;
        else if (item == "honey") honey_jar = quantity;
        else if (item == "sugar") sugar_sachet = quantity;
        else if (item == "milk") milk_bottle = quantity;
        else if (item == "lemon") lemon = quantity;
    }

    void addInventory(string item, int quantity) {
        if (!isValidItem(item) || quantity <= 0) {
            cout << "Invalid item or quantity.\n";
            return;
        }

        int currentStock = getStock(item);
        setStock(item, currentStock + quantity);
        cout << "Inventory updated.\n";
    }

    void updateInventory(string item, int quantity) {
        if (!isValidItem(item) || quantity < 0) {
            cout << "Invalid item or quantity.\n";
            return;
        }

        setStock(item, quantity);
        cout << "Inventory updated.\n";
    }

    void checkInventory(string item) {
        if (!isValidItem(item)) {
            cout << "Item not found.\n";
            return;
        }

        int stock = getStock(item);
        cout << item << ": " << stock << " units";

        if (stock == 0) cout << " (OUT OF STOCK)";
        else if (stock <= 5) cout << " (LOW STOCK)";
        else cout << " (OK)";

        cout << endl;
    }

    void viewInventory() {
        checkInventory("coffee");
        checkInventory("tea");
        checkInventory("matcha");
        checkInventory("honey");
        checkInventory("sugar");
        checkInventory("milk");
        checkInventory("lemon");
    }
};


// ===================== ORDER ITEM =====================

class OrderItem {
private:
    string drink_id;
    char size;
    int quantity;
    double unit_price;

public:
    OrderItem() {
        drink_id = "N/A";
        size = 'M';
        quantity = 0;
        unit_price = 0;
    }

    OrderItem(string id, char s, int q, double price) {
        drink_id = id;
        size = s;
        quantity = q;
        unit_price = price;
    }

    string getDrinkID() { return drink_id; }
    char getSize() { return size; }
    int getQuantity() { return quantity; }
    double getUnitPrice() { return unit_price; }

    void setQuantity(int q) {
        if (q > 0) quantity = q;
    }

    double calculateSubtotal() {
        return quantity * unit_price;
    }

    void displayItem() {
        cout << drink_id << " | Size: " << size
             << " | Quantity: " << quantity
             << " | Unit price: $" << unit_price
             << " | Subtotal: $" << calculateSubtotal() << endl;
    }
};

// One order can contain many order items.
struct OrderItemNode {
    OrderItem data;
    OrderItemNode* next;

    OrderItemNode(OrderItem item) {
        data = item;
        next = nullptr;
    }
};


// ===================== ORDER =====================

class Order {
private:
    int order_id;
    string order_date;
    string order_time;
    string staff_id;
    string status;
    double total_price;

    OrderItemNode* itemHead;

public:
    Order() {
        order_id = 0;
        order_date = "N/A";
        order_time = "N/A";
        staff_id = "N/A";
        status = "Pending";
        total_price = 0;
        itemHead = nullptr;
    }

    Order(int id, string date, string time, string staff) {
        order_id = id;
        order_date = date;
        order_time = time;
        staff_id = staff;
        status = "Pending";
        total_price = 0;
        itemHead = nullptr;
    }

    // Delete all item nodes belonging to this order.
    ~Order() {
        OrderItemNode* current = itemHead;

        while (current != nullptr) {
            OrderItemNode* temp = current;
            current = current->next;
            delete temp;
        }
    }

    int getOrderID() { return order_id; }
    string getOrderDate() { return order_date; }
    string getOrderTime() { return order_time; }
    string getStaffID() { return staff_id; }
    string getStatus() { return status; }

    double calculateTotal() {
        total_price = 0;
        OrderItemNode* current = itemHead;

        while (current != nullptr) {
            total_price += current->data.calculateSubtotal();
            current = current->next;
        }

        return total_price;
    }

    void addItem(string id, char s, int quantity, double price) {
        if (status != "Pending") {
            cout << "This order can no longer be changed.\n";
            return;
        }

        if (quantity <= 0 || price <= 0) {
            cout << "Invalid quantity or price.\n";
            return;
        }

        OrderItem newItem(id, s, quantity, price);
        OrderItemNode* newNode = new OrderItemNode(newItem);

        if (itemHead == nullptr) {
            itemHead = newNode;
        } else {
            OrderItemNode* current = itemHead;

            while (current->next != nullptr) {
                current = current->next;
            }

            current->next = newNode;
        }

        cout << "Item added to order.\n";
    }

    void viewItems() {
        if (itemHead == nullptr) {
            cout << "This order has no items.\n";
            return;
        }

        OrderItemNode* current = itemHead;

        while (current != nullptr) {
            current->data.displayItem();
            current = current->next;
        }
    }

    void removeItem(string id, char s) {
        if (status != "Pending") {
            cout << "This order can no longer be changed.\n";
            return;
        }

        OrderItemNode* current = itemHead;
        OrderItemNode* previous = nullptr;

        while (current != nullptr) {
            if (current->data.getDrinkID() == id &&
                current->data.getSize() == s) {

                if (previous == nullptr) {
                    itemHead = current->next;
                } else {
                    previous->next = current->next;
                }

                delete current;
                cout << "Item removed.\n";
                return;
            }

            previous = current;
            current = current->next;
        }

        cout << "Item not found.\n";
    }

    void updateItem(string id, char s, int newQuantity) {
        if (status != "Pending") {
            cout << "This order can no longer be changed.\n";
            return;
        }

        OrderItemNode* current = itemHead;

        while (current != nullptr) {
            if (current->data.getDrinkID() == id &&
                current->data.getSize() == s) {

                current->data.setQuantity(newQuantity);
                cout << "Item quantity updated.\n";
                return;
            }

            current = current->next;
        }

        cout << "Item not found.\n";
    }

    void confirmOrder() {
        if (itemHead == nullptr) {
            cout << "Cannot confirm an empty order.\n";
            return;
        }

        if (status == "Pending") {
            status = "Confirmed";
            cout << "Order confirmed.\n";
        } else {
            cout << "Order is not pending.\n";
        }
    }

    void cancelOrder() {
        if (status == "Completed") {
            cout << "A completed order cannot be cancelled.\n";
            return;
        }

        status = "Cancelled";
        cout << "Order cancelled.\n";
    }

    void completeOrder() {
        if (status == "Confirmed") {
            status = "Completed";
            cout << "Order completed.\n";
        } else {
            cout << "Only confirmed orders can be completed.\n";
        }
    }

    void displayOrder() {
        cout << "\nOrder ID: " << order_id << endl;
        cout << "Date: " << order_date << endl;
        cout << "Time: " << order_time << endl;
        cout << "Staff ID: " << staff_id << endl;
        cout << "Status: " << status << endl;

        viewItems();

        cout << "Total: $" << calculateTotal() << endl;
    }
};

// The node stores a pointer to an Order.
// CoffeeShop creates and deletes the Order objects.
struct OrderNode {
    Order* data;
    OrderNode* next;

    OrderNode(Order* newOrder) {
        data = newOrder;
        next = nullptr;
    }
};


// ===================== STAFF =====================

class Staff {
private:
    string staff_id;
    string staff_name;
    string position;
    string working_time;

public:
    Staff() {
        staff_id = "N/A";
        staff_name = "N/A";
        position = "N/A";
        working_time = "N/A";
    }

    Staff(string id, string name, string job, string time) {
        staff_id = id;
        staff_name = name;
        position = job;
        working_time = time;
    }

    string getStaffID() { return staff_id; }
    string getStaffName() { return staff_name; }

    void setStaffName(string name) { staff_name = name; }
    void setPosition(string job) { position = job; }
    void setWorkingTime(string time) { working_time = time; }

    void displayStaff() {
        cout << "Staff ID: " << staff_id << endl;
        cout << "Name: " << staff_name << endl;
        cout << "Position: " << position << endl;
        cout << "Working time: " << working_time << endl;
    }

    void updateStaff(string name, string job, string time) {
        staff_name = name;
        position = job;
        working_time = time;
    }
};

struct StaffNode {
    Staff data;
    StaffNode* next;

    StaffNode(Staff newStaff) {
        data = newStaff;
        next = nullptr;
    }
};


// ===================== SALES REPORT =====================

class SalesReport {
private:
    double totalRevenue;
    int totalOrders;

public:
    SalesReport() {
        totalRevenue = 0;
        totalOrders = 0;
    }

    void calculateReport(OrderNode* orderHead) {
        totalRevenue = 0;
        totalOrders = 0;

        OrderNode* current = orderHead;

        while (current != nullptr) {
            if (current->data->getStatus() == "Completed") {
                totalRevenue += current->data->calculateTotal();
                totalOrders++;
            }

            current = current->next;
        }
    }

    void displayReport() {
        cout << "\n===== SALES REPORT =====\n";
        cout << "Completed orders: " << totalOrders << endl;
        cout << "Total revenue: $" << totalRevenue << endl;
    }
};


// ===================== COFFEE SHOP =====================

class CoffeeShop {
private:
    Inventory inventory;

    // Each pointer stores the first node of a linked list.
    MenuNode* menuHead;
    StaffNode* staffHead;
    OrderNode* orderHead;

    int nextOrderID;

    // Administrator password.
    string adminPassword;

    // Ask for the password whenever an administrator function is used.
    bool checkAdminPassword() {
        string enteredPassword;

        cout << "Enter administrator password: ";
        cin >> enteredPassword;

        if (enteredPassword == adminPassword) {
            return true;
        }

        cout << "Incorrect password. Access denied.\\n";
        return false;
    }

public:
    CoffeeShop() {
        menuHead = nullptr;
        staffHead = nullptr;
        orderHead = nullptr;
        nextOrderID = 1;

        // Default administrator password.
        adminPassword = "admin123";
    }

    // ---------- ADMINISTRATOR SECURITY ----------

    void changeAdminPassword() {
        // The current password must be correct before changing it.
        if (checkAdminPassword() == false) {
            return;
        }

        string newPassword;

        cout << "Enter new password: ";
        cin >> newPassword;

        if (newPassword.length() < 6) {
            cout << "Password must contain at least 6 characters.\\n";
            return;
        }

        adminPassword = newPassword;
        cout << "Administrator password changed successfully.\\n";
    }

    // Free all nodes when the CoffeeShop object is destroyed.
    ~CoffeeShop() {
        MenuNode* menuCurrent = menuHead;
        while (menuCurrent != nullptr) {
            MenuNode* temp = menuCurrent;
            menuCurrent = menuCurrent->next;
            delete temp;
        }

        StaffNode* staffCurrent = staffHead;
        while (staffCurrent != nullptr) {
            StaffNode* temp = staffCurrent;
            staffCurrent = staffCurrent->next;
            delete temp;
        }

        OrderNode* orderCurrent = orderHead;
        while (orderCurrent != nullptr) {
            OrderNode* temp = orderCurrent;
            orderCurrent = orderCurrent->next;

            delete temp->data;  // Order deletes its own OrderItem nodes.
            delete temp;
        }
    }

    // ---------- MENU LINKED LIST ----------

    void addMenuItem(Menu newMenu) {
        if (checkAdminPassword() == false) return;
        MenuNode* newNode = new MenuNode(newMenu);

        if (menuHead == nullptr) {
            menuHead = newNode;
        } else {
            MenuNode* current = menuHead;

            while (current->next != nullptr) {
                current = current->next;
            }

            current->next = newNode;
        }

        cout << "Menu item added.\n";
    }

    void viewMenu() {
        if (menuHead == nullptr) {
            cout << "Menu is empty.\n";
            return;
        }

        MenuNode* current = menuHead;

        while (current != nullptr) {
            current->data.displayMenu();
            current = current->next;
        }
    }

    void removeMenuItem(string id) {
        if (checkAdminPassword() == false) return;
        MenuNode* current = menuHead;
        MenuNode* previous = nullptr;

        while (current != nullptr) {
            if (current->data.getDrinkID() == id) {
                if (previous == nullptr) {
                    menuHead = current->next;
                } else {
                    previous->next = current->next;
                }

                delete current;
                cout << "Menu item removed.\n";
                return;
            }

            previous = current;
            current = current->next;
        }

        cout << "Menu item not found.\n";
    }

    // ---------- INVENTORY ----------

    void manageInventory() {
        if (checkAdminPassword() == false) return;
        int choice;
        string item;
        int quantity;

        cout << "\n1. Add stock\n";
        cout << "2. Set stock quantity\n";
        cout << "3. View inventory\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            cout << "Enter item name: ";
            cin >> item;
            cout << "Enter quantity: ";
            cin >> quantity;

            if (choice == 1) inventory.addInventory(item, quantity);
            else inventory.updateInventory(item, quantity);
        } else if (choice == 3) {
            inventory.viewInventory();
        } else {
            cout << "Invalid choice.\n";
        }
    }

    // ---------- STAFF LINKED LIST ----------

    void addStaff(Staff newStaff) {
        if (checkAdminPassword() == false) return;
        StaffNode* newNode = new StaffNode(newStaff);

        if (staffHead == nullptr) {
            staffHead = newNode;
        } else {
            StaffNode* current = staffHead;

            while (current->next != nullptr) {
                current = current->next;
            }

            current->next = newNode;
        }

        cout << "Staff member added.\n";
    }

    void viewStaff() {
        if (checkAdminPassword() == false) return;
        if (staffHead == nullptr) {
            cout << "There is no staff record.\n";
            return;
        }

        StaffNode* current = staffHead;

        while (current != nullptr) {
            current->data.displayStaff();
            current = current->next;
        }
    }

    void removeStaff(string id) {
        if (checkAdminPassword() == false) return;
        StaffNode* current = staffHead;
        StaffNode* previous = nullptr;

        while (current != nullptr) {
            if (current->data.getStaffID() == id) {
                if (previous == nullptr) {
                    staffHead = current->next;
                } else {
                    previous->next = current->next;
                }

                delete current;
                cout << "Staff member removed.\n";
                return;
            }

            previous = current;
            current = current->next;
        }

        cout << "Staff member not found.\n";
    }

    // ---------- ORDER LINKED LIST ----------

    void takeOrder(string date, string time, string staffID) {
        Order* newOrder = new Order(nextOrderID, date, time, staffID);
        nextOrderID++;

        OrderNode* newNode = new OrderNode(newOrder);

        if (orderHead == nullptr) {
            orderHead = newNode;
        } else {
            OrderNode* current = orderHead;

            while (current->next != nullptr) {
                current = current->next;
            }

            current->next = newNode;
        }

        cout << "New order created. Order ID: "
             << newOrder->getOrderID() << endl;
    }

    void viewOrderHistory() {
        if (checkAdminPassword() == false) return;
        if (orderHead == nullptr) {
            cout << "There is no order history.\n";
            return;
        }

        OrderNode* current = orderHead;

        while (current != nullptr) {
            current->data->displayOrder();
            current = current->next;
        }
    }

    void generateSalesReport() {
        if (checkAdminPassword() == false) return;
        SalesReport report;
        report.calculateReport(orderHead);
        report.displayReport();
    }

    // ---------- MAIN PROGRAM MENU ----------

    void displayMainMenu() {
        cout << "\n========== COFFEE SHOP SYSTEM ==========\n";
        cout << "1. Manage Menu (Administrator)\n";
        cout << "2. Manage Inventory (Administrator)\n";
        cout << "3. Take New Order\n";
        cout << "4. View Order History (Administrator)\n";
        cout << "5. Manage Staff (Administrator)\n";
        cout << "6. Sales Report (Administrator)\n";
        cout << "7. Change Administrator Password\n";
        cout << "8. Exit\n";
        cout << "========================================\n";
    }

    // CSV loading and saving will be designed in a later phase.
};
