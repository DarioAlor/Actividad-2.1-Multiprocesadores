#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *image, *outputImage, *lecturas, *fptr1, *fptr2, *fptr3, *fptr4;
    image = fopen("imagen.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("img7_dd.bmp","wb");    //Imagen transformada
    long ancho;
    long alto;
    unsigned char r, g, b;               //Pixel
    int azul = 0, verde = 0, rojo = 0, gris = 0;
    int red[255] = {0};
    int green[255]= {0};
    int blue[255] = {0};
    int gray[255] = {0};

    unsigned char xx[54];
    int cuenta = 0;
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("Largo de la imagen en pixeles: %li\n",alto);
    printf("Ancho de la imagen en pixeles: %li\n",ancho);

    fptr1=fopen("Red.txt","w");
    fptr2=fopen("Green.txt","w");
    fptr3=fopen("Blue.txt","w");
    fptr4=fopen("Gray.txt","w");

    while(!feof(image)) {                                        //Grises
       b = fgetc(image);
       g = fgetc(image);
       r = fgetc(image);
       
       azul = blue[b]; 
       blue[b] = azul + 1;
       verde = green[g];
       green[g] = verde + 1;
       rojo = red[r];
       red[r] = rojo + 1;

       unsigned char pixel = 0.21*r+0.72*g+0.07*b;
       fputc(pixel, outputImage);
       fputc(pixel, outputImage);
       fputc(pixel, outputImage);

      gris = gray[pixel];
      gray[pixel] = gris + 1;
    }

    for (int i = 0; i<256; i++) {
        fprintf(fptr1, "%d\n",red[i]);
    }
    fclose(fptr1);

    for (int i = 0; i<256; i++) {
        fprintf(fptr2, "%d\n",green[i]);
    }
    fclose(fptr2);

    for (int i = 0; i<256; i++) {
        fprintf(fptr3, "%d\n",blue[i]);
    }
    fclose(fptr3);

    for (int i = 0; i<256; i++) {
        fprintf(fptr4, "%d\n",gray[i]);
    }
    fclose(fptr4);

    fclose(image);
    fclose(outputImage);
    return 0;
}