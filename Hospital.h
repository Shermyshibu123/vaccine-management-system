#include <iostream>

class Hospital

{

      void viewCurrentStock();

      void hospitalMain(std::string);

      void currentBookings();

      void providingVaccine();

      void requestVaccine();

      void vaccinationDoneDetails(std::string);
      std::string HospitalId, line5, Id,existingHospitalname,infilehospitalname;
      std::string choice;
      int HospitalVaccines;
      std::string correspondingHospitalId,Dose1,DateofDose1,Dose2;
      std::string Hospitalname, Name, Address, Pincode;
      std::string returnHospitalName;
      int total,samenumber,sameidnumber ;
      std::string line, HospitalName, Vaccine, Hospitalid;
      std::string Cowin, Covishield, Total, VaccineDone;
      int TempCowin, TempCovishield, TempTotal;
      std::string correspondingHospitalname,DateofDose2;
      bool booking;
      std::string delimiter,Cowinrequired,Covishieldrequired;
      size_t pos;
      std::string Cowinvaccine,Covishieldvaccine,Dateofvaccine,Totalvaccine;
      bool idnamematch ,idnumbermatch ;
      std::string token;
      std::string line3, phonenumber;
      bool namematch,numbermatch,vaccinedate;
      std::string originalLine;
      int CowinVaccine, CovishieldVaccine, TotalVaccine;
      std::string id;
      int getvaccine ;
      int requestchoice;
      std::string patientname, Patientphonenumber, Patientname, Phonenumber;
      char ch;

 public:
      void hospitalLogin();
      Hospital();
};