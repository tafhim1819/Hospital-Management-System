#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100

// Patient Structure
typedef struct
{
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[50];
    char doctor[50];
    float cost;
} Patient;

Patient patients[MAX_PATIENTS];
int patientCount = 0;

// Function Declarations
void addPatient();
void displayPatients();
void searchPatient();
void updatePatient();
void assignDoctor();
void calculateCost();
void clearInputBuffer();

int main()
{
    int choice;

    while (1)
    {
        printf("\n=========================================\n");
        printf("     HOSPITAL MANAGEMENT SYSTEM          \n");
        printf("=========================================\n");
        printf("1. Add Patient Information\n");
        printf("2. Display All Patients\n");
        printf("3. Search Patient by Patient ID\n");
        printf("4. Update Patient Information\n");
        printf("5. Assign Doctor to a Patient\n");
        printf("6. Calculate and Display Treatment Cost\n");
        printf("7. Exit\n");
        printf("-----------------------------------------\n");
        printf("Enter your choice (1-7): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
        case 1:
            addPatient();
            break;
        case 2:
            displayPatients();
            break;
        case 3:
            searchPatient();
            break;
        case 4:
            updatePatient();
            break;
        case 5:
            assignDoctor();
            break;
        case 6:
            calculateCost();
            break;
        case 7:
            printf("\nExiting Program. Thank you!\n");
            exit(0);
        default:
            printf("\nInvalid choice! Please choose between 1 and 7.\n");
        }
    }

    return 0;
}

// Function to clear input buffer
void clearInputBuffer()
{
    while (getchar() != '\n');
}

// 1. Add Patient Information
void addPatient()
{
    if (patientCount >= MAX_PATIENTS)
    {
        printf("\n[Error] Hospital database is full!\n");
        return;
    }

    Patient p;
    printf("\n--- Add New Patient ---\n");
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    clearInputBuffer();

    // Check for duplicate ID
    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].id == p.id)
        {
            printf("[Error] Patient with ID %d already exists!\n", p.id);
            return;
        }
    }

    printf("Enter Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0; // Remove newline

    printf("Enter Age: ");
    scanf("%d", &p.age);
    clearInputBuffer();

    printf("Enter Gender: ");
    fgets(p.gender, sizeof(p.gender), stdin);
    p.gender[strcspn(p.gender, "\n")] = 0;

    printf("Enter Disease: ");
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

    strcpy(p.doctor, "Not Assigned");
    p.cost = 0.0;

    patients[patientCount++] = p;
    printf("\n[Success] Patient added successfully!\n");
}

// 2. Display All Patients
void displayPatients()
{
    if (patientCount == 0)
    {
        printf("\n[Info] No patient records found.\n");
        return;
    }

    printf("\n--------------------------------------------------------------------------------------------------------\n");
    printf("%-8s | %-20s | %-5s | %-8s | %-15s | %-18s | %-10s\n", "ID", "Name", "Age", "Gender", "Disease", "Doctor", "Cost ($)");
    printf("--------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < patientCount; i++)
    {
        printf("%-8d | %-20s | %-5d | %-8s | %-15s | %-18s | %-10.2f\n",
               patients[i].id, patients[i].name, patients[i].age,
               patients[i].gender, patients[i].disease,
               patients[i].doctor, patients[i].cost);
    }
    printf("--------------------------------------------------------------------------------------------------------\n");
}

// 3. Search Patient by Patient ID
void searchPatient()
{
    if (patientCount == 0)
    {
        printf("\n[Info] No patient records available.\n");
        return;
    }

    int id, found = 0;
    printf("\nEnter Patient ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].id == id)
        {
            printf("\n--- Patient Details ---\n");
            printf("ID          : %d\n", patients[i].id);
            printf("Name        : %s\n", patients[i].name);
            printf("Age         : %d\n", patients[i].age);
            printf("Gender      : %s\n", patients[i].gender);
            printf("Disease     : %s\n", patients[i].disease);
            printf("Doctor      : %s\n", patients[i].doctor);
            printf("Cost ($)    : %.2f\n", patients[i].cost);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\n[Error] Patient with ID %d not found.\n", id);
    }
}

// 4. Update Patient Information
void updatePatient()
{
    if (patientCount == 0)
    {
        printf("\n[Info] No patient records available to update.\n");
        return;
    }

    int id, found = 0;
    printf("\nEnter Patient ID to update: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].id == id)
        {
            printf("\n--- Update Info for ID: %d ---\n", id);

            printf("Enter New Name: ");
            fgets(patients[i].name, sizeof(patients[i].name), stdin);
            patients[i].name[strcspn(patients[i].name, "\n")] = 0;

            printf("Enter New Age: ");
            scanf("%d", &patients[i].age);
            clearInputBuffer();

            printf("Enter New Gender: ");
            fgets(patients[i].gender, sizeof(patients[i].gender), stdin);
            patients[i].gender[strcspn(patients[i].gender, "\n")] = 0;

            printf("Enter New Disease: ");
            fgets(patients[i].disease, sizeof(patients[i].disease), stdin);
            patients[i].disease[strcspn(patients[i].disease, "\n")] = 0;

            printf("\n[Success] Patient information updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\n[Error] Patient with ID %d not found.\n", id);
    }
}

// 5. Assign Doctor to a Patient
void assignDoctor()
{
    if (patientCount == 0)
    {
        printf("\n[Info] No patient records available.\n");
        return;
    }

    int id, found = 0;
    printf("\nEnter Patient ID to assign doctor: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].id == id)
        {
            printf("Enter Doctor's Name: ");
            fgets(patients[i].doctor, sizeof(patients[i].doctor), stdin);
            patients[i].doctor[strcspn(patients[i].doctor, "\n")] = 0;

            printf("\n[Success] Doctor assigned to Patient ID %d successfully!\n", id);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\n[Error] Patient with ID %d not found.\n", id);
    }
}

// 6. Calculate and Display Treatment Cost
void calculateCost()
{
    if (patientCount == 0)
    {
        printf("\n[Info] No patient records available.\n");
        return;
    }

    int id, found = 0;
    printf("\nEnter Patient ID to calculate cost: ");
    scanf("%d", &id);

    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].id == id)
        {
            float doctorFee, medicineCost, roomCharge;

            printf("\n--- Calculate Treatment Cost for ID: %d ---\n", id);
            printf("Enter Doctor Fee ($): ");
            scanf("%f", &doctorFee);
            printf("Enter Medicine Cost ($): ");
            scanf("%f", &medicineCost);
            printf("Enter Hospital/Room Charge ($): ");
            scanf("%f", &roomCharge);

            patients[i].cost = doctorFee + medicineCost + roomCharge;

            printf("\n-----------------------------------------\n");
            printf(" Total Treatment Cost: $%.2f\n", patients[i].cost);
            printf("-----------------------------------------\n");
            printf("[Success] Cost updated for Patient ID %d!\n", id);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\n[Error] Patient with ID %d not found.\n", id);
    }
}
