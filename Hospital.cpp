
#include "Hospital.h"

#include <algorithm>
#include <stack>
#include <iostream>



Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
    doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
    return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
    letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
    return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
    unsigned counter = 0;
    for (auto &doctor : doctors)
    {
        if (doctor.getMedicalSpecialty() == medicalSpecialty)
        {
            counter += doctor.getPatients().size();
        }
    }
    return counter;
}

bool lessThan(Doctor &d1, Doctor &d2)
{
    if (d1.getPatients().size() == d2.getPatients().size())
    {
        if(d1.getMedicalSpecialty() == d2.getMedicalSpecialty())
        {
            return d1.getCode() < d2.getCode();
        }
        return d1.getMedicalSpecialty() < d2.getMedicalSpecialty();
    }
    return d1.getPatients().size() < d2.getPatients().size();
}

void Hospital::sortDoctors() {
    doctors.sort(lessThan);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
    Doctor doctorAdd = Doctor(codM1, medicalSpecialty1);
    auto doctorsInSpecialty = 0;

    for (auto doctorInDoctors : doctors)
    {
        if(doctorInDoctors.getMedicalSpecialty() == medicalSpecialty1)
        {
            doctorsInSpecialty++;
        }
    }

    if (doctorsInSpecialty >= 3)
    {
        return false;
    }

    if (doctorsInSpecialty < 3)
    {
        doctors.push_back(doctorAdd);
        return true;
    }
}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
    queue<Patient> patientsCopy;
    auto doctorIterator = doctors.begin();
    while (doctorIterator != doctors.end())
    {
        if(doctorIterator->getCode() == codM1)
        {
            patientsCopy = doctorIterator->getPatients();
            doctorIterator = doctors.erase(doctorIterator);
            return patientsCopy;
        }
        else
        {
            doctorIterator++;
        }
    }
    throw DoctorInexistent();

}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
    Patient patientAdd = Patient(cod1, medicalSpecialty1);
    int minPatients = INT_MAX;
    int numDoctorsInMedicalSpecialty = 0;
    auto minIterator = doctors.begin();
    auto doctorsIterator = doctors.begin();

    while (doctorsIterator != doctors.end())
    {
        if(doctorsIterator->getMedicalSpecialty() == medicalSpecialty1)
        {
            numDoctorsInMedicalSpecialty++;
            if (doctorsIterator->getPatients().size() < minPatients)
            {
                minPatients = doctorsIterator->getPatients().size();
                minIterator = doctorsIterator;
            }
        }
        doctorsIterator++;
    }
    minIterator->addPatient(patientAdd);

    if (numDoctorsInMedicalSpecialty == 0)
    {
        return false;
    }
    return true;

}


void Hospital::processPatient(unsigned codM1) {
    auto doctorsIterator = doctors.begin();
    bool finished = true;

    while(doctorsIterator != doctors.end())
    {
        if (doctorsIterator->getCode() == codM1 && doctorsIterator->getPatients().size() > 0)
        {
            for (auto &tray : letterTray)
            {
                if (tray.size() < trayCapacity)
                {
                    finished = false;
                    break;
                }
            }

            if (!finished)
            {
                for (auto &tray : letterTray) {
                    if (tray.size() < trayCapacity) {
                        tray.push(doctorsIterator->removeNextPatient());
                        break;
                    }
                }
            }
            else {
                for (auto &tray: letterTray) {
                    stack<Patient> trayAdd;
                    trayAdd.push(doctorsIterator->removeNextPatient());
                    addTrays(trayAdd);
                    break;
                }
            }
        }
        doctorsIterator++;
    }
}


unsigned Hospital::removePatients(unsigned codP1) {
    auto trayIterator = letterTray.begin();
    int patientsRemoved = 0;

    while (trayIterator != letterTray.end())
    {
        if (trayIterator->top().getCode() == codP1)
        {
            trayIterator->pop();
            patientsRemoved++;
        }

        if (trayIterator->size() == 0)
        {
            trayIterator = letterTray.erase(trayIterator);
        }
        trayIterator++;
    }

    return patientsRemoved;
}
