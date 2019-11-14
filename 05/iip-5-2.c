#include<stdio.h>
#include<stdlib.h>
# define N 100
unsigned char header[54];
char c;
int high;
int wide;
int bits;
long offset;
int cp_color[3];
unsigned char imgin[3][512][512];
unsigned char imgout[3][512][512]={};
void get_data();
void rgb_to_ybr();
void processing();
void ybr_to_rgb();
void put_data();

int main(void){
  get_data();
  rgb_to_ybr();
  processing();
  ybr_to_rgb();
  put_data();
  return 0;
}

void get_data(){
  FILE *fp;
  char name[N];
  int i;
  long filesize=0;
  long width=0;
  long height=0;
  long bit=0;
  int x,y,z;
  printf("入力ファイル名を入力して下さい:");
  scanf("%s",name);
  fp=fopen(name,"rb");
  if(fp==NULL){
    printf("ファイルをオープンできません.\n");
    exit(1);
  }

  printf("ファイルをオープンしました.\n");
  for(i=0;i<54;i++){
    header[i]=fgetc(fp);
  }
  printf("\n");
  printf("＜ファイルサイズ＞\n");
  for(;i<6;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  filesize+=header[5];
  filesize=filesize << 8 | (0xFF & header[4]);
  filesize=filesize << 8 | (0xFF & header[3]);
  filesize=filesize << 8 | (0xFF & header[2]);
  printf("\n%ldバイト\n",filesize);
  printf("\n");
  /*printf("＜予約領域＞\n");
  for(;i<10;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  printf("\n");
  printf("\n");*/
  printf("＜オフセット＞\n");
  for(;i<14;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  offset+=header[13];
  offset=offset << 8 | (0xFF & header[12]);
  offset=offset << 8 | (0xFF & header[11]);
  offset=offset << 8 | (0xFF & header[10]);
  printf("\n%ldバイト\n",offset);
  printf("\n");
  /* printf("＜情報ヘッダサイズ＞\n");
  for(;i<18;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  printf("\n");
  printf("\n");*/
  printf("＜画像の幅＞\n");
  for(;i<22;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  width+=header[21];
  width=width << 8 | (0xFF & header[20]);
  width=width << 8 | (0xFF & header[19]);
  width=width << 8 | (0xFF & header[18]);
  printf("\n%ld画素\n",width);
  wide=width;
  printf("\n");
  printf("＜画像の高さ＞\n");
  for(;i<26;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  height+=header[25];
  height=height << 8 | (0xFF & header[24]);
  height=height << 8 | (0xFF & header[23]);
  height=height << 8 | (0xFF & header[22]);
  printf("\n%ldライン\n",height);
  printf("\n");
  high=height;
  /*printf("＜色プレーン数＞\n");
  for(;i<28;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  printf("\n");
  printf("\n");*/
  printf("＜1画素当たりのビット数＞\n");
  for(;i<30;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  bit+=header[29];
  bit=bit << 8 | (0xFF & header[28]);
  printf("\n%ldビット\n",bit);
  printf("\n");
  /*printf("＜圧縮方式＞\n");
  for(;i<34;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  printf("\n");
  printf("\n");
  printf("＜画像データサイズ＞\n");
  for(;i<38;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  printf("\n");
  printf("\n");
  printf("＜水平解像度＞\n");
  for(;i<42;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  printf("\n");
  printf("\n");
  printf("＜垂直解像度＞\n");
  for(;i<46;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  printf("\n");
  printf("\n");
  printf("＜色数＞\n");
  for(;i<50;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  printf("\n");
  printf("\n");
  printf("＜重要な色数＞\n");
  for(;i<54;i++){
    printf("header[%d]=%.2x ",i,header[i]);
  }
  printf("\n");
  printf("\n");*/
  printf("＜挿入ビット数＞\n");
  printf("%ldバイト\n",filesize-offset-width*height*(bit/8));
  printf("\n");
  bits=filesize-offset-width*height*(bit/8);
 
  for(x=height-1;x>=0;x--){
    for(y=0;y<width;y++){
      for(z=2;z>=0;z--){
        imgin[z][y][x]=fgetc(fp);
      }
    }
  }
 
  fclose(fp);
}

void processing(){
  int i;
  int j;
  // printf("入力画像データを表示します.\n");
  // printf("\n");
  //printf("<R 信号>\n");
  printf("\nファイルをクローズしました.\n");
  printf("コピーモードを入力して下さい.\n");
  printf("(コピーする場合:1,固定値に置き換える場合:0)\n");
  printf("Y : ");
  scanf("%d",&cp_color[0]);
  printf("Cb : ");
  scanf("%d",&cp_color[1]);
  printf("Cr : ");
  scanf("%d",&cp_color[2]);

  if(cp_color[0]==1){
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	//printf("%.2x ",imgin[0][j][i]);
	imgout[0][j][i]=imgin[0][j][i];
      }
      //printf("\n");
    }
  }

  if(cp_color[0]==0){
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	imgout[0][j][i]=128;
      }
    }
  }
   
  //printf("\n<G 信号>\n");
  if(cp_color[1]==1){
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	// printf("%.2x ",imgin[1][j][i]);
	imgout[1][j][i]=imgin[1][j][i];
      }
      //printf("\n");
    }
  }

  if(cp_color[1]==0){
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	imgout[1][j][i]=128;
      } 
    }
  }

  if(cp_color[2]==1){
    //printf("\n<B 信号>\n");
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	//printf("%.2x ",imgin[2][j][i]);
	imgout[2][j][i]=imgin[2][j][i];
      }
      //printf("\n");
    }
  }
  if(cp_color[2]==0){
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	imgout[2][j][i]=128;
      } 
    }
  }

 
} 
void put_data(){
  FILE *fp2;
  char cpname[N];
  int i=0;
  int j;
  int k;
  printf("出力画像データを作成しました.\n");
  printf("\n");
  printf("出力ファイル名を入力して下さい:");
  scanf("%s",cpname);
  fp2=fopen(cpname,"wb");
  printf("ファイルをオープンしました.\n");
  while(i<54){
    fputc(header[i],fp2);
    i++;
  }
  for(i=high-1;i>=0;i--){
    for(j=0;j<wide;j++){
      for(k=2;k>=0;k--){
	fputc(imgout[k][j][i],fp2);
      }
    }
  }
  fclose(fp2);
  printf("ファイルをクローズしました.\n");
}


