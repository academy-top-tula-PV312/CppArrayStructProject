#include <iostream>

template <typename T>
struct Array
{
    T* items = nullptr;
    int size = 0;
};

Array<int>& ArrayIntCreate(int size);

void ArrayIntInit(Array<int> array);
void ArrayIntPrint(Array<int> array);

template <typename T>
void ArrayPushBack(Array<T>& array, T value);

template <typename T>
void ArrayPushFront(Array<T>& array, T value);

template <typename T>
void ArrayInsert(Array<T>& array, T value, int index);



int main()
{
    srand(time(nullptr));

    Array<int> array = ArrayIntCreate(10);
    ArrayIntInit(array);
    ArrayIntPrint(array);

    ArrayPushFront(array, 100);
    ArrayPushBack(array, 200);
    ArrayInsert(array, 300, 6);

    ArrayIntPrint(array);
}



Array<int>& ArrayIntCreate(int size)
{
    Array<int> array;

    array.items = new int[size];
    array.size = size;

    return array;
}

void ArrayIntInit(Array<int> array)
{
    for (int i{}; i < array.size; i++)
        array.items[i] = rand() % 100;
}

void ArrayIntPrint(Array<int> array)
{
    for (int i{}; i < array.size; i++)
        std::cout << array.items[i] << " ";
    std::cout << "\n";
}

template<typename T>
void ArrayPushBack(Array<T>& array, T value)
{
    T* itemsNew = new T[array.size + 1];

    for (int i{}; i < array.size; i++)
        itemsNew[i] = array.items[i];

    itemsNew[array.size++] = value;

    if(array.items)
        delete[] array.items;
    array.items = itemsNew;
}

template<typename T>
void ArrayPushFront(Array<T>& array, T value)
{
    T* itemsNew = new T[array.size + 1];

    for (int i{}; i < array.size; i++)
        itemsNew[i + 1] = array.items[i];

    itemsNew[0] = value;

    if (array.items)
        delete[] array.items;
    array.items = itemsNew;

    array.size++;
}

template<typename T>
void ArrayInsert(Array<T>& array, T value, int index)
{
    if (index <= 0)
    {
        ArrayPushFront(array, value);
        return;
    }

    if (index >= array.size)
    {
        ArrayPushBack(array, value);
        return;
    }

    T* itemsNew = new T[array.size + 1];

    for (int i{}; i < index; i++)
        itemsNew[i] = array.items[i];

    itemsNew[index] = value;

    for (int i{ index }; i < array.size; i++)
        itemsNew[i + 1] = array.items[i];

    if (array.items)
        delete[] array.items;
    array.items = itemsNew;

    array.size++;
}
