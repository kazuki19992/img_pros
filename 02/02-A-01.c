// 画像情報処理
// ファイルアクセス
// 2019/09/20 13:55

#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *fp;
    int c = 0, byt_cnt = 0;
    
    char fname[20];

    // ファイル名の入力
    printf("ファイル名を入力して下さい：");
    scanf("%s", fname);

    fp = fopen(fname, "rb");
    
    // ファイルが存在するか確認
    if(fp == NULL){
        printf("ファイルをオープンできません。\n");
        exit(1);
    }

    printf("ファイルをオープンしました。\n");


    // ファイルから1バイトずつ読み込み
    c = fgetc(fp);

    while(c != EOF){
        printf("%3d\n",c);
        byt_cnt++;
        c = fgetc(fp);
    }

    // ファイルクローズ
    fclose(fp);

    printf("全部で%dバイト読み込みました\n", byt_cnt);
    printf("ファイルをクローズしました\n");

    return 0;
}
