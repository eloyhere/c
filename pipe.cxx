#include <list>
#include <map>
#include <array>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <iostream>
namespace flow
{
/**
*  管道流类
*/
template <class E>
class pipe;

/**
*  返回一个空的管道流
*/
template <class E>
pipe<E> empty();

/**
*  以特定类型元素填充该管道流，数量为count
*/
template <class E>
pipe<E> fill(const E &element, const int &count);

/**
*  从列表创建管道流
*/
template <class E>
pipe<E> from(std::list<E> l);

/**
*  从向量创建管道流
*/
template <class E>
pipe<E> from(std::vector<E> v);

/**
*  从数组创建管道流
*/
template <class E>
pipe<E> from(const E *elements, const int &size);

template <class E>
pipe<E> from(const E &e);

template <class E>
pipe<E> from(const E &e, const E &e1);

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2);

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3);

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4);

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5);

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6);

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6, const E &e7);

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6, const E &e7, const E &e8);

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6, const E &e7, const E &e8, const E &e9);

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6, const E &e7, const E &e8, const E &e9, const E &e10);

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6, const E &e7, const E &e8, const E &e9, const E &e10, const E &e11);

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6, const E &e7, const E &e8, const E &e9, const E &e10, const E &e11, const E &e12);

/**
*  根据一个特定种子
*  由函数进行迭代转换
*  仅当predicate为true时，添加到管道流中
*  否则保留已有元素，并终止生成
*/
template <class E>
pipe<E> generate(const E &seed, const std::function<E(E)> generator, const std::function<bool(E)> predicate);

/**
*  生成特定区间[start, end)内的元素，
*  再经过函数转换为特定类型元素，
*  再填充管道流
*/
template <class E>
pipe<E> range(const int &start, const int &end, const std::function<E(int)> &mapper);

/**
*  生成特定区间[start, end)内的char元素，
*  填充管道流
*/
pipe<char> range(const char &start, const char &end);

/**
*  生成特定区间[start, end)内的short元素，
*  填充管道流
*/
pipe<short> range(const short &start, const short &end);

/**
*  生成特定区间[start, end)内的int元素，
*  填充管道流
*/
pipe<int> range(const int &start, const int &end);

/**
*  生成特定区间[start, end)内的long元素，
*  填充管道流
*/
pipe<long> range(const long &start, const long &end);

template <class E>
class pipe
{
  protected:
    const std::vector<E> vector;

    bool checkIndex(const int &index)
    {
        return -this->size() < index && index < this->size();
    }

  public:
    pipe(const std::vector<E> &vector) : vector(vector)
    {
    }

    pipe(const pipe<E> &p) : vector({p.vector})
    {
    }

    pipe<E> add(const E &element) const
    {
        std::vector<E> vector = {};
        this->forEach([&vector](const E &element) -> void {
            vector.push_back(element);
        });
        vector.push_back(element);
        return pipe<E>::of(vector);
    }

    bool allMatch(const std::function<bool(E)> &predicate)
        const
    {
        for (int i = 0; i < this->size(); i++)
        {
            if (!predicate(this->at(i)))
            {
                return false;
            }
        }
        return true;
    }

    bool anyMatch(const std::function<bool(E)> &predicate) const
    {
        for (int i = 0; i < this->size(); i++)
        {
            if (predicate(this->at(i)))
            {
                return true;
            }
        }
        return false;
    }

    E &at(const int &index) const
    {
        const int &i = ((index % this->size()) + this->size()) % this->size();
        return const_cast<E &>(this->vector[i]);
    }

    double average(const std::function<long(E)> &average) const
    {
        return this->reduce<long>(0, [&average](const long &accumulator, const E &element) -> long {
            return accumulator + average(element);
        }) / this->size();
    }

    pipe<E> combine(const pipe<E> &p, const std::function<E(E, E)> &combiner) const
    {
        int min = this->size() < p.size() ? this->size() : p.size();
        std::vector<E> v = {};
        for (int i = 0; i < min; i++)
        {
            v.push_back(combiner(this->at(i), p.at(i)));
        }
        return pipe<E>::of(v);
    }

