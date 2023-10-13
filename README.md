# c
An efficient tool to enchance c++ development.
+ > pipe  
  > A super powerful class to operate data group designed from ```java.util.stream.Stream```  
  + > @param E The type of internal elements.  
    ```c++  
    template <class E>
    ```  
  + Constructors  
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
        pipe<E> add(const E &element);  
        ```
      + > Tests if all element matahces the condition with given ```std::function<bool(E)>```  
        ```c++  
        //Tests if all elements are odd numbers.  
        flow::pipe<int> p = flow::range(0, 73);  
        bool predicate = p.allMatch([](const int &element)-> bool{  
            return element % 2 != 0;  
        });
        ```  
        > @param predicate Accepts a parameter from this pipe line and returns a ```bool```.  
        > @return Returns true only if all elements are tested and every time predicate returns true. Otherwise returns false.
        ```c++
        bool allMatch(const std::function<bool(E)> &predicate);  
        ```
      + > Tests if any element matahces the condition with given ```std::function<bool(E)>```.
      ```c++  
        //Tests if any element are odd numbers.  
        flow::pipe<int> p = flow::range(0, 73);  
        bool predicate = p.anyMatch([](const int &element)-> bool{  
            return element % 2 != 0;  
        });  
        ```  
