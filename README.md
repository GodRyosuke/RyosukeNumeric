# 数値計算のサンプルプログラム
このリポジトリには、
 - 並び替え、基本データ構造いろいろ
 - 符号理論で使ったやつ
 - euler法サンプル
 - runge-kutta法サンプル

が入っている。

## eulerとrunge-kuttaについて
installation and tutorials
```bash
$ cd /path/to/desired/dir/
$ git clone https://github.com/GodRyosuke/RyosukeNumeric.git
$ cd RyosukeNumeric
$ rm -r build
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./euler # euler法でネイピア数導出
$ ./runge # runge-kutta法でネイピア数導出
```