    template <class T, class R>
    pipe<E> combine(const pipe<T> &p, const std::function<R(E, T)> &combiner) const
    {
        int min = this->size() < p.size() ? this->size() : p.size();
        std::vector<R> v = {};
        for (int i = 0; i < min; i++)
        {
            v.push_back(combiner(this->at(i), p.at(i)));
        }
        return pipe<R>::of(v);
    }

    pipe<E> concat(const pipe<E> &p) const
    {
        std::vector<E> result = {};
        auto iterator = [&result](const E &element) -> void {
            result.push_back(element);
        };
        this->forEach(iterator);
        p.forEach(iterator);
        return pipe<E>::of(result);
    }

    bool contains(const E &e) const
    {
        return this->anyMatch([e](const E &element) -> bool {
            return e == element;
        });
    }

    bool containsAll(const pipe<E> &p) const
    {
        for (int i = 0; i < p.size(); i++)
        {
            const E &element = p.at(i);
            if (this->noneMatch([](const E &e) -> bool {
                    return element == e;
                }))
            {
                return false;
            }
        }
        return true;
    }

    bool containsAny(const pipe<E> &p) const
    {
        for (int i = 0; i < p.size(); i++)
        {
            const E &element = this->at(i);
            if (p.anyMatch([element](const E &e) -> bool {
                    return element == e;
                }))
            {
                return false;
            }
        }
        return true;
    }

    pipe<E> cout() const
    {
        std::cout << '[';
        for (int i = 0; i < this->size(); i++)
        {
            std::cout << this->at(i);
            if (i < this->size() - 1)
            {
                std::cout << ',';
            }
        }
        std::cout << ']';
        return *this;
    }

    pipe<E> distinct() const
    {
        pipe<E> proxy = *this;
        return this->filter([&proxy](const E &element) -> bool {
            return proxy.indexOf(element) == proxy.lastIndexOf(element);
        });
    }

    pipe<E> dropWhile(const std::function<bool(E)> &predicate) const
    {
        std::vector<E> vector = {};
        this->forEach([&vector, &predicate](const E &element) -> void {
            if (!predicate(element))
            {
                vector.push_back(element);
            }
        });
        return pipe<E>::of(vector);
    }

    bool empty() const
    {
        return this->size() == 0;
    }

    pipe<E> filter(const std::function<bool(int, E)> &filter) const
    {
        std::vector<E> vector = {};
        this->peek([&filter, &vector](const int &index, const E &element) -> bool {
            if (filter(index, element))
            {
                vector.push_back(element);
            }
        });
        return pipe<E>::of(vector);
    }

    E &findAny() const
    {
        srand(time(0));
        return this->at(rand());
    }

    E &findFirst() const
    { 
        return this->at(0);
    }

    E &findLast() const
    {
        return this->at(this->size() - 1);
    }

    pipe<E> flat(const std::function<pipe<E>(E)> &mapper)
        const
    {
        std::vector<E> result = {};
        for (int i = 0; i < this->size(); i++)
        {
            mapper(this->at(i)).forEach([&result](const E &element) -> void {
                result.push_back(element);
            });
        }
        return pipe<E>::of(result);
    }

    pipe<E> flatCombine(const pipe<E> &source, const std::function<E(E, E)> &combiner) const
    {
        std::vector<E> result = {};
        for (int i = 0; i < this->size(); i++)
        {
            for (int j = 0; j < source.size(); j++)
            {
                result.push_back(combiner(this->at(i), source.at(j)));
            }
        }
        return pipe<E>::of(result);
    }

    template <class R>
    pipe<R> flatCombine(const pipe<E> &source, const std::function<R(E, E)> &combiner) const
    {
        std::vector<R> result = {};
        for (int i = 0; i < this->size(); i++)
        {
            for (int j = 0; j < source.size(); j++)
            {
                result.push_back(combiner(this->at(i), source.at(j)));
            }
        }
        return pipe<R>::of(result);
    }

