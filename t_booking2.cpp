#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

int main()
{
    int choice, choiceone, choicetwo, day, month, year, seat;
    int ticketID, win, meal, tempticketID, flightno;
    double amt = 0;
    int clas;
    string pname, to, from; // passenger name

    time_t now = std::time(0);
    tm *ltm = localtime(&now);

    while (choiceone != 4)
    {
        cout << "\n=====================================================" << endl;
        cout << "            WELCOME TO TRAVEL AGENCY" << endl;
        cout << "=====================================================" << endl;
        cout << "\n1. Flight Booking System" << endl;
        cout << "2. Bus Booking System" << endl;
        cout << "3. Train Booking System" << endl;
        cout << "4. Exit" << endl;
        cout << "=====================================================" << endl;
        cout << "\nEnter your choice: ";
        cin >> choiceone;
        if (choiceone != 4)
        {
            cout << "\nEnter Departure City/State: ";
            cin >> from;
            cout << "Enter Arrival City/State: ";
            cin >> to;
        }

        if (!from.empty())
            from[0] = toupper(from[0]);
        if (!to.empty())
            to[0] = toupper(to[0]);

        switch (choiceone)
        {
        case 1:
        {

            cout << "\n=====================================================" << endl;
            cout << "       WELCOME TO FLIGHT BOOKING SYSTEM" << endl;
            cout << "=====================================================" << endl;
            cout << "\nPlease enter your travel details below " << endl;

            while (choice != 5)
            {

                cout << "=====================================================" << endl;
                cout << "1. Book Ticket" << endl;
                cout << "2. Cancel Ticket" << endl;
                cout << "3. Check Ticket Status" << endl;
                cout << "4. Check Available Flights" << endl;
                cout << "5. Exit" << endl;
                cout << "=====================================================" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                srand(time(0));
                ticketID = rand() % 10000; // random ticket ID

                switch (choice)
                {
                case 1:
                {
                    cout << "\n====================================================" << endl;
                    cout << "Available Flights: \n";
                    cout << "Flight Name\t   \tFlight Number \t     \t Destination\n";
                    cout << "IndiGO     \t - \t     101      \t -   \t" << from << " to " << to << "\n";
                    cout << "Air India  \t - \t     202      \t -   \t" << from << " to " << to << "\n";
                    cout << "Akasa Air  \t - \t     303      \t -   \t" << from << " to " << to << "\n";
                    cout << "====================================================" << endl;
                    cout << "Enter flight number to book: ";
                    cin >> flightno;

                    if (flightno == 101 || flightno == 202 || flightno == 303)
                    {
                        // clear buffer before getline
                        cin.ignore();
                        cout << "Enter passenger name: ";
                        getline(cin, pname); // the getline function call and add cin.ignore() to consume the leftover newline character from the input buffer.//

                        cout << "Enter date of journey DD MM YYYY: ";
                        cin >> day >> month >> year;

                        //A.I

                        // Validate that date is not in the past
                        time_t now = time(0);
                        tm *ltm = localtime(&now);

                        tm journeyDate = {};
                        journeyDate.tm_mday = day;
                        journeyDate.tm_mon = month - 1;   // months since January [0,11]
                        journeyDate.tm_year = year - 1900; // years since 1900

                        time_t journey_time = mktime(&journeyDate);

                        // compare the journey date with current date
                        if (difftime(journey_time, now) < 0)
                        {
                            cout << " Invalid date! You cannot select a past date.\n";
                            continue; // go back to menu instead of booking
                        }


                        cout << "Enter class: (1 for Economy, 2 for Business): ";
                        cin >> clas;

                        cout << "===================================================" << endl;

                        cout << "Additional Services " << endl;
                        cout << "Do you want a window seat? (1 for Yes, 2 for No): ";
                        cin >> win;

                        cout << "Do you want a meal? (1 for Yes, 2 for No): ";
                        cin >> meal;

                        cout << "How many seats do you want to book?: ";
                        cin >> seat;

                        cout << "Note: Window seat costs an additional 500 and meal costs an additional 300." << endl;
                        cout << "============================================================" << endl;

                        // Calculate amount correctly

                        if (flightno == 101)
                            amt = ((clas == 1 ? 6250 : 9450) + (win == 1 ? 500 : 0) + (meal == 1 ? 300 : 0)) * seat;
                        else if (flightno == 202)
                            amt = ((clas == 1 ? 6999 : 10200) + (win == 1 ? 500 : 0) + (meal == 1 ? 300 : 0)) * seat;
                        else if (flightno == 303)
                            amt = ((clas == 1 ? 5599 : 7599) + (win == 1 ? 500 : 0) + (meal == 1 ? 300 : 0)) * seat;

                        cout << "Ticket booked successfully!" << endl;
                        cout << "Passenger: " << pname << endl;
                        cout << "Flight No: " << flightno << "\n Class: " << (clas == 1 ? "Economy" : "Business") << endl;
                        cout << "Seats: " << seat << endl;
                        cout << "Amount: " << amt << endl;
                        cout << "Your ticket ID is " << ticketID << endl;
                        int startSeat = (rand() % (186 - seat + 1)) + 1;
                        cout << "Allocated Seats: ";
                        for (int i = 0; i < seat; i++)
                        {
                            cout << startSeat + i;
                            if (i != seat - 1)
                                cout << ", ";
                        }
                        cout << endl;

                        ofstream outFile("bookings.txt", ios::app);
                        outFile << ticketID << ","
                                << pname << ","
                                << (clas == 1 ? "Economy" : "Business") << ","
                                << flightno << ","
                                << seat << ",";
                        // write allocated seats
                        for (int i = 0; i < seat; i++)
                        {
                            outFile << (startSeat + i);
                            if (i != seat - 1)
                                outFile << " ";
                        }

                        outFile << ","
                                << day << "-" << month << "-" << year << ","
                                << 1900 + ltm->tm_year << "-"
                                << 1 + ltm->tm_mon << "-"
                                << ltm->tm_mday << " "
                                << ltm->tm_hour << ":"
                                << ltm->tm_min << ":"
                                << ltm->tm_sec << ","
                                << amt << ",Confirmed" << endl;
                        outFile.close();
                    }
                    else
                    {
                        cout << "Invalid flight number. Please try again." << endl;
                    }
                    break;
                }

                case 2:
                {
                    cout << "Enter ticket ID to cancel: "; // AI
                    cin >> ticketID;

                    ifstream inFile("bookings.txt");
                    ofstream tempFile("temp.txt");
                    string line;
                    bool found = false;

                    while (getline(inFile, line))
                    {
                        if (line.find(to_string(ticketID) + ",") == 0)
                        {
                            found = true;
                            size_t pos = line.rfind("Confirmed");
                            if (pos != string::npos)
                            {
                                line.replace(pos, 9, "Cancelled");
                            }
                        }
                        tempFile << line << endl;
                    }

                    inFile.close();
                    tempFile.close();

                    remove("bookings.txt");
                    rename("temp.txt", "bookings.txt");

                    if (found)
                        cout << "Ticket " << ticketID << " cancelled successfully." << endl;
                    else
                        cout << "Invalid ticket ID." << endl;
                    break;
                }

                case 3:
                {
                    cout << "Enter ticket ID to check status: ";
                    cin >> tempticketID;

                    ifstream inFile("bookings.txt");
                    string line;
                    bool found = false;

                    while (getline(inFile, line))
                    {
                        if (line.find(to_string(tempticketID) + ",") == 0)
                        {
                            found = true;

                            stringstream ss(line);
                            string tid, pname, cls, fno, seats, al, doj, btime, amount, status;
                            getline(ss, tid, ',');
                            getline(ss, pname, ',');
                            getline(ss, cls, ',');
                            getline(ss, fno, ',');
                            getline(ss, seats, ',');
                            getline(ss, al, ',');
                            getline(ss, doj, ',');
                            getline(ss, btime, ',');
                            getline(ss, amount, ',');
                            getline(ss, status, ',');

                            cout << "\n===== Ticket Details =====" << endl;
                            cout << "Ticket ID: " << tid << endl;
                            cout << "Passenger: " << pname << endl;
                            cout << "Class: " << cls << endl;
                            cout << "Flight No: " << fno;
                            if (fno == "101")
                                cout << " (" << from << " to " << to << ")" << endl;
                            else if (fno == "202")
                                cout << " (" << from << " to " << to << ")" << endl;
                            else if (fno == "303")
                                cout << " (" << from << " to " << to << ")" << endl;
                            else
                                cout << " (Unknown Route)" << endl;
                            cout << "Seats: " << seats << endl;
                            cout << "Allocated Seats: " << al << endl;
                            cout << "Date of Journey: " << doj << endl;
                            cout << "Booking Time: " << btime << endl;
                            cout << "Amount: " << amount << endl;
                            cout << "Status: " << status << endl;
                            break;
                        }
                    }
                    inFile.close();

                    if (!found)
                        cout << "Invalid ticket ID. Please try again." << endl;
                    break;
                }

                case 4:
                    cout << "============================================================" << endl;
                    cout << "Available Flights: \n";
                    cout << "Flight Name\t   \tFlight Number \t     \t Destination\n";
                    cout << "IndiGO     \t - \t     101      \t -   \t" << from << " to " << to << "\n";
                    cout << "Air India  \t - \t     202      \t -   \t" << from << " to " << to << "\n";
                    cout << "Akasa Air  \t - \t     303      \t -   \t" << from << " to " << to << "\n";
                    break;

                case 5:
                    cout << "Exiting..." << endl;
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        break;
        }
        case 2:
        {
            while (choice != 5)
            {
                int busno;

                cout << "=====================================================" << endl;
                cout << "1. Book Ticket" << endl;
                cout << "2. Cancel Ticket" << endl;
                cout << "3. Check Ticket Status" << endl;
                cout << "4. Check Available Buses" << endl;
                cout << "5. Exit" << endl;
                cout << "=====================================================" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                srand(time(0));
                ticketID = rand() % 10000; // random ticket ID

                switch (choice)
                {
                case 1:
                {
                    cout << "\n=============================================" << endl;
                    cout << "       WELCOME TO BUS BOOKING SYSTEM" << endl;
                    cout << "====================================================" << endl;
                    cout << "Available Buses: \n";
                    cout << "Bus Name        \t   \tBus Number \t     \t Destination\n";
                    cout << "Himalaya Travels\t - \t     101   \t -   \t" << from << " to " << to << "\n";
                    cout << "Ramu Travels    \t - \t     202   \t -   \t" << from << " to " << to << "\n";
                    cout << "Nandan Travels  \t - \t     303   \t -   \t" << from << " to " << to << "\n";
                    cout << "====================================================" << endl;
                    cout << "Enter Bus number to book: ";
                    cin >> busno;

                    if (busno == 101 || busno == 202 || busno == 303)
                    {
                        // clear buffer before getline
                        cin.ignore();
                        cout << "Enter passenger name: ";
                        getline(cin, pname); // the getline function call and add cin.ignore() to consume the leftover newline character from the input buffer.//

                        cout << "Enter date of journey DD MM YYYY: ";
                        cin >> day >> month >> year;

                         // Validate that date is not in the past
                        time_t now = time(0);
                        tm *ltm = localtime(&now);

                        tm journeyDate = {};
                        journeyDate.tm_mday = day;
                        journeyDate.tm_mon = month - 1;   // months since January [0,11]
                        journeyDate.tm_year = year - 1900; // years since 1900

                        time_t journey_time = mktime(&journeyDate);

                        // compare the journey date with current date
                        if (difftime(journey_time, now) < 0)
                        {
                            cout << " Invalid date! You cannot select a past date.\n";
                            continue; // go back to menu instead of booking
                        }

                        cout << "How many seats do you want to book?: ";
                        cin >> seat;

                        cout << "============================================================" << endl;

                        if (busno == 101)
                            amt = 6200 * seat;
                        else if (busno == 202)
                            amt = 5800 * seat;
                        else if (busno == 303)
                            amt = 5500 * seat;

                        cout << "Ticket booked successfully!" << endl;
                        cout << "Passenger: " << pname << endl;
                        cout << "Bus No: " << busno << endl;
                        cout << "Seats: " << seat << endl;
                        cout << "Amount: " << amt << endl;
                        cout << "Your ticket ID is " << ticketID << endl;

                        int startSeat = (rand() % (50 - seat + 1)) + 1;

                        cout << "Allocated Seats: ";
                        for (int i = 0; i < seat; i++)
                        {
                            cout << startSeat + i;
                            if (i != seat - 1)
                                cout << ", ";
                        }
                        cout << endl;

                        // Save booking with seat numbers
                        ofstream outFile("bookings.txt", ios::app);
                        outFile << ticketID << ","
                                << pname << ","
                                << busno << ","
                                << seat << ",";

                        // write allocated seats
                        for (int i = 0; i < seat; i++)
                        {
                            outFile << (startSeat + i);
                            if (i != seat - 1)
                                outFile << " ";
                        }

                        outFile << ","
                                << day << "-" << month << "-" << year << ","
                                << 1900 + ltm->tm_year << "-"
                                << 1 + ltm->tm_mon << "-"
                                << ltm->tm_mday << " "
                                << ltm->tm_hour << ":"
                                << ltm->tm_min << ":"
                                << ltm->tm_sec << ","
                                << amt << ",Confirmed" << endl;
                        outFile.close();
                    }
                    else
                    {
                        cout << "Invalid Bus number. Please try again." << endl;
                    }
                    break;
                }

                case 2:
                {
                    cout << "Enter ticket ID to cancel: "; // AI
                    cin >> ticketID;

                    ifstream inFile("bookings.txt");
                    ofstream tempFile("temp.txt");
                    string line;
                    bool found = false;

                    while (getline(inFile, line))
                    {
                        if (line.find(to_string(ticketID) + ",") == 0)
                        {
                            found = true;
                            size_t pos = line.rfind("Confirmed");
                            if (pos != string::npos)
                            {
                                line.replace(pos, 9, "Cancelled");
                            }
                        }
                        tempFile << line << endl;
                    }

                    inFile.close();
                    tempFile.close();

                    remove("bookings.txt");
                    rename("temp.txt", "bookings.txt");

                    if (found)
                        cout << "Ticket " << ticketID << " cancelled successfully." << endl;
                    else
                        cout << "Invalid ticket ID." << endl;
                    break;
                }

                case 3:
                {
                    cout << "Enter ticket ID to check status: ";
                    cin >> tempticketID;

                    ifstream inFile("bookings.txt");
                    string line;
                    bool found = false;

                    while (getline(inFile, line))
                    {
                        if (line.find(to_string(tempticketID) + ",") == 0)
                        {
                            found = true;

                            stringstream ss(line);
                            string tid, pname, bno, seats, al, doj, btime, amount, status;
                            getline(ss, tid, ',');
                            getline(ss, pname, ',');
                            getline(ss, bno, ',');
                            getline(ss, seats, ',');
                            getline(ss, al, ',');
                            getline(ss, doj, ',');
                            getline(ss, btime, ',');
                            getline(ss, amount, ',');
                            getline(ss, status, ',');

                            cout << "\n===== Ticket Details =====" << endl;
                            cout << "Ticket ID: " << tid << endl;
                            cout << "Passenger: " << pname << endl;
                            cout << "Bus No: " << bno;
                            if (bno == "101")
                                cout << " (" << from << " to " << to << ")" << endl;
                            else if (bno == "202")
                                cout << " (" << from << " to " << to << ")" << endl;
                            else if (bno == "303")
                                cout << " (" << from << " to " << to << ")" << endl;
                            else
                                cout << " (Unknown Route)" << endl;
                            cout << "Seats: " << seats << endl;
                            cout << "Allocated Seats: " << al << endl;
                            cout << "Date of Journey: " << doj << endl;
                            cout << "Booking Time: " << btime << endl;
                            cout << "Amount: " << amount << endl;
                            cout << "Status: " << status << endl;
                            break;
                        }
                    }
                    inFile.close();

                    if (!found)
                        cout << "Invalid ticket ID. Please try again." << endl;
                    break;
                }

                case 4:
                    cout << "====================================================" << endl;
                    cout << "Available Buses: \n";
                    cout << "Bus Name        \t   \tBus Number \t     \t Destination\n";
                    cout << "Himalaya Travels\t - \t     101   \t -   \t" << from << " to " << to << "\n";
                    cout << "Ramu Travels    \t - \t     202   \t -   \t" << from << " to " << to << "\n";
                    cout << "Nandan Travels  \t - \t     303   \t -   \t" << from << " to " << to << "\n";
                    break;

                case 5:
                    cout << "Exiting..." << endl;
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        break;
        }
        case 3:
        {
            while (choice != 5)
            {
                int trainno;

                cout << "=====================================================" << endl;
                cout << "1. Book Ticket" << endl;
                cout << "2. Cancel Ticket" << endl;
                cout << "3. Check Ticket Status" << endl;
                cout << "4. Check Available Trains" << endl;
                cout << "5. Exit" << endl;
                cout << "=====================================================" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                srand(time(0));
                ticketID = rand() % 10000; // random ticket ID

                switch (choice)
                {
                case 1:
                {
                    cout << "\n=============================================" << endl;
                    cout << "       WELCOME TO TRAIN BOOKING SYSTEM" << endl;
                    cout << "====================================================" << endl;
                    cout << "Available Trains: \n";
                    cout << "Train Name          \t   \tTrain Number \t     \t Destination\n";
                    cout << "Himalaya Travels    \t - \t     101     \t -   \t" << from << " to " << to << "\n";
                    cout << "Shatabdi Express    \t - \t     202     \t -   \t" << from << " to " << to << "\n";
                    cout << "Vande Bharat Express\t - \t     303     \t -   \t" << from << " to " << to << "\n";
                    cout << "====================================================" << endl;
                    cout << "Enter Train number to book: ";
                    cin >> trainno;

                    if (trainno == 101 || trainno == 202 || trainno == 303)
                    {
                        // clear buffer before getline
                        cin.ignore();
                        cout << "Enter passenger name: ";
                        getline(cin, pname);

                        cout << "Enter date of journey DD MM YYYY: ";
                        cin >> day >> month >> year;

                         //  Validate that date is not in the past
                        time_t now = time(0);
                        tm *ltm = localtime(&now);

                        tm journeyDate = {};
                        journeyDate.tm_mday = day;
                        journeyDate.tm_mon = month - 1;   // months since January [0,11]
                        journeyDate.tm_year = year - 1900; // years since 1900

                        time_t journey_time = mktime(&journeyDate);

                        // compare the journey date with current date
                        if (difftime(journey_time, now) < 0)
                        {
                            cout << " Invalid date! You cannot select a past date.\n";
                            continue; // go back to menu instead of booking
                        }

                        cout << "====================================================" << endl;

                        cout << "1.AC\n2.Non-AC\n3.Sleeper\nEnter class: ";
                        cin >> clas;

                        cout << "How many seats do you want to book?: ";
                        cin >> seat;

                        cout << "Do you want a meal? (1 for Yes, 2 for No): ";
                        cin >> meal;

                        cout << "============================================================" << endl;

                        if (trainno == 101)
                        {
                            if (clas == 1)
                                amt = (4500 + (meal == 1 ? 300 : 0)) * seat;
                            else if (clas == 2)
                                amt = (3700 + (meal == 1 ? 300 : 0)) * seat;
                            else if (clas == 3)
                                amt = (2900 + (meal == 1 ? 300 : 0)) * seat;
                        }
                        else if (trainno == 202)
                        {
                            if (clas == 1)
                                amt = (4600 + (meal == 1 ? 300 : 0)) * seat;
                            else if (clas == 2)
                                amt = (3500 + (meal == 1 ? 300 : 0)) * seat;
                            else if (clas == 3)
                                amt = (2700 + (meal == 1 ? 300 : 0)) * seat;
                        }
                        else if (trainno == 303)
                        {
                            if (clas == 1)
                                amt = (4400 + (meal == 1 ? 300 : 0)) * seat;
                            else if (clas == 2)
                                amt = (3600 + (meal == 1 ? 300 : 0)) * seat;
                            else if (clas == 3)
                                amt = (2800 + (meal == 1 ? 300 : 0)) * seat;
                        }

                        // coach assignment based on class
                        string coachPrefix;
                        if (clas == 1)
                            coachPrefix = "A"; // AC
                        else if (clas == 2)
                            coachPrefix = "B"; // Non-AC
                        else
                            coachPrefix = "S"; // Sleeper

                        int coachNum = (rand() % 3) + 1; // 3 coaches per type
                        string coach = coachPrefix + to_string(coachNum);

                        // consecutive seats inside a coach
                        int startSeat = (rand() % (72 - seat + 1)) + 1;

                        cout << "Ticket booked successfully!" << endl;
                        cout << "Passenger: " << pname << endl;
                        cout << "Train No: " << trainno << "\nClass: ";
                        if (clas == 1)
                            cout << "AC";
                        else if (clas == 2)
                            cout << "Non-AC";
                        else
                            cout << "Sleeper";
                        cout << endl;

                        cout << "Seats: " << seat << endl;
                        cout << "Allocated Seats: ";
                        for (int i = 0; i < seat; i++)
                        {
                            cout << coach << "-" << startSeat + i;
                            if (i != seat - 1)
                                cout << ", ";
                        }
                        cout << endl;

                        cout << "Amount: " << amt << endl;
                        cout << "Your ticket ID(PNR) is " << ticketID << endl;

                        // save booking into file
                        ofstream outFile("bookings.txt", ios::app);
                        outFile << ticketID << ","
                                << pname << ",";
                        if (clas == 1)
                            outFile << "AC";
                        else if (clas == 2)
                            outFile << "Non-AC";
                        else if (clas == 3)
                            outFile << "Sleeper";
                        else
                            outFile << "Unknown";

                        outFile << "," << trainno << "," << seat << ",";

                        // write allocated seats to file
                        for (int i = 0; i < seat; i++)
                        {
                            outFile << coach << (startSeat + i);
                            if (i != seat - 1)
                                outFile << " ";
                        }

                        outFile << ","
                                << day << "-" << month << "-" << year << ","
                                << 1900 + ltm->tm_year << "-"
                                << 1 + ltm->tm_mon << "-"
                                << ltm->tm_mday << " "
                                << ltm->tm_hour << ":"
                                << ltm->tm_min << ":"
                                << ltm->tm_sec << ","
                                << amt << ",Confirmed" << endl;
                        outFile.close();
                    }
                    else
                    {
                        cout << "Invalid Train number. Please try again." << endl;
                    }
                    break;
                }

                case 2:
                {
                    cout << "Enter ticket ID(PNR) to check status: ";
                    cin >> tempticketID;

                    ifstream inFile("bookings.txt");
                    string line;
                    bool found = false;

                    while (getline(inFile, line))
                    {
                        if (line.find(to_string(tempticketID) + ",") == 0)
                        {
                            found = true;

                            stringstream ss(line);
                            string tid, pname, cls, tno, seats, doj, btime, amount, status;

                            getline(ss, tid, ',');    // ticket ID
                            getline(ss, pname, ',');  // passenger name
                            getline(ss, cls, ',');    // class (Economy/Business/First)
                            getline(ss, tno, ',');    // train no
                            getline(ss, seats, ',');  // seat count
                            getline(ss, doj, ',');    // date of journey
                            getline(ss, btime, ',');  // booking time
                            getline(ss, amount, ','); // amount
                            getline(ss, status, ','); // status

                            cout << "\n===== Ticket Details =====" << endl;
                            cout << "Ticket ID (PNR): " << tid << endl;
                            cout << "Passenger: " << pname << endl;
                            cout << "Class: " << cls << endl;
                            cout << "Train No: " << tno;
                            if (tno == "101")
                                cout << " (" << from << " to " << to << ")" << endl;
                            else if (tno == "202")
                                cout << " (" << from << " to " << to << ")" << endl;
                            else if (tno == "303")
                                cout << " (" << from << " to " << to << ")" << endl;
                            else
                                cout << " (Unknown Route)" << endl;

                            cout << "Seats: " << seats << endl;
                            cout << "Date of Journey: " << doj << endl;
                            cout << "Booking Time: " << btime << endl;
                            cout << "Amount: " << amount << endl;
                            cout << "Status: " << status << endl;
                            break;
                        }
                    }

                    if (!found)
                    {
                        cout << "Ticket ID not found!" << endl;
                    }

                    inFile.close();
                    break;
                }

                case 4:
                    cout << "====================================================" << endl;
                    cout << "Available Trains: \n";
                    cout << "Train Name          \t   \tTrain Number \t     \t Destination\n";
                    cout << "Rajdhani Express    \t - \t     101     \t -   \t" << from << " to " << to << "\n";
                    cout << "Shatabdi Express    \t - \t     202     \t -   \t" << from << " to " << to << "\n";
                    cout << "Vande Bharat Express\t - \t     303     \t -   \t" << from << " to " << to << "\n";
                    break;

                case 5:
                    cout << "Exiting..." << endl;
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        break;
        }

        default:
            cout << "Exiting the system. Thank you!" << endl;
        }
    }
    return 0;
}

