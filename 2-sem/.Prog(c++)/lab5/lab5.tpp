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
void Queue<N,T>::push(T val){
    try{
        if ( rear+1 == frnt || ( rear + 1 ==N && !frnt )) {
            throw QueueOut();
        }
        rear++;
        if ( rear==N ) rear = 0 ;
        queue [ rear ] = val;
    }
    catch (QueueOut& e){
        std::cerr<<e.what()<<std::endl;
    }
}

template<int N, typename T>
void Queue<N, T>::pop() {
        try{
            if ( frnt == rear ) {
                throw QueueEmpty();
            }
            frnt++;
            if ( frnt==N ) frnt = 0 ;
        }
        catch (QueueEmpty& e){
            std::cerr<<e.what()<<std::endl;
        }
}