    template <class R>
    pipe<R> flatMap(const std::function<pipe<R>(E)> &mapper) const
    {
        std::vector<R> result = {};
        for (int i = 0; i < this->size(); i++)
        {
            mapper(this->at(i)).forEach([&result](const R &element) -> void {
                result.push_back(element);
            });
        }
        return pipe<R>::of(result);
    }

    pipe<E> forEach(const std::function<void(E)> &iterator) const
    {
        std::vector<E> vector = {};
        for (int i = 0; i < this->size(); i++)
        {
            iterator(this->at(i));
            vector.push_back(this->at(i));
        }
        return pipe<E>::of(vector);
    }

    pipe<E> forEach(const int &start, const int &end, const std::function<void(E)> iterator)
    {
        std::vector<E> vector = {};
        if (checkIndex(start) && checkIndex(end))
        {
            int s = start < end ? start : end;
            int e = end > start ? end : start;
            for (int i = s; i < e; i++)
            {
                iterator(this->at(i));
                vector.push_back(this->at(i));
            }
        }
        return pipe<E>::of(vector);
    }

    template <class K>
    std::map<K, E> group(const std::function<K(E)> &mapper) const
    {
        std::map<K, E> map = {};
        this->forEach([&map, &mapper](const E &e) -> void {
            map[mapper(e)] = e;
        });
        return map;
    }

    int indexOf(const E &element) const
    {
        for (int i = 0; i < this->size(); i++)
        {
            if (this->at(i) == element)
            {
                return i;
            }
        }
        return -1;
    }

    bool isEmpty()
    {
        return this->size() == 0;
    }

    bool isPresent()
    {
        return this->size() > 0;
    }

    std::string joint(const std::string &splice) const
    {
        return this->reduce<std::string>("", [&splice](const std::string &a, const E &e) -> std::string {
            return a + std::to_string(e);
        });
    }

    int lastIndexOf(const E &element) const
    {
        for (int i = this->size() - 1; i > -1; i--)
        {
            if (this->at(i) == element)
            {
                return i;
            }
        }
        return -1;
    }

    pipe<E> limit(const long &count) const
    {
        const long n = count < 0 ? 0 : (count < this->size() ? count : this->size());
        std::vector<E> v = {};
        for (long i = 0; i < n; i++)
        {
            v.push_back(this->at(i));
        }
        return pipe<E>::of(v);
    }

    pipe<E> map(const std::function<E(E)> mapper)
        const
    {
        std::vector<E> v = {};
        while (v.size() < this->size())
        {
            v.push_back(mapper(this->at(v.size())));
        }
        return pipe<E>::of(v);
    }

    template <class R>
    pipe<R> map(const std::function<R(E)> &mapper) const
    {
        std::vector<R> v = {};
        while (v.size() < this->size())
        {
            v.push_back(mapper(this->at(v.size())));
        }
        return pipe<R>::of(v);
    }

    E max(const E &identity, const std::function<int(E, E)> comparator) const
    {
        std::vector<E> v = {};
        v.push_back(identity);
        for (int i = 0; i < this->size(); i++)
        {
            if (comparator(v[v.size() - 1], this->at(i)) == -1)
            {
                v.push_back(this->at(i));
            }
        }
        return v[v.size() - 1];
    }

    pipe<E> middle(const std::function<long(E, E)> &comparator) const
    {
        const pipe<E> &proxy = *this;
        return this->sort(comparator).filter([&proxy](const int &index, const E &e) -> bool {
            return index == proxy.size() / 2 || (proxy.size() % 2 == 0 && index == proxy.size() / 2 - 1);
        });
    }

    E min(const E &identity, const std::function<int(E, E)> comparator) const
    {
        std::vector<E> v = {};
        v.push_back(identity);
        for (int i = 0; i < this->size(); i++)
        {
            if (comparator(v[v.size() - 1], this->at(i)) == 1)
            {
                v.push_back(this->at(i));
            }
        }
        return v[v.size() - 1];
    }

