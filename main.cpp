#include <iostream>
#include <conio.h>//for getch()
#include <iomanip>//for setw()
#include<fstream>//for file write()
#include<ios>//stream size
#include<limits>//numeric limits
#include<windows.h>//for editing display
using namespace std;

//structure of a registered course, a student and a course
struct Reg_course
{
    int reg_courseNo;
    string grade;
};

struct Student
{
	int id;
	string fname;
	string lname;
	int age;
	char sex;
	Reg_course reg_course[50];
    Student *snext;

};

struct Course 
{
    int courseNo;
    int creditHr;
    string courseName;
    Course *cnext;
};

//declaration of functions
void registerStudents();
void registerToCourses();
void maintainGrades();
void searchStudents();
void searchCourses();
void sortStudents();
void displayStudents();
void deleteStudents();
void deleteCourses();
void writeToFile();

//struct pointer variables
struct Student *std_start_ptr = NULL, *Stemp;
struct Course *crs_start_ptr = NULL, *Ctemp;
int main()
{
    //edit the display
    CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = 0;// Width of each character in the font
        cfi.dwFontSize.Y = 24;// Height
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;
        std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
        system("color 71");

	//choice input of user
	int choice;

	while(true)
	{
	    //display menu
		cout << "-----------------------------------------------------------------------" << endl;
		cout << "WELCOME TO STUDENT RECORD MANAGEMENT SYSTEM" << endl;
		cout << "-----------------------------------------------------------------------" << endl << endl;
		cout << "1. Register students" << endl;
		cout << "2. Register students to courses" << endl;
		cout << "3. Maintain grades of students in courses on which they were registered" << endl;
		cout << "4. Search a student by id " << endl;
		cout << "5. Search a course by its course number" << endl;
		cout << "6. Sort students by their name" << endl;
		cout << "7. Display the details of all students." << endl;
		cout << "8. Delete a student by id" << endl;
		cout << "9. Delete a course by courseNo" << endl;
		cout << "10. Save Student information to file" << endl;
		cout << "11. Exit" << endl << endl;
		cout << "Enter your choice: (1-9)" << endl;
		//enter choice
		if(!(cin>>choice))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

		switch(choice)
		{
		    case 1:
			    registerStudents();
				break;
            case 2:
                registerToCourses();
                break;
			case 3:
			    maintainGrades();
				break;
			case 4:
			    searchStudents();
				break;
			case 5:
			    searchCourses();
				break;
			case 6:
			    sortStudents();
				break;
			case 7:
			    displayStudents();
				break;
			case 8:
			    deleteStudents();
				break;
			case 9:
			    deleteCourses();
				break;
			case 10:
				writeToFile();
				break;
            case 11:
				return 0;

			default:
				cout << "invalid input, please try again!" << endl;
		}
		getch();
		system("cls");
	}//end of while loop

	return 0;
}

void registerStudents()
{
    //accept inputs
    Stemp = new Student;
    cout<<"enter the student's id"<<endl;
    while(!(cin>>Stemp->id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "please, enter a valid input" << endl;
    }
    struct Student *Stemp_2 = std_start_ptr;
    if(std_start_ptr!=NULL)
    {
        while(Stemp_2!=NULL)
        {
            if(Stemp_2->id == Stemp->id)
            {
                cout << "A student with id: " << Stemp->id << " is already registered!" << endl;
                return;
            }
            Stemp_2 = Stemp_2->snext;
        }
    }
    cout<<"enter the student's first name"<<endl;
    cin>>Stemp->fname;
    cout<<"enter the student's last name"<<endl;
    cin>>Stemp->lname;
    cout<<"enter the student's age"<<endl;
    while(!(cin>>Stemp->age))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "please, enter a valid input" << endl;
    }
    cout<<"enter the student's sex(M/F)"<<endl;
    cin >>Stemp->sex;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //add the student info to the student linked list
    Stemp -> snext = NULL;
    if(std_start_ptr == NULL)
        std_start_ptr = Stemp;

    else
    {
        struct Student *Stemp_2 = std_start_ptr;
        while(Stemp_2->snext != NULL)
            {
                Stemp_2 = Stemp_2->snext;
            }
        Stemp_2->snext = Stemp;
    }
    //display successful msg
    cout << "student info added successfully!" << endl;
}

