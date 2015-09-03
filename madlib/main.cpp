#include <iostream>
#include <string>
//Drew Barrett
using namespace std;

string leader;
string civilization;
double gandhidistance; //distance to gandis empire
double gandhisize; //size of gandhis borders
double gandhiborders; //calcuated distance to gandhis borders
int armysize; //size of player army
int armyfood; //food of army
int armysurvivors; // amount of surviving army calculated

int sizecheckdouble() {
	if (gandhisize >= gandhidistance) {
		cout << "That decimal number is not smaller. Please enter a smaller decimal number: ";
		cin >> gandhisize;
		sizecheckdouble();//repeat check with new value
	}
	else {
		return 0;
	}
}
int sizecheckint() {
	if (armyfood >= armysize) {
		cout << "That whole number is not smaller. Please enter a smaller whole number: ";
		cin >> armyfood;
		sizecheckint();//repeat check with new value
	}
	else {
		return 0;
	}
}

int main()
{
	cout << "Please enter the following to begin the game" << endl
		<< "Enter your last name: ";
	getline(cin, leader);//allows for value to have spaces if they enter whole name
	cout << "Enter the name of a country/empire: ";
	getline(cin, civilization);
	cout << "Enter a large decimal number: ";
	cin >> gandhidistance;
	cout << "Enter a smaller decimal number: ";
	cin >> gandhisize;
	sizecheckdouble(); //make sure size is smaller
	gandhiborders = gandhidistance - (gandhisize / 2);//distance to gandhi borders
	cout << "Enter a whole number: ";
	cin >> armysize;
	cout << "Enter a smaller whole number: ";
	cin >> armyfood;
	sizecheckint();//same thing as before with different message
	armysurvivors = armyfood/*base survivors*/ + (armysize / armyfood);//amount of people able to scavenge food
	cout << "Welcome to your civilization!\nWill it stand the test of time?\n";
	cout << "You are " << leader << " the Great of " << civilization << endl;
	cout << "You send your army of " << armysize << " out to explore for threats with enough food for "
		<< armyfood << " of them in hopes that the rest will find food to scavenge.\n";
	cout << "After " << gandhidistance / 2/*time to get to borders*/
		<< " days your army finds the borders of a large empire.\nBy this time only "
		<< armysurvivors << " soldiers remain alive in your army.\n";
	cout << "Your army soon finds out that this large empire is run by the famous warmonger Gandhi and in the "
		<< gandhidistance / 2 << " days it took to find him he has created " << int(gandhidistance / 5) << " nuclear weapons!\n";
	cout << "Gandhi has destroyed your civilization\n";
	cout << "Your civilization lasted " << gandhidistance / 2 << " days\n";
	system("PAUSE");
	return 0;
}
/*
Please enter the following to begin the game
Enter your last name: Barrett
Enter the name of a country/empire: Arabia
Enter a large decimal number: 2000.789
Enter a smaller decimal number: 3000
That decimal number is not smaller. Please enter a smaller decimal number: 347.6
Enter a whole number: 200
Enter a smaller whole number: 300
That whole number is not smaller. Please enter a smaller whole number: 20
Welcome to your civilization!
Will it stand the test of time?
You are Barrett the Great of Arabia
You send your army of 200 out to explore for threats with enough food for 20 of
them in hopes that the rest will find food to scavenge.
After 1000.39 days your army finds the borders of a large empire.
By this time only 30 soldiers remain alive in your army.
Your army soon finds out that this large empire is run by the famous warmonger G
andhi and in the 1000.39 days it took to find him he has created 400 nuclear wea
pons!
Gandhi has destroyed your civilization
Your civilization lasted 1000.39 days
Press any key to continue . . .
*/

