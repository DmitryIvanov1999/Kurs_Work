#ifndef SAPPER_H_INCLUDED
#define SAPPER_H_INCLUDED
class One_Sapper
{
private:
    unsigned int rows;//Number of rows
    unsigned int cols;//Number of columns
    unsigned int mines;//Number of mines
    unsigned int **matrix;//Matrix of game field
    bool **open;//Matrix of boolean values
    unsigned int seconds;//Game Timer
    bool timer_mode;//Timer on/off
    One_Sapper();//Constructor can't create new objects
    One_Sapper(const One_Sapper& root) = delete;//Copy constructor is deleted
    One_Sapper& operator=(const One_Sapper&) = delete;//This operator is needed no more
public:
    ~One_Sapper();
    static One_Sapper& Instance();//Static method for only one object instance
    set_rows(unsigned int param);//Setting of rows' number
    unsigned int get_rows();//Getting of rows' number
    set_cols(unsigned int param);//Setting of columns' number
    unsigned int get_cols();//Getting of columns' number
    set_mines(unsigned int param);//Setting of mines' number
    unsigned int get_mines();//Getting of mines' number
    set_seconds(unsigned int param);//Setting of seconds' number
    unsigned int get_seconds();//Getting of seconds' number
    set_timer_mode(bool param);//Setting of game mode
    bool get_timer_mode();//Getting of game mode value
    set_matrix(unsigned int rows, unsigned int cols);//Creatimg od dynamic rows x cols matrix
};
#endif // SAPPER_H_INCLUDED


