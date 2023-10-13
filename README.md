# c
An efficient tool to enchance c++ development.
+ > pipe  
  > A super powerful class to operate data group designed from ```java.util.stream.Stream```  
  + > @param E The type of internal elements.  
    ```c++  
    template <class E>
    ```  
  + Constructors
    + ```c++
      public:
      ``` 
      + > Creates a pipe line from a std::vector  
        ```c++
        pipe(const std::vector<E> &vector) : vector(vector){}  
        ```
      + > Deep clone from another pipe line.  
        ```c++  
        pipe(const pipe<E> &p) : vector({p.vector}{}
        ```
  + Members and methods  
    + ```c++
      protected:  
      ```  
      + > Container that stores elements.  
        ```c++
        const std::vector vector;
        ```
      + > Check the given index that is valid.  
        > @param index The index to be tested.  
        > @return Returns true if the given index is in range [0, this-> size()).  
        ```c++  
         bool checkIndex(const int &index);  
        ```
    + ```c++  
      public:  
      ```  
      + > Adds an element to the tail of the pipe line and returns a new one without operating this one.  
        > @param E The type of internal elements.  
        > @param element The element to be added into this pipe line.  
        > @return The pipe that contains the added element.  
        ```c++  
        pipe<E> add(const E &element) const;  
        ```  
      + > Tests if all element matahces the condition with given ```std::function<bool(E)>```  
        ```c++  
        //Tests if all elements are odd numbers.  
        flow::pipe<int> p = flow::range<int>(0, 73);  
        bool predicate = p.allMatch([](const int &element)-> bool{  
            return element % 2 != 0;  
        });
        ```  
        > @param predicate Accepts a parameter from this pipe line and returns a ```bool```.  
        > @return Returns true only if all elements are tested and every time predicate returns true. Otherwise returns false.
        ```c++
        bool allMatch(const std::function<bool(E)> &predicate) const; 
        ```
      + > Tests if any element matahces the condition with given ```std::function<bool(E)>```.
        ```c++  
          //Tests if any element is odd numbers.  
          flow::pipe<int> p = flow::range<int>(0, 73);  
          bool predicate = p.anyMatch([](const int &element)-> bool{  
           return element % 2 != 0;  
          });  
          ```  
          > @param predicate  Accepts elements from this pipe line and returna a ```bool```.  
          > @return returns ```true``` only if predicate returns ```true```.  
          ```c++  
          bool anyMatch(const std::function<bool(E)> &predicate) const;
          ```
      + >  Gets an element from given index that is limited in [0, this-> size().
        ```c++  
        flow::pipe<int> p = range<int>(0, 63); // size = 64  
        const int e = p.at(-1); // e = 63  index = p.size() + (-1).  
        const int e1 = p.at(65); // e = 0 index = 65 % p.size().
        ```
        > @param E The type of internal elements.  
        > @param index The index where to find element.  
        > @return The element at the target index.
        ```c++
        E &at(const int& index) const;  
        ```
      + >  Calculates the average value according to the summation with long value that converts from ```std::function<long(E)>```.  
        >  @param average Accepts element from this pipe line and convertes it into a long value returned.  
        >  @return The long value converted from the elements.  
        ```c++  
        double average(const std::function<long(E)> &average) const;  
        ```  
