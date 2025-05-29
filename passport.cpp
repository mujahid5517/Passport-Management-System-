#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <regex>
#include <ctime>
using namespace std;

struct Passport {
    string id;
    string fullname;
    string dob;
    string nationality;
    string phoneNumber;
    string gender;
    string createdDate;
    string appointmentDate;
    string payment;
    string paymentStatus;
    string passType;
    Passport* next;
};

Passport* head = nullptr;
const string fileName = "passport.csv";

void createPassport();
void retrievePassports();
void updatePassport();
void deletePassport();
void searchPassport();
void sortPassports();
void saveToFile();
void loadFromFile();
void freeList();
bool isValidDate(const string& date);
bool isOver18(const string& dob);
bool isFutureDate(const string& date);
bool isAlphanumeric(const string& str);
bool isLettersOnly(const string& str);
bool isNumbersOnly(const string& str);
bool isUniqueID(const string& id, const string& excludeID = "");
bool idExists(const string& id);
string getCurrentDate();
string getDateTwoDaysLater(const string& date);

bool isValidDate(const string& date) {
    regex datePattern("\\d{4}-\\d{2}-\\d{2}");
    if (!regex_match(date, datePattern)) return false;

    int year, month, day;
    istringstream iss(date);
    char dash1, dash2;
    iss >> year >> dash1 >> month >> dash2 >> day;
    if (iss.fail() || dash1 != '-' || dash2 != '-') return false;

    if (month < 1 || month > 12 || day < 1 || day > 31) return false;
    return true;
}

bool isOver18(const string& dob) {
    time_t now = time(nullptr);
    tm* current = localtime(&now);
    int currYear = current->tm_year + 1900;
    int currMonth = current->tm_mon + 1;
    int currDay = current->tm_mday;

    int birthYear, birthMonth, birthDay;
    istringstream iss(dob);
    char dash1, dash2;
    iss >> birthYear >> dash1 >> birthMonth >> dash2 >> birthDay;
    if (iss.fail() || dash1 != '-' || dash2 != '-') return false;

    int age = currYear - birthYear;
    if (currMonth < birthMonth || (currMonth == birthMonth && currDay < birthDay)) {
        age--;
    }
    return age >= 18;
}

bool isFutureDate(const string& date) {
    if (!isValidDate(date)) return false;

    time_t now = time(nullptr);
    tm* current = localtime(&now);
    int currYear = current->tm_year + 1900;
    int currMonth = current->tm_mon + 1;
    int currDay = current->tm_mday;

    int inputYear, inputMonth, inputDay;
    istringstream iss(date);
    char dash1, dash2;
    iss >> inputYear >> dash1 >> inputMonth >> dash2 >> inputDay;
    if (iss.fail() || dash1 != '-' || dash2 != '-') return false;

    if (inputYear > currYear) return true;
    if (inputYear == currYear && inputMonth > currMonth) return true;
    if (inputYear == currYear && inputMonth == currMonth && inputDay >= currDay) return true;
    return false;
}

bool isAlphanumeric(const string& str) {
    regex pattern("^[a-zA-Z0-9]+$");
    return regex_match(str, pattern);
}

bool isLettersOnly(const string& str) {
    regex pattern("^[a-zA-Z ]+$");
    return regex_match(str, pattern);
}

bool isNumbersOnly(const string& str) {
    regex pattern("^[0-9]+$");
    return regex_match(str, pattern);
}

bool isUniqueID(const string& id, const string& excludeID) {
    Passport* temp = head;
    while (temp != nullptr) {
        if (temp->id == id && temp->id != excludeID) {
            return false;
        }
        temp = temp->next;
    }
    return true;
}

bool idExists(const string& id) {
    Passport* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

string getCurrentDate() {
    time_t now = time(nullptr);
    tm* current = localtime(&now);
    stringstream ss;
    ss << setfill('0') << setw(4) << current->tm_year + 1900 << "-"
       << setw(2) << current->tm_mon + 1 << "-"
       << setw(2) << current->tm_mday;
    return ss.str();
}

string getDateTwoDaysLater(const string& date) {
    int year, month, day;
    istringstream iss(date);
    char dash1, dash2;
    iss >> year >> dash1 >> month >> dash2 >> day;
    if (iss.fail() || dash1 != '-' || dash2 != '-') return "";

    day += 2;
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28)) {
            day -= (isLeap ? 29 : 28);
            month++;
        }
    } else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        day -= 30;
        month++;
    } else if (day > 31) {
        day -= 31;
        month++;
    }
    if (month > 12) {
        month = 1;
        year++;
    }

    stringstream ss;
    ss << setfill('0') << setw(4) << year << "-"
       << setw(2) << month << "-"
       << setw(2) << day;
    return ss.str();
}
void createPassport() {
    
}
void retrievePassports() {
    if (head == nullptr) {
        cout << "No passports found.\n";
        return;
    }
    Passport* temp = head;
    cout << "\n-- List of Passports --\n";
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Name: " << temp->fullname
             << ", DOB: " << temp->dob << ", Nationality: " << temp->nationality
             << ", Phone: " << temp->phoneNumber << ", Gender: " << temp->gender
             << ", Created: " << temp->createdDate << ", Appointment: " << temp->appointmentDate
             << ", Payment: " << temp->payment << ", Pass Type: " << temp->passType << "\n";
        temp = temp->next;
    }

}
void updatePassport() {

}
void deletePassport() {
 int deleteChoice;
    cout << "Delete Options:\n1. Delete by ID\n2. Delete All\nEnter choice (1 or 2): ";
    cin >> deleteChoice;
    cin.ignore();

    if (deleteChoice == 1) {
        string id;
        cout << "Enter Passport ID to delete: ";
        getline(cin, id);

        Passport* temp = head;
        Passport* prev = nullptr;
        while (temp != nullptr) {
            if (temp->id == id) {
                if (prev == nullptr) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                saveToFile();
                cout << "Passport deleted successfully!\n";
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Passport not found.\n";
    } else if (deleteChoice == 2) {
        freeList();
        saveToFile();
        cout << "All passports deleted successfully!\n";
    } else {
        cout << "Invalid choice!\n";
    }
}
void searchPassport(){

}
void sortPassports(){

}
void saveToFile() {

}
void loadFromFile() {

}
void freeList() {
    
}
int main() {
    loadFromFile();
    string id, fullname, dob, nationality, phoneNumber, gender, createdDate, appointmentDate, payment, paymentStatus, passType;
    int choice;

    while (true) {
        cout << "\nPassport Management System\n";
        cout << "1. Create Passport\n";
        cout << "2. Retrieve Passports\n";
        cout << "3. Update Passport\n";
        cout << "4. Delete Passport\n";
        cout << "5. Search Passport\n";
        cout << "6. Sort Passports\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                createPassport();
                break;
            case 2:
                retrievePassports();
                break;
            case 3:
                updatePassport();
                break;
            case 4:
                deletePassport();
                break;
            case 5:
               searchPassport();
                break;
            case 6:
                sortPassports();
                break;
            case 0:
                freeList();
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
    return 0;
}