#include<iostream>  //For Input/Output
#include<string>   //For Strings
#include<chrono>  //For Access&Deal Time
#include<thread> //For efficiency of program make it to execute multiple tasks conqurently.
#include<fstream> // ✅ File Handling

using namespace std;

//==================== Function Prototypes ====================

//Main Menu Funtions
void bookmenu();
void membermenu();
void finedetails();
void profilemenu();
void rules();

//Book Menu Funtions
void searchbook();
void addbook();
void removebook();
void checkavailability();
void issuebook();
void returnbook();           // ✅ NEW
void bookdetails();
void totalbooks();
void checkLowBookAvailability();

//Member Menu Funtions
void searchmember();
void addmember();
void removemember();
void memberdetails();
void totalmembers();
void checkLowMemberCount();

//Rules & Regulations Functions
void libraryhours();
void borrowingprivileges();
void finepolicy();
void rights();

// ✅ File Handling Functions
void saveToFile();
void loadFromFile();

//==================== Global Data ====================

//max size of string 100 for adding books and members
const int max_size = 100;

// Predefined books
string bookIds[max_size] = {"101", "102", "103", "104", "105", "106", "107", "108", "109", "110"};
string bookNames[max_size] = {"Sapiens", "Dune", "IT", "1984", "Beloved", "Hatchet", "EMMA", "Speak", "Room", "Blink"};
string authors[max_size] = {"Yuval Noah Harari", "Frank Herbert", "Stefen king", "George Orwell", "Toni Morrison", "Gary Paulsen", "Jane Austen", "Laurie Halse Anderson", "Emma Donoghue", "Malcolm Gladwell"};
string publishedDates[max_size] = {"2014", "1965", "1986", "1949", "1987", "1986", "1815", "1999", "2010", "2005"};
bool availability[max_size] = {true, true, true, true, true, true, true, true, true, true};
string issuedToMemberIds[max_size] = {"N/A", "N/A", "N/A", "N/A", "N/A","N/A","N/A","N/A","N/A","N/A"};
int totalBooks = 10;

// Predefined members
string memberIds[max_size] = {"1001", "1002", "1003", "1004", "1005", "1006", "1007", "1008", "1009", "1010"};
string memberNames[max_size] = {"Hassan", "Mian Moaz", "Mian Ahmar", "Talha AR", "Hasnain Sandhu", "Sikander", "Umm E Salma", "Rumaisa", "Raghad Zia", "Noor Malik"};
string rollNos[max_size] = {"1068", "1052", "1056", "1080", "1065","1079", "1095", "1089", "1101", "1102"};
string departments[max_size] = {"CS", "CS", "CS", "SE", "AI","CS", "AI", "BS", "TT", "FD"};
int totalMembers = 10;

//==================== main() ====================

int main()
{
    // ✅ Load data from file if exists
    loadFromFile();

	cout<<"========================================================"<<endl;
	cout<<"              National Textile University               "<<endl;
	cout<<"========================================================"<<endl;
	cout<<"          Welcome To Library Management System          "<<endl;
	cout<<"========================================================"<<endl;

	bool check = false;
	int attempts = 0;
	while(!check)
	{
	  string name;
	  int pass;
	  cout<<"Enter Admin Username : ";
	  cin>>name;
	  cout<<"Enter Password : ";
	  cin>>pass;
	  cout<<"========================================================"<<endl;
	   if(name=="Admin"&&pass==1234)
	   {
	   	cout<<"                 Login Successful"<<endl;
	   	cout<<"========================================================"<<endl;
	   	check =  true;
	   }
	   else
	   {
	   	attempts++;
	   	cout<<"Invalid Username or Password"<<endl;
	   	cout<<"========================================================"<<endl;
	   	if(attempts>=3)
	   	{
	   	    cout<<"To many attempts.Try Again."<<endl;
		    cout<<"========================================================"<<endl;
	   	    return 0;
	   	}
	   }
    }

    cout<<endl;
	int input;
	while(true)
	{
		cout<<"========================================================"<<endl;
		cout<<"                   Main Menu                            "<<endl;
		cout<<"========================================================"<<endl;
		cout<<"Choose a option                                         "<<endl;
		cout<<"1. Books Details                                        "<<endl;
		cout<<"2. Members Details                                      "<<endl;
		cout<<"3. Fine Details                                         "<<endl;
		cout<<"4. Rules & Regulations                                  "<<endl;
		cout<<"5. Personal Profile                                     "<<endl;
		cout<<"6. Exit                                                 "<<endl;
		cout<<"========================================================"<<endl;
		cin>>input;

		switch(input)
		{
			case 1: bookmenu(); break;
			case 2: membermenu(); break;
			case 3: finedetails(); break;
			case 4: rules(); break;
			case 5: profilemenu(); break;
			case 6:
				cout<<"Good Bye.Thanks For Coming"<<endl;
				return 0;
			default:
				cout<<"Invalid Option"<<endl;
		}
	}
}

