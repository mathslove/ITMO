//
//  std и boost-like контейнер
//
#pragma once
#include "iterator.h"
#include <memory>

template<class T, class Alloc = std::allocator<T>>
class circular_buffer {

    // Basic types
    typedef typename std::allocator_traits<Alloc>::value_type           value_type;
    typedef typename std::allocator_traits<Alloc>::pointer              pointer;
    typedef typename std::allocator_traits<Alloc>::const_pointer        const_pointer;
    typedef typename std::allocator_traits<Alloc>::value_type&          reference;
    typedef const typename std::allocator_traits<Alloc>::value_type&    const_reference;
    typedef typename std::allocator_traits<Alloc>::difference_type      difference_type;
    typedef typename std::allocator_traits<Alloc>::size_type            size_type;

    using allocator_type = Alloc;

    typedef cb_details::iterator< circular_buffer<T, Alloc>, T> iterator;
    typedef cb_details::const_iterator< circular_buffer<T, Alloc>, T> const_iterator;

private:
    // Member variables

    //! The internal buffer used for storing elements in the circular buffer.
    pointer m_buff;

    //! The internal buffer's end (end of the storage space).
    pointer m_end;

    //! The virtual beginning of the circular buffer.
    pointer m_first;

    //! The virtual end of the circular buffer (one behind the last element).
    pointer m_last;

    //! The number of items currently stored in the circular buffer.
    size_type m_size;

    allocator_type m_alloc;
public:

    template <class Buff, class Tp> friend struct cb_details::iterator;

    //  Constructor

    explicit circular_buffer( const allocator_type& alloc = allocator_type() ) noexcept
            : m_buff(0), m_end(0), m_first(0), m_last(0), m_size(0), m_alloc(alloc) {}

    explicit circular_buffer( size_type buffer_capacity,
                              const allocator_type& alloc = allocator_type() )
            : m_size(0), m_alloc(alloc)
    {
        initialize_buffer(buffer_capacity);
        m_first = m_last = m_buff;
    }

    circular_buffer( size_type n, const value_type& item, const allocator_type& alloc = allocator_type() )
            : m_size(n), m_alloc(alloc)
    {
        initialize_buffer(n, item);
        m_first = m_last = m_buff;
    }

    circular_buffer( size_type n, value_type&& item, const allocator_type& alloc = allocator_type() )
            : m_size(n), m_alloc(alloc)
    {
        initialize_buffer(n, std::move(item));
        m_first = m_last = m_buff;
    }

    circular_buffer( size_type buffer_capacity, size_type n, const value_type& item,
                     const allocator_type& alloc = allocator_type() )
            : m_size(n), m_alloc(alloc)
    {
        assert( buffer_capacity >= size() );
        initialize_buffer(buffer_capacity, item);
        m_first = m_buff;
        m_last = buffer_capacity == n ? m_buff : m_buff + n;
    }

    circular_buffer(const circular_buffer<T, Alloc>& cb)
            : m_size( cb.size() ), m_alloc(cb.get_allocator())
    {
        initialize_buffer( cb.capacity() );
        m_first = m_buff;
        try
        {
            m_last = cb_details::uninitialized_copy(cb.begin(), cb.end(), m_buff, m_alloc);
        }
        catch(...)
        {
            deallocate( m_buff, cb.capacity() );
            throw;
        }
        if ( m_last == m_end )
            m_last = m_buff;
    }

    circular_buffer(circular_buffer<T, Alloc>&& cb) noexcept
            : m_buff(0), m_end(0), m_first(0), m_last(0), m_size(0), m_alloc( cb.get_allocator() )
    {
        cb.swap(*this);
    }

    ~circular_buffer()
    {
        destroy();
    }
    //  !Constructor

    //  Size and capacity
    size_type size(){
        return m_size;
    }

    size_type capacity() const noexcept { return m_end - m_buff; }


    void set_capacity(size_type new_capacity)
    {
        if (new_capacity == capacity())
            return;
        pointer buff = allocate(new_capacity);
        iterator b = begin();
        try
        {
            reset(buff,
                  cb_details::uninitialized_copy(b, b + (std::min)(new_capacity, size()), buff, m_alloc),
                  new_capacity);
        }
        catch(...)
        {
            deallocate(buff, new_capacity);
            throw;
        }
    }
    //  !Size and capacity

