#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;


// ======================================================
//                     ROOM CLASS
// ======================================================

class Room
{
private:
    int roomNo;
    string roomType;
    float price;
    bool available;

public:

    Room()
    {
        roomNo = 0;
        roomType = "Not Assigned";
        price = 0;
        available = true;
    }

    Room(int no, string type, float p)
    {
        roomNo = no;
        roomType = type;
        price = p;
        available = true;
    }

    void displayRoom()
    {
        cout << left
             << setw(10) << roomNo
             << setw(15) << roomType
             << setw(12) << price
             << setw(15)
             << (available ? "Available" : "Booked")
             << endl;
    }

    void setStatus(bool status)
    {
        available = status;
    }

    bool isAvailable()
    {
        return available;
    }

    int getRoomNo()
    {
        return roomNo;
    }

    float getPrice()
    {
        return price;
    }

    string getRoomType()
    {
        return roomType;
    }
};


// ======================================================
//                   CUSTOMER CLASS
// ======================================================

class Customer
{
private:
    int customerId;
    string name;
    string mobile;
    string address;

public:

    Customer()
    {
        customerId = 0;
        name = "";
        mobile = "";
        address = "";
    }

    Customer(int id, string n, string m, string a)
    {
        customerId = id;
        name = n;
        mobile = m;
        address = a;
    }

    void displayCustomer()
    {
        cout << "\n---------- CUSTOMER DETAILS ----------\n";
        cout << "Customer ID : " << customerId << endl;
        cout << "Name        : " << name << endl;
        cout << "Mobile      : " << mobile << endl;
        cout << "Address     : " << address << endl;
    }

    string getName()
    {
        return name;
    }

    string getMobile()
    {
        return mobile;
    }

    string getAddress()
    {
        return address;
    }

    int getId()
    {
        return customerId;
    }
};


// ======================================================
//                  RESERVATION CLASS
// ======================================================

class Reservation
{
private:
    int bookingId;
    Customer customer;
    int roomNo;
    string roomType;
    float pricePerDay;
    int days;
    float totalAmount;
    bool active;

public:

    Reservation()
    {
        bookingId = 0;
        roomNo = 0;
        roomType = "";
        pricePerDay = 0;
        days = 0;
        totalAmount = 0;
        active = false;
    }

    void makeReservation(int id, Customer c, Room &room, int d)
    {
        bookingId = id;
        customer = c;

        roomNo = room.getRoomNo();
        roomType = room.getRoomType();
        pricePerDay = room.getPrice();

        days = d;
        totalAmount = pricePerDay * days;

        active = true;

        room.setStatus(false);
    }

    int getBookingId()
    {
        return bookingId;
    }

    int getRoomNo()
    {
        return roomNo;
    }

    float getTotalAmount()
    {
        return totalAmount;
    }

    float getPricePerDay()
    {
        return pricePerDay;
    }

    int getDays()
    {
        return days;
    }

    string getCustomerName()
    {
        return customer.getName();
    }

    string getCustomerMobile()
    {
        return customer.getMobile();
    }

    string getCustomerAddress()
    {
        return customer.getAddress();
    }

    string getRoomType()
    {
        return roomType;
    }

    bool isActive()
    {
        return active;
    }

    void cancel()
    {
        active = false;
    }

    void displayReservation()
    {
        if(!active)
            return;

        cout << "\n========================================\n";
        cout << "          RESERVATION DETAILS\n";
        cout << "========================================\n";

        cout << "Booking ID   : " << bookingId << endl;
        cout << "Customer     : " << customer.getName() << endl;
        cout << "Mobile       : " << customer.getMobile() << endl;
        cout << "Room No.     : " << roomNo << endl;
        cout << "Room Type    : " << roomType << endl;
        cout << "Price/Day    : Rs. " << pricePerDay << endl;
        cout << "Days         : " << days << endl;
        cout << "Total Amount : Rs. " << totalAmount << endl;

        cout << "========================================\n";
    }

    // ==================================================
    //              SAVE DATA TO FILE
    // ==================================================

    void saveToFile()
    {
        ofstream file;

        file.open("reservations.txt", ios::app);

        if(file.is_open())
        {
            file << bookingId << endl;
            file << customer.getId() << endl;
            file << customer.getName() << endl;
            file << customer.getMobile() << endl;
            file << customer.getAddress() << endl;
            file << roomNo << endl;
            file << roomType << endl;
            file << pricePerDay << endl;
            file << days << endl;
            file << totalAmount << endl;
            file << "------------------------" << endl;

            file.close();

            cout << "\nBooking data saved to file successfully!\n";
        }
        else
        {
            cout << "\nError opening file!\n";
        }
    }
};


