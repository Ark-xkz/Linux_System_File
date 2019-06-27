#include "head.h"

int getEmptyBlock(){
    int emptyNum,num;
    FILE *sfp;
    sfp = fopen("fileSystem.dat", "r+b");
    if(super_block.pointArr[0]!=1){

        num = 16;
        for(int i=16; i>0&&super_block.pointArr[i]==-1 ; i--){
            num = i-1;
        }
        emptyNum = super_block.pointArr[num];
        super_block.pointArr[num] = -1;
        super_block.pointArr[0]--;

    }else{

        emptyNum = super_block.pointArr[1];
        int temp[17];
        for(int i=0;i<17;i++){
            fread(&temp[i],sizeof(int),1,sfp);
        }

        for(int i=0;i<17;i++){
            super_block.pointArr[i] = temp[i];
        }

    }
    fclose(sfp);
    return emptyNum;
}


//获取空节点
int getEmptyNode(){
    int numRecord = -1;
    for(int i=0;i<MAX_NODE;i++){
        if(inode_sys[i].address==-1){
            numRecord = i;
            break;
            //return &inode_sys[i];
        }
    }
    if(numRecord==-1){
        cout<<"no empty inode !"<<endl;
    }
    inode_sys[numRecord].inum= numRecord;
    inode_sys[numRecord].countNum=1;
    return numRecord;
}

int getEmptyDentry(){
    int numRecord = -1;
    for(int i=0;i< MAIN_DENTRY; i++){
        if(main_dir.mainDirs[i].inum ==-1){
            numRecord = i;
            break;
        }
    }
    if(numRecord == -1){
        cout<<"no empty main dir"<<endl;
    }

    return numRecord;
}
int getEmptyDir(){
    int numRecord = -1;
    for(int i=0;i<MAX_DIR;i++){
        if(dir_sys[i].sizeDir == -1){
            numRecord = i;
            break;
        }
    }
    if(numRecord == -1){
        cout<<"no empty dir"<<endl;
    }
    return numRecord;
}
