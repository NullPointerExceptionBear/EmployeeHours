#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>


using namespace std;

class Employee
{
private:
    string empName;
    double payRate;
    double hrsWorked;
    time_t wrkrClkIn;
    time_t wrkrClkOut;
public:
    Employee()
    {
        empName = "Best Employee Ever";
        payRate = 1.00;
        hrsWorked = 0.0;
    }

    Employee(string empN, double pay)
    {
        empName = empN;
        payRate = pay;
    }

    Employee(string empN, double pay, time_t tmr)
    {
        empName = empN;
        payRate = pay;
        wrkrClkIn = tmr;
    }

    void SetName(string name)
    {
        empName = name;
    }

    void SetPay(double pay)
    {
        payRate = pay;
    }

    void SetTimeIn(time_t theTime)
    {
        wrkrClkIn = theTime;
    }

    void SetTimeOut(time_t daTime)
    {
        wrkrClkOut = daTime;
    }

    void SetHrsWrkd(double hrs)
    {
        hrsWorked = hrs;
    }

    string GetName()
    {
        return empName;
    }

    double GetPay()
    {
        return payRate;
    }

    time_t GetWrkTimeIn()
    {
        return wrkrClkIn;
    }

    time_t GetWrkTimeOut()
    {
        return wrkrClkOut;
    }

    double GetHrsWrkd()
    {
        return hrsWorked;
    }

};

