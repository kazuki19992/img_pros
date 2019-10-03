// 画像処理演習(ファイル読み込み/情報表示)
// u306065 櫛田一樹
// 2019/10/03 13:00

#include<stdio.h>
unsigned char header[54];

void get_data(void);

int main(){
    get_data();
    return 0;
}

void get_data(void){
    char fname[20];
    FILE *fp;

    // ファイル名の入力
    printf("入力ファイル名を入力してください：");
    scanf("%s",fname);

    // ファイルオープン
    fp = fopen(fname, "rb");

    if(fp == NULL){
        printf("ファイルをオープンできませんでした\n");
        exit(1);
    }

    printf("ファイルをオープンしました.\n");
}