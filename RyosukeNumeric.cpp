#include <iostream>
#include <cmath>

// �j���[�g���@�ŉ~���������߂�(f(x) = sinx���g�p)
double innerLeadPi(double xn, int n, int k);

double LeadPi(double x0, int n)
{
	return innerLeadPi(x0, n, 0);
}

double innerLeadPi(double xn, int n, int k)
{
	if (k == n) {
		return xn;
	}
	return innerLeadPi(xn - tan(xn), n, k + 1);
}

int main(int argc, char** argv)
{
	std::cout << LeadPi(3.0, 1) << std::endl;

	// N�̉񐔂����j���[�g���@�����s
	// �e�񐔂̎��s���ʂ�\��
	int N = 20;
	for (int i = 0; i < N; i++) {
		std::cout << i << ": " << LeadPi(3.0, i) << std::endl;
	}

	std::cout << 3 - tan(3) << std::endl;

	return 1;
}