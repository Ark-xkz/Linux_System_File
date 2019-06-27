#include "head.h"


void findFile(string cover,string dest){
    bool flag = true;
    int tempCur;//source µÄÄ¿Â¼Ïîpoint
    if(cover == " "){
        tempCur = cur_dir;
    }else{
        tempCur= findDentry(cover,flag);
    }
    if(flag ==false){
        return;
    }
    findSubFile(tempCur ,dest);
}


void findSubFile(int padir,string name){
    Dentry den = main_dir.mainDirs[padir];
    string fileName(den.nameFile);
    if(name == fileName){
        printPath(padir);
    }
    if(den.type != 'd'){
        return;
    }else{
        for(int i = 0;i< dir_sys[den.pointNum].sizeDir;i++){
            int numSub = dir_sys[den.pointNum].pointNum[i];
            findSubFile(numSub,name);
        }

    }

}
void printPath(int numcur){
    vector<string> paths;
    Inode inodeNow = inode_sys[main_dir.mainDirs[numcur].inum];
    while(inodeNow.inum != 0){
        string nameNow(inodeNow.fileName);
        paths.push_back(nameNow);
        inodeNow = inode_sys[inodeNow.numParent];
    }
    for(int i = (int)paths.size()-1;i>=0;i--){
        cout<<"/"<<paths[i];
    }
    cout<<endl;
}
void chmod(int num,string path){
    int power[3];
    power[0] = num / 100;
    num-=power[0]*100;
    power[1] = num /10;
    power[2] = num % 10;

    bool flag =true;
    int tempCur;
    tempCur= findDentry(path,flag);
     if(flag ==false){
        return;
    }
    Inode tmp = inode_sys[main_dir.mainDirs[tempCur].inum];
    if(0!=strcmp(tmp.ownerName,usr_act.name) && 0 !=strcmp(usr_act.name,"root")){
        cout<<"you don't have the power!"<<endl;
        return;
    }

    inode_sys[main_dir.mainDirs[tempCur].inum].powerUsr[0]=power[0];
    inode_sys[main_dir.mainDirs[tempCur].inum].powerUsr[1]=power[1];
    inode_sys[main_dir.mainDirs[tempCur].inum].powerUsr[2]=power[2];
    saveInode(main_dir.mainDirs[tempCur].inum);


}
//将新生成的节点插入到USR table 中
void addToUser(int numInode){
    Inode tmpInode = inode_sys[numInode];
    for(int i =0;i<MAX_USRNUM;i++){
        UsrTable tmpTable = usr_tables[i];
        if(0 == strcmp(tmpInode.ownerName,tmpTable.usrName)){
            for(int j =0;j<MAX_USRTABLE;j++){
                if(usr_tables[i].usrTable[j] == -1){
                    usr_tables[i].usrTable[j] = numInode;
                    break;
                }
            }

            break;
        }
    }
}

void delFromUsr(int numInode){
    Inode tmpInode = inode_sys[numInode];
    for(int i =0;i<MAX_USRNUM;i++){
        UsrTable tmpTable = usr_tables[i];
        if(0 == strcmp(tmpInode.ownerName,tmpTable.usrName)){
            for(int j =0;j<MAX_USRTABLE;j++){
                if(usr_tables[i].usrTable[j] == numInode){
                    usr_tables[i].usrTable[j] = -1;
                    break;
                }
            }

            break;
        }
    }


}
