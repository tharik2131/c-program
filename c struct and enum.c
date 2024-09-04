
#include <stdio.h>
#include <time.h> // Required for time functions

// Define enumeration for departments
enum Department {
    ACCOUNTS = 1,
    CLERICAL
};

// Define enumeration for experience-based enumeration percentages
enum Experience {
    LESS_THAN_3_YEARS = 2,
    THREE_TO_FIVE_YEARS = 5,
    MORE_THAN_FIVE_YEARS = 10
};

// Define the structure for an employee
struct Employee {
    int id;
    char name[50];
    char designation[50];
    float basicSalary;
    struct tm dateOfJoining; // Use struct tm to handle date
    enum Department department;
};

// Function to calculate experience-based enumeration for Accounts Department Head
float calculateAccountsEnumeration(int yearsOfService) {
    if (yearsOfService > 5) {
        return 0.10; // 10% enumeration
    } else if (yearsOfService >= 3) {
        return 0.05; // 5% enumeration
    } else {
        return 0.02; // 2% enumeration
    }
}

// Function to calculate experience-based enumeration for Clerical Head
float calculateClericalEnumeration(int yearsOfService) {
    if (yearsOfService > 5) {
        return 0.15; // 15% enumeration
    } else if (yearsOfService >= 3) {
        return 0.10; // 10% enumeration
    } else {
        return 0.05; // 5% enumeration
    }
}

// Function to calculate total salary based on basic salary, department, and experience
float calculateTotalSalary(float basicSalary, enum Department department, struct tm dateOfJoining) {
    // Get current date
    time_t now;
    time(&now);
    struct tm *currentDate = localtime(&now);

    // Calculate the number of years of service
    int yearsOfService = currentDate->tm_year - dateOfJoining.tm_year;
    if (currentDate->tm_mon < dateOfJoining.tm_mon ||
        (currentDate->tm_mon == dateOfJoining.tm_mon && currentDate->tm_mday < dateOfJoining.tm_mday)) {
        yearsOfService--;
    }

    // Calculate enumeration based on department and years of service
    float enumerationPercentage = 0;
    if (department == ACCOUNTS) {
        enumerationPercentage = calculateAccountsEnumeration(yearsOfService);
    } else if (department == CLERICAL) {
        enumerationPercentage = calculateClericalEnumeration(yearsOfService);
    }

    float enumeration = basicSalary * enumerationPercentage;
    return basicSalary + enumeration;
}

// Function to input employee details
void inputEmployee(struct Employee *emp) {
    printf("Enter employee ID: ");
    scanf("%d", &emp->id);
    printf("Enter employee name: ");
    scanf(" %[^\n]s", emp->name);
    printf("Enter designation: ");
    scanf(" %[^\n]s", emp->designation);
    printf("Enter basic salary: ");
    scanf("%f", &emp->basicSalary);

    // Input date of joining
    printf("Enter date of joining (dd mm yyyy): ");
    scanf("%d %d %d", &emp->dateOfJoining.tm_mday, &emp->dateOfJoining.tm_mon, &emp->dateOfJoining.tm_year);
    // tm_year is year since 1900
    emp->dateOfJoining.tm_year -= 1900;
    emp->dateOfJoining.tm_mon -= 1; // tm_mon is 0-based

    // Input department
    printf("Enter department (1 for Accounts, 2 for Clerical): ");
    scanf("%d", (int*)&emp->department);
}

// Function to display employee details
void displayEmployee(struct Employee emp) {
    printf("\nEmployee ID: %d\n", emp.id);
    printf("Name: %s\n", emp.name);
    printf("Designation: %s\n", emp.designation);
    printf("Basic Salary: %.2f\n", emp.basicSalary);
    printf("Date of Joining: %02d-%02d-%04d\n", emp.dateOfJoining.tm_mday, emp.dateOfJoining.tm_mon + 1, emp.dateOfJoining.tm_year + 1900);
    printf("Total Salary: %.2f\n", calculateTotalSalary(emp.basicSalary, emp.department, emp.dateOfJoining));
}

int main() {
    struct Employee emp;

    inputEmployee(&emp);
    displayEmployee(emp);

    return 0;
}