//==================== File Handling ====================

void saveToFile()
{
    ofstream file("LMS.txt");
    if(!file)
    {
        cout << "Error: LMS.txt open nahi ho rahi (write)!" << endl;
        return;
    }

    file << "BOOKS " << totalBooks << "\n";
    for(int i=0; i<totalBooks; i++)
    {
        file << bookIds[i] << "|"
             << bookNames[i] << "|"
             << authors[i] << "|"
             << publishedDates[i] << "|"
             << (availability[i] ? 1 : 0) << "|"
             << issuedToMemberIds[i] << "\n";
    }

    file << "MEMBERS " << totalMembers << "\n";
    for(int i=0; i<totalMembers; i++)
    {
        file << memberIds[i] << "|"
             << memberNames[i] << "|"
             << rollNos[i] << "|"
             << departments[i] << "\n";
    }

    file.close();
}

void loadFromFile()
{
    ifstream file("LMS.txt");
    if(!file)
    {
        return; // no file -> keep predefined
    }

    string tag;
    int count;

    file >> tag >> count;
    file.ignore();

    if(tag == "BOOKS")
    {
        totalBooks = 0;
        for(int i=0; i<count && i<max_size; i++)
        {
            string line;
            getline(file, line);

            int p1 = line.find('|');
            int p2 = line.find('|', p1+1);
            int p3 = line.find('|', p2+1);
            int p4 = line.find('|', p3+1);
            int p5 = line.find('|', p4+1);

            if(p1==string::npos || p2==string::npos || p3==string::npos ||
               p4==string::npos || p5==string::npos) continue;

            bookIds[totalBooks] = line.substr(0, p1);
            bookNames[totalBooks] = line.substr(p1+1, p2-(p1+1));
            authors[totalBooks] = line.substr(p2+1, p3-(p2+1));
            publishedDates[totalBooks] = line.substr(p3+1, p4-(p3+1));

            string availStr = line.substr(p4+1, p5-(p4+1));
            availability[totalBooks] = (availStr == "1");

            issuedToMemberIds[totalBooks] = line.substr(p5+1);
            totalBooks++;
        }
    }

    file >> tag >> count;
    file.ignore();

    if(tag == "MEMBERS")
    {
        totalMembers = 0;
        for(int i=0; i<count && i<max_size; i++)
        {
            string line;
            getline(file, line);

            int p1 = line.find('|');
            int p2 = line.find('|', p1+1);
            int p3 = line.find('|', p2+1);

            if(p1==string::npos || p2==string::npos || p3==string::npos) continue;

            memberIds[totalMembers] = line.substr(0, p1);
            memberNames[totalMembers] = line.substr(p1+1, p2-(p1+1));
            rollNos[totalMembers] = line.substr(p2+1, p3-(p2+1));
            departments[totalMembers] = line.substr(p3+1);
            totalMembers++;
        }
    }

    file.close();
}

//==================== Menus ====================

