//
// Created by mmas6 on 15.04.2020.
//

template <typename containerIterator, typename object>
bool noneOf(const containerIterator begin, const containerIterator end, bool (&f)(object)) {
    for (containerIterator it = begin; it != end; it = next(it)) {
        if (f(*it)) {
            return false;
        }
    }
    return true;
}

template <typename containerIterator, typename object>
bool isSorted(const containerIterator begin, const containerIterator end, bool (&f)(object, object)) {
    containerIterator prev = begin;
    for (containerIterator it = next(begin); it != end; it = next(it)) {
        if (!f(*prev, *it)) {
            return false;
        }
        prev = it;
    }
    return true;
}

template <typename containerIterator, typename object>
object findNot(const containerIterator begin, const containerIterator end, const object v) {
    for (containerIterator it = begin; it != end; it = next(it)) {
        if (*it != v) {
            return *it;
        }
    }
    return object();
}