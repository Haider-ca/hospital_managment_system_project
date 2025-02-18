/******************************************************************************
* File: hospital_management_system.c
 * Purpose: Implementation of a Hospital Management System in C.
 *          This program allows users to manage patient records and doctor schedules.
 * Features:
 *   - Add, view, search, and discharge patients.
 *   - Assign doctors to shifts and display weekly schedules.
 * Author: Valley Balfour
 * Author: Haider Al-Sudani
 * Date: Feb 18th, 2025
 * Version: 1.0
 * Dependencies: Standard C libraries (stdio.h, string.h)
 ******************************************************************************/

#include <stdio.h>
#include <string.h>

// Constants for maximum limits
#define MAX_DOCTORS 50
#define DAYS_IN_WEEK 7
#define SHIFTS_IN_DAY 3

// Structure to store patient information
struct Patient {
    int patientID;       // Unique identifier for the patient
    int age;             // Age of the patient
    int roomNumber;      // Room number assigned to the patient
    char name[100];      // Full name of the patient
    char diagnose[100];  // Diagnosis or medical condition of the patient
};

// Structure to store doctor schedules for a week
struct DoctorSchedule {
    char schedule[DAYS_IN_WEEK][SHIFTS_IN_DAY][100];  // 3D array to store doctor names for each shift of each day
};

// Function to display the main menu and get user choice
int displayMenu() {
    int choice;
    printf("\n--- Patient and Doctor Schedule Management System ---\n");
    printf("1. Add a new patient\n");
    printf("2. Display all patient records\n");
    printf("3. Discharge a patient\n");
    printf("4. Display doctor schedule\n");
    printf("5. Assign doctor to shift\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

// Function to add a new patient to the system
void addPatient(struct Patient patients[], int *count) {
    // Check if the maximum limit of patients has been reached
    if (*count >= 50) {
        printf("Cannot add more patients. Maximum limit reached (50).\n");
        return;
    }
    printf("\nEnter details for patient %d:\n", *count + 1);

    // Input validation for Patient ID (must be unique)
    while (1) {
        printf("Enter patient ID: ");
        scanf("%d", &patients[*count].patientID);

        int uniqueID = 1;
        for (int i = 0; i < *count; i++) {
            if (patients[i].patientID == patients[*count].patientID) {
                uniqueID = 0;
                printf("Patient ID: %d already exists. Please enter a unique ID.\n", patients[*count].patientID);
                break;
            }
        }
        if (uniqueID) {
            break;
        }
    }

    // Input patient name
    printf("Enter patient Name: ");
    scanf(" %[^\n]", patients[*count].name); // Space before %[^\n] consumes any leftover newline

    // Input validation for patient age (must be between 1 and 100)
    while (1) {
        printf("Enter patient age: ");
        scanf("%d", &patients[*count].age);

        if (patients[*count].age > 0 && patients[*count].age <= 100) {
            break;
        }
        printf("Invalid age. Please enter an age between 1 and 100.\n");
    }

    // Input patient diagnosis
    printf("Diagnosis: ");
    scanf(" %[^\n]", patients[*count].diagnose); // Space before %[^\n] consumes any leftover newline

    // Input validation for room number (must be a positive integer)
    while (1) {
        printf("Enter patient Room Number: ");
        scanf("%d", &patients[*count].roomNumber);

        if (patients[*count].roomNumber > 0) {
            break;
        }
        printf("Invalid room number. Please enter a positive number.\n");
    }

    (*count)++; // Increment the patient count
    printf("Patient added successfully!\n");
}

// Function to display all patient records
void displayAllPatients(struct Patient patients[], int count) {
    // Check if there are no patients to display
    if (count == 0) {
        printf("-----------------------\n");
        printf("No patients to display.\n");
        printf("-----------------------\n");
        return;
    }

    // Display all patient records in a structured format
    printf("\n--- List of Patients ---\n");
    for (int i = 0; i < count; i++) {
        printf("Patient ID: %d\n", patients[i].patientID);
        printf("Name: %s\n", patients[i].name);
        printf("Age: %d\n", patients[i].age);
        printf("Diagnosis: %s\n", patients[i].diagnose);
        printf("Room Number: %d\n", patients[i].roomNumber);
        printf("----------------------------\n");
    }
}

// Function to search for a patient by ID or name
void searchPatient(struct Patient patients[], int count) {
    // Check if there are no patients to search
    if (count == 0) {
        printf("No patients to search.\n");
        return;
    }

    int choice;
    printf("\nSearch by:\n");
    printf("1. Patient ID\n");
    printf("2. Patient Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Search by Patient ID
        int searchID;
        printf("Enter Patient ID: ");
        scanf("%d", &searchID);

        for (int i = 0; i < count; i++) {
            if (patients[i].patientID == searchID) {
                printf("\nPatient found!\n");
                printf("Patient ID: %d\n", patients[i].patientID);
                printf("Name: %s\n", patients[i].name);
                printf("Age: %d\n", patients[i].age);
                printf("Diagnosis: %s\n", patients[i].diagnose);
                printf("Room Number: %d\n", patients[i].roomNumber);
                return;
            }
        }
        printf("Patient with ID %d not found.\n", searchID);
    } else if (choice == 2) {
        // Search by Patient Name
        char searchName[100];
        printf("Enter Patient Name: ");
        scanf(" %[^\n]", searchName);

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcasecmp(patients[i].name, searchName) == 0) {
                printf("\nPatient found!\n");
                printf("Patient ID: %d\n", patients[i].patientID);
                printf("Name: %s\n", patients[i].name);
                printf("Age: %d\n", patients[i].age);
                printf("Diagnosis: %s\n", patients[i].diagnose);
                printf("Room Number: %d\n", patients[i].roomNumber);
                found = 1;
            }
        }
        if (!found) {
            printf("Patient with name '%s' not found.\n", searchName);
        }
    } else {
        printf("Invalid choice. Please enter 1 or 2.\n");
    }
}