    // Tools methods

    template<class Pointer>
    void increment(Pointer& p) const noexcept
    {
        if (++p == m_end)
            p = m_buff;
    }

    template<class Pointer>
    void decrement(Pointer& p) const noexcept
    {
        if (p == m_buff)
            p = m_end;
        --p;
    }

    template<class Pointer>
    Pointer add(Pointer p, difference_type n) const noexcept
    {
        return p + ( n < (m_end - p) ? n : n - capacity() );
    }

    template<class Pointer>
    Pointer sub(Pointer p, difference_type n) const noexcept
    {
        return p - (n > (p - m_buff) ? n - capacity() : n);
    }

    pointer allocate(size_type n)
    {
        if ( (n > std::allocator_traits<Alloc>::max_size(m_alloc)) )
            throw std::length_error("circular_buffer");
        return (n == 0) ? nullptr : m_alloc.allocate(n);
    }

    void deallocate(pointer p, size_type n)
    {
        if (p != nullptr)
            m_alloc.deallocate(p, n);
    }

    void replace(pointer pos, const value_type& item) noexcept
    {
        *pos = item;
    }

    void replace(pointer pos, value_type& item) noexcept
    {
        *pos = std::move(item);
    }

    void construct_or_replace(bool construct, pointer pos, const value_type& item) noexcept
    {
        construct ?
        std::allocator_traits<Alloc>::construct(m_alloc, std::addressof(*pos), item)
                  : replace(pos, item);
    }

    void construct_or_replace(bool construct, pointer pos, value_type& item)  noexcept
    {
        construct ?
        std::allocator_traits<Alloc>::construct( m_alloc, std::addressof(*pos), std::move(item) )
                  : replace( pos, std::move(item) );
    }

    void destroy()
    {
        for ( size_type i = 0; i < size(); ++i, increment(m_first) )
            std::allocator_traits<Alloc>::destroy( m_alloc, std::addressof(*m_first) );
        deallocate( m_buff, capacity() );
    }

    void initialize_buffer(size_type buffer_capacity)
    {
        m_buff = allocate(buffer_capacity);
        m_end = m_buff + buffer_capacity;
    }

    void initialize_buffer(size_type buffer_capacity, const value_type& item)
    {
        initialize_buffer(buffer_capacity);
        try
        {
            auto next = m_buff;
            try
            {
                size_type n = size();
                for (; n > 0; ++m_buff, --n)
                    std::allocator_traits<Alloc>::construct(m_alloc, std::addressof(*m_buff), item);
            }
            catch (...)
            {
                for (; next != m_buff; ++next)
                    std::allocator_traits<Alloc>::destroy(m_alloc, std::addressof(*next));
                throw;
            }
        } catch(...) {
            deallocate(m_buff, size());
            throw;
        }
    }

    void reset(pointer buff, pointer last, size_type new_capacity)
    {
        destroy();
        m_size = last - buff;
        m_first = m_buff = buff;
        m_end = m_buff + new_capacity;
        m_last = last == m_end ? m_buff : last;
    }

    void destroy_item(pointer p){
        std::allocator_traits<Alloc>::destroy(m_alloc, std::addressof(p));
    }
//      !Tools

//      Buffer access
    iterator begin() noexcept { return iterator (this, size() == 0 ? nullptr : m_first);}
    iterator end() noexcept { return iterator(this, 0); }

    const_iterator cbegin() const noexcept   {return const_iterator(this, size() == 0 ? nullptr : m_first);}
    const_iterator cend() const noexcept { return const_iterator(this, 0); }

    reference operator [](size_type index)
    {
        assert( index < size() );
        return *add(m_first, index);
    }
    const_reference operator [](size_type index) const
    {
        assert( index < size() );
        return *add(m_first, index);
    }
//    !Buffer access

//  Push

private:
    template<typename ValT>
    void push_back_lval(ValT item){
        if (capacity()==size()) {
            if (size()==0)
                return;
            replace(m_last, static_cast<ValT>(item));
            increment(m_last);
            m_first = m_last;
        } else {
            std::allocator_traits<Alloc>::construct(m_alloc, std::addressof(*m_last), static_cast<ValT>(item));
            increment(m_last);
            ++m_size;

        }
    }

