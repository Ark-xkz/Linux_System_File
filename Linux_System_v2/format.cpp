#include "head.h"
void format(){
    cout<<"is ready to format the file system"<<"!!!"<<"all the data will lost"<<endl;
    char choice;
    cout<<"are you sure? Y | N : ";
    cin>>choice;
    if(choice == 'N'){
        return ;
    }
    //创建文件系统
    FILE *fileSys;
    fileSys = fopen("fileSystem.dat", "w+b");
    /*
    //存放数据区的位示图
    for(int i=0;i<SIZE_BLOCK;i++){
        fputc('0',fileSys);
    }
    */
    //超级块
    SuperBlock superblock;
    superblock.pointArr[0]=1;
    superblock.pointArr[1]=0;
    for(int i=2;i<17;i++){
        superblock.pointArr[i]=-1;
    }
    fwrite(&superblock, sizeof(SuperBlock), 1, fileSys);
    //索引节点的初始化
    Inode inode;
    inode.inum = 0;
    inode.type = 'd';
    inode.countNum=100;
    inode.numParent=-1;
    inode.change=0;
    inode.address =0;
    inode.length = 0;
    strcpy(inode.fileName, "/");
    strcpy(inode.ownerName, "root");
    strcpy(inode.groupName,"default");
    inode.powerUsr[0] = 7;
    inode.powerUsr[1] = 6;
    inode.powerUsr[2] = 6;
    fwrite(&inode, sizeof(Inode), 1, fileSys);
    //etc
    inode.inum = 1;
    inode.type = 'd';
    inode.countNum=0;
    inode.numParent=0;
    inode.change=0;
    inode.address = 1;
    strcpy(inode.fileName, "etc");
    strcpy(inode.ownerName, "root");
    strcpy(inode.groupName,"default");
    inode.powerUsr[0] = 7;
    inode.powerUsr[1] = 6;
    inode.powerUsr[2] = 6;
    fwrite(&inode, sizeof(Inode), 1, fileSys);
    //home
    inode.inum = 2;
    inode.type = 'd';
    inode.countNum=0;
    inode.numParent=0;
    inode.change=0;
    inode.address = 2;
    strcpy(inode.fileName, "home");
    strcpy(inode.ownerName, "root");
    strcpy(inode.groupName,"default");
    inode.powerUsr[0] = 7;
    inode.powerUsr[1] = 6;
    inode.powerUsr[2] = 6;
    fwrite(&inode, sizeof(Inode), 1, fileSys);

    inode.inum=-1;
    inode.address=-1;
    for (int i = 3; i < MAX_NODE; i++){
			fwrite(&inode, sizeof(Inode), 1, fileSys);
    }
    //main_Dir项
    MainDir tempMain;
    tempMain.sizeDir=3;

    tempMain.mainDirs[0].inum =0;
    strcpy(tempMain.mainDirs[0].nameFile,"/");
    tempMain.mainDirs[0].pointNum = 0;
    tempMain.mainDirs[0].type = 'd';

    tempMain.mainDirs[1].inum =1;
    strcpy(tempMain.mainDirs[1].nameFile,"etc");
    tempMain.mainDirs[1].pointNum = 1;
    tempMain.mainDirs[1].type = 'd';

    tempMain.mainDirs[2].inum =2;
    strcpy(tempMain.mainDirs[2].nameFile,"home");
    tempMain.mainDirs[2].pointNum = 2;
    tempMain.mainDirs[2].type = 'd';

    for(int i=3;i< MAIN_DENTRY;i++){
        tempMain.mainDirs[i].inum =-1;
        strcpy(tempMain.mainDirs[i].nameFile,"null");
        tempMain.mainDirs[i].pointNum = -1;
        tempMain.mainDirs[i].type = 'd';
    }
    fwrite(&tempMain,sizeof(MainDir),1,fileSys);
    /*
    Dentry dentry;
    dentry.inum = 0;
    strcpy(dentry.nameFile,"/");
    dentry.pointNum = 0;
    dentry.type='d';
    fwrite(&dentry, sizeof(Dentry), 1, fileSys);

    dentry.inum = 1;
    strcpy(dentry.nameFile,"etc");
    dentry.pointNum=1;
    dentry.type='d';
    fwrite(&dentry, sizeof(Dentry), 1, fileSys);
    for(int i=2;i<MAIN_DENTRY;i++){
        for(int j=0;j<(int)sizeof(Dentry);j++){
            fputc('\0',fileSys);
        }
    }
    */
    Dir tempDir;
    tempDir.pointNum[0]=1;
    tempDir.pointNum[1]=2;
    for(int i=2;i<MAX_DENTRY;i++){
        tempDir.pointNum[i]=-1;
    }
    tempDir.sizeDir=2;
    fwrite(&tempDir, sizeof(Dir), 1, fileSys);

    tempDir.pointNum[0]=-1;
    tempDir.pointNum[1]=-1;
    tempDir.sizeDir=0;
    for(int i=0;i<2;i++){
        fwrite(&tempDir, sizeof(Dir), 1, fileSys);
    }
    //tempDir.pointNum[0]=2;
    tempDir.sizeDir=-1;
    for(int i=3;i<MAX_DIR;i++){
        fwrite(&tempDir, sizeof(Dir), 1, fileSys);
    }
    /*
    for(int i=0;i<MAX_DENTRY;i++){
        tempDir.pointNum[i]=-1;
    }
    tempDir.sizeDir=0;
    fwrite(&tempDir, sizeof(Dir), 1, fileSys);
    */
    //链式管理空闲块初始化
    int sumItem=0;
    int lenItem = 16;

    for(int i=0;i<31;i++){
        for(int j=0;j<SIZE_BLOCK;j++){
            if(j==0){
                fwrite(&lenItem, sizeof(int), 1, fileSys);
                j+=3;

            }else if(j<17*(int)sizeof(int)){
                int fNum =sumItem +32;
                sumItem++;
                fwrite(&fNum, sizeof(int), 1, fileSys);
                j+=3;

            }else{
                fputc('\0',fileSys);
            }
        }
    }
    lenItem=15;
    for(int j=0;j<SIZE_BLOCK;j++){

            if(j==0){
                fwrite(&lenItem, sizeof(int), 1, fileSys);
                j+=3;
                //continue;
            }else if(j==4){
                int tempN = -1;
                fwrite(&tempN,sizeof(int),1,fileSys);
                j+=3;
                //continue;
            }else if(j<17*(int)sizeof(int)){
                int fNum =sumItem +32;
                sumItem++;
                fwrite(&fNum, sizeof(int), 1, fileSys);
                j+=3;
                //continue;
            }else{
                fputc('\0',fileSys);
            }
        }

        for(int i=32*SIZE_BLOCK;i<MAX_BLOCK*SIZE_BLOCK;i++){
            fputc('\0',fileSys);
        }
        UsrTable loadUsr;
        strcpy(loadUsr.usrName,"root");
        loadUsr.usrTable[0] = 0;
        loadUsr.usrTable[1] = 1;
        loadUsr.usrTable[2] = 2;
        for(int i = 3;i<MAX_USRTABLE;i++){
            loadUsr.usrTable[i] = -1;
        }
        fwrite(&loadUsr, sizeof(UsrTable), 1, fileSys);
        strcpy(loadUsr.usrName,"null");
        loadUsr.usrTable[0] = -1;
        loadUsr.usrTable[1] = -1;
        loadUsr.usrTable[2] = -1;
        for(int i = 1;i<MAX_USRNUM;i++){
            fwrite(&loadUsr, sizeof(UsrTable), 1, fileSys);
        }
        Group loadgroup;
        strcpy(loadgroup.groupName,"default");
        for(int i = 0;i<10;i++){
            strcpy(loadgroup.memberName[i],"null");
        }
        fwrite(&loadgroup, sizeof(Group), 1, fileSys);
        strcpy(loadgroup.groupName,"null");
        for(int i = 1;i< 10;i++){
            fwrite(&loadgroup, sizeof(Group), 1, fileSys);
        }
        fclose(fileSys);
        //对用户信息进行初始化，只剩下root
        remove("usr.txt");
        ofstream ofp;
        ofp.open("usr.txt");
        ofp<<"root"<<endl;
        ofp<<"123456";
        ofp.close();

        //格式化后需要初始化
        init();

}
