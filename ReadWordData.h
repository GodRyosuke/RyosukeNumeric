#pragma once

class ReadWordData {
public:
	ReadWordData();
	void ReadWord(const char* addr); // �e�L�X�g�t�@�C������f�[�^��ǂݎ��
	void shuffle(int shufflenum); // shufflenum��V���b�t������
	void Insertion(); // �}���@�ŕ��ёւ���

private:
	char** WordData;
	char** ShuffledWordData;
	int WordNum; // �ێ��P�ꐔ
};