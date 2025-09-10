Clinic Assignment
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Appointment 
{
private:
    int id;
    string date;
    string time;
    string reason;
    string status;       
    string patientName;
    string doctorName;

public:
    Appointment(int id, string date, string time, string reason,
                string patientName, string doctorName)
        : id(id), date(date), time(time), reason(reason),
          status("Scheduled"), 
          patientName(patientName), doctorName(doctorName) {}

    int getId() { return id; }

    void setStatus(string s) { status = s; }

    void printInfo() 
	{
        cout << "[Appointment " << id << "] Date: " << date << " " << time << endl;
        cout << "   Patient: " << patientName << endl;
        cout << "   Doctor: " << doctorName << endl;
        cout << "   Reason: " << reason << endl;
        cout << "   Status: " << status << endl;
    }
};


class Patient 
{
protected:
    string name;
    int id;
    int age;
    string history;
    vector<Appointment> appointments;

public:
    Patient(string name, int id, int age)
        : name(name), id(id), age(age), history("") {}

    void addHistory(string record) 
	{
        history += record + "\n";
    }

    void scheduleAppointment(string date, string time, string reason, string doctorName) 
	{
        Appointment app(1, date, time, reason, name, doctorName);
        cout << "Appointment scheduled for " << name << endl;
        app.printInfo();
    }
	void printAppointments() 
	{
        cout << "Appointments for " << name << ":\n";
        for (int i = 0; i < appointments.size(); i++) {
            appointments[i].printInfo();
        }
    }
    void printInfo() 
	{
        cout << "[Patient] " << name << " (ID: " << id << ", Age: " << age << ")" << endl;
        cout << "History:\n" << history << endl;
        printAppointments();
    }
};
//Inheritance
class ChronicPatient : public Patient 
{
private:
    string condition;
    string lastCheckup;

public:
    ChronicPatient(string name, int id, int age, string condition, string lastCheckup)
        : Patient(name, id, age), condition(condition), lastCheckup(lastCheckup) {}

    void scheduleAppointment(string date, string time, string reason, string doctorName) {
        cout << "Chronic patient " << name << " requires regular checkups every 3 months.\n";
        Appointment app(1, date, time, reason, name, doctorName);
        app.printInfo();
    }

    void printInfo() {
        Patient::printInfo();
        cout << "Condition: " << condition << ", Last check-up: " << lastCheckup << endl;
    }
};


class Doctor 
{
private:
    string name;
    int id;
    string specialty;

public:
    Doctor(string name, int id, string specialty)
        : name(name), id(id), specialty(specialty) {}

    void printInfo() {
        cout << "[Doctor] " << name << " (ID: " << id << ", Specialty: " << specialty << ")" << endl;
    }
};


int main() {
   
    Patient p1("Alice", 101, 30);
    ChronicPatient cp1("Bob", 102, 55, "Diabetes", "01/06/2025");

 
    Doctor d1("Dr. Smith", 201, "General Medicine");
    
	p1.addHistory("01/11/2024: Treated for cold");
    p1.addHistory("10/02/2025: Annual health check");

    cp1.addHistory("05/01/2025: Blood sugar monitoring");
    cp1.addHistory("01/06/2025: Routine diabetes check");
  
    cout << " Patient Info " << endl;
    p1.printInfo();
    cp1.printInfo();

    cout << " Doctor Info " << endl;
    d1.printInfo();

    cout << " Scheduling Appointments " << endl;
    p1.scheduleAppointment("15/09/2025", "09:00", "Flu symptoms", "Dr. Smith");
    cp1.scheduleAppointment("20/09/2025", "10:30", "Routine check-up", "Dr. Smith");
	system("pause");
    return 0;
}

