#include <SFML/Graphics.hpp>//Граф. библиотека
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "Sapper.h"

using namespace std;
using namespace sf;//Пространство имен граф. библиотеки SFML

bool is_number(string param)//Проверка строки на содержание числа
{
    for (int i = 0; i < param.length(); i++)
    {
        if (param[i] != 45)
        {
            if ((param[i] < 48) || (param[i] > 57))
                return false;
        }
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "rus");//Подключение кириллицы
    string answer;
    int param;
    int rows, cols, seconds, mines;
    One_Sapper &Game_Object = One_Sapper::Instance();//Появление главного игрового объекта
    while(1)//Главный игровой цикл
    {
        while(1)//Цикл выбора игры или выхода
        {
            system("cls");
            cout << "1 - Играть\n2 - Выйти\n";
            cin >> answer;
            if(is_number(answer) == false)
            {
                cout << "Неверный параметр!\n";
                system("pause");
                continue;
            }
            else
                param = atoi(answer.c_str());
            if(param > 2 || param < 1)
            {
                cout << "Неверный параметр!\n";
                system("pause");
                continue;
            }
            else
                break;
        }
        if(param == 2)//Выход
           break;
        else
        {
            while(1)//Выбор строк
            {
                system("cls");
                cout << "Введите количество строк (минимум 2, максимум 20):\n";
                cin >> answer;
                if(is_number(answer) == false)
                {
                    cout << "Неверный параметр!\n";
                    system("pause");
                    continue;
                }
                else
                    rows = atoi(answer.c_str());
                if(rows <= 1 || rows > 20)
                {
                    cout << "Неверный параметр!\n";
                    system("pause");
                    continue;
                }
                else
                {
                    Game_Object.set_rows(rows);
                    break;
                }
            }
            while(1)//Выбор столбцов
            {
                system("cls");
                cout << "Введите количество столбцов (минимум 2, максимум 40):\n";
                cin >> answer;
                if(is_number(answer) == false)
                {
                    cout << "Неверный параметр!\n";
                    system("pause");
                    continue;
                }
                else
                    cols = atoi(answer.c_str());
                if(cols <= 1 || cols > 40)
                {
                    cout << "Неверный параметр!\n";
                    system("pause");
                    continue;
                }
                else
                {
                    Game_Object.set_cols(cols);
                    break;
                }
            }
            while(1)//Выбор количества мин
            {
                system("cls");
                cout << "Введите количество мин:\n";
                cin >> answer;
                if(is_number(answer) == false)
                {
                    cout << "Неверный параметр!\n";
                    system("pause");
                    continue;
                }
                else
                    mines = atoi(answer.c_str());
                if(mines >= (Game_Object.get_cols() * Game_Object.get_rows()))
                {
                    cout << "Неверный параметр!\n";
                    system("pause");
                    continue;
                }
                else
                {
                    Game_Object.set_mines(mines);
                    break;
                }
            }
            while(1)//Выбор режима ограничения по времени
            {
                system("cls");
                cout << "Хотите ли Вы играть с ограничением по времени?\n";
                cout << "y - Да\n";
                cout << "n - Нет\n";
                cin >> answer;
                if(answer != "y" && answer != "n")
                {
                    cout << "Неверный параметр!\n";
                    system("pause");
                    continue;
                }
                if(answer == "n")
                {
                    Game_Object.set_timer_mode(false);
                    Game_Object.set_seconds(0);
                }
                else
                {
                    Game_Object.set_timer_mode(true);
                    while(1)//Выбор количества секунд, если режим выбора времени включен
                    {
                        system("cls");
                        cout << "Введите количество секунд (минимум 5):\n";
                        cin >> answer;
                        if(is_number(answer) == false)
                        {
                            cout << "Неверный параметр!\n";
                            system("pause");
                            continue;
                        }
                        else
                            seconds = atoi(answer.c_str());
                        if(seconds < 5)
                        {
                            cout << "Неверный параметр!\n";
                            system("pause");
                            continue;
                        }
                        else
                        {
                            Game_Object.set_seconds(seconds);
                            break;
                        }
                    }
                }
                break;
            }
            system("cls");
//-------------------Инициализация закончена, переходим к игре----------------------------------------------------
            Game_Object.mem_gridLogic();//Выделяем память для лог. массива
            Game_Object.mem_gridView();//Выделяем память для граф. данных
            srand(time(0));// Генератор случайных чисел
            int w = 32;//Ширина клетки
	        RenderWindow app(VideoMode(Game_Object.get_cols() * w, Game_Object.get_rows() * w), "Сапёр");//Открывается окно на нужный размер поля с подписью "Сапёр"
	        bool fail = false;//Флаг "Поражение", изначально отрицательный
	        bool fail_t = false;//Флаг "Поражение" по времени
	        bool win = false;//Флаг "Победа", изначально отрицательный
	        Texture t;//Загрузка текстуры
	        t.loadFromFile("C:\\images\\tiles.jpg");//Загрузка тексутры по расположению C:\images\tiles.jpg
	        Sprite s(t);//Спрайт
	        bool flag;//Вспомогательный флаг для цикла генерации кординат мин
	        int i_mines[Game_Object.get_mines()];//Массив для хранения строк ячеек, где будут мины
	        int j_mines[Game_Object.get_mines()];//Массив для хранения столбцов ячеек, где будут мины
            for(int i = 0; i < Game_Object.get_mines(); i++)//Обнуление этих массивов
                   i_mines[i] = j_mines[i] = 0;
            for(int i = 0; i < Game_Object.get_mines(); i++)//Заполнение массивов парами строк и столбцов, где будут мины
            {
                while(true)
                {
                    flag = true;
                    i_mines[i] = rand() % Game_Object.get_rows();//Теперь здесь находится какая-то координата строки
                    j_mines[i] = rand() % Game_Object.get_cols();//Теперь здесь находится какая-то координата столбца
                    for(int j = 0; j < Game_Object.get_mines(); j++)
                    {
                        if(i == j)//Не сравниваем текущие координаты с ними же
                           continue;//На следующую итерацию
                        else
                           if(i_mines[i] == i_mines[j] && j_mines[i] == j_mines[j])//Такие координаты уже существуют
                           {
                              flag = false;//Надо будет генерировать координаты заново
                              break;//Выходим из цикла
                           }
                    }
                    if(flag)//Если координаты уникальны, можем переходить к генерации следующих координат
                       break;//Выходим из бесконечного цикла
                }
            }
	        for(int i = 0; i < Game_Object.get_rows(); i++)//
		       for(int j = 0; j < Game_Object.get_cols(); j++)//Расставляем мины на поле
		       {
                  flag = false;//По умолчанию совпадений нет
                  Game_Object.set_gridView(i, j, 10);//Вид - неизвестная клетка
                  for(int k = 0; k < Game_Object.get_mines(); k++)//Проверка на совпадение с подготовленными координатами
                      if(i_mines[k] == i && j_mines[k] == j)//Есть совпадение с подготовленными координатами
                      {
                          flag = true;
                          Game_Object.set_gridLogic(i, j, 9);//Мина
                          break;//Можно выходить из этого цикла
                      }
                  if(!flag)
                    Game_Object.set_gridLogic(i, j, 0);//Ничего
		       }
            for(int i = 0; i < Game_Object.get_rows(); i++)//Подсчет мин вокруг каждой клетки
		       for(int j = 0; j < Game_Object.get_cols(); j++)//
		       {
			      int n = 0;//Определяем, какое число будет находиться в ячейке (сколько вокруг мин)
			      if(Game_Object.get_gridLogic(i, j) == 9)//Это мина, идем на следующую итерацию
                     continue;
			      if((i != Game_Object.get_rows() - 1) && (Game_Object.get_gridLogic(i + 1, j) == 9))//Снизу?
			         n++;
			      if((j != Game_Object.get_cols() - 1) && (Game_Object.get_gridLogic(i, j + 1) == 9))//Справа?
			         n++;
			      if((i != 0) && (Game_Object.get_gridLogic(i - 1, j) == 9))//Сверху?
			         n++;
			      if((j != 0) && (Game_Object.get_gridLogic(i, j - 1) == 9))//Слева?
			         n++;
                  if((i != Game_Object.get_rows() - 1) && (j != Game_Object.get_cols() - 1) && (Game_Object.get_gridLogic(i + 1, j + 1) == 9))//Юго-восток?
			         n++;
			      if((i != 0) && (j != 0) && (Game_Object.get_gridLogic(i - 1, j - 1) == 9))//Северо-запад?
			         n++;
			      if((i != 0) && (j != Game_Object.get_cols() - 1) && (Game_Object.get_gridLogic(i - 1, j + 1) == 9))//Северо-восток?
			         n++;
			      if((i != Game_Object.get_rows() - 1) && (j != 0) && (Game_Object.get_gridLogic(i + 1, j - 1) == 9))//Юго-запад?
			         n++;
			      Game_Object.set_gridLogic(i, j, n);//Итак, цифра помещается в лог. массив (макс. - 8)
		       }
            const clock_t start = clock();//Начало отчета
            while(app.isOpen())//Продолжается, пока графическое приложение запущено
	        {
               Event e;
               while(app.pollEvent(e))//Цикл обработки всех событий (мышь, клавиатура, фокус и пр.)
               {
                  if(Game_Object.get_timer_mode())
                  {
                      const double duration = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
                      if(duration >= Game_Object.get_seconds())
                      {
                          fail_t = true;
                          fail = false;
                          for(int i = 0; i < Game_Object.get_rows(); i++)
			                 for(int j = 0; j < Game_Object.get_cols(); j++)
                                Game_Object.set_gridView(i, j, Game_Object.get_gridLogic(i, j));
                      }
                  }
                  for(int i = 0; i < Game_Object.get_rows(); i++)//Проверка на победу
                  {
                     for(int j = 0; j < Game_Object.get_cols(); j++)
                     {
                        if(Game_Object.get_gridLogic(i, j) == 9)
                        {
                           if(Game_Object.get_gridView(i, j) != Game_Object.get_gridLogic(i, j))
                              win = true;
                           else
                           {
                              win = false;
                              break;
                           }
                        }
                        else
                        {
                           if(Game_Object.get_gridView(i, j) == Game_Object.get_gridLogic(i, j))
                              win = true;
                           else
                           {
                              win = false;
                              break;
                           }
                        }
                     }
                     if(!win)
                        break;
                  }
		          Vector2i pos = Mouse::getPosition(app);//Получение координат мыши относительно окна
		          int x = pos.x / w;//Координаты мыши
		          int y = pos.y / w;//
		          if(e.type == Event::MouseLeft || e.type == Event::LostFocus)//На новую итерацию основного цикла, если потеряли фокус или курсор вышел за окно
                     break;
			      if(e.type == Event::Closed)//Закрыть крестиком
				     app.close();
                  if(e.type == Event::KeyPressed && (fail_t || fail || win))//Закрыть, если проиграли или победили
                     app.close();
			      if(e.type == Event::MouseButtonPressed)//Опрос нажатия кнопки мыши
				     if(e.key.code == Mouse::Left)
                     {
                        if(fail_t || fail || win)//Закрыть, если проиграли или выиграли
                           app.close();
                        else
                           Game_Object.set_gridView(y, x, Game_Object.get_gridLogic(y, x));//Открыть клетку, если левая кнопка
                     }
				     else
                        if(e.key.code == Mouse::Right && Game_Object.get_gridView(y, x) == 10)
                           Game_Object.set_gridView(y, x, 11);//Если клетка неизвестна, ставим флажок
                        else
                           if(e.key.code == Mouse::Right && Game_Object.get_gridView(y, x) == 11)
                              Game_Object.set_gridView(y, x, 10);//Если флажок был, убираем его
		          app.clear(Color::Black);//Черный фон
		          for(int i = 0; i < Game_Object.get_rows(); i++)
			         for(int j = 0; j < Game_Object.get_cols(); j++)
                     {
				        if(Game_Object.get_gridView(y, x) == 9)//Попадаем на мину, проигрыш
                        {
                           Game_Object.set_gridView(i, j, Game_Object.get_gridLogic(i, j));
                           fail = true;
                           fail_t = false;
                        }
                        s.setTextureRect(IntRect(Game_Object.get_gridView(i, j) * w, 0, w, w));//Вырезка нужного сегмента текстуры
                        s.setPosition(j * w, i * w);//Установка заданной позиции
                        app.draw(s);//Отрисовка позиции
			         }
		          app.display();//Отображение всей сцены
               }
	        }
	        if(fail_t)
               cout << "Время вышло, Вы проиграли!\n";
	        if(fail)
               cout << "Вы проиграли!\n";
            if(win)
               cout << "Вы победили!\n";
            system("pause");
	        Game_Object.reset();//Освобождение динамически выделенной памяти
        }
    }
    cout << "Всего доброго!\n";
    return 0;
}