void displayWorkers(Employee myArray[])
 {
     bool hasWrkrs = false;
     cout << "\n\n\tEmployee Name\t\tWage\n\n";
     for(int count = 0; count < 20; count++)
     {
         if(myArray[count].GetName() != "No Worker")
         {
             cout << setw(10) << (count + 1) << ".) " << myArray[count].GetName() << "\t\t$ " << setprecision(2)
                  << fixed << myArray[count].GetPay() << endl;
             hasWrkrs = true;
         }
         else if(hasWrkrs == false)
         {
             cout << "\n There are no employees to display." << endl;
             break;
         }
     }
 }

 void saveWorkerSheet(fstream &file, Employee myArray[])
 {
     file.open("workers.txt", ios::out);
     if(file.fail())
     {
         cout << "\nERROR: Workers file cannot be opened.\n";
     }
     else
     {
         for(int counter = 0; counter < 20; counter++)
         {
             file << myArray[counter].GetName() << " " << myArray[counter].GetPay() << endl;
         }
     }
 }

 void addWorker(fstream &file, Employee empArray[])
 {
     int index = 0;
     string input;
     string nome;
     double paper = 0.0;
     cout << "\nEnter Employee's Name: ";
     getline(cin, nome);
     cout << "\nEnter this worker's hourly rate: ";
     cin >> paper;

     Employee newWorker(nome, paper);
     for(int count = 0; count < 20;)
     {
         if(empArray[count].GetName() == "No Worker")
         {
             empArray[count] = newWorker;
             index = count;
             break;
         }
         else
         {
             count++;
         }
     }
     displayWorkers(empArray);

     cout << "\nDo you want to save these changes?\n Type Y or N: ";
     cin.ignore();
     cin.clear();
     getline(cin, input);
     while(input != "Y" && input != "N")
     {
         cin.ignore();
         cin.clear();
         cout << "\nInvalid input, please enter Y or N: ";
         getline(cin, input);
     }
     if(input == "Y")
     {
         saveWorkerSheet(file, empArray);
     }
     else if(input == "N")
     {
         cout << "\nVery well.\n";
         empArray[index].SetName("No Worker");
         empArray[index].SetPay(0.0);
     }
 }

 void kickWorker(fstream &file, Employee empArray[])
 {
     string input;
     Employee curEmployee;
     string nombre;
     string empNombre;
     cout << "Enter Employee to be deleted: ";
     //cin.ignore();
     cin.clear();
     getline(cin, nombre);
     for(int index = 0; index < 20; index++)
     {
         empNombre = empArray[index].GetName();
         if(empNombre == nombre)
         {
             empArray[index].SetName("No Worker");
             empArray[index].SetPay(0.0);
             cout << "\nEmployee has been terminated." << endl;
             break;
         }
         else if(index == 19 && empNombre != nombre)
         {
             cout << "\nEmployee not found." << endl;
         }
     }
     displayWorkers(empArray);

     cout << "\nDo you want to save these changes?\n Type Y or N: ";
     //cin.ignore();
     cin.clear();
     getline(cin, input);
     while(input != "Y" && input != "N")
     {
         cin.ignore();
         cin.clear();
         cout << "\nInvalid input, please enter Y or N: ";
         getline(cin, input);
     }
     if(input == "Y")
     {
         saveWorkerSheet(file, empArray);
     }
     else if(input == "N")
     {
         cout << "\nVery well.\n";
     }
 }

 void clearAll(fstream &file, Employee datArray[])
 {
     string choice = "";
     cout << "\nWARNING: This will delete all Employees on the file. Do you want to proceed?\nY or N: ";
     cin >> choice;
     while(choice != "Y" && choice != "N")
     {
         cout << "\nInvalid input, please enter Y or N: ";
         cin >> choice;
     }
     if(choice == "Y")
     {
        for(int count = 0; count < 20; count++)
        {
            datArray[count].SetName("No Worker");
            datArray[count].SetPay(0.0);
        }
        saveWorkerSheet(file, datArray);
        cout << "All Employees Cleared." << endl;
     }
     else if(choice == "N")
     {
         cout << "\n Okiee Dokiee." << endl;
     }
 }

 void wrkrClockIn(Employee wkArray[], time_t punchIn, bool pchIn[])
 {
     int empNum = 0;
     fstream dataOut;
     displayWorkers(wkArray);
     cout << "Choose employee: ";
     cin >> empNum;
      for(int count = 0; count < 20; count++)
     {
         if(pchIn[count] == true)
         {
             cout << "\nThis worker is already clocked in" << endl;
             break;
         }
         else if(pchIn[count] == false && empNum - 1 == count)
         {
             time(&punchIn);
             wkArray[count].SetTimeIn(punchIn);
             pchIn[count] = true;
             dataOut.open("times.txt", ios::out);
             for(int daCount = 0; daCount < 20; daCount++)
             {
                 dataOut << wkArray[daCount].GetWrkTimeIn() << " " << wkArray[daCount].GetWrkTimeOut() << " " << wkArray[daCount].GetHrsWrkd() << " " <<  pchIn[daCount] << endl;
             }
             dataOut.close();
             cout << "\n" << wkArray[count].GetName() << " has successfully clocked in at " << ctime(&punchIn) << endl;
             break;
         }
         else
         {
             cout << "\nError clocking in." << endl;
             break;
         }
     }
     displayWorkers(wkArray);
 }

 void wrkrClockOut(Employee wkArray[], time_t punchOut, bool pchIn[])
 {
     int empNum = 0;
     fstream dataOut;
     displayWorkers(wkArray);
     cout << "Choose employee: ";
     cin >> empNum;
      for(int count = 0; count < 20; count++)
     {
         if(pchIn[count] == false)
         {
             cout << "\nThis worker is already clocked out." << endl;
             break;
         }
         else if(pchIn[count] == true && empNum - 1 == count)
         {
             time(&punchOut);
             wkArray->SetTimeOut(punchOut);
             double hours = wkArray[count].GetHrsWrkd();
             double diff = 0.0;
             diff = difftime(punchOut, wkArray->GetWrkTimeIn());
             hours += diff;
             wkArray[count].SetHrsWrkd(hours);
             pchIn[count] = false;
             dataOut.open("times.txt", ios::out);
             for(int daCount = 0; daCount < 20; daCount++)
             {
                 dataOut << wkArray[daCount].GetWrkTimeIn() << " " << wkArray[daCount].GetWrkTimeOut() << " " << wkArray[daCount].GetHrsWrkd() << " " <<  pchIn[daCount] << endl;
             }
             dataOut.close();
             cout << endl << wkArray[count].GetName() << " has successfully clocked out at " << ctime(&punchOut) << endl;
             break;
         }
         else
         {
             cout << "\nError clocking out." << endl;
         }
     }
     displayWorkers(wkArray);
 }

 void showHrsWrkd(Employee pplArray[])
 {
     cout << "\n\tEmployee\t\tHours Worked" << endl << endl;
     for(int ctr = 0; ctr < 20; ctr++)
     {
         int sec = pplArray[ctr].GetHrsWrkd();
         int minutes = sec / 60;
         int hours = sec / 3600;
         if(hours >= 1.0)
         {
             for(int ct = 0; ct < hours; ct++)
             {
                    minutes %= 60;
             }
         }
         if(minutes >= 1.0)
         {
             for(int ct = 0; ct < minutes; ct++)
             {
                    sec %= 60;
             }
         }
         if(pplArray[ctr].GetName() != "No Worker")
         {
             cout << setw(10) << ctr + 1 << ".) " << pplArray[ctr].GetName() << "\t\t" << setprecision(0) << setw(3) << hours << " hrs " << minutes << " min " << sec << " sec " << endl;
         }
     }
 }

 void printSheet()
 {
     ofstream printer;
     printer.open("LPT1");
     if(printer.fail())
     {
         cout << "\n Couldn't get a hold of printer." << endl;
     }
     else
     printer << "Good Job.";
     printer.close();
 }