    bool noneMatch(const std::function<bool(E)> &predicate) const
    {
        for (int i = 0; i < this->size(); i++)
        {
            if (predicate(this->at(i)))
            {
                return false;
            }
        }
        return true;
    }

    static pipe<E> of(const std::list<E> &list)
    {
        std::vector<E> v = {};
        for (auto iterator = list.begin(); iterator != list.end(); iterator++)
        {
            v.push_back(*iterator);
        }
        pipe<E> result{v};
        return result;
    }

    static pipe<E> of(const std::vector<E> &vector)
    {
        std::vector<E> v = {};
        for (int i = 0; i < vector.size(); i++)
        {
            v.push_back(vector[i]);
        }
        pipe<E> result{v};
        return result;
    }

    static pipe<E> of(const E *elements, const int &count)
    {
        std::vector<E> v = {};
        for (int i = 0; i < count; i++)
        {
            v.push_back(elements[i]);
        }
        pipe<E> result{v};
        return result;
    }

    static pipe<E> of(const E &e)
    {
        std::vector<E> v = {};
        v.push_back(e);
        return pipe<E>::of(v);
    }

    pipe<E> peek(const std::function<void(int, E)> &iterator) const
    {
        std::vector<E> vector = {};
        for (int i = 0; i < this->size(); i++)
        {
            iterator(i, this->at(i));
            vector.push_back(this->at(i));
        }
        return pipe<E>::of(vector);
    }

    pipe<E> peek(const int &start, const int &end, const std::function<void(int, E)> iterator)
    {
        std::vector<E> vector = {};
        if (checkIndex(start) && checkIndex(end))
        {
            int s = start < end ? start : end;
            int e = end > start ? end : start;
            for (int i = s; i < e; i++)
            {
                iterator(i, this->at(i));
                vector.push_back(this->at(i));
            }
        }
        return pipe<E>::of(vector);
    }

    E reduce(const E &identity, std::function<E(E, E)> reduce) const
    {
        std::vector<E> v = {};
        v.push_back(identity);
        for (int i = 0; i < this->size(); i++)
        {
            v.push_back(reduce(v[v.size() - 1], this->at(i)));
        }
        return v[v.size() - 1];
    }

    template <class R>
    R reduce(const R &identity, const std::function<R(R, E)> &reduce) const
    {
        std::vector<R> v = {};
        v.push_back(identity);
        for (int i = 0; i < this->size(); i++)
        {
            v.push_back(reduce(v[v.size() - 1], this->at(i)));
        }
        return v[v.size() - 1];
    }

    pipe<E> reindex(const std::function<int(int, E)> &mapper) const
    {
        const int &size = this->size();
        std::vector<E> vector = this->vector;
        this->peek([&vector, &mapper, &size](const int &index, const E &element) -> void {
            vector[(mapper(index, element) + size) % size] = element;
        });
        return pipe<E>::of(vector);
    }

    pipe<E> repeat(const long &count) const
    {
        std::vector<E> vector = {};
        while (vector.size() < this->size() * count)
        {
            this->forEach([&vector](const E &element) -> void {
                vector.push_back(element);
            });
        }
        return pipe<E>::of(vector);
    }

    pipe<E> replace(const std::function<E(E)> &replace) const
    {
        std::vector<E> vector = {};
        this->forEach([&vector, &replace](const E &element) -> void {
            vector.push_back(replace(element));
        });
        return pipe<E>::of(vector);
    }

    pipe<E> replace(const std::function<E(int, E)> &replace) const
    {
        std::vector<E> vector = {};
        this->peek([&vector, &replace](const int &index, const E &element) -> void {
            vector.push_back(replace(index, element));
        });
        return pipe<E>::of(vector);
    }

    template <class R>
    pipe<R> replace(const std::function<R(E)> &replace) const
    {
        std::vector<R> vector = {};
        this->forEach([&vector, &replace](const E &element) -> void {
            vector.push_back(replace(element));
        });
        return pipe<R>::of(vector);
    }

