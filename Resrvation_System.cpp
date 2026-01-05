#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
using namespace std;

const int FLOORS = 5;
const int ROOMS = 6;
int hotel[FLOORS][ROOMS] = {0};

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void saveToFile() {
    ofstream out("hotel.txt");
    for (int i = 0; i < FLOORS; i++) {
        for (int j = 0; j < ROOMS; j++)
            out << hotel[i][j] << " ";
        out << endl;
    }
    out.close();
}

void loadFromFile() {
    ifstream in("hotel.txt");
    if (!in) return;
    for (int i = 0; i < FLOORS; i++)
        for (int j = 0; j < ROOMS; j++)
            in >> hotel[i][j];
    in.close();
}

void displayRooms() {
    setColor(11);
    cout << endl << left << setw(30) << "ROOM STATUS" << endl;
    cout << "+--------+------+------+------+------+------+------+" << endl;
    cout << "| Floor  |  1   |  2   |  3   |  4   |  5   |  6   |" << endl;
    cout << "+--------+------+------+------+------+------+------+" << endl;

    for (int i = 0; i < FLOORS; i++) {
        cout << "| " << setw(6) << left << (i + 1) << " |";
        for (int j = 0; j < ROOMS; j++)
            cout << "  " << setw(3) << hotel[i][j] << " |";
        cout << endl;
    }
    cout << "+--------+------+------+------+------+------+------+" << endl;
    setColor(15);
}

void menu() {
    cout << endl;
    cout << "+-------------------------------+" << endl;
    cout << "|          HOTEL MENU          |" << endl;
    cout << "+-------------------------------+" << endl;
    cout << "| 1. Display Rooms             |" << endl;
    cout << "| 2. Reserve Room              |" << endl;
    cout << "| 3. Cancel Reservation        |" << endl;
    cout << "| 4. Check Available Rooms     |" << endl;
    cout << "| 5. Count Room Types          |" << endl;
    cout << "| 6. Show Fully Booked Floors  |" << endl;
    cout << "| 7. Exit                      |" << endl;
    cout << "+-------------------------------+" << endl;
    cout << "Enter Choice: ";
}

void reserveRoom() {
    setColor(10);
    int f, r;
    cout << endl << "Enter Floor (1-5): ";
    cin >> f;
    cout << "Enter Room  (1-6): ";
    cin >> r;

    if (f < 1 || f > 5 || r < 1 || r > 6)
        cout << endl << "Invalid Input!" << endl;
    else if (hotel[f-1][r-1] == 0) {
        hotel[f-1][r-1] = 1;
        cout << endl << "Room Reserved Successfully!" << endl;
        saveToFile();
    } else
        cout << endl << "Room Already Reserved!" << endl;

    setColor(15);
}

void cancelReservation() {
    setColor(14);
    int f, r;
    cout << endl << "Enter Floor (1-5): ";
    cin >> f;
    cout << "Enter Room  (1-6): ";
    cin >> r;

    if (hotel[f-1][r-1] == 1) {
        hotel[f-1][r-1] = 0;
        cout << endl << "Reservation Cancelled." << endl;
        saveToFile();
    } else
        cout << endl << "Room is Already Empty." << endl;

    setColor(15);
}

void availableRooms() {
    setColor(9);
    int count = 0;
    for (int i = 0; i < FLOORS; i++)
        for (int j = 0; j < ROOMS; j++)
            if (hotel[i][j] == 0) count++;

    cout << endl << "Available Rooms: " << count << endl;
    setColor(15);
}

void countRoomTypes() {
    setColor(13);
    int single = 0, dbl = 0;
    for (int i = 0; i < FLOORS; i++)
        for (int j = 0; j < ROOMS; j++)
            if (hotel[i][j] == 0)
                (j < 3 ? single : dbl)++;

    cout << endl << "Single Rooms Available: " << single << endl;
    cout << "Double Rooms Available: " << dbl << endl;
    setColor(15);
}

void fullFloors() {
    setColor(12);
    bool found = false;
    cout << endl << "Fully Booked Floors: ";
    for (int i = 0; i < FLOORS; i++) {
        int c = 0;
        for (int j = 0; j < ROOMS; j++)
            if (hotel[i][j] == 1) c++;
        if (c == ROOMS) {
            cout << i+1 << " ";
            found = true;
        }
    }
    if (!found) cout << "None";
    cout << endl;
    setColor(15);
}

int main() {
    setColor(11);
    cout << endl << "WELCOME TO HOTEL RESERVATION SYSTEM" << endl;

    loadFromFile();
    int choice;

    do {
        setColor(15);
        menu();
        cin >> choice;

        switch (choice) {
            case 1: displayRooms(); break;
            case 2: reserveRoom(); break;
            case 3: cancelReservation(); break;
            case 4: availableRooms(); break;
            case 5: countRoomTypes(); break;
            case 6: fullFloors(); break;
            case 7:
                setColor(10);
                cout << endl << "Thank you for using the system!" << endl;
                break;
            default:
                setColor(12);
                cout << endl << "Invalid Choice!" << endl;
        }

    } while (choice != 7);

    setColor(15);
    return 0;
}
