#define _CRT_SECURE_NO_WARNINGS

#include "ReadWordData.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#define WRITE_SHUFFLED_DATA // シャッフルしたデータをテキストファイルに書き込む

const int MaxStrlen = 20; // 単語の文字列の長さの最大値

ReadWordData::ReadWordData()
	:WordData(NULL),
	WordNum(0),
	ShuffledWordData(NULL)
{

}

template<typename t>
void swp(t& a, t& b);
bool checkChar(char a, char b); // 文字 a <= b かどうかを調べる

void testInsertion();

void ReadWordData::ReadWord(const char* addr)
{
	const int WordSize = 20;

	FILE* fp = fopen(addr, "rb");
	if (!fp) {
		std::cout << "error: failed to open file" << std::endl;
		exit(1);
	}

	char c = fgetc(fp);
	int MaxWordNum = 200;
	WordData = (char**)calloc(MaxWordNum, sizeof(char*));
	while (c != EOF) {
		char* WordTemp = (char*)calloc(WordSize, sizeof(char));
		int j = 0;
		while ((c != EOF) && (c != '\n')) { // 1単語を読み込む
			WordTemp[j++] = c;
			c = fgetc(fp);
		}
		WordTemp[j] = '\0';

		if (WordNum >= MaxWordNum) { // 単語数が領域を超過したら領域再確保
			MaxWordNum *= 2;
			WordData = (char**)realloc(WordData, MaxWordNum * sizeof(char**));
		}
		WordData[WordNum++] = WordTemp; // 1単語追加
		c = fgetc(fp);
	}

	char* temp = WordData[WordNum - 1];

	fclose(fp);
}

void ReadWordData::shuffle(int shufflenum)
{
	std::mt19937 mt(1);
	// todo: 乱数の種を現在時刻にする

	ShuffledWordData = (char**)calloc(WordNum, sizeof(char*));

	// WordDataをコピー(中身が変わらないようにするため)
	char** Data = (char**)calloc(WordNum, sizeof(char*));
	for (int i = 0; i < WordNum; i++) {
		char* temp = (char*)malloc(strlen(WordData[i]) * sizeof(char));
		strcpy(temp, WordData[i]);
		Data[i] = temp;
	}


	// シャッフルする
	for (int l = 0; l < shufflenum; l++) {
		if (ShuffledWordData[0] != NULL) { // 2回目以降のシャッフルでは
			free(Data);
			Data = (char**)malloc(WordNum * sizeof(char*));
			for (int k = 0; k < WordNum; k++) { // 以前のデータを移し替える
				Data[k] = (char*)malloc(strlen(ShuffledWordData[k]) * sizeof(char));
				Data[k] = ShuffledWordData[k];
			}
		}

		int i = 0;
		for (int j = WordNum - 1; j >= 0; j--) {
			std::uniform_int_distribution<> shuffleid(0, j);
			int idx = shuffleid(mt);
			char* temp = Data[idx]; // idxとjを交換
			Data[idx] = Data[j];
			Data[j] = temp;
			ShuffledWordData[i++] = Data[j]; // idxの単語データを結果のリストに記録する
		}
	}

	
#ifdef WRITE_SHUFFLED_DATA
	// ----- テキストファイルに書き込む ------
	FILE* fp = fopen("shuffled_data.txt", "wb");
	if (!fp) {
		std::cout << "error: failed to open file to write" << std::endl;
		exit(1);
	}

	for (int k = 0; k < WordNum; k++) {
		int length = strlen(ShuffledWordData[k]);
		for (int l = 0; l < length; l++) {
			fputc(ShuffledWordData[k][l], fp);
		}
		fputc('\n', fp);
	}

	fclose(fp);
	// -------------------------------------
#endif
}


