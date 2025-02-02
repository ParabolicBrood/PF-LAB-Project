#include <iostream>
#include <string>
using namespace std;

int max_products = 20;
string admin_pin = "1234";
string buyer_pin = "5678";

struct product {
    string name;
    double price;
    int quantity;
};

void display_catalog(const product items[], int count) {
    cout << "\nProduct Catalog:\n";
    cout << "Index\tName\t\tPrice\tQuantity\n";
    for (int i = 0; i < count; ++i) {
        cout << i + 1 << "\t" << items[i].name << "\t$" << items[i].price << "\t" << items[i].quantity << endl;
    }
}

void add_to_cart(product items[], product cart[], int& cart_count, int item_index) {
    if (item_index >= 0 && item_index < max_products && items[item_index].quantity > 0) {
        cart[cart_count] = items[item_index];
        items[item_index].quantity--;
        cout << items[item_index].name << " added to cart.\n";
        cart_count++;
    } else {
        cout << "Invalid product or insufficient quantity.\n";
    }
}

double calculate_total(const product cart[], int cart_count) {
    double total = 0.0;
    for (int i = 0; i < cart_count; ++i) {
        total += cart[i].price;
    }
    return total;
}

int is_owner(const string& pin) {
    return pin == admin_pin;
}

int is_buyer(const string& pin) {
    return pin == buyer_pin;
}

void add_product(product items[], int& count) {
    if (count < max_products) {
        cout << "Enter product name: ";
        cin.ignore();
        getline(cin, items[count].name);
        cout << "Enter product price: ";
        cin >> items[count].price;
        cout << "Enter product quantity: ";
        cin >> items[count].quantity;
        count++;
        cout << "Product added successfully!\n";
    } else {
        cout << "Maximum number of products reached.\n";
    }
}

void manage_inventory(product items[], int count) {
    int choice;
    do {
        cout << "\nInventory Management:\n";
        cout << "1. View Catalog\n2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                display_catalog(items, count);
                break;
            case 2:
                cout << "Exiting Inventory Management.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 2);
}

void display_payment_message(double total_cost) {
    if (total_cost > 0) {
        cout << "\nCurrently, we only support cash payment.\n";
    } else {
        cout << "\nThank you for visiting! Have a good day!\n";
    }
}

int main() {
    product items[max_products] = {
        {"Janan Perfume", 34.99, 5},
        {"FruitZips", 30, 500},
        {"Herbal Berberine Tea", 24.99, 1100}
    };
    int count = 3;
    product cart[max_products];
    int cart_count = 0;
    int choice, item_index;
    string user_pin;

    while (true) {
        cout << "Enter your PIN (Different for Buyer / Admin Access: ";
        cin >> user_pin;
        if (user_pin == "exit") return 0;
        if (is_owner(user_pin) || is_buyer(user_pin)) break;
        cout << "Invalid PIN. Try again.\n";
    }

    if (is_owner(user_pin)) {
        cout << "Welcome, Admin!\n";
        while (true) {
            cout << "\n1. Add Product\n2. Manage Inventory\n3. View Catalog\n4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    add_product(items, count);
                    break;
                case 2:
                    manage_inventory(items, count);
                    break;
                case 3:
                    display_catalog(items, count);
                    break;
                case 4:
                    cout << "Exiting Admin Mode.\n";
                    return 0;
                default:
                    cout << "Invalid choice.\n";
            }
        }
    } else {
        cout << "Welcome, Buyer!\n";
        do {
            display_catalog(items, count);
            cout << "\nSelect a product (enter index, 0 to exit): ";
            cin >> choice;
            if (choice != 0) {
                item_index = choice - 1;
                add_to_cart(items, cart, cart_count, item_index);
            }
        } while (choice != 0);

        cout << "\nYour Cart:\n";
        display_catalog(cart, cart_count);
        double total_cost = calculate_total(cart, cart_count);
        cout << "\nTotal Cost: $" << total_cost << endl;
        display_payment_message(total_cost);
    }
    return 0;
}
