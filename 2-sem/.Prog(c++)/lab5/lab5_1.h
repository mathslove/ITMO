//
// Created by mmas6 on 25.03.2020.
//

//Задание 1
template <typename T>
void my_swap ( T & first , T & second )
{
    T temp(first) ;
    first = second ;
    second = temp ;
}


//Здание 2
template <int N, typename T>
void Queue<N,T>::push(const T& val)
{
    if ( size == myList.size() )
        throw QueueOut();
    myList.push_back(val);
}

template<int N, typename T>
T Queue<N,T>::pop()
{
    if (myList.size() == 0)
        throw QueueEmpty();
    myList.pop_back();
}