int main()
{
    fstream dataFile;
    time_t clockIn , clockOut, myTimeIn, myTimeOut;
    Employee wrkrArray[20];
    bool clkd[20];
    bool in_out;
    for(int count = 0; count < 20; count++)
    {
        wrkrArray[count].SetName("No Worker");
        wrkrArray[count].SetPay(0.0);
    }
    for(int count = 0; count < 20; count++)
    {
        clkd[count] = false;
    }



    string input ="";
    string empName = "";
    string fName= "";
    string lName = "";
    double pay = 0.0;
    double myHours = 0.0;


    dataFile.open("workers.txt", ios::in);
        if(dataFile.fail())
        {
            cout << "No data. Either the worker file has been corrupted or there is no file to read." << endl;
        }
        else
        {
            for(int counter = 0; counter < 20; counter++)
            {
                dataFile >> fName >> lName;
                if(lName.empty())
                {
                    empName = fName;
                }
                else
                {
                    empName += fName + " " + lName;
                }
                dataFile >> pay;
                wrkrArray[counter].SetName(empName);
                wrkrArray[counter].SetPay(pay);
                empName = "";
            }
            dataFile.close();
        }
        dataFile.open("times.txt", ios::in);
        if(dataFile.fail())
        {
            cout << "No data. Either the time file has been corrupted or there is no file to read." << endl;
        }
        else
        {
            for(int daCount = 0; daCount < 20; daCount++)
            {
                dataFile >> myTimeIn >> myTimeOut >> myHours >> in_out;
                wrkrArray[daCount].SetTimeIn(myTimeIn);
                wrkrArray[daCount].SetTimeOut(myTimeOut);
                wrkrArray[daCount].SetHrsWrkd(myHours);
                clkd[daCount] = in_out;
            }
        }
        dataFile.close();

    do
    {
        cout << "\n\tMain Menu\n -------------------------"
             << "\n 1.) Add Employee\n 2.) Delete Employee\n 3.) Display Workers\n"
             << " 4.) Clock In\n 5.) Clock Out\n 6.) Clear Employee List\n 7.) Print\n 8.) Quit\n" << endl;
        cin >> input;
        while(input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "6" && input != "7" && input != "8")
        {
            cout << "\nInvalid Entry. Please put select option: ";
            cin.ignore();
            cin.clear();
            cin >> input;
        }
        if(input == "1")
        {
            cin.ignore();
            cin.clear();
            addWorker(dataFile, wrkrArray);
        }
        else if(input == "2")
        {
            cin.ignore();
            cin.clear();
            kickWorker(dataFile, wrkrArray);
        }
        else if(input == "3")
        {
            cin.ignore();
            cin.clear();
            displayWorkers(wrkrArray);
            showHrsWrkd(wrkrArray);
        }
        else if(input == "4")
        {
            wrkrClockIn(wrkrArray, clockIn, clkd);
        }
        else if(input == "5")
        {
            wrkrClockOut(wrkrArray, clockOut, clkd);
        }
        else if(input == "6")
        {
            clearAll(dataFile, wrkrArray);
        }
        else if(input == "7")
        {
            printSheet();
        }

    }while(input != "8");

    return 0;
}

