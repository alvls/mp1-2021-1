/*Разработать прототип файлового менеджера с функцией показа файлов в заданном каталоге, упорядоченных по возрастанию / убыванию размера.

Входные данные :
Путь до директории, в которой необходимо отсортировать содержимое.
Метод сортировки.
Выходные данные :
Отсортированный список имен файлов с указанием размера.
Время сортировки.
Программа должна предоставлять пользователю возможность сменить метод сортировки и повторно формировать выходные данные.

Программа должна реализовывать диалог с пользователем посредством интерфейса, который включает :
возможность ввода пути до заданного каталога;
возможность выбора метода сортировки;
возможность просмотра отсортированного списка файлов с указанием размера.
Cписок методов сортировки :
пузырьком
выбором
вставками
слиянием
Хоара
Шелла
подсчетом*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  // из него функции
#include <time.h>  
#include <locale.h>
#include <omp.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>
void bubble();
void choice();
void insert();
void merge();// с этого начинается через три параметра
void arr_merger();
void Hoar();
void Shell();// два параметра, как и ниже
void counting();
int increment();
void printer();
void menu();
double worktime; //время работы сортировки (вывод через lf)
typedef struct fileinf
{
    char name[_MAX_PATH];
    int size;
} fileinf;
int count = 0;
fileinf* manager();
fileinf min_finder();
int main(void)
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    menu();
    system("pause");
}
void printer(fileinf* list, int size)
{
    int i, a, a_clean, flag = 0;
    printf("Массив отсортирован. Как вы хотите его вывести:\n1. По возрастанию\n2. По убыванию\n");
    do {
        do
        {
            scanf("%d", &a);
        } while (getchar() != '\n');
        switch (a)
        {
        case 1:
            printf("ИМЯ ФАЙЛА");
            for (i = 0; i < 69; i++)
                printf(" ");
            printf("РАЗМЕР\n");
            for (i = 0; i < size; i++)
            {
                printf("%-77s %d байт\n", list[i].name, list[i].size);
            }
            printf("\nВремя сортировки: %lf\n\n", worktime);
            break;
        case 2:
            printf("ИМЯ ФАЙЛА");
            for (i = 0; i < 69; i++)
                printf(" ");
            printf("РАЗМЕР\n");
            for (i = size - 1; i >= 0; i--)
            {
                printf("%-77s %d байт\n", list[i].name, list[i].size);
            }
            printf("\nВремя сортировки: %lf\n\n", worktime);
            break;
        default:
            printf("Вы выбрали не тот символ, напишите заново\n");
            printf("Напоминание:\n1. По возрастанию\n2. По убыванию\n");
            flag = 1;
        }
    } while (flag);
}
void menu()
{
    fileinf* list;
    setlocale(LC_ALL, "Russian");
    int a, a_clean, flag = 0;
    char answer;//ответ на вопрос о выходе из программы
    printf("");
    list = manager();
    printf("\n");
    do
    {
        if (flag == 2)
            printf("Вы можете снова выбрать метод сортировки: \n");
        else
            printf("Введите цифру - метод сортировки:\n");
        printf("1) Cортировка пузырьком\n2) Сортировка выбором\n3) Сортировка вставками\n4) Сортировка слиянием\n5) Сортировка Хоара\n6) Сортировка Шеллa\n7) Сортировка подсчётом \n8)Сменить сортируемый каталог\n");
        printf("Или выберите 0 для выхода\n");
        do
        {
            a_clean = scanf("%i", &a);
        } while (getchar() != '\n'&& a_clean);
        if (a >= 0 && a <= 8)
            switch (a)
            {
            case 0:
                printf("Вы уверены, что хотите выйти? y (английская раскладка) - да, любой другой символ - нет\n");
                scanf("%c", &answer);
                if (answer == 'y')
                {
                    printf("До свидания! Надеюсь, вы остались довольны!\n");
                    flag = 0;
                }
                else
                    flag = 2;
                break;
            case 1:
                printf("\n");
                bubble(list, count);
                printer(list, count);
                flag = 2;
                break;
            case 2:
                printf("\n");
                choice(list, count);
                printer(list, count);
                flag = 2;
                break;
            case 3:
                printf("\n");
                insert(list, count);
                printer(list, count);
                flag = 2;
                break;
            case 4:
                printf("\n");
                merge(list, count);
                printer(list, count);
                flag = 2;
                break;
            case 5:
                printf("\n");
                Hoar(list, 0, count - 1);
                printer(list, count);
                flag = 2;
                break;
            case 6:
                printf("\n");
                Shell(list, count);
                printer(list, count);
                flag = 2;
                break;
            case 7:
                printf("\n");
                counting(list, count);
                printer(list, count);
                flag = 2;
                break;
            case 8:
                printf("\n");
                menu();
                break;
            }
        else
        {
            printf("Ошибка ввода, введите ещё раз, пожалуйста\n");
            flag = 2;
        }
    } while (flag!=0);
}
fileinf* manager()// занимается нахождением файлов с заданной пользователем маской в каталоге, заданном пользователем
{
    //setlocale(LC_ALL, "Russian");
    struct _finddata_t c_file;//структура, состоящая из набора элементов (объединение разнотипных полей)
    intptr_t hFile;//
    char path[255];
    int flag = 0;
    int tmp_count = 0;
    int i, j;
    fileinf* list;
    printf("Введите путь до каталога, в котором нужно отыскать все файлы.\nВ пути для каталога использовать либо один обычный, либо один обратный слэш.\nВ конце поставьте слэш и звёздочку\n");
    do {
        gets(path);
        for (i = 0; i < 200 && path[i] != '\0'; i++)
        {
            if (path[i] == '/' && path[i + 1] != '/')
                path[i] = '\\';
        }
        if ((hFile = _findfirst(path, &c_file)) == -1L)// Находит первый файл по имени path, кладёт информацию в си файл, елсли не найден файл, то hFile даёт значение - 1 в типе лонг
        {
            printf("По указанному пути не было найдено ни одного файла!\n");
            printf("Введите путь ещё раз\n");
            flag = 1;
        }
        else
        {
            do
            {
                count++;
            } while (_findnext(hFile, &c_file) == 0);// вызов функции
            _findclose(hFile);// закрытие поиска
            count -= 2;
            list = (fileinf*)malloc(sizeof(fileinf) * count);
            if (list == 0)
                return;
            tmp_count = 0;
            hFile = _findfirst(path, &c_file);
            printf("ИМЯ ФАЙЛА");
            for (i = 0; i < 69; i++)
                printf(" ");
            printf("РАЗМЕР\n");
            do
            {
                if (tmp_count >= 2)
                {
                    strcpy(list[tmp_count - 2].name, c_file.name);
                    list[tmp_count - 2].size = c_file.size;
                    printf("%-77s", list[tmp_count - 2].name);////////////////////////////////////////////////////////////////////////////////////////////////можно украсить, если время будет. Ха, время будет))
                    printf(" %d\n", list[tmp_count - 2].size);
                }
                tmp_count++;
            } while (_findnext(hFile, &c_file) == 0);
            _findclose(hFile);
            return list;
        }
    } while (flag);
}
void bubble(fileinf* a, int size) // работает
{
    fileinf k;// для перемены местами элементов массива
    int i, j;// счётчики
    double t1, t2;//время
    int met;
    t1 = omp_get_wtime();//старт времени
    for (i = 0; i < size; i++)
    {
        met = 0;
        for (j = 0; j < size-i-1; j++) 
            if (a[j + 1].size < a[j].size)
            {
                met++;
                k = a[j + 1];
                a[j + 1] = a[j];
                a[j] = k;
            }
        if (met == 0)
            break;
    }
    t2 = omp_get_wtime();// финиш
    worktime = t2 - t1;// получение разности
}
void choice(fileinf* a, int size) // работает
{
    fileinf k;// для перемены местами структур
    int min_ind;// индекс минимального элемента
    int i, j;// счётчики
    double t1, t2;//время
    t1 = omp_get_wtime();
    for (i = 0; i < size; i++)
    { 
        min_ind = i; // присваиваем индексу минимума теперешний индекс
        k = a[min_ind]; //присваиваем дополнительной переменной значение i-того элемента
        for (j = i + 1; j < size; j++)	// цикл выбора наименьшего элемента
            if (a[j].size < k.size) // сравниваем очередной элемент с min_ind-ым
            {
                min_ind = j; // меняем индекс наименьшего элемента
                k = a[min_ind]; // меняем значение к, чтобы более эффективно сравнивать
            }
        a[min_ind] = a[i];
        a[i] = k;
    }
    t2 = omp_get_wtime();// финиш
    worktime = t2 - t1;// получение разности    
}
void insert(fileinf* a, int size) // работает
{
    fileinf k;// для перемены местами элементов массива
    int i, j;// счётчики
    double t1, t2;//время
    fileinf tmp; // временная переменная для хранения нулевого элемента
    tmp = a[0];
    t1 = omp_get_wtime();
    a[0] = min_finder(a, size);
    for (i = 1; i < size; i++)
    {
        k = a[i];
        for (j = i - 1; a[j].size > k.size; j--)
            a[j + 1] = a[j];
        a[j + 1] = k;
    }
    for (j = 1; j < size && a[j].size < tmp.size; j++) // нахождение места нулевого элемента
        a[j - 1] = a[j];
    a[j - 1] = tmp; // вставка нулевого элемента на отсортированное место
    t2 = omp_get_wtime(); // финиш
    worktime = t2 - t1;// получение разности
}
fileinf min_finder(fileinf* a, int size) // работает
{
    fileinf min;
    int i;
    min = a[0];
    for (i = 0; i < size; i++)
    {
        if (a[i].size < min.size)
            min = a[i];
    }
    return min;
}
void merge(fileinf* a, int size)//почему-то в рекурсии срабатывает исключение 
{
    double t1, t2;//время
    int step = 1; // шаг разбиения последовательности
    fileinf* temp; // дополнительный массив
    t1 = omp_get_wtime();
    temp = (int*)malloc(size * sizeof(fileinf));//создание массива
    while (step < size) // пока шаг меньше длины массива
    {
        int ind = 0; // индекс основного массива
        int left = 0; // левая граница массива
        int mid = left + step; // середина массива
        int right = left + step * 2; // правая граница массива
        int i; //  начало первого пути
        int j; // начало второго пути
        do
        {
            mid = mid < size ? mid : size; // сортируемый участок не выходит за границы последовательности
            right = right < size ? right : size;
            for (i = left, j = mid; i < mid && j < right; ) // пока i1 не дошёл до середины и i2 не дошёл до конца
            {
                if (a[i].size < a[j].size)
                {
                    temp[ind++] = a[i++]; // заполняем участка дополнительного массива
                } 
                else
                {
                    temp[ind++] = a[j++];
                }
            }
            // Или i < mid или j < right - только одно из условий для while может выполниться
            while (i < mid)
                temp[ind++] = a[i++]; // заносим оставшиеся элементы сортируемых участков
            while (j < right)
                temp[ind++] = a[j++]; // в результирующий массив
            left += step * 2; // перемещаемся на следующий сортируемый участок
            mid += step * 2;
            right += step * 2;
        } while (left < size); // пока левая граница сортируемого участка - в пределах последоватльности
        for (i = 0; i < size; i++) // получение отсортированного массива
            a[i] = temp[i];
        step *= 2; // увеличиваем в 2 раза шаг разбиения
    }
        free(temp);
        t2 = omp_get_wtime();// финиш
        worktime = t2 - t1;// получение разности
}
void Hoar(fileinf* a, int left, int right) // работает
{
    double t1, t2;//время
    int i = left, j = right;
    fileinf tmp;//опять этот дополнительный элемент
    fileinf x;
    t1 = omp_get_wtime();
    x = a[(left + right) / 2];
    // алгоритм основан на разделении массива на две части, одна из которых не превышает вторую
    // элементы одной части не превосходят элементов другой части. 
    // для этого создаётся опорный элемент, лучше случайный, но и одинаковый пойдёт
    do {
        while (a[i].size < x.size)
            i++;
        while (a[j].size > x.size)
            j--;

        if (i <= j)
        {
            if (i < j) //перестановка
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);
    // рекурсивные вызовы сортировки с разделом массива
    if (i < right)
        Hoar(a, i, right);
    if (left < j)
        Hoar(a, left, j);
    t2 = omp_get_wtime();// финиш
    worktime = t2 - t1;// получение разности
}
int increment(int inc[], int size) // работает
{
    int p1, p2, p3, s;
    p1 = p2 = p3 = 1;
    s = -1;
    do {
        if (++s % 2) {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        }
        else {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    } while (3 * inc[s] < size);
    return s > 0 ? --s : 0;// if (s>0) return --s; else return 0;
}
void Shell(fileinf* a, int size) // работает
{
    int k;// для перемены местами элементов массива
    int i, j;// счётчики
    double t1, t2;//время
    fileinf tmp;// доп элемент
    int seq[40], inc;
    int s;
    t1 = omp_get_wtime();
    // вычисление последовательности приращений
    s = increment(seq, size);
    while (s >= 0) {
        // сортировка вставками с инкрементами inc[] 
        inc = seq[s--];
        for (i = inc; i < size; i++) {
             tmp = a[i];
            for (j = i - inc; (j >= 0) && (a[j].size > tmp.size); j -= inc)
                a[j + inc] = a[j];
            a[j + inc] = tmp;
        }
    }
    t2 = omp_get_wtime();// финиш
    worktime = t2 - t1;// получение разности
}
void counting(fileinf* a, int size) 
{
    double t1, t2;//время
   // могу доказать, что подобие сортировки внизу было написано 30 ноября (я отправил себе её вконтакте на всякий случай). Просто оказалось, что я перепутал
    int i, j;//счётчики
    int size_of_tmp; //количество массивов (для первого счётчика)
    int* count; //массив размеров массивов
    //int* counter;//счётчик массива размеров массивов (где остановились в данном месте), для оптимизации
    fileinf** _tmp;//массив массивов, в котором будут храниться структуры
    const int nul = -1;//для того, чтобы можно было бы заменять
    int max = a[0].size, min = a[0].size, k = 0;// k для обычного массива
    t1 = omp_get_wtime();
    //nul.name = a[0].name;
    for (i = 0; i < size; i++)
        if (max < a[i].size)//находим максимальный элемент
        {
            max = a[i].size;
        }
        else
            if (min > a[i].size)//находим минимальный элемент
                min = a[i].size;
    size_of_tmp = max - min + 1;
    count = (int*)malloc(sizeof(int) * size_of_tmp);// массив для подсчёта
    for (i = 0; i < size_of_tmp; i++)
    {
        count[i] = 0;
    }
    for (i = 0; i < size; i++)
    {
        count[a[i].size - min]++; // получаем количество структур каждого размера
    }
    _tmp = (fileinf**)malloc(sizeof(fileinf*) * size_of_tmp);//массив массивов структур получает память
    for (i = 0; i < size_of_tmp; i++)
        _tmp[i] = (fileinf*)malloc(sizeof(fileinf) * count[i]);//для каждого временного массива структур пишем размер
    for (i = 0; i < size_of_tmp; i++)
        for (j = 0; j < count[i]; j++)
        {
            _tmp[i][j].size = nul; //обнуление
        }
    for (i = 0; i < size; i++)//до size, т.к. переносим все элементы из а
    {
        j = 0;
        while (_tmp[a[i].size - min][j].size != nul)
            j++;
        _tmp[a[i].size - min][j] = a[i];//заменяем обнулённый элемент на обычный
    }
    //Я не знаю, как у меня получилось создать штуки снизу, но я их оставлю на память. Кстати, каждый такой тройной слэш можно копировать через Shift+Enter
    /// <summary>
    ///
    /// </summary>
    /// <param name="a"></param>
    /// <param name="size"></param>
    k = 0;
    for (i = 0; i < size_of_tmp; i++)//перевод массива из временного хранилища в постоянное
        for (j = 0; j < count[i]; j++)//изменение до момента, когда всё заполнено
        {
            a[k] = _tmp[i][j];
            k++;
        }
    for (i = 0; i < size_of_tmp; i++)
        free(_tmp[i]);
    free(count); 
    /*int min, max, i, k = 0, c;
    fileinf* buff;
    int* count;
    min = max = a[0].size;
    for (i = 1; i < size; i++) {
        if (a[i].size < min)
            min = a[i].size;
        if (a[i].size > max)
            max = a[i].size;
    }
    c = max - min + 1;          
    buff = (fileinf*)malloc(sizeof (fileinf) * c * size);
    count = (int*)malloc(sizeof(int) * c);
    for (i = 0; i < c; i++)
        count[i] = 0;
    for (i = 0; i <size; i++)
        buff[size * (a[i].size - min) + count[a[i].size - min]++] = a[i];
    for (i = 0; i < c; i++)
        for(int j = 0; j < count[i] ; j++)
            a[k++] = buff[size * i + j];            
    free(count);
    free(buff);*/
    t2 = omp_get_wtime();// финиш
    worktime = t2 - t1;// получение разности
}