/*#include <iostream>
    #include <time.h>
    #include <windows.h>
    #include <conio.h>
    using namespace std;

    // N - ������ ���� �� ��������� (��� ����������); M - ����� ��� �� ����

    #define N 10
    #define M 10

    // ����, � ������ ���������� ��������, ������������ �� ����, ��� �������
    int matrix[N][N];
    bool open[N][N];

    // ��������� ������ �� ����; ����� �� ������� ���������� false
    bool mine(int i, int j){
        if((i>=0) && (i<N)){
            if((j>=0) && (j<N)){
                if(matrix[i][j]==-1) return true;
            }
        }
        return false;
    }

    // ��������� ������ �� ������� (true), ����� �� ������� ������� ���������� false
    bool empty(int i, int j){
        if((i>=0) && (i<N)){
            if((j>=0) && (j<N)){
                if(matrix[i][j]==0) return true;
            }
        }
        return false;
    }

    // ����������� �������, ������� ��������� ���� � ����� ���������
    void clean(int i,int j){
        // �������� �� ����� �� ������� �������
        if((i>=0) && (i<N)){
            if((j>=0) && (j<N)){
                // ��������, �� ���� �� ������� ���� ������
                if(!open[i][j]){
                    // �������
                    open[i][j]=true;
                    // ���� ���� ������ (=0), ������ ����������� ���� ��� �������
                    if(matrix[i][j]==0){
                        clean(i-1,j-1);
                        clean(i-1,j);
                        clean(i-1,j+1);
                        clean(i,j-1);
                        clean(i,j+1);
                        clean(i+1,j-1);
                        clean(i+1,j);
                        clean(i+1,j+1);
                    }
                    // ���� �� ������ (!=0) ��������� ������ ������ (=0) �������
                    else{
                        if(empty(i-1,j-1)) clean(i-1,j-1);
                        if(empty(i-1,j)) clean(i-1,j);
                        if(empty(i-1,j+1)) clean(i-1,j+1);
                        if(empty(i,j-1)) clean(i,j-1);
                        if(empty(i,j+1)) clean(i,j+1);
                        if(empty(i+1,j-1)) clean(i+1,j-1);
                        if(empty(i+1,j)) clean(i+1,j);
                        if(empty(i+1,j+1)) clean(i+1,j+1);
                    }
                }
            }
        }
    }

    // ������ "����" - ��������� �������� �����
    void coutmine(HANDLE hConsole){
        SetConsoleTextAttribute(hConsole, 12);  // red text
        cout<<"* ";
        SetConsoleTextAttribute(hConsole, 7);   // white text
    }

    // ������ ������ ���� � ������ �������� � �������� �����
    // � ��������������� ���
    void draw_matrix(HANDLE hConsole){
        SetConsoleTextAttribute(hConsole, 6);  // dark yellow text
        cout<<"  A B C D E F G H I J\n";
        SetConsoleTextAttribute(hConsole, 7);  // white text
        for(int x=0;x<N;x++){
            SetConsoleTextAttribute(hConsole, 6);  // dark yellow text
            cout<<x<<" ";
            SetConsoleTextAttribute(hConsole, 7);  // white text
            for(int y=0;y<N;y++){
                if(open[x][y]){
                    SetConsoleTextAttribute(hConsole, 8);  // gray text
                    if(matrix[x][y]==-1) coutmine(hConsole);
                    else if(matrix[x][y]==0) cout<<". ";
                    else cout<<matrix[x][y]<<" ";
                    SetConsoleTextAttribute(hConsole, 7);  // white text
                }
                else{

                    cout<<"# ";

                }
            }
            cout<<"\n";
        }
    }

    // ������� ��������� ����, ������ ���� �� ���� �������� "Loser!" ��� "Winner!"
    void fin(HANDLE hConsole, bool loser){
        COORD coord;
        coord.X = 33;
        coord.Y = 10;
        system("cls");
        draw_matrix(hConsole);
        SetConsoleCursorPosition(hConsole, coord);
        if(loser){
            SetConsoleTextAttribute(hConsole, 12);  // red text
            cout<<"L O S E R ! ! !";
            SetConsoleTextAttribute(hConsole, 7);  // white text
        }
        else{
            SetConsoleTextAttribute(hConsole, 10);  // green text
            cout<<"W I N N E R ! ! !";
            SetConsoleTextAttribute(hConsole, 7);  // white text
        }
        cout<<"\n\n\n\n";
        _getch();
    }

    // � ������ ��������� ��� ������� ������� ��� ����
    void openmines(){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(matrix[i][j]==-1) open[i][j]=true;
            }
        }
    }

    // ���������, ��� �� ���� �������, ����� ��� (������ ������� ������)
    bool checkwin(){
        for(int x=0;x<N;x++){
            for(int y=0;y<N;y++){
                if((matrix[x][y]!=-1) && (!open[x][y])) return false;
            }
        }
        return true;
    }


    int main()
    {
        bool flag;
        char ans='0';
        int delta=0;
        int MINES;
        int i,j,k=0;
        char s[3];
        // ����� ���� ��������� ��� ��������� �������� ������
        HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        // �������������
        setlocale(LC_ALL, "rus");
        srand((int)time(NULL));
        while(1)
        {
        MINES=M+delta;
        // ��� ������
        for(int c=0;c<100;c++){ matrix[c/10][c%10]=0; open[c/10][c%10]=false; }
        // ��������� ������ ���� ������
        for(int c=0;c<MINES;c++){
            do{
                i=rand()%N; j=rand()%N;
            }while(matrix[i][j]!=0);
            matrix[i][j]=-1;
        }
        // ��������� ������ ���� �������
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                if(matrix[i][j]!=-1){
                    k=0;
                    if(mine(i-1,j-1)) k++;
                    if(mine(i-1,j)) k++;
                    if(mine(i-1,j+1)) k++;
                    if(mine(i,j-1)) k++;
                    if(mine(i,j+1)) k++;
                    if(mine(i+1,j-1)) k++;
                    if(mine(i+1,j)) k++;
                    if(mine(i+1,j+1)) k++;
                    matrix[i][j]=k;
                }
            }
        }

        // ������� ������� ����
        while(true){
            // ������ ����� �� ������� �������
            system("cls");
            cout << "������ �� ���� " << N+delta << " ���!\n\n\n";
            // ������ ����
            draw_matrix(hConsole);
            cout<<"\n";
            // ����������� ���������� �����
            cout<<"������� ���������� �����: ";
            cin>>s;
            // ��������� ���������� � �������� ���
            if((s[0]>=65) && (s[0]<=74)) j=s[0]-65;        // ����� � ���������� �� A �� J
            else if((s[0]>=97) && (s[0]<=106)) j=s[0]-97;  // ����� � ���������� �� a �� j
            else continue;                              // ���� ������� �������� ��������, ������� � ������ �����
            if((s[1]>=48)&&(s[1]<=57)) i=s[1]-48;
            else continue;
            // ����� ��������� ��� ������ ��������� ����� �� ������ ������
            // � ���� ���� ���������� ����� ����� ����
            clean(i,j);

            if(mine(i,j)){ openmines(); fin(hConsole, true); flag=false; break; }  // ��������� �������� ���� � ������ ���������
            if(checkwin()){ fin(hConsole, false); flag=true; break; }                 // ��� ������
        }
        while(1)
        {
        system("cls");
        cout << "������ ������? (y/n)\n";
        cin >> ans;
        if(ans=='y'||ans=='n')
            break;
        else
            continue;
        }
        if(ans=='y')
        {
            if(flag==true)
                delta++;
            if(delta==90)
            {
                cout << "�� ����� ��������!\n";
                break;
            }
            continue;
        }
        else
            break;
        }
        return 0;
    }*/