void registerToCourses()
{
    //accept inputs
    int ID;
    bool isStdFound = false;
    cout<<"enter the student's id"<<endl;
    while(!(cin>>ID))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "please, enter a valid input" << endl;
    }

    struct Student *Stemp_2 = std_start_ptr;
    if(std_start_ptr==NULL)
    {
        cout << "Empty student list!" << endl;
        return;
    }


    //check if there is a student already registered with the given id
    while(Stemp_2!=NULL)
    {
        if(Stemp_2->id == ID)
        {
            cout << "found" << endl;
            isStdFound = true;
            break;
        }
        Stemp_2 = Stemp_2->snext;
    }

    if(isStdFound)
    {
        char input;
        int i=0;//index
        while(Stemp_2 ->reg_course[i].reg_courseNo!=0)
            i++;
        //store registered course in the linked list
        do
        {
            //check if registered course size is reached maximum limit
            if(i >= 50)
            {
                cout << "course registration reached maximum limit, you cannot register anymore courses!" << endl;
                break;
            }
            Ctemp = new Course;
            //accept inputs
            cout<<"enter a course name to register"<<endl;
            cin.ignore();
            getline(cin, Ctemp->courseName);
            cout<<"enter the course number to register"<<endl;
            while(!(cin>>Stemp->reg_course[i].reg_courseNo))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "please, enter a valid input :" << endl;
            }

            Ctemp->courseNo = Stemp->reg_course[i].reg_courseNo;
            cout<<"enter the course credit hour to register :"<<endl;
            while(!(cin>>Ctemp->creditHr))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "please, enter a valid input :" << endl;
            }
            cout<<endl;
            cout<<"do you want to register more courses(Y/N) :"<<endl;
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            //set grade to NG
            Stemp->reg_course[i].grade = "NG";

            Ctemp->cnext = NULL;

            //add the course info to the Course linked list
            if(crs_start_ptr == NULL)
                    crs_start_ptr = Ctemp;

            else
            {
                struct Course *Ctemp_2 = crs_start_ptr;
                while(Ctemp_2->cnext!= NULL)
                {
                    Ctemp_2 = Ctemp_2->cnext;
                }
                Ctemp_2->cnext = Ctemp;
            }//end of else statement
            i++;

        }while(input=='Y'||input=='y');
    }

    else
        cout << "There is no student registered with id: " << ID << endl;
}

void maintainGrades()
{
    int ID, regCourseNo;
    bool foundId = true;
    string regCourseGrade;
    cout << "enter the student's ID" << endl;
    while(!(cin>>ID))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "please, enter a valid input :" << endl;
    }
    struct Student *Stemp_2 = std_start_ptr;
    if(Stemp_2 == NULL)
    {
        cout << "Empty Student list!" << endl;
        return;
    }

    while(Stemp_2 != NULL)
    {
        if(Stemp_2->id == ID)
        {
            foundId = true;
            break;
        }
        Stemp_2 = Stemp_2->snext;
    }
    if(foundId)
    {
        //accept registered course number
        cout << "enter the registered course number :" << endl;
        while(!(cin>>regCourseNo))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "please, enter a valid input" << endl;
        }
        //check and add a grade for the corresponding registered course
        int i=0;//index

        if(Stemp_2->reg_course[i].reg_courseNo == 0)
        {
            cout << "there are no registered courses to grade!" << endl;
            return;
        }
        do
        {
            if(Stemp_2->reg_course[i].reg_courseNo == regCourseNo)
            {
                cout << "enter the grade for the course" << endl;
                cin >> regCourseGrade;
                Stemp_2->reg_course[i].grade = regCourseGrade;
                cout << "course grade updated successfully!" << endl;
                return;
            }
            i++;

        }while(Stemp_2->reg_course[i].reg_courseNo != 0);

        cout << "no registered courses found with :" << regCourseNo << " course number" << endl;

    }// end of if statement

    else
        cout << "student with ID: " << ID << " not found " << endl;
}