// Function to discharge a patient (remove their record)
void dischargePatient(struct Patient patients[], int *count) {
    // Check if there are no patients to discharge
    if (*count == 0) {
        printf("No patients to discharge.\n");
        return;
    }

    int patientID, index = -1;
    printf("Enter Patient ID to discharge: ");
    scanf("%d", &patientID);

    // Find the patient by ID
    for (int i = 0; i < *count; i++) {
        if (patients[i].patientID == patientID) {
            index = i;
            break;
        }
    }

    // If patient not found, display an error message
    if (index == -1) {
        printf("Patient ID not found.\n");
        return;
    }

    // Shift all elements after the discharged patient to the left
    for (int i = index; i < *count - 1; i++) {
        patients[i] = patients[i + 1];
    }
    (*count)--; // Decrement the patient count
    printf("Patient with ID %d has been discharged.\n", patientID);
}

// Function to display the doctor schedule for the week
void displayDoctorSchedule(struct DoctorSchedule *schedule) {
    printf("\n--- Doctor Schedule for the Week ---\n");
    char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    char *shifts[] = {"Morning", "Afternoon", "Evening"};

    // Iterate through each day and shift to display the schedule
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%s: ", days[i]);
        for (int j = 0; j < SHIFTS_IN_DAY; j++) {
            if (strlen(schedule->schedule[i][j]) > 0) {
                printf("%s (%s) ", shifts[j], schedule->schedule[i][j]);
            } else {
                printf("%s (No doctor assigned) ", shifts[j]);
            }
        }
        printf("\n");
    }
}

// Function to assign a doctor to a specific shift on a specific day
void assignDoctorToShift(struct DoctorSchedule *schedule) {
    char doctorName[100];
    int day, shift;

    printf("\nEnter doctor's name: ");
    scanf(" %[^\n]", doctorName); // Space before %[^\n] consumes any leftover newline
    printf("Enter day of the week (0-Monday, 6-Sunday): ");
    scanf("%d", &day);
    printf("Enter shift (0-Morning, 1-Afternoon, 2-Evening): ");
    scanf("%d", &shift);

    // Validate day and shift inputs
    if (day < 0 || day >= DAYS_IN_WEEK || shift < 0 || shift >= SHIFTS_IN_DAY) {
        printf("Invalid input. Please enter valid day and shift.\n");
        return;
    }

    // Assign the doctor to the specified shift
    strcpy(schedule->schedule[day][shift], doctorName);

    printf("Doctor %s assigned to %s shift on %s.\n", doctorName,
           (shift == 0 ? "Morning" :
           (shift == 1 ? "Afternoon" : "Evening")),
           (day == 0 ? "Monday" : (day == 1 ? "Tuesday" :
           (day == 2 ? "Wednesday" : (day == 3 ?
           "Thursday" : (day == 4 ? "Friday" :
           (day == 5 ? "Saturday" : "Sunday")))))));
}

// Main function to run the program
int main() {
    struct Patient patients[50]; // Array to store up to 50 patients
    struct DoctorSchedule doctorSchedule = {0};  // Initialize doctor schedule with empty strings
    int patientCount = 0; // Counter to track the number of patients
    int choice;

    // Main loop to display the menu and handle user input
    while (1) {
        choice = displayMenu();
        switch (choice) {
            case 1:
                addPatient(patients, &patientCount);
                break;
            case 2:
                displayAllPatients(patients, patientCount);
                break;
            case 3:
                dischargePatient(patients, &patientCount);
                break;
            case 4:
                displayDoctorSchedule(&doctorSchedule);
                break;
            case 5:
                assignDoctorToShift(&doctorSchedule);
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    }
}