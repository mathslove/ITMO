#pragma once

#include <iterator>
#include <cassert>

namespace cb_details
{
    //  Help
    /*!
    \fn ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator dest)
    \brief Equivalent of <code>std::uninitialized_copy</code> but with explicit specification of value type.
    */
    template<class InputIterator, class ForwardIterator, class Alloc>
    ForwardIterator uninitialized_copy(InputIterator first,
                         InputIterator last,
                         ForwardIterator dest,
                         Alloc& a)
    {
        ForwardIterator next = dest;
        try
        {
            for (; first != last; ++first, ++dest)
                std::allocator_traits<Alloc>::construct(a, std::addressof(*dest), *first);
        }
        catch (...)
        {
            for (; next != dest; ++next)
                std::allocator_traits<Alloc>::destroy(a, std::addressof(*next));
            throw;
        }
        return dest;
    }


    template<typename Buff,typename Tp, typename Distance = ptrdiff_t,
            typename Pointer = Tp*, typename Reference = Tp&>
    struct iterator: public std::iterator<std::random_access_iterator_tag, Tp, Distance, Pointer, Reference>{

        typedef typename std::iterator<std::random_access_iterator_tag, Tp, Distance, Pointer, Reference> base_iterator;

        typedef typename std::random_access_iterator_tag    iterator_category;
        typedef typename base_iterator::value_type          value_type;
        typedef typename base_iterator::difference_type     difference_type;
        typedef typename base_iterator::pointer             pointer;
        typedef typename base_iterator::reference           reference;

        //! The circular buffer where the iterator points to.
        const Buff* m_buff;

        //! An internal iterator.
        pointer m_it;

    public:
//          Constructors
        //! Default constructor.
        iterator() : m_buff(0), m_it(0) {}

        iterator(const iterator& it) : m_buff(it.m_buff), m_it(it.m_it) {}

        iterator(const Buff* cb, const pointer p) : m_buff(cb), m_it(p) {}

        iterator& operator =(const iterator& it) noexcept
        {
            if ( this == &it )
                return *this;
            m_buff = it.m_buff;
            m_it = it.m_it;
            return *this;
        }

//          !Constructors

        bool is_valid(const Buff* b)
        {
            return b != nullptr && m_it < (b->m_end);
        }

//          Main methods

        //! Dereferencing operator.
        reference operator *() const
        {
            assert(m_it != 0);
            return *m_it;
        }

        //! Dereferencing operator.
        pointer operator ->() const noexcept { return &( operator*() ); }

        template <class Tp0>
        difference_type operator - (const iterator<Buff, Tp0>& it) const {
            return linearize_pointer(*this) - linearize_pointer(it);
        }

        //! Increment operator (prefix).
        iterator& operator ++()
        {
            assert(m_it != nullptr);
            m_buff->increment(m_it);
            if ( m_it == m_buff->m_last )
                m_it = nullptr;
            return *this;
        }

        //! Increment operator (postfix).
        iterator operator ++(int) noexcept
        {
            iterator<Buff, Tp> tmp = *this;
            ++*this;
            return tmp;
        }

        //! Decrement operator (prefix).
        iterator& operator --()
        {
            assert(m_it != m_buff->m_first);
            if ( m_it == 0 )
                m_it = m_buff->m_last;
            m_buff->decrement(m_it);
            return *this;
        }

        //! Decrement operator (postfix).
        iterator operator --(int) noexcept
        {
            iterator<Buff, Tp> tmp = *this;
            --*this;
            return tmp;
        }

        //! Iterator addition.
        iterator& operator +=(difference_type n) noexcept
        {
            if ( n > 0 )
            {
                m_it = m_buff->add(m_it, n);
                if ( m_it == m_buff->m_last )
                    m_it = nullptr;
            }
            else if (n < 0)
                *this -= -n;
            return *this;
        }

        //! Iterator addition.
        iterator operator +(difference_type n) const noexcept { return iterator<Buff, Tp>(*this) += n; }
        
        //! Iterator subtraction.
        iterator& operator -=(difference_type n) noexcept
        {
            if ( n > 0 )
                m_it = m_buff->sub((m_it == nullptr) ? m_buff->m_last : m_it, n);
            else if (n < 0)
                *this += -n;
            return *this;
        }

        //! Iterator subtraction.
        iterator operator -(difference_type n) const noexcept { return iterator<Buff, Tp>(*this) -= n; }

        //! Element access operator.
        reference operator [](difference_type n) const noexcept { return *(*this + n); }

// Equality & comparison

        //! Equality.
        template <class Tp0>
        bool operator == (const iterator<Buff, Tp0>& it) const {
            return m_it == it.m_it;
        }

        //! Inequality.
        template <class Tp0>
        bool operator != (const iterator<Buff, Tp0>& it) const {
            return m_it != it.m_it;
        }

        //! Less.
        template <class Tp0>
        bool operator < (const iterator<Buff, Tp0>& it) const {
            return linearize_pointer(*this) < linearize_pointer(it);
        }

        //! Greater.
        template <class Tp0>
        bool operator > (const iterator<Buff, Tp0>& it) const { return it < *this; }

        //! Less or equal.
        template <class Tp0>
        bool operator <= (const iterator<Buff, Tp0>& it) const { return !(it < *this); }

        //! Greater or equal.
        template <class Tp0>
        bool operator >= (const iterator<Buff, Tp0>& it) const { return !(*this < it); }
//          !Methods

// Helpers

        //! Get a pointer which would point to the same element as the iterator in case the circular buffer is linearized.
        template <class Tp0>
        pointer linearize_pointer(const iterator<Buff, Tp0>& it) const {
            return (it.m_it == 0) ? (m_buff->m_buff + m_buff->m_size) :
                   (it.m_it < m_buff->m_first ? it.m_it + (m_buff->m_end - m_buff->m_first)
                                              : m_buff->m_buff + (it.m_it - m_buff->m_first));
        }

    };// !iterator

    template<typename Buff, typename Tp, typename Distance = ptrdiff_t,
            typename Pointer = const Tp*, typename Reference = const Tp&>
    class const_iterator: public iterator<Buff, Tp, Distance, Pointer, Reference>{    };// !const_iterator

    //! Iterator addition.
    template <class Buff, class Traits>
    iterator<Buff, Traits>
    operator + (typename Traits::difference_type n, const iterator<Buff, Traits>& it) {
        return it + n;
    }

}// !lab7 namespace