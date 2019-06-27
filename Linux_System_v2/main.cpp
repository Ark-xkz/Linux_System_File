#include "head.h"
SuperBlock super_block;         //内存超级块
MainDir main_dir;               //主目录
Inode inode_sys[MAX_NODE];      //内存inode
Dir dir_sys[MAX_DIR];           //内存目录
int cur_dir;                    //当前目录
User usr_act;                   //当前用户
vector<User> user_table;        //当前用户表
File open_table[20][MAX_OPENFILE];   //用户打开表
char flushTmp[SIZE_BLOCK];      //缓冲区
UsrTable usr_tables[MAX_USRNUM];
Group  group_all[10];

int main()
{
    /*int tmp =0;
    string t ="";
    while(t !="e"){
        cout<<"come in"<<endl;
        getline(cin,t);
        tmp++;
        cout<<tmp<<" "<<t<<endl;
    }
    return 0;
    */
      //format();
      login();
      init();
      bool judgeFlag = true;
      string order;
      int num =1;
      while(judgeFlag == true){
        if(num != 0){
            cout<<"["<<usr_act.name<<"@localhost "<<main_dir.mainDirs[cur_dir].nameFile<<"]# ";
        }
        //cout<<"["<<usr_act.name<<"@localhost "<<main_dir.mainDirs[cur_dir].nameFile<<"]# ";
        getline(cin,order);
        //num++;
        //cout<<"num:"<<num<<endl;
        if(order.length() == 0){
            num = 0;
            continue;
        }else{
            num = 1;
        }
        judgeFlag = analyse(order);
      }

      /*
      int len = user_table.size();
      for(int i=0;i<len;i++){
        User temp = user_table.at(i);
        cout<<temp.name<<" "<<temp.password<<endl;
      }

      cout<<"是否增添用户? Y|N ";
      char judge;
      cin>>judge;
      while(judge == 'Y'){
            string name;
        string pass;
        cout<<"name:";
        cin>>name;
        cout<<"pass";
        cin>>pass;
        userAdd( name,pass);
              cout<<"是否增添用户? Y|N ";
      cin>>judge;
      }
      cout<<"是否删除用户 Y | N : ";
      cin>>judge;
      while(judge == 'Y'){
            string name;
        cout<<"name:";
        cin>>name;
        usrDel(name);
        cout<<"是否删除用户? Y|N ";
      cin>>judge;
      }

      cout<<"是否需要重建format（）";
      char c;
      cin>>c;
      if(c=='y'){
        format();
      }
      init();

      //init(super_block,inode_sys[], main_dir, dir_sys[]);
      cout<<"成功"<<endl;
      cur_dir = 0;
      ls('l'," ");
      cout<<"是否创建目录Y|N？"<<endl;
      cin>>judge;
      while(judge == 'Y'){
        string name;
        cout<<"name:";
        cin>>name;
        mkdir(name);
        cout<<"是否创建目录Y|N？"<<endl;
        cin>>judge;
      }

      cout<<"是否创建文件Y|N？"<<endl;
      cin>>judge;
      while(judge == 'Y'){
        string name;
        cout<<"name:";
        cin>>name;
        touch(name);
        cout<<"是否创建文件Y|N？"<<endl;
        cin>>judge;
      }
      ls('l'," ");

      cout<<"是否进入新的目录？Y|N"<<endl;
      cin>>judge;
      while(judge == 'Y'){
        string name;
        cout<<"cd ";
        cin>>name;
        cd(name);
        ls('l'," ");
        char judge2;
        cout<<"是否创建目录Y|N？"<<endl;
        cin>>judge2;
        while(judge2 == 'Y'){
        string name2;
        cout<<"name:";
        cin>>name2;
        mkdir(name2);
        cout<<"是否创建目录Y|N？"<<endl;
        cin>>judge2;
      }
       cout<<"是否创建文件Y|N？"<<endl;
      cin>>judge2;
      while(judge2 == 'Y'){
        string name;
        cout<<"name:";
        cin>>name;
        touch(name);
        cout<<"是否创建文件Y|N？"<<endl;
        cin>>judge2;
      }
      cout<<"是否写文件Y|N？"<<endl;
      cin>>judge2;
      while(judge2 == 'Y'){
        string name;
        cout<<"vim:";
        cin>>name;
        vim(name);
        cout<<"是否写文件Y|N？"<<endl;
        cin>>judge2;
      }
      ls('l'," ");
      cout<<"是否进入新的目录？Y|N"<<endl;
      cin>>judge;
      }
      ls('l'," ");
      cout<<"是否创建链接Y|N？"<<endl;
      cin>>judge;
      while(judge == 'Y'){
        cout<<"软链接 s|硬链接 n";
        char lnc;
        cin>>lnc;
        string name;
        string name2;
        cout<<"ln ";
        cin>>name;
        cin>>name2;
        ln(lnc,name,name2);
        cout<<"是否创建链接Y|N？"<<endl;
        cin>>judge;
      }

      ls('l'," ");
      cout<<"是否删除 Y|N";
      cin>>judge;
      while(judge == 'Y'){
        string name;
        cout<<"rm:";
        cin>>name;
        rm(name);
        cout<<"是否创建删除Y|N？"<<endl;
        cin>>judge;
      }
   ls('l'," ");
    cout<<"是否复制 Y|N";
      cin>>judge;
      while(judge == 'Y'){
        string src;
      string des;
      cout<<"cp:";
      cin>>src;
      cin>>des;
      cp(src,des);
        cout<<"是否创建复制Y|N？"<<endl;
        cin>>judge;
      }
    cout<<"是否切换用户Y | N  ";
    cin>>judge;
    if(judge == 'Y'){
        string name;
        cout<<"su ";
        cin>>name;
        su(name);
    }
    ls('l'," ");
*/
      quitSave();
    return 0;
}
