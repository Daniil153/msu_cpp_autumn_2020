template <class T>
class Allocator {
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    pointer allocate(size_t n) {
        return new value_type [n];
    }
    template <class... Args>
    void create(pointer ptr, Args&&... args){
        new(ptr) value_type(std::forward<Args>(args)...);
    }
    void deallocate(pointer ptr) {
        delete [] ptr;
    }
    void destroy(pointer p){
        p->~value_type();
    }
};

template <class T>
class Iterator {
    T *cur;
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    explicit Iterator(pointer ptr) : cur(ptr) {}
    Iterator(const Iterator<value_type>& it) : cur(it.cur) {}
    bool operator ==(const Iterator<value_type>& it) const {
        return it.cur == cur;
    }
    bool operator !=(const Iterator<value_type>& it) const {
        return it.cur != cur;
    }
    bool operator >=(const Iterator<value_type>& it) const {
        return cur >= it.cur;
    }
    bool operator <=(const Iterator<value_type>& it) const {
        return cur <= it.cur;
    }
    bool operator >(const Iterator<value_type>& it) const {
        return cur > it.cur;
    }
    bool operator <(const Iterator<value_type>& it) const {
        return cur < it.cur;
    }
    T& operator*() const
    {
        return *cur;
    }
    Iterator<value_type>& operator +(size_t n) const {
        Iterator<value_type> tmp(cur + n);
        return tmp;
    }
    Iterator<value_type>& operator -(size_t n) const {
        Iterator<value_type> tmp(cur - n);
        return tmp;
    }
    Iterator<value_type>& operator +=(size_t n) {
        cur += n;
        return *this;
    }
    Iterator<value_type>& operator -=(size_t n) {
        cur -= n;
        return *this;
    }
    Iterator<value_type>& operator++(){
        ++cur;
        return *this;
    }
    Iterator<value_type>& operator--(){
        --cur;
        return *this;
    }
    Iterator<value_type> operator++(int){
        Iterator<value_type> temp(*this);
        ++cur;
        return temp;
    }
    Iterator<value_type> operator--(int){
        Iterator<value_type> temp(*this);
        --cur;
        return temp;
    }
    T& operator[](size_t n){
        return cur[n];
    }
};

template <class T>
class Vector {
    Allocator<T> allocator;
    T* data;
    size_t size_{};
    size_t mem_size{};
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    explicit Vector(size_t n = 0) {
        data = allocator.allocate(n);
        size_ = n;
        mem_size = n;
        for (size_t i = 0; i < size_; ++i)
            allocator.create(data + i);
    }
    Vector (const Vector& v) {
        size_ = v.size_;
        mem_size = v.mem_size;
        for (size_t i = 0; i < mem_size; ++i) {
            allocator.create(data + i);
            data[i] = v[i];
        }
    }
    void push_back(value_type &&data_){
        if (size_ >= mem_size) {
            int count = 0;
            if (mem_size == 0) {
                count = 1;
            }
            reserve(2 * mem_size + count);
        }
        allocator.create(data + size_, std::move(data_));
        ++size_;
    }
    void push_back(const value_type& data_) {
        if (size_ >= mem_size) {
            int count = 0;
            if (mem_size == 0) {
                count = 1;
            }
            reserve(2 * mem_size + count);
        }
        allocator.create(data + size_, std::move(data_));
        ++size_;
    }
    template <class... Args>
    void emplace_back(Args&&... args) {
        if (size_ >= mem_size) {
            int count = 0;
            if (mem_size == 0) {
                count = 1;
            }
            reserve(2 * mem_size + count);
        }
        allocator.create(data + size_, std::move(args)...);
        ++size_;
    }
    void pop_back() {
        size_--;
        allocator.destroy(data + mem_size);
    }
    bool empty() const {
        return size_ == 0;
    }
    size_t size() {
        return size_;
    }
    Iterator<value_type> begin() const {
        return Iterator<value_type>(data);
    }
    Iterator<value_type> end() const {
        return Iterator<value_type>(data + size_);
    }
    std::reverse_iterator<Iterator<value_type>> rbegin() const {
        return std::reverse_iterator<Iterator<value_type>>(end());
    }
    std::reverse_iterator<Iterator<value_type>> rend() const {
        return std::reverse_iterator<Iterator<value_type>>(begin());
    }
    size_t capacity(){
        return mem_size;
    }
    reference operator [](size_t index) {
        return this->data[index];
    }
    const value_type& operator[] (size_t index) const {
        return this->data[index];
    }
    void clear() {
        for (size_t i = size_; i > 0; --i) {
            allocator.destroy(data + i);
        }
        size_ = 0;
    }
    void reserve(size_t count) {
        if (count > mem_size) {
            T* tmp = allocator.allocate(count);
            for (size_t i = 0; i < size_; ++i){
                allocator.create(tmp + i, data[i]);
                allocator.destroy(data + i);
            }
            allocator.deallocate(data);
            data = tmp;
            mem_size = count;
        }
    }
    void resize(size_t count) {
        if (mem_size >= count) {
            for (T* ptr = data + count; ptr != data + mem_size; ++ptr) {
                allocator.destroy(ptr);
            }
        } else {
            this->reserve(count);
            for (T* ptr = data + size_; ptr != data + count; ++ptr) {
                allocator.create(ptr);
            }
        }
        size_ = count;
    }
    ~Vector(){
        clear();
        allocator.deallocate(data);
    }
};
