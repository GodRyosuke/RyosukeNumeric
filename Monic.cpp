#include "monic.h"
#include <iostream>

int Monic::convertBtoD(std::string& b)
{
	int len = b.size();
	int ans = 0;
	for (int i = 0; i < len; i++) {
		if (b[len - i - 1] == '1') {
			ans += exp(2, i);
		}
	}
	return ans;
}

int Monic::exp(int a, int b)
{
	int temp = 1;
	if (b == 0) {
		return 1;
	}
	if (b > 0) {
		for (int i = 0; i < b; i++) {
			temp *= a;
		}
	}
	else {
		std::cout << "負のべき乗は計算できません" << std::endl;
		exit(1);
	}

	return temp;
}

void Monic::ShowVectorTable(int monic)
{
	// monic多項式の最高位ビットを求める
	int deg = 0;
	for (int i = 0; i < 32; i++) {
		if (SBdigit(monic, i)) {
			deg = i;
		}
	}

	int ans = 1;
	int dm = monic;
	int tableitem = 0;
	RBdigit(dm, deg, 0);
	bool flg = 0;
	std::cout << "dm:  "; SB(dm, 5); std::cout << std::endl;
	for (int i = 0; i < 1000; i++) {
		if (SBdigit(ans, deg)) {
			RBdigit(ans, deg, 0); // 最高位ビットを0に戻す
			tableitem = polyAdd(ans, dm);
			ans = tableitem;
			flg = 1;
		}
		SB(ans, 8);
		std::cout << std::endl;
		VectorTable.push_back(ans);
		if ((ans == 1) && (flg == 1)) {
			break;
		}
		ans <<= 1;
	}

	std::cout << "-----------------" << std::endl;
	for (auto& i : VectorTable) {
		SB(i, 8);
		std::cout << ':' << i <<  std::endl;
	}
}

int Monic::SBdigit(int a, int k)
{

	return 1 & (a >> k);
}

void Monic::RBdigit(int& a, int k, int t)
{
	if ((t > 1) || (t < 0)) {
		std::cout << "書き換える数字が大きすぎます@RBdigit" << std::endl;
		exit(1);
	}
	if (t == 1) {
		if (SBdigit(a, k) == 1) {
			return;
		}
		a += exp(2, k);
		return;
	}
	else {
		if (SBdigit(a, k) == 0) {
			return;
		}
		a -= exp(2, k);
		return;
	}
}

void Monic::SB(int a, int k)
{
	for (int i = k - 1; k >= 0; k--) {
		std::cout << SBdigit(a, k) << ' ';
	}
}

int Monic::polyAdd(int a, int b)
{
	// 2つの多項式の最高位次数をそれぞれ求める
	int deg1 = 0;
	for (int i = 0; i < 32; i++) {
		if (SBdigit(a, i)) {
			deg1 = i;
		}
	}
	int deg2 = 0;
	for (int i = 0; i < 32; i++) {
		if (SBdigit(b, i)) {
			deg2 = i;
		}
	}
	int deg = (deg1 > deg2) ? deg1 : deg2;

	int ans = 0;
	for (int i = 0; i <= deg; i++) {
		if (SBdigit(a, i) == SBdigit(b, i)) {
			RBdigit(ans, i, 0);
		}
		else {
			RBdigit(ans, i, 1);
		}
	}

	return ans;
}

void Monic::CheckRand(std::vector<int> vectorI)
{
	std::vector<int>vector;
	int deg = 0; // 次数を求める
	for (auto v : vectorI) {
		for (int i = 31; i >= 0; i--) {
			if ((SBdigit(v, i) == 1) && (i > deg)) {
				deg = i;
			}
		}
	}
	for (int i = 0; i < vectorI.size() - 1; i++) {
		if (SBdigit(vectorI[i], deg)) {
			vector.emplace_back(1);
		}
		else {
			vector.emplace_back(-1);
		}
	}

	std::vector<int> temp = vector;

	std::vector<double> R(vector.size());
	for (int i = 0; i < R.size(); i++) {
		R[i] = 0;
	}
	for (int k = 0; k < vector.size(); k++) {
		ShiftLeftArray(temp, k); // kビット左シフト
		for (int i = 0; i < vector.size(); i++) { // 相関の計算
			R[k] += static_cast<double>(temp[i] * vector[i]);
		}
		R[k] /= static_cast<double>(vector.size());
	}

	int i = 0;
	for (auto r : R) {
		std::cout << i << ':' << r << std::endl;
		i++;
	}
}

void Monic::ShiftLeftArray(std::vector<int>& vector, int k)
{
	if (k < 0) {
		std::cout << "右シフトはできません" << std::endl;
		exit(1);
	}
	std::vector<int> temp(k);
	for (int i = 0; i < k; i++) {
		temp[i] = vector[i];
	}

	for (int i = k; i < vector.size(); i++) {
		vector[i - k] = vector[i];
	}
	for (int i = vector.size() - k, j = 0; i < vector.size(); i++, j++) {
		vector[i] = temp[j];
	}
}