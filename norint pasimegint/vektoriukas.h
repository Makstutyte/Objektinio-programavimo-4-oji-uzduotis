#pragma once
#include <memory>
#include <algorithm>
#include <random>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <iostream>

template <class T > 
class Vector 
{
    public: 
      typedef T* iterator;
      typedef const T* const_iterator;
      typedef size_t size_type;
      typedef T value_type;
      typedef ptrdiff_t diff_type;

      typedef T& reference;
      typedef const T& const_reference;
      typedef std::allocator<T>allocator_type;

      typedef typename std::allocator_traits<allocator_type>::pointer pointer;
      typedef typename std::allocator_traits<allocator_type>::const_pointer const_pointer;

      typedef std::reverse_iterator<iterator> reverse_iterator;
      typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


    void reallocate(const unsigned int &A, const unsigned int &B) 
    {
        avail = A;
        limit = B;
    }

    T& at(int it) 
    {
		return data1[it];
	}

    reference back()
    {
        return *(avail - 1);
    }

    T* data() noexcept;

    T& front()
    {    
        if(avail > 0)
          return data1[0];

        else
          throw  std::logic_error("Emty container - pas tave cia tuscia");
    }

      // rule of three
      Vector() { create(); }
      explicit Vector(size_type n, const T& t = T{}) { create(n, t); }
      Vector(const Vector& v) { create(v.begin(), v.end()); }
      
      Vector& operator=(const Vector&);
      ~Vector() { uncreate(); }
  
      T& operator[](size_type i) { return data1[i]; }
      const T& operator[](size_type i) const { return data1[i]; }

      size_type max_size() const noexcept;  
      size_type size() const { return avail - data1; } 
      size_type capacity() const { return limit - data1; }

      iterator begin() { return data1; }
      const_iterator begin() const { return data1; }
      iterator cbegin() { return data1; } 
      reverse_iterator rbegin() noexcept {return reverse_iterator(avail); } 
      const_reverse_iterator rbegin() const noexcept {return reverse_iterator(avail);} 
      const_reverse_iterator crbegin() const noexcept {return reverse_iterator(avail); } 

      iterator end() { return avail; }
      const_iterator end() const { return avail; }
      iterator cend() { return avail; }     
      reverse_iterator rend() noexcept {return reverse_iterator(data1);} 
      const_reverse_iterator rend() const noexcept {return reverse_iterator(data1);} 
      const_reverse_iterator crend() const noexcept { return reverse_iterator(data1);} 
               
        bool operator==(const Vector<T>& v) const;
        bool operator!=(const Vector<T>& v) const; 
        bool operator<(const Vector<T>& v) const;
        bool operator<=(const Vector<T>& v) const;
        bool operator>(const Vector<T>& v) const; 
        bool operator>=(const Vector<T>& v) const; 

        void push_back(const T& t)
        {
            if (avail == limit)
              grow();

            unchecked_append(t);
        }

        void assign(T* t_start_ptr, T* t_end_ptr);
        void assign(unsigned int t_number, const T& t_value);
        void assign(const_iterator t_start_ptr, const_iterator t_end_ptr);
        void resize(size_t resize_size);
        void pop_back();  
        void insert(const_iterator index, const T& item) ;
        void insert(const_iterator it, int n, T value);
        void clear(); 
        void erase(const_iterator it); 
        void erase(const_iterator it1, const_iterator it2); 
        void resize(int n, T val); 
        void resize(int n); 
        void swap(Vector<T>& v); 
        void shrink_to_fit();  
        void reserve(int n);
        bool empty() {return  begin() == end();}
        void emplace(Vector<T>::const_iterator it, T args); 
        void emplace_back(T args); 

      inline typename std::remove_reference<T>::type&& move_(T& obj); 
  	  inline typename std::remove_reference<T>::type&& move_(T&& obj);

    private:
      iterator data1; 
      iterator avail; 
      iterator limit; 
      std::allocator<T> alloc; 
      void create();  
      void create(size_type, const T&);
      void create(const_iterator, const_iterator);
      void uncreate();  
      void grow();  
      void unchecked_append(const T&);

      size_t _capacity;
	  size_t _size;	
};

template<class T>
void Vector<T>::assign(T* t_start_ptr, T* t_end_ptr) 
{
		clear();
		resize(0);

		for (T* iter = t_start_ptr; iter < t_end_ptr; ++iter) 
        {
			push_back(*iter);
		}
}

