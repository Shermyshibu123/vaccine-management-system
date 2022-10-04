#include "Hospital.h"
#include <string.h>
#include <fstream>
#include <regex>
#include <math.h>
#include <ctime>
Hospital::Hospital()
{
    CowinVaccine = 0;
    CovishieldVaccine = 0;
    TotalVaccine = 0;
    total = 0;
    delimiter = ";";
    pos = 0;
    idnamematch = false;
    idnumbermatch = false;
    namematch = false;
    numbermatch = false;
    choice = "";
    int getvaccine = 0;
    int samenumber = 0;
    bool vaccinedate = false;
    int sameidnumber = 0;
}
void Hospital::hospitalLogin() // For Hospital Login
{
    std::ifstream Hospitalfile("Hospitalfile.txt", std::ios::in);
    std::cout << "\n\n\t\tEnter HospitalId: ";
    std::cin >> HospitalId;
    int count = 0;
    while (getline(Hospitalfile, line5))
    {
        while ((pos = line5.find(delimiter)) != std::string::npos)
        {
            token = line5.substr(0, pos);
            if (token.rfind("Name ", 0) == 0)
            {
                existingHospitalname = token.substr(5);
            }
            if (token.rfind("Id ", 0) == 0)
            {
                Id = token.substr(3);

                if (HospitalId == Id)
                {
                    count++;
                    correspondingHospitalId = Id;
                    correspondingHospitalname = existingHospitalname;
                }
            }
            line5.erase(0, pos + delimiter.length());
        }
    }
    if (count > 0)
    {
        hospitalMain(correspondingHospitalId);
        count = 0;
    }
    else
    {
        std::cout << "\n\n\t\tInvalid Id!!!Try again.";
    }

    Hospitalfile.close();
}

void Hospital::hospitalMain(std::string correspondingHospitalId) // For getting Hospital Menu
{
    while (true)
    {
        std::string choice = " ";
        std::cout << "\n\n\t\t-->>HOSPITAL MENU<<--";
        std::cout << "\n\n\t\t1.Current stock of vaccine  \n\t\t2.Current user vaccination booking  \n\t\t3.Provide Vaccine to user"
                     "\n\t\t4.Request vaccine stock  \n\t\t5.Current vaccine done details \n\t\t6.Logout"
                  << std::endl;
        std::cout << "\n\n\t\tEnter your choice: ";
        std::cin >> choice;
        std::regex h("^[1-6]{1}$"); // only accepts one digit from 1 to 6
        if (std::regex_match(choice, h))
        {
            switch (std::stoi(choice))
            {
            case 1:
                viewCurrentStock();
                break;

            case 2:
                currentBookings();
                break;

            case 3:
                providingVaccine();
                break;

            case 4:
                requestVaccine();
                break;

            case 5:
                vaccinationDoneDetails(correspondingHospitalId);
                break;
            case 6:
                return;
                break;
            default:
                std::cout << "\n\n\t\tInvalid Choice!!!!!!";
                hospitalMain(correspondingHospitalId);
                break;
            }
        }
        else
        {
            std::cout << "\n\n\t\tInvalid input...";
        }
    }
}

