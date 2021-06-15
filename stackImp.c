//#include<stdio.h>
//#include<stdlib.h>
//#include"Interface.h"
//#include "Item.h"
//#define exch(A, B){Item t = A; A = B; B = t;} //AとBを入れ替える
//
//typedef int Item;
//static int N;
//static Item* stack;
//static Item* aux;
//
//int count;
//
//typedef struct list {
//	Item item;
//	struct list* next;
//}List;
//
//void stackinit(int maxN) {
//	stack = malloc(maxN * sizeof(int));
//	N = 0;
//}
//
//void push(Item item) {
//	stack[N++] = item;
//}
//
//Item pop() {
//	
//	return stack[--N];
//}
//
//int stackEmpty() {
//	return N == 0;
//}
//
//static List* top, * bottom;
//void qinit(int maxN) {
//	top = malloc(sizeof(List));
//	bottom = top;
//}
//
//void qinsert(Item item) {
//	List* t = malloc(sizeof(List)); t->next = malloc(sizeof(List));
//	if (top == bottom) {
//		top->next = t;
//		t->item = item; bottom = t;
//	}
//	t->item = item;
//	bottom->next = t; bottom = t;
//}
//
//Item qget() {
//	List* t = top->next;
//	free(top); top = t;
//	return top->item;
//}
//
//int qEmpty() {
//	return top == bottom;
//}
//
//static int M = 9;
//
//void selection(Item* a, int l, int r) 
//{
//	int i, j, min = 0, tmp;
//	for (i = l; i <= r; i++) {
//		for (j = i; j <= r; j++) {
//			if (a[min] > a[j])min = j;
//		}
//		tmp = a[i]; a[i] = a[min]; a[min] = tmp;
//	}
//}
//
//void insertion(Item* a, int l, int r)
//{
//	int i, j, tmp;
//	for (i = l; i <= r; i++) {
//		for (j = i; j > l; j--) {
//			if (a[j - 1] > a[j]) {
//				tmp = a[j]; a[j] = a[j - 1]; a[j - 1] = tmp;
//			}
//		}
//	}
//}
//
//void insertsort(Item* a, int l, int r) {
//	int i, j, v, min, tmp;
//	for (i = r, min = l; i  > l; i--) 
//		if (a[i - 1] > a[i]) {
//			tmp = a[i];
//			a[i] = a[i - 1];
//			a[i - 1] = tmp;
//		}
//	for (i = l + 2; i <= r; i++) {
//		v = a[i];
//		for (j = i; a[j - 1] > v; j--) {
//			a[j] = a[j - 1];
//		}
//		a[j] = v;
//	}
//}
//
//void bubble(Item* a, int l, int r) {
//	int i, j, tmp;
//	for (i = l; i < r; i++) {
//		for (j = r; j > i; j--) {
//			if (a[j - 1] > a[j]){ tmp = a[j]; a[j] = a[j - 1]; a[j - 1] = tmp; }
//		}
//	}
//}
//
//void shellsort(Item* a, int l, int r) {
//	int i, j, h, v, tmp;
//	
//	for (h = 1; h <= (r - l) / 9; h = h * 3 + 1);
//	for (; h > 0; h /= 3) {
//		for (i = l + h; i <= r; i++) {
//			for (j = i, v = a[i]; (j - h >= l) && (a[j - h] > v); j -= h) {
//				a[j] = a[j - h];
//			}
//			a[j] = v;
//		}
//	}
//}
//
//void insitu(int* data, int* a, int l, int r) {
//	int i, j,tmp, v;
//	for (i = l; i <= r; i++) {
//		v = data[i];
//		for (j = i; a[j] != i; j = tmp) {
//			data[j] = data[a[j]];
//			tmp = a[j];
//			a[j] = j;
//		}
//		a[j] = v; a[j] = j;
//	}
//}
//
//List* listselection(List* L) {
//	List* t = malloc(sizeof(List)), * Max, * x, * out = NULL;
//	while (L->next != NULL){
//		for (t = L, Max = L; t->next != NULL; t = t->next) //minの後ろの要素がLの最小値
//			if (Max->next->item < t->next->item)Max = t;
//		x = Max->next; Max->next = x->next;//最大値をLから削除
//		x->next = out; out = x;
//	}
//	L->next = out;
//	return L;
//}
//
////キー添字計数法 時間は線形　ただし、キーの値の範囲はファイルによらず一定
//void distcount(Item* a, int l, int r) {
//	int N = 50, n = r - l + 1, j = 0, i;
//	int* arr = malloc(N * sizeof(int)), * b = malloc(n * sizeof(int));
//	for (i = l; i <= r; i++)arr[j++] = 0;//0で初期化
//	for (i = l; i <= r; i++)arr[a[i] + 1]++; //配列a要素の個数を、arr配列に代入
//	for (i = 1; i < N; i++) arr[i] += arr[i - 1]; //これで対象要素が並び替え後の配列の開始インデックスになる
//	for (i = l; i <= r; i++)b[arr[a[i]]++] = a[i];
//	for (i = l; i <= r; i++)a[i] = b[i - l];
//}
//
////クイックソートにおける分割処理
//int partion(Item* a, int l, int r){
//	int i = l- 1, j = r, v = a[r], t;
//	for (;;) {
//		while (a[++i] < v);
//		while (a[--j] > v)if (j == l)break;
//		if (j <= i)break;
//		t = a[i]; a[i] = a[j]; a[j] = t;
//	}
//	t = a[i]; a[i] = a[r]; a[r] = t;
//	return i;
//}
//
//void quicksort(Item* a, int l, int r) {
//	if (r <= l)return;	//最小の要素にたどり着いたら、これが成立する。
//	int i = partion(a, l, r);
//	quicksort(a, l, i - 1); quicksort(a, i + 1, r);
//}
//
////非再帰版のクイックソート
//void quicksortN(Item* a, int l, int r) {
//	int i;
//	stackinit(1000);
//	push(r); push(l);
//	while (!stackEmpty()) {
//		l = pop(); r = pop();
//		if (r <= l)continue;
//		i = partion(a, l, r);
//		if ((i - l) < (r - i)) {
//			push(r); push(i + 1); push(i - 1); push(l);
//		}
//		else {
//			push(i - 1); push(l); push(r); push(i + 1);
//		}
//	}
//}
//
////大きさMでソートをやめるクイックソート
//void quicksortF(int* a, int l, int r) {
//	int i;
//	if ((r - l) <= M) {
//		//insertsort(a, l, r);
//		return;
//	}
//	i = partion(a, l, r);
//	quicksortF(a, l, i - 1);
//	quicksortF(a, i + 1, r);
//}
//
////中央値で分割するクイックソート
//void quicksortR(int* a, int l, int r) {
//	int i, j, m = (l + r) / 2, t;
//	if ((r - l) <= M)return;
//	t = a[m]; a[m] = a[r - 1]; a[r - 1] = t;
//	if (a[l] > a[r - 1])t = a[l]; a[l] = a[r - 1]; a[r - 1] = t;
//	if (a[l] > a[r])t = a[l]; a[l] = a[r]; a[r] = t;
//	if (a[r - 1] > a[r])t = a[r]; a[r] = a[r - 1]; a[r - 1] = t;
//	i = partion(a, l + 1, r - 1);
//	quicksortR(a, l, i - 1); quicksortR(a, i + 1, r);
//}
//
////3分岐の分割によるクイックソート
//void quicksortS(int* a, int l, int r) {
//	int i = l - 1, p = l - 1, j = r, q = r, v = a[r], t, k;
//	if (r <= l)return;
//	for (;;) {
//		while (a[++i] < v);
//		while (a[--j] > v)if (j == l)break;
//		if (j <= i)break;
//		t = a[i]; a[i] = a[j]; a[j] = t;
//		if (a[i] == a[r]) {
//			p++; t = a[p]; a[p] = a[i]; a[i] = t;
//		}
//		if (a[j] == a[r]) {
//			q--; t = a[q]; a[q] = a[j]; a[j] = t;
//		}
//	}
//	t = a[i]; a[i] = a[r]; a[r] = t;
//	for (j = i + 1, k = r - 1; k >= q; k--, j++) { t = a[j]; a[j] = a[k]; a[k] = t;}
//	for (i = i - 1, k = l; k <= p; k++, i--) { t = a[i]; a[i] = a[k]; a[k] = t; }
//	quicksortS(a, l, i); quicksortS(a, j, r);
//}
//
////クイックソートを用いた探索
//int select(int* a, int l, int r, int k) {
//	if (r <= l)return a[l];
//	int i = partion(a, l, r);
//	if (i == k)return a[k];
//	if (k < i)return select(a, l, i - 1, k);
//	if (i < k)return select(a, i + 1, r, k);
//}
//
////クイックソートを用いた探索　非再帰版
//int selectN(int* a, int l, int r, int k) {
//	int i;
//	while (l <= r) {
//		i = partion(a, l, r);
//		if (k == i)return a[i];
//		if (k < i)r = i - 1;
//		if (i < k)l = i + 1;
//	}
//	return 0;
//}
//
//
//int aux[100000];
//
//
////配列a, bを配列cにマージして格納する
//void mergeAB(int* a, int M, int* b, int N, int* c) {
//	int i, j, k;
//	for (k = 0, i = 0, j = 0; k < N + M + 1; k++) {
//		if (i == M) { c[k] = b[j++]; continue; }
//		if (j == N) { c[k] = a[i++]; continue; }
//		c[k] = (a[i] < b[j]) ? a[i++] : b[j++];
//	}
//}
//
////配列aのl - m, m + 1 - r それぞれに入っている２配列をマージする
//void mergeBI(int* a, int l, int m, int r) {
//	int i, j, k;
//	for (i = m + 1; i > l; i--)aux[i - 1] = a[i - 1]; //バイトニック列
//	for (j = m; j < r; j++) aux[r - j + m] = a[j + 1];
//	for (k = l; k <= r; k++) {
//		a[k] = (aux[i] < aux[j]) ? aux[i++] : aux[j--];
//	}
//}
// 
////トップダウン型マージソート
//void mergesort(int* a, int l, int r) {
//	int m = (l + r) / 2;
//	if (r <= l)return;
//	mergesort(a, l, m); mergesort(a, m + 1, r);
//	mergeBI(a, l, m, r);
//}
//
////コピー無しのマージソート
////配列ｂを並び替えて、配列aに格納する
//void mergesortABr(int* a, int* b, int l, int r) {
//	int i, j, m = (r + l) / 2;
//	if ((r - l) <= M) {
//		insertsort(a, l, r); return;
//	}
//	mergesortABr(b, a, l, m); mergesortABr(b, a, m + 1, r);
//	mergeAB(b + l, m - l + 1, b + m + 1, r - m, a);
//}
//
////ボトムアップ型のマージソート
//void mergesortBU(int* a, int l, int r) {
//	int i, j, m;
//	for (m = 1; m <= r - l; m *= 2) {
//		for (i = l; i + m < r; i += m * 2)
//			mergeBI(a, i,i + m - 1, (i + m + m - 1 < r) ? i + m + m - 1 : r);
//	}
//}
//
////リストを用いた併合操作
////リストa, bは頭から要素が格納されている
////返値のリストも先頭セルはなく、初めから要素が入っている
//List* mergeList(List* a, List* b) {
//	List* t, * c = malloc(sizeof(List)), * head ;
//	head = c;
//	while ((a != NULL) && (b != NULL)) {
//		if (a->item < b->item) {
//			c->next = a; c = a;
//			a = a->next; 
//			continue;
//		}
//		else {
//			c->next = b; c = b;
//			b = b->next;
//			continue;
//		}
//	}
//	c->next = (a == NULL) ? b : a;
//	return head->next;
//}
//
////トップダウン型のリストマージソート
//List* mergesortList(List* c) {
//	List* t,* a,* b;
//	if ((c == NULL) || (c->next == NULL))return c;
//	a = c;  b = c->next;
//	while ((b != NULL) && (b->next != NULL)) { //リストを半分にする
//		c = c->next; b = b->next->next;
//	}
//	b = c->next; c->next = NULL;
//	return mergeList(mergesortList(a), mergesortList(b));
//}
//
////ボトムアップ型のリストマージソート
//List* mergesortListBU(List* a) {
//	List* u;
//	int i;
//	for (; a != NULL; a = u) {
//		u = a->next; a->next = NULL; QLput(a);
//	}
//	u = QLget();
//	while (!QLEmpty()) {
//		QLput(u);
//		u = mergeList(QLget(), QLget());
//	}
//	return u;
//}
//
//typedef struct Qlink {
//	List* item;
//	struct Qlink* next;
//}Qlink;
//Qlink* head, * tail;
//
//Qlink* NEW(List* item, Qlink* next) {
//	Qlink* u = malloc(sizeof(Qlink));
//	u->item = item; u->next = next;
//	return u;
//}
//
//void QLinit(void) {
//	head = NULL;
//}
//
//void QLput(List* t) {
//	if (head == NULL) {
//		head = (tail = NEW(t, head)); //循環リスト
//		return;
//	}
//	tail->next = NEW(t, tail->next);
//	tail = tail->next;
//}
//
//List* QLget() {
//	Qlink* u = head->next;
//	List* It = head->item;
//	free(head);
//	head = u; return It;
//}
//
//int QLEmpty() {
//	return head == NULL;
//}
//
//
//
//static Item* pq;
//static int PN;
//
////maxN個の要素を持つ順位キューを作る
//void PQinit(int maxN) {
//	pq = malloc(maxN * sizeof(Item));
//}
//int PQempty() { //順位キューの空判定
//	return N == 0;
//}
//void PQinsert(Item v) { // 順位キューの挿入操作
//	pq[N++] = v;
//}
//Item PQdelmax() { // 順位キューの最大値削除
//	int i = 0, max = 0, t;
//	for (i = 0; i < N; i++) {
//		if (pq[max] < pq[i])max = i;
//	}
//	t = pq[max]; pq[max] = pq[N - 1]; pq[N - 1] = t;
//	return pq[--N];
//}
//
////ボトムアップ型のヒープ化
//void fixup(Item* a, int k) {
//	int i; Item t;
//	for (i = k; i > 1; i /= 2) {
//		if (a[i] < a[i / 2])break;
//		t = a[i]; a[i] = a[i / 2]; a[i / 2] = t;
//	}
//}
//
////トップダウン型のヒープ化
//void fixdown(Item* a, int k, int N) { 
//	int i, j; Item t;
//	for (i = k; i * 2 <= N; i = j) {
//		j = i * 2;
//		if ((j < N) && (a[j] < a[j + 1]))j++;
//		if (a[i] >= a[j])break;
//		t = a[i]; a[i] = a[j]; a[j] = t;
//	}
//}
//
////heapに基づく順位キューの初期化
//void PQinitHP(int maxN) {
//	pq = malloc((maxN + 1) * sizeof(Item)); //maxN個のヒープ領域を確保
//}
//
//int PQemptyHP() {
//	return PN == 0;
//}
//
//void PQinsertHP(Item v) {
//	pq[++PN] = v;
//	fixup(pq, PN);
//}
//
//Item PQdelmaxHP() {
//	Item t;
//	int i;
//	t = pq[1]; pq[1] = pq[PN]; pq[PN] = t;
//	fixdown(pq, 1, PN - 1);
//	return pq[PN--];
//}
//
//void PQsort(Item* a, int l, int r) {
//	int i, nn = r - l + 1;
//	PQinit(nn);
//	for (i = l; i <= r; i++)PQinsert(a[i]);
//	for (i = r; !PQempty(); i--)a[i] = PQdelmax();
//}
//
//void heapsort(Item* a, int l, int r) {
//	int i, nn = r - l + 1; pq = a + l - 1; Item t;
//	for (i = nn / 2; i >= 1; i--)fixdown(pq, i, nn); //ヒープを作る
//	while (nn > 1) {
//		t = pq[1]; pq[1] = pq[nn]; pq[nn] = t;
//		fixdown(pq, 1, --nn);
//	}
//	a = pq + 1;
//}
//
//typedef struct PQnode {
//	Item key;
//	struct PQnode*  prev,* next;
//}PQlink;
//typedef struct pq{
//	PQlink* head,* tail;
//} PQ;
//
//PQ* PQLinit() {
//	PQ* pql = malloc(sizeof(PQ));
//	PQlink* h = malloc(sizeof(PQlink)),
//		*t = malloc(sizeof(PQlink));
//	h->prev = t; h->next = t;
//	t->prev = h; t->next = h;
//	pql->head = h; pql->tail = t;
//	return pql;
//}
//
//int PQLemmpty(PQ* pql) {
//	return pql->head->next->next == pql->head;
//}
//
//void PQLinsert(PQ* pql, Item v) {
//	PQlink* t = malloc(sizeof(PQlink));
//	t->key = v;
//	t->next = pql->head->next; t->next->prev = t;
//	t->prev = pql->head; pql->head->next = t;
//}
//
//Item PQLdelmax(PQ* pql) {
//	Item max; PQlink* t,* x = pql->head->next;
//	for (t = x; t != pql->head; t = t->next)
//		if (t->key > x->key) x = t;
//	max = x->key;
//	x->next->prev = x->prev;
//	x->prev->next = x->next;
//	free(x); return max;
//}
//
//void PQLjoin(PQ* a, PQ* b) { //両方向リストa, bについて、aの後ろにbをつなげる
//	a->tail->prev->next = b->head->next;
//	b->head->next->prev = a->tail->prev;
//	a->head->prev = b->tail;
//	b->tail->next = a->head;
//	free(a->tail); free(b->head);
//}
//
////struct PQnodeB {
////	Item key;
////	struct PQnodeB* l, * r;
////};
////struct pqB {
////	PQlinkB** bq;
////};
////
////PQlinkB* pair(PQlinkB* p, PQlinkB* q) {
////	if (p->key < q->key) {
////		p->r = q->l; q->l = p; return q;
////	}
////	else {
////		q->r = q->l; p->l = q; return p;
////	}
////}
////
////PQB* PQBinit() {
////	int i;
////	PQB* c = malloc(sizeof(PQB));
////	c->bq = malloc(maxbq * sizeof(PQlinkB*));
////	for (i = 0; i < maxbq; i++) {
////		c->bq[i] = malloc(sizeof(PQlinkB));
////		c->bq[i] = NULL;
////	}
////
////	return c;
////}
////
////void PQinsertB(PQB* pq, Item v) {
////	int i; PQlinkB* c = malloc(sizeof(PQlinkB)),* t;
////	t = c;
////	c->key = v; c->r = NULL; c->l = NULL;
////	for (i = 0; i < maxbq; i++) { //cは繰り上がりの数字が入る
////		if (c == NULL)break;
////		if (pq->bq[i] == NULL) { //1 + 0 = 1
////			pq->bq[i] = c; break;
////		}
////		c = pair(pq->bq[i], c); pq->bq[i] = NULL; // 1 + 1 = 10
////	}
////}
////
////Item PQBdelmax(PQB* pq) {
////	int i, max; PQlinkB* x; Item v; //vに最大値を格納
////	PQB* temp1 = PQBinit(); PQlinkB** temp = temp1->bq;
////	for (i = 0; i < maxbq; i++)
////		if (pq->bq[i] != NULL) {
////			v = pq->bq[i]->key;
////			break;
////		}
////	for (i = 0, max = -1; i < maxbq; i++) //pqの要素のうち、最大値を探す
////		if (pq->bq[i] != NULL)
////			if ((max == -1) || (v < pq->bq[i]->key)) {
////				max = i; v = pq->bq[i]->key;
////			}
////	x = pq->bq[max]->l;
////	for (i = max; i < maxbq; i++)temp[i] = NULL;
////	for (i = max; i > 0; i--) {
////		temp[i - 1] = x;
////		//if (x == NULL)break;
////		x = x->r; temp[i - 1]->r = NULL;
////	}
////	free(pq->bq[max]);
////	pq->bq[max] = NULL;
////	BQjoin(pq->bq, temp);
////	return v;
////}
////
////#define test(C, B, A) 4 * (C) + 2 * (B) + 1 * (A)
////void BQjoin(PQlinkB** a, PQlinkB** b) {
////	int i; PQlinkB* c = malloc(sizeof(PQlinkB)); c = NULL;
////	for (i = 0; i < maxbq; i++)
////		switch (test(c != NULL, b[i] != NULL, a[i] != NULL)) {
////		case 2: a[i] = b[i]; break;
////		case 3: c = pair(a[i], b[i]);
////			a[i] = NULL; break;
////		case 4: a[i] = c; c = NULL; break;
////		case 5: c = pair(c, a[i]); a[i] = NULL; break;
////		case 6: 
////		case 7: c = pair(c, b[i]); break;
////		}
////}
//
//
//
//#define digit(A, B)(((A) >> (bitsword - (B) - 1)) & 1 )//AのBビット目を取り出す
//#define bin(A) l + count[A] //配列を分けたビン
//#define Bytes(A, B)((A)[bytesword - (B) - 1])
//
//int bitsword = 8;
//
//void quicksortB(int* a, int l, int r, int w) {//bit演算を用いたクイックソートクイックソート
//	int i, j; i = l; j = r;
//	if ((r <= l) || (w > bitsword))return;
//	while (i != j) {
//		while (((digit(a[i], w)) == 0) && (i < j))i++;
//		while (((digit(a[j], w)) == 1) && (i < j))j--;
//		exch(a[i], a[j]);
//	}
//	if ((digit(a[r], w)) == 0)j++;
//	quicksortB(a, l, j - 1, w + 1); quicksortB(a, j , r, w + 1);
//}
////
////
////
////void radixMSD(Item* a, int l, int r, int w) {
////	int i, j;
////	if (w >= bitsword ) return;
////	if (r - l <= M) {
////		insertion(a, l, r);
////		return;
////	}
////	for (i = 0; i < R; i++)count[i] = 0;
////	for (i = l; i <= r; i++)count[(digit(a[i], w)) + 1]++;
////	for (i = 1; i < R ; i++)count[i] = count[i - 1];
////	for (i = l; i <= r; i++)aux[count[(digit(a[i], w))]++] = a[i];
////	for (i = l; i <= r; i++)a[i] = aux[i - l];
////	radixMSD(a, l, count[0] - 1, w + 1);
////	for (i = 0; i < R - 2; i++)radixMSD(a, count[i], count[i + 1] - 1, w + 1);
////}
////
//////なぜ動かない？
////void sortRadixMSD(Item* a, int l, int r) {
////	aux = malloc((r - l + 1) * sizeof(Item));
////	count = malloc(R * sizeof(int));
////	radixMSD(a, l, r, 0);
////}
//
////なぜ動かない？
//void quicksortX(Item* a, int l, int r, int w) {
//	int i, j, q, p, k;
//	i = p = l - 1; j = q = r;
//	Item v = digit(a[r], w);
//	if ((r - l) <= M) {
//		insertion(a, l, r); 
//		return;
//	}
//	while (i < j) {
//		while ((digit(a[++i], w)) < v) {
//			printf("(i)a[%d]: ", i); shownomber(a[i]);
//		}
//		while ((digit(a[--j], w)) > v) {
//			printf("(j)a[%d]: ", j); shownomber(a[j]);
//			if (j == l)break;
//		}
//		if (j < i)break;
//		printf("exch((i)a[%d] = %d,(j) a[%d] = %d)\n", i,a[i], j, a[j]);
//		printf("w : %d", w);
//		printf("a[i] : "); shownomber(a[i]);
//		printf("a[j] : "); shownomber(a[j]);
//		exch(a[i], a[j]);
//		if ((digit(a[i], w)) == v) { p++; exch(a[p], a[i]); printf("a[p] : %d\n", a[p]); }
//		if ((digit(a[j], w)) == v) { q--; exch(a[q], a[j]); printf("a[q] : %d\n", a[q]); }
//	}
//	if (p == q) {
//		printf("p == q\n");
//		if (w < bitsword) {
//			printf("再帰実行p == q\n");
//			quicksortX(a, l, r, w + 1);
//		}
//		return;
//	}
//	if ((digit(a[i], w)) < v)i++;
//	for (k = l; k <= p; k++, j--) {
//		printf("exch(a[k] : %d, a[j] : %d)\n", a[k], a[j]);
//		exch(a[k], a[j]);
//	}
//	for (k = r; k >= q; k--, i++) {
//		printf("exch(a[k] : %d, a[i] : %d)\n", a[k], a[i]);
//		exch(a[k], a[i]);
//	}
//	printf("再帰実行#2\n");
//	quicksortX(a, l, j, w);
//	if ((i == r) && ((digit(a[i], w)) == v))i++;
//	quicksortX(a, i + 1, i - 1, w + 1);
//	quicksortX(a, i, r, w);
//}
//
////なぜ動かない？
////void quicksortX(Item* a, int l, int r, int w) {
////	int i, j, p, q, k;
////	Item v = (digit(a[r], w));
////
////	i = p = l - 1; j = q = r;
////
////	if ((r - l) < M) {
////		printf("insertion\n");
////		insertion(a, l, r);
////	}
////
////	for (;;) {
////		while ((digit(a[++i], w)) < v) {
////			printf("w : %d, a[i](%d) : ",w, a[i]); shownomber(a[i]);
////		}
////		while ((digit(a[--j], w)) > v) {
////			printf("w : %d, a[j](%d) : ",w,  a[j]); shownomber(a[j]);
////			if (a[j] == l)break;
////		}
////		if (j <= i)break;
////		printf("exch\n");
////		exch(a[i], a[j]);
////		if (a[i] == v) { p++; exch(a[p], a[i]); }
////		if (a[j] == v) { q--; exch(a[q], a[j]); }
////	}
////	exch(a[i], a[r]);
////	for (k = r - 1, j = i + 1; k >= q; k--, j++)exch(a[j], a[k]);
////	for (k = l, i = i - 1; k <= p; k++, i--)exch(a[i], a[k]);
////	quicksortX(a, l, i, w);
////	//if (((digit(a[i], w)) == v) && (i == r))i++;
////	quicksortX(a, i + 1, j - 1, w + 1);
////	quicksortX(a, j, r, w);
////}
//
//
//void shownomber(int a)
//{
//	int i;
//	
//	for (i = 16; i < bitsword; i++) {
//		printf("%2d", digit(a, i));
//	}
//	putchar('\n');
//}
//
//void batchersort(Item* a, int l, int r)
//{
//	int i, j, k, p, Num = r - l + 1;
//
//	for (p = 1; p < Num; p += p)
//		for (k = p; k > 0; k /= 2)
//			for (j = k % p; j + k < Num; j += (k + k))
//				for (i = 0; i < k; i++)
//					if (j + i + k < Num)
//						if ((i + j) / (p + p) == (i + j + k) / (p + p))
//							if (!(a[l + j + i] < a[l + j + i + k]))exch(a[l + j + i], a[l + j + i + k]);
//}
//
//static Item* st;
//
//void ArrayInit(int maxN) // maxN個の要素を持つ配列を作る
//{
//	st = malloc(maxN * sizeof(Item));
//	N = 0;
//}
//
//int ArrayCount()//要素数を返す
//{
//	return N;
//}
//
//void ArrayInsert(Item item)//要素の挿入
//{
//	int j = N++;
//	Item v = item;
//	
//	while ((j > 0) && (v < st[j - 1])) {
//		st[j] = st[j - 1];
//		j--;
//	}
//	st[j] = v;
//}
//
//Item ArraySearch(Item item) //求める要素が含まれているか調べる
//{
//	int j, flag;
//	Item v = item;
//
//	st[N] = v; // 配列の最後に番兵
//	for (j = 0;; j++) {
//		if (st[j] == v) {
//			flag = 1;
//			break;
//		}
//		if (v < st[j]) {
//			flag = 0;
//			break;
//		}
//	}
//	if ((j == N) || (!flag))return 0;
//	return st[j];
//}
//
//void printst(Item item) {
//	printf("%d\n", item);
//	return;
//}
//
//Item ArraySelect(int k)//st[k]を返す	
//{
//	return st[k];
//}
//
//void ArraySort(void (*visit)(Item)) // 与えられた配列を並び替える
//{
//	int i;
//	for (i = 0; i < N; i++) visit(st[i]);
//}
//
//List SThead;
////
////void ListInit(int max)
////{
////	SThead.next = NULL;
////	N = 0;
////}
////
////int ListCount()
////{
////	return N;
////}
////
////void ListInsert(Item v)
////{
////	int i;
////	List* t = malloc(sizeof(List)), * s = malloc(sizeof(List));
////	t->item = v;
////	if (SThead.next == NULL) {
////		t->next = NULL;
////		SThead.next = t;
////		return;
////	}
////	for (s = SThead.next; s != NULL; s = s->next) {
////		t->next = s->next;
////		s->next = t;
////	}
////	N++;
////}
////
////Item ListSearch(List* t, Item v)
////{
////	int i, j;
////	List* tmp;
////	for (tmp = SThead.next; tmp != NULL; tmp = tmp->next) {
////		if (v == tmp->item) return(tmp->item);
////	}
////	return (0);
////}
////
////Item ListSelect(int k)
////{
////	int i;
////	List* t;
////
////
////
////	for (i = 0, t = SThead.next; (i < k) && (t != NULL); i++, t = t->next);
////	if (t == NULL)return 0;
////	
////	return (t->item);
////	
////}
////
////void printList()
////{
////	List* t;
////	for (t = SThead.next; t != NULL; t = t->next) {
////		printf("%d\n", t->item);
////	}
////}
//
//void PfixUP(int* a, int k)
//{
//	int i = k;
//	while (a[i / 2] < a[i]) {
//		if (i <= 1)break;
//		exch(a[i / 2], a[i]);
//		i /= 2;
//	}
//}
//
//void PfixDown(int* a,int k, int N)
//{
//	int i, j;
//	
//	i = k;
//	while (a[i] < a[i * 2]) {
//		j = i * 2;
//		if (j > N)break;
//		if (j + 1 <= N) {
//			if (a[j] < a[j + 1])j++;
//		}
//		exch(a[i], a[j]);
//		i = j;
//	}
//}
//
//void Pheap(int* a, int l, int r)
//{
//	int i, j, Num = r - l + 1;
//	int* temp = a + l - 1;
//	
//	for (i = Num / 2; i >= 1; i--) {
//		fixdown(temp, i, Num);
//	}
//
//	j = 0;
//	for (i = Num; i >= 2; i--) {
//		exch(temp[1], temp[i]);
//		//a[r - j] = temp[i];
//		fixup(temp, 1, i - 1);
//	}
//	//a[l] = temp[1];
//
//	
//}
//
//Item* st;
//int stnum;
//int stmax;
//
//void STinit(int maxN) // maxN個の要素を持つsymble tableを作る
//{
//	st = malloc(maxN * sizeof(Item));
//	stnum = 0;
//	stmax = maxN;
//}
//int STcount() // symble table内の要素数を返す
//{
//	return (stnum);
//}
//void STinsert(Item item) // symble tableに要素を挿入
//{
//	if (stnum == stmax) {
//		printf("tableは一杯です\n");
//		return;
//	}
//	st[stnum++] = item; 
//}
//Item BBseach(Item item); // symble tableにitemがあるかどうか二分探索で探す
//void STprint(); // symble tableの中身を表示