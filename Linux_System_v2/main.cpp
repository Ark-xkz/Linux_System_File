#include "head.h"
SuperBlock super_block;         //�ڴ泬����
MainDir main_dir;               //��Ŀ¼
Inode inode_sys[MAX_NODE];      //�ڴ�inode
Dir dir_sys[MAX_DIR];           //�ڴ�Ŀ¼
int cur_dir;                    //��ǰĿ¼
User usr_act;                   //��ǰ�û�
vector<User> user_table;        //��ǰ�û���
File open_table[20][MAX_OPENFILE];   //�û��򿪱�
char flushTmp[SIZE_BLOCK];      //������
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

      cout<<"�Ƿ������û�? Y|N ";
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
              cout<<"�Ƿ������û�? Y|N ";
      cin>>judge;
      }
      cout<<"�Ƿ�ɾ���û� Y | N : ";
      cin>>judge;
      while(judge == 'Y'){
            string name;
        cout<<"name:";
        cin>>name;
        usrDel(name);
        cout<<"�Ƿ�ɾ���û�? Y|N ";
      cin>>judge;
      }

      cout<<"�Ƿ���Ҫ�ؽ�format����";
      char c;
      cin>>c;
      if(c=='y'){
        format();
      }
      init();

      //init(super_block,inode_sys[], main_dir, dir_sys[]);
      cout<<"�ɹ�"<<endl;
      cur_dir = 0;
      ls('l'," ");
      cout<<"�Ƿ񴴽�Ŀ¼Y|N��"<<endl;
      cin>>judge;
      while(judge == 'Y'){
        string name;
        cout<<"name:";
        cin>>name;
        mkdir(name);
        cout<<"�Ƿ񴴽�Ŀ¼Y|N��"<<endl;
        cin>>judge;
      }

      cout<<"�Ƿ񴴽��ļ�Y|N��"<<endl;
      cin>>judge;
      while(judge == 'Y'){
        string name;
        cout<<"name:";
        cin>>name;
        touch(name);
        cout<<"�Ƿ񴴽��ļ�Y|N��"<<endl;
        cin>>judge;
      }
      ls('l'," ");

      cout<<"�Ƿ�����µ�Ŀ¼��Y|N"<<endl;
      cin>>judge;
      while(judge == 'Y'){
        string name;
        cout<<"cd ";
        cin>>name;
        cd(name);
        ls('l'," ");
        char judge2;
        cout<<"�Ƿ񴴽�Ŀ¼Y|N��"<<endl;
        cin>>judge2;
        while(judge2 == 'Y'){
        string name2;
        cout<<"name:";
        cin>>name2;
        mkdir(name2);
        cout<<"�Ƿ񴴽�Ŀ¼Y|N��"<<endl;
        cin>>judge2;
      }
       cout<<"�Ƿ񴴽��ļ�Y|N��"<<endl;
      cin>>judge2;
      while(judge2 == 'Y'){
        string name;
        cout<<"name:";
        cin>>name;
        touch(name);
        cout<<"�Ƿ񴴽��ļ�Y|N��"<<endl;
        cin>>judge2;
      }
      cout<<"�Ƿ�д�ļ�Y|N��"<<endl;
      cin>>judge2;
      while(judge2 == 'Y'){
        string name;
        cout<<"vim:";
        cin>>name;
        vim(name);
        cout<<"�Ƿ�д�ļ�Y|N��"<<endl;
        cin>>judge2;
      }
      ls('l'," ");
      cout<<"�Ƿ�����µ�Ŀ¼��Y|N"<<endl;
      cin>>judge;
      }
      ls('l'," ");
      cout<<"�Ƿ񴴽�����Y|N��"<<endl;
      cin>>judge;
      while(judge == 'Y'){
        cout<<"������ s|Ӳ���� n";
        char lnc;
        cin>>lnc;
        string name;
        string name2;
        cout<<"ln ";
        cin>>name;
        cin>>name2;
        ln(lnc,name,name2);
        cout<<"�Ƿ񴴽�����Y|N��"<<endl;
        cin>>judge;
      }

      ls('l'," ");
      cout<<"�Ƿ�ɾ�� Y|N";
      cin>>judge;
      while(judge == 'Y'){
        string name;
        cout<<"rm:";
        cin>>name;
        rm(name);
        cout<<"�Ƿ񴴽�ɾ��Y|N��"<<endl;
        cin>>judge;
      }
   ls('l'," ");
    cout<<"�Ƿ��� Y|N";
      cin>>judge;
      while(judge == 'Y'){
        string src;
      string des;
      cout<<"cp:";
      cin>>src;
      cin>>des;
      cp(src,des);
        cout<<"�Ƿ񴴽�����Y|N��"<<endl;
        cin>>judge;
      }
    cout<<"�Ƿ��л��û�Y | N  ";
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
