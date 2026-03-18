#include <iostream>
using namespace std;
// Function Prototypes (declarations)
void say_hello();
int give_the_answer();
int double_a_number(int num);

// Function Definitions
int main()
{
say_hello();
int my_answer = give_the_answer();
cout << "The answer is: " << my_answer << endl;
cout << "Type in an integer:";
int num;
cin >> num;
// now double the answer
int twotimes = double_a_number(num);
cout << "Here's another number: " << twotimes << endl;
return 0;
}
void say_hello() {
cout << "Hello world. " << endl;
return;
}
int give_the_answer() {
return 42;
}
int double_a_number(int num) {
int new_num = num * 2;
return new_num;
}
