#include "Admin.h"
#include <string.h>
#include <fstream>
#include <regex>
#include <ctime>
int idGenerate()//For autogenerating Hospital ID
{
    int id;
    srand(time(0));//srand() initialize random number generators
    id = rand();//generate random numbers
    return id;
}
Admin::Admin()
{
    admin_choice = "";
    VaccineChoice = "";
    delimiter = ";";
    sameid = false;
    pos = 0;
    idfound = false;
}
void Admin::adminLogin()//For admin login
{
    std::cout << "\n\t\t\t\t*****************************************";
    std::cout << "\n\t\t\t\t   *    VACCINE MANAGEMENT SYSTEM    *";
    std::cout << "\n\t\t\t\t*****************************************";
    std::cout << "\n\n\t\t -->> ADMIN LOGIN <<--\n";
    std::cout << "\n\t\tEnter Your Password: ";
    std::cin >> adminpassword;

    if (strcmp(adminpassword, "1234567") == 0)
    {
        std::cout << "\n\n\n\t\n\t\t\t| Verfiying ADMIN |\n\t\t\t\t\t";

        std::cout << "\n\n\t\tAccess Granted..\n\n";
        adminMain();
    }
    else
    {
        std::cout << "\n\n\n\t\t\t\t\t| Verfiying ADMIN |\n\t\t\t\t\t";

        std::cout << "\n\n\t\tAccess Aborted...Try again!!!\n\n";
        return;
    }
}

void Admin::adminMain()//For getting admin menu
{
    std::cout << "\n\t\t\t\t*****************************************";
    std::cout << "\n\t\t\t\t   *    VACCINE MANAGEMENT SYSTEM    *";
    std::cout << "\n\t\t\t\t*****************************************";

    while (true)
    {
        std::cout << "\n\n\t\t -->> ADMIN MENU <<--";
        std::cout << "\n\n\t\t 1. Add Hospitals";
        std::cout << "\n\t\t 2. Add Vaccine stock";
        std::cout << "\n\t\t 3. Show Vaccine Stock";
        std::cout << "\n\t\t 4. Approve vaccine request";
        std::cout << "\n\t\t 5. Logout ";
        std::cout << "\n\n\t\tEnter your choice: ";
        std::cin >> admin_choice;
        std::regex s("^[1-5]{1}$");// only accepts one digit from 1 to 5
        if (std::regex_match(admin_choice, s))
        {
            switch (std::stoi(admin_choice))
            {
            case 1:
                addHospital();
                break;
            case 2:
                addVaccine();
                break;
            case 3:
                displayVaccine();
                break;
            case 4:
                approveVaccineRequest();
                break;
            case 5:
                return;
            }
        }
        else
        {
            std::cout << "\n\n\t\tInvalid input...Please try again...!!!";
        }
    }
    return;
}