    template <class R>
    pipe<R> replace(const std::function<R(int, E)> &replace) const
    {
        std::vector<R> vector = {};
        this->peek([&vector, &replace](const int &index, const E &element) -> void {
            vector.push_back(replace(index, element));
        });
        return pipe<R>::of(vector);
    }

    pipe<E> reverse() const
    {
        std::vector<E> v = {};
        for (int i = this->size() - 1; i > -1; i--)
        {
            v.push_back(this->at(i));
        }
        return pipe<E>::of(v);
    }

    int size() const
    {
        return this->vector.size();
    }

    pipe<E> skip(const long &count) const
    {
        const long n = count < 0 ? 0 : (count < this->size() ? count : this->size());
        std::vector<E> v = {};
        for (long i = count; i < n; i++)
        {
            v.push_back(this->at(i));
        }
        return pipe<E>::of(v);
    }

    pipe<E> sub(const long &start, const long &end) const
    {
        long a = start < 0 ? 0 : start;
        long b = end < 0 ? 0 : end;
        b = b > a ? b : a;
        b = b < this->count ? b : this->count;
        std::vector<E> v = {};
        for (long i = start; i < end; i++)
        {
            v.push_back(this->at(i));
        }
        return pipe<E>::of(v);
    }

    long summate(const std::function<long(E)> &summation) const
    {
        return this->reduce<long>(0, [summation](const long &a, const E &e) -> long {
            return a + summation(e);
        });
    }

    pipe<E> sort(const std::function<long(E, E)> &comparator) const
    {
        std::vector<E> v = {};
        this->forEach([&v](const E &element) -> void {
            v.push_back(element);
        });
        for (int a = 0; a < this->size(); a++)
        {
            for (int b = a; b < this->size(); b++)
            {
                if (comparator(v[a], v[b]) == 1)
                {
                    E temp = v[b];
                    v[b] = v[a];
                    v[a] = temp;
                }
            }
        }
        return pipe<E>::of(v);
    }

    std::string stringify() const
    {
        const pipe<E> &p = *this;
        return this->reduce<std::string>("[", [&p](const std::string &a, const E &e) -> std::string {
            return p.indexOf(e) < p.size() - 1 ? a + std::to_string(e) + "," : a + std::to_string(e);
        }) + "]";
    }

    std::string stringify(const std::string &splice) const
    {
        const pipe<E> &p = *this;
        return this->reduce<std::string>("[", [&p, &splice](const std::string &a, const E &e) -> std::string {
            return p.indexOf(e) < p.size() - 1 ? a + std::to_string(e) + splice : a + std::to_string(e);
        }) + "]";
    }

    std::string stringify(const std::function<std::string(E)> &stringify) const
    {
        const pipe<E> &p = *this;
        return this->reduce<std::string>("[", [&p, &stringify](const std::string &a, const E &e) -> std::string {
            return p.indexOf(e) < p.size() - 1 ? a + stringify(e) + "," : a + stringify(e);
        }) + "]";
    }

    std::string stringify(const std::string &splice, const std::function<std::string(E)> &stringify) const
    {
        const pipe<E> &p = *this;
        return this->reduce<std::string>("[", [&p, &splice, &stringify](const std::string &a, const E &e) -> std::string {
            return p.indexOf(e) < p.size() - 1 ? a + stringify(e) + splice : a + stringify(e);
        }) + "]";
    }

    pipe<E> takeWhile(const std::function<bool(E)> &predicate) const
    {
        std::vector<E> vector = {};
        this->forEach([&vector, &predicate](const E &element) -> void {
            if (predicate(element))
            {
                vector.push_back(element);
            }
        });
        return pipe<E>::of(vector);
    }

    template <size_t N>
    std::array<E, N> toArray()
    {
        std::array<E, N> array;
        this->peek(0, N < size() ? N : size(), [&array](const int &index, const E &e) -> void {
            array[index] = e;
        });
        return array;
    }

