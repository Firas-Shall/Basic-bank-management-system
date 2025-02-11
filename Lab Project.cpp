//by Mohamad Firas and Malak Shall

#include <iostream>
#include <cstdlib>//for random generator
#include <ctime>
#include <iomanip>
#include <fstream>//for saving and loading data
using namespace std;

void sortaccounts(int arr[], float arr2[], int arr3[], int Size) {
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size-1; j++) { //size-1 because j+1 can't be applied to the last array element
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				float temp2 = arr2[j];
				int temp3 = arr3[j];
				arr[j] = arr[j + 1];
				arr2[j] = arr2[j + 1];//any change in the fist array will be applied in second and third
				arr3[j] = arr3[j + 1];
				arr[j + 1] = temp;
				arr2[j + 1] = temp2;
				arr3[j + 1] = temp3;//to keep arrays parallel
			}
		}
	}

}


void addaccount(int arr[], float arr2[], int arr3[], int Size) {
	int accountnumber;
	int PIN;
	int position=-1;
	srand(time(0));
	accountnumber = 45658 + rand() % 567768;
	cout << "Your account number is " << accountnumber << endl;
	for (int i = 0; i < Size; i++) {
		if (arr[i] == 0) { //to search for empty element
			arr[i] = accountnumber;
			position = i;
			
			break;
		}
	}
	
	cout << "Enter a PIN: \n";
	cin >> PIN;
	while (PIN < 1000 || PIN>9999) {
		cout << "PIN must be 4 digits\n";
		cin >> PIN;
	}
	arr3[position] = PIN;
	arr2[position] = 0.0;
	sortaccounts(arr, arr2, arr3, Size);//only arr1 is sorted because it's the only one we use binary search in
}


int binarysearch(int arr[], int Size, int target) { //checks if middle element is the target
	int left = 0, right = Size - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] == target) {
			return mid;
		}
		if (arr[mid] < target) { //the array we search in becomes to the right of original mid
			left = mid + 1;
		}
		else {                   //the array we search in becomes to the left of original mid
			right = mid - 1; 
		}
	}
	return -1;
}

void editPin(int arr1[], int arr3[], int Size) {
	int target;
	int PIN;
	int index;
	cout << "Please enter your account number: \n";
	cin >> target;

	while (target < 45658 || target>613425) {
		cout << "Invalid account number! Please check and enter again: \n";
		cin >> target;
	}
	index = binarysearch(arr1, Size, target); //searches for index of account number entered
	if (index == -1) { //binarysearch returns -1 if target not found
		cout << "No account found!\n";
	}
	else {
		cout << "Enter your PIN: \n";
		cin >> PIN;
		while (PIN != arr3[index]) {
			cout << "Wrong PIN! Enter again: \n";
			cin >> PIN;
		}
		cout << "Enter your new pin: \n";
		cin >> arr3[index];
	}
}

void deposit(int arr1[], float arr2[], int arr3[], int Size) {
	int target;
	float money;
	int PIN;
	int index;
	cout << "Please enter your account number: \n";
	cin >> target;

	while (target < 45658 || target>613425) {
		cout << "Invalid account number! Please check and enter again: \n";
		cin >> target;
	}
	index = binarysearch(arr1, Size, target); //searches for index of account number entered
	if (index == -1) { //binarysearch returns -1 if target not found
		cout << "No account found!\n";
	}
	else {
		cout << "Enter your PIN: \n";
		cin >> PIN;
		while (PIN != arr3[index]) {
			cout << "Wrong PIN! Enter again: \n";
			cin >> PIN;
		}
		cout << "Enter the amount you want to deposit: \n";
		cin >> money;
		arr2[index] += money;//all info stored with same index to keep arrays parallel
	}

}

void withdraw(int arr1[], float arr2[], int arr3[], int Size) {
	int target;
	float money;
	int PIN;
	int index;
	cout << "Please enter your account number: \n";
	cin >> target;

	while (target < 45658 || target>613425) {
		cout << "Invalid account number! Please check and enter again: \n";
		cin >> target;
	}
	index = binarysearch(arr1, Size, target);
	if (index == -1) {
		cout << "No account found!\n";
	}
	else {
		cout << "Enter your PIN: \n";
		cin >> PIN;
		while (PIN != arr3[index]) {
			cout << "Wrong PIN! Enter again: \n";
			cin >> PIN;
		}
		cout << "Enter the amount you want to withdraw: \n";
		cin >> money;
		if (money < arr2[index]) {
			arr2[index] -= money;
		}
		else {
			cout << "Can't withdraw!\n";
		}
	}

}

void transfer(int arr[], float arr2[], int arr3[], int Size) {
	int target;
	float money;
	int PIN;
	int target2;
	int index, index2;
	cout << "Please enter your account number: \n";
	cin >> target;

	while (target < 45658 || target>613425) {
		cout << "Invalid account number! Please check and enter again: \n";
		cin >> target;
	}
	index = binarysearch(arr, Size, target);
	if (index == -1) {
		cout << "No account found!\n";
	}
	else {
		cout << "Enter your PIN: \n";
		cin >> PIN;
		while (PIN != arr3[index]) {
			cout << "Wrong PIN! Enter again: \n";
			cin >> PIN;
		}
		cout << "Enter the amount you want to transfer: \n";
		cin >> money;
		if (money < arr2[index]) {
			arr2[index] -= money;
			cout << "Please enter the account number you want to transfer the money to: \n";
			cin >> target2;

			while (target2 < 45658 || target2>613425) {
				cout << "Invalid account number! Please check and enter again: \n";
				cin >> target2;
			}
			index2 = binarysearch(arr, Size, target2);
			if (index2 == -1) {
				cout << "No account found!\n";
			}
			else {
				arr2[index2] += money;
			}
		}
		else {
			cout << "No enough funds!\n";
		}

	}

	
}

