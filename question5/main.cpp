#include <cstdlib>
#include <iostream>
//Drew Barrett
//test
using namespace std;

int main(int argc, char *argv[])
{
    int num1;
    int num2;
    int num3;
    cout << "type 3 numbers" << endl;;
    cin >> num1;
    cin >> num2;
    cin >> num3;
    int largest = num1;
    int smallest = num1;
    cout << "Permutations" << endl;
    cout << num1 << " " << num2 << " " << num3 << endl;
    cout << num1 << " " << num3 << " " << num2 << endl;
    cout << num2 << " " << num1 << " " << num3 << endl;
    cout << num2 << " " << num3 << " " << num1 << endl;
    cout << num3 << " " << num1 << " " << num2 << endl;
    cout << num3 << " " << num2 << " " << num1 << endl;
    cout << "Sum: " << num1 + num2 + num3 << endl;
    cout << "Average: " << (num1 + num2 + num3)/3 << endl;
    cout << "Multiplied: " << num1 * num2 * num3 << endl;
    if (num2 > largest){
       largest = num2;
    }
    if (num3 > largest){
       largest = num3;
    }
    cout << "Largest: " << largest << endl;
    if (num2 < smallest){
       smallest = num2;
    }
    if (num3 < smallest){
       smallest = num3;
    }
    cout << "Smallest: " << smallest << endl;
    cout << "Difference: " << largest - smallest << endl;
    
    cout << "Mod: " << largest % smallest << endl;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
/* OUTPUT:
type 3 numbers
1
2
3
Permutations
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
Sum: 6
Average: 2
Multiplied: 6
Largest: 3
Smallest: 1
Difference: 2
Mod: 0
Press any key to continue . . .
*/
