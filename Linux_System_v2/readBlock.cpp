#include "head.h"

//��i�ڵ�ָ��Ŀ������ݶ��뵽������
//addrΪinode�е�address��ַ
void readBlock(int addr,char flush[]){
    FILE *bfp;
    bfp = fopen("fileSystem.dat","r+b");

    fseek(bfp,sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE+sizeof(MainDir)+sizeof(Dir)*MAX_DIR+(long)SIZE_BLOCK*addr,SEEK_SET);
    for(int i =0; i<SIZE_BLOCK;i++){
        flush[i] = fgetc(bfp);
    }

    fclose(bfp);
}
