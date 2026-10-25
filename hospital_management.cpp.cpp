#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
using namespace std;

// Abstract base class
class Person
{
protected:
    int id;
    string name;

public:
    Person(int i, const string& n)
    {
        if (i <= 0)
            throw invalid_argument("ID must be greater than zero.");
        if (n.empty())
            throw invalid_argument("Name cannot be empty.");

        id = i;
        name = n;
    }

    virtual void display() const = 0;
    virtual ~Person() {}
};

// Patient inherits Person
class Patient : public Person
{
private:
    int age;
    string illness;

public:
    Patient(int i, const string& n, int a, const string& ill)
        : Person(i, n)
    {
        if (a < 1 || a > 120)
            throw out_of_range("Patient age must be between 1 and 120.");
        if (ill.empty())
            throw invalid_argument("Illness/problem cannot be empty.");

        age = a;
        illness = ill;
    }

    void display() const override
    {
        cout << "\n--- PATIENT DETAILS ---\n";
        cout << "Patient ID: " << id << '\n';
        cout << "Name: " << name << '\n';
        cout << "Age: " << age << '\n';
        cout << "Illness: " << illness << '\n';
    }

    const string& getName() const { return name; }
};

class Doctor : public Person
{
private:
    string specialization;

public:
    Doctor(int i, const string& n, const string& s)
        : Person(i, n)
    {
        if (s.empty())
            throw invalid_argument("Doctor specialization cannot be empty.");
        specialization = s;
    }

    void display() const override
    {
        cout << "\n--- DOCTOR DETAILS ---\n";
        cout << "Doctor ID: " << id << '\n';
        cout << "Name: " << name << '\n';
        cout << "Specialization: " << specialization << '\n';
    }

    const string& getName() const { return name; }
};

class Bill
{
private:
    int patientId;
    double consultationFee;
    double medicineFee;

public:
    Bill(int id, double consultation, double medicine)
    {
        if (id <= 0)
            throw invalid_argument("Patient ID for billing must be greater than zero.");
        if (consultation < 0 || medicine < 0)
            throw invalid_argument("Fees cannot be negative.");

        patientId = id;
        consultationFee = consultation;
        medicineFee = medicine;
    }

    friend void displayBill(const Bill& b);

    double getTotal() const
    {
        return consultationFee + medicineFee;
    }
};

void displayBill(const Bill& b)
{
    cout << "\n--- BILL DETAILS ---\n";
    cout << "Patient ID: " << b.patientId << '\n';
    cout << "Consultation Fee: Rs. " << b.consultationFee << '\n';
    cout << "Medicine Fee: Rs. " << b.medicineFee << '\n';
    cout << "Total Bill: Rs. " << b.getTotal() << '\n';
}

int readInt(const string& prompt)
{
    int value;
    cout << prompt;

    if (!(cin >> value))
        throw invalid_argument("Please enter a whole number for this field.");

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

double readFee(const string& prompt)
{
    double value;
    cout << prompt;

    if (!(cin >> value))
        throw invalid_argument("Please enter a numeric value for the fee.");

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (value < 0)
        throw invalid_argument("Fee cannot be negative.");

    return value;
}

string readText(const string& prompt)
{
    string value;
    cout << prompt;
    getline(cin, value);

    if (value.empty())
        throw invalid_argument("This field cannot be empty.");

    return value;
}

int main()
{
    try
    {
        cout << "=== HOSPITAL PATIENT & APPOINTMENT MANAGEMENT SYSTEM ===\n";

        int patientId = readInt("\nEnter Patient ID: ");
        string patientName = readText("Enter Patient Name: ");

        int age = readInt("Enter Patient Age: ");

        // Check age immediately so the error appears right after age input.
        if (age < 1 || age > 120)
            throw out_of_range("Patient age must be between 1 and 120.");

        string illness = readText("Enter Illness/Problem: ");

        int doctorId = readInt("\nEnter Doctor ID: ");
        string doctorName = readText("Enter Doctor Name: ");
        string specialization = readText("Enter Doctor Specialization: ");
        string appointmentDate = readText("Enter Appointment Date (e.g. 25-10-2026): ");

        double consultationFee = readFee("\nEnter Consultation Fee (Rs.): ");
        double medicineFee = readFee("Enter Medicine Fee (Rs.): ");

        Patient patient(patientId, patientName, age, illness);
        Doctor doctor(doctorId, doctorName, specialization);
        Bill bill(patientId, consultationFee, medicineFee);

        cout << "\n========== RECORD SUMMARY ==========\n";

        const Person* person = &patient;
        person->display();

        person = &doctor;
        person->display();

        cout << "\n--- APPOINTMENT DETAILS ---\n";
        cout << "Patient: " << patient.getName() << '\n';
        cout << "Doctor: " << doctor.getName() << '\n';
        cout << "Appointment Date: " << appointmentDate << '\n';

        displayBill(bill);
        cout << "\nRecord displayed successfully.\n";
    }
    catch (const out_of_range& error)
    {
        cout << "\nAge/Range Error: " << error.what() << '\n';
        cout << "Please run the program again and enter valid information.\n";
        return 1;
    }
    catch (const invalid_argument& error)
    {
        cout << "\nInput Error: " << error.what() << '\n';
        cout << "Please run the program again and enter valid information.\n";
        return 1;
    }
    catch (const exception& error)
    {
        cout << "\nUnexpected Error: " << error.what() << '\n';
        return 1;
    }
    catch (...)
    {
        cout << "\nUnknown error occurred.\n";
        return 1;
    }

    return 0;
}