void rgb_to_ybr(){
  int i,j,k=0;;
  double ybr[3][3]={
    {0.2990,0.5870,0.1140},
    {-0.1687,-0.3313,0.50000},
    {0.50000,-0.4187,-0.0813},
  };


  //printf("<入力信号(RGB)>\n");
  //printf("---R---\n");
  for(i=0;i<high;i++){
    for(j=0;j<wide;j++){
      //      printf("%.2x ",imgin[0][j][i]);
      //imgout[0][j][i]=imgin[0][j][i];
    }
    // printf("\n");
  }
  //printf("---G---\n");
  for(i=0;i<high;i++){
    for(j=0;j<wide;j++){
      // printf("%.2x ",imgin[1][j][i]);
      //imgout[1][j][i]=imgin[1][j][i];
    }
    //printf("\n");
  }

  //printf("---B---\n");
  for(i=0;i<high;i++){
    for(j=0;j<wide;j++){
      // printf("%.2x ",imgin[2][j][i]);
      //imgout[2][j][i]=imgin[2][j][i];
    }
    //printf("\n");
  }

  double imgin3[3][512][512];


  //計算

    for(i=0;i<512;i++){
      for(j=0;j<512;j++){
	for(k=0;k<3;k++){	
	  imgin3[0][i][j]+=ybr[0][k]*imgin[k][i][j];
	  imgin3[1][i][j]+=ybr[1][k]*imgin[k][i][j];
	  imgin3[2][i][j]+=ybr[2][k]*imgin[k][i][j];
	}
      }
    }
  
  
    //printf("<入力信号(YCbCr)>\n");

    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
        if(imgin3[0][i][j]>=0){
	  imgin3[0][i][j]+=0.5;
	  imgin3[0][i][j]=(int)imgin3[0][i][j];
      }
	else{
	  if(imgin3[k][i][j]<0){
	    imgin3[k][i][j]-=0.5;
	    imgin3[k][i][j]=(int)imgin3[0][i][j];
	  }
	}
      }
    }
    for(k=0;k<3;k++){
      for(i=0;i<high;i++){
	for(j=0;j<wide;j++){
	  if(imgin3[k][j][i]>=0){
	    imgin3[k][j][i]+=0.5;
	    imgin3[k][j][i]=(int)imgin3[k][j][i];
	  }
	  else{
	    imgin3[k][j][i]-=0.5;
	    imgin3[k][j][i]=(int)imgin3[k][j][i];
	  }
	}
      }
    }
    for(k=1;k<3;k++){
      for(i=0;i<high;i++){
	for(j=0;j<wide;j++){
	  imgin3[k][j][i]+=128;
	}
      }
    }

    for(i=0;i<3;i++){
      for(j=0;j<512;j++){
        for(k=0;k<512;k++){
          if(imgin3[i][k][j]>=255){
            imgin3[i][k][j]=255;
          }
          else if(imgin3[i][k][j]<=0){
            imgin3[i][k][j]=0;
          } 
        }
      }
    }

    for(i=0;i<3;i++){
      for(j=0;j<512;j++){
	for(k=0;k<512;k++){
	  imgin[i][k][j]=(int)imgin3[i][k][j];
	}
      }
    }

    // printf("---Y---\n");
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	//printf("%.2x ",imgin[0][j][i]);
	//imgout[0][j][i]=imgin[0][j][i];                                         
      }
      // printf("\n");
    }
    // printf("---Cb---\n");
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	//printf("%.2x ",imgin[1][j][i]);
	//imgout[1][j][i]=imgin[1][j][i];                                         
      }
      // printf("\n");
    }
    
    // printf("---Cr---\n");
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	//	printf("%.2x ",imgin[2][j][i]);
      //imgout[2][j][i]=imgin[2][j][i];                                         
      }
      // printf("\n");
    }
}