void Hospital::viewCurrentStock() // To view or display the current vaccine stock of that particular hospital from Hospitalfile.txt
{
    std::ifstream Hospitalfile("Hospitalfile.txt");
    while (std::getline(Hospitalfile, line3))
    {
        while ((pos = line3.find(delimiter)) != std::string::npos)
        {
            token = line3.substr(0, pos);
            if (token.rfind("Id ", 0) == 0)
            {
                id = token.substr(3);
            }
            if (id == correspondingHospitalId)
            {
                if (token.rfind("Cowin ", 0) == 0)
                {
                    Cowinvaccine = token.substr(6);
                }
                if (token.rfind("Covishield ", 0) == 0)
                {
                    Covishieldvaccine = token.substr(11);
                }
                if (token.rfind("TotalVaccine ", 0) == 0)
                {
                    Totalvaccine = token.substr(13);
                }
            }
            line3.erase(0, pos + delimiter.length());
        }
    }
    std::cout << "\n\n\t\t-->>HOSPITAL STOCK<<--";
    std::cout << "\n\n\t\tCowin Stock: " << Cowinvaccine;
    std::cout << "\n\t\tCovishield Stock: " << Covishieldvaccine;
    std::cout << "\n\t\tTotal Stock: " << Totalvaccine << "\n\n";
    Hospitalfile.close();
}
void Hospital::currentBookings() // To display the current bookings for vaccine of that particular hospital from Bookingfile.txt file
{
    booking = false;
    std::ifstream InFile("Bookingfile.txt");
    while (std::getline(InFile, line))
    {
        booking = false;
        while ((pos = line.find(delimiter)) != std::string::npos)
        {
            token = line.substr(0, pos);
            if (token.rfind("Hospital ", 0) == 0)
            {
                Hospitalname = token.substr(9);
                if (correspondingHospitalname == Hospitalname)
                {
                    booking = true;
                }
               
            }
             if (token.rfind("Dose1 ", 0) == 0 && booking)
                {
                    Dose1 = token.substr(6);
                }
                if (token.rfind("Dose2 ", 0) == 0 && booking)
                {
                    Dose2 = token.substr(6);

                    
                        if (Dose1 == "Cowin" || Dose2 == "Cowin")
                        {
                            ++CowinVaccine;
                        }
                        else if((Dose1 == "Covishield" || Dose2 == "Covishield"))
                        {
                            ++CovishieldVaccine;
                        }
                    
                }

            line.erase(0, pos + delimiter.length());
        }
    }
    total = CowinVaccine + CovishieldVaccine;
    std::cout << "\n\n\t\tTotal Number of Booking: " << total;
    std::cout << "\n\n\t\tCowin Booking: " << CowinVaccine;
    std::cout << "\n\n\t\tCovishield Booking: " << CovishieldVaccine;
    total = 0;
    CowinVaccine = 0;
    CovishieldVaccine = 0;
    InFile.close();
}
void Hospital::requestVaccine() // Hospital making a request for a vaccine
{
    std::fstream requestfile;
    requestfile.open("request.txt", std::ios::app | std::ios::in);
    std::cout << "\n\t\tNumber of cowin vaccine Required: ";
    std::cin >> Cowinrequired;
    std::regex s("^[0-9]+$"); // only accepts numbers
    if (!std::regex_match(Cowinrequired, s))
    {
        std::cout << "\n\t\tInvalid input!!!";
        return;
    }
    requestfile << "HospitalId " << correspondingHospitalId << ";";
    requestfile << "CowinRequired " << Cowinrequired << ";";

    std::cout << "\t\tNumber of covishield vaccine Required: ";
    std::cin >> Covishieldrequired;
    std::regex c("^[0-9]+$"); // only accepts numbers
    if (!std::regex_match(Covishieldrequired, c))
    {
        std::cout << "\n\t\tInvalid input!!!";
        return;
    }
    requestfile << "CovishieldRequired " << Covishieldrequired << ";\n";
    std::cout << "\n\n\t\tVaccine stock requested.";
    requestfile.close();
    return;
}

