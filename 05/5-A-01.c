// 画像処理 色空間変換
// 2019/11/08 13:17
// u306065 櫛田 一樹

#include<stdio.h>

int main(){
    double rgbio[3] = {0};
    double ycbcr[3][3] = {{ 0.2990, 0.5870, 0.1140},
                          { -0.1687, -0.3313, 0.5000},
                          { 0.5000, -0.4187, -0.0813}};

    double rgb[3][3] = {{ 1.0000, 0.0000, 1.4020},
                        { 1.0000, -0.3441, -0.7141},
                        { 1.0000, 1.7720, 0.0000}};
    double ycbcr_cnv[3] = {0};

    printf("信号値を入力して下さい(実数値)\n");
    printf(" R  : ");
    scanf("%lf",&rgbio[0]);
    printf(" G  : ");
    scanf("%lf",&rgbio[1]);
    printf(" B  : ");
    scanf("%lf",&rgbio[2]);

    // 入力値出力
    printf("<入力されたRGB信号(実数値)>\n");
    printf(" R  : %9.4lf\n",rgbio[0]);
    printf(" G  : %9.4lf\n",rgbio[1]);
    printf(" B  : %9.4lf\n",rgbio[2]);

    // 変換
    printf("<変換されたYCbCr信号(実数値)>\n");
    for(int i = 0; i < 3; i++){
        
        for(int j = 0; j < 3; j++){
            ycbcr_cnv[i] += ycbcr[i][j] * rgbio[j];
        }
        
        switch(i){
            case 0:{
                printf(" Y  : %9.4lf\n",ycbcr_cnv[i]);
                break;
            }
            case 1:{
                printf(" Cb : %9.4lf\n",ycbcr_cnv[i]);
                break;
            }
            case 2:{
                printf(" Cr : %9.4lf\n",ycbcr_cnv[i]);
                break;
            }
        }
    }


    // RGB変換
    printf("<変換されたRGB信号(実数値)>\n");
    for(int i = 0; i < 3; i++){
        
        for(int j = 0; j < 3; j++){
            rgbio[i] += rgb[i][j] * ycbcr_cnv[j];
        }
        
        switch(i){
            case 0:{
                printf(" R  : %9.4lf\n",rgbio[i]);
                break;
            }
            case 1:{
                printf(" G  : %9.4lf\n",rgbio[i]);
                break;
            }
            case 2:{
                printf(" B  : %9.4lf\n",rgbio[i]);
                break;
            }
        }
    }
    
    return 0;
}
