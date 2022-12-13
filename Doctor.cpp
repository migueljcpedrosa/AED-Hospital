
#include "Doctor.h"
#include <algorithm>
#include "iostream"


Patient::Patient() {}

Patient::Patient(unsigned codP, string mS): codeP(codP), medicalSpecialty(mS)
{}

string Patient::getMedicalSpecialty() const {
    return medicalSpecialty;
}

unsigned Patient::getCode() const {
    return codeP;
}

Doctor::Doctor(unsigned codM, string mS): codeM(codM), medicalSpecialty(mS)
{}


Doctor::Doctor(unsigned codM, string mS, queue<Patient> patients1): codeM(codM), medicalSpecialty(mS), patients(patients1)
{}

unsigned Doctor::getCode() const {
    return codeM;
}

string Doctor::getMedicalSpecialty() const {
    return medicalSpecialty;
}

queue<Patient> Doctor::getPatients() const {
    return patients;
}

void Doctor::addPatient(const Patient &p1) {
    patients.push(p1);
}

Patient Doctor::removeNextPatient() {
    if (!patients.empty()) {
        Patient p1 = patients.front();
        patients.pop();
        return p1;
    }
    else throw PatientInexistent();
}




void Doctor::moveToFront(unsigned codP1) {
    auto patientsSize = patients.size();
    auto counter = 0;
    while (counter < patientsSize)
    {
        if (patients.front().getCode() == codP1)
        {
            break;
        }
        else
        {
            patients.push(patients.front());
            patients.pop();
        }
        counter++;
    }
}

void Doctor::operator=(const Doctor &d1) {
    codeM = d1.getCode();
    medicalSpecialty = d1.getMedicalSpecialty();
}

void Patient::operator=(const Patient &p1) {
    codeP = p1.getCode();
    medicalSpecialty = p1.getMedicalSpecialty();
}