template<class T>
void Vector<T>::assign(unsigned int t_number, const T& t_value) 
{
	clear();
	reserve(t_number);

	for (unsigned int i = 0; i < t_number; ++i) 
    {
		push_back(t_value);
	}
}

template<class ForwardIt, class T>
void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value);

template<class InputIt, class ForwardIt>
ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first);

template <class T> 
void Vector<T>::create() 
{
    data1 = avail = limit = nullptr;
}

template <class T> 
void Vector<T>::create(size_type n, const T& val) 
{
    data1 = alloc.allocate(n);
    limit = avail = data1 + n; 
    std::uninitialized_fill(data1, limit, val);
}

template <class T>
void Vector<T>::create(const_iterator i, const_iterator j) 
{
    data1 = alloc.allocate(j - i); 
    limit = avail = std::uninitialized_copy(i, j, data1); 
}

template <class T> 
void Vector<T>::uncreate() 
{
    if (data1) 
    {
      iterator it = avail;

      while (it != data1)
        alloc.destroy(--it);

      alloc.deallocate(data1, limit - data1);
    }

    data1 = limit = avail = nullptr;
}

template <class T> 
void Vector<T>::grow() 
{
    size_type new_size = std::max(2 * (limit - data1), ptrdiff_t(1));
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data1, avail, new_data);

    uncreate();
    data1 = new_data;
    avail = new_avail;
    limit = data1 + new_size;
}

template <class T> 
void Vector<T>::unchecked_append(const T& value) 
{
   alloc.construct(avail++, value);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
    if (&rhs != this) 
    {
      uncreate();
      create(rhs.begin(), rhs.end());
    }

    return *this;
}

template<class T> class allocator 
{
  public:
    T* allocate(size_t);
    void deallocate(T*, size_t);
    void construct(T*, const T&); 
    void destroy(T*);
};

template <class T>
void Vector<T>::insert(Vector<T>::const_iterator index, const T& item) 
{ 
        if ((index < data1) || (index > avail)) 
        {
            std::cout << "Throw exception" << std::endl;
        }

        int v = 0;
        for (auto k = begin(); k < index; k++) 
        {
            v++;
        }

        size_type new_size = (size() + 1);
        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = std::uninitialized_copy(data1, avail + 1, new_data);

        for (int i = 0; i < v; i++) 
        {
            new_data[i] = data1[i];
        }

        new_data[v] = item;
        int z = v + 1;
        int g = size() + 1;

        for (int i = z; i < g; i++) 
        {
            new_data[i] = data1[i - 1];
        }

        uncreate();
        data1 = new_data;
        avail = new_avail;
        limit = data1 + new_size;

}

 template <typename T>
 void Vector<T>::insert(Vector<T>::const_iterator it, int n, T value)
{
        if (it < data1 || n < 1 || it > avail) 
            throw std::out_of_range{ "Vector::insert" };

        avail += n;
        int v = 0;

        for (auto k = begin(); k < it; k++) 
        {
            v++;
        }

        size_type new_size = (size() + n);
        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = std::uninitialized_copy(data1, avail, new_data);

        for (int i = 0; i < v; i++) 
        {
            new_data[i] = data1[i];
        }

        for (int r = v; r <= v + n; r++)
            new_data[r] = value;

        int z = v + n;
        int g = size() + n;

        for (int i = z; i < g; i++) 
        {
            new_data[i] = data1[i - n];
        }

        uncreate();
        data1 = new_data;
        avail = new_avail;
        limit = data1 + new_size;
}

template <typename T>
void Vector<T>::clear() 
{
    resize(0);
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
    if (avail < limit) 
    {
        limit = avail;
    }
}

template <typename T>
void Vector<T>::erase(Vector<T>::const_iterator it) 
{
       if (it < data1 || it > avail) 
         throw std::out_of_range{ "Vector::erase" };

       int v = 0;

       for (auto k = begin(); k < it; ++k) 
       {
           v++;
       }

       if (v < size()) 
       {
           for (v; v < size(); v++) 
           {
               data1[v] = data1[v + 1];
           }
           avail--;
       }
}

    
template <typename T>
void Vector<T>::erase(Vector<T>::const_iterator it1, Vector<T>::const_iterator it2) 
{
	if (it1 < data1 || it2 > avail) 
        throw std::out_of_range{ "Vector::erase" };

    int v = 0, g = 0;

    for (auto k = begin(); k < it1; ++k) 
    {
        v++;
    }

    for (auto k = it1; k < it2; ++k) 
    {
        g++;
    }

        for (v; v < size() - g; v++) 
        {
            data1[v] = data1[v+g];
        }

        avail -= g;
}