void bookmenu()
{
	int op;
	while(true)
	{
		cout<<"========================================================"<<endl;
		cout<<"Choose a option                                         "<<endl;
		cout<<"1. Search a book                                        "<<endl;
		cout<<"2. Add a book                                           "<<endl;
		cout<<"3. Remove a book                                        "<<endl;
		cout<<"4. Check Availability                                   "<<endl;
		cout<<"5. Issue a book                                         "<<endl;
        cout<<"6. Return a book                                        "<<endl; // ✅ NEW
		cout<<"7. Display all book & their details                     "<<endl;
		cout<<"8. Total books                                          "<<endl;
		cout<<"9. Exit                                                 "<<endl;
		cout<<"========================================================"<<endl;
		cin>>op;

		switch(op)
		{
			case 1: searchbook(); break;
			case 2: addbook(); break;
			case 3: removebook(); break;
			case 4: checkavailability(); break;
			case 5: issuebook(); break;
            case 6: returnbook(); break; // ✅ NEW
			case 7: bookdetails(); break;
			case 8: totalbooks(); break;
			case 9: return;
			default: cout<<"Invalid Option"<<endl;
		}
		checkLowBookAvailability();
	}
}

void membermenu()
{
	int option;
	while(true)
	{
		cout<<"========================================================"<<endl;
		cout<<"Choose a option                                         "<<endl;
		cout<<"1. Search a member                                      "<<endl;
		cout<<"2. Add a member                                         "<<endl;
		cout<<"3. Remove a member                                      "<<endl;
		cout<<"4. Display all members & their details                  "<<endl;
		cout<<"5. Total members                                        "<<endl;
		cout<<"6. Exit                                                 "<<endl;
		cout<<"========================================================"<<endl;
		cin>>option;

		switch(option)
		{
			case 1: searchmember(); break;
			case 2: addmember(); break;
			case 3: removemember(); break;
			case 4: memberdetails(); break;
			case 5: totalmembers(); break;
			case 6: return;
			default: cout<<"Invalid Option"<<endl;
		}
		checkLowMemberCount();
	}
}

void finedetails()
{
    string id;
    cout << "Enter Book ID to check Fine: ";
    cin >> id;

    for (int i = 0; i < totalBooks; i++)
    {
        if (bookIds[i] == id)
        {
            cout << "Book Found: " << bookNames[i] << endl;
            cout << "Fined: " << (availability[i] ? "No" : "Yes") << endl;

            if (!availability[i])
            {
                cout << "Issued to Member ID: " << issuedToMemberIds[i] << endl;

                int fineAmount = 5;
                int totalFine = 0;
                char choice;

                do
                {
                    totalFine += fineAmount;
                    cout << "Fine: " << totalFine << " Rupees" << endl;
                    cout << "Do you want to continue? (y/n): ";
                    cin >> choice;
                }
                while (choice == 'y' || choice == 'Y');

                cout << "Exiting fine calculation for this book." << endl;
            }
            return;
        }
    }
    cout<<"Book not found"<<endl;
}

void rules()
{
	int inp;
	while(true)
	{
		cout<<"========================================================"<<endl;
		cout<<"Choose a option                                         "<<endl;
		cout<<"1. Library  Hours Details                               "<<endl;
		cout<<"2. Borrowing Privilieges                                "<<endl;
		cout<<"3. Fine Policy                                          "<<endl;
		cout<<"4. University Rights                                    "<<endl;
		cout<<"5. Exit                                                 "<<endl;
		cout<<"========================================================"<<endl;
		cin>>inp;

		switch(inp)
		{
			case 1: libraryhours(); break;
			case 2: borrowingprivileges(); break;
			case 3: finepolicy(); break;
			case 4: rights(); break;
			case 5: return;
			default: cout<<"Invalid Option"<<endl;
		}
	}
}

