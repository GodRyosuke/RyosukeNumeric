#pragma once

class ReadWordData {
public:
	ReadWordData();
	void ReadWord(const char* addr); // テキストファイルからデータを読み取る
	void shuffle(int shufflenum); // shufflenum回シャッフルする
	void Insertion(); // 挿入法で並び替える

private:
	char** WordData;
	char** ShuffledWordData;
	int WordNum; // 保持単語数
};