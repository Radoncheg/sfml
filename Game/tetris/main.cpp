#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int M = 20; // высота игрового поля
const int N = 10; // ширина игрового поля

int field[M][N] = {0}; // игровое поле

// Точка с целыми координатами
struct Point
{
    int x, y;
} a[4], b[4]; // Два вспомогательных массива

// Массив фигурок-тетрамино
int figures[7][4] =
    {
        1, 3, 5, 7, // I
        2, 4, 5, 7, // S
        3, 5, 4, 6, // Z
        3, 5, 4, 7, // T
        2, 3, 5, 7, // L
        3, 5, 7, 6, // J
        2, 3, 4, 5, // O
};

// Проверка соблюдения границ игрового поля и занятости ячеек другими фигурами
bool check()
{
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M)
            return false;
        else if (field[a[i].y][a[i].x])
            return false;
    return true;
};

int main()
{
    srand(time(0));

    //Создание окна разрешением 320 на 480 пикселей, которое будет называться Tetris
    RenderWindow window(VideoMode(320, 480), "Tetris");

    // Создание и загрузка текстур
    Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");      // квадратик
    t2.loadFromFile("images/background.png"); // задник
    t3.loadFromFile("images/frame.png");      // обрамление

    // Создание спрайтов
    Sprite s(t1), background(t2), frame(t3); // квадратик, задник и обрамление соответсвенно

    int dx = 0;            // Переменная для горизонтального смещения тетрамино
    bool rotate = false;   // Переменная для вращения
    int colorNum = 1;      // Номер цвета фигуры
    bool beginGame = true; // Флажок начала игры
    int n = rand() % 7;    // Задаем случайный тип фигуры (один из семи)
    float timer = 0;       // Счетчик таймера
    float delay = 0.3;     // Период времени между смещениями тетрамино вниз (в секундах)
    Clock clock;           // Часы (время, прошедшее с начала отсчета)

    // Главный цикл игры: выполняется, пока открыто окно
    while (window.isOpen())
    {
        // Получаем время, прошедшее с начала отсчета, и конвертируем его в секунды
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        // Если это первое тетрамино на поле
        if (beginGame)
        {
            beginGame = false; // больше это не начало игры
            n = rand() % 7;    // случайный тип фигуры
            for (int i = 0; i < 4; i++)
            {
                a[i].x = figures[n][i] % 2;
                a[i].y = figures[n][i] / 2;
            }
        }

        // Обрабатываем события в цикле
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) // пользователь нажал на «крестик» и хочет закрыть окно?
                window.close();          // да пожалуйста

            // Была ли нажата клавиша на клавиатуре?
            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::Up)
                    rotate = true; // если это кнопка вверх, то вращаем тетрамино
                else if (e.key.code == Keyboard::Left)
                    dx = -1; // если это кнопка влево, то смещаем влево
                else if (e.key.code == Keyboard::Right)
                    dx = 1; // если это кнопка вправо, то смещаем вправо
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
            delay = 0.05; // Если была нажата клавиша вниз, то ускоряем падение тетрамино

        // Смещаем каждый квадратик тетрамино в нужном напралении по горизонтали
        for (int i = 0; i < 4; i++)
        {
            b[i] = a[i];  // запоминаем изначальное расположение тетрамино
            a[i].x += dx; // смещаем
        }
        if (!check()) // если не соблюдаются границы
            for (int i = 0; i < 4; i++)
                a[i] = b[i]; // то возвращаемся обратно

        // Вращение
        if (rotate)
        {
            Point p = a[1]; //центр вращения
            for (int i = 0; i < 4; i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if (!check())
                for (int i = 0; i < 4; i++)
                    a[i] = b[i];
        }

        // Манипуляции со временем (падение фигурок)
        if (timer > delay) // Если прошел период обновления экрана
        {
            for (int i = 0; i < 4; i++) // то смещаем на одну позицию вниз
            {
                b[i] = a[i];
                a[i].y += 1;
            }
            if (!check())
            {
                for (int i = 0; i < 4; i++) // закрашиваем занятые ячейки поля нужным цветом
                    field[b[i].y][b[i].x] = colorNum;
                colorNum = 1 + rand() % 7; //меняяем цвет фигурки случайным образом
                int n = rand() % 7;        //меняяем тип фигурки случайным образом

                for (int i = 0; i < 4; i++)
                {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                    if (field[a[i].y][a[i].x])
                    {
                        window.close();
                    }
                }
            }
            timer = 0; // зануляем счетчик таймера
        }

        // Возвращаем прежние значения геймплейных параметров
        dx = 0;
        rotate = false;
        delay = 0.3;

        // Аннигиляция заполненных строк
        int k = M - 1;                  // координата самой нижней строки
        for (int i = M - 1; i > 0; i--) // проверяем строки снизу вверх
        {
            int count = 0; // счетчик закрашенных квадратиков
            for (int j = 0; j < N; j++)
            {
                if (field[i][j])           //если квадратик не пустой
                    count++;               // то
                field[k][j] = field[i][j]; // заменяем текущую строку той, что прямо над ней
            }
            if (count < N)
                k--;
        }

        // Наводим красоту
        window.draw(background); // ставим на фон картинку
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
            {
                if (field[i][j] == 0)
                    continue;
                s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18)); // разукрашиваем поле
                s.setPosition(j * 18, i * 18);                          // устанавливаем позицию каждой ячейки
                s.move(28, 31);                                         // смещаем начало координат поля соответсвенно текстуре задника
                window.draw(s);                                         // отрисовка
            }
        for (int i = 0; i < 4; i++) // делаем то же самое для отдельного тетрамино
        {
            s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            s.setPosition(a[i].x * 18, a[i].y * 18);
            s.move(28, 31);
            window.draw(s);
        }
        window.draw(frame); // ставим обрамление
        window.display();   // Отображаем окно
    }
    return 0;
}