void Hospital::providingVaccine() // To Provide Vaccines for Users who has booked from Bookingfile.txt file
{
    int samenumber = 0;
    bool vaccinedate = false;
    std::cout << "\n\t\tEnter patient name: ";
    std::cin >> patientname;
    std::regex n("^[a-zA-Z\\s]+$"); // Only accepts lower case letters,upper case letters and spaces
    if (!(std::regex_match(patientname, n)))
    {
        std::cout << "\n";
        std::cout << "\n\t\tInvalid Name! Please try again.\n";
        std::cout << "\n";
        return;
    }

    std::cout << "\t\tEnter patient phone number: ";
    std::cin >> Patientphonenumber;
    std::regex r("(0|91)?[6-9][0-9]{9}"); // Regular expression to match standard 10 digit phone number
    if (!std::regex_match(Patientphonenumber, r))
    {
        std::cout << "\n\t\tInvalid Phone number! Please try again.\n";
        return;
    }
    std::ifstream Providefile("Bookingfile.txt");

    while (std::getline(Providefile, line3))
    {
        numbermatch = false;
        namematch = false;

        while ((pos = line3.find(delimiter)) != std::string::npos)
        {
            token = line3.substr(0, pos);
            if (token.rfind("Name ", 0) == 0)
            {
                Patientname = token.substr(5);
                if (patientname == Patientname)
                {
                    namematch = true;
                }
            }

            if (token.rfind("PhoneNo ", 0) == 0 && namematch)
            {
                Phonenumber = token.substr(8);
                if (Phonenumber == Patientphonenumber)
                {
                    samenumber++;
                    numbermatch = true;
                }
            }

            if (token.rfind("Hospital ", 0) == 0 && numbermatch)
            {
                HospitalName = token.substr(9);
            }
            line3.erase(0, pos + delimiter.length());
        }
        if (numbermatch)
        {
            break;
        }
    }
    Providefile.close();
    if (samenumber > 0)
    {
        bool idMatch = false;
        std::ifstream vaccinedone("vaccinedone.txt");

        while (std::getline(vaccinedone, line3))
        {
            idnumbermatch = false;
            idMatch = false;
            while ((pos = line3.find(delimiter)) != std::string::npos)
            {
                token = line3.substr(0, pos);
                if (token.rfind("PhoneNo ", 0) == 0)
                {
                    phonenumber = token.substr(8);
                    if (phonenumber == Patientphonenumber)
                    {
                        idnumbermatch = true;
                    }
                }
                if (token.rfind("Dose2 ", 0) == 0 && idnumbermatch)
                {
                    Vaccine = token.substr(6);
                    if (Vaccine == "Cowin" || Vaccine == "Covishield")
                    {
                        idMatch = true;
                        vaccinedone.close();
                        std::cout << "\n\t\tAlready Approved";
                        return;
                    }
                }
                line3.erase(0, pos + delimiter.length());
            }
            if (idMatch)
            {
                vaccinedone.close();
                break;
            }
        }
        vaccinedone.close();
        if (!idMatch)
        {

            if (correspondingHospitalname == HospitalName)
            {
            
                std::cout << "\n\n\t\tApprove?(y/n): ";
                std::cin >> ch;
                if (ch == 'Y' || ch == 'y')
                {

                    std::ifstream in;
                    std::ofstream vaccinedone, tempfile;
                    in.open("Bookingfile.txt");
                    vaccinedone.open("vaccinedone.txt", std::ios::out | std::ios::app);

                    while (std::getline(in, line3))
                    {
                        originalLine = line3;
                        idnumbermatch = false;
                        idnamematch = false;
                        sameidnumber = 0;
                        while ((pos = line3.find(delimiter)) != std::string::npos)
                        {

                            token = line3.substr(0, pos);
                            if (token.rfind("Name ", 0) == 0)
                            {
                                std::string patientName = token.substr(5);
                                if (patientName == patientname)
                                {
                                    idnamematch = true;
                                }
                            }
                            if (token.rfind("PhoneNo ", 0) == 0 && idnamematch)
                            {
                                std::string phonenum = token.substr(8);
                                if (phonenum == Patientphonenumber)
                                {
                                    idnumbermatch = true;
                                    sameidnumber++;
                                }
                            }
                            if (token.rfind("Hospital ", 0) == 0 && idnumbermatch)
                            {
                                HospitalName = token.substr(9);
                            }
                            if (token.rfind("Pincode ", 0) == 0 && idnumbermatch)
                            {
                                Pincode = token.substr(8);
                            }
                            if (token.rfind("Dose1 ", 0) == 0 && idnumbermatch)
                            {
                                Dose1 = token.substr(6);
                            }
                            if (token.rfind("DateOfDose1 ", 0) == 0 && idnumbermatch)
                            {
                                Dateofvaccine = token.substr(12);
                            }
                            if (token.rfind("Dose2 ", 0) == 0 && idnumbermatch)
                            {
                                Vaccine = token.substr(6);
                            }
                            if (token.rfind("DateOfDose2 ", 0) == 0 && idnumbermatch)
                            {
                                DateofDose2 = token.substr(12);
                                tempfile.open("temp.txt", std::ios::app);
                                tempfile << "\nName " << patientname;
                                tempfile << ";PhoneNo " << Patientphonenumber;
                                tempfile << ";Pincode " << Pincode;
                                tempfile << ";Hospital " << HospitalName;
                                tempfile << ";Dose1 " << Dose1;
                                tempfile << ";DateOfDose1 " << Dateofvaccine;
                                tempfile << ";Dose2 " << Vaccine;
                                tempfile << ";DateOfDose2 " << DateofDose2 << ";\n";
                                tempfile.close();
                            }
                            line3.erase(0, pos + delimiter.length());
                        }
                        if (!idnamematch)
                        {
                            tempfile.open("temp.txt", std::ios::app);
                            tempfile << originalLine << "\n";
                            tempfile.close();
                        }
                    }
                    remove("vaccinedone.txt");
                    rename("temp.txt", "vaccinedone.txt");
                    std::cout << "\n\t\tvaccine approved\n";
                    vaccinedone.close();
                    in.close();
                }
                else if (ch == 'N' || ch == 'n')
                {
                    std::cout << "\n\t\tvaccine declined\n";
                    return;
                }
                else
                {
                    std::cout << "\n\t\tInvalid input!!!";
                    return;
                }
                return;
            }
            else
            {
                std::cout << "\n\t\tNo such booking!!!";
            }
        }
    }
    else
    {
        std::cout << "\n\t\tInvalid patientname or phone number";
    }
    return;
}
/** For getting Hospital Name with respect to Hospital ID
 *
 *  @param Id ID of Hospital used while Loging in
 */
