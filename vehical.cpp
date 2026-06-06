#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>
using namespace std;

// Base Class
class User {
private:
    string name, email, phone;

public:
    User() {}

    User(string n, string e, string p) {
        name = n;
        email = e;
        phone = p;
    }

    string getName() { return name; }
    string getEmail() { return email; }
    string getPhone() { return phone; }

    void setName(string n) { name = n; }
    void setEmail(string e) { email = e; }
    void setPhone(string p) { phone = p; }
};

// Derived Class
class VehicleOwner : public User {
public:
    VehicleOwner() {}

    VehicleOwner(string n, string e, string p)
        : User(n, e, p) {}
};

// Vehicle Class
class Vehicle {
private:
    string plateNumber, vehicleType;
    int year;
    VehicleOwner owner;

public:
    Vehicle() {}

    Vehicle(string plate, string type, int y, VehicleOwner o) {
        plateNumber = plate;
        vehicleType = type;
        year = y;
        owner = o;
    }

    string getPlateNumber() { return plateNumber; }
    string getVehicleType() { return vehicleType; }
    int getYear() { return year; }
    VehicleOwner getOwner() { return owner; }
};

// Validation Functions
bool validateEmail(string email) {
    return email.find('@') != string::npos &&
           email.find('.') != string::npos &&
           email.front() != '@' &&
           email.back() != '.';
}

bool validatePhone(string phone) {
    if (phone.length() != 13) return false;
    if (phone.substr(0, 4) != "+250") return false;

    for (int i = 4; i < 13; i++) {
        if (!isdigit(phone[i]))
            return false;
    }
    return true;
}

bool validatePlate(string plate) {
    regex pattern("[A-Z]{3}[0-9]{3}[A-Z]");
    return regex_match(plate, pattern);
}

// Add Record
void addRecord() {
    string plate, type, ownerName, email, phone;
    int year;

    do {
        cout << "Plate Number: ";
        cin >> plate;
    } while (!validatePlate(plate));

    cout << "Vehicle Type: ";
    cin >> type;

    cout << "Year: ";
    cin >> year;

    cin.ignore();

    cout << "Owner Name: ";
    getline(cin, ownerName);

    do {
        cout << "Email: ";
        getline(cin, email);
    } while (!validateEmail(email));

    do {
        cout << "Phone (+250xxxxxxxxx): ";
        getline(cin, phone);
    } while (!validatePhone(phone));

    ofstream file("records.txt", ios::app);
    file << plate << ","
         << type << ","
         << year << ","
         << ownerName << ","
         << email << ","
         << phone << endl;

    file.close();

    cout << "Record saved successfully.\n";
}

// Search Record
void searchVehicle() {
    string searchPlate, line;

    cout << "Enter Plate Number: ";
    cin >> searchPlate;

    ifstream file("records.txt");
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);

        string plate, type, yearStr, owner, email, phone;

        getline(ss, plate, ',');
        getline(ss, type, ',');
        getline(ss, yearStr, ',');
        getline(ss, owner, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');

        if (plate == searchPlate) {
            cout << "\nVehicle Found\n";
            cout << "Plate: " << plate << endl;
            cout << "Type: " << type << endl;
            cout << "Year: " << yearStr << endl;
            cout << "Owner: " << owner << endl;
            cout << "Email: " << email << endl;
            cout << "Phone: " << phone << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Vehicle does not exist in the system.\n";

    file.close();
}

// Display All Records
void displayRecords() {
    ifstream file("records.txt");
    string line;

    cout << left
         << setw(12) << "Plate"
         << setw(15) << "Type"
         << setw(8) << "Year"
         << setw(20) << "Owner"
         << setw(25) << "Email"
         << setw(15) << "Phone" << endl;

    cout << string(95, '-') << endl;

    while (getline(file, line)) {
        stringstream ss(line);

        string plate, type, year, owner, email, phone;

        getline(ss, plate, ',');
        getline(ss, type, ',');
        getline(ss, year, ',');
        getline(ss, owner, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');

        cout << left
             << setw(12) << plate
             << setw(15) << type
             << setw(8) << year
             << setw(20) << owner
             << setw(25) << email
             << setw(15) << phone
             << endl;
    }

    file.close();
}

// Main Function
int main() {
    int choice;

    do {
        cout << "\n===== Vehicle Registration System =====\n";
        cout << "1. Add Record\n";
        cout << "2. Search Vehicle\n";
        cout << "3. Display All Records\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addRecord();
            break;
        case 2:
            searchVehicle();
            break;
        case 3:
            displayRecords();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid Choice\n";
        }

    } while (choice != 4);

    return 0;
}
