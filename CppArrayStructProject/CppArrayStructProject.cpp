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

template <typename T>
T ArrayPopBack(Array<T>& array);


int BracketsValidate(char* str);
int CharIndex(const char* str, char symbol);



int main()
{
    srand(time(nullptr));

    char* str = new char[13];
    strcpy_s(str, 13, "[({})()[]}]");

    std::cout << BracketsValidate(str);
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

template<typename T>
T ArrayPopBack(Array<T>& array)
{
    T pop = array.items[array.size - 1];

    T* itemsNew = new T[--array.size];

    for (int i{}; i < array.size; i++)
        itemsNew[i] = array.items[i];

    if (array.items)
        delete[] array.items;
    array.items = itemsNew;

    return pop;
}


int BracketsValidate(char* str)
{
    char bracketsOpen[]  { "{([" };
    char bracketsClose[] { "})]" };

    Array<char> stack;

    int i{};
    while (str[i])
    {
        //if (str[i] != bracketOpen && str[i] != bracketClose)
        if(!strchr(bracketsOpen, str[i]) && !strchr(bracketsClose, str[i]))
        {
            i++;
            continue;
        }

        if (strchr(bracketsOpen, str[i]))
            ArrayPushBack(stack, str[i]);
        
        if (strchr(bracketsClose, str[i]))
        {
            if (!stack.size)
                return i;
            else
            {
                int typeClose = CharIndex(bracketsClose, str[i]);
                int typeOpen = CharIndex(bracketsOpen, ArrayPopBack(stack));
                if (typeClose != typeOpen)
                    return i;
            }
        }
        i++;
    }
    
    if (stack.size)
        return i;

    return -1;
}

int CharIndex(const char* str, char symbol)
{
    int index{};
    while (str[index])
    {
        if (symbol == str[index])
            return index;
        index++;
    }
    return -1;
}