void searchStudents()
{
    int searchId, foundId=0;
    cout << "enter the student's ID" << endl;
    while(!(cin>>searchId))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "please, enter a valid input" << endl;
    }
    struct Student *Stemp_2 = std_start_ptr;
    //check if list is empty
    if(Stemp_2 == NULL)
    {
        cout << "Empty Student list!" << endl;
        return;
    }

    //navigate through the list to find the searched student and display the information if present
    cout << "result: " << endl;
    while(Stemp_2 != NULL)
    {
        if(Stemp_2->id == searchId)
        {
            int i=0;//index
           //display the list
           cout << endl;
           cout << "ID: " << Stemp_2->id << endl;
           cout << "first name: " << Stemp_2->fname << endl;
           cout << "last name: " << Stemp_2->lname << endl;
           cout << "age: " << Stemp_2->age << endl;
           cout << "sex: " << Stemp_2->sex << endl;
           //display all the registered course
           cout << "registered course Number " << setw(30) << "registered course grade " << endl;
           cout << "---------------------------------------------------------" << endl << endl;
           while(Stemp_2 ->reg_course[i].reg_courseNo!=0)
           {
                cout << Stemp_2 ->reg_course[i].reg_courseNo << setw(30) << Stemp_2 ->reg_course[i].grade << endl;
                i++;
           }
            return;
        }
        Stemp_2 = Stemp_2->snext;
    }//end of while loop

    //if course not found display a msg
    cout << "student with ID: " << searchId << " not found!" << endl;

}

void searchCourses()
{
    int searchCrsNo, foundCrs = 0;
    cout << "enter the course number" << endl;
    while(!(cin>>searchCrsNo))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "please, enter a valid input" << endl;
    }
    struct Course *Ctemp_2 = crs_start_ptr;
    //check if list is empty
    if(Ctemp_2 == NULL)
    {
        cout << "Empty Course list!" << endl;
        return;
    }

    //navigate through the list to find the searched course and display the information if present
    cout << "result: " << endl;
    while(Ctemp_2 != NULL)
    {
        if(Ctemp_2->courseNo == searchCrsNo)
        {
            //display the list of courses
           cout << endl;
           cout << "Course name: " << Ctemp_2->courseName << endl;
           cout << "Course number: " << Ctemp_2->courseNo << endl;
           cout << "Credit hour: " << Ctemp_2->creditHr << endl;
           return;

        }
        Ctemp_2 = Ctemp_2->cnext;
    }//end of while loop

    //if course not found display a msg
    cout << "Course with course number: " << searchCrsNo << " not found!" << endl;
}

void sortStudents()
{
    int i=0, n=0;//size of the list
    Student *smallest = NULL, *Stemp_2 = std_start_ptr, *temp = new Student;
    if(std_start_ptr == NULL)
    {

        cout << "Empty student list" << endl;
        return;
    }

    //determining the size of the list
    while(Stemp_2!=NULL)
    {
        Stemp_2 = Stemp_2->snext;
        n++;
    }

    Stemp = std_start_ptr;
    Stemp_2 = std_start_ptr;
    //sort the list
    while(i<n)
    {
        smallest = Stemp;
        Stemp_2 = Stemp->snext;
        while(Stemp_2!=NULL)
        {
            string name = Stemp_2->fname + Stemp_2->lname;
            string smallest_name = smallest->fname + smallest->lname;
            //change the names to lower case
            for(int i=0; i<name.length(); i++)
                name[i] = tolower(name[i]);

            for(int i=0; i<smallest_name.length(); i++)
                smallest_name[i] = tolower(smallest_name[i]);
            //make the node smallest by comparing their names
            if(smallest_name.compare(name) > 0)
                smallest = Stemp_2;
            Stemp_2 = Stemp_2->snext;
        }

        //swap the student info
        temp->id = Stemp->id;
        temp->age = Stemp->age;
        temp->fname = Stemp->fname;
        temp->lname = Stemp->lname;
        temp->sex = Stemp->sex;
        for(int i=0; i<50; i++)
        {
            temp->reg_course[i].grade = Stemp->reg_course[i].grade;
            temp->reg_course[i].reg_courseNo = Stemp->reg_course[i].reg_courseNo;
        }


        Stemp->id = smallest->id;
        Stemp->age = smallest->age;
        Stemp->fname = smallest->fname;
        Stemp->lname = smallest->lname;
        Stemp->sex = smallest->sex;
        for(int i=0; i<50; i++)
        {
            Stemp->reg_course[i].grade = smallest->reg_course[i].grade;
            Stemp->reg_course[i].reg_courseNo = smallest->reg_course[i].reg_courseNo;
        }


        smallest->id = temp->id;
        smallest->age = temp->age;
        smallest->fname = temp->fname;
        smallest->lname = temp->lname;
        smallest->sex = temp->sex;
        for(int i=0; i<50; i++)
        {
            smallest->reg_course[i].grade = temp->reg_course[i].grade;
            smallest->reg_course[i].reg_courseNo = temp->reg_course[i].reg_courseNo;
        }

        i++;
        Stemp = Stemp->snext;
    }//end of while loop

    cout << "successfully sorted!" << endl;

}

