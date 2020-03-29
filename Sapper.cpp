#include "Sapper.h"
One_Sapper::One_Sapper(){}
bool One_Sapper::is_mine(int i, int j)
{
    if((i >= 0) && (i < rows))
    {
        if((j >= 0) && (j < cols))
        {
            if(matrix[i][j] == -1)
                return true;
        }
    }
    return false;
}
One_Sapper::~One_Sapper()
{
    for (int i = 0; i < rows; i++)
    {
        if(matrix[i])
            delete [] matrix[i];
    }
}
One_Sapper& One_Sapper::Instance()
{
    static One_Sapper One_Object;
    return One_Object;
}
One_Sapper::set_rows(int param)
{
    rows = param;
}
unsigned int One_Sapper::get_rows()
{
    return rows;
}
One_Sapper::set_cols(int param)
{
    cols = param;
}
unsigned int One_Sapper::get_cols()
{
    return cols;
}
One_Sapper::set_mines(int param)
{
    mines = param;
}
unsigned int One_Sapper::get_mines()
{
    return mines;
}
One_Sapper::set_seconds(int param)
{
    seconds = param;
}
unsigned int One_Sapper::get_seconds()
{
    return seconds;
}
One_Sapper::set_timer_mode(bool param)
{
    timer_mode = param;
}
bool One_Sapper::get_timer_mode()
{
    return timer_mode;
}
One_Sapper::set_matrix()
{
    srand(time(NULL));
    int i, j, k, m;
    matrix = new int* [rows];
    for (i = 0; i < rows; i++)
        matrix[i] = new int [cols];
    for(m = 0; m < mines ; m++)
    {
        do
        {
            i = rand() % rows;
            j = rand() % cols;
        }
        while(matrix[i][j] != 0);
        matrix[i][j] = -1;
    }
    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            if(matrix[i][j] != -1)
            {
                k=0;
                if(is_mine(i - 1, j - 1))
                    k++;
                if(is_mine(i - 1, j))
                    k++;
                if(is_mine(i - 1, j + 1))
                    k++;
                if(is_mine(i, j - 1))
                    k++;
                if(is_mine(i, j + 1))
                    k++;
                if(is_mine(i + 1, j - 1))
                    k++;
                if(is_mine(i + 1, j))
                    k++;
                if(is_mine(i + 1, j + 1))
                    k++;
                matrix[i][j] = k;
            }
        }
    }
}
