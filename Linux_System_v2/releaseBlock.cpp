#include "head.h"

void releaseBlock(int addr){
    FILE *bfp;
    bfp = fopen("fileSystem.dat","r+b");
    int tempN[17];
    //超级块的改写
    if(super_block.pointArr[0]==16){
        for(int i=0;i<17;i++){
            tempN[i]= super_block.pointArr[i];
        }
        super_block.pointArr[0]=1;
        super_block.pointArr[1] = addr;

         //超级块的写入
        fseek(bfp,0,SEEK_SET);
        fwrite(&super_block, sizeof(SuperBlock), 1, bfp);
        //数据块的初始化
        fseek(bfp,sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE+sizeof(MainDir)+sizeof(Dir)*MAX_DIR+(long)SIZE_BLOCK*addr,SEEK_SET);
        for(int i=0;i<SIZE_BLOCK;i++){
            if(i<17*(int)sizeof(int)){
                fwrite(&tempN[i],sizeof(int),1,bfp);
                i+=3;
                //continue;
            }else{
                fputc('\0',bfp);
            }
        }

    }else {
        int Num=16;
        for(int i=16;i>0&&super_block.pointArr[i]==-1;i--){
            Num = i;
        }
        super_block.pointArr[Num] = addr ;
        super_block.pointArr[0]++;
        //超级块的写入
        fseek(bfp,0,SEEK_SET);
        fwrite(&super_block, sizeof(SuperBlock), 1, bfp);
        //数据块清空
        fseek(bfp,sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE+sizeof(MainDir)+sizeof(Dir)*MAX_DIR+(long)SIZE_BLOCK*addr,SEEK_SET);
        for(int i=0;i<SIZE_BLOCK;i++){
            fputc('\0',bfp);
        }
    }


    fclose(bfp);
}

void releaseNode(int num){
    //将原来内存中Node清空
    //将清空的Inode存入磁盘


    FILE *fp;
    fp=fopen("fileSystem.dat","r+b");
    fseek(fp,sizeof(SuperBlock)+num*sizeof(Inode),SEEK_SET);
    //Inode inode_sys[num];
    inode_sys[num].address = -1;
    inode_sys[num].change = 0;
    inode_sys[num].countNum = 0;
    strcpy(inode_sys[num].fileName, "null");
    inode_sys[num].inum = -1;
    inode_sys[num].type ='d';
    inode_sys[num].numParent = 0;
    strcpy(inode_sys[num].ownerName, "root");
    strcpy(inode_sys[num].groupName,"default");
    inode_sys[num].powerUsr[0] = 7;
    inode_sys[num].powerUsr[1] = 6;
    inode_sys[num].powerUsr[2] = 6;
    /*
    strcpy(inode_sys[num].otherName[0], "none");
    strcpy(inode_sys[num].otherName[1], "none");
    strcpy(inode_sys[num].otherName[2], "none");
    inode_sys[num].power[0]='y';
    inode_sys[num].power[1]='y';
    inode_sys[num].power[2]='n';
    */
    inode_sys[num].length = 0;
    fwrite(&inode_sys[num],sizeof(Inode),1,fp);
    fclose(fp);
}


void releaseDir(int num){
    FILE *fp;
    fp=fopen("fileSystem.dat","r+b");
    fseek(fp,sizeof(SuperBlock)+MAX_BLOCK*sizeof(Inode)+sizeof(MainDir)+num*sizeof(Dir),SEEK_SET);
    //Dir dir_sys[num];
    for(int i=0;i<MAX_DENTRY;i++){
        dir_sys[num].pointNum[i] = -1;
    }
    dir_sys[num].sizeDir = -1;

    fwrite(&dir_sys[num], sizeof(Dir), 1, fp);


    fclose(fp);
}

void releaseDentry(int num){
    FILE *fp;
    fp=fopen("fileSystem.dat","r+b");
    fseek(fp,sizeof(SuperBlock)+MAX_BLOCK*sizeof(Inode)+num*sizeof(Dentry),SEEK_SET);

    main_dir.sizeDir--;
    main_dir.mainDirs[num].inum = -1;
    strcpy(main_dir.mainDirs[num].nameFile,"null");
    main_dir.mainDirs[num].pointNum = -1;
    main_dir.mainDirs[num].type = 'd';

    fwrite(&(main_dir.mainDirs[num]),sizeof(Dentry),1,fp);
    fclose(fp);

}

