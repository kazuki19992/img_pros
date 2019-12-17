// 画像処理 量子化
// 2019/11/29 13:44
// u306065 櫛田 一樹

#include<stdio.h>
#include<stdlib.h>

const double ycbcr[3][3] = {{ 0.2990, 0.5870, 0.1140},
                        { -0.1687, -0.3313, 0.5000},
                        { 0.5000, -0.4187, -0.0813}};
const double rgb[3][3] = {{ 1.0000, 0.0000, 1.4020},
                        { 1.0000, -0.3441, -0.7141},
                        { 1.0000, 1.7720, 0.0000}};

double ycbcr_cnv[3][512][512] = {}, do_ycbcr_cnv[3] = {}, rgbio[3] = {}, rgb_cnv[3][512][512] = {};
int int_ycbcr_cnv[3] = {}, int_rgbio[3] = {}, width, height, ins;

unsigned char header[54];
unsigned char imgin[3][512][512], imgout[3][512][512];

void rgb_to_ybr();
void ybr_to_rgb();
void get_data();
void put_data();
void processing();


int main(){
    get_data();
    rgb_to_ybr();
    processing();
    ybr_to_rgb();
    put_data();
    return 0;
}

void get_data(){
    char fname[20];
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
    for(int cnt = 0; cnt < 54; cnt++){
        header[cnt] = fgetc(fp);
    }


    // printf("\n<ファイルタイプ>\n");
    // for(i = 0; i < 2; i++){
    //     printf("header[%d] = %02x ", i, header[i]);
    // }
    // putchar('\n');

    printf("\n<ファイルサイズ>\n");
    for(i = 2; i < 6; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    int filesize = *(int *)&header[2];
    printf("\n%dバイト\n", filesize);
    
    // printf("\n<予約領域>\n");
    // for(i = 6; i < 10; i++){
    //     printf("header[%d] = %02x ", i, header[i]);
    // }
    // putchar('\n');

    printf("\n<オフセット>\n");
    for(i = 10; i < 13; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    int offset = *(int *)&header[10];
    printf("\n%dバイト\n", offset);

    // printf("\n<情報ヘッダサイズ>\n");
    // for(i = 14; i < 18; i++){
    //     printf("header[%d] = %02x ", i, header[i]);
    // }
    // putchar('\n');

    printf("\n<画像の幅>\n");
    for(i = 18; i < 22; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    width = *(int *)&header[18];
    printf("\n%d画素\n", width);

    printf("\n<画像の高さ>\n");
    for(i = 22; i < 26; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    height = *(int *)&header[22];
    printf("\n%dライン\n", height);

    // printf("\n<色プレーン数>\n");
    // for(i = 26; i < 28; i++){
    //     printf("header[%d] = %02x ", i, header[i]);
    // }
    // putchar('\n');
    
    printf("\n<1画素あたりのビット数>\n");
    for(i = 28; i < 30; i++){
        printf("header[%d] = %02x ", i, header[i]);
    }
    int bit = *(int *)&header[28];
    printf("\n%oビット\n", *(short *)&header[28]);
    
    // printf("\n<圧縮方式>\n");
    // for(i = 30; i < 34; i++){
    //     printf("header[%d] = %02x ", i, header[i]);
    // }
    // putchar('\n');
    
    // printf("\n<画像データサイズ>\n");
    // for(i = 34; i < 38; i++){
    //     printf("header[%d] = %02x ", i, header[i]);
    // }
    // putchar('\n');
    
    // printf("\n<水平解像度>\n");
    // for(i = 38; i < 42; i++){
    //     printf("header[%d] = %02x ", i, header[i]);
    // }
    // putchar('\n');
    
    // printf("\n<垂直解像度>\n");
    // for(i = 42; i < 46; i++){
    //     printf("header[%d] = %02x ", i, header[i]);
    // }
    // putchar('\n');
    
    // printf("\n<色数>\n");
    // for(i = 46; i < 50; i++){
    //     printf("header[%d] = %02x ", i, header[i]);
    // }
    // putchar('\n');
    
    // printf("\n<重要な色数>\n");
    // for(i = 50; i < 54; i++){
    //     printf("header[%d] = %02x ", i, header[i]);
    // }
    // putchar('\n');
    
    printf("\n<挿入ビット数>\n");
    ins = filesize - offset - width * height * (bit / 8);
    printf("%dバイト\n\n", ins);


    for(i = height - 1; i >= 0; i--){
        for(int j = 0; j < width; j++){
            for(int k = 2; k >= 0; k--){
                imgin[k][i][j] = fgetc(fp);
            }
        }
    }

    // ファイルクローズ
    fclose(fp); 
}

void rgb_to_ybr(){
    // 入力値出力
    // printf("<入力信号(RGB)>\n");
    // printf("---R---\n");
    // for(int i = 0; i < height; i++){
    //     for(int j = 0; j < width; j++){
    //         printf("%.2X ",imgin[0][i][j]);
    //     }
    //     putchar('\n');
    // }
    // printf("---G---\n");
    // for(int i = 0; i < height; i++){
    //     for(int j = 0; j < width; j++){
    //         printf("%.2X ",imgin[1][i][j]);
    //     }
    //     putchar('\n');
    // }
    // printf("---B---\n");
    // for(int i = 0; i < height; i++){
    //     for(int j = 0; j < width; j++){
    //         printf("%.2X ",imgin[2][i][j]);
    //     }
    //     putchar('\n');
    // }
    
    // YCbCrへの変換(整数)
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            for(int k = 0; k < 3; k++){
                ycbcr_cnv[0][i][j] += ycbcr[0][k] * imgin[k][i][j];
                ycbcr_cnv[1][i][j] += ycbcr[1][k] * imgin[k][i][j];
                ycbcr_cnv[2][i][j] += ycbcr[2][k] * imgin[k][i][j];
            }
        }
    }

    // 四捨五入
    for(int k = 0; k < 3; k++){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                if(ycbcr_cnv[k][i][j] >= 0){
                    ycbcr_cnv[k][i][j] += 0.5;
                    ycbcr_cnv[k][i][j] = (int)ycbcr_cnv[k][i][j];
                }else if(ycbcr_cnv[k][i][j] < 0){
                    ycbcr_cnv[k][i][j] -= 0.5;
                    ycbcr_cnv[k][i][j] = (int)ycbcr_cnv[k][i][j];
                }
            }
        }
    }

    // CbとCrにオフセット加算
    for(int k = 1; k < 3; k++){
        for(int i = 0; i < height; i++){
            for(int j = 0 ; j < width; j++){
                ycbcr_cnv[k][i][j] += 128;
            }
        }
    }

    // 1バイト外数値時修正処理
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < width; k++){
                if(ycbcr_cnv[i][j][k] >= 255){
                    ycbcr_cnv[i][j][k] = 255;
                }else if(ycbcr_cnv[i][j][k] <= 0){
                    ycbcr_cnv[i][j][k] = 0;
                }
            }
        }
    }

    // imginへの上書き処理
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < width; k++){
                imgin[i][j][k] = (int)ycbcr_cnv[i][j][k];
            }
        }
    }
    
    // 出力
    // printf("<入力信号(YCbCr)>\n");
    // for(int i = 0; i < 3; i++){
    //     switch(i){
    //         case 0:{
    //             printf("--- Y ---\n");
    //             break;
    //         }
    //         case 1:{
    //             printf("--- Cb ---\n");
    //             break;
    //         }
    //         case 2:{
    //             printf("--- Cr ---\n");
    //             break;
    //         }
    //     }
    //     for(int j = 0; j < height; j++){
    //         for(int k = 0; k < width; k++){
    //             printf("%.2X ",imgin[i][j][k]);
    //         }
    //         putchar('\n');
    //     }
    // }
    putchar('\n');
}

