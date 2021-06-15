#define _CRT_SECURE_NO_WARNINGS

#include "ReadWordData.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#define WRITE_SHUFFLED_DATA // �V���b�t�������f�[�^���e�L�X�g�t�@�C���ɏ�������

const int MaxStrlen = 20; // �P��̕�����̒����̍ő�l

ReadWordData::ReadWordData()
	:WordData(NULL),
	WordNum(0),
	ShuffledWordData(NULL)
{

}

template<typename t>
void swp(t& a, t& b);
bool checkChar(char a, char b); // ���� a <= b ���ǂ����𒲂ׂ�

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
		while ((c != EOF) && (c != '\n')) { // 1�P���ǂݍ���
			WordTemp[j++] = c;
			c = fgetc(fp);
		}
		WordTemp[j] = '\0';

		if (WordNum >= MaxWordNum) { // �P�ꐔ���̈�𒴉߂�����̈�Ċm��
			MaxWordNum *= 2;
			WordData = (char**)realloc(WordData, MaxWordNum * sizeof(char**));
		}
		WordData[WordNum++] = WordTemp; // 1�P��ǉ�
		c = fgetc(fp);
	}

	char* temp = WordData[WordNum - 1];

	fclose(fp);
}

void ReadWordData::shuffle(int shufflenum)
{
	std::mt19937 mt(1);
	// todo: �����̎�����ݎ����ɂ���

	ShuffledWordData = (char**)calloc(WordNum, sizeof(char*));

	// WordData���R�s�[(���g���ς��Ȃ��悤�ɂ��邽��)
	char** Data = (char**)calloc(WordNum, sizeof(char*));
	for (int i = 0; i < WordNum; i++) {
		char* temp = (char*)malloc(strlen(WordData[i]) * sizeof(char));
		strcpy(temp, WordData[i]);
		Data[i] = temp;
	}


	// �V���b�t������
	for (int l = 0; l < shufflenum; l++) {
		if (ShuffledWordData[0] != NULL) { // 2��ڈȍ~�̃V���b�t���ł�
			free(Data);
			Data = (char**)malloc(WordNum * sizeof(char*));
			for (int k = 0; k < WordNum; k++) { // �ȑO�̃f�[�^���ڂ��ւ���
				Data[k] = (char*)malloc(strlen(ShuffledWordData[k]) * sizeof(char));
				Data[k] = ShuffledWordData[k];
			}
		}

		int i = 0;
		for (int j = WordNum - 1; j >= 0; j--) {
			std::uniform_int_distribution<> shuffleid(0, j);
			int idx = shuffleid(mt);
			char* temp = Data[idx]; // idx��j������
			Data[idx] = Data[j];
			Data[j] = temp;
			ShuffledWordData[i++] = Data[j]; // idx�̒P��f�[�^�����ʂ̃��X�g�ɋL�^����
		}
	}

	
#ifdef WRITE_SHUFFLED_DATA
	// ----- �e�L�X�g�t�@�C���ɏ������� ------
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
	int* thisIdxArray = NULL; // ���ݕ��ёւ��Ώۂ̕����̃C���f�b�N�X�̃e�[�u��

	//  --- �P��̖���������ёւ��Ă��� ---

	// �P��̃e�[�u���̕�����̍ő�C���f�b�N�X�𓱏o
	int MaxIdx = 0;
	for (int i = 0; i < WordNum; i++) {
		int ThisWordLen = strlen(ShuffledWordData[i]);
		if (MaxIdx < ThisWordLen) {
			MaxIdx = ThisWordLen;
		}
	}
	MaxIdx--;

	// ���ёւ��悤�̉��u���������ɃR�s�[
	char** tempWords = NULL;
	tempWords = (char**)malloc(WordNum * sizeof(char*));
	for (int i = 0; i < WordNum; i++) {
		char* tempWord = (char*)malloc(strlen(ShuffledWordData[i]) * sizeof(char));
		tempWord = ShuffledWordData[i];
		tempWords[i] = tempWord;
	}



	// �P��𖖔����珇�Ԃɕ��ׂĂ���
	for (int k = 0; k <= MaxIdx; k++) { // ��������k�Ԗڂ̒P��ɂ���
		thisIdxArray = (int*)malloc(WordNum * sizeof(int));
		for (int i = 0; i < WordNum; i++) { // ���ёւ��̑Ώۂ̒P��̃C���f�b�N�X�𓱂�
			int thislen = strlen(tempWords[i]) - 1;
			int thisidx = (thislen - 1 < k) ? 0 : (thislen - k - 1);
			char* thisword = tempWords[i];
			thisIdxArray[i] = thisidx;
		}

		//// �ŏ��l�𓱏o
		//char minword = tempWords[0][thisIdxArray[0]];
		//int minIdx = 0;
		//for (int i = 0; i < WordNum; i++) {
		//	char thisWord = tempWords[i][thisIdxArray[i]];
		//	if (checkChar(thisWord, minword)) {
		//		minword = thisWord;
		//		minIdx = i;
		//	}
		//}

		// �ŏ��l��擪�Ɏ����Ă���
		for (int i = WordNum - 1; i >= 1; i--) {
			char nowWord = tempWords[i][thisIdxArray[i]];
			char prevWord = tempWords[i - 1][thisIdxArray[i - 1]];
			if (checkChar(nowWord, prevWord)) { // nowWord < prevWord �Ȃ����ւ���
				swp<char*>(tempWords[i], tempWords[i - 1]);
				swp<int>(thisIdxArray[i], thisIdxArray[i - 1]);
			}
		}

		if (WordNum >= 3) {
			for (int i = 2; i < WordNum; i++) {
				for (int j = i; j >= 0; j--) {
					char thisword = tempWords[j][thisIdxArray[j]];
					char prevword = tempWords[j - 1][thisIdxArray[j - 1]];
					if (checkChar(prevword, thisword)) { // prevword < thisword �Ȃ�
						break;
					}
					swp<char*>(tempWords[j], tempWords[j - 1]);
					swp<int>(thisIdxArray[j], thisIdxArray[j - 1]);
				}
			}
		}

		// �ŏ��l��擪�Ɏ����Ă���
		//for (int i = WordNum - 1; i >= 1; i--) { 
		//	if (testData[i] < testData[i - 1]) {
		//		swp<int>(testData[i], testData[i - 1]);
		//	}
		//}

	


		//// ���ёւ�
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
	for (int i = 0; i < testNum; i++) { // �ŏ��l�𓱏o
		if (minNum > testData[i]) {
			minNum = testData[i];
		}
	}
	for (int i = testNum - 1; i >= 1; i--) { // �ŏ��l��擪�Ɉړ�
		if (testData[i] < testData[i - 1]) {
			swp<int>(testData[i], testData[i - 1]);
		}
	}

	for (int i = 0; i < testNum; i++) { // �o��
		std::cout << testData[i] << std::endl;
	}

	// ���ёւ�
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
	if (diff > 25) { // �啶���Ə������̔�r
		if (tempA >= 97) { // �������̕���啶���ɂ���
			tempA -= 32;
		}
		else if (tempB >= 97) {
			tempB -= 32;
		}
		else {
			std::cout << "�s���ȕ�����" << std::endl;
			exit(1);
		}
	}

	return (tempA <= tempB);
}
