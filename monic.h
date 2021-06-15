#pragma once
#include <string>
#include <vector>

class Monic {
public:
	// 2�i���\�L����10�i���ɕϊ�
	int convertBtoD(std::string& b);
	// @return a^b
	int exp(int a, int b);
	// 2�i��a��k�̈ʂ̐���Ԃ�
	int SBdigit(int a, int k);
	// 2�i����a��k�̈ʂ̐�����t�ŏ���������
	void RBdigit(int& a, int k, int t);
	// 2�̑������̘a
	int polyAdd(int a, int b);
	// 10�i����k����2�i���\�L�ŕ\��
	void SB(int a, int k);
	// ���񑽍���monic�̃x�N�g���\�����쐬
	void ShowVectorTable(int monic);
	// �������`�F�b�N
	void CheckRand(std::vector<int> vector);

	std::vector<int> GetVectorTable() { return VectorTable; }

private:
	// vector�z���k�������ւ��炷
	void ShiftLeftArray(std::vector<int>& vector, int k);

	int monic;
	std::vector<int> VectorTable;
};