// ======================================================
//                DISPLAY ALL ROOMS
// ======================================================

void displayAllRooms(Room rooms[], int size)
{
    cout << "\n====================================================\n";
    cout << "                    ROOM DETAILS\n";
    cout << "====================================================\n";

    cout << left
         << setw(10) << "Room No."
         << setw(15) << "Room Type"
         << setw(12) << "Price"
         << setw(15) << "Status"
         << endl;

    cout << "----------------------------------------------------\n";

    for(int i = 0; i < size; i++)
    {
        rooms[i].displayRoom();
    }
}


// ======================================================
//             READ FILE - SEQUENTIAL ACCESS
// ======================================================

void readReservationFile()
{
    ifstream file;

    file.open("reservations.txt");

    if(!file.is_open())
    {
        cout << "\nNo reservation file found!\n";
        return;
    }

    string line;

    cout << "\n==============================================\n";
    cout << "        SAVED RESERVATION FILE DATA\n";
    cout << "==============================================\n";

    while(getline(file, line))
    {
        cout << line << endl;
    }

    file.close();

    cout << "==============================================\n";
}


// ======================================================
//                       MAIN
// ======================================================

int main()
{
    Room rooms[5] =
    {
        Room(101, "Single", 1000),
        Room(102, "Double", 1500),
        Room(103, "Deluxe", 2000),
        Room(104, "Suite", 3000),
        Room(105, "Deluxe", 2000)
    };

    Reservation reservations[10];

    int reservationCount = 0;
    int bookingCounter = 1001;
    int choice;


    // ==================================================
    //                    MAIN MENU
    // ==================================================

    do
    {
        cout << "\n\n";
        cout << "====================================================\n";
        cout << "          HOTEL ROOM RESERVATION SYSTEM\n";
        cout << "====================================================\n";

        cout << "1. Display All Rooms\n";
        cout << "2. Book Room\n";
        cout << "3. View Reservations\n";
        cout << "4. Search Reservation\n";
        cout << "5. Cancel Reservation\n";
        cout << "6. Generate Bill\n";
        cout << "7. Read Saved File\n";
        cout << "8. Exit\n";

        cout << "----------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;


        switch(choice)
        {

            // ==========================================
            //             DISPLAY ROOMS
            // ==========================================

            case 1:
            {
                displayAllRooms(rooms, 5);
                break;
            }


            // ==========================================
            //                 BOOK ROOM
            // ==========================================

            case 2:
            {
                if(reservationCount >= 10)
                {
                    cout << "\nReservation limit reached!\n";
                    break;
                }

                int id;
                string name, mobile, address;
                int selectedRoom, days;

                cout << "\n========== BOOK ROOM ==========\n";

                cout << "Enter Customer ID: ";
                cin >> id;

                cin.ignore();

                cout << "Enter Customer Name: ";
                getline(cin, name);

                cout << "Enter Mobile Number: ";
                getline(cin, mobile);

                cout << "Enter Address: ";
                getline(cin, address);

                Customer c(id, name, mobile, address);

                displayAllRooms(rooms, 5);

                cout << "\nEnter Room Number: ";
                cin >> selectedRoom;

                cout << "Enter Number of Days: ";
                cin >> days;

                bool found = false;

                for(int i = 0; i < 5; i++)
                {
                    if(rooms[i].getRoomNo() == selectedRoom)
                    {
                        found = true;

                        if(rooms[i].isAvailable())
                        {
                            reservations[reservationCount].makeReservation(
                                bookingCounter,
                                c,
                                rooms[i],
                                days
                            );

                            cout << "\nRoom booked successfully!\n";

                            cout << "Booking ID: "
                                 << bookingCounter << endl;

                            reservations[reservationCount]
                                .displayReservation();

                            // SAVE BOOKING TO FILE
                            reservations[reservationCount]
                                .saveToFile();

                            reservationCount++;
                            bookingCounter++;
                        }
                        else
                        {
                            cout << "\nSorry! Room is already booked.\n";
                        }

                        break;
                    }
                }

                if(!found)
                {
                    cout << "\nInvalid Room Number!\n";
                }

                break;
            }


            // ==========================================
            //             VIEW RESERVATIONS
            // ==========================================

            case 3:
            {
                cout << "\n========== ALL RESERVATIONS ==========\n";

                bool found = false;

                for(int i = 0; i < reservationCount; i++)
                {
                    if(reservations[i].isActive())
                    {
                        reservations[i].displayReservation();
                        found = true;
                    }
                }

                if(!found)
                {
                    cout << "\nNo active reservations found.\n";
                }

                break;
            }


            // ==========================================
            //             SEARCH RESERVATION
            // ==========================================

            case 4:
            {
                int id;
                bool found = false;

                cout << "\nEnter Booking ID to search: ";
                cin >> id;

                for(int i = 0; i < reservationCount; i++)
                {
                    if(reservations[i].getBookingId() == id &&
                       reservations[i].isActive())
                    {
                        reservations[i].displayReservation();

                        found = true;
                        break;
                    }
                }

                if(!found)
                {
                    cout << "\nReservation not found!\n";
                }

                break;
            }


            // ==========================================
            //             CANCEL RESERVATION
            // ==========================================

            case 5:
            {
                int id;
                bool found = false;

                cout << "\nEnter Booking ID to cancel: ";
                cin >> id;

                for(int i = 0; i < reservationCount; i++)
                {
                    if(reservations[i].getBookingId() == id &&
                       reservations[i].isActive())
                    {
                        int roomNo =
                            reservations[i].getRoomNo();

                        reservations[i].cancel();

                        for(int j = 0; j < 5; j++)
                        {
                            if(rooms[j].getRoomNo() == roomNo)
                            {
                                rooms[j].setStatus(true);
                                break;
                            }
                        }

                        cout << "\nReservation cancelled successfully!\n";

                        found = true;
                        break;
                    }
                }

                if(!found)
                {
                    cout << "\nReservation not found!\n";
                }

                break;
            }


            // ==========================================
            //              GENERATE BILL
            // ==========================================

            case 6:
            {
                int id;
                bool found = false;

                cout << "\n========== BILL GENERATION ==========\n";

                cout << "Enter Booking ID: ";
                cin >> id;

                for(int i = 0; i < reservationCount; i++)
                {
                    if(reservations[i].getBookingId() == id &&
                       reservations[i].isActive())
                    {
                        float roomAmount =
                            reservations[i].getTotalAmount();

                        float gst = roomAmount * 0.05;

                        float grandTotal =
                            roomAmount + gst;

                        cout << fixed << setprecision(2);

                        cout << "\n";
                        cout << "==============================================\n";
                        cout << "               HOTEL ROOM BILL\n";
                        cout << "==============================================\n";

                        cout << "Booking ID       : "
                             << reservations[i].getBookingId()
                             << endl;

                        cout << "Customer Name    : "
                             << reservations[i].getCustomerName()
                             << endl;

                        cout << "Mobile Number    : "
                             << reservations[i].getCustomerMobile()
                             << endl;

                        cout << "Room Type        : "
                             << reservations[i].getRoomType()
                             << endl;

                        cout << "Price Per Day    : Rs. "
                             << reservations[i].getPricePerDay()
                             << endl;

                        cout << "Number of Days   : "
                             << reservations[i].getDays()
                             << endl;

                        cout << "----------------------------------------------\n";

                        cout << "Room Amount      : Rs. "
                             << roomAmount << endl;

                        cout << "GST (5%)         : Rs. "
                             << gst << endl;

                        cout << "----------------------------------------------\n";

                        cout << "GRAND TOTAL      : Rs. "
                             << grandTotal << endl;

                        cout << "==============================================\n";
                        cout << "          Thank You! Visit Again!\n";
                        cout << "==============================================\n";

                        found = true;
                        break;
                    }
                }

                if(!found)
                {
                    cout << "\nReservation not found!\n";
                }

                break;
            }


            // ==========================================
            //             READ SAVED FILE
            // ==========================================

            case 7:
            {
                readReservationFile();
                break;
            }


            // ==========================================
            //                    EXIT
            // ==========================================

            case 8:
            {
                cout << "\nThank you for using Hotel Reservation System!\n";
                cout << "Have a nice day!\n";
                break;
            }


            default:
            {
                cout << "\nInvalid choice! Please try again.\n";
            }

        }

    } while(choice != 8);


    return 0;
}