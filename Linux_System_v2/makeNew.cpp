#include "head.h"




void mkdir(string name){
    int index = name.find_last_of('/');
    int lenLast = 1;
    if(index != 0){
        lenLast = index;
    }
    string lastDir(name,0,lenLast);
    string dest(name,index+1);
    if(index == -1){
        lastDir = main_dir.mainDirs[cur_dir].nameFile;
    }
    bool flag =true;
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
    int pointPower = inode_sys[main_dir.mainDirs[tempCurDest].inum].inum;
    if(havePower(pointPower) < 4 && 0!= strcmp(usr_act.name,"root")){
        cout<<"you don't have the power!"<<endl;
        return;
    }

    int paDirNum = main_dir.mainDirs[tempCurDest].pointNum ;
    if(dir_sys[paDirNum].sizeDir>=MAX_DENTRY){
        cout<<"cannot mkdir into the dir!"<<endl;
        return;
    }
    int numNewNode=getEmptyNode();
    //设置inode
    inode_sys[numNewNode].type = 'd';
    for(int i=0;i<10;i++){
        inode_sys[numNewNode].fileName[i]='\0';
        inode_sys[numNewNode].ownerName[i]='\0';
    }
    strcpy(inode_sys[numNewNode].fileName,dest.data());
    strcpy(inode_sys[numNewNode].ownerName,usr_act.name);
    inode_sys[numNewNode].length = 0;
    inode_sys[numNewNode].countNum = 0;
    inode_sys[numNewNode].numParent = inode_sys[main_dir.mainDirs[tempCurDest].inum].inum;
    int numNewDir = getEmptyDir();
    inode_sys[numNewNode].address = numNewDir;
    //cout<<"new Inode: "<<inode_sys[numNewNode].fileName<<endl;
    saveInode(inode_sys[numNewNode].inum);

    //生成dir
    dir_sys[numNewDir].sizeDir = 0;
    saveDir(numNewDir);
    //产生Dentry
    int numNewDentry = getEmptyDentry();

    main_dir.mainDirs[numNewDentry].inum = inode_sys[numNewNode].inum;
    strcpy(main_dir.mainDirs[numNewDentry].nameFile,dest.data());
    main_dir.mainDirs[numNewDentry].type = inode_sys[numNewNode].type;
    main_dir.mainDirs[numNewDentry].pointNum = numNewDir;
    saveDentry(numNewDentry);
    main_dir.sizeDir++;

    //在父目录中插入目录项
    //cur_dir 主目录中的目录位置
    dir_sys[paDirNum].pointNum[dir_sys[paDirNum].sizeDir] = numNewDentry;
    dir_sys[paDirNum].sizeDir++;
    saveDir(main_dir.mainDirs[tempCurDest].pointNum);



}

//新建一个文件
void touch(string name){
    int index = name.find_last_of('/');
    int lenLast = 1;
    if(index != 0){
        lenLast = index;
    }
    string lastDir(name,0,lenLast);
    string dest(name,index+1);
    if(index == -1){
        lastDir = main_dir.mainDirs[cur_dir].nameFile;
    }
    bool flag =true;
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

    int pointPower = inode_sys[main_dir.mainDirs[tempCurDest].inum].inum;
    if(havePower(pointPower) < 4 && 0!=strcmp(usr_act.name,"root")){
        cout<<"you don't have the power!"<<endl;
        return;
    }


    int paDirNum = main_dir.mainDirs[tempCurDest].pointNum ;
    if(dir_sys[paDirNum].sizeDir>=MAX_DENTRY){
        cout<<"cannot touch new file into the dir!"<<endl;
        return;
    }
    //设置node
    int numNewNode=getEmptyNode();
    inode_sys[numNewNode].type = 't';
    for(int i=0;i<10;i++){
        inode_sys[numNewNode].fileName[i]='\0';
        inode_sys[numNewNode].ownerName[i]='\0';
    }
    strcpy(inode_sys[numNewNode].fileName,dest.data());
    strcpy(inode_sys[numNewNode].ownerName,usr_act.name);
    inode_sys[numNewNode].length = 0;
    inode_sys[numNewNode].countNum = 1;
    inode_sys[numNewNode].numParent = inode_sys[main_dir.mainDirs[tempCurDest].inum].inum;

    int numNewBlock = getEmptyBlock();
    inode_sys[numNewNode].address = numNewBlock;
    saveInode(inode_sys[numNewNode].inum);

    int numNewDentry = getEmptyDentry();
    main_dir.mainDirs[numNewDentry].inum = inode_sys[numNewNode].inum;
    strcpy(main_dir.mainDirs[numNewDentry].nameFile,dest.data());
    main_dir.mainDirs[numNewDentry].type = 't';//inode_sys[numNewNode].type;
    main_dir.mainDirs[numNewDentry].pointNum = -1;
    saveDentry(numNewDentry);
    main_dir.sizeDir++;


    int numNewDir = getEmptyDir();
    inode_sys[numNewNode].address = numNewDir;
    //cout<<"new Inode: "<<inode_sys[numNewNode].fileName<<endl;
    saveInode(inode_sys[numNewNode].inum);

    //在父目录中插入目录项
    //cur_dir 主目录中的目录位置
    dir_sys[paDirNum].pointNum[dir_sys[paDirNum].sizeDir] = numNewDentry;
    dir_sys[paDirNum].sizeDir++;
    saveDir(main_dir.mainDirs[tempCurDest].pointNum);


}
void vim(string path){
    bool flag = true;
    int tempCur;
    tempCur= findDentry(path,flag);
    if(flag ==false){
        return;
    }
    int pointPower = inode_sys[main_dir.mainDirs[tempCur].inum].inum;
    if(havePower(pointPower) < 4 && 0!=strcmp(usr_act.name,"root")){
        cout<<"you don't have the power!"<<endl;
        return;
    }

    cout<<"--------------------------------------------------"<<endl;
    int len=0;
    char temp;
    for(int i = 0;i<SIZE_BLOCK;i++){
        cin>>temp;
        if(temp == '#'){
            break;
        }else{
            flushTmp[i] = temp;
            len++;
        }
    }
    inode_sys[main_dir.mainDirs[tempCur].inum].length = len;
    if(inode_sys[main_dir.mainDirs[tempCur].inum].type == 'd'){
        cout<<"It's a dirctory !"<<endl;
    }else{
        writeBlock(flushTmp,inode_sys[main_dir.mainDirs[tempCur].inum].address);
        saveInode(main_dir.mainDirs[tempCur].inum);
        cout<<"--------------------------------------------------"<<endl;
    }
    int paInum = inode_sys[main_dir.mainDirs[tempCur].inum].numParent;
    while(-1 != paInum){
        inode_sys[paInum].length+=len;
        saveInode(paInum);
        paInum = inode_sys[paInum].numParent;
    }

}