    template <class ValT>
    void push_front_lval(ValT item) {
        try {
            if (capacity()==size()) {
                if (size()==0)
                    return;
                decrement(m_first);
                replace(m_first, static_cast<ValT>(item));
                m_last = m_first;
            } else {
                decrement(m_first);
                std::allocator_traits<Alloc>::construct(m_alloc, std::addressof(*m_first),
                                                        static_cast<ValT>(item));
                ++m_size;
            }
        } catch (...) {
            increment(m_first);
            throw;
        }
    }

public:
    void push_back(const value_type& el){
        push_back_lval<const value_type&>(el);
    }

    void push_back(value_type&& el){
        push_back_lval<value_type&&>(std::move(el));
    }

    void push_front(const value_type& el){
        push_front_lval<const value_type&>(el);
    }

    void push_front(value_type&& el){
        push_front_lval<value_type&&>(std::move(el));
    }

//  !Push

//  Pop

    void pop_back(){
        assert(size()!=0);  // check for empty buffer (back element not available)
        decrement(m_last);
        destroy_item(m_last);
        --m_size;
    }

    void pop_front() {
        assert(size()!=0);  // check for empty buffer (front element not available)
        destroy_item(m_first);
        increment(m_first);
        --m_size;
    }

//  !Pop

//  Insert
private:
    template<class ValT>
    iterator insert_impl(iterator pos, ValT item)
    {
//        assert();
        iterator b = begin();
        if (capacity() == size() && pos == b)
            return b;
        return insert_item<ValT>( pos, static_cast<ValT>(item) );
    }

    template<class ValT>
    iterator insert_item(const iterator& pos, ValT item)
    {
        pointer p = pos.m_it;
        if ( p == nullptr )
        {
            construct_or_replace(capacity() != size(), m_last, static_cast<ValT>(item));
            p = m_last;
        }
        else
        {
            pointer src = m_last;
            pointer dest = m_last;
            bool construct = capacity() != size();
            try
            {
                while (src != p)
                {
                    decrement(src);
                    construct_or_replace(construct, dest, std::move_if_noexcept(*src));
                    decrement(dest);
                    construct = false;
                }
                replace(p, static_cast<ValT>(item));
            }
            catch(...)
            {
                if (!construct && capacity() != size())
                {
                    increment(m_last);
                    ++m_size;
                }
                throw;
            }
        }
        increment(m_last);
        if ( capacity() == size())
            m_first = m_last;
        else
            ++m_size;
        return iterator(this, p);
    }

public:
    iterator insert(iterator pos, const value_type& item)
    {
        return insert_impl<const value_type&>(pos, item);
    }

    iterator insert(iterator pos, value_type&& item)
    {
        return insert_impl<value_type&&>( pos, std::move(item) );
    }
//  !Insert

//  Erase

    iterator erase(iterator pos){
        assert(pos.is_valid(this)); // check for uninitialized or invalidated iterator
        assert(pos.m_it != 0);      // check for iterator pointing to end()
        pointer next = pos.m_it;
        increment(next);
        for (pointer p = pos.m_it; next != m_last; p = next, increment(next))
            replace(p, std::move_if_noexcept(*next));
        decrement(m_last);
        destroy_item(m_last);
        --m_size;
        return m_last == pos.m_it ? end() : pos;
    }

    iterator erase(iterator first, iterator last) {
        assert(first.is_valid(this)); // check for uninitialized or invalidated iterator
        assert(last.is_valid(this));  // check for uninitialized or invalidated iterator
        assert(first <= last);        // check for wrong range
        if (first == last)
            return first;
        pointer p = first.m_it;
        while (last.m_it != 0)
            replace((first++).m_it, std::move_if_noexcept(*last++));
        do {
            decrement(m_last);
            destroy_item(m_last);
            --m_size;
        } while(m_last != first.m_it);
        return m_last == p ? end() : iterator(this, p);
    }

//  !Erase

};