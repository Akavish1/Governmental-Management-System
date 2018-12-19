#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <assert.h>
#include "MinUnit.h"

///START OF DECLARATIONS
typedef struct database {
	char firstname[20];
	char lastname[20];
	int id;
	char dateofbirth[11];
	char address[60];
	char gender[10];
	char telnumber[15];
	char cellnumber[15];
	char fathername[20];
	char mothername[20];
	char grandfathername[20];
	char religion[15];
	char placeofbirth[60];
	char goodconductcert[10];
} database;

typedef struct passport {
	char firstname[20];
	char lastname[20];
	int id;
	char validity[11];
	char needsrenewal[10];
	char countryoforigin[20];
}passport;

typedef struct user {
	int id;
	char username[20];
	char password[20];
	int permission;
}user;
///END OF DECLARATIONS

///COUNT FUNCTIONS
//counts how many people there are in the database file
int numofpersons() {
	FILE *fp;
	int count = 0;
	char line[512];
	fp = fopen("data.txt", "r");
	if (fp == NULL) {
		printf("Error opening data file\n");
		return 0;
	}
	while (fgets(line, 512, fp) != NULL){
		count++;
	}
	fclose(fp);
	return count;
}

//passes
MU_TEST(test_numofpersons) {
	//arrange
	int nopcheck = 6;
	//act
	int result = numofpersons();
	//assert
	mu_check(result == nopcheck);
}

//counts how many users there are in the users file
int numofusers() {
	FILE *fp;
	int count = 0;
	char line[512];
	fp = fopen("users.txt", "r");
	if (fp == NULL) {
		printf("Error opening users file\n");
		return 0;
	}
	while (fgets(line, 512, fp) != NULL) {
		count++;
	}
	fclose(fp);
	return count;
}

//passes
MU_TEST(test_numofusers) {
	//arrange
	int noucheck = 5;
	//act
	int result = numofusers();
	//assert
	mu_check(result == noucheck);
}

//counts how many passports there are in the passports file
int numofpassports() {
	FILE *fp;
	int count = 0;
	char line[512];
	fp = fopen("passports.txt", "r");
	if (fp == NULL) {
		printf("Error opening passports file\n");
		return 0;
	}
	while (fgets(line, 512, fp) != NULL) {
		count++;
	}
	fclose(fp);
	return count;
}

//fails
MU_TEST(test_numofpassports) {
	//arrange
	int nopcheck = 0;
	//act
	int result = numofpassports();
	//assert
	mu_assert(result < nopcheck, "\nWrong statement, Passport file contains 7 persons, 7>0 0\n");
}
///END OF COUNT FUNCTIONS

///START OF ARRAY INPUT 
//copies the database file's contents into an array of database structs so it can be used dynamically
void filldatabase(database *dbarr) {
	FILE *fp;
	int i = 0;
	fp = fopen("data.txt", "r");
	if (fp == NULL) {
		printf("Error opening data file\n");
		return;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d %s %s %s %s %s %s %s %s %s %s %s \n", &dbarr[i].firstname, &dbarr[i].lastname, &dbarr[i].id, &dbarr[i].dateofbirth, &dbarr[i].address, &dbarr[i].telnumber, &dbarr[i].cellnumber, &dbarr[i].fathername, &dbarr[i].mothername, &dbarr[i].grandfathername, &dbarr[i].religion, &dbarr[i].placeofbirth, &dbarr[i].gender, &dbarr[i].goodconductcert);
		i++;
	}
	fclose(fp);
}

//copies the users file's contents into an array of user structs so it can be used dynamically
void filluser(user *userarr) {
	FILE *fp;
	int i = 0;
	fp = fopen("users.txt", "r");
	if (fp == NULL) {
		printf("Error opening users file\n");
		return;
	}
	while (!feof(fp)) {
		fscanf(fp, "%d %s %s %d", &userarr[i].id, &userarr[i].username, &userarr[i].password, &userarr[i].permission);
		i++;
	}
	fclose(fp);
}

//copies the passports file's contents into an array of passports structs so it can be used dynamically
void fillpassport(passport *passportarr) {
	FILE *fp;
	int i = 0;
	fp = fopen("passports.txt", "r");
	if (fp == NULL) {
		printf("Error opening passports file\n");
		return;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d %s %s %s", &passportarr[i].firstname, &passportarr[i].lastname, &passportarr[i].id, &passportarr[i].validity, &passportarr[i].needsrenewal, &passportarr[i].countryoforigin);
		i++;
	}
	fclose(fp);
}
///END OF ARRAY INPUT

