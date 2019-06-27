#include "head.h"
void login(){
    string usrName;
    string password;
    char ch;
    bool flag = true;
    while(flag){
        cout<<"localhost login: ";
        cin>>usrName;
        cout<<"password: ";
        ch = _getch();
        while(ch!='\n'&&ch!='\r'){
            _putch('*');
            password += ch;
            ch =_getch();
        }
        cout<<endl;
        string strFileName;
        string strFileWord;
        ifstream myFile ("usr.txt");
        //myFile.open("usr.txt");
        if(myFile.is_open()){
            while( getline(myFile, strFileName) ){
                getline(myFile,strFileWord);
                if(usrName == strFileName){
                if(password == strFileWord){
                    //密码和账号都正确
                    strcpy(usr_act.name,usrName.data());
                    strcpy(usr_act.password,password.data());
                    user_table.push_back(usr_act);
                    myFile.close();
                    return;
                }else{
                    //密码不正确，重新输入
                    password="";

                    break;
                }
                }

            }
             myFile.close();
        }else{
            //文件系统不存在，需要重建
            cout<<"cannot open the file!"<<endl;
            format();//格式化

        }
    }

}

void userAdd(string name,string password){
    string userName=usr_act.name;
    string userPass=usr_act.password;
    if(userName != "root"){
        cout<<"you don't have the power!"<<endl;
        return;
    }
    ofstream os;
    os.open("usr.txt",ios::app);
    os<<'\n'<<name<<endl;
    os<<password;
    os.close();
}
//删除用户将用户创建的文件ownerName 变成 null
void usrDel(string name){
    //删除掉usr表中数据 和 文件中的数据
    string nameNow = usr_act.name;
    if("root" != nameNow){
        cout<<"you dont't have the power!"<<endl;
        return ;
    }
    vector<string> data;
    string nameFile;
    string passwordFile;
    bool flag = false;
    ifstream myFile ("usr.txt");
    while( getline(myFile, nameFile) ){
        getline(myFile,passwordFile);
        if(name == nameFile){
            flag = true;
        }else{
            data.push_back(nameFile);
            data.push_back(passwordFile);
        }

    }
    if(flag == false){
        cout<<"the usr is not exist!"<<endl;
        return;
    }
    myFile.close();
    //
    remove("usr.txt");
    ofstream os("usr.txt");
    for(int i =0;i<(int)data.size();i++){
        os<<data[i]<<endl;
    }
    os.close();
    myFile.open("usr.txt");
    while( getline(myFile, nameFile) ){
        getline(myFile,passwordFile);
        cout<<nameFile<<" : "<<passwordFile<<endl;
    }

    myFile.close();

    //删除table中的inode创建者名字
    int numDelete = -1;
    for(int i= 0;i<MAX_USRNUM;i++){
        if( 0 ==strcmp(usr_tables[i].usrName,name.data())){
            numDelete = i;
            break;
        }
    }
    UsrTable tmp = usr_tables[numDelete];
    for(int i = 0;i<MAX_USRTABLE;i++){
        if(tmp.usrTable[i]!= -1){
            strcpy(inode_sys[tmp.usrTable[i]].ownerName,"null");
            saveInode(tmp.usrTable[i]);

        }
    }
    strcpy(usr_tables[numDelete].usrName,"null");
    for(int i =0;i<MAX_USRTABLE;i++){
        usr_tables[numDelete].usrTable[i] = -1;
    }
    //删除group中的名字
    for(int i = 0; i< 10;i++){
        string gName(group_all[i].groupName);
        if("null" != gName){
            for(int j = 0;j<10;j++){
                string uName(group_all[i].memberName[j]);
                if(uName == name){
                    strcpy(group_all[i].memberName[j],"null");
                }
            }
        }


    }


}
