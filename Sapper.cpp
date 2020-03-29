#include "Sapper.h"
One_Sapper::One_Sapper(){}
One_Sapper::~One_Sapper()
{

}
One_Sapper& One_Sapper::Instance()
{
    static One_Sapper One_Object;
    return One_Object;
}
One_Sapper::set_rows(unsigned int param)
{
    rows = param;
}
unsigned int One_Sapper::get_rows()
{
    return rows;
}
One_Sapper::set_cols(unsigned int param)
{
    cols = param;
}
unsigned int One_Sapper::get_cols()
{
    return cols;
}
One_Sapper::set_mines(unsigned int param)
{
    mines = param;
}
unsigned int One_Sapper::get_mines()
{
    return mines;
}
One_Sapper::set_seconds(unsigned int param)
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
One_Sapper::set_matrix(unsigned int rows, unsigned int cols)
{
    matrix = new unsigned int* [rows];
    for (int i = 0; i < rows; i++)
        matrix[i] = new unsigned int [cols];
}
