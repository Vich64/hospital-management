#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Define the Patient structure
struct Patient {
    string Name;
    int ID;
    int Age;
    char Gender;
    string Telephone;
    string Date;
    string Symptoms;
    int Sickness_Level; // 1: red, 2: yellow, 3: green
    int Time_Treatment;
    string Accompany;
    string Prescription;
    string Consultant;
};

// Define the PatientList class
class PatientList {
private:
    Patient *Red_Top;
    Patient *Yellow_Top;
    Patient *Green_Top;
    const string fileName = "patients.csv"; // CSV file name

public:
    // Constructor
    PatientList() {
        Red_Top = nullptr;
        Yellow_Top = nullptr;
        Green_Top = nullptr;

        // Load patients from the file
        LoadFromFile();
    }

    ~PatientList() {
        SaveToFile(); // Save patients to file upon destruction
    }

    // Add a new patient
    void AddPatient() {
        Patient newPatient;

        // Input patient details
        cout << "------------------ Welcome to Sabay Hospital --------------------\n";
        cout << "Enter Your Full Name: ";
        cin.ignore(); // To clear the newline buffer
        getline(cin, newPatient->Name);
        cout << "Enter Your ID: ";
        cin >> newPatient->ID;

        // Check for duplicate ID
        if (CheckDuplicateID(newPatient.ID)) {
            cout << "Error: Duplicate ID detected. Please try again.\n";
            return;
        }

        cout << "Enter Your Age: ";
        cin >> newPatient->Age;
        cout << "Enter Your Gender (M/F): ";
        cin >> newPatient->Gender;
        cout << "Enter Your Telephone: ";
        cin >> newPatient->Telephone;
        cout << "Enter Today's Date (YYYY-MM-DD): ";
        cin >> newPatient->Date;
        cout << "Enter Your Symptoms: ";
        cin.ignore();
        getline(cin, newPatient->Symptoms);
        cout << "Enter Your Sickness Level (1: Red, 2: Yellow, 3: Green): ";
        cin >> newPatient->Sickness_Level;
        cout << "Enter Your Time for Treatment (in minutes): ";
        cin >> newPatient->Time_Treatment;
        cout << "Enter the Name of Accompanying Person (if any): ";
        cin.ignore();
        getline(cin, newPatient->Accompany);
        cout << "Enter Your Prescription: ";
        getline(cin, newPatient->Prescription);
        cout << "Enter the Name of Your Consultant Doctor: ";
        getline(cin, newPatient->Consultant);

        // Save the patient to the `patients.csv` file
        SavePatientToFile(newPatient);

        cout << "Patient added successfully!\n";
    }

    // Display patients from the `patients.csv` file by priority
    void DisplayPatients() {
        cout << "----------------- Display Patients by Priority ------------------\n";

        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "No patients found.\n";
            return;
        }

        DisplayPatientsByPriority(file, 1, "Red Patients");
        file.clear();
        file.seekg(0); // Rewind the file
        DisplayPatientsByPriority(file, 2, "Yellow Patients");
        file.clear();
        file.seekg(0); // Rewind the file
        DisplayPatientsByPriority(file, 3, "Green Patients");

        file.close();
    }

    // Process and remove a patient (pop)
    void ProcessPatient() {
        cout << "----------------- Processing Patient ------------------\n";

        if (Pop(Red_Top)) return;    // Process from Red queue (top priority)
        if (Pop(Yellow_Top)) return; // Process from Yellow queue
        if (Pop(Green_Top)) return;  // Process from Green queue

        cout << "No patients left to process.\n";
    }

    // Display all patients
    void DisplayPatients() {
        cout << "\nDisplaying Red Patients (Top to Bottom):\n";
        DisplayStack(Red_Top);

        cout << "\nDisplaying Yellow Patients (Top to Bottom):\n";
        DisplayStack(Yellow_Top);

        cout << "\nDisplaying Green Patients (Top to Bottom):\n";
        DisplayStack(Green_Top);
    }

