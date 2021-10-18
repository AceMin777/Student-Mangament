// StudentManagement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#define getch() _getch() //This allows getch() to be used. Without it caused an error 0x8007002
using namespace std;

///////////////////////////////Create Student///////////////////////////////////////
class student
{
private:
	string name, roll_no, course, address, email_id, contact_no;
public:
	/////////////////////////////Declaration////////////////////////////////////////
	void menu(); //Creates menu
	void insert(); //Create Insert which is create new record
	void display(); //Display Record
	void modify(); //Modify Declare, modify Student's record
	void search(); //Search Declare
	void deleted(); //Delete Student Record
};

/////////////////////Menu//////////////////////
void student::menu()
{
	menuStart:
	int choice;
	char x;
	system("cls");

	cout << "\t\t\t---------------------------" << endl;
	cout << "\t\t\t|   Student Managament    |" << endl;
	cout << "\t\t\t---------------------------" << endl;
	cout << "\t\t\t 1. Enter New Record" << endl;
	cout << "\t\t\t 2. Display Record" << endl;
	cout << "\t\t\t 3. Modify Record" << endl;
	cout << "\t\t\t 4. Search Record" << endl;
	cout << "\t\t\t 5. Delete Record" << endl;
	cout << "\t\t\t 6. Exit" << endl;

	cout << "\t\t\t------------------------------" << endl;
	cout << "\t\t\t|Choose Option: [1/2/3/4/5/6]|" << endl;
	cout << "\t\t\t------------------------------" << endl;
	cout << "Enter Your Choice: " << endl;
	cin >> choice;

	switch (choice)
	{
	case 1:
		do
		{
			insert();
			cout << "\n\t\t\t Add Another Student Record (Y\N): ";
			cin >> x;
		} while (x == 'y' || x == 'Y');
		break;
	case 2:
		display();
		break;
	case 3:
		modify();
		break;
	case 4:
		search();
		break;
	case 5:
		deleted();
		break;
	case 6:
		exit(0);
		break;
	default:
		cout << "\n\t\t\t Invalid Choice... Please Pick a Number Between (1-6)" << endl;
		//break;
	}

	//getch is the problem. Without #include <conio.h> and #define getch() _getch() it will not work
	getch(); //get character command doesn't show the "Press any key to continue..."
	goto menuStart; //goto is an unconditional jump statement that jumps to a specified location
}

//////////////////////Create Student Details//////////////////////////
void student::insert() //Add Student Detail
{
	system("cls"); //cls means clear the screen. The cursor is moved to the upper left part of the screen
	fstream file;
	cout << "\n---------Add Student Detail------" << endl;
	cout << "\t\t\tEnter Name: ";
	cin >> name;
	cout << "\t\t\tEnter Roll No.: ";
	cin >> roll_no;
	cout << "\t\t\tEnter Course: ";
	cin >> course;
	cout << "\t\t\tEnter Email Id: ";
	cin >> email_id;
	cout << "\t\t\tEnter Contact No: ";
	cin >> contact_no;
	cout << "\t\t\tEnter Address: ";
	cin >> address;

	/*In file, the ios::out writes the text, the ios::app appends the text meaning it adds in the mode which is txt.
	  Not inlucing the ios::app will overwrite whats in the file. */
	file.open("studentRecord.txt", ios::app | ios::out);
	file << " " << name << " " << roll_no << " " << course << " " << email_id << " " << contact_no << " " << address << " "
		<< "\n";
	file.close();
}

/////////////////Display Student Records///////////////////
void student::display()
{
	system("cls");
	fstream file;
	int total = 0;
	cout << "\n-------------------------------------------------------------" << endl;
	cout << "----------------------Student Record Table-------------------" << endl;
	
	file.open("studentRecord.txt", ios::in); //ios::in allows the file to be read
	if (!file) //If there is no file that doesn't have the name then no data is found
	{
		cout << "\n\t\t\File Does Not Exist...";
		getch();
		file.close();
	}
	else
	{
		file >> name >> roll_no >> course >> email_id >> contact_no >> address;
		while (!file.eof()) /*eof means end of file. Returns a nonzero (meaning TRUE) when there are no more data to be read 
			                  from an input file stream, and zero (meaning FALSE) otherwise. While we don't reach the end of 
			                  the file the loop will continue */
		{
			cout << "\n\n\t\t\t Student No: " << total++ << endl;
			cout << "\t\t\t Student Name: " << name << endl;
			cout << "\t\t\t Student Roll No: " << roll_no << endl;
			cout << "\t\t\t Student Course: " << course << endl;
			cout << "\t\t\t Student Email Id: " << email_id << endl;
			cout << "\t\t\t Student Address: " << address << endl;
			file >> name >> roll_no >> course >> email_id >> contact_no >> address;
		}
		if (total == 0)
		{
			cout << "\n\t\t\tNo Data is Found...";
		}
	}
	file.close();
	//system("pause");
	getch();
}

