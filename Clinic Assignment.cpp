Clinic Assignment
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Prescription 
{
private:
    string medicine;
    string dosage;
    string duration;

public:
    Prescription(string med, string dose, string dur)
        : medicine(med), dosage(dose), duration(dur) {}

    void printInfo() 
	{
        cout << "   Prescription: " << medicine
             << " | Dosage: " << dosage
             << " | Duration: " << duration << endl;
    }
};

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
    vector<Prescription> prescriptions;

public:
    Appointment(int id, string date, string time, string reason,
                string patientName, string doctorName)
        : id(id), date(date), time(time), reason(reason),
          status("Scheduled"), 
          patientName(patientName), doctorName(doctorName) {}

    int getId() { return id; }
	string getDoctorName() { return doctorName; }
    string getPatientName() { return patientName; }
    
    void addPrescription(string med, string dose, string dur) 
	{
        prescriptions.push_back(Prescription(med, dose, dur));
    }
    
    void setStatus(string s) { status = s; }

    void printInfo() 
	{
        cout << "[Appointment " << id << "] Date: " << date << " " << time << endl;
        cout << "   Patient: " << patientName << endl;
        cout << "   Doctor: " << doctorName << endl;
        cout << "   Reason: " << reason << endl;
        cout << "   Status: " << status << endl;
        for (int i = 0; i < prescriptions.size(); i++) 
		{
            prescriptions[i].printInfo();
        }
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
    int nextAppId = 1;  // auto-increment ID

public:
    Patient(string name, int id, int age)
        : name(name), id(id), age(age), history("") {}

    int getId() { return id; }
    string getName() { return name; }
    int getAge() { return age; }

    void addHistory(string record) 
    {
        history += record + "\n";
    }

    virtual void scheduleAppointment(string date, string time, string reason, string doctorName) 
    {
        Appointment app(nextAppId++, date, time, reason, name, doctorName);
        appointments.push_back(app);  
        cout << "Appointment scheduled for " << name << endl;
        app.printInfo();
    }

    void addPrescriptionToAppointment(int appId, string med, string dose, string dur) 
    {
        for (size_t i = 0; i < appointments.size(); i++) 
        {
            if (appointments[i].getId() == appId) {
                appointments[i].addPrescription(med, dose, dur);
                cout << "Prescription added to Appointment " << appId << endl;
                return;
            }
        }
        cout << "No appointment found with ID " << appId << endl;
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

    vector<Appointment>& getAppointments() { return appointments; }
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

    void scheduleAppointment(string date, string time, string reason, string doctorName) override
    {
        cout << "Chronic patient " << name << " requires regular checkups every 3 months.\n";
        Appointment app(nextAppId++, date, time, reason, name, doctorName);
        appointments.push_back(app); 
        app.printInfo();
    }

    void printInfo() 
    {
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
    vector<Appointment> appointments;

public:
    Doctor(string name, int id, string specialty)
        : name(name), id(id), specialty(specialty) {}
        
    string getName() { return name; }
    int getId() { return id; }
    
    void assignAppointment(Appointment app) 
    {
        appointments.push_back(app);
    }
        
	void updateAppointmentStatus(int appId, string newStatus) 
    {
        for (int i = 0; i < appointments.size(); i++) 
		{
            if (appointments[i].getId() == appId) 
			{
                appointments[i].setStatus(newStatus);
                cout << "Doctor updated status of Appointment " << appId 
                     << " to " << newStatus << endl;
                return;
            }
        }
        cout << "Appointment not found for this doctor.\n";
    }

    void printAppointments() 
    {
        cout << "Appointments for Dr. " << name << ":\n";
        for (int i = 0; i < appointments.size(); i++) 
		{
            appointments[i].printInfo();
        }
    }

    void printInfo() {
        cout << "[Doctor] " << name << " (ID: " << id << ", Specialty: " << specialty << ")" << endl;
    }
};

Patient* searchPatientById(vector<Patient*>& patients, int id) 
{
    for (auto p : patients) 
	{
        if (p->getId() == id)
            return p;
    }
    return nullptr;
}

Doctor* searchDoctorByName(vector<Doctor*>& doctors, string name) 
{
    for (auto d : doctors) {
        if (d->getName() == name)
            return d;
    }
    return nullptr;
}

int main() 
{
    Patient p1("Alice", 101, 30);
    ChronicPatient cp1("Bob", 102, 55, "Diabetes", "01/06/2025");

    Doctor d1("Dr. Smith", 201, "General Medicine");
    Doctor d2("Dr. Lee", 202, "Cardiology");

    vector<Patient*> patients = {&p1, &cp1};
    vector<Doctor*> doctors = {&d1, &d2};

    p1.addHistory("01/11/2024: Treated for cold");
    cp1.addHistory("05/01/2025: Blood sugar monitoring");

    cout << " Scheduling Appointments n";
	p1.scheduleAppointment("15/09/2025", "09:00", "Flu symptoms", "Dr. Smith");
	cp1.scheduleAppointment("20/09/2025", "10:30", "Routine check-up", "Dr. Lee");

	cout << " Adding Prescription ";
	p1.addPrescriptionToAppointment(1, "Paracetamol", "500mg", "5 days");
	cp1.addPrescriptionToAppointment(1, "Insulin", "10 units", "Daily");

    cout << " Search Demo " ;
    Patient* foundPatient = searchPatientById(patients, 102);
    if (foundPatient) foundPatient->printInfo();

    Doctor* foundDoctor = searchDoctorByName(doctors, "Dr. Lee");
    if (foundDoctor) foundDoctor->printInfo();

    cout << " All Patient Info ";
    p1.printInfo();
    cp1.printInfo();

    system("pause");
    return 0;
}