void displayStudents()
{
    struct Student *Stemp_2 = std_start_ptr;
    int i=0;//index

    //check if list is empty
    if(std_start_ptr == NULL)
    {

        cout << "Empty student list!" << endl;
        return;
    }

    //display the list
    while(Stemp_2 != NULL)
    {
       cout << endl;
       i = 0;//assign index to 0
       cout << "ID: " << Stemp_2->id << endl;
       cout << "first name: " << Stemp_2->fname << endl;
       cout << "last name: " << Stemp_2->lname << endl;
       cout << "age: " << Stemp_2->age << endl;
       cout << "sex: " << Stemp_2->sex << endl;
       //display all the registered course
       cout << "registered course Number " << setw(30) << "registered course grade " << endl;
       cout << "---------------------------------------------------------" << endl << endl;
       while(Stemp_2 ->reg_course[i].reg_courseNo!=0)
       {
            cout << Stemp_2 ->reg_course[i].reg_courseNo << setw(30) << Stemp_2 ->reg_course[i].grade << endl;
            i++;
       }
       Stemp_2 = Stemp_2->snext;
    }//end of while loop
}

void deleteStudents()
{
    cout << "enter the student id" << endl;
    int ID;
    while(!(cin>>ID))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "please, enter a valid input" << endl;
    }
    struct Student *Stemp_2 = std_start_ptr;
    //check if list is empty
    if(std_start_ptr == NULL)
    {
        cout << "Empty Student list" << endl;
        return;
    }

    //check list and if match found delete that student info
    Stemp = std_start_ptr;
    if(Stemp->snext == NULL)
    {
        if(ID == Stemp->id)
        {
            delete Stemp;
            std_start_ptr = NULL;
            cout << "student info deleted!" << endl;
            return;
        }
    }

    else
    {
        while(Stemp != NULL)
        {
            if(ID == Stemp->id)
            {
                if(Stemp == std_start_ptr)
                {
                    Stemp_2 = Stemp->snext;
                    delete Stemp;
                    std_start_ptr = Stemp_2;
                    cout << "student info deleted" << endl;
                    return;
                }
                else
                {
                    Stemp_2->snext = Stemp->snext;
                    delete Stemp;
                    cout << "student info deleted" << endl;
                    return;
                }

            }
            Stemp_2 = Stemp;
            Stemp = Stemp->snext;
        }
    }//end of else statement

    cout << "student with id: " << ID << " not found!" << endl;
}

