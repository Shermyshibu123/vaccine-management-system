#include "user.h"
#include <string.h>
#include <fstream> //For file operations
#include <regex>   //To create a regular expression object
#include <ctime>
User::User()
{
    ExistingMobileNumber = false;
    ExistingUserName = false;
    ExistingName = false;
    ExistingPassword = false;
    delimiter = ";";
    EqualUserName = 0;
    EqualPhoneNumber = 0;
    EqualHospitalName = 0;
    EqualPassword = 0;
    pos = 0;
    Vaccinechoice = "", choice = "";
    Dose = "";
}

/** To calculate age automatically from date of birth
 *
 *  @return age - string
 */
std::string User::calculateAge()
{
    std::time_t t = std::time(0);          // To get current time
    std::tm *now = std::localtime(&t);     // To get current Date using time
    int presentYear = now->tm_year + 1900; // current year
    int presentMonth = now->tm_mon + 1;    // current month
    int presentDay = now->tm_mday;         // current day
    if (year > presentYear)
    {
        std::cout << "\n";
        std::cout << "\t\tPlease enter valid date!\n";
        std::cout << "\n";
        age = "";
        return age;
    }
    else if ((year - presentYear) == 0)
    {
        if (presentMonth > month)
        {
            age = (std::to_string(presentMonth - month)) + " months";
            return age;
        }
        else if ((presentMonth < month))
        {
            std::cout << "\n";
            std::cout << "\t\tPlease enter valid date!\n";
            std::cout << "\n";
            age = "";
            return age;
        }
        else
        {
            if (presentDay > day)
            {
                age = (std::to_string(presentDay - day)) + " days";
                return age;
            }
            else
            {
                std::cout << "\n";
                std::cout << "\t\tPlease enter valid date!\n";
                std::cout << "\n";
                age = "";
                return age;
            }
        }
    }
    age = (std::to_string(presentYear - year)) + " years";
    return age;
}
// For registering new users that saved into userfile.txt
bool User::registerAccount()
{

    std::cout << "\n\t\t -->> REGISTRATION <<--";
    std::cout << "\n\n\t\tEnter the Name : ";
    std::getline(std::cin >> std::ws, name);
    std::regex n("^[a-zA-Z\\s]+$"); // Only accepts lower case letters,upper case letters and spaces
    if (!(std::regex_match(name, n)))
    {
        std::cout << "\n";
        std::cout << "\t\tInvalid input! Please try again.\n";
        std::cout << "\n";
        return false;
    }

    std::cout << "\t\tEnter Date Of Birth (DD/MM/YYYY):";
    const std::regex pattern("(((0[1-9]{1})|([1-3]{1}[0-9]{1}))/((0[1-9]{1})|(1[0-2]{1}))/(\\d{4}))"); // Accepts date of birth in the form dd/mm/yyyy
    std::getline(std::cin >> std::ws, dob);
    if (regex_match(dob, pattern))
    {
        dayInString = dob[0];                   // dayInString contains first character of DD/MM/YYYY
        dayInString = dayInString + dob[1];     // dayInString contains first 2 characters of string DD/MM/YYYY
        monthInString = dob[3];                 // monthInString contains fourth character of DD/MM/YYYY
        monthInString = monthInString + dob[4]; // monthInString contains fourth and fifth characters of string DD/MM/YYYY
        yearInString = dob[6];                  // yearInString contains seventh character of DD/MM/YYY
        yearInString = yearInString + dob[7];   // yearInString contains seventh and sixth characters of string DD/MM/YYYY
        yearInString = yearInString + dob[8];   // yearInString contains seventh sixth and eighth characters of string DD/MM/YYYY
        yearInString = yearInString + dob[9];   // yearInString contains seventh sixth eighth and ninth characters of string DD/MM/YYYY
        day = stoi(dayInString);                // day contains integer value of dayInString
        month = stoi(monthInString);            // month contains integer value of monthInString
        year = stoi(yearInString);              // year contains integer value of yearInString
        if (monthInString == "01" || monthInString == "03" || monthInString == "05" || monthInString == "07" || monthInString == "08" || monthInString == "10" || monthInString == "12")
        {
            if (day > 31)
            {
                std::cout << "\t\tEnter valid date!";
                return false;
            }
        }
        if (monthInString == "02")
        {
            if (!((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0) // checking leap year
            {
                if (day == 29)
                {
                    std::cout << "\t\tEnter valid date!";
                    return false;
                }
            }
            if (day > 30)
            {
                std::cout << "\t\tEnter valid date!";
                return false;
            }
        }
        if (monthInString == "04" || monthInString == "06" || monthInString == "09" || monthInString == "11")
        {
            if (day > 30)
            {
                std::cout << "\t\tEnter valid date!";
                return false;
            }
        }
        std::string age = calculateAge();
        if (age == "")
        {
            return false;
        }
    }
    else
    {
        std::cout << "\n";
        std::cout << "\t\tPlease enter valid DOB!\n";
        std::cout << "\n";
        return false;
    }
    std::cout << "\t\tAge: " << age << "\n";
    std::cout << "\t\tEnter Address : ";
    std::getline(std::cin >> std::ws, address);
    std::regex h("^[a-zA-Z\\s]+$"); // Only accepts lower case letters,upper case letters and spaces
    if (!(std::regex_match(address, h)))
    {
        std::cout << "\n";
        std::cout << "\n\t\tInvalid input!!! Please try again.\n";
        std::cout << "\n";
        return false;
    }
    std::cout << "\t\tEnter Phone number : ";
    std::cin >> phoneno;
    std::regex r("(0|91)?[6-9][0-9]{9}"); // Regular expression to match standard 10 digit phone number
    if (!std::regex_match(phoneno, r))
    {
        std::cout << "\n\t\tInvalid Phone number! Please try again.\n";
        return false;
    }
    else
    {
        std::fstream Userfile;
        Userfile.open("Userfile.txt");
        while (getline(Userfile, line))
        {
            while ((pos = line.find(delimiter)) != std::string::npos)
            {
                token = line.substr(0, pos);
                if (token.rfind("PhoneNo ", 0) == 0)
                {
                    phone = token.substr(8);
                    if (phone == phoneno)
                    {
                        EqualPhoneNumber++;
                    }
                }
                line.erase(0, pos + delimiter.length());
            }
        }
        if (EqualPhoneNumber > 0)
        {
            std::cout << "\n\t\tPhone number already exists!\n";
            EqualPhoneNumber = 0;
            return false;
        }
    }
    std::cout << "\t\tEnter Password: ";
    std::cin >> Password;
    std::cout << "\n\n\t\tSuccessfully Registered.\n";

    std::fstream Inputfile;
    Inputfile.open("Userfile.txt", std::ios::app);
    Inputfile << "\nName " << name << ";";
    Inputfile << "DOB " << day << "/" << month << "/" << year << ";";
    Inputfile << "Age " << age << ";";
    Inputfile << "Address " << address << ";";
    Inputfile << "PhoneNo " << phoneno << ";";
    Inputfile << "Password " << Password << ";";
    Inputfile.close();
    return true;
}
// For users,To Login into vaccine management using their Username and password from userfile.txt
void User::userLogin()
{
    std::ifstream Userfile("Userfile.txt");
    while (true)
    {
        std::cout << "\n\n\t\t -->> USER MENU <<--";
        std::cout << "\n\n\t\t1.Register ";
        std::cout << "\n\t\t2.Login";
        std::cout << "\n\t\t3.Back\n\n";
        std::cout << "\n\t\tEnter your choice: ";
        std::cin >> choice;
        std::regex u("^[1-3]{1}$"); // Only accepts one digit from 1-3
        if (std::regex_match(choice, u))
        {
            switch (std::stoi(choice))
            {
            case 1:
            {
                bool ret = registerAccount();
                if (ret == true)
                    break;
                else
                {
                    break;
                }
            }
            break;

            case 2:
            {
                std::cout << "\n\n\t\tEnter Your Mobile number: ";
                std::cin >> EnteredMobileNumber;
                std::cout << "\t\tEnter Your Password: ";
                std::cin >> EnteredPassword;

                while (std::getline(Userfile, line1))
                {
                    ExistingUserName = false;
                    ExistingPassword = false;
                    EqualPassword=0;
                    while ((pos = line1.find(delimiter)) != std::string::npos)
                    {
                        token = line1.substr(0, pos);
                        if (token.rfind("Name ", 0) == 0)
                        {
                            Name = token.substr(5);
                        }
                        if (token.rfind("PhoneNo ", 0) == 0)
                        {
                            phoneNo = token.substr(8);
                            if (EnteredMobileNumber == phoneNo)
                            {
                                ExistingUserName = true;
                            }
                        }
                        if (token.rfind("Password ", 0) == 0 && ExistingUserName)
                        {
                            Password = token.substr(9);

                            if (EnteredPassword == Password)
                            {
                                ExistingPassword = true;
                                EqualPassword++;
                                fileName = Name;
                                filephoneNo = phoneNo;
                            }
                        }

                        line1.erase(0, pos + delimiter.length());
                    }
                    if (ExistingPassword)
                    {
                        break;
                    }
                }
                Userfile.close();
                if (EqualPassword > 0)
                {
                    while (true)
                    {
                        std::cout << "\n\n\t\t-->> USER LOGIN<<--";
                        std::cout << "\n\n\t\t1.Vaccine booking\n\t\t2.Vaccination status\n\t\t3.Logout " << std::endl;
                        std::cout << "\n\n\t\tEnter your choice: ";
                        std::cin >> choice;
                        std::regex u("^[1-3]{1}$"); // Only accepts one digit from 1-3
                        if (std::regex_match(choice, u))
                        {
                            switch (std::stoi(choice)) // converting string to integer
                            {
                            case 1:
                                vaccineBooking(fileName, filephoneNo);
                                break;
                            case 2:
                                vaccinationStatus(filephoneNo);
                                break;
                            case 3:
                                return;
                            }
                        }
                        else
                        {
                            std::cout << "\n\t\tInvalid input!!!";
                        }
                    }
                }
                else
                {
                    EqualPassword = 0;
                    std::cout << "\n\t\tInvalid mobile number or Password";
                    return;
                }
            }
            break;
            case 3:
                return;
            default:
                std::cout << "\n\t\tInvalid choice!!";
                return;
            }
        }
        else
        {
            std::cout << "\n\t\tInvalid input!!!";
        }
    }
    return;
}
/** For booking vaccine (Dose 1,Dose 2)into Bookingfile.txt
 *
 *  @param fileName Name of user with respect to username
 *  @param filephoneNo User phone number
 */
void User::vaccineBooking(std::string fileName, std::string filephoneNo)
{
    int mobilecount = 0;
    bool existingphonenumber = false;
    std::string newphone;
    bool newfound = false;
    time_t tmNow;
    tmNow = time(NULL);
    struct tm t = *localtime(&tmNow); // For getting Date and Time
    std::string dayInString, monthInString, yearInString, date, Phone;
    std::fstream Infile("Hospitalfile.txt");
    SamePhoneNumber = 0;
    std::ifstream file;
    file.open("pincode.txt");
    std::ifstream Bookingfile;
    Bookingfile.open("Bookingfile.txt");
    while (std::getline(Bookingfile, line3))
    {
        while ((pos = line3.find(delimiter)) != std::string::npos)
        {
            token = line3.substr(0, pos);
            if (token.rfind("PhoneNo ", 0) == 0)
            {
                Phone = token.substr(8);
                if (Phone == filephoneNo)
                {
                    SamePhoneNumber++;
                }
            }

            line3.erase(0, pos + delimiter.length());
        }
    }
    Bookingfile.close();
    std::cout << "\n\t\tSelect any pincode: \n";
    while (std::getline(file, line2))
    {
        while ((pos = line2.find(delimiter)) != std::string::npos)
        {
            token = line2.substr(0, pos);
            if (token.rfind("Pincode ", 0) == 0)
            {
                Pincode = token.substr(8);
                std::cout << "\n\t\t" << Pincode << "\n";
            }
            line2.erase(0, pos + delimiter.length());
        }
    }
    file.close();
    std::fstream Hospitalfile("Hospitalfile.txt");
    std::cout << "\n\n\t\tEnter Pincode: ";
    std::cin >> EnteredPincode;
    std::fstream file2("pincode.txt");
    while (std::getline(file2, line2))
    {
        while ((pos = line2.find(delimiter)) != std::string::npos)
        {
            token = line2.substr(0, pos);

            if (token.rfind("Pincode ", 0) == 0)
            {
                PincodeFromFile = token.substr(8);
                if (PincodeFromFile == EnteredPincode)
                {
                    EqualPincode++;
                }
            }
            line2.erase(0, pos + delimiter.length());
        }
    }
    file2.close();
    if (EqualPincode == 0)
    {
        std::cout << "\n\t\tInvalid Pincode";
    }
    else
    {
        EqualPincode = 0;
        while (std::getline(Hospitalfile, line2))
        {
            while ((pos = line2.find(delimiter)) != std::string::npos)
            {
                token = line2.substr(0, pos);
                if (token.rfind("Name ", 0) == 0)
                {
                    HospitalName = token.substr(5);
                    fileHospitalName = HospitalName;
                    GetHospitalName = true;
                }
                if (token.rfind("Pincode ", 0) == 0 && GetHospitalName)
                {
                    filepincode = token.substr(8);
                    if (filepincode == EnteredPincode)
                    {
                        ExistingPincode = true;
                        std::cout << "\n\t\t"
                                  << "->" << fileHospitalName << "\t";
                    }
                }
                line2.erase(0, pos + delimiter.length());
            }
        }
        Hospitalfile.close();
        if (ExistingPincode)
        {
            std::cout << "\n\t\tChoose the Hospital from above: ";
            std::cout << "\n\n\t\tEnter Hospital name: ";
            std::cin >> EnteredHospital;
            EqualHospitalName = 0;
            std::fstream Hospitalfile("Hospitalfile.txt");
            while (std::getline(Hospitalfile, line2))
            {
                while ((pos = line2.find(delimiter)) != std::string::npos)
                {
                    token = line2.substr(0, pos);
                    if (token.rfind("Name ", 0) == 0)
                    {
                        HospitalName = token.substr(5);

                        if (HospitalName == EnteredHospital)
                        {
                            EqualHospitalName++;
                        }
                    }
                    line2.erase(0, pos + delimiter.length());
                }
            }
            if (EqualHospitalName > 0)
            {
                EqualHospitalName = 0;
                while (true)
                {
                    std::cout << "\n\n\t\tChoose Dose: \n\n\t\t1.Dose 1\n\t\t2.Dose 2\n\n\t\tEnter choice: ";
                    std::cin >> Dose;
                    std::regex s("^[1-2]{1}$");
                    if (std::regex_match(Dose, s))
                    {
                        switch (std::stoi(Dose))
                        {
                        case 1:
                        {
                            std::fstream Booking("Bookingfile.txt");
                            while (std::getline(Booking, line2))
                            {
                                existingphonenumber = false;
                                while ((pos = line2.find(delimiter)) != std::string::npos)
                                {
                                    token = line2.substr(0, pos);
                                    if (token.rfind("PhoneNo ", 0) == 0)
                                    {
                                        newphone = token.substr(8);
                                        if (newphone == filephoneNo)
                                        {
                                            existingphonenumber = true;
                                        }
                                    }
                                    if (token.rfind("Dose1 ", 0) == 0 && existingphonenumber)
                                    {
                                        Dose1 = token.substr(6);
                                        if (Dose1 == "Cowin" || Dose1 == "Covishield")
                                        {
                                            mobilecount++;
                                        }
                                    }
                                    line2.erase(0, pos + delimiter.length());
                                }
                                if (existingphonenumber)
                                {
                                    std::cout << "\n\t\tDose 1 already booked";
                                    break;
                                }
                            }
                            Booking.close();
                            if (!existingphonenumber)
                            {
                                mobilecount = 0;
                                std::cout << "\n\n\t\t1.Cowin \n\t\t2.Covishield";
                                std::cout << "\n\n\t\tEnter choice: ";
                                std::cin >> Vaccinechoice;
                                std::regex p("^[1-2]{1}$"); // Only accepts one digit 1 or 2
                                if (std::regex_match(Vaccinechoice, p))
                                {
                                    switch (std::stoi(Vaccinechoice))
                                    {
                                    case 1:
                                    {
                                        std::cout << "\n\n\t\tAvailable dates:\n "
                                                  << "\n\t\t" << t.tm_mday << "/0" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "\n";     //
                                        std::cout << "\n\t\t" << t.tm_mday + 1 << "/0" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "\n"; // For displaying dates
                                        std::cout << "\n\t\t" << t.tm_mday + 2 << "/0" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "\n"; //
                                        std::cout << "\n\t\tEnter Date from above(dd/mm/yyyy): ";
                                        const std::regex pattern("(((0[1-9]{1})|([1-3]{1}[0-9]{1}))/((0[1-9]{1})|(1[0-2]{1}))/(\\d{4}))"); // Accepts date of birth in the form dd/mm/yyyy
                                        std::getline(std::cin >> std::ws, date);
                                        if (regex_match(date, pattern))
                                        {
                                            dayInString = date[0];                   // dayInString contains first character of DD/MM/YYYY
                                            dayInString = dayInString + date[1];     // dayInString contains first 2 characters of string DD/MM/YYYY
                                            monthInString = date[3];                 // monthInString contains fourth character of DD/MM/YYYY
                                            monthInString = monthInString + date[4]; // monthInString contains fourth and fifth characters of string DD/MM/YYYY
                                            yearInString = date[6];                  // yearInString contains seventh character of DD/MM/YYY
                                            yearInString = yearInString + date[7];   // yearInString contains seventh and sixth characters of string DD/MM/YYYY
                                            yearInString = yearInString + date[8];   // yearInString contains seventh sixth and eighth characters of string DD/MM/YYYY
                                            yearInString = yearInString + date[9];   // yearInString contains seventh sixth eighth and ninth characters of string DD/MM/YYYY
                                            day = stoi(dayInString);                 // day contains integer value of dayInString
                                            month = stoi(monthInString);             // month contains integer value of monthInString
                                            year = stoi(yearInString);
                                            if ((day == t.tm_mday) && (month == t.tm_mon + 1) && (year == t.tm_year + 1900) || (day == t.tm_mday + 1) && (month == t.tm_mon + 1) && (year == t.tm_year + 1900) || (day == t.tm_mday + 2) && (month == t.tm_mon + 1) && (year == t.tm_year + 1900))
                                            {
                                                std::cout << "\n\n\t\tVaccine Booked successfully.";
                                                std::fstream Bookingfile("Bookingfile.txt", std::ios::app);
                                                Bookingfile << "\nName " << fileName;
                                                Bookingfile << ";PhoneNo " << filephoneNo;
                                                Bookingfile << ";Pincode " << EnteredPincode << ";";
                                                Bookingfile << "Hospital " << EnteredHospital << ";";
                                                Bookingfile << "Dose1 Cowin;";
                                                Bookingfile << "DateOfDose1 " << day << "/0" << month << "/" << year << ";";
                                                Bookingfile << "Dose2 0;";
                                                Bookingfile << "DateOfDose2 00/00/0000;\n";
                                                Bookingfile.close();
                                                return;
                                            }
                                            else
                                            {
                                                std::cout << "\n\t\tInvalid date!!!";
                                                return;
                                            }
                                        }
                                        else
                                        {
                                            std::cout << "\n\t\tInvalid date!!!";
                                            return;
                                        }
                                    }
                                    break;
                                    case 2:
                                    {
                                        std::cout << "\n\n\t\t-->>Available dates <<-- \n"
                                                  << "\n\t\t" << t.tm_mday << "/0" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "\n";
                                        std::cout << "\n\n\t\t" << t.tm_mday + 1 << "/0" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "\n";
                                        std::cout << "\n\n\t\t" << t.tm_mday + 2 << "/0" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "\n";
                                        std::cout << "\n\n\t\tEnter Date from above(dd/mm/yyyy): ";
                                        const std::regex pattern("(((0[1-9]{1})|([1-3]{1}[0-9]{1}))/((0[1-9]{1})|(1[0-2]{1}))/(\\d{4}))"); // Accepts date of birth in the form dd/mm/yyyy
                                        std::getline(std::cin >> std::ws, date);
                                        if (regex_match(date, pattern))
                                        {
                                            dayInString = date[0];                   // dayInString contains first character of DD/MM/YYYY
                                            dayInString = dayInString + date[1];     // dayInString contains first 2 characters of string DD/MM/YYYY
                                            monthInString = date[3];                 // monthInString contains fourth character of DD/MM/YYYY
                                            monthInString = monthInString + date[4]; // monthInString contains fourth and fifth characters of string DD/MM/YYYY
                                            yearInString = date[6];                  // yearInString contains seventh character of DD/MM/YYY
                                            yearInString = yearInString + date[7];   // yearInString contains seventh and sixth characters of string DD/MM/YYYY
                                            yearInString = yearInString + date[8];   // yearInString contains seventh sixth and eighth characters of string DD/MM/YYYY
                                            yearInString = yearInString + date[9];   // yearInString contains seventh sixth eighth and ninth characters of string DD/MM/YYYY
                                            day = stoi(dayInString);                 // day contains integer value of dayInString
                                            month = stoi(monthInString);             // month contains integer value of monthInString
                                            year = stoi(yearInString);
                                            if ((day == t.tm_mday) && (month == t.tm_mon + 1) && (year == t.tm_year + 1900) || (day == t.tm_mday + 1) && (month == t.tm_mon + 1) && (year == t.tm_year + 1900) || (day == t.tm_mday + 2) && (month == t.tm_mon + 1) && (year == t.tm_year + 1900))
                                            {
                                                std::cout << "\n\n\t\tVaccine Booked successfully.";
                                                std::fstream Bookingfile("Bookingfile.txt", std::ios::app);
                                                Bookingfile << "\nName " << fileName;
                                                Bookingfile << ";PhoneNo " << filephoneNo;
                                                Bookingfile << ";Pincode " << EnteredPincode << ";";
                                                Bookingfile << "Hospital " << EnteredHospital << ";";
                                                Bookingfile << "Dose1 Covishield;";
                                                Bookingfile << "DateOfDose1 " << day << "/0" << month << "/" << year << ";";
                                                Bookingfile << "Dose2 0;";
                                                Bookingfile << "DateOfDose2 00/00/0000;\n";
                                                Bookingfile.close();
                                                return;
                                            }
                                            else
                                            {
                                                std::cout << "\n\t\tInvalid date!!!";
                                                return;
                                            }
                                        }
                                        else
                                        {
                                            std::cout << "\n\t\tInvalid date!!!";
                                            return;
                                        }
                                    }

                                    break;
                                    default:
                                        std::cout << "\n\n\t\tInvalid choice...";
                                        return;
                                    }
                                }
                                else
                                {
                                    std::cout << "\n\t\tInvalid Input!!!";
                                }
                            }
                            else
                            {
                                return;
                            }
                        }
                        break;

                        case 2:
                        {
                            std::fstream Booking("Bookingfile.txt");
                            while (std::getline(Booking, line2))
                            {
                                existingphonenumber = false;mobilecount=0;
                                while ((pos = line2.find(delimiter)) != std::string::npos)
                                {
                                    token = line2.substr(0, pos);
                                    if (token.rfind("PhoneNo ", 0) == 0)
                                    {
                                        newphone = token.substr(8);
                                        if (newphone == filephoneNo)
                                        {
                                            existingphonenumber = true;
                                        }
                                    }
                                    if (token.rfind("Dose2 ", 0) == 0 && existingphonenumber)
                                    {
                                        Dose2 = token.substr(6);
                                        if (Dose2 == "Cowin" || Dose2 == "Covishield")
                                        {
                                            mobilecount++;
                                        }
                                    }
                                    line2.erase(0, pos + delimiter.length());
                                }
                                if(mobilecount>0)
                                {
                                    std::cout << "\n\t\tDose 2 already booked";
                                    return;
                                }
                            }
                            Booking.close();
                            if(mobilecount==0)
                            {
                            std::ifstream booking;
                            booking.open("vaccinedone.txt");
                            while (std::getline(booking, line2))
                            {
                                ExistingName = false;
                                while ((pos = line2.find(delimiter)) != std::string::npos)
                                {
                                    token = line2.substr(0, pos);
                                    if (token.rfind("Name ", 0) == 0)
                                    {
                                        name = token.substr(5);
                                    }
                                    if (name == fileName)
                                    {
                                        ExistingName = true;

                                        if (token.rfind("Dose1 ", 0) == 0 && ExistingName)
                                        {
                                            Dose1 = token.substr(6);
                                        }
                                        if (token.rfind("DateOfDose1 ", 0) == 0 && ExistingName)
                                        {
                                            DateOfDose1 = token.substr(12);
                                        }
                                    }
                                    line2.erase(0, pos + delimiter.length());
                                }
                            }
                            if (!ExistingName)
                            {
                                std::cout << "\n\t\tYou have not taken Dose 1!!!";
                                return;
                            }
                            else
                            {
                                std::ifstream booking1;
                                booking1.open("vaccinedone.txt");
                                while (std::getline(booking, line4))
                                {
                                    ExistingName = false;
                                    newfound = false;

                                    while ((pos = line4.find(delimiter)) != std::string::npos)
                                    {
                                        token = line4.substr(0, pos);
                                        if (token.rfind("Name ", 0) == 0)
                                        {
                                            name = token.substr(5);
                                        }
                                        if (name == fileName)
                                        {
                                            ExistingName = true;

                                            if (token.rfind("Dose2 ", 0) == 0 && ExistingName)
                                            {
                                                Dose2 = token.substr(6);
                                                if (Dose2 == "Cowin" || Dose2 == "Covishield")
                                                {
                                                    newfound = true;
                                                }
                                            }
                                            if (token.rfind("DateOfDose2 ", 0) == 0 && ExistingName)
                                            {
                                                DateOfDose2 = token.substr(12);
                                            }
                                        }
                                        line4.erase(0, pos + delimiter.length());
                                    }
                                }
                                if (newfound)
                                {
                                    std::cout << "\n\t\tYou have already taken both vaccines!!!";
                                    return;
                                }
                            }
                            dayVar = DateOfDose1[0];
                            dayVar = dayVar + DateOfDose1[1];
                            monthVar = DateOfDose1[3];
                            monthVar = monthVar + DateOfDose1[4];
                            yearVar = DateOfDose1[6];
                            yearVar = yearVar + DateOfDose1[7];
                            yearVar = yearVar + DateOfDose1[8];
                            yearVar = yearVar + DateOfDose1[9];

                            day = std::stoi(dayVar);     //
                            month = std::stoi(monthVar); // converting string to integer
                            year = std::stoi(yearVar);   //
                            const int monthDays[12] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
                            long int dayCount1 = (year * 365);
                            dayCount1 += monthDays[month];
                            dayCount1 += day; // For finding 60 days difference between dose1 date and dose2 date
                            long int dayCount2 = ((t.tm_year + 1900) * 365);
                            dayCount2 += monthDays[(t.tm_mon + 1)];
                            dayCount2 += t.tm_mday;
                            days = abs(dayCount2 - dayCount1);
                           
                            if (Dose1 == "Cowin" && days > 60)
                            {

                                std::cout << "\n\n\t\tAvailable dates:\n "
                                          << "\n\t\t" << t.tm_mday << "/0" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "\n";     //
                                std::cout << "\n\t\t" << t.tm_mday + 1 << "/0" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "\n"; // For displaying dates
                                std::cout << "\n\t\t" << t.tm_mday + 2 << "/0" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "\n"; //
                                std::cout << "\n\t\tEnter Date from above(dd/mm/yyyy): ";
                                const std::regex pattern("(((0[1-9]{1})|([1-3]{1}[0-9]{1}))/((0[1-9]{1})|(1[0-2]{1}))/(\\d{4}))"); // Accepts date of birth in the form dd/mm/yyyy
                                std::getline(std::cin >> std::ws, date);
                                if (regex_match(date, pattern))
                                {
                                    dayInString = date[0];                   // dayInString contains first character of DD/MM/YYYY
                                    dayInString = dayInString + date[1];     // dayInString contains first 2 characters of string DD/MM/YYYY
                                    monthInString = date[3];                 // monthInString contains fourth character of DD/MM/YYYY
                                    monthInString = monthInString + date[4]; // monthInString contains fourth and fifth characters of string DD/MM/YYYY
                                    yearInString = date[6];                  // yearInString contains seventh character of DD/MM/YYY
                                    yearInString = yearInString + date[7];   // yearInString contains seventh and sixth characters of string DD/MM/YYYY
                                    yearInString = yearInString + date[8];   // yearInString contains seventh sixth and eighth characters of string DD/MM/YYYY
                                    yearInString = yearInString + date[9];   // yearInString contains seventh sixth eighth and ninth characters of string DD/MM/YYYY
                                    day1 = stoi(dayInString);                // day contains integer value of dayInString
                                    month1 = stoi(monthInString);            // month contains integer value of monthInString
                                    year1 = stoi(yearInString);
                                    if ((day1 == t.tm_mday) && (month1 == t.tm_mon + 1) && (year1 == t.tm_year + 1900) || (day1 == t.tm_mday + 1) && (month1 == t.tm_mon + 1) && (year1 == t.tm_year + 1900) || (day1 == t.tm_mday + 2) && (month1 == t.tm_mon + 1) && (year1 == t.tm_year + 1900))
                                    {

                                        std::string originalLine;
                                        std::ofstream temp;
                                        temp.open("temp.txt", std::ios::app);
                                        std::fstream Bookingfile("Bookingfile.txt");
                                        while (std::getline(Bookingfile, line2))
                                        {
                                            originalLine = line2;
                                            existingphonenumber = false;
                                            while ((pos = line2.find(delimiter)) != std::string::npos)
                                            {
                                                token = line2.substr(0, pos);
                                                if (token.rfind("PhoneNo ", 0) == 0)
                                                {
                                                    newphone = token.substr(8);
                                                    if (newphone == filephoneNo)
                                                    {
                                                        existingphonenumber = true;
                                                    }
                                                }
                                                line2.erase(0, pos + delimiter.length());
                                            }
                                            if (existingphonenumber)
                                            {
                                                temp << "\nName " << fileName;
                                                temp << ";PhoneNo " << filephoneNo;
                                                temp << ";Pincode " << EnteredPincode << ";";
                                                temp << "Hospital " << EnteredHospital << ";";
                                                temp << "Dose1 Cowin;";
                                                temp << "DateOfDose1 " << DateOfDose1 << ";";
                                                temp << "Dose2 Cowin;";
                                                temp << "DateOfDose2 " << day1 << "/0" << month1 << "/" << year1 << ";";
                                            }
                                            else
                                            {
                                                temp << originalLine<<"\n";
                                            }
                                        }
                                        temp.close();
                                        Bookingfile.close();
                                        remove("Bookingfile.txt");
                                        rename("temp.txt", "Bookingfile.txt");
                                        std::cout << "\n\n\t\tCowin Vaccine Booked";
                                        return;
                                    }
                                        else
                                        {
                                            std::cout << "\n\t\tInvalid date!!!";
                                            return;
                                        }
                                    }
                                    else
                                    {
                                        std::cout << "\n\t\tInvalid date!!!";
                                        return;
                                    }
                                }
                                else if (Dose1 == "Covishield" && days > 60)
                                {
                                    std::cout << "\n\n\t\tAvailable dates:\n "
                                              << "\n\t\t" << t.tm_mday << "/0" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "\n";     //
                                    std::cout << "\n\t\t" << t.tm_mday + 1 << "/0" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "\n"; // For displaying dates
                                    std::cout << "\n\t\t" << t.tm_mday + 2 << "/0" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << "\n"; //
                                    std::cout << "\n\t\tEnter Date from above(dd/mm/yyyy): ";
                                    const std::regex pattern("(((0[1-9]{1})|([1-3]{1}[0-9]{1}))/((0[1-9]{1})|(1[0-2]{1}))/(\\d{4}))"); // Accepts date of birth in the form dd/mm/yyyy
                                    std::getline(std::cin >> std::ws, date);
                                    if (regex_match(date, pattern))
                                    {
                                        dayInString = date[0];                   // dayInString contains first character of DD/MM/YYYY
                                        dayInString = dayInString + date[1];     // dayInString contains first 2 characters of string DD/MM/YYYY
                                        monthInString = date[3];                 // monthInString contains fourth character of DD/MM/YYYY
                                        monthInString = monthInString + date[4]; // monthInString contains fourth and fifth characters of string DD/MM/YYYY
                                        yearInString = date[6];                  // yearInString contains seventh character of DD/MM/YYY
                                        yearInString = yearInString + date[7];   // yearInString contains seventh and sixth characters of string DD/MM/YYYY
                                        yearInString = yearInString + date[8];   // yearInString contains seventh sixth and eighth characters of string DD/MM/YYYY
                                        yearInString = yearInString + date[9];   // yearInString contains seventh sixth eighth and ninth characters of string DD/MM/YYYY
                                        day2 = stoi(dayInString);                // day contains integer value of dayInString
                                        month2 = stoi(monthInString);            // month contains integer value of monthInString
                                        year2 = stoi(yearInString);
                                        if ((day2 == t.tm_mday) && (month2 == t.tm_mon + 1) && (year2 == t.tm_year + 1900) || (day2 == t.tm_mday + 1) && (month2 == t.tm_mon + 1) && (year2 == t.tm_year + 1900) || (day2 == t.tm_mday + 2) && (month2 == t.tm_mon + 1) && (year2 == t.tm_year + 1900))
                                        {
                                            std::string originalLine;
                                        std::ofstream temp1;
                                        temp1.open("temp.txt", std::ios::app);
                                        std::fstream Bookingfile("Bookingfile.txt");
                                        while (std::getline(Bookingfile, line2))
                                        {
                                            originalLine = line2;
                                            existingphonenumber = false;
                                            while ((pos = line2.find(delimiter)) != std::string::npos)
                                            {
                                                token = line2.substr(0, pos);
                                                if (token.rfind("PhoneNo ", 0) == 0)
                                                {
                                                    newphone = token.substr(8);
                                                    if (newphone == filephoneNo)
                                                    {
                                                        existingphonenumber = true;
                                                    }
                                                }
                                                line2.erase(0, pos + delimiter.length());
                                            }
                                            if (existingphonenumber)
                                            {
                                            temp1 << "\nName " << fileName;
                                            temp1 << ";PhoneNo " << filephoneNo;
                                            temp1 << ";Pincode " << EnteredPincode << ";";
                                            temp1 << "Hospital " << EnteredHospital << ";";
                                            temp1 << "Dose1 Covishield;";
                                            temp1 << "DateOfDose1 " << DateOfDose1 << ";";
                                            temp1 << "Dose2 Covishield;";
                                            temp1 << "DateOfDose2 " << day2 << "/0" << month2 << "/" << year2 << ";";
                                            }
                                            else
                                            {
                                                temp1 << originalLine<<"\n";
                                            }
                                        }
                                        temp1.close();
                                        Bookingfile.close();
                                        remove("Bookingfile.txt");
                                        rename("temp.txt", "Bookingfile.txt");
                                        std::cout << "\n\n\t\tCowin Vaccine Booked";
                                        return;
                                    }
                                        else
                                        {
                                            std::cout << "\n\t\tInvalid date!!!";
                                            return;
                                        }
                                    }
                                    else
                                    {
                                        std::cout << "\n\t\tInvalid date!!!";
                                        return;
                                    }
                                }
                                else
                                {
                                    std::cout << "\n\n\t\tNot eligible for Dose 2";
                                    return;
                                }
                                booking.close();
                                // }

                                //    }
                            }
                        }
                            break;
                        default:
                            std::cout << "\n\n\t\tInvalid choice!!!";
                        }
                        }
                        else
                        {
                            std::cout << "\n\t\tInvalid choice!!!";
                            return;
                        }
                    }
                }
                else
                {
                    std::cout << "\n\t\tWrong Hospital Name!!!\n\n";
                }
            }
            else
            {
                std::cout << "\n\t\tNo Hospital Exist In This Pincode\n\n";
            }
        }
    }
    // For printing vaccination status
    void User::vaccinationStatus(std::string filephoneNo)
    {
        EqualPhoneNumber = 0;
        found = false;
        count = 0;
        count2 = 0;
        count3 = 0;
        Dose1found = false;
        Dose2found = false;
        std::ifstream Donefile("vaccinedone.txt");
        while (std::getline(Donefile, line3))
        {

            found = false;
            while ((pos = line3.find(delimiter)) != std::string::npos)
            {
                token = line3.substr(0, pos);
                if (token.rfind("PhoneNo ", 0) == 0)
                {
                    newphone1 = token.substr(8);
                    if (newphone1 == filephoneNo)
                    {
                        found = true;
                    }
                }
                if (token.rfind("Dose1 ", 0) == 0 && found)
                {
                    Dose1 = token.substr(6);
                    if (Dose1 == "Cowin" || Dose1 == "Covishield")
                    {
                        count++;
                    }
                }
                if (token.rfind("Dose2 ", 0) == 0 && found)
                {
                    Dose2 = token.substr(6);
                    if (Dose2 == Dose1)
                    {
                        count2++;
                    }
                }
                line3.erase(0, pos + delimiter.length());
            }
            if (found)
            {
                break;
            }
        }
        Donefile.close();
        if (count2 > 0)
        {
            std::cout << "\n\t\tDose 1: Completed";
            std::cout << "\n\t\tDose 2: Completed";
            std::ifstream Userfile1;
            Userfile1.open("vaccinedone.txt");
            while (std::getline(Userfile1, line5))
            {
                ExistingMobileNumber = false;
                EqualPhoneNumber = 0;
                Dose1found = false;
                Dose2found = false;
                while ((pos = line5.find(delimiter)) != std::string::npos)
                {
                    token = line5.substr(0, pos);
                    if (token.rfind("Name ", 0) == 0)
                    {
                        name = token.substr(5);
                    }
                    if (token.rfind("PhoneNo ", 0) == 0)
                    {
                        phoneNo = token.substr(8);
                        if (phoneNo == filephoneNo)
                        {
                            ExistingMobileNumber = true;
                            EqualPhoneNumber++;
                            PatientName = name;
                        }
                    }
                    if (token.rfind("Dose1 ", 0) == 0 && ExistingMobileNumber)
                    {
                        Dose1 = token.substr(6);
                        Dose1found = true;
                    }
                    if (token.rfind("DateOfDose1 ", 0) == 0 && ExistingMobileNumber)
                    {
                        DateOfDose1 = token.substr(12);
                    }
                    if (token.rfind("Dose2 ", 0) == 0 && ExistingMobileNumber)
                    {
                        Dose2 = token.substr(6);
                    }
                    if (token.rfind("DateOfDose2 ", 0) == 0 && ExistingMobileNumber)
                    {
                        DateOfDose2 = token.substr(12);
                    }

                    line5.erase(0, pos + delimiter.length());
                }
                if (ExistingMobileNumber)
                {
                    break;
                }
            }
            Userfile1.close();
            if (ExistingMobileNumber)
            {
                std::cout << "\n\t\tDo you want to print certificate: (y/n) ";
                std::cin >> Choice;
                if (Choice == 'y' || Choice == 'Y')
                {
                    std::cout << "\n\t\t****************************";
                    std::cout << "\n\t\t    Certificate";
                    std::cout << "\n\n\t\t Name: " << PatientName;
                    std::cout << "\n\t\t Dose1: " << Dose1;
                    std::cout << "\n\t\t Date of Dose1: " << DateOfDose1;
                    std::cout << "\n\t\t Dose2: " << Dose2;
                    std::cout << "\n\t\t Date of Dose2: " << DateOfDose2;
                    std::cout << "\n\n\t\t****************************";
                    return;
                }
                else
                {
                    std::cout << "\n\n\t\tThank you for using Vaccine Management System";
                    return;
                }
            }

            std::fstream Booking("Bookingfile.txt");
            while (std::getline(Booking, line2))
            {
                found = false;
                count = 0;
                while ((pos = line2.find(delimiter)) != std::string::npos)
                {
                    token = line2.substr(0, pos);
                    if (token.rfind("PhoneNo ", 0) == 0)
                    {
                        newphone1 = token.substr(8);
                        if (newphone1 == filephoneNo)
                        {
                            found = true;
                        }
                    }
                    if (token.rfind("Dose2 ", 0) == 0 && found)
                    {
                        Dose2 = token.substr(6);
                        if (Dose2 == "Cowin" || Dose2 == "Covishield")
                        {
                            count++;
                        }
                    }
                    line2.erase(0, pos + delimiter.length());
                }
                if (found)
                {
                    break;
                }
            }
            if (count > 0)
            {
                std::cout << "Dose 1 : Completed\n";
                std::cout << "Dose 2 : Booked";

                Booking.close();
                return;
            }
            else
            {
                std::cout << "Dose 1 :Completed\n";
                std::cout << "Dose 2 :Not Booked";

                Booking.close();
                return;
            }
        }
        else if (count > 0 && count2 == 0)
        {
            std::cout << "\n\t\tDose 1: Completed\n";
            std::cout << "\n\t\tDose 2: Not Completed";
            std::ifstream Userfile;
            Userfile.open("vaccinedone.txt");
            while (std::getline(Userfile, line3))
            {
                ExistingMobileNumber = false;
                EqualPhoneNumber = 0;
                Dose1found = false;
                Dose2found = false;
                while ((pos = line3.find(delimiter)) != std::string::npos)
                {
                    token = line3.substr(0, pos);
                    if (token.rfind("Name ", 0) == 0)
                    {
                        name = token.substr(5);
                    }
                    if (token.rfind("PhoneNo ", 0) == 0)
                    {
                        phoneNo = token.substr(8);
                        if (phoneNo == filephoneNo)
                        {
                            ExistingMobileNumber = true;
                            EqualPhoneNumber++;
                            PatientName = name;
                        }
                    }
                    if (token.rfind("Hospital ", 0) == 0 && ExistingMobileNumber)
                    {
                        HospitalName = token.substr(9);
                    }
                    if (token.rfind("Dose1 ", 0) == 0 && ExistingMobileNumber)
                    {
                        Dose1 = token.substr(6);
                    }
                    if (token.rfind("DateOfDose1 ", 0) == 0 && ExistingMobileNumber)
                    {
                        DateOfDose1 = token.substr(12);
                    }

                    line3.erase(0, pos + delimiter.length());
                }
                if (ExistingMobileNumber)
                {
                    break;
                }
            }
            Userfile.close();
            if (ExistingMobileNumber)
            {
                std::cout << "\n\t\tDo you want to print certificate: (y/n) ";
                std::cin >> Choice;
                if (Choice == 'y' || Choice == 'Y')
                {
                    std::cout << "\n\t\t****************************";
                    std::cout << "\n\t\t    Certificate";
                    std::cout << "\n\n\t\t Name: " << PatientName;
                    std::cout << "\n\t\t Dose1: " << Dose1;
                    std::cout << "\n\t\t Date of Dose1: " << DateOfDose1;
                    std::cout << "\n\t\t Dose2: Nil";
                    std::cout << "\n\t\t Date of Dose2: Nil";
                    std::cout << "\n\n\t\t****************************";
                    return;
                }
                else
                {
                    std::cout << "\n\n\t\tThank you for using Vaccine Management System";
                    return;
                }
            }
        }
        else
        {
            std::fstream Booking("Bookingfile.txt");
            while (std::getline(Booking, line2))
            {
                found = false;
                count = 0;
                count3 = 0;
                while ((pos = line2.find(delimiter)) != std::string::npos)
                {
                    token = line2.substr(0, pos);
                    if (token.rfind("PhoneNo ", 0) == 0)
                    {
                        newphone1 = token.substr(8);
                        if (newphone1 == filephoneNo)
                        {
                            found = true;
                        }
                    }
                    if (token.rfind("Dose1 ", 0) == 0 && found)
                    {
                        Dose1 = token.substr(6);
                        if (Dose1 == "Cowin" || Dose1 == "Covishield")
                        {
                            count++;
                        }
                    }
                    line2.erase(0, pos + delimiter.length());
                }
                if (found)
                {
                    break;
                }
            }
            if (count > 0)
            {
                std::cout << "\n\t\tDose 1 : Booked\n";
                std::cout << "\n\t\tDose 2 : Not Booked";

                Booking.close();
                return;
            }
            else
            {
                count = 0;
                std::cout << "\n\t\tDose 1 :Not Booked\n";
                std::cout << "\n\t\tDose 2 :Not Booked";
                Booking.close();
                return;
            }
        }

    }
