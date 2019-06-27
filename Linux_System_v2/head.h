#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<conio.h>
#include<fstream>
#include<vector>

using namespace std;
#define MAIN_DENTRY 200         //��Ŀ¼��dentry����
#define MAX_DENTRY 20           //Ŀ¼���������
#define MAX_BLOCK 512           //��������Ŀ
#define MAX_NODE 30             //����Node��Ŀ
#define MAX_DIR 30              //����Dir��Ŀ
#define MAX_OPENFILE 20         //���Ĵ��ļ���Ŀ
#define MAX_ORDER 20            //����ָ����
#define MAX_USRTABLE 50         //�û�����������ļ���Ŀ
#define MAX_USRNUM 10

#define SIZE_BLOCK 512          //��Ĵ�С

//20(B)
struct User{
    char name[10];              //�û��˺�
    char password[10];          //�û�������
};
//80(B)
struct Inode {
    int inum;                   //���������
    char fileName[10];          //�ļ���
    char type;                  //�ļ�������
    int numParent;              //��Ŀ¼�Ľڵ�
    int length;                 //�ļ��ĳ���
    int countNum;               //�����õļ���
    int address;                //����ļ��ĵ�ַ

    char groupName[10];
    int powerUsr[3];
    char ownerName[10];         //������name
    /*
    char otherName[3][10];      //���name
    char power[3];              //���Ȩ��
    */
    int change;                 //�Ƿ����

};
//24(B)
struct Dentry {
    char type;                  //����Ƿ���Ŀ¼
    int inum;                   //��Ӧ���������
    int pointNum;               //ָ��Ľڵ���� Ŀ¼���
    char nameFile[10];          //�ļ�������
};
//������dir---84(B)
struct Dir {
    int pointNum[MAX_DENTRY];   //��Ϊָ��mainDir��ָ��
    int sizeDir;                //�ļ����������
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
//���ļ������24(B)
struct File{
    int inum;                   //inode�ڵ��
    char fileName[10];          //�ļ�������
    int mode;                   //��дģʽ 1-read|2-write|3_read&write
    int offset;                 //ƫ����
};
//������68(B)
struct SuperBlock {
    int pointArr[17];           //ģ���ջ��ָ��տ���
};
struct UsrTable {
    int usrTable[MAX_USRTABLE];
    char usrName[10];
};
struct Group {
    char groupName[10];
    char memberName[10][10];
};

//ȫ�ֱ���
extern UsrTable usr_tables[MAX_USRNUM];
extern Group  group_all[10];
extern SuperBlock super_block;         //�ڴ泬����
extern MainDir main_dir;               //��Ŀ¼
extern Inode inode_sys[MAX_NODE];      //�ڴ�inode
extern Dir dir_sys[MAX_DIR];           //�ڴ�Ŀ¼
extern int cur_dir;                    //��ǰĿ¼
extern User usr_act;                   //��ǰ�û�
extern vector<User> user_table;        //��ǰ�û���
extern File open_table[20][MAX_OPENFILE];   //�û��򿪱�
extern char flushTmp[SIZE_BLOCK];      //������

void login();                           //��¼
void format();                          //��ʽ��
void init();                            //��ʼ��
void saveInode(int num);                //����ڵ�
int getEmptyBlock();                    //�õ��տ�
void readBlock(int addr,char flush[]);  //��������
void writeBlock(char flush[], int addr);//д�����ݵ�����
void releaseBlock(SuperBlock &super_block,int addr);    //�ͷſ�
void userAdd(string name,string password); //�����û�
int getEmptyNode();                                     //�õ��սڵ�
void ls(char choice,string path);                                   //�鿴Ŀ¼
void mkdir(string name);                                //mkdir
int getEmptyDentry();                                   //�õ�����Ŀ¼��
int getEmptyDir();                                      //�õ���Ŀ¼
void saveDir(int num);                                  //����Ŀ¼
void saveDentry(int num);                               //������Ŀ¼��
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