private:
    // Push a patient onto the stack (queue as stack)
    void Push(Patient *&top, Patient *newPatient) {
        newPatient->Next = top;
        top = newPatient;
    }

    // Pop a patient from the stack (queue as stack)
    bool Pop(Patient *&top) {
        if (!top) return false;

        Patient *temp = top;
        top = top->Next;

        // Display the patient details
        cout << "Processing Patient:\n";
        cout << "----------------------\n";
        cout << "Name: " << temp->Name << "\n";
        cout << "ID: " << temp->ID << "\n";
        cout << "Age: " << temp->Age << "\n";
        cout << "Gender: " << temp->Gender << "\n";
        cout << "Telephone: " << temp->Telephone << "\n";
        cout << "Date: " << temp->Date << "\n";
        cout << "Symptoms: " << temp->Symptoms << "\n";
        cout << "Sickness Level: " << temp->Sickness_Level << "\n";
        cout << "Time for Treatment: " << temp->Time_Treatment << "\n";
        cout << "Accompany: " << temp->Accompany << "\n";
        cout << "Prescription: " << temp->Prescription << "\n";
        cout << "Consultant: " << temp->Consultant << "\n";
        cout << "----------------------\n";

        delete temp; // Free the memory
        return true;
    }

    // Display the patients in a stack (queue as stack)
    void DisplayStack(Patient *top) {
        if (!top) {
            cout << "No patients in this category.\n";
            return;
        }

        Patient *current = top;
        while (current) {
            cout << "----------------------\n";
            cout << "Name: " << current->Name << "\n";
            cout << "ID: " << current->ID << "\n";
            cout << "Age: " << current->Age << "\n";
            cout << "Gender: " << current->Gender << "\n";
            cout << "Telephone: " << current->Telephone << "\n";
            cout << "Date: " << current->Date << "\n";
            cout << "Symptoms: " << current->Symptoms << "\n";
            cout << "Sickness Level: " << current->Sickness_Level << "\n";
            cout << "Time for Treatment: " << current->Time_Treatment << "\n";
            cout << "Accompany: " << current->Accompany << "\n";
            cout << "Prescription: " << current->Prescription << "\n";
            cout << "Consultant: " << current->Consultant << "\n";
            current = current->Next;
        }
    }

    // Check for duplicate patient ID
    bool CheckDuplicateID(int id) {
        return (FindInStack(Red_Top, id) || FindInStack(Yellow_Top, id) || FindInStack(Green_Top, id));
    }

    // Find a patient in a stack
    bool FindInStack(Patient *top, int id) {
        Patient *current = top;
        while (current) {
            if (current->ID == id) {
                return true;
            }
            current = current->Next;
        }
        return false;
    }

    // Display the patient history from `history.csv`
    void DisplayHistory() {
        cout << "----------------- Display Patient History ------------------\n";

        ifstream file(historyFileName);
        if (!file.is_open()) {
            cout << "No history found.\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            ReplaceCommasWithNewlines(line); // Format and display the line
            cout << "----------------------\n";
        }

        file.close();
    }

