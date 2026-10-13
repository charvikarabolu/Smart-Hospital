#include <stdio.h>
#include <stdlib.h>
#include "hospital.h"
#include "storage.h"
#include "ai_triage.h"
static void readLine(char *text, int size)
{
    int ch;
    if (fgets(text, size, stdin) == NULL) {
        text[0] = '\0';
        return;
    }

    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

static int readInt(const char *prompt)
{
    int value;
    printf("%s", prompt);
    scanf("%d", &value);
    while (getchar() != '\n')
        ;
    return value;
}

static Patient enterPatient(void)
{
    Patient p;

    p.id = readInt("Patient ID: ");
    printf("Patient name: ");
    readLine(p.name, NAME_SIZE);
    p.age = readInt("Age: ");
    printf("Condition: ");
    readLine(p.condition, DISEASE_SIZE);
    p.emergency = readInt("Emergency priority (1-4): ");

    if (p.emergency < 0) p.emergency = 0;
    if (p.emergency > 5) p.emergency = 5;

    return p;
}

static Doctor enterDoctor(void)
{
    Doctor d;

    d.id = readInt("Doctor ID: ");
    printf("Doctor name: ");
    readLine(d.name, DOCTOR_NAME_SIZE);
    printf("Specialty: ");
    readLine(d.specialty, SPECIALTY_SIZE);
    d.available = readInt("Available? (1=yes, 0=no): ") ? 1 : 0;

    return d;
}

static void patientMenu(HospitalState *h)
{
    Patient p;
    Patient *found;
    int choice, id;

    do {
        printf("\n--- Patient Records ---\n");
        printf("1. Add patient\n");
        printf("2. Search patient\n");
        printf("3. List patients\n");
        printf("4. Sort by patient ID\n");
        printf("0. Back\n");
        choice = readInt("Choice: ");

        switch (choice) {
        case 1:
            p = enterPatient();
            if (addPatient(&h->patients, p))
                printf("Patient added.\n");
            else
                printf("Unable to add patient. ID may already exist.\n");
            break;

        case 2:
            id = readInt("Patient ID to search: ");
            found = lookupRecord(&h->patients, id);
            if (found != NULL)
                printf("Found: %d, %s, age %d, %s\n",
                       found->id, found->name,
                       found->age, found->condition);
            else
                printf("Patient not found.\n");
            break;

        case 3:
            listPatients(&h->patients);
            break;

        case 4:
            sortPatientsById(&h->patients);
            printf("Records sorted.\n");
            break;
        }
    } while (choice != 0);
}

static void doctorMenu(HospitalState *h)
{
    Doctor d;
    int choice, id;

    do {
        printf("\n--- Doctor Registry ---\n");
        printf("1. Register doctor\n");
        printf("2. List doctors\n");
        printf("3. Change availability\n");
        printf("0. Back\n");
        choice = readInt("Choice: ");

        switch (choice) {
        case 1:
            d = enterDoctor();
            if (registerDoctor(&h->doctors, d))
                printf("Doctor registered.\n");
            else
                printf("Unable to register doctor. ID may already exist.\n");
            break;

        case 2:
            showDoctors(&h->doctors);
            break;

        case 3:
            id = readInt("Doctor ID: ");
            changeDoctorAvailability(&h->doctors,
                                     id,
                                     readInt("Available? (1/0): "));
            printf("Availability updated if doctor exists.\n");
            break;
        }
    } while (choice != 0);
}

static void queueMenu(HospitalState *h)
{
    int choice, id;
    Patient *p;
    Patient out;

    do {
        printf("\n--- Patient Flow ---\n");
        printf("1. Put normal patient in waiting room\n");
        printf("2. Send patient to emergency room\n");
        printf("3. Call next waiting patient\n");
        printf("4. Call highest-priority emergency patient\n");
        printf("5. Show waiting room\n");
        printf("6. Show emergency room\n");
        printf("0. Back\n");
        choice = readInt("Choice: ");

        switch (choice) {
        case 1:
            id = readInt("Patient ID: ");
            p = lookupRecord(&h->patients, id);
            if (p != NULL && admitToWaitingRoom(&h->waiting, p))
                printf("Patient placed in waiting room.\n");
            else
                printf("Patient not found or waiting room is full.\n");
            break;

        case 2:
            id = readInt("Patient ID: ");
            p = lookupRecord(&h->patients, id);
            if (p != NULL && sendToEmergency(&h->emergency, *p))
                printf("Patient added to emergency queue.\n");
            else
                printf("Patient not found or emergency room is full.\n");
            break;

        case 3:
            if (releaseFromWaitingRoom(&h->waiting, &out))
                printf("Now serving patient %d.\n", out.id);
            else
                printf("Waiting room is empty.\n");
            break;

        case 4:
            if (takeEmergencyPatient(&h->emergency, &out))
                printf("Emergency patient %d is being served.\n", out.id);
            else
                printf("Emergency queue is empty.\n");
            break;

        case 5:
            showWaitingRoom(&h->waiting);
            break;

        case 6:
            showEmergencyRoom(&h->emergency);
            break;
        }
    } while (choice != 0);
}


/*
 * Runs the classroom AI classifier independently of queue management.
 * The prediction is informational only and never changes queue priority.
 */
static void aiClassificationMenu(void)
{
    AIFeatures features;

    printf("\n--- AI Classification Demonstration ---\n");
    printf("For this demo, enter 0 for No or 1 for Yes.\n");
    printf("This is a synthetic classroom model, not medical advice.\n");

    features.fever = readInt("Fever? (0/1): ");
    features.cough = readInt("Cough? (0/1): ");
    features.breathing_difficulty =
        readInt("Breathing difficulty? (0/1): ");
    features.severe_pain = readInt("Severe pain? (0/1): ");
    features.confusion = readInt("Confusion? (0/1): ");

    if (!ai_features_valid(&features)) {
        printf("Invalid input: each answer must be 0 or 1.\n");
        return;
    }

    ai_demo_print_result(&features);
    printf("A qualified staff member must make all real care decisions.\n");
}

int main(void)
{
    HospitalState hospital;
    int choice;

    hospitalInit(&hospital);

    do {
        printf("\n==============================\n");
        printf("       SMART HOSPITAL\n");
        printf("==============================\n");
        printf("1. Patient records\n");
        printf("2. Doctor registry\n");
        printf("3. Patient flow / queues\n");
        printf("4. Save data\n");
        printf("5. Load data\n");
        printf("6. AI classification demonstration\n");
        printf("0. Exit\n");

        choice = readInt("Choice: ");

        switch (choice) {
        case 1:
            patientMenu(&hospital);
            break;
        case 2:
            doctorMenu(&hospital);
            break;
        case 3:
            queueMenu(&hospital);
            break;
        case 4:
            printf("Patients: %s\n",
                   savePatients(&hospital.patients, "patients.dat")
                   ? "saved" : "failed");
            printf("Doctors: %s\n",
                   saveDoctors(&hospital.doctors, "doctors.dat")
                   ? "saved" : "failed");
            break;
        case 5:
            printf("Patients: %s\n",
                   loadPatients(&hospital.patients, "patients.dat")
                   ? "loaded" : "file unavailable");
            printf("Doctors: %s\n",
                   loadDoctors(&hospital.doctors, "doctors.dat")
                   ? "loaded" : "file unavailable");
            break;
        case 6:
            aiClassificationMenu();
            break;
        }
    } while (choice != 0);

    hospitalFree(&hospital);
    return 0;
}