void ybr_to_rgb(){
  double rgb[3][3]={
    {1.0000,0.0000,1.4020},
    {1.0000,-0.3441,-0.7141},
    {1.0000,1.7720,-0.0000},
  };
  int i,j,k=0;
  //printf("＜出力信号(YCbCr)＞\n");
  //printf("--- Y ---\n");
 
  for(i=0;i<high;i++){
    for(j=0;j<wide;j++){
      //  printf("%.2x ",imgout[0][j][i]);
    }
    // printf("\n");
  }
  //printf("--- Cb ---\n");
  for(i=0;i<high;i++){
    for(j=0;j<wide;j++){
      //  printf("%.2x ",imgout[1][j][i]);
    }
    // printf("\n");
  }
  
  //printf("--- Cr ---\n");
  for(i=0;i<high;i++){
    for(j=0;j<wide;j++){
      //  printf("%.2x ",imgout[2][j][i]);
    }
    //  printf("\n");
  }
  //printf("\n");
  short imgout3[3][512][512]={};
  double imgout4[3][512][512]={};
  /////

  for(k=0;k<3;k++){
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
        imgout3[k][j][i]=imgout[k][j][i];
      }
    }
  }

  

 for(k=1;k<3;k++){
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	imgout3[k][j][i]=imgout3[k][j][i]-128.0;
      }
    }
  }

  
    /////

  for(i=0;i<high;i++){
    for(j=0;j<wide;j++){
      for(k=0;k<3;k++){
	imgout4[0][i][j]+=rgb[0][k]*imgout3[k][i][j];
	imgout4[1][i][j]+=rgb[1][k]*imgout3[k][i][j];
	imgout4[2][i][j]+=rgb[2][k]*imgout3[k][i][j];
      }
    }
  }


  for(k=0;k<3;k++){
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	if(imgout4[k][j][i]>=0){
	  imgout4[k][j][i]+=0.5;
	}
	if(imgout4[k][j][i]<0){
	  imgout4[k][j][i]-=0.5;
	}
	imgout4[k][j][i]=(int)imgout4[k][j][i];
      }
    }
  }

  for(k=0;k<3;k++){
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	if(imgout4[k][j][i]>255){
	  imgout4[k][j][i]=255;
	}
	if(imgout4[k][j][i]<0){
	    imgout4[k][j][i]=0;
	}
      }
    }
  }
  

  for(k=0;k<3;k++){
    for(i=0;i<high;i++){
      for(j=0;j<wide;j++){
	imgout[k][j][i]=imgout4[k][j][i];
      }
    }
  }
  


  // printf("＜出力信号(RGB)＞\n");
  // printf("--- R ---\n");
  for(i=0;i<high;i++){
    for(j=0;j<wide;j++){
      //  printf("%.2x ",imgout[0][j][i]);
    }
    //printf("\n");
  }
  //printf("--- G ---\n");
  for(i=0;i<high;i++){
    for(j=0;j<wide;j++){
      //   printf("%.2x ",imgout[1][j][i]);
    }
    // printf("\n");
  }

  //printf("--- B ---\n");
  for(i=0;i<high;i++){
    for(j=0;j<wide;j++){
      //  printf("%.2x ",imgout[2][j][i]);
    }
    // printf("\n");
  }
}