//To enter hospital details and storing it in Hospitalfile.txt file
void Admin::addHospital()
{
    int checkingpincode=0;
    std::cout << "\n\n\t\t-->> HOSPITAL DETAILS <<--" << std::endl;
    std::cout << "\n\t\tEnter the Hospital Name: ";
    std::getline(std::cin >> std::ws, HospitalName);
    std::regex n("^[a-zA-Z\\s]+$");// Only accepts lower case letters,upper case letters and spaces
    if (!(std::regex_match(HospitalName, n)))
    {
        std::cout << "\n";
        std::cout << "\t\tInvalid Hospital Name! Please try again.\n";
        std::cout << "\n";
        return;
    }
    std::cout << "\t\tID of the Hospital: H#" << idGenerate();
    HospitalId = idGenerate();
    std::cout << "\n\t\tEnter the Hospital Address: ";
    std::getline(std::cin >> std::ws, HospitalAddress);
    std::regex h("^[a-zA-Z\\s]+$");// Only accepts lower case letters,upper case letters and spaces
    if (!(std::regex_match(HospitalAddress, h)))
    {
        std::cout << "\n";
        std::cout << "\t\tInvalid Hospital Address! Please try again.\n";
        std::cout << "\n";
        return;
    }
    std::cout << "\t\tEnter the Pincode: ";
    std::cin >> HospitalPincode;
    std::regex p("^[1-9]{1}[0-9]{5}$");// Regex to check valid pin code of India.
    if (!(std::regex_match(HospitalPincode, p)))
    {
        std::cout << "\n";
        std::cout << "\t\tInvalid Hospital Pincode! Please try again.\n";
        std::cout << "\n";
        return;
    }
    std::regex x("^[0-9]+$");// only accepts numbers 
    std::cout << "\t\tNumber of Cowin Vaccines: ";
    std::getline(std::cin >> std::ws, HospitalCowin);
    if (!(std::regex_match(HospitalCowin, x)))
    {
        std::cout << "\n";
        std::cout << "\t\tInvalid Format! Accepts only numbers ! Please try again.\n";
        std::cout << "\n";
        return;
    }
    int cowinnumber = stoi(HospitalCowin);
    std::cout << "\t\tNumber of Covishield Vaccines: ";
    std::cin >> HospitalCovishield;
    std::regex y("^[0-9]+$");// only accepts numbers 
    if (!(std::regex_match(HospitalCovishield, y)))
    {
        std::cout << "\n";
        std::cout << "\t\tInvalid Format! Accepts only numbers ! Please try again.\n";
        std::cout << "\n";
        return;
    }
    int covishieldnumber = stoi(HospitalCovishield);
    std::cout << "\t\tNumber of Vaccines alloted for the Hospital: ";
    HospitalVaccines = cowinnumber + covishieldnumber;
    std::cout << HospitalVaccines << "\n";
    std::cout << "\n\n\t\tHospital details Added into file."
              << "\n";
    std::ofstream HospitalFile;
    HospitalFile.open("Hospitalfile.txt", std::ios::out | std::ios::app);
    HospitalFile << "\nName " << HospitalName << ";";
    HospitalFile << "Id "
                 << "H#" << HospitalId << ";";
    HospitalFile << "Address " << HospitalAddress << ";";
    HospitalFile << "Pincode " << HospitalPincode << ";";
    HospitalFile << "Cowin " << HospitalCowin << ";";
    HospitalFile << "Covishield " << HospitalCovishield << ";";
    HospitalFile << "TotalVaccine " << HospitalVaccines << ";";
    std::ifstream file;
   //for storing pincodes of different hospitals in pincode.txt file
    file.open("pincode.txt");
     while (std::getline(file, line))
                {
                    while ((pos = line.find(delimiter)) != std::string::npos)
                    {
                        token = line.substr(0, pos);
                        if (token.rfind("Pincode ", 0) == 0)
                        {
                            Pincode = token.substr(8);
                            if((Pincode==HospitalPincode))
                            {
                                checkingpincode++;
                            }
                        }

                        
                        line.erase(0, pos + delimiter.length());
                    }
                }
                 file.close();
               
                if(checkingpincode==0)
                {
                     std::ofstream ofile;
   
    ofile.open("pincode.txt",std::ios::app);
               
                    ofile<<"Pincode "<<HospitalPincode<<";\n";
                    ofile.close();
                }
               
    HospitalFile.close();
}
//To add total vaccine stock for cowin and covishield by admin.
void Admin::addVaccine()
{

    while (true)
    {
        std::cout << "\n\n\t\t-->> Name of vaccine <<-- \n\n\t\t1.Cowin\n\t\t2.Covishield \n\t\t3.Back";
        std::cout << "\n\n\t\tEnter choice: ";
        std::cin >> VaccineChoice;
        std::regex s("^[1-3]{1}$");// only accepts one digit from 1 to 3
        if (std::regex_match(VaccineChoice, s))
        {
            switch (std::stoi(VaccineChoice))
            {
            case 1:
            {
                std::fstream Adminfile;
                Adminfile.open("Adminfile.txt");
                while (std::getline(Adminfile, line))
                {
                    while ((pos = line.find(delimiter)) != std::string::npos)
                    {
                        token = line.substr(0, pos);
                        if (token.rfind("Cowin ", 0) == 0)
                        {
                            Cowin = token.substr(6);
                        }
                        if (token.rfind("Covishield ", 0) == 0)
                        {
                            Covishield = token.substr(11);
                        }

                        line.erase(0, pos + delimiter.length());
                    }
                }
                Adminfile.close();
                std::cout << "\n\n\t\tNumber of cowin vaccine: ";
                std::cin >> CowinStock;
                std::regex q("^[0-9]+$");// only accepts numbers 
                if (std::regex_match(CowinStock, q))
                {
                    std::ofstream temp;

                    temp.open("temp.txt");
                    temp << "Cowin " << std::stoi(Cowin) + std::stoi(CowinStock);
                    temp << ";Covishield " << Covishield << ";\n";
                    temp.close();
                    remove("Adminfile.txt");
                    rename("temp.txt", "Adminfile.txt");
                    std::cout << "\n\n\t\tVaccine stock added.\n\n";
                    break;
                }
                else
                {
                    std::cout << "\n\t\tInvalid input!!!";
                    break;
                }
            }
            break;
            case 2:
            {
                std::fstream Adminfile;
                Adminfile.open("Adminfile.txt");
                while (std::getline(Adminfile, line))
                {
                    while ((pos = line.find(delimiter)) != std::string::npos)
                    {
                        token = line.substr(0, pos);
                        if (token.rfind("Cowin ", 0) == 0)
                        {
                            Cowin = token.substr(6);
                        }
                        if (token.rfind("Covishield ", 0) == 0)
                        {
                            Covishield = token.substr(11);
                        }

                        line.erase(0, pos + delimiter.length());
                    }
                }
                Adminfile.close();
                std::cout << "\n\n\t\tNumber of covishield vaccine: ";
                std::cin >> CovishieldStock;
                std::regex s("^[0-9]+$");// only accepts numbers 
                if (std::regex_match(CovishieldStock, s))
                {
                    std::ofstream temp;
                    temp.open("temp.txt");
                    temp << "Cowin " << Cowin;
                    temp << ";Covishield " << std::stoi(Covishield) + std::stoi(CovishieldStock) << ";";
                    temp.close();
                    remove("Adminfile.txt");
                    rename("temp.txt", "Adminfile.txt");
                    std::cout << "\n\n\t\tVaccine stock added.\n\n";
                }
                else
                {
                    std::cout << "\n\t\tInvalid input!!!";
                }
            }
            break;
            case 3:
                return;
            default:
                std::cout << "\n\t\tInvalid Choice!!!";
            }
        }
        else
        {
            std::cout << "\n\t\tInvalid input!!!";
        }
    }
}
//To display total vaccine stock details from Adminfile.txt file
void Admin::displayVaccine()
{
    std::ifstream inputfile("Adminfile.txt");
    while (std::getline(inputfile, line1))
    {
        while ((pos = line1.find(delimiter)) != std::string::npos)
        {
            token = line1.substr(0, pos);
            if (token.rfind("Covishield ", 0) == 0)
            {
                vaccinecovishield = token.substr(11);
            }
            if (token.rfind("Cowin ", 0) == 0)
            {
                Vaccinecowin = token.substr(6);
            }

            line1.erase(0, pos + delimiter.length());
        }
    }
    std::cout << "\n\n\t\t-->> VACCINE STOCK <<--" << std::endl;
    std::cout << " \n\t\t1.Cowin: " << Vaccinecowin;
    std::cout << "\n\t\t2.Covishield: " << vaccinecovishield;
    inputfile.close();
    std::cout << std::endl;
}
//To approve vaccine request made by hospitals from request.txt file
void Admin::approveVaccineRequest()
{
    std::fstream requestfile("request.txt", std::ios::out | std::ios::in | std::ios::app);
    std::ifstream request;
    request.open("request.txt");
    request.seekg(0, std::ios::end);// using seekg()place pointer at end of file
    if (request.tellg() == 0)//using tellg() to know where the get pointer is in a file.
    {

        std::cout << "\n\n\t\tNo Request Found\n";
        request.close();
        return;
    }
    else
    {
        while (std::getline(requestfile, line3))
        {
            while ((pos = line3.find(delimiter)) != std::string::npos)
            {
                token = line3.substr(0, pos);
                if (token.rfind("HospitalId ", 0) == 0)
                {
                    sameid = true;
                    hospitalid = token.substr(11);
                    std::cout << "\n\t\tHospitalId: " << hospitalid;
                }
                if (token.rfind("CowinRequired ", 0) == 0 && sameid)
                {
                    cowin = token.substr(14);
                    std::cout << " CowinRequired: " << cowin;
                }
                if (token.rfind("CovishieldRequired ", 0) == 0 && sameid)
                {
                    covishield = token.substr(19);
                    std::cout << " CovishieldRequired: " << covishield << "\n";
                }
                line3.erase(0, pos + delimiter.length());
            }
        }
        requestfile.close();
    }
    std::cout << "\n\n\t\tEnter Hospital Id for Vaccine Approval:";
    std::cin >> EnteredhospitalId;
        std::ifstream acceptfile("request.txt");

        while (std::getline(acceptfile, line3))
        {
            sameid = false;
            while ((pos = line3.find(delimiter)) != std::string::npos)
            {
                token = line3.substr(0, pos);
                if (token.rfind("HospitalId ", 0) == 0)
                {
                    filehospitalId = token.substr(11);
                    if (filehospitalId == EnteredhospitalId)
                    {
                        sameid = true;
                    }
                }
                if (token.rfind("CowinRequired ", 0) == 0 && sameid)
                {
                    cowin = token.substr(14);
                }
                if (token.rfind("CovishieldRequired ", 0) == 0 && sameid)
                {
                    covishield = token.substr(19);
                   
                }
                line3.erase(0, pos + delimiter.length());
            }
             if(sameid)
                    {
                        break;
                    }
        }
        acceptfile.close();
    if(sameid)
    {

    
        std::fstream hospitalfile("Hospitalfile.txt", std::ios::out | std::ios::in);
        
        while (std::getline(hospitalfile, line3))
        {
            sameid = false;
            while ((pos = line3.find(delimiter)) != std::string::npos)
            {
                token = line3.substr(0, pos);
                if (token.rfind("Name ", 0) == 0)
                {
                    name = token.substr(5);
                }
                if (token.rfind("Id ", 0) == 0)
                {
                    hospitalid = token.substr(3);
                    if (hospitalid == EnteredhospitalId)
                    {
                        sameid = true;
                        orginalName = name;
                    }
                }
                if (token.rfind("Address ", 0) == 0 && sameid)
                {
                    address = token.substr(8);
                }
                if (token.rfind("Pincode ", 0) == 0 && sameid)
                {
                    pincode = token.substr(8);
                }
                if (token.rfind("Cowin ", 0) == 0 && sameid)
                {
                    cowinAvailable = token.substr(6);
                }
                if (token.rfind("Covishield ", 0) == 0 && sameid)
                {
                    covishieldAvailable = token.substr(11);
                }
                line3.erase(0, pos + delimiter.length());
            }
        }

        std::cout << "\n\n\t\tApprove or Decline?(y/n): ";
        std::cin >> admininput;
        if (admininput == 'Y' || admininput == 'y')
        {

            std::ifstream in, fin;
            std::ofstream temp, fout;
            in.open("Hospitalfile.txt");
            temp.open("temp.txt");
            while (std::getline(in, line3))
            {
                idfound=false;
                std::string originalLine=line3;
                while ((pos = line3.find(delimiter)) != std::string::npos)
                {
                    token = line3.substr(0, pos);
                    if (token.rfind("Id ", 0) == 0)
                    {
                        std::string hospitalid = token.substr(3);
                        if (hospitalid == EnteredhospitalId)
                        {
                            idfound = true;
                            temp << "Name " << orginalName;
                            temp << ";Id " << EnteredhospitalId;
                            temp << ";Address " << address;
                            temp << ";Pincode " << pincode;
                            temp << ";Cowin " << std::stoi(cowin) + std::stoi(cowinAvailable);
                            temp << ";Covishield " << std::stoi(covishield) + std::stoi(covishieldAvailable);
                            temp << ";TotalVaccine " << std::stoi(cowin) + std::stoi(cowinAvailable) + std::stoi(covishield) + std::stoi(covishieldAvailable) << ";\n";
                        }
                    }
                    line3.erase(0, pos + delimiter.length());
                }
                if (!idfound)
                {
                    temp << originalLine << "\n";
                }
            }
            temp.close();
            in.close();
            remove("Hospitalfile.txt");
            rename("temp.txt", "Hospitalfile.txt");
            fin.open("request.txt");
            fout.open("temp.txt");
            while (std::getline(fin, line3))
            {  
                idfound=false;
                std::string originalLine=line3;
                while ((pos = line3.find(delimiter)) != std::string::npos)
                {
                    token = line3.substr(0, pos);
                    if (token.rfind("HospitalId ", 0) == 0)
                    {
                        std::string hospitalid = token.substr(11);
                        if (hospitalid == EnteredhospitalId)
                        {
                            idfound = true;
                        }
                    }
                    line3.erase(0, pos + delimiter.length());
                }
                if (!idfound)
                {
                    fout << originalLine << "\n";
                }
            }
            fout.close();
            fin.close();
            remove("request.txt");
            rename("temp.txt", "request.txt");
            std::cout << "\n\n\t\tRequest approved";
        }
        else if (admininput == 'n' || admininput == 'N')
        {
            std::ifstream fin;
            std::ofstream fout;
            fin.open("request.txt");
            fout.open("temp.txt");
            while (std::getline(fin, line3))
            {   idfound=false;
                std::string originalLine=line3;
                while ((pos = line3.find(delimiter)) != std::string::npos)
                {
                    token = line3.substr(0, pos);
                    if (token.rfind("HospitalId ", 0) == 0)
                    {
                        std::string hospitalid = token.substr(11);
                        if (hospitalid == EnteredhospitalId)
                        {
                            idfound = true;
                        }
                    }
                    line3.erase(0, pos + delimiter.length());
                }
                if (!idfound)
                {
                    fout << originalLine << "\n";
                }
            }
            fout.close();
            fin.close();
            remove("request.txt");
            rename("temp.txt", "request.txt");

            std::cout << "\n\n\t\tRequest declined";
        }
        else
        {

            std::cout << "\n\t\tInvalid input !!";

            approveVaccineRequest();
        }
   }
    else
    {
        std::cout << "\n\t\tInvalid hospital id";
    }
}