void processing(){
    // 明度レベルカウンタ
    double brightness[256] = {0};
    double bright_conv[256] = {0};
    int max[2] = {0};

    for(int i = 0; i < 3; i++){
        // コピーを行う
        for(int j = 0; j < height; j++){
            for(int k = 0; k < width; k++){
               
                if(i == 0){

                    // 明度レベル毎のカウントを行う
                    for(int l = 0; l < 256; l++){
                        // 明度カウント処理
                        if(imgin[i][j][k] == l){
                            brightness[l]++;
                        }
                    }
                }

                // 画像コピーを行う
                imgout[i][j][k] = imgin[i][j][k];
            }
        }
    }

    // 最大度数算出
    for(int i = 0; i < 256; i++){
        if(brightness[i] > max[0]){
            // 最大度数と添字を格納
            max[0] = brightness[i];     // 最大度数
            max[1] = i;                 // 最大度数の添字
        }
    }

    // 正規化処理
    for(int i = 0; i < 256; i++){
        bright_conv[i] = (brightness[i] / max[0]) * 100;
        
        // 四捨五入
        bright_conv[i] += 0.5;
        bright_conv[i] = (int)bright_conv[i];
    }

    // ヒストグラム描画処理
    for(int j = 0; j < height; j++){
        for(int k = 0; k < width; k++){
            // ヒストグラム範囲設定
            if( j > height - 100 && k < 256){
                
                // グラフ描画
                if( height - j < (int)bright_conv[k]){
                    // グラフ色：赤
                    imgout[0][j][k] = 0x00;
                    imgout[1][j][k] = 0x80;
                    imgout[2][j][k] = 0xff;
                }else{
                    // グラフ背景：黒
                    imgout[0][j][k] = 0x00;
                    imgout[1][j][k] = 0x80;
                    imgout[2][j][k] = 0x80;
                }
            }
        }
    }


    // 出力処理
    printf("＜最大度数＞\n");
    printf("画素値%4d : %5d\n\n",max[1], max[0]);

    printf("＜度数表＞\n");
    for(int i = 0; i < 256; i++){
        printf("画素値%4d : %5.0f --> %4.0f\n", i, brightness[i], bright_conv[i]);
    }
    
}