void profilemenu()
{
	cout<<"========================================================"<<endl;
	cout<<"Name :                 |     Muhammad                   "<<endl;
	cout<<"F.Name :               |     Muhammad                   "<<endl;
	cout<<"Contact No :           |     0000-0000000               "<<endl;
	cout<<"CNIC No :              |     00000-0000000-0            "<<endl;
	cout<<"Address :              |     Faisalabad                 "<<endl;
	cout<<"Education :            |     Ph.D. in Computer Science  "<<endl;
	cout<<"Institute Name :       |     National Textile University"<<endl;
	cout<<"========================================================"<<endl;
}

//==================== Book Functions ====================

void addbook()
{
    if (totalBooks >= max_size)
	{
        cout << "Book storage is full!" << endl;
        return;
    }

    string id, name, author, date;
    cout << "Enter Book ID: ";
    cin >> id;
    cout << "Enter Book Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Author: ";
    getline(cin, author);
    cout << "Enter Published Year: ";
    cin >> date;

    bookIds[totalBooks] = id;
    bookNames[totalBooks] = name;
    authors[totalBooks] = author;
    publishedDates[totalBooks] = date;
    availability[totalBooks] = true;
    issuedToMemberIds[totalBooks] = "N/A";
    totalBooks++;

    cout << "Book added successfully!" << endl;
    saveToFile();
}

void removebook()
{
    string id;
    cout << "Enter Book ID to remove: ";
    cin >> id;

    for (int i = 0; i < totalBooks; i++)
	{
        if (bookIds[i] == id)
		{
            for (int j = i; j < totalBooks - 1; j++)
			{
                bookIds[j] = bookIds[j + 1];
                bookNames[j] = bookNames[j + 1];
                authors[j] = authors[j + 1];
                publishedDates[j] = publishedDates[j + 1];
                availability[j] = availability[j + 1];
                issuedToMemberIds[j] = issuedToMemberIds[j + 1];
            }
            totalBooks--;
            cout << "Book removed successfully!" << endl;
            saveToFile();
            return;
        }
    }
    cout << "Book not found!" << endl;
}

void searchbook()
{
    string id;
    cout << "Enter Book ID to search: ";
    cin >> id;

    for (int i = 0; i < totalBooks; i++)
	{
        if (bookIds[i] == id)
		{
            cout << "Book Found: " << bookNames[i] << endl;
            cout << "Author: " << authors[i] << endl;
            cout << "Published Year: " << publishedDates[i] << endl;
            cout << "Availability: " << (availability[i] ? "Available" : "Issued") << endl;
            if (!availability[i])
			{
                cout << "Issued to Member ID: " << issuedToMemberIds[i] << endl;
            }
            return;
        }
    }
    cout << "Book not found." << endl;
}

void checkavailability()
{
    string id;
    cout << "Enter Book ID to check availability: ";
    cin >> id;

    for (int i = 0; i < totalBooks; i++)
	{
        if (bookIds[i] == id)
		{
            cout << "Book is " << (availability[i] ? "Available" : "Issued") << endl;
            return;
        }
    }
    cout << "Book not found!" << endl;
}

void issuebook()
{
    string id, memberId;
    cout << "Enter Book ID to issue: ";
    cin >> id;

    for (int i = 0; i < totalBooks; i++)
	{
        if (bookIds[i] == id)
		{
            if (!availability[i])
			{
                cout << "Book is already issued!" << endl;
                return;
            }

            cout << "Enter Member ID: ";
            cin >> memberId;

            for (int j = 0; j < totalMembers; j++)
			{
                if (memberIds[j] == memberId)
				{
                    availability[i] = false;
                    issuedToMemberIds[i] = memberId;
                    cout << "Book issued successfully!" << endl;
                    saveToFile();
                    return;
                }
            }

            cout << "Member not found!" << endl;
            return;
        }
    }
    cout << "Book not found!" << endl;
}

