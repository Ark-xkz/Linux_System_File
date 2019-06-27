#include "head.h"

void saveInode(int num){
    FILE *ifp;
    ifp = fopen("fileSystem.dat", "r+b");
    inode_sys[num].change = 0;
    fseek(ifp, sizeof(SuperBlock)+num*sizeof(Inode),SEEK_SET);
    fwrite(&(inode_sys[num]),sizeof(Inode),1,ifp);
    fclose(ifp);
}

void saveDir(int num){
    FILE *fp;
    fp = fopen("fileSystem.dat", "r+b");
    fseek(fp, sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE+sizeof(MainDir)+(long)sizeof(Dir)*num,SEEK_SET);
    fwrite(&(dir_sys[num]),sizeof(Dir),1,fp);
    fclose(fp);

}

void saveDentry(int num){
    FILE *fp;
    fp = fopen("fileSystem.dat", "r+b");
    fseek(fp, sizeof(SuperBlock)+MAX_NODE*sizeof(Inode)+(long)sizeof(Dentry)*num,SEEK_SET);
    fwrite(&(main_dir.mainDirs[num]),sizeof(Dentry),1,fp);
    fclose(fp);

}
//每次退出系统必须保存，super_block  和  main_dir
void quitSave(){
    FILE *fp;
    fp = fopen("fileSystem.dat", "r+b");
    fseek(fp, 0,SEEK_SET);
    fwrite(&(super_block),sizeof(SuperBlock),1,fp);
    fseek(fp, sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE,SEEK_SET);
    fwrite(&(main_dir),sizeof(MainDir),1,fp);

    //保存usr信息
    fseek(fp,sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE+sizeof(MainDir)+sizeof(Dir)*MAX_DIR+SIZE_BLOCK*MAX_BLOCK,SEEK_SET);
    for(int i = 0;i< MAX_USRNUM;i++){
        fwrite(&(usr_tables[i]),sizeof(UsrTable),1,fp);
    }
    for(int i = 0;i<10;i++){
        fwrite(&(group_all[i]),sizeof(Group),1,fp);
    }
    fclose(fp);

}
