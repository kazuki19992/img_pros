// 画像情報処理(コピー)
// 2019/09/20
// 櫛田一樹
#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *fp;
    int c, i, num = 0, count = 0;
    unsigned char array[100];

    // ファイルオープン
    fp = fopen("test.bmp","rb");

    if(fp == NULL){
        printf("ファイルをオープンできませんでした\n");
        exit(1);
    }

    printf("読み込み用ファイルをオープンしました.\n");

    // ファイルから1バイトずつ読み込む
    c = getc(fp);
    while(c != EOF){
        array[num] = c;
        c = fgetc(fp);
        count++;
        num++;
    }

    // ファイルクローズ
    fclose(fp);

    printf("%d個のデータを読み込み,配列に格納しました.\n",count);
    printf("読み込み用ファイルをクローズしました.\n");
    putchar('\n');

    // 配列の中身を表示
    printf("配列の中身を表示します\n");
    for(i = 0; i < num; i++){
        printf("array[%d] = %d\n", i, array[i]);
    }
    putchar('\n');

    // 書き出し用fopen
    fp = fopen("testcp.bmp", "wb");

    if(fp == NULL){
        printf("ファイルをオープンできません.\n");
        exit(1);
    }

    printf("書き出し用ファイルをオープンしました.\n");

    // ファイルに書き出し
    for(i = 0; i < num; i++){
        fputc(array[i], fp);
    }

    // ファイルクローズ
    fclose(fp);
    printf("配列に格納されていた%d個のデータを書き出しました.\n", num);
    printf("書き出し用ファイルをクローズしました.\n");

    return 0;
}