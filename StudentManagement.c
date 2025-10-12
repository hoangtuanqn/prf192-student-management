#include <stdio.h>
#include <string.h>

struct Student {
	char studentCode[15];
	char fullName[255];
	int birthYear;
	char major[255];
	float gpa;
	float scores[4]; // mặc định sẽ có 4 môn
};

void menu();
void addStudent(struct Student students[], int *currentStudent);
void displayAllStudent(struct Student students[], int currentStudent);
void deleteStudent(struct Student students[], int *currentStudent);
void clearEscape(char *str);
void deleteStudent(struct Student students[], int *currentStudent);
void editStudent(struct Student students[], int currentStudent);
void enterScores(struct Student students[], int currentStudent);
int findStudentByID(struct Student students[], int currentStudent, char studentCode[15]);
float calculateGPA(struct Student student);
void searchStudents(struct Student students[], int currentStudent);
void printInfoStudent(struct Student student);

const int MAX_STUDENTS = 200;
int currentStudent = 0;
struct Student students[200];

int main() {
	loadDataFormFile(students, &currentStudent);
	int choice;
	do {
		menu();
		scanf("%d", &choice);
		getchar();
		switch(choice) {
			case 1:
				displayAllStudent(students, currentStudent);
				break;
			case 2: 
				addStudent(students, &currentStudent);
				writeDataToFile(students, currentStudent);
				break;
			case 3:
				editStudent(students, currentStudent);
				writeDataToFile(students, currentStudent);
				break;
			case 4: 
				deleteStudent(students, &currentStudent);
				writeDataToFile(students, currentStudent);
				break;
			case 5:
				enterScores(students, currentStudent);
				writeDataToFile(students, currentStudent);
				break;
			case 6:
				searchStudents(students, currentStudent);
				break;
			case 7:
				handleSortStudent(students, currentStudent);
				break;
			case 0: 
				printf("\nExit programing successfully!");
				break;
			default: 
				printf("\nChoice invalid!\n");
		}
	} while(choice != 0);
}

int handleSortStudent(struct Student students[], int currentStudent) {
	int choice;
	do {
		menuSortStudent();
		scanf("%d", &choice);
		getchar();
		switch(choice) {
			case 1:
				// sort theo GPA
				sortStudentGPA(students, currentStudent);
				break;
			case 2: 

				// sort theo Name
				break;
			case 3:
				// sort theo birth year
				break;
			default: 
				printf("\nChoice invalid!\n");
		}
	} while(choice < 0 || choice > 3);
	
}

// đọc dữ liệu từ file
void loadDataFormFile(struct Student students[], int *currentStudent) {
	FILE *fp;
	fp = fopen("students.txt", "r");
	if (fp == NULL) {
        printf("\nCannot open file.");
        return;
    }
    
   int count = 0;
    while (count < MAX_STUDENTS) {
    	if (fgets(students[count].studentCode, sizeof(students[count].studentCode), fp) == NULL)
            break;
        clearEscape(students[count].studentCode);

        if (fgets(students[count].fullName, sizeof(students[count].fullName), fp) == NULL)
            break;
        clearEscape(students[count].fullName);

        if (fscanf(fp, "%d\n", &students[count].birthYear) != 1)
            break;

        if (fgets(students[count].major, sizeof(students[count].major), fp) == NULL)
            break;
        clearEscape(students[count].major);

        if (fscanf(fp, "%f\n", &students[count].gpa) != 1)
            break;

        if (fscanf(fp, "%f %f %f %f\n", 
            &students[count].scores[0], &students[count].scores[1],
            &students[count].scores[2], &students[count].scores[3]) != 4)
            break;

        count++;
    }
    *currentStudent = count;

    fclose(fp);
}

// ghi dữ liệu xuống file
void writeDataToFile(struct Student students[], int currentStudent) {
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL) {
        printf("\nCannot open file.");
        return;
    }

    for (int i = 0; i < currentStudent; i++) {
        fprintf(fp, "%s\n", students[i].studentCode);
        fprintf(fp, "%s\n", students[i].fullName);
        fprintf(fp, "%d\n", students[i].birthYear);
        fprintf(fp, "%s\n", students[i].major);
        fprintf(fp, "%.2f\n", students[i].gpa);
        fprintf(fp, "%.2f %.2f %.2f %.2f\n", 
            students[i].scores[0], students[i].scores[1],
            students[i].scores[2], students[i].scores[3]);
        fprintf(fp, "\n");
    }

    fclose(fp);
}

// menu gọi học sinh
void menu() {
	printf("\n=========== Manager Student ===========");
	printf("\n1. View all student");
	printf("\n2. Add student");
	printf("\n3. Edit student");
	printf("\n4. Delete student");
	printf("\n5. Enter score student");
	printf("\n6. Search for students");
	printf("\n7. Sort for students");
	printf("\n0. Exit!");
	printf("\nPlease enter your choice: ");
}
void menuSortStudent() {
	printf("\n=========== Sort Student ===========");
	printf("\n1. GPA");
	printf("\n2. Name");
	printf("\n3. Birth Year");
	printf("\n0. Return to Menu");
	printf("\nPlease enter your choice: ");
}

void sortStudentGPA(struct Student students[], int currentStudent) {
    for (int i = 0; i < currentStudent - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < currentStudent; j++) {
            if (students[j].gpa < students[minIdx].gpa) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            struct Student temp = students[i];
            students[i] = students[minIdx];
            students[minIdx] = temp;
        }
    }
    printf("\nStudents sorted by GPA successfully!\n");
}

