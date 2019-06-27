#include "head.h"


void ls(char choice,string path){
    bool flag =true;
    int tempCur;
    if(path == " "){
        tempCur = cur_dir;
    }else{
        tempCur= findDentry(path,flag);
    }
    //tempCur= findDentry(path,flag);
    if(flag ==false){
        return;
    }


    if(choice !='l'){
      Dir tempDir = dir_sys[main_dir.mainDirs[tempCur].pointNum];
     for(int j =0;j<tempDir.sizeDir;j++){
        Dentry temp = main_dir.mainDirs[tempDir.pointNum[j]];
        cout<<temp.nameFile<<endl;
        //cout<<inode_sys[temp.inum].fileName<<endl;
     }

    }else{
        Dir tempDir = dir_sys[main_dir.mainDirs[tempCur].pointNum];
        for(int j=0;j<tempDir.sizeDir;j++){
            Dentry temp = main_dir.mainDirs[tempDir.pointNum[j]];
            Inode tempInode = inode_sys[temp.inum];
            if(temp.type =='d'){
                cout<<'d';
            }else if(temp.type =='l'){
                cout<<'l';
            }else{
                cout<<'-';
            }
            printPower(tempInode.powerUsr[0]);
            printPower(tempInode.powerUsr[1]);
            printPower(tempInode.powerUsr[2]);
            /*
            cout<<"rw-";
            if(tempInode.power[0]=='y'){
                cout<<'r';
            }else{
                cout<<'-';
            }
            if(tempInode.power[1]=='y'){
                cout<<'w';
            }else{
                cout<<'-';
            }
            if(tempInode.power[2]=='y'){
                cout<<'x';
            }else{
                cout<<'-';
            }
            cout<<" "<<tempInode.ownerName<<" "<<tempInode.otherName[0]<<" "<<tempInode.length<<" ";
            */
            cout<<" "<<tempInode.ownerName<<" "<<tempInode.groupName<<" "<<tempInode.length<<" ";
            cout<<temp.nameFile<<endl;
            //cout<<tempInode.fileName<<endl;

        }



    }
}
//进入目录
void cd(string path){
    if(path =="/"){
        cur_dir = 0;
        return;
    }
    //解析路径名
    char dataChar[30];
    strcpy(dataChar, path.c_str());
    //char dataChar[(path.data.length())] = path.data();
    vector<string> pathItem;
    string tempStr="";
    if(dataChar[0] == '/'){
        tempStr="/";
        //pathItem.push_back(tempStr);
        //tempStr = "";
    }
    for(int i = 0;i<(int)path.length();i++){
        if(dataChar[i] != '/' ){
            tempStr.push_back(dataChar[i]);
        }else if(dataChar[i]=='/'){
            pathItem.push_back(tempStr);
            tempStr = "";
        }

    }
    pathItem.push_back(tempStr);
    //根据路径找到目录
    int tempCur = cur_dir;
    if(pathItem[0] == "/"&& 1!=pathItem.size()){
        tempCur = 0 ;//从初始目录开始查找
        pathItem.erase(pathItem.begin());
    }
    bool tempFlag = false;
    //vector中存放的都是目录下即将进入的目录名称
    for(int i = 0;i < (int)pathItem.size();i++){
        Dir tempDir =dir_sys[main_dir.mainDirs[tempCur].pointNum];
        for(int j=0;j<tempDir.sizeDir;j++){
            string tempFile(main_dir.mainDirs[tempDir.pointNum[j]].nameFile);
            if(pathItem[i] == tempFile){
                tempFlag = true;
                tempCur = tempDir.pointNum[j];
                break;
            }
        }
        if(tempFlag == false){
            break;
        }
    }
    if(tempFlag == false){
        cout<<"there in no the file!"<<endl;
    }else{
        cur_dir = tempCur;
    }

}
//解析命令
bool analyse(string order){
    string instructions[MAX_ORDER]={"ls","cd","mkdir","su","mkfs","touch","vim","cat","cp",
                               "ln","usrDel","usrAdd","logout","rm","exit","chmod","vi","help","find","pwd"};//指令格式
    //存在的指令
    bool returnBool = true;
    vector<string> item;
    char data[50];
    strcpy(data,order.data());
    string tempStr ="";
    for(int i =0;i<(int)order.length();i++){
        if(data[i]!=' '){
            tempStr.push_back(data[i]);
        }else{
            item.push_back(tempStr);
            tempStr = "";
        }
    }
    item.push_back(tempStr);

    int choice = -1;
    for(int i =0;i<MAX_ORDER;i++){
        if(item[0]==instructions[i]){
            choice = i;
            break;
        }
    }

    char mode ='n';
    string tmpPath =" ";
    string source;
    string dest;
    int numPower;
    switch(choice){
    case 0:
        mode ='n';
        tmpPath =" ";
        if(item.size() == 1){
            //do nothing
        }else if(item.size()==2&&item[1]!="-l"){
            tmpPath = item[2];
        }else if(item.size()==2&&item[1]=="-l"){
            mode = 'l';
        }else if(item.size()==3&&item[1]=="-l"){
            mode = 'l';
            tmpPath = item[2];
        }
        ls(mode,tmpPath);
        break;
    case 1:
        tmpPath = item[1];
        cd(tmpPath);
        break;
    case 2:
        tmpPath = item[1];
        mkdir(tmpPath);
        break;
    case 3:
        tmpPath = item[1];
        su(tmpPath);
        break;
    case 4:
        format();
        break;
    case 5:
        tmpPath = item[1];
        touch(tmpPath);
        break;
    case 6:
        tmpPath = item[1];
        vim(tmpPath);
        break;
    case 7:
        tmpPath = item[1];
        cat(tmpPath);
        break;
    case 8:
        source = item[1];
        dest = item[2];
        cp(source,dest);
        break;
    case 9:

        if(item.size() == 4 && item[1]=="-s"){
            mode = 's';
            source = item[2];
            dest = item[3];
        }else if(item.size() == 3){
            mode = 'n';
            source = item[1];
            dest = item[2];
        }
        ln(mode,source,dest);
        break;
    case 10:
        tmpPath = item[1];
        usrDel(tmpPath);
        break;
    case 11:
        source = item[1];
        dest = item[2];
        userAdd(source,dest);
        break;
    case 12:
        login();
        break;
    case 13:
        tmpPath = item[1];
        rm(tmpPath);
        break;
    case 14:
        //exit();
        returnBool = false;
        break;
    case 15:
        //chmod();
        numPower = atoi(item[1].data());
        chmod(numPower,item[2]);
        break;
    case 16:
        //vi();
        break;
    case 17:
        //help
        break;
    case 18:
        if(item.size() <3){
            cout<<"wrong order"<<endl;
        }else if(item.size() == 3 && item[1]=="-name"){
            findFile(" ",item[2]);
        }else if(item.size() == 4 && item[2]=="-name"){
            findFile(item[1],item[3]);
        }
        break;
    case 19:
        printPath(cur_dir);
        break;
    default:
        if(choice == -1){
            cout<<"there is no the order !"<<endl;
        }

    }
    return returnBool;

}
//找到所给路径的main_dir 中的编号
int findDentry(string path,bool &flag){
    if(path =="/"){
        flag =true;
        return 0;
    }
    int numRecord;
    //解析路径名
    char dataChar[30];
    strcpy(dataChar, path.c_str());
    //char dataChar[(path.data.length())] = path.data();
    vector<string> pathItem;
    string tempStr="";
    if(dataChar[0] == '/'){
        tempStr="/";
        //pathItem.push_back(tempStr);
        //tempStr = "";
    }
    for(int i = 0;i<(int)path.length();i++){
        if(dataChar[i] != '/' ){
            tempStr.push_back(dataChar[i]);
        }else if(dataChar[i]=='/'){
            pathItem.push_back(tempStr);
            tempStr = "";
        }

    }
    pathItem.push_back(tempStr);
    //根据路径找到目录
    int tempCur = cur_dir;
    if(pathItem[0] == "/"&&1!=pathItem.size()){
        tempCur = 0 ;//从初始目录开始查找
        pathItem.erase(pathItem.begin());
    }
    bool tempFlag = false;
    //vector中存放的都是目录下即将进入的目录名称
    for(int i = 0;i < (int)pathItem.size();i++){
        Dir tempDir =dir_sys[main_dir.mainDirs[tempCur].pointNum];
        for(int j=0;j<tempDir.sizeDir;j++){
            string tempFile(main_dir.mainDirs[tempDir.pointNum[j]].nameFile);
            if(pathItem[i] == tempFile){
                tempFlag = true;
                tempCur = tempDir.pointNum[j];
                break;
            }
        }
        if(tempFlag == false){
            break;
        }
    }
    if(tempFlag == false){
        flag =false;
        cout<<"there in no the file!"<<endl;
    }else{
        numRecord = tempCur;
    }
    return numRecord;

}


