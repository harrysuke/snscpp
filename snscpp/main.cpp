// snscpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdlib.h>
#include <iostream>
#include <string>
#include "mysql_connection.h"
//#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;
using namespace sql;

const string server = "tcp://localhost:3306";
const string username = "root";
const string password = "";
const string database = "tbpsns";

void readAllVEP(Connection* conn) {
    try {
        Statement* stmt = conn->createStatement();
        ResultSet* rs = stmt->executeQuery("SELECT * FROM vep");

        while (rs->next()) {
            cout << "NRIC/Passport No: " << rs->getString("NRICPassportNo") << endl;
            cout << "Name: " << rs->getString("Name") << endl;
            cout << "Company name: " << rs->getString("CompanyName") << endl;
        }
        delete rs;
        delete stmt;
    }
    catch (SQLException &e) {
        cout << e.what() << endl;
    }
}

void createVEP(Connection* conn) {
    try {
        string NRICPassportNo, Name, CompanyName, VehicleNo, ContactNo, sql;

        //USER INPUT
        cout << "Enter NRIC/Passport number: ";
        getline(cin, NRICPassportNo);

        cout << "Enter name:";
        getline(cin, Name);

        cout << "Enter company name:";
        getline(cin, CompanyName);

        cout << "Enter vehicle number:";
        getline(cin, VehicleNo);

        cout << "Enter contact number:";
        getline(cin, ContactNo);

        sql = "INSERT INTO vep (NRICPassportNo, Name, CompanyName, VehicleNo, ContactNo) VALUES (?,?,?,?,?) ";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setString(1, NRICPassportNo);
        pstmt->setString(2, Name);
        pstmt->setString(3, CompanyName);
        pstmt->setString(4, VehicleNo);
        pstmt->setString(5, ContactNo);
        pstmt->executeUpdate();

        delete pstmt;
    }
    catch (SQLException &e) {
        cout << e.what() << endl;
    }
}

void updateVEP(Connection* conn) {
    try {
        int id;

        cout << "Enter the ID of the record to update:";
        cin >> id;
        cin.ignore();

        string NRICPassportNo, Name, CompanyName, VehicleNo, ContactNo, sql;

        //USER INPUT
        cout << "Enter NRIC/Passport number: ";
        getline(cin, NRICPassportNo);

        cout << "Enter name:";
        getline(cin, Name);

        cout << "Enter company name:";
        getline(cin, CompanyName);

        cout << "Enter vehicle number:";
        getline(cin, VehicleNo);

        cout << "Enter contact number:";
        getline(cin, ContactNo);

        sql = "UPDATE vep SET NRICPassportNo=?, Name=?, CompanyName=?, VehicleNo=?, ContactNo=? WHERE id=?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);

        pstmt->setString(1, NRICPassportNo);
        pstmt->setString(2, Name);
        pstmt->setString(3, CompanyName);
        pstmt->setString(4, VehicleNo);
        pstmt->setString(5, ContactNo);
        pstmt->setInt(6, id);
        pstmt->executeUpdate();

        delete pstmt;
    }
    catch (SQLException &e) {
        cout << e.what() << endl;
    }
}

void searchVEP(Connection* conn) {
    try {
        string keyword,sql;
        cout << "Enter keyword to search:";
        getline(cin, keyword);

        sql = "SELECT * FROM vep WHERE Name LIKE ?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setString(1, "%"+keyword+"%");

        ResultSet* rs = pstmt->executeQuery();

        while (rs->next()) {
            cout << "ID: " << rs->getInt("id") << endl;
            cout << "Name: " << rs->getString("Name") << endl;
            cout << "NRIC/Passport No: " << rs->getString("NRICPassportNo") << endl;
            cout << "Company name: " << rs->getString("CompanyName") << endl;
            cout << "Vehicle number: " << rs->getString("VehicleNo") << endl;
            cout << "Contact number: " << rs->getString("ContactNo") << endl;
        }

    }
    catch (SQLException &e) {
        cout << e.what() << endl;
    }
}

void deleteVEP(Connection* conn) {
    try {
        int id;
        string sql;

        cout << "Enter record ID to delete:";
        cin >> id;
        cin.ignore();

        sql = "DELECT FROM vep WHERE id=?";
        PreparedStatement* pstmt = conn->prepareStatement(sql);
        pstmt->setInt(1,id);

        int rowsDeleted = pstmt->executeUpdate();
        cout << rowsDeleted << " record deleted" << endl;

        delete pstmt;
    }
    catch (SQLException &e) {
        cout << e.what() << endl;
    }
}

void mainMenu() {
    cout << "Welcome to Safety and Security system" << endl;
    cout << "**********************************" << endl;
    cout << "SNS menu" << endl;
    cout << "1. Create new VEP" << endl;
    cout << "2. Update exsiting record" << endl;
    cout << "3. View all records" << endl;
    cout << "4. Search VEP record" << endl;
    cout << "5. Delete existing record" << endl;
    cout << "**********************************" << endl;
}

int main()
{
    try {
        Driver* driver = get_driver_instance();
        Connection* conn = driver->connect(server, username, password);
        conn->setSchema(database);

        int choice;
        do {
            mainMenu();
            cout << "Enter choice:";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                createVEP(conn);
                break;
            case 2:
                updateVEP(conn);
                break;
            case 3:
                readAllVEP(conn);
                break;
            case 4:
                searchVEP(conn);
                break;
            case 5:
                deleteVEP(conn);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }

        } while (choice != 0);

        delete conn;

        //std::cout << "Hello World!\n";
    }
    catch (SQLException &e) {
        cout << e.what() << endl;
    }
    return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
