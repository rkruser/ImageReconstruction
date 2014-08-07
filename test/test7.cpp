#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<double> b;
	b.reserve(20);
	cout << b.size() << '\n';
	b.push_back(3);
	cout << b.size() << '\n';
	for (int i = 0; i < b.size(); i++) {
		cout << b[i] << ' ';
	}
	cout << '\n';




	return 0;
}