void su(string name){
    string nameFile;
    string passwordFile;
    ifstream myFile ("usr.txt");
    bool flag =false;
    while( getline(myFile, nameFile) ){
        getline(myFile,passwordFile);
        if(name == nameFile){
            string password;
            cout<<"password: ";
            char ch;
            ch = _getch();
            while(ch!='\n'&&ch!='\r'){
                _putch('*');
                password += ch;
                ch =_getch();
            }
            cout<<endl;
            //cin>>password;
            if(password == passwordFile){
                //密码和账号都正确
                strcpy(usr_act.name,name.data());
                strcpy(usr_act.password,password.data());
                user_table.push_back(usr_act);
                cur_dir = 0;
                flag = true;
            }else{
                cout<<"password is wrong!"<<endl;
            }
            break;
        }

    }
    if(flag ==false){
        cout<<"the usr don't exit!"<<endl;
    }
    myFile.close();
    //system("cls");
}


//查看文件内容，包含查看硬链接，软链接
void cat(string path){
    bool flag =true;
    int tempCur;
    tempCur= findDentry(path,flag);
     if(flag ==false){
        return;
    }
    int pointPower = inode_sys[main_dir.mainDirs[tempCur].inum].inum;
    cout<<havePower(pointPower)<<usr_act.name<<endl;
    if(havePower(pointPower) < 2 && 0 !=strcmp(usr_act.name,"root")){
        cout<<"you don't have the power!"<<endl;
        return;
    }

    Inode tempInode = inode_sys[main_dir.mainDirs[tempCur].inum];
    if(tempInode.type != 'd'){
        FILE * fp;
        fp = fopen("fileSystem.dat", "r+b");
        int addr = tempInode.address;
        fseek(fp,sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE+sizeof(MainDir)+sizeof(Dir)*MAX_DIR+(long)SIZE_BLOCK*addr,SEEK_SET);

        while(tempInode.type == 'l'){
            char realpath[tempInode.length];
            fread(&realpath,sizeof(char)*tempInode.length,1,fp);
            //fread(&realPath,sizeof(char)*tempInode.length,1,fp);
            cout<<addr<<endl;
            cout<<realpath<<endl;
            string realPath(realpath);
            tempCur= findDentry(realPath,flag);

            if(flag ==false){
                return;

            }
            tempInode = inode_sys[main_dir.mainDirs[tempCur].inum];

            if(tempInode.type == 'd'){
                cout<<"it's a dirctory !"<<endl;
                fclose(fp);
                return ;
            }
            addr = tempInode.address;
            fseek(fp,sizeof(SuperBlock)+sizeof(Inode)*MAX_NODE+sizeof(MainDir)+sizeof(Dir)*MAX_DIR+(long)SIZE_BLOCK*addr,SEEK_SET);
        }
        cout<<"---------------------------"<<endl;
        for(int i=0;i<tempInode.length;i++){
            cout<<(char)fgetc(fp);
        }
        cout<<'\n'<<"---------------------------"<<endl;
        fclose(fp);

    }else{
        cout<<"it's a dirctory !"<<endl;
        return ;
    }

}
void printPower(int power){
    switch(power){
    case 1:
        cout<<"--x";
        break;
    case 2:
        cout<<"-r-";
        break;
    case 3:
        cout<<"-rx";
        break;
    case 4:
        cout<<"w--";
        break;
    case 5:
        cout<<"w-x";
        break;
    case 6:
        cout<<"wr-";
        break;
    case 7:
        cout<<"wrx";
        break;
    default:
        cout<<"wrong power!";

    }

}

