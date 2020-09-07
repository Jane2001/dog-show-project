#include<iostream>
#include<string>
#include<ctime>
#include<fstream>
#include<vector>
#include<conio.h>
#include<iomanip>
#include<clocale>
using namespace std;
const int n = 30;
const int b = 25;
string arrayOfNames[n], arrayOfBreeds[b];
vector<int>place;
class Dog {
	string breed, name;
	int number, age;
	int placeInFair;
	static int sameBreedAmount[b];
	static int counter;
public:
	Dog *next;
	Dog(int anumber, Dog *nxt) {
		age = rand() % 15 + 1;
		number = anumber;
		breed = arrayOfBreeds[rand()%b];
		name = arrayOfNames[rand()%n];
		compareBreeds(breed);
		placeInFair = randomPlaceInFair();
   	    next = nxt;
		counter++;
	}
	Dog( string n, string b, int a, Dog *nxt) {
		counter++;
		number = counter;
		name = n;
		breed = b;
		age = a;
		compareBreeds(breed);
		placeInFair = counter;
		next = nxt;
	}
	Dog(string n, int nb, int a, Dog *nxt) {
		counter++;
		number = counter;
		name = n;
		for (int i = 0; i < b; i++) {
			if (nb - 1 == i) {
				breed = arrayOfBreeds[i];
			}
		}
		age = a;
		compareBreeds(breed);
		placeInFair = counter;
		next = nxt;
	}
	Dog(){}
	~Dog() {
		counter--;
	}
	void setNumber(int num) {
		number = num;
	}
	void setPlaceInFair(int place) {
		placeInFair = place;
	}
	int getAge() {
		return age;
	}
	int getNumber() {
		return number;
	}
	string getBreed() {
		return breed;
	}
	string getName() {
		return name;
	}
	int getPlaceInFair() {
		return placeInFair;
	}
	static void minusSameBreedAmount(string breed);
	static void printSameBreedAmount();
	static void inputBreedFile();
	static void inputNameFile();
	static void vectorFilling(int a);
	static int getCounter();
private:
	static void compareBreeds(string abreed);
	int randomPlaceInFair() {
		int index, value;
		index = rand() % place.size();
		value = place[index];
		place.erase(place.begin() + index);
		return value;
	}
};
int Dog::sameBreedAmount[b] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int Dog::counter = 0;
int Dog::getCounter() {
	return counter;
}
void Dog::minusSameBreedAmount(string breed) {
	for (int i = 0; i < b; i++) {
		if (breed == arrayOfBreeds[i] && sameBreedAmount[i] > 1) {
			sameBreedAmount[i]--;
		}
	}
}
void Dog::vectorFilling(int a) {
	for (int i = 0; i < a; i++) {
		place.push_back(i + 1);
	}
}
void Dog::inputBreedFile(){
	fstream fbreeds;
	fbreeds.open("Breeds.txt", ios::in);
	for (int i = 0; i < b; i++) {
		fbreeds >> arrayOfBreeds[i];
	}
	fbreeds.close();
}
void Dog::inputNameFile(){
	fstream fnames;
	fnames.open("Name.txt", ios::in);
	for (int i = 0; i < n; i++) {
		fnames >> arrayOfNames[i];
	}
	fnames.close();
}
void Dog::printSameBreedAmount() {
	bool check = false;
	cout << endl << "Amount of identical breeds: " ;
	for (int i = 0; i < b; i++) {
		if (sameBreedAmount[i] > 1) {
			check = true;
			cout << endl << arrayOfBreeds[i] << " " << sameBreedAmount[i];
		}
	}
	if (check == false) {
		cout << "-" << endl;
	}
}
void Dog::compareBreeds(string abreed) {
	for (int i = 0; i < b; i++) {
		if (abreed == arrayOfBreeds[i]) {
			sameBreedAmount[i]++;
		}
	}
}
class list {
	Dog *head, *current;
public:
	list() {
		head = 0;
	}
	void add(int n) {
		Dog *p = new Dog(n, 0);
		if (head == 0) {
			head = p;
		}
		else {
			current = head;
			while (current->next != 0) {
				current = current->next;
			}
			current->next = p;
		}
	}
	void add(string name, string breed, int age) {
		Dog *p = new Dog(name, breed, age, 0);

		if (head == 0) {
			head = p;
		}
		else {
			current = head;
			while (current->next != 0) {
				current = current->next;
			}
			current->next = p;
		}
	}
	void add(string name, int numBreed, int age) {
		Dog *p = new Dog(name, numBreed, age, 0);

		if (head == 0) {
			head = p;
		}
		else {
			current = head;
			while (current->next != 0) {
				current = current->next;
			}
			current->next = p;
		}
	}
	bool printList(bool check, int userN) {
		if (emptyList()) {
			if (check) {
				current = head;
				table();
				while (current) {
					outputAll();
					current = current->next;
				}
			}
			else {
				current = head;
				while (current) {
					if (userN == current->getNumber()) {
						table();
						outputAll();
						return true;
						break;
					}
					else {
						current = current->next;
					}
				}
				return false;
			}
		}
		else {}
	}
	void printListFromAnyElement(int numOfel) {
		bool check;
		if (emptyList()) {
			check = false;
			table();
			for (int i = 0; i < 2; i++) {
				current = head;
				if (numOfel < current->getNumber()) {
					cout << "No such element!" << endl;
					break;
				}
				while (current) {
					if (i == 0 && numOfel <= current->getNumber()) {
						
						outputAll();
						check = true;
					}
					if (i == 1 && numOfel > current->getNumber() && check == true) {
						outputAll();
					}
					current = current->next;
				}
				if (check == false) {
					cout << "No such element!" << endl;
					break;
				}
			}
			
		}
	}
	bool basedOnNameOutput(int numname) {
		bool check;
		if (emptyList()) {
			check = false;
			current = head;
			table();
			while (current) {
				if (arrayOfNames[numname-1] == current->getName()) {	
					outputAll();
					check = true;
				}
				if (check == false && current->next == 0) {
					return true;
				}
				current = current->next;
			}
			return false;
		}
		
	}
	bool basedOnBreedOutput(int numbreed) {
		bool check;
		if (emptyList()) {
			check = false;
			current = head;
			table();
			while (current) {
				if (arrayOfBreeds[numbreed-1] == current->getBreed()) {
					outputAll();
					check = true;
				}
				if (check == false && current->next == 0) {
					return true;
				}
				current = current->next;
			}
			return false;
		}
	}
	bool basedOnAgeOutput(int age) {
		bool check;
		if (emptyList()) {
			check = false;
			current = head;
			table();
			while (current) {
				if (age == current->getAge()) {
					outputAll();
					check = true;
				}
				if (check == false && current->next == 0) {
					return true;
				}
				current = current->next;
			}
			return false;
		}
	}
	bool basedOnPlaceOutput(int place) {
		bool check;
		if (emptyList()) {
			check = false;
			current = head;
			while (current) {
				if (place == current->getPlaceInFair()) {
					table();
					outputAll();
					check = true;
				}
				if (check == false && current->next == 0) {
					return true;
				}
				current = current->next;
			}
			return false;
		}
	}
	void topPlaces() {
		if (emptyList()) {
			table();
			current = head;
			while (current){
				if (current->getPlaceInFair() < 4) {
					outputAll();
				}
				current = current->next;
			}
		}
	}
	void deleteElement(int numOfelement) {
		current = head;
		while (current) {
			if (numOfelement == current->getNumber()) {
				Dog::minusSameBreedAmount(current->getBreed());
			}
			current = current->next;
		}
		int n;
		current = head;
		for (int i = 1; i < numOfelement && current != NULL; i++) {
			current = current->next;
		}
		if (current != NULL && numOfelement > 0) {
			if (numOfelement == head->getNumber()) {
				head = head->next;
				delete current;
			}
			else {
				Dog *p = head;
				while (p->next != current) {
					p = p->next;
				}
				p->next = current->next;
				delete current;
			}
			current = head;
			while (current) {
				if (current->getNumber() > numOfelement) {
					n = current->getNumber();
					current->setNumber(n - 1);
				}
				current = current->next;
			}	
		}
		else {
			cout << "No such element!" << endl;
		}
	}
	void changePlaceInFair(int numOfel, int newPlace) {
		int temp, temp2;
		current = head;
		while (current) {
			if (numOfel == current->getNumber()) {
				temp = current->getPlaceInFair();
				current->setPlaceInFair(newPlace);
			}
			current = current->next;
		}
		current = head;
		while (current) {
			if (newPlace == current->getPlaceInFair() && numOfel != current->getNumber()) {
				current->setPlaceInFair(temp);

			}
			current = current->next;
		}
	}
	void listNameSort(int am) {
		table();
		for (int i = 65; i <= 90; i++) {
			current = head;
			for (int j = 0; j < am; j++) {
				for (int k = 0; k < current->getName().length(); k++) {
					if (current->getName()[k] == (char)(i)) {
						outputAll();
					}
				}
				current = current->next;
			}
			
		}
	}
	~list() {
		while (head) {
			current = head;
			head = head->next;
			delete current;
		}
	}
private:
	void outputAll() {
		cout << current->getNumber() << setw(15);
		cout << current->getPlaceInFair() << setw(10) << '\t';
		cout << current->getName() << "\t\t";
		cout << current->getAge() << '\t';
		cout << current->getBreed() << endl;
	}
	bool emptyList() {
		if (head != 0) {
			return true;
		}
		else {
			cout << "List is empty!" << endl;
			return false;
		}
	}
	void table() {
		cout << "No.\t" << "Place in fair\t\t" << "Name\t\t" << "Age\t " << "Breed\t" << endl;
		cout << "===================================================================" << endl;
	}
};
void main() {
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	Dog::inputBreedFile();
	Dog::inputNameFile();
	bool check1, check2;
	int amount, userInt, age, userPlace, user, am;
	char userChoice;
	string userStr, name, breed;
	do {
		cout << "Please, input amount of elements in list (not more than 20): ";
		cin >> amount;
		if (amount > 20 || amount <= 0) {
			system("cls");
			cout << "Wrong amount! Try again..." << endl;
		}
	} while (amount > 20 || amount <=0);
	Dog::vectorFilling(amount);
	list dogList;
	for (int i = 0; i < amount; i++) {
		dogList.add(i + 1);
	}
	 do{
		 system("cls");
		 cout << "1-list output;" << endl << "2-list output starting from any element;" << endl << "3-output certain element;" << endl << "4-based output;" << endl << "5-top places;" << endl;
		 cout << "6-delete element;" << endl << "7-add element;" << endl << "8-alphabetical output;" << endl << "9-change place in fair;" << endl <<"0-information about author;" << endl << "esc-exit" << endl;
		 cout << "Please, input your choice: ";
		 user = _getch();
		 cout << endl;
		 switch (user) {
		 case '1':
			 system("cls");
			 dogList.printList(true, 0);
			 Dog::printSameBreedAmount();
			 cout << endl;
			 cout << "Amount of instances: ";
			 cout << Dog::getCounter() << endl;
			 break;
		 case '2':
			 system("cls");
			 cout << "Input number of element that will start the list: ";
			 cin >> userInt;
			 dogList.printListFromAnyElement(userInt);
			 break;
		 case '3':
			 system("cls");
			 cout << "Input number of element that you want to output: ";
			 cin >> userInt;
			 if (dogList.printList(false, userInt)) {}
			 else {
				 cout << "No such element!" << endl;
			 }
			 break;
		 case '4': 
			 do{
				 system("cls");
				 cout << "Please, input on what output will based:" << endl << "1-name;  2-breed;  3-age;  4-place in fair;" << endl;
				 cin >> userChoice;

				 switch (userChoice) {
				 case '1':
					 system("cls");
					 for (int i = 0; i < n; i++) {
						 cout << i + 1 << '.' << " " << arrayOfNames[i] << endl;
					 }
					 cout << endl << "Input number of name: ";
					 cin >> userInt;
					 if (dogList.basedOnNameOutput(userInt)) {
						 cout << "No such name!" << endl;
					 }
					 break;
				 case '2':
					 system("cls");
					 for (int i = 0; i < b; i++) {
						 cout << i + 1 << '.' << " " << arrayOfBreeds[i] << endl;
					 }
					 cout << "Input breed: ";
					 cin >> userInt;
					 if (dogList.basedOnBreedOutput(userInt)) {
						 cout << "No such breed!" << endl;
					 }
					 break;
				 case'3':
					 system("cls");
					 cout << "Input age: ";
					 cin >> userInt;
					 if (dogList.basedOnAgeOutput(userInt)) {
						 cout << "No such age!" << endl;
					 }
					 break;
				 case '4':
					 system("cls");
					 cout << "Input place in fair: ";
					 cin >> userInt;
					 if (dogList.basedOnPlaceOutput(userInt)) {
						 cout << "No such place in fair!" << endl;
					 }
					 break;
				 default:
					 cout << "You input wrong value!" << endl;
					 system("pause");
					 break;
				 }
				 
			 } while (userChoice != '1' && userChoice != '2' && userChoice != '3' && userChoice != '4');
			 break;
		 case '5':
			 system("cls");
			 cout << setw(43) << "Top places:" << endl;
			 dogList.topPlaces();
			 break;
		 case '6':
			 cout << "Input number of element that you want to delete: ";
			 cin >> userInt;
			 dogList.deleteElement(userInt);
			 break;
		 case '7':
			 system("cls");
			 do {
				 cout << "1-input data;" << endl << "2-add automatically;" << endl;
				 cin >> userChoice;
				 if (userChoice != '1' && userChoice != '2') {
					 cout << "You have to input 1 or 2! Try again..." << endl;
				 }
			 } while (userChoice != '1' && userChoice != '2');

			 if (userChoice == '1') {
				 system("cls");
				 cout << "Input name: ";
				 cin >> name; 
				 cout << endl << "Do you want to choose breed or input yourself? 1-choose; 2-input;" << endl;
				 do {
					 cin >> userChoice;
					 if (userChoice != '1' && userChoice != '2') {
						 cout << "You have to input 1 or 2! Try again..." << endl;
					 }
				 } while (userChoice != '1' && userChoice != '2');
				 if (userChoice == '1') {
					 system("cls");
					 for (int i = 0; i < b; i++) {
						 cout << i + 1 << '.' << " " << arrayOfBreeds[i] << endl;
					 }
					 cout << "Input number of breed that you want to add: ";
					 cin >> userInt;
				 }
				 else {
					 cout << "Input breed: ";
					 cin >> breed;
				 }
				 do {
					cout << endl << "Input age: ";
					cin >> age;
					if (age > 20 || age <= 0) {
						cout << "Error... Such age does not exist!" << endl;
					}
				 } while (age > 20 || age <= 0);
				 if (userChoice == '1') {
					 dogList.add(name, userInt, age);
				 }
				 else {
					 dogList.add(name, breed, age);
				 }
			 }
			 else {
				 am = Dog::getCounter();
				 am++;
				 place.push_back(am);
				 dogList.add(am);
			 }
			 break;
		 case '8':
			 dogList.listNameSort(Dog::getCounter());
			 break;
		 case '9':
			 system("cls");
			 check1 = false;
			 check2 = false;
			 cout << "Input number of element that you want to change: ";
			 cin >> userInt;
			 cout << "New place in fair: ";
			 cin >> userPlace;
			 for (int i = 1; i <= Dog::getCounter(); i++) {
				 if (userInt == i) {
					 check1 = true;
				 }
			 }
			 for (int i = 1; i <= Dog::getCounter(); i++) {
				 if (userPlace == i) {
					 check2 = true;
				 }
			 }
			 if (check1 == true && check2 == true) {
				 dogList.changePlaceInFair(userInt, userPlace);
			 }
			 else {
				 cout << "You input wrong number or place in fair!" << endl;
			 }
			 break;
		 case'0':
			 cout << endl << "Хахалева Евгения ОПК-217" << endl;
			 break;
		 case 27:
			 exit(0);
			 break;
		 default:
			 cout << "You input wrong value!" << endl;
		 }
		 system("pause");
	 } while (true);
}