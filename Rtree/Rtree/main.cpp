#include "base.h"
#include "point.h"

int main() {
	cout << "Test" << endl;
	cout << dcmp(2.0) << endl;
	Point p, q;
	p.m_value.push_back(0); p.m_value.push_back(0);
	q.m_value.push_back(1); q.m_value.push_back(1);
	cout << p.valid() << endl;
	cout << fixed << setprecision(2) << p.distance_to(q) << endl;
	q = p;
	cout << q.m_value[0] << " " << q.m_value[1] << endl;
	cin.get();
	return 0;
}