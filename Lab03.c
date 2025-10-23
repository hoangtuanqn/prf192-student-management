#include <stdio.h>
#include <string.h>

void menu();
void addStudent(char studentCode[15], char fullName[100], int *birthYear, char major[100], float *gpa);
void displayStudent(char studentCode[15], char fullName[50], int birthYear, char major[50], float gpa);
void enterScores(char studentCode[15], float *gpa);
void printInfoStudent(char studentCode[15], char fullName[50], int birthYear, char major[50], float gpa);
void editStudent(char studentCode[15], char fullName[50], int *birthYear, char major[50], float *gpa);
void classifyStudent(float gpa);
float enterValueFloat(float min, float max, char *prompt);
int enterValueInteger(int min, int max, char *prompt);
void enterValueString(char *value, int maxLength, char *prompt);

int main() {
    char studentCode[15] = "";
    char fullName[100] = "";
    int birthYear = 0;
    char major[100] = "";
    float gpa = 0.0;
    int choice;

    do {
        menu();
        scanf("%d", &choice);
        fflush(stdin);
        switch(choice) {
            case 1:
                displayStudent(studentCode, fullName, birthYear, major, gpa);
                break;
            case 2:
                addStudent(studentCode, fullName, &birthYear, major, &gpa);
                break;
            case 3:
                editStudent(studentCode, fullName, &birthYear, major, &gpa);
                break;
            case 4:
                enterScores(studentCode, &gpa);
                break;
            case 0:
                printf("\nExit successfully!\n");
                break;
            default:
                printf("\nChoice invalid!\n");
        }
    } while(choice != 0);

    return 0;
}
void menu() {
    printf("\n=========== Manager Student ===========");
    printf("\n1. View student information");
    printf("\n2. Add student");
    printf("\n3. Edit student");
    printf("\n4. Enter score student");
    printf("\n0. Exit!");
    printf("\nPlease enter your choice: ");
}

void displayStudent(char studentCode[15], char fullName[50], int birthYear, char major[50], float gpa) {
    if (strlen(studentCode) == 0) {
        printf("\nNo student information available.\n");
    } else {
        printInfoStudent(studentCode, fullName, birthYear, major, gpa);
    }
}

void printInfoStudent(char studentCode[15], char fullName[50], int birthYear, char major[50], float gpa) {
    printf("\n===============");
    printf("\nStudent Code: %s", studentCode);
    printf("\nFull Name: %s", fullName);
    printf("\nBirth Year: %d", birthYear);
    printf("\nMajor: %s", major);
    printf("\nGPA: %.2f", gpa);
    classifyStudent(gpa);
    printf("\n===============\n");
}

void addStudent(char studentCode[15], char fullName[50], int *birthYear, char major[50], float *gpa) {
    if (strlen(studentCode) > 0) {
        printf("\nStudent information already added!\n");
        return;
    }

    printf("===== Add Student =====\n");
    printf("Enter Student Code: ");
	scanf("%14s", studentCode);
	fflush(stdin);
	
    enterValueString(fullName, 100, "Enter Full Name: ");
    
    *birthYear = enterValueInteger(1980, 2025, "Enter Birth Year: ");
    
    enterValueString(major, 100, "Enter Major: ");
    
    printf("\nAdd student successful!\n");
}

void enterScores(char studentCode[15], float *gpa) {
    if (strlen(studentCode) == 0) {
        printf("\nNo student information available.\n");
        return;
    }

    *gpa = enterValueFloat(0, 4, "Enter GPA: ");
    printf("GPA entered successfully\n");
}

void editStudent(char studentCode[15], char fullName[50], int *birthYear, char major[50], float *gpa) {
    if (strlen(studentCode) == 0) {
        printf("\nNo student information available to edit.\n");
        return;
    }

    printf("===== Edit Student =====\n");
    enterValueString(fullName, 50, "Enter Full Name: ");
    
    *birthYear = enterValueInteger(1980, 2025, "Enter Birth Year: ");
    
    enterValueString(major, 50, "Enter Major: ");
    
    printf("Update student successfully!\n");
}

void classifyStudent(float gpa) {
    printf("Academic performance: ");
    if (gpa >= 3.6) 
        printf("Excellent\n");
    else if (gpa >= 3) 
        printf("Very Good\n");
    else if (gpa >= 2.5) 
        printf("Good\n");
    else if (gpa >= 2) 
        printf("Average\n");
    else 
        printf("Poor\n");
}

int enterValueInteger(int min, int max, char *prompt) {
    int value;
    do {
        printf("%s", prompt);
        scanf("%d", &value);
        fflush(stdin);
        if(value < min || value > max) {
            printf("Value invalid. Value must be between %d and %d\n", min, max);
        }
    } while(value < min || value > max);
    return value;
}

float enterValueFloat(float min, float max, char *prompt) {
    float value;
    do {
        printf("%s", prompt);
        scanf("%f", &value);
        fflush(stdin);
        if(value < min || value > max) {
            printf("Value invalid. Value must be between %.2f and %.2f\n", min, max);
        }
    } while(value < min || value > max);
    return value;
}

void enterValueString(char *variable, int maxLength, char *prompt) {

    do {
    	printf("%s", prompt);
		scanf("%99^\n]", variable);
		fflush(stdin);
		
		if(strlen(variable) == 0 || strlen(variable) > maxLength) {
			printf("Input invalid. Please enter a valid value.\n");
		}
		
	} while(strlen(variable) == 0 || strlen(variable) > maxLength);

}
