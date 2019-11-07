#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 100
int size,width,height;
unsigned char header[54];
unsigned char img[3][512][512];
void get_data();
void processing();
int main(void)
{
    get_data();
    processing();
    return (0);
}
void get_data(){
    FILE *fp;
    int filesize=0,offset=0,bits=0;
    int i,j,k;
    char filename[MAX];
    printf("ファイル名を入力:");
    scanf("%s",filename);
    fp=fopen(filename,"rb");
    if(fp==NULL)
    {
        printf("ファイルをオープンできません\n");
        exit (1);
    }
    printf("ファイルをオープンしました\n");

    for(i=0;i<54;i++){
        header[i]=fgetc(fp);
    }
    printf("<ファイルタイプ>\n");
    printf("header[0]=%02x\n",header[0]);
    printf("header[1]=%02x\n",header[1]);
    printf("<ファイルサイズ>\n");
    for(i=2;i<=5;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    filesize=header[5]*pow(2,24)+header[4]*pow(2,16)+header[3]*pow(2,8)+header[2]*pow(2,0);
    printf("%dバイト\n",filesize);
    printf("<予約領域>\n");
    for(i=6;i<=9;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    printf("<オフセット>\n");
    for(i=10;i<=13;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    offset=header[13]*pow(2,24)+header[12]*pow(2,16)+header[11]*pow(2,8)+header[10]*pow(2,0);
    printf("\n");
    printf("%dバイト\n",offset);
    printf("<情報ヘッダサイズ>\n");
    for(i=14;i<=17;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    printf("<画像の幅>\n");
    for(i=18;i<=21;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    width=header[21]*pow(2,24)+header[20]*pow(2,16)+header[19]*pow(2,8)+header[18]*pow(2,0);
    printf("%d画素\n",width);

    printf("<画像の高さ>\n");
    for(i=22;i<=25;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    height=header[25]*pow(2,24)+header[24]*pow(2,16)+header[23]*pow(2,8)+header[22]*pow(2,0);
    printf("%dライン\n",height);
    printf("<色プレーン数>\n");
    for(i=26;i<=27;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    size=header[27]*pow(2,8)+header[26]*pow(2,0);
    printf("<１画素当たりのビット数>\n");
    for(i=28;i<=29;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    bits=header[29]*pow(2,8)+header[28]*pow(2,0);
    printf("%dビット\n",bits);
    printf("<圧縮方式>\n");
    for(i=30;i<=33;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    printf("<画像データサイズ>\n");
    for(i=34;i<=37;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    printf("<水平解像度>\n");
    for(i=38;i<=41;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    printf("<垂直解像度>\n");
    for(i=42;i<=45;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    printf("<色数>\n");
    for(i=46;i<=49;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    printf("<重要な色数>\n");
    for(i=50;i<=53;i++){
        printf("header[%d]=%02x ",i,header[i]);
    }
    printf("\n");
    size=filesize-offset-width*height*(bits/8);

    printf("<挿入ビット数>\n");
    printf("%dバイト\n",size);

    for(i=height-1;i>=0;i--){
        for(j=0;j<width;j++){
            for(k=2;k>=0;k--){
                img[k][i][j]=fgetc(fp);
            }
        }
    }
    fclose(fp);

    printf("ファイルをクローズしました\n");
}

void processing(void){
    int i,j;
    printf("入力画像データを表示します");
    printf("\n<R信号>\n");
    for(j=0;j<height;j++){
        for(i=0;i<width;i++){
            printf("%02x ",img[0][j][i]);
        }
        printf("\n");
    }
    printf("<G信号>\n");
    for(j=0;j<height;j++){
        for(i=0;i<width;i++){
            printf("%02x ",img[1][j][i]);
        }
        printf("\n");
    }
    printf("<B信号>\n");
    for(j=0;j<height;j++){
        for(i=0;i<width;i++){
            printf("%02x ",img[2][j][i]);
        }
        printf("\n");
    }
}