///START OF ARRAY INITIALIZATIONS
//database array initialization
database *dbinit() {
	database *dbarr;
	dbarr = (database *)malloc(numofpersons() * sizeof(database));
	filldatabase(dbarr);
	return dbarr;
}

//passes
MU_TEST(test_dbinit) {
	//arrange
	database *dbarr;
	dbarr = (database *)malloc(numofpersons() * sizeof(database));
	//act
	int result = sizeof(dbinit());
	//assert
	mu_check(result == sizeof(dbarr));
}

//users array initialization
user *userinit() {
	user *userarr;
	userarr = (user *)malloc(numofpersons() * sizeof(user));
	filluser(userarr);
	return userarr;
}

//fails
MU_TEST(test_userinit) {
	//arrange
	user *userarr;
	userarr = (user *)malloc(numofusers() * sizeof(user));
	//act
	int result = sizeof(userinit());
	//assert
	mu_assert(result > sizeof(userarr), "\nWrong statement, they are the same size\n");
}

//passports array initialization
passport *passportinit() {
	passport *passportarr;
	passportarr = (passport *)malloc(numofpassports() * sizeof(passport));
	fillpassport(passportarr);
	return passportarr;
}

//passes
MU_TEST(test_passportinit) {
	//arrange
	passport *passportarr;
	passportarr = (passport *)malloc(numofpassports() * sizeof(passport));
	//act
	int result = sizeof(passportinit());
	//assert
	mu_check(result == sizeof(passportarr));
}
///END OF ARRAY INITIALIZATIONS

///START OF VALIDATION FUNCTIONS
//validates an ID input (an integer of 9 digits)
int validateid() {
	int id = 0;
	int ch = 0;
	printf("Enter a valid ID number\n");
	while (id < 100000000 || id > 999999999) {
		if (scanf("%d", &id) == 1) {
			if (id > 100000000 && id < 999999999) {
				break;
			}
			else {
				printf("Invalid input, try again\n");
			}
		}
		else {
			printf("Invalid input, try again\n");
			while ((ch = getchar()) != '\n') {
				if (ch == EOF) {
					fprintf(stderr, "problem getting input\n");
					return 1;
				}
			}
		}
	}
	return id;
}

//passes
MU_TEST(test_validateid) {
	//arrange
	int id = 123456789;
	//act
	int result = validateid(); //entering 123456789
	//assert
	mu_check(result == 123456789);
}

//login function - returns the user's permission level or -1 if the credentials are incorrect
int login(user *users, int id) {
	char username[20];
	char password[20];
	int i = 0;
	printf("Enter your user name : \n");
	scanf("%s", &username);
	printf("Enter your password : \n");
	scanf("%s", &password);
	while (i < numofusers()) {
		if (id == users[i].id && !strcmp(username, users[i].username) && !strcmp(password, users[i].password)) {
			printf("Login successful, welcome %s\n", users[i].username);
			return users[i].permission;
		}
		i++;
	}
	printf("Login failed, Invalid credentials\n");
	return -1;
}

//fails
MU_TEST(test_login) {
	//arrange
	int id = 123456789;
	user *userscheck = userinit();
	//act
	int result = login(userscheck, id);
	//assert
	mu_assert(result == 2, "\nreturns -1 when wrong credentials are entered\n");
}
///END OF VALIDATION FUNCTIONS

//frees the memory
void freearrs(database *dbarr, user *userarr, passport *passportsarr) {
	free(dbarr);
	free(userarr);
	free(passportsarr);
}

///START OF GET FUNCTIONS
///DATABASE GETS
//scans an id number and prints the name and gender associated with it
void getname(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			if (!strcmp(dbarr[i].gender, "male") || !strcmp(dbarr[i].gender, "MALE")) {
				printf("First name = %s\nLast name = %s\nGender = Male\n", dbarr[i].firstname, dbarr[i].lastname);
				return;
			}
			else if (!strcmp(dbarr[i].gender, "female") || !strcmp(dbarr[i].gender, "FEMALE")) {
				printf("First name = %s\nLast name = %s\nGender = Female\n", dbarr[i].firstname, dbarr[i].lastname);
				return;
			}
		}
		i++;
	}
	printf("ID isnt in the database - person not found\n");
}

//scans for a last name and finds the id number associated with it
void getid(database *dbarr) {
	char lastname[100];
	int i = 0;
	printf("Enter a last name of find an associated ID number\n");
	scanf("%s", &lastname);
	while (i < numofpersons()) {
		if (!strcmp(lastname, dbarr[i].lastname)) {
			printf("ID = %d\n", dbarr[i].id);
			return;
		}
		i++;
	}
	printf("Last name is not in the database - person not found\n");
}