void deleteCourses()
{
    cout << "enter the course number" << endl;
    int crNumber;
    while(!(cin>>crNumber))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "please, enter a valid input" << endl;
    }
    struct Course *Ctemp_2 = crs_start_ptr;
    struct Student *Stemp_2 = std_start_ptr;

    //check if list is empty
    if(crs_start_ptr == NULL)
    {
        cout << "Empty course list" << endl;
        return;
    }

    //check if list is empty
    bool iSEmpty = false;
    if(std_start_ptr == NULL)
        iSEmpty = true;

    //check list and if match found delete that student info
    Ctemp = crs_start_ptr;
    Stemp = std_start_ptr;
    if(Ctemp->cnext == NULL)
    {
        if(crNumber == Ctemp->courseNo)
        {
            //deleting the registered courses
            if(!iSEmpty)
            {
                while(Stemp != NULL)
                {
                    Reg_course *temp_reg_course = new Reg_course[50];
                    for(int i=0, j=0; i<50; i++)
                    {
                        if(Stemp->reg_course[i].reg_courseNo == crNumber)
                            continue;
                        temp_reg_course[j].reg_courseNo = Stemp->reg_course[i].reg_courseNo;
                        temp_reg_course[j].grade = Stemp->reg_course[i].grade;
                        j++;
                    }

                    for(int i=0; i<50; i++)
                    {
                        Stemp->reg_course[i].reg_courseNo = temp_reg_course[i].reg_courseNo;
                        Stemp->reg_course[i].grade = temp_reg_course[i].grade;
                    }
                    delete []temp_reg_course;
                    Stemp = Stemp->snext;
                }
            }//end of the most inner if statement

            //deleting the course
            delete Ctemp;
            crs_start_ptr = NULL;
            cout << "course info deleted!" << endl;
            return;
        }//end of inner if statement

    }//end of if statement

    else
    {
        //deleting the registered courses
        if(!iSEmpty)
        {
            while(Stemp != NULL)
            {
                Reg_course *temp_reg_course = new Reg_course[50];
                for(int i=0, j=0; i<50; i++)
                {
                    if(Stemp->reg_course[i].reg_courseNo == crNumber)
                    {
                        continue;
                    }
                    temp_reg_course[j].reg_courseNo = Stemp->reg_course[i].reg_courseNo;
                    temp_reg_course[j].grade = Stemp->reg_course[i].grade;
                    j++;
                }

                for(int i=0; i<50; i++)
                {
                    Stemp->reg_course[i].reg_courseNo = temp_reg_course[i].reg_courseNo;
                    Stemp->reg_course[i].grade = temp_reg_course[i].grade;
                }
                delete []temp_reg_course;
                Stemp = Stemp->snext;
            }//end of inner while loop

        }//end of inner if statement


        //deleting the course
        while(Ctemp != NULL)
        {
            if(crNumber == Ctemp->courseNo)
            {
                if(Ctemp == crs_start_ptr)
                {
                    Ctemp_2 = Ctemp->cnext;
                    delete Ctemp;
                    crs_start_ptr = Ctemp_2;
                    cout << "course info deleted" << endl;
                    return;
                }
                Ctemp_2->cnext = Ctemp->cnext;
                delete Ctemp;
                cout << "course info deleted" << endl;
                return;
            }
            Ctemp_2 = Ctemp;
            Ctemp = Ctemp->cnext;
        }//end of while loop

    }//end of the else statement
    cout << "course with course number: " << crNumber << " not found!" << endl;

}

void writeToFile()
{
    //write the info to the file
    Stemp = std_start_ptr;
    ofstream file("Student info.txt", ios::app);
    if(!file)
    {
        cout << "error, cannot open file!" << endl;
        return;
    }

    while(Stemp!=NULL)
    {
        file << "First_name: " << Stemp->fname << endl;
        file << "Last_name: " << Stemp->fname << endl;
        file << "ID: " << Stemp->fname << endl;
        file << "Age: " << Stemp->fname << endl;
        file << "Sex: " << Stemp->fname << endl;
        file << "Registered course: \tGrade" << endl;
        for(int i=0; Stemp->reg_course[i].reg_courseNo!=0; i++)
            file << "\t" << Stemp->reg_course[i].reg_courseNo << "\t\t" << Stemp->reg_course[i].grade << endl;
        file << endl << endl;;
        Stemp = Stemp->snext;
    }
    cout << "information added successfully!" << endl;
}
