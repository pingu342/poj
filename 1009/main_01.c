// RLE (Run Length Encoding, 連長圧縮) で圧縮された入力画像を読み込み、画像に対してエッジ検出を行い、その結果をRLEで圧縮して出力する
// 入力画像のピクセル数は2〜10^9個である
// RLEで圧縮された画像は、ピクセル値(0-255)とその連長のペアの配列から成る
// このペア数は入力画像では多くても1000ペアであるが、出力では1000ペアを超える場合がある
//
// ---
// 入力画像(幅7)の例
//
//      15  15  15  15 100 100 100 <-画像の1行目
//     100 100 100 100 100 100 100 <-画像の2行目
//
// 上記の入力画像がRLEで圧縮されたものがプログラムへの入力となる
//
//       7
//       15 4
//       100 10
//
// これを効率よく処理するために仮想的な行を加える
// 
//       7
//       -1 8   <- 仮想的な行
//       15 4
//       100 10
//       -1 8   <- 仮想的な行
//
//  -1  -1  -1  -1  -1  -1  -1  -1    <-仮想的な行
//      15  15  15  15 100 100 100    <-画像の1行目
//     100 100 100 100 100 100 100    <-画像の2行目
//      -1  -1  -1  -1  -1  -1  -1 -1 <-仮想的な行
// 
// このRLEで圧縮された入力画像のRLEペア(値,連長)を1002個保存するメモリを確保し、仮想的な行も含めた全てをメモリにロードする
//
// デコーダを3つ用意する
// ここで、画像の幅が7、画像の1行目の先頭をピクセル0とする
// 各デコーダの初期デコード位置を以下のピクセルにセットする
// 
//    デコーダ1 : ピクセル-8
//    デコーダ2 : ピクセル-1
//    デコーダ3 : ピクセル6
//
// 初回のデコードは初期デコード位置から3ピクセルをデコードし、結果を配列であるin[9]に保持する
//
//    デコーダ1 : ピクセル-8,-7,-6をデコードし、結果をin[0]~in[2]に保存
//    デコーダ2 : ピクセル-1,0,1をデコードし、結果をin[3]~in[5]に保存
//    デコーダ3 : ピクセル6,7,8をデコードし、結果をin[6]~in[8]に保存
//
// ピクセル0(すなわちin[4])の周りのピクセルとの差分の最大を求めることで、ピクセル0に対するエッジ検出の結果が得られる
//
// 次のピクセル1に対するエッジ検出の結果を得るには、以下のとおり配列の要素コピー及び各デコーダで1ピクセルのデコードを行い、ピクセル0(すなわちin[4])の周りのピクセルとの差分の最大を求めればよい
//
//    in[0]<-in[1], in[1]<-in[2], in[2]<-デコーダ1のピクセル-5のデコード結果
//    in[3]<-in[4], in[4]<-in[5], in[5]<-デコーダ2のピクセル2のデコード結果
//    in[6]<-in[7], in[7]<-in[8], in[8]<-デコーダ3のピクセル9のデコード結果
//
// 次のピクセル2に対してエッジ検出を行う際、もし以下の条件が全て真なら、そのエッジ検出の結果は、1つ前のピクセル1に対するエッジ検出の結果と同じになるので、配列の要素コピーやデコードの処理を省略できる
//
//    ・ピクセル0に対するエッジ検出が終了した時点でのin[0],in[1],in[2]の値と、ピクセル-4のデコード結果が全て等しい
//    ・ピクセル0に対するエッジ検出が終了した時点でのin[3],in[4],in[6]の値と、ピクセル3のデコード結果が全て等しい
//    ・ピクセル0に対するエッジ検出が終了した時点でのin[6],in[7],in[8]の値と、ピクセル10のデコード結果が全て等しい
//
//
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int val, len; //値,連長
} RLE;

typedef struct {
	RLE *rle; int len, cnt; //現在デコード中のRLEペア(値,連長), 未デコードの連長, デコード済の連長
} RLE_DEC;

int w, n; //画像の幅、総ピクセル数

//ピクセルaとその周囲8ピクセルe0〜e7との差分の最大値を求める
int edge(int e0, int e1, int e2, int e3, int e4, int e5, int e6, int e7, int a)
{
	int i, e[8], d, max=0;
	e[0]=e0;
	e[1]=e1;
	e[2]=e2;
	e[3]=e3;
	e[4]=e4;
	e[5]=e5;
	e[6]=e6;
	e[7]=e7;
	for (i=0; i<8; i++) {
		if (e[i]<0) {
			continue;
		} else {
			d = (e[i]-a);
			if (d < 0) d*=-1;
			if (d > max) max = d;
		}
	}
	return max;
}

int advance_dec(RLE_DEC *dec, int i)
{
	int val = dec->rle->val;
	int tmp;
	dec->len -= i;
	dec->cnt += i;
	while ((tmp = dec->len) <= 0) {
		dec->rle++;
		dec->len = dec->rle->len + tmp;
		dec->cnt = tmp * -1;
	}
	return val;
}

void ini_dec(RLE_DEC *dec, RLE *rle, int i)
{
	dec->rle = rle;
	dec->len = rle->len;
	dec->cnt = 0;
	advance_dec(dec, i);
}

int main()
{
	int i, j, in[9], out, skip;
	RLE *top = malloc(sizeof(RLE)*1002), *cur, enc;
	RLE_DEC dec[3];
	while (scanf("%d",&w), w) {
		printf("%d\n", w);
		top->val = -1;
		top->len = w+1;
		for (cur=top+1,n=0;scanf("%d %d",&cur->val,&cur->len),cur->len;cur++)
			n += cur->len;
		cur->val = -1;
		cur->len = w+1;
		ini_dec(&dec[0], top, 0);
		ini_dec(&dec[1], top, w);
		ini_dec(&dec[2], top, 2*w);
		enc.val = enc.len = -1;
		for (i=0;i<n;i++) {
			skip = 0;
			for (j=0;j<9;j++)
				if (i==0 || j%3==2)
					in[j] = advance_dec(&dec[j/3], 1);
				else
					in[j] = in[j+1];
			if (w>=2) {
				if (i%w==0)
					out = edge(   -1,in[1],in[2],   -1,in[5],   -1,in[7],in[8],in[4]);
				else if (i%w==w-1)
					out = edge(in[0],in[1],   -1,in[3],   -1,in[6],in[7],   -1,in[4]);
				else
					out = edge(in[0],in[1],in[2],in[3],in[5],in[6],in[7],in[8],in[4]);
			} else {
				out = edge(-1,in[1],-1,-1,-1,-1,in[7],-1,in[4]);
			}
skip_decomp_edge:
			if (enc.val!=out) {
				if (enc.val >= 0)
					printf("%d %d\n", enc.val, enc.len);
				enc.val = out;
				enc.len = 1;
			} else {
				if (skip)
					enc.len += skip;
				else
					enc.len++;
			}
			if (dec[0].cnt>=3 && dec[1].cnt>=3 && dec[2].cnt>=3)
				skip = ((dec[0].len < dec[1].len) \
					    ? ((dec[0].len < dec[2].len) ? dec[0].len : dec[2].len) \
					    : ((dec[1].len < dec[2].len) ? dec[1].len : dec[2].len)) - 1;
			if (skip > 0) {
				for (j=0;j<3;j++) {
					dec[j].len -= skip;
					dec[j].cnt += skip;
				}
				i += skip;
				goto skip_decomp_edge;
			}
		}
		printf("%d %d\n0 0\n", enc.val, enc.len);
	}
	printf("0\n");
}