/////////////////////////////////Modify/////////////////////////////
void student::modify()
{
	system("cls");
	fstream file, file1;
	string rollno;
	int found = 0;
	cout << "\n---------------------------------------------------------------" << endl;
	cout << "\n--------------------Modify Student Detail----------------------" << endl;

	file.open("studentRecord.txt", ios::in);
	if (!file) //Check to see if a file exits
	{
		cout << "\n\t\t\tNo File is Present";
		file.close();
	}
	else
	{
		cout << "\nEnter the Roll No. of Student You Wish to Modify: ";
		cin >> rollno;
		file1.open("Record.txt", ios::app | ios::out);
		file >> name >> roll_no >> course >> email_id >> contact_no >> address;

		while (!file.eof())
		{
			if (rollno != roll_no)
			{
				file1 << " " << name << " " << roll_no << " " << course << " "
				<< email_id << " " << contact_no << " " << address << " " << "\n";
			}
			else
			{
				cout << "\t\t\tEnter Name: ";
				cin >> name;
				cout << "\t\t\tEnter Roll No.: ";
				cin >> roll_no;
				cout << "\t\t\tEnter Course: ";
				cin >> course;
				cout << "\t\t\tEnter Email Id: ";
				cin >> email_id;
				cout << "\t\t\tEnter Contact No: ";
				cin >> contact_no;
				cout << "\t\t\tEnter Address: ";
				cin >> address;

				//Without it the new record won't be added and the previous record is gone
				file1 << " " << name << " " << roll_no << " " << course << " "
				<< email_id << " " << contact_no << " " << address << " " << "\n";

				found++;
			}

			file >> name >> roll_no >> course >> email_id >> contact_no >> address;
			if (found == 0)
			{
				cout << "\n\t\t\tStudent Roll No. Not Found";
			}
		}
		file1.close();
		file.close();

		//We remove the old studentRecord then we rename Record.txt to studentRecord.txt
		remove("studentRecord.txt");
		rename("Record.txt", "studentRecord.txt");
	}
}

void student::search()
{
	system("cls");
	fstream file;
	int found = 0;
	file.open("studentRecord.txt", ios::in);
	if (!file)
	{
		cout << "\n--------------------------------------------------------------------------" << endl;
		cout << "------------------------ Search Student Record ---------------------------" << endl;
		cout << "\n\t\t\t The Record File is Not Found" << endl;
	}
	else
	{
		string rollno;
		cout << "\n--------------------------------------------------------------------------" << endl;
		cout << "------------------------ Search Student Record ---------------------------" << endl;
		cout << "Enter Roll No of Student You Want to Search: ";
		cin >> rollno;
		file >> name >> roll_no >> course >> email_id >> contact_no >> address;
		while (!file.eof())
		{
			if (rollno == roll_no)
			{
				cout << "\t\t\t Student Name: " << name << endl;
				cout << "\t\t\t Student Roll No: " << roll_no << endl;
				cout << "\t\t\t Student Course: " << course << endl;
				cout << "\t\t\t Student Email Id: " << email_id << endl;
				cout << "\t\t\t Student Address: " << address << endl;
				found++;
			}
		    file >> name >> roll_no >> course >> email_id >> contact_no >> address;
		}
		if (found == 0)
		{
			cout << "\n\t\t\tThere is no Student with that Roll No.";
		}
		file.close();
	}
}

void student::deleted()
{
	system("cls");
	fstream file, file1;
	string rollno;
	int found = 0;
	cout << "\n--------------------------------------------------------------------------" << endl;
	cout << "------------------------ Delete Student Record ---------------------------" << endl;
	file.open("studentRecord.txt", ios::in);
	if (!file)
	{
		cout << "\n--------------------------------------------------------------------------" << endl;
		cout << "\n\t\t\t The Record File Does Not Exist" << endl;
	}
	else
	{
		cout << "\nEnter The Roll No. of The Student You Wish to Delete: ";
		cin >> rollno;
		file1.open("record.txt", ios::app | ios::out);
		file >> name >> roll_no >> course >> email_id >> contact_no >> address;
		while (!file.eof())
		{
			if (rollno != roll_no)
			{
				file1 << " " << name << " " << roll_no << " " << course << " "
					<< email_id << " " << contact_no << " " << address << " " << "\n";
			}
			else
			{
				found++;
				cout << "\n\t\t\tSuccessfully Deleted Student Data";
			}
			file >> name >> roll_no >> course >> email_id >> contact_no >> address;
		}
		if (found == 0)
		{
			cout << "\n\t\t\tStudent Roll No Not Found";
		}
		file1.close();
		file.close();
		remove("studentRecord.txt");
		rename("record.txt", "studentRecord.txt");
	}
}

int main()
{
	student project;
	project.menu();
	return 0;
}