template <typename T>
void Vector<T>::resize(int n, T val)
{
    if (n > size()) 
    {
        int o = size();
        int z = n - size();
        avail += z;

        for (int i = o; i < n; i++) 
        {
            data1[i] = val;
        }
    }

    else resize(n);
}

template <typename T>
void Vector<T>::resize(int n) 
{
    int k = 0;
    if(n < size())
    {
        for (int i = n; i < size(); i++) 
        {
            data1[i] = 0;
            k++;
        }
        avail -= k;
    }

    else 
    {
        int o = size();
        int z = n - size();
        avail += z;

        for (int i = o; i < n; i++) 
        {
            data1[i] = 0;
        }
    }
}

template<typename T>
void Vector<T>::reserve(int n) 
{
    int b = capacity();

    if (n > b)
    {
        size_type new_size = n;
       
        iterator new_data = alloc.allocate(new_size);
        iterator new_avail = std::uninitialized_copy(data1, avail, new_data);

        uncreate();
        data1 = new_data;
        avail = new_avail;
        limit = data1 + new_size;
    }
 }


template<typename T>
T* Vector<T>::data() noexcept 
{
    return data;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::max_size() const noexcept 
{
    double imin = std::numeric_limits<T>::min();
    double imax = std::numeric_limits<T>::max();
    double sum = (imax - imin);
    return sum/4;
}

template<typename T>
void Vector<T>::swap(Vector<T>& v) 
{
    iterator data2 = data1 , avail2 = avail, limit2 = limit; 
    data1 = v.data1;
    limit = v.limit;
    avail = v.avail;

    v.data1 = data2;
    v.avail = avail2;
    v.limit = limit2;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T>& v) const 
{
    if (v.size() != size()) 
        return false;

    else 
    {
        int g = v.size();

        for (int k = 0 ; k < g; k++)
        {
            if (data1[k] != v.data1[k]) { return false; }
        }

        return true;
    }
}

template<typename T>
bool Vector<T>::operator!=(const Vector<T>& v) const 
{
    if (v.size() != size()) 
        return true;

    else 
    {
        int g = v.size();

        for (int k = 0; k < g; k++) 
        {
            if (data1[k] != v.data1[k]) { return true; }
        }

        return false;
    }
}

template<typename T>
bool Vector<T>::operator<(const Vector<T>& v) const 
{
    bool tr;
    tr = operator==(v);

    if ( tr == true) 
        return false;

    else 
    {
        int g = v.size();

        for (int a = 0; a < g; a++) 
        {
            if (data1[a] < v.data1[a]) 
                return true;

            else if (data1[a] > v.data1[a]) 
                return false;
        }
    }
}

template<typename T>
bool Vector<T>::operator<=(const Vector<T>& v) const 
{
    bool tr;
    tr = operator==(v);

    if (tr == true) 
        return true;

    else 
    {
        tr = operator<(v);

        if (tr == true) 
          return true;

        else 
          return false;
    }
}

template<typename T>
bool Vector<T>::operator>(const Vector<T>& v) const 
{
    bool t;
    t = operator<=(v);

    if (t == true) 
        return false;

    else 
        return true;
}

template<typename T>
bool Vector<T>::operator>=(const Vector<T>& v) const 
{
    bool t;
    t = operator<(v);
    
    if (t == true) 
        return false;

    else 
        return true;
}

template<typename T>
void Vector<T>::emplace(Vector<T>::const_iterator it, T args) 
{
        if ((it < data1) || (it > avail)) 
        {
          std::cout << "Throw exception" << std::endl;
        }
            int v = 0;

            for (auto a = begin(); a < it; a++) 
            {
                v++;
            }

    size_type new_size = (size() + 1);
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data1, avail+1, new_data);

    for(int i = 0; i< v; i++)
    {
        new_data[i] = data1[i];
    }

    new_data[v] = args;
    int z = v + 1;
    int g = size() + 1;

    for(int i = z; i< g; i++)
    {
        new_data[i] = data1[i-1];
    }
    
    uncreate();
    data1 = new_data;
    avail = new_avail;
    limit = data1 + new_size;
}

template<typename T>
void Vector<T>::emplace_back(T args) 
{
    push_back(args);
}
