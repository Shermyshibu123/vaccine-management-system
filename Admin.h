#include <iostream>
#include <string.h>
class Admin
{
  std::string admin_choice;
  std::string delimiter;
  std::string originalLine, VaccineChoice;
  bool idfound;
  bool sameid;
  size_t pos;
  std::string CowinStock, CovishieldStock;
  int CowinStocks, CovishieldStocks;
  void adminMain();
  void addHospital();
  void addVaccine();
  void displayVaccine();
  void approveVaccineRequest();

public:
  Admin();
  void adminLogin();
  char adminpassword[20];
  int choice;
  std::string token, filehospitalId;
  std::string line3, EnteredhospitalId,hospitalid, cowin, covishield, cowinAvailable, covishieldAvailable;
  std::string name, orginalName, pincode, address;
  char admininput;
  std::string line1, Vaccinecowin, vaccinecovishield;
  std::string line, Cowin, Covishield;
  std::string HospitalName,Pincode;
  int HospitalId;
  std::string HospitalAddress;
  std::string HospitalPincode;
  int HospitalVaccines;
  std::string HospitalCowin, HospitalCovishield;
  int cowinnumber,covishieldnumber;
};
