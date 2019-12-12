// 画像処理演習(ファイル読み込み/情報表示)
// u306065 櫛田一樹
// 2019/10/03 13:00

#include<stdio.h>
#include<stdlib.h>

unsigned char header[54];

void get_data(void);

int main(){
    get_data();
    return 0;
}

void get_data(void){
    char fname[20], data;
    FILE *fp;
    int i;

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

    // ヘッダー情報の取得
    data = getc(fp);
    for(int cnt = 0; cnt < 54; cnt++){
        header[cnt] = data;
        data = fgetc(fp);
    }

    printf("\n<ファイルタイプ>\n");

    for(i = 0; i < 2; i++){
        printf("header[%d] = %2x ", i, header[i]);
    }
    putchar('\n');

    printf("\n<ファイルサイズ>\n");
    for(i = 2; i < 6; i++){
        
        printf("header[%d] = %2x ", i, header[i]);

    }
    printf("\nfilesize = %dバイト\n", *(int *)&header[2]);
    // ファイルクローズ
    fclose(fp); 
}
