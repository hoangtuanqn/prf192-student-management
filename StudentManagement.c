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

const int MAX_STUDENTS = 200;
int currentStudent = 0;
struct Student students[200];

int main() {
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
				break;
			case 3:
				editStudent(students, currentStudent);
				break;
			case 4: 
				deleteStudent(students, &currentStudent);
				break;
			case 5:
				// nhập điểm cho từng sinh viên
				enterScores(students, currentStudent);
				break;
			case 6:
				// 
				break;
			case 0: 
//				deleteStudent(students, &currentStudent);
				// exit
				break;
			default: 
				printf("\nChoice invalid!\n");
		}
	} while(choice != 0);
}

// menu gọi học sinh
void menu() {
	printf("\n=========== Manager Student ===========");
	printf("\n1. View all student");
	printf("\n2. Add student");
	printf("\n3. Edit student");
	printf("\n4. Delete student");
	printf("\n5. Enter score student");
	printf("\n0. Exit!");
	printf("\nPlease enter your choice: ");
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
			printf("\n=== Student %d ===", i + 1);
			printf("\nStudent Code: %s", students[i].studentCode);
			printf("\nFull Name: %s", students[i].fullName);
			printf("\nBirth Year: %d", students[i].birthYear);
			printf("\nMajor: %s", students[i].major);
			printf("\nGPA: %.2f", students[i].gpa);
			printf("\n===============\n");
		}
	}
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