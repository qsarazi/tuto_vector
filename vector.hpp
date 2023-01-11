
#ifndef VECTOR_H
 #define VECTOR_H

namespace tuto
{  
   template<class T> // Template permet une abstraction du type

 class vector{
   private:
      T * tab = nullptr;
      unsigned int size_tab = 0;
    
   public:
    vector() = default; /* Constructeur */
    
    T *data() /*Fonction 1*/
    { 
       return tab;
     };

    void push_back(const T &val )
    {
        T * tab_l = nullptr;
       /*A la premiere fois */
       if(size_tab == 0)
       {
          tab = new T[size_tab +1];
          tab[size_tab] = val;
          (size_tab) ++; 
       }
       else
       { 
        tab_l = new T[size_tab +1];
        tab_l[size_tab] = val;
       
        for (unsigned int i = 0; i <size_tab; i++)
        {
        tab_l[i] = tab[i];
        }
        /* Trés important l'idée est d'évité la fuite de mémoire aprés de appelle successif */
        delete tab_l; 
        (size_tab) ++;

        tab = tab_l;
       } 
 
    }
     
     T size()
     {
      /* size_tab is the number of element in your vector*/
       return (size_tab);
     }
    /*ça c'est magique la déclarer c'est pour acceder en [] dans les fct */
     T & operator[](unsigned int index)
     {
      T & v = tab[index];
      return v;
     }

     ~vector()
     {
      delete tab;
     };
 };
}
  /*template<class T>
   T* vector<T>::data()
   {
   }*/


#endif /* VECTOR_H*/

