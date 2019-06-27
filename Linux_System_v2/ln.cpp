#include "head.h"


void ln(char choice,string source,string dest){
    //软链接
    if(choice == 's'){
        //软链接可以指向不存在的目录/目录项
        //找到dest的父目录
        int index = dest.find_last_of('/');
        int lenLast = 1;
        if(index != 0){
            lenLast = index;
        }
        string lastDir(dest,0,lenLast);
        string name(dest,index+1);
        if(index == -1){
            lastDir = main_dir.mainDirs[cur_dir].nameFile;
            //name = dest;
        }
        bool flag =true;
        int tempCurDest;
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


        int numBlock = getEmptyBlock();
        strcpy(flushTmp,source.data());
        //strcpy(flushTmp, source.c_str());
        writeBlock(flushTmp,numBlock);

        int numInode = getEmptyNode();
        inode_sys[numInode].address = numBlock;
        inode_sys[numInode].length = source.length();
        inode_sys[numInode].numParent = main_dir.mainDirs[tempCurDest].inum;
        strcpy(inode_sys[numInode].ownerName, usr_act.name);
        strcpy(inode_sys[numInode].fileName, name.data());
        inode_sys[numInode].type = 'l';
        saveInode(numInode);

        int numNewDentry = getEmptyDentry();
        main_dir.mainDirs[numNewDentry].inum = numInode;
        strcpy(main_dir.mainDirs[numNewDentry].nameFile,name.data());
        main_dir.mainDirs[numNewDentry].type = inode_sys[numInode].type;// inode_sys[numInode].type;
        main_dir.mainDirs[numNewDentry].pointNum = -1;
        saveDentry(numNewDentry);
        cout<<"new Dentry: "<<numNewDentry<<" "<<main_dir.mainDirs[numNewDentry].nameFile<<endl;
        main_dir.sizeDir++;
        //在父目录中插入目录项
        int paDirNum;
        int paInum = inode_sys[main_dir.mainDirs[tempCurDest].inum].inum;
            for(int i =0;i< MAIN_DENTRY;i++){
                if(main_dir.mainDirs[i].inum==paInum){
                    paDirNum = main_dir.mainDirs[i].pointNum;
                    break;
                }
            }
            dir_sys[paDirNum].pointNum[dir_sys[paDirNum].sizeDir] = numNewDentry;
            dir_sys[paDirNum].sizeDir++;
            saveDir(main_dir.mainDirs[tempCurDest].pointNum);


        int faInum = inode_sys[numInode].numParent;
        while(-1 != faInum){
            inode_sys[faInum].length+=inode_sys[numInode].length;
            saveInode(faInum);
            faInum = inode_sys[faInum].numParent;
        }

    }else{
        //硬链接
        //硬链接不可以指向目录
        //找到source
        //解析路径名
        bool flag = true;
        int tempCur;
        tempCur= findDentry(source,flag);
        if(flag ==false){
            return;
        }
        //找到dest的父目录
        int index = dest.find_last_of('/');
        int lenLast = 1;
        if(index != 0){
            lenLast = index;
        }
        string lastDir(dest,0,lenLast);
        string name(dest,index+1);
        if(index == -1){
            lastDir = "";
            lastDir = main_dir.mainDirs[cur_dir].nameFile;
            //name = dest;
        }
        flag =true;
        int tempCurDest;
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

        int numSource = main_dir.mainDirs[tempCur].inum;//source 的 inum
        int numNewDentry = getEmptyDentry();
        main_dir.mainDirs[numNewDentry].inum = inode_sys[numSource].inum;

        strcpy(main_dir.mainDirs[numNewDentry].nameFile,name.data());
        main_dir.mainDirs[numNewDentry].type = 'l';// inode_sys[numSource].type;
        main_dir.mainDirs[numNewDentry].pointNum = main_dir.mainDirs[tempCur].pointNum ;
        saveDentry(numNewDentry);
        cout<<"new Dentry: "<<numNewDentry<<" "<<main_dir.mainDirs[numNewDentry].nameFile<<endl;
        main_dir.sizeDir++;
            //在父目录中插入目录项
            int paDirNum;
            //int numNewNode = main_dir.mainDirs[tempCurDest].inum;
            int paInum = inode_sys[main_dir.mainDirs[tempCurDest].inum].inum;
            for(int i =0;i< MAIN_DENTRY;i++){
                if(main_dir.mainDirs[i].inum==paInum){
                    paDirNum = main_dir.mainDirs[i].pointNum;
                    break;
                }
            }
            dir_sys[paDirNum].pointNum[dir_sys[paDirNum].sizeDir] = numNewDentry;
            dir_sys[paDirNum].sizeDir++;
            saveDir(main_dir.mainDirs[tempCurDest].pointNum);

        //原文件的count++
        inode_sys[main_dir.mainDirs[tempCurDest].inum].countNum++;
        saveInode(main_dir.mainDirs[tempCurDest].inum);

        int faInum = paInum;
        while(-1 != faInum){
            inode_sys[faInum].length+=inode_sys[numSource].length;
            saveInode(faInum);
            faInum = inode_sys[faInum].numParent;
        }
    }

}
//复制
void cp(string source,string dest){
    bool flag = true;
    int tempCur;//source 的目录项point
    tempCur= findDentry(source,flag);
    if(flag ==false){
        return;
    }
    //找到dest的父目录
    int index = dest.find_last_of('/');
    int lenLast = 1;
    if(index != 0){
        lenLast = index;
    }
    string lastDir(dest,0,lenLast);
    string name(dest,index+1);
    if(index == -1){
        lastDir = main_dir.mainDirs[cur_dir].nameFile;
    }
    flag =true;
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
    int pointPower2 = inode_sys[main_dir.mainDirs[tempCur].inum].inum;
    if(0!=strcmp(usr_act.name,"root")){
        if(havePower(pointPower) < 4 &&havePower(pointPower2) < 2){
            cout<<"you don't have the power!"<<endl;
            return;
        }
    }


    //source 不是目录，可以为文件或者软链接
    if(inode_sys[main_dir.mainDirs[tempCur].inum].type != 'd'){
        Inode sourceNode = inode_sys[main_dir.mainDirs[tempCur].inum];
        int numBlock = getEmptyBlock();
        int numInode = getEmptyNode();
        inode_sys[numInode].address = numBlock;
        inode_sys[numInode].change = 1;// sourceNode.change;
        //inode_sys[numInode].countNum = sourceNode.countNum;
        inode_sys[numInode].length = sourceNode.length;
        inode_sys[numInode].numParent = main_dir.mainDirs[tempCurDest].inum;
        strcpy(inode_sys[numInode].ownerName, usr_act.name);
        //inode_sys[numInode].otherName = "none";
        strcpy(inode_sys[numInode].fileName, name.data());
        inode_sys[numInode].type = sourceNode.type;
        saveInode(numInode);
        //inode_sys[numInode].power = sourceNode;
        readBlock(sourceNode.address,flushTmp);
        writeBlock(flushTmp,numBlock);

        int numNewDentry = getEmptyDentry();
        main_dir.mainDirs[numNewDentry].inum = numInode;
        strcpy(main_dir.mainDirs[numNewDentry].nameFile,name.data());
        main_dir.mainDirs[numNewDentry].type = inode_sys[numInode].type;// inode_sys[numInode].type;
        main_dir.mainDirs[numNewDentry].pointNum = -1;
        saveDentry(numNewDentry);
        cout<<"new Dentry: "<<numNewDentry<<" "<<main_dir.mainDirs[numNewDentry].nameFile<<endl;
        main_dir.sizeDir++;
        //在父目录中插入目录项
        int paDirNum;
        int paInum = inode_sys[main_dir.mainDirs[tempCurDest].inum].inum;
            for(int i =0;i< MAIN_DENTRY;i++){
                if(main_dir.mainDirs[i].inum==paInum){
                    paDirNum = main_dir.mainDirs[i].pointNum;
                    break;
                }
            }
            dir_sys[paDirNum].pointNum[dir_sys[paDirNum].sizeDir] = numNewDentry;
            dir_sys[paDirNum].sizeDir++;
            saveDir(main_dir.mainDirs[tempCurDest].pointNum);


        int faInum = pointPower;
        while(-1 != faInum){
            inode_sys[faInum].length+=sourceNode.length;
            saveInode(faInum);
            faInum = inode_sys[faInum].numParent;
        }

    }else{


    }
}
