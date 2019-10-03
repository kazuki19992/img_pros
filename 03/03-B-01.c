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
        printf("header[%d] = %02x ", i, header[i]);
    }
    putchar('\n');

    printf("\n<ファイルサイズ>\n");
    for(i = 2; i < 6; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    printf("\n%dバイト\n", *(int *)&header[2]);
    
    printf("\n<予約領域>\n");
    for(i = 6; i < 10; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    putchar('\n');

    printf("\n<オフセット>\n");
    for(i = 10; i < 13; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    printf("\n%dバイト\n", *(int *)&header[10]);

    printf("\n<情報ヘッダサイズ>\n");
    for(i = 14; i < 18; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    putchar('\n');

    printf("\n<画像の幅>\n");
    for(i = 18; i < 22; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    printf("\n%d画素\n", *(int *)&header[18]);

    printf("\n<画像の高さ>\n");
    for(i = 22; i < 26; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    printf("\n%dライン\n", *(int *)&header[22]);

    printf("\n<色プレーン数>\n");
    for(i = 26; i < 28; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    putchar('\n');
    
    printf("\n<1画素あたりのビット数>\n");
    for(i = 28; i < 30; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    printf("\n%dビット\n", *(int *)&header[28]);
    
    printf("\n<圧縮方式>\n");
    for(i = 30; i < 34; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    putchar('\n');
    
    printf("\n<画像データサイズ>\n");
    for(i = 34; i < 38; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    putchar('\n');
    
    printf("\n<水平解像度>\n");
    for(i = 38; i < 42; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    putchar('\n');
    
    printf("\n<垂直解像度>\n");
    for(i = 42; i < 46; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    putchar('\n');
    
    printf("\n<色数>\n");
    for(i = 46; i < 50; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    putchar('\n');
    
    printf("\n<重要な色数>\n");
    for(i = 50; i < 54; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    putchar('\n');
    
    printf("\n<挿入ビット数>\n");
    printf("2バイト\n");
    
    // ファイルクローズ
    fclose(fp); 
}
