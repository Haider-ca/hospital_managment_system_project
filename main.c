#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct Patient {
    int patientID;
    int age;
    int roomNumber;
    char name[100];
    char diagnose[100];

};

//Function for displaying the menu
int displayMenu() {
    int choice;
    printf("\n--- Patient Management System ---\n");
    printf("1. Add a new patient\n");
    printf("2. Display all patient records\n");
    printf("3. Search for a paitent\n");
    printf("4. Discharge a paitent\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

//Function for adding a patient
void addPatient(struct Patient patients[], int *count) {
    if (*count >= 50) {
        printf("Cannot add more patients. Maximum limit reached (50).\n");
        return;
    }
    printf("\nEnter details for patient %d:\n", *count + 1);

    //Handle input validation for ID
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

    //Entering patient name
    printf("Enter patient Name: ");
    scanf(" %[^\n]", patients[*count].name); // Space before %[^\n] consumes any leftover newline

    //Handle input validation for age
    while (1) {
        printf("Enter patient age: ");
        scanf("%d", &patients[*count].age);

        if (patients[*count].age > 0 && patients[*count].age <= 100) {
            break;
        }
        printf("Invalid age. Please enter an age between 1 and 100.\n");
    }

    //Entering patient diagnosis
    printf("Diagnosis: ");
    scanf(" %[^\n]", patients[*count].diagnose); // Space before %[^\n] consumes any leftover newline

    // Handle input validation for room number
    while (1) {
        printf("Enter patient Room Number: ");
        scanf("%d", &patients[*count].roomNumber);

        if (patients[*count].roomNumber > 0) {
            break;
        }
        printf("Invalid room number. Please enter a positive number.\n");
    }

    (*count)++;
    printf("Patient added successfully!\n");
}

//Function to display all patients
void displayAllPatients(struct Patient patients[], int count) {
    if (count == 0) {
        printf("No patients to display.\n");
        return;
    }

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

//Function to search for a patient by ID or name
void searchPatient(struct Patient patients[], int count) {
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
        //Search by ID
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
        //Search by name
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

int main() {
    struct Patient patients[50];
    int patientCount = 0;
    int choice;

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
                searchPatient(patients, patientCount);
            break;
            case 4:
                printf("Exiting the program. Goodbye!\n");
            return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    }
}