    std::list<E> toList()
    {
        std::list<E> list = {};
        this->forEach([&list](const E &e) -> void {
            list.push_back(e);
        });
        return list;
    }

    std::vector<E> toVector()
    {
        std::vector<E> vector = {};
        this->forEach([&vector](const E &e) -> void {
            vector.push_back(e);
        });
        return vector;
    }

    friend std::ostream &operator<<(std::ostream &stream, const pipe<E> &p)
    {
        stream << '[';
        p.peek([&stream, &p](const int &index, const E &element) -> void {
            stream << element << (index < p.size() - 1 ? ',' : (char)0);
        });
        stream << ']';
        return stream;
    }

    pipe<E> &operator=(const std::vector<E> &vector)
    {
        std::vector<E> &v = const_cast<std::vector<E> &>(this->vector);
        v.clear();
        while (v.size() < vector.size())
        {
            v.push_back(vector[v.size()]);
        }
        return *this;
    }

    pipe<E> &operator=(const pipe<E> &p)
    {
        std::vector<E> &vector = const_cast<std::vector<E> &>(this->vector);
        vector.clear();
        p.forEach([&vector](const E &element) -> void {
            vector.push_back(element);
        });
        return *this;
    }

    bool operator==(const pipe<E> &p) const
    {
        return this->size() == p.size() && this->containsAll(p);
    }

    E &operator[](const int &index) const
    {
        const int &i = ((index % this->size()) + this->size()) % this->size();
        return const_cast<E &>(this->vector[i]);
    }
};

template <class E>
pipe<E> empty()
{
    std::vector<E> vector = {};
    return pipe<E>::of(vector);
}

template <class E>
pipe<E> fill(const E &element, const int &count)
{
    std::vector<E> v = {};
    while (v.size() < count)
    {
        v.push_back(element);
    }
    return pipe<E>::of(v);
}

template <class E, size_t N>
pipe<E> from(std::array<E, N> array)
{
    std::vector<E> vector = {};
    while (vector.size() < array.size())
    {
        vector.push_back(array[vector.size()]);
    }
    return pipe<E>::of(vector);
}

template <class E>
pipe<E> from(std::list<E> list)
{
    return pipe<E>::of(list);
}

template <class E>
pipe<E> from(std::vector<E> vector)
{
    return pipe<E>::of(vector);
}

template <class E>
pipe<E> from(const E *array, const int &count)
{
    return pipe<E>::of(array, count);
}