//scans for an id number and prints the date of birth associated with it
void getdateofbirth(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("date of birth = %s\n", dbarr[i].dateofbirth);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//scans for an id number and prints the address associated with it
void getaddress(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Address = %s\n", dbarr[i].address);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//scans for an id number and prints the telehpone number associated with it
void gettelnumber(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Telephone number = %s\n", dbarr[i].telnumber);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//scans for an id number and prints the cellular number associated with it
void getcellnumber(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Cellular number = %s\n", dbarr[i].cellnumber);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//scans for an id number and prints father, mother and grandfather names associated with it
void getparentsnames(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Father's name = %s\nMother's name = %s\nGrandfather's name = %s\n", dbarr[i].fathername, dbarr[i].mothername, dbarr[i].grandfathername);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//scans for an id number and prints religion associated with it
void getreligion(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Religion = %s\n", dbarr[i].religion);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//scans for an id number and prints the place of birth associated with it
void getplaceofbirth(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Place of birth = %s\n", dbarr[i].placeofbirth);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//scans for an id number and prints whether the associated person is eligible of a certificate of good conduct
void goodconductcert(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			if (!strcmp(dbarr[i].goodconductcert, "yes") || !strcmp(dbarr[i].goodconductcert, "YES")) {
				printf("%s %s is eligible for a certificate of good conduct - has NO criminal record!\n", dbarr[i].firstname, dbarr[i].lastname);
				return;
			}
			else if (!strcmp(dbarr[i].goodconductcert, "no") || !strcmp(dbarr[i].goodconductcert, "NO")) {
				printf("%s %s is NOT eligible for a certificate of good conduct - has criminal record!\n", dbarr[i].firstname, dbarr[i].lastname);
				return;
			}
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}
///END OF DATABASE GETS

///USER GETS
//scans for an id number and prints the user name and password associated with it
void getuserdetails(user *userarr, int id) {
	int i = 0;
	while (i < numofusers()) {
		if (id == userarr[i].id) {
			printf("User name = %s\nPassword = %s\n", userarr[i].username, userarr[i].password);
			if (userarr[i].permission == 0) {
				printf("A normal user\n");
			}
			if (userarr[i].permission == 1) {
				printf("A user with database editing permissions\n");
			}
			if (userarr[i].permission == 2) {
				printf("User is an administrator\n");
			}
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}
///END OF USER GETS

///PASSPORT GETS
//scans for an id number and prints the names of the passport owner associated with it.
void getpassportname(passport *passportarr, int id) {
	int i = 0;
	while (i < numofpassports()) {
		if (id == passportarr[i].id) {
			printf("First name = %s\nLast name = %s\nCountry of origin(passport's) = %s\n", passportarr[i].firstname, passportarr[i].lastname, passportarr[i].countryoforigin);
			return;
		}
		i++;
	}
	printf("ID isnt in the database - person not found\n");
}

//scans for an id number and prints the associated passport's expiration date and whether it needs to be renewed.
void getpassportdates(passport *passportarr, int id) {
	int i = 0;
	while (i < numofpassports()) {
		if (id == passportarr[i].id) {
			if (!strcmp(passportarr[i].needsrenewal, "yes") || !strcmp(passportarr[i].needsrenewal, "YES")) {
				printf("Passport expiration date is %s - needs renewal!\n", passportarr[i].validity);
				return;
			}
			else if (!strcmp(passportarr[i].needsrenewal, "no") || !strcmp(passportarr[i].needsrenewal, "NO")) {
				printf("Passport expiration date is %s - up to date\n", passportarr[i].validity);
				return;
			}
		}
		i++;
	}
	printf("ID isnt in the database - person not found\n");
}
///END OF PASSPORT GETS
///END OF GET FUNCTIONS

///START OF ARRAY OUTPUT
//output from data.txt into dbarr
void rewritedata(database *dbarr) {
	FILE *fp;
	int i = 0;
	char line[512];
	int oldsize = numofpersons();
	fp = fopen("data.txt", "w+");
	if (fp == NULL) {
		printf("Error opening data file\n");
		return;
	}
	while (i < oldsize) {
		fprintf(fp, "%s %s %d %s %s %s %s %s %s %s %s %s %s %s \n", dbarr[i].firstname, dbarr[i].lastname, dbarr[i].id, dbarr[i].dateofbirth, dbarr[i].address, dbarr[i].telnumber, dbarr[i].cellnumber, &dbarr[i].fathername, &dbarr[i].mothername, &dbarr[i].grandfathername, dbarr[i].religion, dbarr[i].placeofbirth, dbarr[i].gender, dbarr[i].goodconductcert);
		i++;
	}
	fclose(fp);
}

//output from users.txt into userarr
void rewriteusers(user *userarr) {
	FILE *fp;
	int i = 0;
	char line[512];
	int oldsize = numofusers();
	fp = fopen("users.txt", "w+");
	if (fp == NULL) {
		printf("Error opening users file\n");
		return;
	}
	while (i < oldsize) {
		fprintf(fp, "%d %s %s %d \n", userarr[i].id, userarr[i].username, userarr[i].password, userarr[i].permission);
		i++;
	}
	fclose(fp);
}

//output from passports.txt into passportarr
void rewritepassports(passport *passportarr) {
	FILE *fp;
	int i = 0;
	char line[512];
	int oldsize = numofpassports();
	fp = fopen("passports.txt", "w+");
	if (fp == NULL) {
		printf("Error opening passports file\n");
		return;
	}
	while (i < oldsize) {
		fprintf(fp, "%s %s %d %s %s %s \n", passportarr[i].firstname, passportarr[i].lastname, passportarr[i].id, passportarr[i].validity, passportarr[i].needsrenewal, passportarr[i].countryoforigin);
		i++;
	}
	fclose(fp);
}
///END OF ARRAY OUTPUT

//ID printing query
void printdbid(database *dbarr) {
	int i = 0;
	printf("The following ID numbers are in the database - \n");
	while (i < numofpersons()) {
		printf("%d. %d\n", i + 1, dbarr[i].id);
		i++;
	}
}

///START OF SETS
///START OF DATABASE SETS
//edits a person's first name
void setfirstname(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Enter a new first name\n");
			scanf("%s", &dbarr[i].firstname);
			rewritedata(dbarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a person's last name
void setlastname(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Enter a new last name\n");
			scanf("%s", &dbarr[i].lastname);
			rewritedata(dbarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a person's date of birth
void setdateofbirth(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Enter a new date - format dd/mm/yyyy\n");
			scanf("%s", &dbarr[i].dateofbirth);
			rewritedata(dbarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a person's address
void setaddress(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Enter a new address - format streetname-xx,city (no spaces)\n");
			scanf("%s", &dbarr[i].address);
			rewritedata(dbarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a person's gender
void setgender(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Enter a new gender - male or female\n");
			scanf("%s", &dbarr[i].gender);
			rewritedata(dbarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a person's telephone number
void settelnumber(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Enter a new telephone number\n");
			scanf("%s", &dbarr[i].telnumber);
			rewritedata(dbarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a person's cellular number
void setcellnumber(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Enter a new cellular number\n");
			scanf("%s", &dbarr[i].cellnumber);
			rewritedata(dbarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a person's father's name
void setfathername(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Enter a new father's name\n");
			scanf("%s", &dbarr[i].fathername);
			rewritedata(dbarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a person's mother's name
void setmothername(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Enter a new mother's name\n");
			scanf("%s", &dbarr[i].mothername);
			rewritedata(dbarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a person's grandfather's name
void setgrandfathername(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Enter a new grandfather's name\n");
			scanf("%s", &dbarr[i].grandfathername);
			rewritedata(dbarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a person's religion
void setreligion(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Enter a new religion\n");
			scanf("%s", &dbarr[i].religion);
			rewritedata(dbarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a person's certification for good conduct
void setgoodconductcert(database *dbarr, int id) {
	int i = 0;
	while (i < numofpersons()) {
		if (id == dbarr[i].id) {
			printf("Enter a new certification level - yes if certified, no if not \n");
			scanf("%s", &dbarr[i].goodconductcert);
			rewritedata(dbarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}
///END OF DATABASE SETS

///START OF USER SETS
//edits a user's user name
void setusername(user *userarr, int id) {
	int i = 0;
	while (i < numofusers()) {
		if (id == userarr[i].id) {
			printf("Enter a new user name\n");
			scanf("%s", &userarr[i].username);
			rewriteusers(userarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a user's password
void setuserpassword(user *userarr, int id) {
	int i = 0;
	while (i < numofusers()) {
		if (id == userarr[i].id) {
			printf("Enter a new password\n");
			scanf("%s", &userarr[i].password);
			rewriteusers(userarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a user's permission level
void setuserpermission(user *userarr, int id) {
	int i = 0;
	while (i < numofusers()) {
		if (id == userarr[i].id) {
			printf("Enter a new permission level - 0 for a normal user, 1 for a manager, 2 for an administrator\n");
			scanf("%d", &userarr[i].permission);
			rewriteusers(userarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}
///END OF USER SETS

///START OF PASSPORT SETS
//edits a passport's first name
void setpassportfirstname(passport *passportarr, int id) {
	int i = 0;
	while (i < numofpassports()) {
		if (id == passportarr[i].id) {
			printf("Enter a new first name\n");
			scanf("%s", &passportarr[i].firstname);
			rewritepassports(passportarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a passport last name
void setpassportlastname(passport *passportarr, int id) {
	int i = 0;
	while (i < numofpassports()) {
		if (id == passportarr[i].id) {
			printf("Enter a new last name\n");
			scanf("%s", &passportarr[i].lastname);
			rewritepassports(passportarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits a passport expiration date
void setpassportvalidity(passport *passportarr, int id) {
	int i = 0;
	while (i < numofpassports()) {
		if (id == passportarr[i].id) {
			printf("Enter a new validity - format dd/mm/yyyy\n");
			scanf("%s", &passportarr[i].validity);
			rewritepassports(passportarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}

//edits whether the passport needs renewal
void setpassportrenewal(passport *passportarr, int id) {
	int i = 0;
	while (i < numofpassports()) {
		if (id == passportarr[i].id) {
			printf("Enter a new renewal status - yes or no\n");
			scanf("%s", &passportarr[i].needsrenewal);
			rewritepassports(passportarr);
			return;
		}
		i++;
	}
	printf("ID is not in the database - person not found\n");
}
///END OF PASSPORT SETS
///END OF SETS

///START OF INTERFACE MANAGEMENT
//manages the interface for a regular user
void userinterface(database *dbarr, user *userarr, passport *passportarr, int id) {
	printf("\nAs a user you may view the following - \n");
	printf("Your name, dath of birth, address, tel number, cell number, parents names, place of birth, religion and whether you are eligible of a certificate of good conduct\n");
	printf("You may edit the following - \n");
	printf("Address, religion, tel number, cell number and account password\n");
	printf("You may also view the details of your passport\n");
	printf("1 - view personal details, 2 - edit personal details, 3 - view passport details, 4 - view user details, 5 - change your password, 0 - go back\n");
	int c1 = 50;
	int c2 = 50;
	while (c1 != 0) {
		scanf("%d", &c1);
		switch (c1) {
		case 1:
			printf("Enter the relevant number for your choice - (VIEW PERSONAL DETAILS)\n");
			printf("1 - name, 2 - date of birth, 3 - address, 4 - tel number, 5 - cell number, 6 - parents names, 7 - place of birth, 8 - religion, 9 - eligibility for cetificate of good will, 0 - go back\n");
			c2 = 50;
			while (c2 != 0) {
				scanf("%d", &c2);
				switch (c2) {
				case 1:
					getname(dbarr, id);
					break;
				case 2:
					getdateofbirth(dbarr, id);
					break;
				case 3:
					getaddress(dbarr, id);
					break;
				case 4:
					gettelnumber(dbarr, id);
					break;
				case 5:
					getcellnumber(dbarr, id);
					break;
				case 6:
					getparentsnames(dbarr, id);
					break;
				case 7:
					getplaceofbirth(dbarr, id);
					break;
				case 8:
					getreligion(dbarr, id);
					break;
				case 9:
					goodconductcert(dbarr, id);
					break;
				case 0:
					break;
				default:
					printf("Invalid input \n");
					continue;
				}
				if (c2 != 0)
					printf("Enter another choice or 0 to go back\n");
			}
			break;
		case 2:
			printf("Enter the relevant number for your choice - (VIEW PERSONAL DETAILS)\n");
			printf("1 - Address, 2 - Religion, 3 - Telephone number, 4 - Cellular number\n");
			c2 = 50;
			while (c2 != 0) {
				scanf("%d", &c2);
				switch (c2) {
				case 1:
					setaddress(dbarr, id);
					break;
				case 2:
					setreligion(dbarr, id);
					break;
				case 3:
					settelnumber(dbarr, id);
					break;
				case 4:
					setcellnumber(dbarr, id);
					break;
				}
				if (c2 != 0)
					printf("Enter another choice or 0 to go back\n");
			}
			break;
		case 3:
			getpassportname(passportarr, id);
			getpassportdates(passportarr, id);
			break;
		case 4:
			getuserdetails(userarr, id);
		case 5:
			setuserpassword(userarr, id);
			break;
		case 0:
			return;
		default:
			break;
		}
		if (c1 != 0)
			printf("\n1 - view personal details, 2 - edit personal details, 3 - view passport details, 4 - change your password, 0 - go back\n");
	}
}

//manages the interface for a manager (someone who works at the ministry of interior)
void managerinterface(database *dbarr, user *userarr, passport *passportarr) {
	printf("\nAs a manager you may view the following - \n");
	printf("Everyone's name, dath of birth, address, tel number, cell number, parents names, place of birth, religion and whether they are eligible of a certificate of good conduct\n");
	printf("You may edit the following - \n");
	printf("Everyone's First name, last name, address, religion, tel number, cell number and change their certificate status incase the police has granted permission\n");
	printf("You may also view the details of everyone's passports and all the ID numbers\n");
	printf("1 - view personal details, 2 - edit personal details, 3 - view passport details, 4 - edit passport details, 5 - view all ID numbers, 0 - go back \n");
	int c1 = 50;
	int c2 = 50;
	int id;
	while (c1 != 0) {
		scanf("%d", &c1);
		switch (c1) {
		case 1:
			system("cls");
			printf("Enter the relevant number for your choice - (VIEW PERSONAL DETAILS)\n");
			printf("1 - name, 2 - date of birth, 3 - address, 4 - tel number, 5 - cell number, 6 - parents names, 7 - place of birth, 8 - religion, 9 - eligibility for cetificate of good will, 0 - go back\n");
			c2 = 50;
			while (c2 != 0) {
				scanf("%d", &c2);
				switch (c2) {
				case 1:
					id = validateid();
					getname(dbarr, id);
					break;
				case 2:
					id = validateid();
					getdateofbirth(dbarr, id);
					break;
				case 3:
					id = validateid();
					getaddress(dbarr, id);
					break;
				case 4:
					id = validateid();
					gettelnumber(dbarr, id);
					break;
				case 5:
					id = validateid();
					getcellnumber(dbarr, id);
					break;
				case 6:
					id = validateid();
					getparentsnames(dbarr, id);
					break;
				case 7:
					id = validateid();
					getplaceofbirth(dbarr, id);
					break;
				case 8:
					id = validateid();
					getreligion(dbarr, id);
					break;
				case 9:
					id = validateid();
					goodconductcert(dbarr, id);
					break;
				case 0:
					break;
				default:
					printf("Invalid input \n");
					continue;
				}
				if (c2 != 0)
					printf("Enter another choice or 0 to go back\n");
			}
			break;
		case 2:
			printf("Enter the relevant number for your choice - (EDIT PERSONAL DETAILS)\n");
			printf("1 - first name, 2 - last name, 3 - date of birth, 4 - address, 5 - gender, 6 - telephone number, 7 - cellular number, 8 - father's name, 9 - mother's name, 10 - grandfather's name, 11 - religion, 12 - good conduct certification level, 0 - go back \n");
			c2 = 50;
			while (c2 != 0) {
				scanf("%d", &c2);
				switch (c2) {
				case 1:
					id = validateid();
					setfirstname(dbarr, id);
					break;
				case 2:
					id = validateid();
					setlastname(dbarr, id);
					break;
				case 3:
					id = validateid();
					setdateofbirth(dbarr, id);
					break;
				case 4:
					id = validateid();
					setaddress(dbarr, id);
					break;
				case 5:
					id = validateid();
					setgender(dbarr, id);
					break;
				case 6:
					id = validateid();
					settelnumber(dbarr, id);
					break;
				case 7:
					id = validateid();
					setcellnumber(dbarr, id);
					break;
				case 8:
					id = validateid();
					setfathername(dbarr, id);
					break;
				case 9:
					id = validateid();
					setmothername(dbarr, id);
					break;
				case 10:
					id = validateid();
					setgrandfathername(dbarr, id);
					break;
				case 11:
					id = validateid();
					setreligion(dbarr, id);
					break;
				case 12:
					id = validateid();
					setgoodconductcert(dbarr, id);
					break;
				case 0:
					break;
				default:
					printf("Invalid input\n");
				}
				if (c2 != 0)
					printf("Enter another choice or 0 to go back\n");
			}
			break;
		case 3:
			id = validateid();
			getpassportname(passportarr, id);
			getpassportdates(passportarr, id);
			break;
		case 4:
			system("cls");
			printf("Enter the relevant number for your choice - (EDIT PASSPORT DETAILS)\n");
			printf("1 - first name, 2 - last name, 3 - validity, 4 - renewal status, 0 - go back \n");
			c2 = 50;
			while (c2 != 0) {
				scanf("%d", &c2);
				switch (c2) {
				case 1:
					id = validateid();
					setpassportfirstname(passportarr, id);
					break;
				case 2:
					id = validateid();
					setpassportlastname(passportarr, id);
					break;
				case 3:
					id = validateid();
					setpassportvalidity(passportarr, id);
					break;
				case 4:
					id = validateid();
					setpassportrenewal(passportarr, id);
					break;
				case 0:
					break;
				default:
					printf("Invalid input\n");
				}
				if (c2 != 0)
					printf("Enter another choice or 0 to go back\n");
			}
			break;
		case 5:
			printdbid(dbarr);
			break;
		case 0:
			return;
		default:
			printf("Invalid input\n");
			continue;
		}
		if (c1 != 0)
			printf("\n1 - view personal details, 2 - edit personal details, 3 - view passport details, 4 - edit passport details, 0 - go back \n");
	}
}

//manages the interface for an administrator (someone who has access to everything, including the program's code)
void admininterface(database *dbarr, user *userarr, passport *passportarr) {
	printf("\nAs an administrator you may view and edit everything - (Personal details, passport details, user details)\n");
	printf("Enter the number for your choice \n");
	printf("1 - view personal details, 2 - edit personal details, 3 - view user details, 4 - edit user details, 5 - view passport details, 6 - edit passport passport details, 7 - view all ID numbers, 0 - go back\n");
	int c1 = 50;
	int c2 = 50;
	int id;
	char lastname[20];
	while (c1 != 0) {
		scanf("%d", &c1);
		switch (c1) {
		case 1:
			system("cls");
			printf("Enter the relevant number for your choice - (VIEW PERSONAL DETAILS) \n");
			printf("1 - name, 2 - date of birth, 3 - address, 4 - tel number, 5 - cell number, 6 - parents names, 7 - place of birth, 8 - religion, 9 - eligibility for cetificate of good will, 10 - ID number 0 - back to previous screen\n");
			c2 = 50;
			while (c2 != 0) {
				scanf("%d", &c2);
				switch (c2) {
				case 1:
					id = validateid();
					getname(dbarr, id);
					break;
				case 2:
					id = validateid();
					getdateofbirth(dbarr, id);
					break;
				case 3:
					id = validateid();
					getaddress(dbarr, id);
					break;
				case 4:
					id = validateid();
					gettelnumber(dbarr, id);
					break;
				case 5:
					id = validateid();
					getcellnumber(dbarr, id);
					break;
				case 6:
					id = validateid();
					getparentsnames(dbarr, id);
					break;
				case 7:
					id = validateid();
					getplaceofbirth(dbarr, id);
					break;
				case 8:
					id = validateid();
					getreligion(dbarr, id);
					break;
				case 9:
					id = validateid();
					goodconductcert(dbarr, id);
					break;
				case 10:
					getid(dbarr);
					break;
				case 0:
					break;
				default:
					printf("Invalid input\n");
				}
				if (c2 != 0)
					printf("Enter another choice or 0 to go back\n");
			}
			break;
		case 2:
			system("cls");
			printf("Enter the relevant number for your choice - (EDIT PERSONAL DETAILS) \n");
			printf("1 - first name, 2 - last name, 3 - date of birth, 4 - address, 5 - gender, 6 - telephone number, 7 - cellular number, 8 - father's name, 9 - mother's name, 10 - grandfather's name, 11 - religion, 12 - good conduct certification level, 0 - back to previous screen \n");
			c2 = 50;
			while (c2 != 0) {
				scanf("%d", &c2);
				switch (c2) {
				case 1:
					id = validateid();
					setfirstname(dbarr, id);
					break;
				case 2:
					id = validateid();
					setlastname(dbarr, id);
					break;
				case 3:
					id = validateid();
					setdateofbirth(dbarr, id);
					break;
				case 4:
					id = validateid();
					setaddress(dbarr, id);
					break;
				case 5:
					id = validateid();
					setgender(dbarr, id);
					break;
				case 6:
					id = validateid();
					settelnumber(dbarr, id);
					break;
				case 7:
					id = validateid();
					setcellnumber(dbarr, id);
					break;
				case 8:
					id = validateid();
					setfathername(dbarr, id);
					break;
				case 9:
					id = validateid();
					setmothername(dbarr, id);
					break;
				case 10:
					id = validateid();
					setgrandfathername(dbarr, id);
					break;
				case 11:
					id = validateid();
					setreligion(dbarr, id);
					break;
				case 12:
					id = validateid();
					setgoodconductcert(dbarr, id);
					break;
				case 0:
					break;
				default:
					printf("Invalid input\n");
				}
				if (c2 != 0)
					printf("Enter another choice or 0 to go back\n");
			}
			break;
		case 3:
			system("cls");
			id = validateid();
			getuserdetails(userarr, id);
			break;
		case 4:
			system("cls");
			printf("Enter the relevant number for your choice - (EDIT USER DETAILS)\n");
			printf("1 - username, 2 - password, 3 - permission level, 0 - back to previous screen \n");
			c2 = 50;
			while (c2 != 0) {
				scanf("%d", &c2);
				switch (c2) {
				case 1:
					id = validateid();
					setusername(userarr, id);
					break;
				case 2:
					id = validateid();
					setuserpassword(userarr, id);
					break;
				case 3:
					id = validateid();
					setuserpermission(userarr, id);
					break;
				case 0:
					break;
				default:
					printf("Invalid input\n");
				}
				if (c2 != 0)
					printf("Enter another choice or 0 to go back\n");
			}
			break;
		case 5:
			system("cls");
			id = validateid();
			getpassportname(passportarr, id);
			getpassportdates(passportarr, id);
			break;
		case 6:
			system("cls");
			printf("Enter the relevant number for your choice - (EDIT PASSPORT DETAILS)\n");
			printf("1 - first name, 2 - last name, 3 - validity, 4 - renewal status, 0 - back to previous screen \n");
			c2 = 50;
			while (c2 != 0) {
				scanf("%d", &c2);
				switch (c2) {
				case 1:
					id = validateid();
					setpassportfirstname(passportarr, id);
					break;
				case 2:
					id = validateid();
					setpassportlastname(passportarr, id);
					break;
				case 3:
					id = validateid();
					setpassportvalidity(passportarr, id);
					break;
				case 4:
					id = validateid();
					setpassportrenewal(passportarr, id);
					break;
				case 0:
					break;
				default:
					printf("Invalid input\n");
				}
				if (c2 != 0)
					printf("Enter another choice or 0 to go back\n");
			}
			break;
		case 7:
			printdbid(dbarr);
			break;
		case 0:
			return;
		default:
			printf("Invalid input\n");
			continue;
		}
		printf("\n1 - view personal details, 2 - edit personal details, 3 - view user details, 4 - edit user details, 5 - view passport details, 6 - edit passport passport details, 0 - go back\n");
	}
}
///END OF INTERFACE MANAGEMENT

MU_TEST_SUITE(test_suite_inits) {
	MU_SUITE_CONFIGURE(NULL, NULL);
	MU_RUN_TEST(test_dbinit);
	MU_RUN_TEST(test_userinit);
	MU_RUN_TEST(test_passportinit);
	MU_REPORT_SUITE();
}

MU_TEST_SUITE(test_suite_counters) {
	MU_SUITE_CONFIGURE(NULL, NULL);
	MU_RUN_TEST(test_numofpersons);
	MU_RUN_TEST(test_numofusers);
	MU_RUN_TEST(test_numofpassports);
	MU_REPORT_SUITE();
}

MU_TEST_SUITE(test_suite_validations) {
	MU_SUITE_CONFIGURE(NULL, NULL);
	MU_RUN_TEST(test_login);
	MU_RUN_TEST(test_validateid);
	MU_REPORT_SUITE();
}

//displays in first screen upon entering the program, allows input of 1 to login or 0 (and else) to exit. 
void entrance(database *dbarr, user *userarr, passport *passportarr) {
	int entry = 50;
	int id;
	printf("Welcome to Or's ultimate and supreme govermental database management program, inspired by the gov.il system.\n");
	printf("You can only browse the system with a personal user that has been created for you in our system.\n");
	int c1 = 50;
	while (c1 != 0) {
		printf("To LOGIN enter 1, For unit tests enter 2, To EXIT enter 0\n");
		scanf("%d", &c1);
		switch (c1) {
		case 1:
			printf("Enter your login details - \n");
			id = validateid();
			entry = login(userarr, id);
			break;
		case 2:
			MU_RUN_SUITE(test_suite_inits);
			MU_RUN_SUITE(test_suite_counters);
			MU_RUN_SUITE(test_suite_validations);
			break;
		case 0:
			printf("Exiting...\n");
			exit(1);
		default:
			printf("Invalid input\n");
			continue;
		}
		if (entry == -1) {
			printf("User credentials are invalid\n");
			continue;
		}
		if (entry == 0) 
			userinterface(dbarr, userarr, passportarr, id);
		if (entry == 1) 
			managerinterface(dbarr, userarr, passportarr);
		if (entry == 2) {
			admininterface(dbarr, userarr, passportarr);
		}
	}
}

int main() {
	database *dbarr = dbinit();
	user *userarr = userinit();
	passport *passportarr = passportinit();
	entrance(dbarr, userarr, passportarr);
	freearrs(dbarr, userarr, passportarr);
}