void rm(string path){
    //找到dest的父目录

    int index = path.find_last_of('/');
    int lenLast = 1;
    if(index != 0){
        lenLast = index;
    }
    string lastDir(path,0,lenLast);
    //string name(path,index+1);
    if(index == -1){
        lastDir = main_dir.mainDirs[cur_dir].nameFile;
    }
    bool flag =true;
    int tempCur;
    tempCur= findDentry(path,flag);
    if(flag ==false){
        return;
    }
    int tempCurDest;//dest父目录的目录项的point
    if(index == -1){
            tempCurDest = cur_dir;
    }else{
        tempCurDest=findDentry(lastDir,flag);
    }
    //tempCurDest=findDentry(lastDir,flag);
    if(flag ==false){
        return;
    }
    int pointPower = inode_sys[main_dir.mainDirs[tempCur].inum].inum;
    if(havePower(pointPower) < 4 && 0!=strcmp(usr_act.name,"root")){
        cout<<"you don't have the power!"<<endl;
        return;
    }

    if(inode_sys[main_dir.mainDirs[tempCur].inum].type != 'd'){
        Inode rmInode = inode_sys[main_dir.mainDirs[tempCur].inum];
        int addr = rmInode.address;
        releaseBlock(addr);
        releaseDentry(tempCur);
        for(int i=0;i<dir_sys[main_dir.mainDirs[tempCurDest].pointNum].sizeDir;i++){
            if(dir_sys[main_dir.mainDirs[tempCurDest].pointNum].pointNum[i]==tempCur){
                dir_sys[main_dir.mainDirs[tempCurDest].pointNum].pointNum[i]=-1;
                break;
            }
        }
        for(int i=0;i<MAX_DENTRY;i++){
            int tempPoint = i+1;
            if(dir_sys[main_dir.mainDirs[tempCurDest].pointNum].pointNum[i]==-1){
                for(int j = tempPoint;j<MAX_DENTRY;j++){
                    if(dir_sys[main_dir.mainDirs[tempCurDest].pointNum].pointNum[j]!=-1){
                        break;
                    }else{
                        tempPoint++;
                    }
                }
                if(tempPoint!=MAX_DENTRY){
                    int tmpNum = dir_sys[main_dir.mainDirs[tempCurDest].pointNum].pointNum[i];
                    dir_sys[main_dir.mainDirs[tempCurDest].pointNum].pointNum[i]=dir_sys[main_dir.mainDirs[tempCurDest].pointNum].pointNum[tempPoint];
                    dir_sys[main_dir.mainDirs[tempCurDest].pointNum].pointNum[tempPoint] = tmpNum;
                    //dir_sys[main_dir.mainDirs[tempCurDest].pointNum].pointNum[i]=dir_sys[main_dir.mainDirs[tempCurDest].pointNum].pointNum[tempPoint];
                }else{
                    break;
                }
            }
        }
        dir_sys[main_dir.mainDirs[tempCurDest].pointNum].sizeDir--;
        saveDir(main_dir.mainDirs[tempCurDest].pointNum);
        releaseNode(main_dir.mainDirs[tempCur].inum);
        //saveInode(main_dir.mainDirs[tempCur].inum);
    }else{
        //目录的递归删除

        deleteDir(tempCur);
    }

    int paInum = inode_sys[main_dir.mainDirs[tempCurDest].inum].inum;
    while(-1 != paInum){
        inode_sys[paInum].length -=inode_sys[pointPower].length;
        saveInode(paInum);
        paInum = inode_sys[paInum].numParent;
    }

}
//目录的递归删除
void deleteDir(int mainPoint){
    //查看
    if(main_dir.mainDirs[mainPoint].type !='d' || dir_sys[main_dir.mainDirs[mainPoint].pointNum].sizeDir <= 0){
        //类型为l 或者 t
        int inodeNum = main_dir.mainDirs[mainPoint].inum;
        int inodePa=inode_sys[inodeNum].numParent;
        for(int i=0;i<dir_sys[inode_sys[inodePa].address].sizeDir;i++){
            if(dir_sys[inode_sys[inodePa].address].pointNum[i]==mainPoint){
                dir_sys[inode_sys[inodePa].address].pointNum[i]=-1;
                break;
            }
        }
        for(int i=0;i<MAX_DENTRY;i++){
            int tempPoint = i+1;
            if(dir_sys[inode_sys[inodePa].address].pointNum[i]==-1){
                for(int j = tempPoint;j<MAX_DENTRY;j++){
                    if(dir_sys[inode_sys[inodePa].address].pointNum[j]!=-1){
                        break;
                    }else{
                        tempPoint++;
                    }
                }
                if(tempPoint!=MAX_DENTRY){
                    int tmpNum = dir_sys[inode_sys[inodePa].address].pointNum[i];
                    dir_sys[inode_sys[inodePa].address].pointNum[i]=dir_sys[inode_sys[inodePa].address].pointNum[tempPoint];
                    dir_sys[inode_sys[inodePa].address].pointNum[tempPoint] = tmpNum;
                }else{
                    break;
                }
            }
        }
        dir_sys[inode_sys[inodePa].address].sizeDir--;
        saveDir(inode_sys[inodePa].address);
        releaseDentry(mainPoint);
        inode_sys[inodeNum].countNum--;
        if(inode_sys[inodeNum].countNum<=0){
            if(inode_sys[inodeNum].type=='d'){
                releaseDir(inode_sys[inodeNum].address);
            }else{
                releaseBlock(inode_sys[inodeNum].address);
            }
            releaseNode(inodeNum);
        }
        return ;
    }else{
        int inodeNum = main_dir.mainDirs[mainPoint].inum;
        int numDir = inode_sys[inodeNum].address;
        int len = dir_sys[numDir].sizeDir;
        for(int i=0;i<len;i++){
            deleteDir(dir_sys[numDir].pointNum[0]);
        }
        deleteDir(mainPoint);


    }

}
int havePower(int numInode){
    int power = 0;
    Inode tmpInode = inode_sys[numInode];
    string nameUsr(usr_act.name);
    string nameInode(tmpInode.ownerName);
    string nameGroup(tmpInode.groupName);
    bool isIn =false;
    for(int i =0;i<10;i++){
        string gName(group_all[i].groupName);
        if(nameGroup == gName){
            for(int j=0;j<10;j++){
                string tmpName(group_all[i].memberName[j]);
                if(tmpName == nameUsr ){
                    isIn = true;
                }
            }
            //isIn = true;
            break;
        }
    }
    if(nameUsr == nameInode){
        power = tmpInode.powerUsr[0];
    }else if(isIn ==true){
        power = tmpInode.powerUsr[1];
    }else{
        power = tmpInode.powerUsr[2];
    }
    return power;
}
