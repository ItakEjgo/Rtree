#include "base.h"

int dcmp(const db &x) {
	if (fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}
