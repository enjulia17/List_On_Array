#include "ListOnArray.h"

using namespace std;

int main()
{
	ListOnArray<int> lst(10);
	lst.push_front(3);
	lst.push_front(2);
	lst.push_front(1);
	cout << lst[1] << endl;
	cout << lst << endl;
}
	


