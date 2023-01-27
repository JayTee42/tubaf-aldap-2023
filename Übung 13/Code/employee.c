#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 20

typedef enum {
	DEP_HR,
	DEP_MARKETING,
	DEP_MANAGEMENT
} department_t;

typedef struct {
	char first_name[MAX_NAME_LEN + 1];
	char last_name[MAX_NAME_LEN + 1];
	float salary;
	department_t department;
} employee_t;

const char* get_department_str(department_t department) {
	switch (department) {
		case DEP_HR: return "Human resources";
		case DEP_MARKETING: return "Marketing";
		case DEP_MANAGEMENT: return "Management";
		default: return "Unknwon department";
	}
}

void print_employee(const employee_t* employee) {
	printf(
		"{ first_name: \"%s\", last_name: \"%s\", salary: %.2f €, department: %s }\n",
		employee->first_name,
		employee->last_name,
		employee->salary,
		get_department_str(employee->department)
	);
}

void print_employees(const employee_t* employees, size_t len) {
	for (size_t i = 0; i < len; i++) {
		print_employee(&employees[i]);
	}
}

void adjust_salary(employee_t* employee, float new_salary) {
	printf("Before salary adjustment: ");
	print_employee(employee);

	employee->salary = new_salary;

	printf("After salary adjustment: ");
	print_employee(employee);
}

void adjust_department(
	employee_t* employee,
	department_t new_department
) {
	printf("Before department transfer: ");
	print_employee(employee);

	// Ensure that the departments are different:
	if (employee->department == new_department) {
		printf(
			"%s is already in %s, cancelling transfer ...\n",
			employee->first_name,
			get_department_str(employee->department)
		);

		return;
	}

	employee->department = new_department;

	printf("After department transfer: ");
	print_employee(employee);
}

void adjust_last_name(
	employee_t* employee,
	const char* new_last_name
) {
	printf("Before name change: ");
	print_employee(employee);

	if (strlen(new_last_name) > MAX_NAME_LEN) {
		printf("Stop hacking your salary!\n");
		return;
	}

	strcpy(employee->last_name, new_last_name);

	printf("After name change: ");
	print_employee(employee);
}

int main(void) {
	// b)
	employee_t max = {
		.first_name = "Max",
		.last_name = "Mustermann",
		.salary = 4500.59,
		.department = DEP_HR
	};

	// c)
	printf("Max: ");
	print_employee(&max);
	printf("=================\n");

	// d)
	adjust_salary(&max, 4800.25);
	printf("=================\n");

	// e)
	adjust_department(&max, DEP_MANAGEMENT);
	adjust_department(&max, DEP_MANAGEMENT);
	printf("=================\n");

	// f)
	adjust_last_name(&max, "Meyer");
	printf("=================\n");

	// g)
	employee_t employees[] = {
		{
			.first_name = "Harry",
			.last_name = "Potter",
			.salary = 6200.38,
			.department = DEP_MARKETING
		},
		{
			.first_name = "Draco",
			.last_name = "Malfoy",
			.salary = 3300.68,
			.department = DEP_HR
		},
		{
			.first_name = "Ron",
			.last_name = "Weasley",
			.salary = 5900.24,
			.department = DEP_MARKETING
		},
		{
			.first_name = "Hermione",
			.last_name = "Granger",
			.salary = 7300.87,
			.department = DEP_MANAGEMENT
		}
	};

	print_employees(employees, 4);
	printf("=================\n");

	// i)
	// TODO ... magic
	print_employees(employees, 3);
}