// ✅ NEW: Return Book (updates file)
void returnbook()
{
    string bookId, memberId;
    cout << "Enter Book ID to return: ";
    cin >> bookId;

    for(int i = 0; i < totalBooks; i++)
    {
        if(bookIds[i] == bookId)
        {
            if(availability[i])
            {
                cout << "This book is already available (not issued)." << endl;
                return;
            }

            cout << "Enter Member ID who is returning: ";
            cin >> memberId;

            if(issuedToMemberIds[i] != memberId)
            {
                cout << "Mismatch! This book is NOT issued to Member ID: " << memberId << endl;
                cout << "Issued To: " << issuedToMemberIds[i] << endl;
                return;
            }

            availability[i] = true;
            issuedToMemberIds[i] = "N/A";

            cout << "Book returned successfully!" << endl;
            saveToFile();
            return;
        }
    }
    cout << "Book not found!" << endl;
}

void bookdetails()
{
    cout << "\nBook Details:\n";
    for (int i = 0; i < totalBooks; i++)
	{
        cout << "ID: " << bookIds[i] << ", Name: " << bookNames[i]
             << ", Author: " << authors[i] << "\nPublished: " << publishedDates[i]
             << ", Availability: " << (availability[i] ? "Available" : "Issued")
             << ", Issued To: " << issuedToMemberIds[i] << endl;
    }
}

void totalbooks()
{
	cout<<"Total Books in Library : "<<totalBooks<<endl;
}

void checkLowBookAvailability()
{
    int remainingBooks = 0;
    for (int i = 0; i < totalBooks; i++)
	{
        if (availability[i]) remainingBooks++;
    }
    if (remainingBooks <= 2)
	{
        cout << "Warning: Only " << remainingBooks << " books remaining in the library!" << endl;
    }
}

//==================== Member Functions ====================

void searchmember()
{
    string id;
    cout << "Enter Member ID to search: ";
    cin >> id;

    for (int i = 0; i < totalMembers; i++)
	{
        if (memberIds[i] == id)
		{
            cout << "Member Found: " << memberNames[i]
                 << ", Roll No: " << rollNos[i]
                 << ", Department: " << departments[i] << endl;

            for (int j = 0; j < totalBooks; j++)
			{
                if (issuedToMemberIds[j] == id)
				{
                    cout << "Issued Book: " << bookNames[j] << endl;
                }
            }
            return;
        }
    }
    cout << "Member not found!" << endl;
}

void addmember()
{
    if (totalMembers >= max_size)
	{
        cout << "Member storage is full!" << endl;
        return;
    }

    string id, name, rollNo, department;
    cout << "Enter Member ID: ";
    cin >> id;

    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Roll No: ";
    getline(cin, rollNo);
    cout << "Enter Department: ";
    getline(cin, department);

    memberIds[totalMembers] = id;
    memberNames[totalMembers] = name;
    rollNos[totalMembers] = rollNo;
    departments[totalMembers] = department;
    totalMembers++;

    cout << "Member added successfully!" << endl;
    saveToFile();
}

void removemember()
{
    string id;
    cout << "Enter Member ID to remove: ";
    cin >> id;

    for (int i = 0; i < totalMembers; i++)
	{
        if (memberIds[i] == id)
		{
            for (int j = i; j < totalMembers - 1; j++)
			{
                memberIds[j] = memberIds[j + 1];
                memberNames[j] = memberNames[j + 1];
                rollNos[j] = rollNos[j + 1];
                departments[j] = departments[j + 1];
            }
            totalMembers--;
            cout << "Member removed successfully!" << endl;
            saveToFile();
            return;
        }
    }
    cout << "Member not found!" << endl;
}

void memberdetails()
{
    cout << "\nMember Details:\n";
    for (int i = 0; i < totalMembers; i++)
	{
        cout << "ID: " << memberIds[i] << ", Name: " << memberNames[i]
             << "\nRoll No: " << rollNos[i]
             << ", Department: " << departments[i] << endl;
    }
}

void totalmembers()
{
	cout<<"Total Members in Library : "<<totalMembers<<endl;
}

void checkLowMemberCount()
{
    if (totalMembers <= 2)
	{
        cout << "Warning: Only " << totalMembers << " members left!" << endl;
    }

    if (totalMembers >= 100)
	{
        cout << "Warning: Member limit reached out!" << endl;
    }
}