void ReadWordData::Insertion()
{
	int* thisIdxArray = NULL; // 現在並び替え対象の文字のインデックスのテーブル

	//  --- 単語の末尾から並び替えていく ---

	// 単語のテーブルの文字列の最大インデックスを導出
	int MaxIdx = 0;
	for (int i = 0; i < WordNum; i++) {
		int ThisWordLen = strlen(ShuffledWordData[i]);
		if (MaxIdx < ThisWordLen) {
			MaxIdx = ThisWordLen;
		}
	}
	MaxIdx--;

	// 並び替えようの仮置きメモリにコピー
	char** tempWords = NULL;
	tempWords = (char**)malloc(WordNum * sizeof(char*));
	for (int i = 0; i < WordNum; i++) {
		char* tempWord = (char*)malloc(strlen(ShuffledWordData[i]) * sizeof(char));
		tempWord = ShuffledWordData[i];
		tempWords[i] = tempWord;
	}



	// 単語を末尾から順番に並べていく
	for (int k = 0; k <= MaxIdx; k++) { // 末尾からk番目の単語について
		thisIdxArray = (int*)malloc(WordNum * sizeof(int));
		for (int i = 0; i < WordNum; i++) { // 並び替えの対象の単語のインデックスを導く
			int thislen = strlen(tempWords[i]) - 1;
			int thisidx = (thislen - 1 < k) ? 0 : (thislen - k - 1);
			char* thisword = tempWords[i];
			thisIdxArray[i] = thisidx;
		}

		//// 最小値を導出
		//char minword = tempWords[0][thisIdxArray[0]];
		//int minIdx = 0;
		//for (int i = 0; i < WordNum; i++) {
		//	char thisWord = tempWords[i][thisIdxArray[i]];
		//	if (checkChar(thisWord, minword)) {
		//		minword = thisWord;
		//		minIdx = i;
		//	}
		//}

		// 最小値を先頭に持ってくる
		for (int i = WordNum - 1; i >= 1; i--) {
			char nowWord = tempWords[i][thisIdxArray[i]];
			char prevWord = tempWords[i - 1][thisIdxArray[i - 1]];
			if (checkChar(nowWord, prevWord)) { // nowWord < prevWord なら入れ替える
				swp<char*>(tempWords[i], tempWords[i - 1]);
				swp<int>(thisIdxArray[i], thisIdxArray[i - 1]);
			}
		}

		if (WordNum >= 3) {
			for (int i = 2; i < WordNum; i++) {
				for (int j = i; j >= 0; j--) {
					char thisword = tempWords[j][thisIdxArray[j]];
					char prevword = tempWords[j - 1][thisIdxArray[j - 1]];
					if (checkChar(prevword, thisword)) { // prevword < thisword なら
						break;
					}
					swp<char*>(tempWords[j], tempWords[j - 1]);
					swp<int>(thisIdxArray[j], thisIdxArray[j - 1]);
				}
			}
		}

		// 最小値を先頭に持ってくる
		//for (int i = WordNum - 1; i >= 1; i--) { 
		//	if (testData[i] < testData[i - 1]) {
		//		swp<int>(testData[i], testData[i - 1]);
		//	}
		//}

	


		//// 並び替え
		//if (testNum >= 3) {
		//	for (int i = 2; i < testNum; i++) {

		//		for (int j = i; j >= 0; j--) {
		//			if (testData[j - 1] < testData[j]) {
		//				break;
		//			}
		//			swp<int>(testData[j - 1], testData[j]);
		//		}
		//	}
		//}
		for (int i = 0; i < WordNum; i++) {
			std::cout << tempWords[i] << std::endl;
		}
		std::cout << "------------------" << std::endl;

		free(thisIdxArray);
		thisIdxArray = NULL;
	}

}

void testInsertion()
{
	int testNum = 20;

	std::mt19937 mt(1);

	int* testData = (int*)malloc(testNum * sizeof(int));
	for (int i = 0; i < testNum; i++) {
		std::uniform_int_distribution<> testRand(-100, 100);
		testData[i] = testRand(mt);
	}

	int minNum = testData[0];
	for (int i = 0; i < testNum; i++) { // 最小値を導出
		if (minNum > testData[i]) {
			minNum = testData[i];
		}
	}
	for (int i = testNum - 1; i >= 1; i--) { // 最小値を先頭に移動
		if (testData[i] < testData[i - 1]) {
			swp<int>(testData[i], testData[i - 1]);
		}
	}

	for (int i = 0; i < testNum; i++) { // 出力
		std::cout << testData[i] << std::endl;
	}

	// 並び替え
	if (testNum >= 3) {
		for (int i = 2; i < testNum; i++) {

			for (int j = i; j >= 0; j--) {
				if (testData[j - 1] < testData[j]) {
					break;
				}
				swp<int>(testData[j - 1], testData[j]);
			}
		}
	}

	for (int i = 0; i < testNum; i++) {
		std::cout << i << ":" << testData[i] << std::endl;
	}

}

template<typename t>
void swp(t& a, t& b)
{
	t temp = a;
	a = b;
	b = temp;
}

bool checkChar(char a, char b)
{
	int tempA = a;
	int tempB = b;
	int diff = ((a - b >= 0) ? a - b : b - a);
	if (diff > 25) { // 大文字と小文字の比較
		if (tempA >= 97) { // 小文字の方を大文字にする
			tempA -= 32;
		}
		else if (tempB >= 97) {
			tempB -= 32;
		}
		else {
			std::cout << "不正な文字列" << std::endl;
			exit(1);
		}
	}

	return (tempA <= tempB);
}
