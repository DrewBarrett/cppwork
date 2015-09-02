#include <iostream>
//Drew Barrett
using namespace std;

string leader;
string civilization;
double gandhidistance; //distance to gandis empire
double gandhisize; //size of gandhis borders
double gandhiborders; //calcuated distance to gandhis borders
int armysize; //size of player army
int armyfood; //food of army
int armysurvivors; // amount of surviving army

int sizecheckdouble(){
    if(gandhisize >= gandhidistance){
        cout << "That decimal number is not smaller. Please enter a smaller decimal number: ";
        cin >> gandhisize;
        sizecheckdouble();//repeat check with new value
    }else{
        return 0;
    }
}
int sizecheckint(){
    if(armyfood >= armysize){
        cout << "That whole number is not smaller. Please enter a smaller whole number: ";
        cin >> armyfood;
        sizecheckint();//repeat check with new value
    }else{
        return 0;
    }
}

int main()
{
    cout << "Please enter the following to begin the game" << endl
    << "Enter your last name: ";
    getline(cin, leader);
    cout << "Enter the name of a country/empire: ";
    getline(cin, civilization);
    cout << "Enter a large decimal number: ";
    cin >> gandhidistance;
    cout << "Enter a smaller decimal number: ";
    cin >> gandhisize;
    sizecheckdouble(); //make sure size is smaller
    gandhiborders = gandhidistance - (gandhisize/2);//distance to gandhi borders
    cout << "Enter a whole number: ";
    cin >> armysize;
    cout << "Enter a smaller whole number: ";
    cin >> armyfood;
    sizecheckint();//same thing as before with different message
    armysurvivors = armyfood/*base survivors*/ + (armysize/armyfood);//amount of people able to scavenge food
    cout << "Welcome to your civilization!\nWill it stand the test of time?\n";
    cout << "You are " << leader << " the Great of " << civilization << endl;
    cout << "You send your army of " << armysize << " out to explore for threats with enough food for "
    << armyfood << " of them in hopes that the rest will find food to scavenge\n";
    cout << "After " << gandhidistance/2/*time to get to borders*/
    << " days your army finds the borders of a large empire. By this time only "
    << armysurvivors << " soldiers remain alive in your army.\n";
    cout << "Your army soon finds out that this large empire is run by the famous warmonger Gandhi and in the "
    << gandhidistance/2 " days it took to find him he has created " << gandhidistance
    return 0;
}


