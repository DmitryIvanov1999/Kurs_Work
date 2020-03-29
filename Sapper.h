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

    // N - размер пол€ по умолчанию (оно квадратное); M - число мин на поле

    #define N 10
    #define M 10

    // поле, и массив логических значений, обозначающий те пол€, что открыты
    int matrix[N][N];
    bool open[N][N];

    // провер€ет €чейку на мину; выход за пределы возвращает false
    bool mine(int i, int j){
        if((i>=0) && (i<N)){
            if((j>=0) && (j<N)){
                if(matrix[i][j]==-1) return true;
            }
        }
        return false;
    }

    // провер€ет €чейку на пустоту (true), выход за пределы массива возвращает false
    bool empty(int i, int j){
        if((i>=0) && (i<N)){
            if((j>=0) && (j<N)){
                if(matrix[i][j]==0) return true;
            }
        }
        return false;
    }

    // рекурсивна€ функци€, котора€ открывает пол€ в точке попадани€
    void clean(int i,int j){
        // проверим на выход за пределы массива
        if((i>=0) && (i<N)){
            if((j>=0) && (j<N)){
                // проверим, не было ли открыто поле раньше
                if(!open[i][j]){
                    // откроем
                    open[i][j]=true;
                    // если поле пустое (=0), просто пооткрываем всех его соседей
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
                    // если не пустое (!=0) открываем только пустых (=0) соседей
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

    // рисует "мину" - звездочку красного цвета
    void coutmine(HANDLE hConsole){
        SetConsoleTextAttribute(hConsole, 12);  // red text
        cout<<"* ";
        SetConsoleTextAttribute(hConsole, 7);   // white text
    }

    // рисует минное поле с учетом открытых и закрытых полей
    // и вспомогательные оси
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

    // функци€ завершает игру, вывед€ одну из двух надписей "Loser!" или "Winner!"
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

    // в случае проигрыша эта функци€ откроет все мины
    void openmines(){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(matrix[i][j]==-1) open[i][j]=true;
            }
        }
    }

    // провер€ет, все ли поле открыто, кроме мин (таково условие победы)
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
        // хэндл экна необходим дл€ рисовани€ цветного текста
        HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        // инициализаци€
        setlocale(LC_ALL, "rus");
        srand((int)time(NULL));
        while(1)
        {
        MINES=M+delta;
        // все чистим
        for(int c=0;c<100;c++){ matrix[c/10][c%10]=0; open[c/10][c%10]=false; }
        // заполн€ем массив пол€ минами
        for(int c=0;c<MINES;c++){
            do{
                i=rand()%N; j=rand()%N;
            }while(matrix[i][j]!=0);
            matrix[i][j]=-1;
        }
        // заполн€ем массив пол€ цифрами
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

        // главный игровой цикл
        while(true){
            // чистим экран от старого рисунка
            system("cls");
            cout << "—ейчас на поле " << N+delta << " мин!\n\n\n";
            // рисуем поле
            draw_matrix(hConsole);
            cout<<"\n";
            // запрашиваем координаты удара
            cout<<"¬ведите координаты удара: ";
            cin>>s;
            // переводим координаты в цифровой вид
            if((s[0]>=65) && (s[0]<=74)) j=s[0]-65;        // буква в промежутке от A до J
            else if((s[0]>=97) && (s[0]<=106)) j=s[0]-97;  // буква в промежутке от a до j
            else continue;                              // если введены неверные значени€, возврат в начало цикла
            if((s[1]>=48)&&(s[1]<=57)) i=s[1]-48;
            else continue;
            // далее провер€ем все восемь окрестных полей на пустые клетки
            // и если надо показываем некий кусок пол€
            clean(i,j);

            if(mine(i,j)){ openmines(); fin(hConsole, true); flag=false; break; }  // программа покидает цикл в случае проигрыша
            if(checkwin()){ fin(hConsole, false); flag=true; break; }                 // или победы
        }
        while(1)
        {
        system("cls");
        cout << "»грать дальше? (y/n)\n";
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
                cout << "¬ы очень удачливы!\n";
                break;
            }
            continue;
        }
        else
            break;
        }
        return 0;
    }*/
