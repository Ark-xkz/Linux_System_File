#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<conio.h>
#include<fstream>
#include<vector>

using namespace std;
#define MAIN_DENTRY 200         //主目录的dentry条数
#define MAX_DENTRY 20           //目录的最大条数
#define MAX_BLOCK 512           //块的最大数目
#define MAX_NODE 30             //最大的Node数目
#define MAX_DIR 30              //最大的Dir数目
#define MAX_OPENFILE 20         //最大的打开文件数目
#define MAX_ORDER 20            //最大的指令数
#define MAX_USRTABLE 50         //用户创建的最大文件数目
#define MAX_USRNUM 10

#define SIZE_BLOCK 512          //块的大小

//20(B)
struct User{
    char name[10];              //用户账号
    char password[10];          //用户的密码
};
//80(B)
struct Inode {
    int inum;                   //索引结点编号
    char fileName[10];          //文件名
    char type;                  //文件的类型
    int numParent;              //父目录的节点
    int length;                 //文件的长度
    int countNum;               //被引用的计数
    int address;                //存放文件的地址

    char groupName[10];
    int powerUsr[3];
    char ownerName[10];         //创建者name
    /*
    char otherName[3][10];      //组的name
    char power[3];              //组的权限
    */
    int change;                 //是否更改

};
//24(B)
struct Dentry {
    char type;                  //辨别是否是目录
    int inum;                   //对应的索引结点
    int pointNum;               //指向的节点或者 目录编号
    char nameFile[10];          //文件的名称
};
//正常的dir---84(B)
struct Dir {
    int pointNum[MAX_DENTRY];   //作为指向mainDir的指针
    int sizeDir;                //文件里项的条数
};
/*
//484(B)
struct Dir {
    struct Dentry dirs[MAX_DENTRY];
    int sizeDir;
};
*/
//4804(B)
struct MainDir {
    struct Dentry mainDirs[MAIN_DENTRY];
    int sizeDir;
};
//打开文件表项——24(B)
struct File{
    int inum;                   //inode节点号
    char fileName[10];          //文件的名称
    int mode;                   //读写模式 1-read|2-write|3_read&write
    int offset;                 //偏移量
};
//超级快68(B)
struct SuperBlock {
    int pointArr[17];           //模拟堆栈，指向空块编号
};
struct UsrTable {
    int usrTable[MAX_USRTABLE];
    char usrName[10];
};
struct Group {
    char groupName[10];
    char memberName[10][10];
};

//全局变量
extern UsrTable usr_tables[MAX_USRNUM];
extern Group  group_all[10];
extern SuperBlock super_block;         //内存超级块
extern MainDir main_dir;               //主目录
extern Inode inode_sys[MAX_NODE];      //内存inode
extern Dir dir_sys[MAX_DIR];           //内存目录
extern int cur_dir;                    //当前目录
extern User usr_act;                   //当前用户
extern vector<User> user_table;        //当前用户表
extern File open_table[20][MAX_OPENFILE];   //用户打开表
extern char flushTmp[SIZE_BLOCK];      //缓冲区

void login();                           //登录
void format();                          //格式化
void init();                            //初始化
void saveInode(int num);                //保存节点
int getEmptyBlock();                    //得到空块
void readBlock(int addr,char flush[]);  //读块内容
void writeBlock(char flush[], int addr);//写块内容到磁盘
void releaseBlock(SuperBlock &super_block,int addr);    //释放块
void userAdd(string name,string password); //增加用户
int getEmptyNode();                                     //得到空节点
void ls(char choice,string path);                                   //查看目录
void mkdir(string name);                                //mkdir
int getEmptyDentry();                                   //得到空主目录项
int getEmptyDir();                                      //得到空目录
void saveDir(int num);                                  //保存目录
void saveDentry(int num);                               //保存主目录项
void releaseDir(int num);
void releaseNode(int num);
void releaseDentry(int num);
void cd(string path);
bool analyse(string order);
void touch(string name);
void ln(char choice,string source,string dest);
int findDentry(string path,bool &flag);
void vim(string path);
void quitSave();
void cp(string source,string dest);
void rm(string path);
void deleteDir(int mainPoint);
void su(string name);
void usrDel(string name);
void cat(string path);
void findFile(string cover,string dest);
void findSubFile(int padir,string name);
void printPath(int numcur);
int havePower(int numInode);
void printPower(int power);
void chmod(int num,string path);
void addToUser(int numInode);
void delFromUsr(int numInode);
