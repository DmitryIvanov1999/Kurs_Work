#ifndef SAPPER_H_INCLUDED
#define SAPPER_H_INCLUDED
#include <time.h>
#include <stdlib.h>

class One_Sapper
{
private:
    int rows;//Строки
    int cols;//Столбцы
    int mines;//Мины
    int **gridLogic;//Логический массив поля
    int **gridView;//Графический массив поля
    int seconds;//Секунды
    bool timer_mode;//On/Off Timer Mode
    One_Sapper();//Обычный конструктор, который не может создать объект
    One_Sapper(const One_Sapper& root) = delete;//Конструктор копирования удален
    One_Sapper& operator=(const One_Sapper&) = delete;//Оператор присваивания тоже не нужен
public:
    ~One_Sapper();//Деструктор
    static One_Sapper& Instance();//Функция производит единственный объект
    void set_rows(int param);//Установить количество строк
    int get_rows();//Получить количество строк
    void set_cols(int param);//Установить количество столбцов
    int get_cols();//Получить количество столбцов
    void set_mines(int param);//Установить количество мин
    int get_mines();//Получить количество мин
    void set_seconds(int param);//Установить количество секунд
    int get_seconds();//Получить количество секунд
    void set_timer_mode(bool param);//Установить On/Off Timer Mode
    bool get_timer_mode();//Получить On/Off Timer Mode
    void reset();//Очистка данных после окончания игры
    void mem_gridLogic();//Выделение памяти для динамического массива gridLogic
    void mem_gridView();//Выделение памяти для динамического массива gridView
    void set_gridLogic(int i, int j, int n);//Установить значение конкретной ячейке в лог. массиве
    void set_gridView(int i, int j, int n);//Установить значение конкретной ячейке в граф. массиве
    int get_gridLogic(int i, int j);//Получаем число по координатам лог. поля
    int get_gridView(int i, int j);//Получаем число по координатам граф. поля
};

#endif // SAPPER_H_INCLUDED