std::string getHospitalName(std::string Id)
{
    std::fstream vaccinedone("Hospitalfile.txt");
    std::string line3, token, Name, hospitalName, id, delimiter = ";";
    size_t pos = 0;

    while (std::getline(vaccinedone, line3))
    {

        while ((pos = line3.find(delimiter)) != std::string::npos)
        {
            token = line3.substr(0, pos);
            if (token.rfind("Name ", 0) == 0)
            {
                Name = token.substr(5);
            }
            if (token.rfind("Id ", 0) == 0)
            {
                id = token.substr(3);

                if (id == Id)
                {

                    hospitalName = Name;

                    vaccinedone.close();
                    return hospitalName;
                }
            }

            line3.erase(0, pos + delimiter.length());
        }
    }
    vaccinedone.close();
    hospitalName = "";
    return hospitalName;
}
void Hospital::vaccinationDoneDetails(std::string Id) // To display current vaccine done details of that particular hospital from vacciedone.txt
{
    int getvaccine = 0;
    returnHospitalName = getHospitalName(Id);
    if (!(returnHospitalName == ""))
    {
        std::fstream vaccinedone("vaccinedone.txt");

        while (std::getline(vaccinedone, line3))
        {
            namematch = false;
            while ((pos = line3.find(delimiter)) != std::string::npos)
            {
                token = line3.substr(0, pos);
                if (token.rfind("Name ", 0) == 0)
                {
                    Name = token.substr(5);
                }
                if (token.rfind("PhoneNo ", 0) == 0)
                {
                    phonenumber = token.substr(8);
                }
                if (token.rfind("Hospital ", 0) == 0)
                {
                    infilehospitalname = token.substr(9);

                    if (infilehospitalname == returnHospitalName)
                    {
                        namematch = true;
                    }
                }
                if (token.rfind("Dose1 ", 0) == 0 && namematch)
                {
                    Dose1 = token.substr(6);
                }
                if (token.rfind("Dose2 ", 0) == 0 && namematch)
                {
                    Dose2 = token.substr(6);
                    getvaccine++;
                    std::cout << "\n\t\tName: " << Name;
                    std::cout << "  PhoneNo: " << phonenumber;
                    std::cout << "  Hospital: " << infilehospitalname;
                    std::cout << "  Dose1: " << Dose1;
                    std::cout << "  Dose2: " << Dose2 << "\n";
                }
                line3.erase(0, pos + delimiter.length());
            }
        }
        if (getvaccine == 0)
        {
            std::cout << "\n\t\tNo Details Found!\n";
            return;
        }
        vaccinedone.close();
        return;
    }
    else
    {
        std::cout << "No such Hospital!\n";
        return;
    }
}
