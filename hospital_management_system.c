#include <stdio.h>
#include <string.h>

#define MAX_DOCTORS 50
#define DAYS_IN_WEEK 7
#define SHIFTS_IN_DAY 3

struct Patient {
    int patientID;
    int age;
    int roomNumber;
    char name[100];
    char diagnose[100];
};

struct DoctorSchedule {
    char schedule[DAYS_IN_WEEK][SHIFTS_IN_DAY][100];  // Doctor's name for each shift of each day
};

// Function for displaying the menu
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

// Function for adding a patient
void addPatient(struct Patient patients[], int *count) {
    if (*count >= 50) {
        printf("Cannot add more patients. Maximum limit reached (50).\n");
        return;
    }
    printf("\nEnter details for patient %d:\n", *count + 1);

    // Handle input validation for ID
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

    // Entering patient name
    printf("Enter patient Name: ");
    scanf(" %[^\n]", patients[*count].name); // Space before %[^\n] consumes any leftover newline

    // Handle input validation for age
    while (1) {
        printf("Enter patient age: ");
        scanf("%d", &patients[*count].age);

        if (patients[*count].age > 0 && patients[*count].age <= 100) {
            break;
        }
        printf("Invalid age. Please enter an age between 1 and 100.\n");
    }

    // Entering patient diagnosis
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

// Function to display all patients
void displayAllPatients(struct Patient patients[], int count) {
    if (count == 0) {
        printf("-----------------------\n");
        printf("No patients to display.\n");
        printf("-----------------------\n");
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

// Function to discharge a patient
void dischargePatient(struct Patient patients[], int *count) {
    if (*count == 0) {
        printf("No patients to discharge.\n");
        return;
    }

    int patientID, index = -1;
    printf("Enter Patient ID to discharge: ");
    scanf("%d", &patientID);

    for (int i = 0; i < *count; i++) {
        if (patients[i].patientID == patientID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Patient ID not found.\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        patients[i] = patients[i + 1];
    }
    (*count)--;
    printf("Patient with ID %d has been discharged.\n", patientID);
}

// Function to display doctor schedule
void displayDoctorSchedule(struct DoctorSchedule *schedule) {
    printf("\n--- Doctor Schedule for the Week ---\n");
    char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    char *shifts[] = {"Morning", "Afternoon", "Evening"};

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

// Function to assign doctor to shift
void assignDoctorToShift(struct DoctorSchedule *schedule) {
    char doctorName[100];
    int day, shift;

    printf("\nEnter doctor's name: ");
    scanf(" %[^\n]", doctorName); // Space before %[^\n] consumes any leftover newline
    printf("Enter day of the week (0-Monday, 6-Sunday): ");
    scanf("%d", &day);
    printf("Enter shift (0-Morning, 1-Afternoon, 2-Evening): ");
    scanf("%d", &shift);

    if (day < 0 || day >= DAYS_IN_WEEK || shift < 0 || shift >= SHIFTS_IN_DAY) {
        printf("Invalid input. Please enter valid day and shift.\n");
        return;
    }

    strcpy(schedule->schedule[day][shift], doctorName);

    printf("Doctor %s assigned to %s shift on %s.\n", doctorName,
           (shift == 0 ? "Morning" :
           (shift == 1 ? "Afternoon" : "Evening")),
           (day == 0 ? "Monday" : (day == 1 ? "Tuesday" :
           (day == 2 ? "Wednesday" : (day == 3 ?
           "Thursday" : (day == 4 ? "Friday" :
           (day == 5 ? "Saturday" : "Sunday")))))));
}

// Main function
int main() {
    struct Patient patients[50];
    struct DoctorSchedule doctorSchedule = {0};  // Initialize doctor schedule with empty strings
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