//==================== Rules Functions ====================

void libraryhours()
{
	cout<<"========================================================"<<endl;
    cout<<"                   Library Hours Details                "<<endl;
	cout<<"========================================================"<<endl;
	cout<<"Library opens seven days a week according to the        "<<endl;
	cout<<"following schedule:                                     "<<endl;
	cout<<"Monday-Thursday           |   08:30 am to 09:00 pm      "<<endl;
	cout<<"Friday                    |   08:30 am to 04:40 pm      "<<endl;
	cout<<"Saturday & Sunday         |   02:00 pm to 09:00 pm      "<<endl;
	cout<<"There will be one-hour Prayer/Lunch break, as notified  "<<endl;
	cout<<"by the administration.                                  "<<endl;
    cout<<"========================================================"<<endl;
}

void borrowingprivileges()
{
	cout<<"========================================================"<<endl;
	cout<<"                  Borrowing Privileges                  "<<endl;
	cout<<"========================================================"<<endl;
	cout<<"1. Students can borrow three books for 21 days.         "<<endl;
	cout<<"2. Borrowing facility is not available to NTU Alumni and"<<endl;
	cout<<"   students reffered from other institutions, however   "<<endl;
	cout<<"   other library services are available accordingly.    "<<endl;
	cout<<"3. Some materials, such as reference books, press       "<<endl;
	cout<<"   clippings, CD-ROMs, current periodicals, or  any     "<<endl;
	cout<<"   other publication marked as reference/reserved will  "<<endl;
	cout<<"   not be circulated/issued.                            "<<endl;
	cout<<"========================================================"<<endl;
}

void finepolicy()
{
	cout<<"========================================================"<<endl;
	cout<<"                       Fine Policy                      "<<endl;
	cout<<"========================================================"<<endl;
	cout<<"Studnts incur fines as follows:                         "<<endl;
	cout<<"1. Overdue Books                                        "<<endl;
	cout<<"   Rs. 5/- per book per day                             "<<endl;
	cout<<"2. Lost Books                                           "<<endl;
	cout<<"   In case of loss or damage, a sum of three-time cost  "<<endl;
	cout<<"   of the original price along with overdue fine will be"<<endl;
	cout<<"   charged.                                             "<<endl;
	cout<<"3. Reserve Material                                     "<<endl;
	cout<<"   This material is issued with the written permission  "<<endl;
	cout<<"   from the Senior Librarian for three hours, overnight,"<<endl;
	cout<<"   and three days only. A fine Rs.10 per each extra hour"<<endl;
	cout<<"   /day will be charged.                                "<<endl;
	cout<<"4. Theft                                                "<<endl;
	cout<<"   The wilful damage or theft of library materials will "<<endl;
	cout<<"   result in an automatic refferal to the university    "<<endl;
	cout<<"   administration and may lead to suspension from the   "<<endl;
	cout<<"   university.                                          "<<endl;
	cout<<"Note :  Users are required to pay fines and fees in the "<<endl;
	cout<<"        bank. NTU Library does not deal in any cash     "<<endl;
	cout<<"        transaction.                                    "<<endl;
	cout<<"========================================================"<<endl;
}

void rights()
{
	cout<<"========================================================"<<endl;
	cout<<"                    University Rights                   "<<endl;
	cout<<"========================================================"<<endl;
	cout<<"1. The University reserves the rights to modify or      "<<endl;
	cout<<"   cancel, without notice, any statement or service in  "<<endl;
	cout<<"   the rules and regulations.                           "<<endl;
	cout<<"2. Please contact the Library HOD/CIRCULATION DESK for  "<<endl;
	cout<<"   further enquiries.                                   "<<endl;
	cout<<"3. Your feedback is welcome that will enable the Library"<<endl;
	cout<<"   Administration to refine and enhance the information "<<endl;
	cout<<"   services.                                            "<<endl;
	cout<<"4. Your cooperation urges us to serve you better.       "<<endl;
	cout<<"========================================================"<<endl;
}