void ybr_to_rgb(){
    // RGB変換(整数)
    // printf("<出力信号(YCbCr)>\n");
    // printf("--- Y ---\n");
    // for(int i = 0; i < height; i++){
    //     for(int j = 0; j < width; j++){
    //         printf("%.2X ",imgin[0][i][j]);
    //     }
    //     putchar('\n');
    // }
    // printf("--- Cb ---\n");
    // for(int i = 0; i < height; i++){
    //     for(int j = 0; j < width; j++){
    //         printf("%.2X ",imgin[1][i][j]);
    //     }
    //     putchar('\n');
    // }
    // printf("--- Cr ---\n");
    // for(int i = 0; i < height; i++){
    //     for(int j = 0; j < width; j++){
    //         printf("%.2X ",imgin[2][i][j]);
    //     }
    //     putchar('\n');
    // }
    // putchar('\n');


    // オフセット加算値減算
    short tmp[3][512][512] = {};
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < width; k++){
                tmp[i][j][k] = imgout[i][j][k];
            }
        }
    }
    for(int i = 1; i < 3; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < width; k++){
                tmp[i][j][k] = tmp[i][j][k] - 128.0;
            }
        }
    }

    
    // RGB変換
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            for(int k = 0; k < 3; k++){
                rgb_cnv[0][i][j] += rgb[0][k] * tmp[k][i][j];
                rgb_cnv[1][i][j] += rgb[1][k] * tmp[k][i][j];
                rgb_cnv[2][i][j] += rgb[2][k] * tmp[k][i][j];
            }
        }
    }

    // 四捨五入
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < width; k++){
                if(rgb_cnv[i][j][k] >= 0){
                    rgb_cnv[i][j][k] += 0.5;
                }else if(rgb_cnv[i][j][k] < 0){
                    rgb_cnv[i][j][k] -= 0.5;
                }
                rgb_cnv[i][j][k] = (int)rgb_cnv[i][j][k];
            }
        }
    }

    // 1バイト範囲外値修正処理
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < width; k++){
                if(rgb_cnv[i][j][k] > 255){
                    rgb_cnv[i][j][k] = 255;
                }else if(rgb_cnv[i][j][k] < 0){
                    rgb_cnv[i][j][k] = 0;
                }
            }
        }
    }

    // rgb_cnv 2 imgout
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < width; k++){
                imgout[i][j][k] = rgb_cnv[i][j][k];
            }
        }
    }

    // 出力
    // printf("<出力信号(RGB)>\n");
    // for(int i = 0; i < 3; i++){
    //     switch(i){
    //         case 0:{
    //             printf("--- R ---\n");
    //             break;
    //         }
    //         case 1:{
    //             printf("--- G ---\n");
    //             break;
    //         }
    //         case 2:{
    //             printf("--- B ---\n");
    //             break;
    //         }
    //     }
    //     for(int j = 0; j < height; j++){
    //         for(int k = 0; k < width; k++){
    //             printf("%.2X ",imgout[i][j][k]);
    //         }
    //         putchar('\n');
    //     }
    // }
}

void put_data(){
    char n_fname[20];
    FILE *fp;
    printf("出力画像データを作成しました.\n\n");
    printf("ファイル名を入力:");
    scanf("%s",n_fname);
    fp=fopen(n_fname,"wb");
    if(fp==NULL){
        printf("ファイルをオープンできません\n");
        exit (1);
    }
    printf("ファイルをオープンしました\n");
    for(int i = 0; i < 54; i++){
        fputc(header[i],fp);
    }
    for(int i = height - 1; i >= 0; i--){
        for(int j = 0; j < width; j++){
            for(int k = 2; k >= 0; k--){
                fputc(imgout[k][i][j],fp );
            }
        }
    }
    fclose(fp);
    printf("ファイルをクローズしました\n");
}
