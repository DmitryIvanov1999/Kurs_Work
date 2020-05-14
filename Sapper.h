#ifndef SAPPER_H_INCLUDED
#define SAPPER_H_INCLUDED
#include <time.h>
#include <stdlib.h>

class One_Sapper
{
private:
    int rows;//������
    int cols;//�������
    int mines;//����
    int **gridLogic;//���������� ������ ����
    int **gridView;//����������� ������ ����
    int seconds;//�������
    bool timer_mode;//On/Off Timer Mode
    One_Sapper();//������� �����������, ������� �� ����� ������� ������
    One_Sapper(const One_Sapper& root) = delete;//����������� ����������� ������
    One_Sapper& operator=(const One_Sapper&) = delete;//�������� ������������ ���� �� �����
public:
    ~One_Sapper();//����������
    static One_Sapper& Instance();//������� ���������� ������������ ������
    void set_rows(int param);//���������� ���������� �����
    int get_rows();//�������� ���������� �����
    void set_cols(int param);//���������� ���������� ��������
    int get_cols();//�������� ���������� ��������
    void set_mines(int param);//���������� ���������� ���
    int get_mines();//�������� ���������� ���
    void set_seconds(int param);//���������� ���������� ������
    int get_seconds();//�������� ���������� ������
    void set_timer_mode(bool param);//���������� On/Off Timer Mode
    bool get_timer_mode();//�������� On/Off Timer Mode
    void reset();//������� ������ ����� ��������� ����
    void mem_gridLogic();//��������� ������ ��� ������������� ������� gridLogic
    void mem_gridView();//��������� ������ ��� ������������� ������� gridView
    void set_gridLogic(int i, int j, int n);//���������� �������� ���������� ������ � ���. �������
    void set_gridView(int i, int j, int n);//���������� �������� ���������� ������ � ����. �������
    int get_gridLogic(int i, int j);//�������� ����� �� ����������� ���. ����
    int get_gridView(int i, int j);//�������� ����� �� ����������� ����. ����
};

#endif // SAPPER_H_INCLUDED
