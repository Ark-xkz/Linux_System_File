#include "head.h"
/*
SuperBlock super_block;
Inode inode_sys[MAX_NODE];
MainDir main_dir;
Dir dir_sys[MAX_DIR];
*/

void init(){
    FILE *fp;
    fp = fopen("fileSystem.dat", "r+b");
    fread(&super_block, sizeof(SuperBlock), 1, fp);
    //show me
    for(int i=0;i<17;i++){
        cout<<super_block.pointArr[i]<<endl;
    }

    for(int i=0;i<MAX_NODE;i++){
        fread(&(inode_sys[i]), sizeof(Inode), 1, fp);
    }
    //show me
    for(int i=0;i<MAX_NODE;i++){
        cout<<inode_sys[i].fileName<<":"<<inode_sys[i].inum<<endl;
    }
    fread(&main_dir,sizeof(MainDir),1,fp);
    cout<<"size of Main:"<<main_dir.sizeDir<<endl;
    for(int i=0;i< 20;i++){
        cout<<"name: "<<main_dir.mainDirs[i].nameFile<<endl;
    }
    for(int i=0;i<MAX_DIR;i++){
        fread(&(dir_sys[i]),sizeof(Dir),1,fp);
    }
    for(int i=0;i<MAX_DIR;i++){
        cout<<"DIR:->"<<dir_sys[i].sizeDir<<" "<<dir_sys[i].pointNum[0]<<endl;
    }

    int testNum[32][17];
    for(int i =0;i<32;i++){
        fseek(fp,sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE+sizeof(MainDir)+sizeof(Dir)*MAX_DIR+(long)SIZE_BLOCK*i,SEEK_SET);
        for(int j=0;j<17;j++){
            fread(&(testNum[i][j]),sizeof(int),1,fp);
        }
    }
    for(int i=0;i<32;i++){
        cout<<"Block record:"<<i<<": ";
        for(int j=0;j<17;j++){
            cout<<testNum[i][j]<<" ";
        }
        cout<<endl;
    }

    for(int i = 0;i< MAX_USRNUM;i++){
        fseek(fp,sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE+sizeof(MainDir)+sizeof(Dir)*MAX_DIR+SIZE_BLOCK*MAX_BLOCK+(long)sizeof(UsrTable)*i,SEEK_SET);
        fread(&(usr_tables[i]),sizeof(UsrTable),1,fp);
    }
    for(int i =0;i<10;i++){
        fseek(fp,sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE+sizeof(MainDir)+sizeof(Dir)*MAX_DIR+SIZE_BLOCK*MAX_BLOCK+(long)sizeof(UsrTable)*MAX_USRNUM+sizeof(Group)*i,SEEK_SET);
        fread(&(group_all[i]),sizeof(Group),1,fp);
    }
    fclose(fp);

    //Çå¿Õ»º´æÇø
    for(int i =0;i<SIZE_BLOCK;i++){
        flushTmp[i] = '\0';
    }

}

