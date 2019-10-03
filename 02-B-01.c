// 画像情報処理
// 2019/09/27
// 櫛田一樹
#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *fp;
    int i, num = 0, val = 0;
    char fname[20];

    // ファイル名の入力
    printf("ファイル名を入力して下さい：");
    scanf("%s", fname);

    // ファイルオープン
    fp = fopen(fname, "wb");

    if(fp == NULL){
        printf("ファイルをオープンできません.\n");
        exit(1);
    }

    printf("ファイルをオープンしました.\n");

    // ファイルの書き出し設定
    printf("何バイト書き出しますか:");
    scanf("%d",&num);
    printf("\n");

    // ファイルに書き出し
    printf("0以上255以下の値を%d個入力してください.\n", num);
    for(i = 0; i < num; i++){
        printf("No.%d:", i+1);
        scanf("%d", &val);
        fputc(val, fp);
    }

    // ファイルクローズ
    fclose(fp);
    printf("ファイルをクローズしました.\n");

    return 0;
}
