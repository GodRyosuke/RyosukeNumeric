#pragma once
#include <string>
#include <vector>

class Monic {
public:
	// 2進数表記から10進数に変換
	int convertBtoD(std::string& b);
	// @return a^b
	int exp(int a, int b);
	// 2進数aのkの位の数を返す
	int SBdigit(int a, int k);
	// 2進数のaのkの位の数字をtで書き換える
	void RBdigit(int& a, int k, int t);
	// 2つの多項式の和
	int polyAdd(int a, int b);
	// 10進数をk桁分2進数表記で表示
	void SB(int a, int k);
	// 既約多項式monicのベクトル表現を作成
	void ShowVectorTable(int monic);
	// 乱数かチェック
	void CheckRand(std::vector<int> vector);

	std::vector<int> GetVectorTable() { return VectorTable; }

private:
	// vector配列をkだけ左へずらす
	void ShiftLeftArray(std::vector<int>& vector, int k);

	int monic;
	std::vector<int> VectorTable;
};