// tìm kiếm học sinh
void searchStudents(struct Student students[], int currentStudent) {
	char keyword[255];
	int countStudent = 0;
	if(currentStudent == 0) { 
		printf("\nNo students to search!");
	} else {
		printf("\nEnter Student Code or Full Name Student: ");
		fgets(keyword, sizeof(keyword), stdin);
		clearEscape(keyword);
		
		for(int i = 0; i < currentStudent; ++i) {
			if(strstr(students[i].fullName, keyword) != NULL || strstr(students[i].studentCode, keyword) != NULL) {
				countStudent++;
				printInfoStudent(students[i]);
			}
		}
		printf("%d students found", countStudent);
	}
}

void enterScores(struct Student students[], int currentStudent) {
	char studentCode[15];
	if(currentStudent == 0) { 
		printf("\nNo students to enter score!");
	} else {
		printf("\nEnter Student Code: ");
		scanf("%s", studentCode);
		getchar();
		int idx = findStudentByID(students, currentStudent, studentCode);
		if(idx != -1) {
			for(int i = 0; i < 4; ++i) {
				printf("Enter %d subject score: ", i + 1);
				scanf("%f", &students[idx].scores[i]);
			}
			students[idx].gpa = calculateGPA(students[idx]);
			printf("Result %.2f", calculateGPA(students[idx]));
			printf("Score entered successfully");
		} else {
			printf("\nNo students found!");
		}
	}
}

// hàm nhập thông tin học sinh
void addStudent(struct Student students[], int *currentStudent) {
	if(*currentStudent >= MAX_STUDENTS) {
		printf("\nThe number of students has reached the limit!");
	} else {
		struct Student student;
		printf("===== Add Student =====");
		printf("\nEnter Student Code: ");
		scanf("%s", student.studentCode);
		getchar();	
		
		printf("Enter Full Name: ");
		fgets(student.fullName, sizeof(student.fullName), stdin);
		clearEscape(student.fullName);

		
		printf("Enter Birth Year: ");
		scanf("%d", &student.birthYear);
		getchar();
		
		printf("Enter Major: ");
		fgets(student.major, sizeof(student.major), stdin);
		clearEscape(student.major);

		students[(*currentStudent)++] = student;
		printf("\nAdd students successful!");
	}
}
float calculateGPA(struct Student student) {
	float sum = 0;
	for(int i = 0; i < 4; ++i) {
		sum += student.scores[i];
	}
	return sum / 4;
	
}

// hiển thị tất cả học sinh
void displayAllStudent(struct Student students[], int currentStudent) {
	if(currentStudent == 0) { 
		printf("\nNo students to display!");
	} else {
		printf("\n=========== Dislay All Info Student ===========");
		for(int i = 0; i < currentStudent; ++i) {
			printInfoStudent(students[i]);
		}
	}
}

void printInfoStudent(struct Student student) {
	printf("\n===============");
	printf("\nStudent Code: %s", student.studentCode);
	printf("\nFull Name: %s", student.fullName);
	printf("\nBirth Year: %d", student.birthYear);
	printf("\nMajor: %s", student.major);
	printf("\nGPA: %.2f", student.gpa);
	printf("\n===============\n");
}

// xóa kí tự xuống dòng ở cuối chuỗi
void clearEscape(char *str) {
	str[strcspn(str, "\n")] = '\0';
}

// xóa học sinh
void deleteStudent(struct Student students[], int *currentStudent) {
	char studentCode[15];
	if(*currentStudent == 0) { 
		printf("\nNo students to delete!");
	} else {
		printf("Enter Student Code: ");
		scanf("%s", studentCode);
		// tìm vị trí của học sinh
		int idx = findStudentByID(students, *currentStudent, studentCode);
		if(idx != -1) {
			for(int i = idx + 1; i < *currentStudent; ++i) {
				students[i - 1] = students[i];
			}
			(*currentStudent)--;
			printf("\nDelete students successful!");
		} else {
			printf("\nNo students found!");
		}
	}	
}
int findStudentByID(struct Student students[], int currentStudent, char studentCode[15]) {
	int idx = -1;
	for(int i = 0; i < currentStudent; ++i) {
		if(strcmp(students[i].studentCode, studentCode) == 0) {
			idx = i;
			break;
		}
	}
	return idx;
}

// cập nhật sinh viên
void editStudent(struct Student students[], int currentStudent) {
	char studentCode[15];
	struct Student student;
	if(currentStudent == 0) { 
		printf("\nNo students to edit!");
	} else {
		printf("Enter Student Code: ");
		scanf("%s", studentCode);
		getchar();
		
		// tìm vị trí của học sinh
		int idx = findStudentByID(students, currentStudent, studentCode);
		if(idx != -1) {
			
			printf("===== Edit Student: %s =====", students[idx].fullName);
			printf("\nEnter Full Name: ");
			fgets(student.fullName, sizeof(student.fullName), stdin);
			clearEscape(student.fullName);
	
			printf("Enter Birth Year: ");
			scanf("%d", &student.birthYear);
			getchar();
			
			printf("Enter Major: ");
			fgets(student.major, sizeof(student.major), stdin);
			clearEscape(student.major);
			
			strcpy(student.studentCode, students[idx].studentCode);
			students[idx] = student;
			
			printf("Update student successfully!");
		} else {
			printf("No students found!");
		}
	}	
}