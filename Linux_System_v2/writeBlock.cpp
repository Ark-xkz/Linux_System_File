#include "head.h"


void writeBlock(char flush[],int addr){

    FILE *bfp;
    bfp = fopen("fileSystem.dat", "r+b");
    fseek(bfp,sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE+sizeof(MainDir)+sizeof(Dir)*MAX_DIR+(long)SIZE_BLOCK*addr,SEEK_SET);

    for(int i =0; i<SIZE_BLOCK; i++){
        fputc(flush[i],bfp);
    }

    fclose(bfp);
    //Ð´ÍêÇå¿Õ»º´æflushTmp[]
    for(int i = 0;i < SIZE_BLOCK;i++){
        flushTmp[i] = '\0';
    }

}
