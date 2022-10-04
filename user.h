#include <iostream>
class User
{
  bool ExistingMobileNumber, GetHospitalName, ExistingUserName;
  std::string delimiter;
  size_t pos;
  bool ExistingPincode, ExistingName, ExistingPassword;
  int EqualPhoneNumber, EqualUserName, EqualPincode, EqualHospitalName, EqualPassword;
  std::string choice;
  std::string Dose, Vaccinechoice;
  int SamePhoneNumber;
  bool registerAccount();
  void vaccineBooking(std::string, std::string);
  void vaccinationStatus(std::string);
  std::string calculateAge();
  int day, month, year, day1, day2, month1, month2, year1, year2;
  int days, Age, doseChoice;
  char Choice;
  bool found = false;
  int count = 0;
  int count2 = 0;
  int count3 = 0;
  bool Dose1found = false;
  bool Dose2found = false;
  std::string newphone1;
  std::string dob, dayInString, monthInString, yearInString;
  std::string dayVar, monthVar, yearVar, age, FileUserName;
  std::string Name, address, phoneno, Pincode;
  std::string phone, filepincode, filephoneNo, fileHospitalName;
  std::string UserName, Password, EnteredUserName, EnteredPassword;
  std::string fileName, PincodeFromFile;
  std::string line, token, PatientName;
  std::string line1, FileHospitalName;
  std::string line2, HospitalName, EnteredMobileNumber;
  std::string EnteredPincode, EnteredHospital, Dose1, Dose2, DateOfVaccine, DateOfDose1, DateOfDose2;
  std::string Mobile, phoneNo, name;
  std::string line3, vaccine, line5, line4;

public:
  User();
  void userLogin();
};