void viewAcc(int arr[], float arr2[], int Size) {
	int target;
	int index;
	cout << "Please enter your account number: \n";
	cin >> target;

	while (target < 45658 || target>613425) {
		cout << "Invalid account number! Please check and enter again: \n";
		cin >> target;
	}
	index = binarysearch(arr, Size, target);
	if (index == -1) {
		cout << "No account found!\n";
	}
	else {
		cout << "account number: " << arr[index] << endl;
		cout << "amount: " << arr2[index] <<"$"<< endl;
	}
}

void viewAllaccounts(int arr[], float arr2[], int Size) {
	cout << "Acc number" << setw(10) << "Amount" << endl;
	for (int i = 0; i < Size; i++) {
		cout << arr[i] << setw(17) << arr2[i] <<"$"<< endl;
	}
}

void viewAllaccounts2(int arr[], float arr2[], int Size) {
	float threshold;
	cout << "Choose a money threshold above which you want to display accounts: \n";
	cin >> threshold;
	while (threshold < 1.0) {
		cout << "Amount should be above one dollar!\n";
		cin >> threshold;
	}
	cout << "Acc number" << setw(10) << "Amount" << endl;
	for (int i = 0; i < Size; i++) {
		if (arr2[i] > threshold) {
			cout << arr[i] << setw(17) << arr2[i] <<"$"<< endl;
		}
	}
}

float compoundInterest(float money, float rate, int years) {
	if (years == 0) {
		return money;
	}
	else {
		return compoundInterest(money * (1 + rate), rate, years - 1);
	}
}

void caculateinterest(int arr1[], float arr2[], int arr3[], int Size, float rate) {
	int target;
	float money;
	int PIN;
	int index;
	int years;
	cout << "Our interest rate is 5% anually, please enter your account number for more info: \n";
	cin >> target;

	while (target < 45658 || target>613425) {
		cout << "Invalid account number! Please check and enter again: \n";
		cin >> target;
	}
	index = binarysearch(arr1, Size, target); 
	if (index == -1) { 
		cout << "No account found!\n";
	}
	else {
		cout << "Enter your PIN: \n";
		cin >> PIN;
		while (PIN != arr3[index]) {
			cout << "Wrong PIN! Enter again: \n";
			cin >> PIN;
		}
	do {
		cout << "Enter number of years: \n";
		cin >> years;
	} while (years < 1);
	cout << "Your amount after " << years << " years becomes " << compoundInterest(arr2[index], rate, years)<<"$"<< endl;
	}
	
}

void loadData(int arr1[], float arr2[], int arr3[], string &filename, int Size) {
	ifstream infile(filename); //to open file
	if (infile.is_open()) {  //checks if the file is open
		for (int i = 0; i < Size; i++) {
			infile >> arr1[i];//loads data to each array's element
			infile >> arr2[i];
			infile >> arr3[i];
		}
		infile.close();
	}
	else {
		cout << "Unable to open file for loading.\n";
	}
}

void saveData(int arr1[], float arr2[], int arr3[], string& filename, int Size) {
	ofstream outfile(filename); //opens file
	if (outfile.is_open()) {
		for (int i = 0; i < Size; i++) {
			outfile << arr1[i] << '\n'; //write data in file
			outfile << arr2[i] << '\n';
			outfile << arr3[i] << '\n';
		}
		outfile.close();
	}
	else {
		cout << "Unable to open file for saving.\n";
	}
}

int main() {

	const int size = 200;
	const float rate = 0.06;
	int AccNum[200] = { 0 };
	float AccMoney[200] = { 0.0 };
	int AccPin[200] = { 0 };
	int choice, again;
	string filename = "bank.txt";

	loadData(AccNum, AccMoney, AccPin, filename, size);

	cout << setw(75) << "*****Welcome to CS BANK*****\n";
	do {
		cout << "Choose number for desired operation: \n";
		cout << "1-Add a new account.\n2-Edit Pin\n3-Deposit.\n4-Withdraw.\n5-Transfer.\n6-Calculate Compound Interest\n7-View Account.\n8-View all accounts.\n";
		cout << "9-View Accounts above a threshold.\n";
		cin >> choice;
		while (choice < 1 || choice>9) {
			cout << "Invalid Number! Try again: \n";
			cin >> choice;
		
		}
		switch (choice) {
		case 1:
			addaccount(AccNum, AccMoney, AccPin, size);
			break;
		case 2:
			editPin(AccNum, AccPin, size);
			break;
		case 3:
			deposit(AccNum, AccMoney, AccPin, size);
			break;
		case 4:
			withdraw(AccNum, AccMoney, AccPin, size);
			break;
		case 5:
			transfer(AccNum, AccMoney, AccPin, size);
			break;

		case 6:
			caculateinterest(AccNum, AccMoney, AccPin, size, rate);
			break;
		case 7:
			viewAcc(AccNum, AccMoney, size);
			break;
		case 8:
			viewAllaccounts(AccNum, AccMoney, size);
			break;
		case 9:
			viewAllaccounts2(AccNum, AccMoney, size);
			break;
		default:
			cout << "Program shouldn't reach this point.";
		}

		cout << "Any more steps? 1-Yes/2-Exit\n";
		cin >> again;
	} while (again == 1);
	
	saveData(AccNum, AccMoney, AccPin, filename, size);

	return 0;
}