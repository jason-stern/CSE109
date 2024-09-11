// constructing vectors
#include <iostream>
#include <vector>
using namespace std;

// shamelessly taken from cplusplus.com and modified
int main () {
  vector<int> first;                               // empty vector of ints
  vector<int> second (4,100);                      // four ints of value 100
  vector<int> third (second.begin(),second.end()); // iterating thru second
  vector<int> fourth (third);                      // a copy of third

  //int x = second.begin();
  //int y = second.end();
  //vector<int> sixth (x, y); 
  //cout << "The contents of sixth are:";
  //for (vector<int>::iterator it = sixth.begin(); it != sixth.end(); ++it)
  //  cout << ' ' << *it;
  //cout << '\n';

  cout << "The contents of first are:";
  for (vector<int>::iterator it = first.begin(); it != first.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';

  first.push_back(-17);  // inserting a value
  first.push_back(-13);
  first.push_back(-11);
  first.push_back(-7);
  first.push_back(-5);

  cout << "first[1] = " << first[1] << " and first[3] = " << first[3] << endl;  // can still access like an array

  cout << "The contents of second are:";
  for (vector<int>::iterator it = second.begin(); it != second.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';

  cout << "The contents of third are:";
  for (vector<int>::iterator it = third.begin(); it != third.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';

  cout << "The contents of fourth are:";
  for (vector<int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int));

  cout << "The contents of fifth, using 'myints[] = {16,2,77,29}', are:";
  for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';


  return 0;
}
