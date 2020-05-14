#include "Sapper.h"

One_Sapper::One_Sapper()
{

}

One_Sapper::~One_Sapper()
{
    for (int i = 0; i < rows; i++)
    {
        if(gridView[i])
            delete [] gridView[i];
    }
    for (int i = 0; i < rows; i++)
    {
        if(gridLogic[i])
            delete [] gridLogic[i];
    }
}

One_Sapper& One_Sapper::Instance()
{
    static One_Sapper One_Object;
    return One_Object;
}

void One_Sapper::set_rows(int param)
{
    rows = param;
    return;
}

int One_Sapper::get_rows()
{
    return rows;
}

void One_Sapper::set_cols(int param)
{
    cols = param;
    return;
}

int One_Sapper::get_cols()
{
    return cols;
}

void One_Sapper::set_mines(int param)
{
    mines = param;
    return;
}

int One_Sapper::get_mines()
{
    return mines;
}

void One_Sapper::set_seconds(int param)
{
    seconds = param;
    return;
}

int One_Sapper::get_seconds()
{
    return seconds;
}

void One_Sapper::set_timer_mode(bool param)
{
    timer_mode = param;
    return;
}

bool One_Sapper::get_timer_mode()
{
    return timer_mode;
}

void One_Sapper::reset()
{
    for (int i = 0; i < rows; i++)
    {
        if(gridView[i])
            delete [] gridView[i];
    }
    for (int i = 0; i < rows; i++)
    {
        if(gridLogic[i])
            delete [] gridLogic[i];
    }
    return;
}

void One_Sapper::mem_gridLogic()
{
    gridLogic = new int* [rows]; //Строки в массиве
    for (int i = 0; i < rows; i++)
        gridLogic[i] = new int [cols]; //Столбцы
    return;
}

void One_Sapper::mem_gridView()
{
    gridView = new int* [rows]; //Строки в массиве
    for (int i = 0; i < rows; i++)
        gridView[i] = new int [cols]; //Столбцы
    return;
}

void One_Sapper::set_gridLogic(int i, int j, int n)
{
    gridLogic[i][j] = n;
    return;
}

void One_Sapper::set_gridView(int i, int j, int n)
{
    gridView[i][j] = n;
    return;
}

int One_Sapper::get_gridLogic(int i, int j)
{
    return gridLogic[i][j];
}

int One_Sapper::get_gridView(int i, int j)
{
    return gridView[i][j];
}
