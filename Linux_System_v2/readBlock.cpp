#include "head.h"

//将i节点指向的块中数据读入到缓冲区
//addr为inode中的address地址
void readBlock(int addr,char flush[]){
    FILE *bfp;
    bfp = fopen("fileSystem.dat","r+b");

    fseek(bfp,sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE+sizeof(MainDir)+sizeof(Dir)*MAX_DIR+(long)SIZE_BLOCK*addr,SEEK_SET);
    for(int i =0; i<SIZE_BLOCK;i++){
        flush[i] = fgetc(bfp);
    }

    fclose(bfp);
}