template <class E>
pipe<E> from(const E &e)
{
    std::vector<E> v = {};
    v.push_back(e);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> from(const E &e, const E &e1)
{
    std::vector<E> v = {};
    v.push_back(e);
    v.push_back(e1);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2)
{
    std::vector<E> v = {};
    v.push_back(e);
    v.push_back(e1);
    v.push_back(e2);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3)
{
    std::vector<E> v = {};
    v.push_back(e);
    v.push_back(e1);
    v.push_back(e2);
    v.push_back(e3);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4)
{
    std::vector<E> v = {};
    v.push_back(e);
    v.push_back(e1);
    v.push_back(e2);
    v.push_back(e3);
    v.push_back(e4);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5)
{
    std::vector<E> v = {};
    v.push_back(e);
    v.push_back(e1);
    v.push_back(e2);
    v.push_back(e3);
    v.push_back(e4);
    v.push_back(e5);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6)
{
    std::vector<E> v = {};
    v.push_back(e);
    v.push_back(e1);
    v.push_back(e2);
    v.push_back(e3);
    v.push_back(e4);
    v.push_back(e5);
    v.push_back(e6);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6, const E &e7)
{
    std::vector<E> v = {};
    v.push_back(e);
    v.push_back(e1);
    v.push_back(e2);
    v.push_back(e3);
    v.push_back(e4);
    v.push_back(e5);
    v.push_back(e6);
    v.push_back(e7);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6, const E &e7, const E &e8)
{
    std::vector<E> v = {};
    v.push_back(e);
    v.push_back(e1);
    v.push_back(e2);
    v.push_back(e3);
    v.push_back(e4);
    v.push_back(e5);
    v.push_back(e6);
    v.push_back(e7);
    v.push_back(e8);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6, const E &e7, const E &e8, const E &e9)
{
    std::vector<E> v = {};
    v.push_back(e);
    v.push_back(e1);
    v.push_back(e2);
    v.push_back(e3);
    v.push_back(e4);
    v.push_back(e5);
    v.push_back(e6);
    v.push_back(e7);
    v.push_back(e8);
    v.push_back(e9);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6, const E &e7, const E &e8, const E &e9, const E &e10)
{
    std::vector<E> v = {};
    v.push_back(e);
    v.push_back(e1);
    v.push_back(e2);
    v.push_back(e3);
    v.push_back(e4);
    v.push_back(e5);
    v.push_back(e6);
    v.push_back(e7);
    v.push_back(e8);
    v.push_back(e9);
    v.push_back(e10);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6, const E &e7, const E &e8, const E &e9, const E &e10, const E &e11)
{
    std::vector<E> v = {};
    v.push_back(e);
    v.push_back(e1);
    v.push_back(e2);
    v.push_back(e3);
    v.push_back(e4);
    v.push_back(e5);
    v.push_back(e6);
    v.push_back(e7);
    v.push_back(e8);
    v.push_back(e9);
    v.push_back(e10);
    v.push_back(e11);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> from(const E &e, const E &e1, const E &e2, const E &e3, const E &e4, const E &e5, const E &e6, const E &e7, const E &e8, const E &e9, const E &e10, const E &e11, const E &e12)
{
    std::vector<E> v = {};
    v.push_back(e);
    v.push_back(e1);
    v.push_back(e2);
    v.push_back(e3);
    v.push_back(e4);
    v.push_back(e5);
    v.push_back(e6);
    v.push_back(e7);
    v.push_back(e8);
    v.push_back(e9);
    v.push_back(e10);
    v.push_back(e11);
    v.push_back(e12);
    return pipe<E>::of(v);
}

template <class E>
pipe<E> generate(const E &seed, const std::function<E(E)> generator, const std::function<bool(E)> predicate)
{
    std::vector<E> v = {};
    if (predicate(seed))
    {
        v.push_back(generate(seed));
    }
    while (predicate(v[v.size() - 1]))
    {
        v.push_back(generator(v[v.size() - 1]));
    }
    return pipe<E>::of(v);
}

template <class E>
pipe<E> range(const int &start, const int &end, const std::function<E(int)> &mapper)
{
    std::vector<E> v = {};
    short min = start < end ? start : end;
    short max = start < end ? end : start;
    for (short i = min; i < max; i++)
    {
        v.push_back(mapper(i));
    }
    return pipe<E>::of(v);
}

pipe<char> range(const char &start, const char &end)
{
    std::vector<char> v = {};
    char min = start < end ? start : end;
    char max = start < end ? end : start;
    for (char i = min; i < max; i++)
    {
        v.push_back(i);
    }
    return pipe<char>::of(v);
}

pipe<short> range(const short &start, const short &end)
{
    std::vector<short> v = {};
    short min = start < end ? start : end;
    short max = start < end ? end : start;
    for (short i = min; i < max; i++)
    {
        v.push_back(i);
    }
    return pipe<short>::of(v);
}

pipe<int> range(const int &start, const int &end)
{
    std::vector<int> v = {};
    int min = start < end ? start : end;
    int max = start < end ? end : start;
    for (int i = min; i < max; i++)
    {
        v.push_back(i);
    }
    return pipe<int>::of(v);
}

pipe<long> range(const long &start, const long &end)
{
    std::vector<long> v = {};
    long min = start < end ? start : end;
    long max = start < end ? end : start;
    for (long i = min; i < max; i++)
    {
        v.push_back(i);
    }
    return pipe<long>::of(v);
}

}; // namespace flow