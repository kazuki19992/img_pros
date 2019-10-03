// 画像情報処理(コピー)
// 2019/09/27
// 櫛田一樹
#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *fp;
    int c, i, num = 0, count = 0;
    unsigned char array[100];
    char fname_b[20], fname_a[20];  // before, after

    // コピー元ファイル名の入力
    printf("コピー元のファイル名を入力して下さい：");
    scanf("%s", fname_b);

    // コピー先のファイル名の入力
    printf("コピー先のファイル名を入力して下さい：");
    scanf("%s", fname_a);


    // ファイルオープン
    fp = fopen(fname_b, "rb");

    if(fp == NULL){
        printf("ファイルをオープンできませんでした\n");
        exit(1);
    }

    printf("%sをオープンしました.\n", fname_b);

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

    printf("%sから%d個のデータを読み込み,配列に格納しました.\n", fname_b, count);
    printf("%sをクローズしました.\n", fname_b);
    putchar('\n');

    // 配列の中身を表示
    printf("配列の内容を表示します\n");
    for(i = 0; i < num; i++){
        printf("array[%d] = %d\n", i, array[i]);
    }
    putchar('\n');

    // 書き出し用fopen
    fp = fopen(fname_a, "wb");

    // if(fp == NULL){
    //     printf("ファイルをオープンできません.\n");
    //     exit(1);
    // }

    printf("%sをオープンしました.\n", fname_a);

    // ファイルに書き出し
    for(i = 0; i < num; i++){
        fputc(array[i], fp);
    }

    // ファイルクローズ
    fclose(fp);
    printf("配列から%d個のデータを%s書き出しました.\n", num, fname_a);
    printf("%sをクローズしました.\n", fname_a);

    return 0;
}

