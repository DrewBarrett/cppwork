#include <cstdlib>
#include <iostream>
//Drew Barrett
using namespace std;

int main(int argc, char *argv[])
{
    string first;
    string last;
    int age;
    cout << "Enter first name: ";
    cin >> first;
    cout << "Enter last name: ";
    cin >> last;
    cout << "Enter age: ";
    cin >> age;
    cout << "Hello " << first << " " << last << " you now have access to our features for ";
    if(age > 65){
           cout << "retired people";
    }else if(age > 30){
          cout << "working adults";
    }else if(age > 19){
          cout << "young adults";
    }else if(age > 12){
          cout << "teens";
    }else{
          cout << "children";
    }
    cout << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
/*
Enter first name: Drew
Enter last name: Barrett
Enter age: 6
Hello Drew Barrett you now have access to our features for children
Press any key to continue . . .

Enter first name: Drew
Enter last name: Barrett
Enter age: 13
Hello Drew Barrett you now have access to our features for teens
Press any key to continue . . .

Enter first name: Drew
Enter last name: Barrett
Enter age: 20
Hello Drew Barrett you now have access to our features for young adults
Press any key to continue . . .

Enter first name: Drew
Enter last name: Barrett
Enter age: 31
Hello Drew Barrett you now have access to our features for working adults
Press any key to continue . . .

Enter first name: Drew
Enter last name: Barrett
Enter age: 173
Hello Drew Barrett you now have access to our features for retired people
Press any key to continue . . .
*/