private:
    // Save a patient to the `patients.csv` file
    void SavePatientToFile(const Patient &patient) {
        ofstream file(fileName, ios::app); // Append mode
        if (!file.is_open()) {
            cout << "Error: Unable to save patient to file.\n";
            return;
        }

        file << patient.Name << "," << patient.ID << "," << patient.Age << "," << patient.Gender << ","
             << patient.Telephone << "," << patient.Date << "," << patient.Symptoms << ","
             << patient.Sickness_Level << "," << patient.Time_Treatment << "," << patient.Accompany << ","
             << patient.Prescription << "," << patient.Consultant << "\n";

        file.close();
    }

    // Save a patient to the `history.csv` file
    void SavePatientToHistory(const Patient &patient) {
        ofstream file(historyFileName, ios::app); // Append mode
        if (!file.is_open()) {
            cout << "Error: Unable to save patient to history file.\n";
            return;
        }

        file << patient.Name << "," << patient.ID << "," << patient.Age << "," << patient.Gender << ","
             << patient.Telephone << "," << patient.Date << "," << patient.Symptoms << ","
             << patient.Sickness_Level << "," << patient.Time_Treatment << "," << patient.Accompany << ","
             << patient.Prescription << "," << patient.Consultant << "\n";

        file.close();
    }

    // Load all patients from the `patients.csv` file
    vector<Patient> LoadPatientsFromFile() {
        vector<Patient> patients;

        ifstream file(fileName);
        if (!file.is_open()) return patients;

        string line, value;
        while (getline(file, line)) {
            stringstream ss(line);
            Patient patient;

            getline(ss, patient.Name, ',');
            getline(ss, value, ',');
            patient.ID = stoi(value);
            getline(ss, value, ',');
            patient.Age = stoi(value);
            getline(ss, value, ',');
            patient.Gender = value[0];
            getline(ss, patient.Telephone, ',');
            getline(ss, patient.Date, ',');
            getline(ss, patient.Symptoms, ',');
            getline(ss, value, ',');
            patient.Sickness_Level = stoi(value);
            getline(ss, value, ',');
            patient.Time_Treatment = stoi(value);
            getline(ss, patient.Accompany, ',');
            getline(ss, patient.Prescription, ',');
            getline(ss, patient.Consultant, ',');

            patients.push_back(patient);
        }

        file.close();
        return patients;
    }

    // Display patients by priority
    void DisplayPatientsByPriority(ifstream &file, int level, const string &title) {
        string line, value;
        cout << title << ":\n";

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, value, ','); // Name
            string name = value;
            getline(ss, value, ','); // ID
            int id = stoi(value);
            getline(ss, value, ','); // Age
            getline(ss, value, ','); // Gender
            getline(ss, value, ','); // Telephone
            getline(ss, value, ','); // Date
            getline(ss, value, ','); // Symptoms
            getline(ss, value, ','); // Sickness_Level
            int sickness_level = stoi(value);

            if (sickness_level == level) {
                ReplaceCommasWithNewlines(line);
                cout << "----------------------\n";
            }
        }
    }

    // Display patient details
    void DisplayPatientDetails(const Patient &patient) {
        cout << "Name: " << patient.Name << "\n";
        cout << "ID: " << patient.ID << "\n";
        cout << "Age: " << patient.Age << "\n";
        cout << "Gender: " << patient.Gender << "\n";
        cout << "Telephone: " << patient.Telephone << "\n";
        cout << "Date: " << patient.Date << "\n";
        cout << "Symptoms: " << patient.Symptoms << "\n";
        cout << "Sickness Level: " << patient.Sickness_Level << "\n";
        cout << "Time for Treatment: " << patient.Time_Treatment << "\n";
        cout << "Accompany: " << patient.Accompany << "\n";
        cout << "Prescription: " << patient.Prescription << "\n";
        cout << "Consultant: " << patient.Consultant << "\n";
    }

    // Replace commas with newlines for display
    void ReplaceCommasWithNewlines(string &line) {
        for (char &ch : line) {
            if (ch == ',') ch = '\n';
        }
        cout << line << endl;
    }

    // Check for duplicate patient ID
    bool CheckDuplicateID(int id) {
        vector<Patient> patients = LoadPatientsFromFile();
        for (const auto &patient : patients) {
            if (patient.ID == id) return true;
        }
        return false;
    }

    // Clear a stack and free memory
    void ClearStack(Patient *&top) {
        while (top) {
            Patient *temp = top;
            top = top->Next;
            delete temp;
        }
    }
};

// Main function
int main() {
    PatientList hospital;

    int option;
    do {
        cout << "\n--------------------- Sabay Hospital ------------------\n";
        cout << "1. Register Patient\n";
        cout << "2. Display All Patients\n";
        cout << "3. Process One Patient\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
            case 1:
                hospital.AddPatient();
                break;
            case 2:
                hospital.DisplayPatients();
                break;
            case 3:
                hospital.ProcessPatient();
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (option != 4);

    return 0;
}
