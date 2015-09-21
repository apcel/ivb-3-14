#pragma once
#include "MyVector.h" // Объявление структуры класса

////////menu/////////////
template<typename __Type>
void MyVector<__Type>::sort(SortType type) // Сортирока указанным методом
  {
    switch (type) {
      case Insertion:
      {
        sortInsertion();//
        break;
      }
      case Bubble:
      {
        sortBubble();// Сортировка пузырьком
        break;
      }
      case Count:
      {
          sortCount();
          break;
      }
    }
  };

template<typename __Type>
int MyVector<__Type>::find(FindType type, __Type keyIn) // Поиск указанным методом
  {
      this->key = keyIn;
    switch (type) {
      case   Binary:
      {
          return findBinary();
      }
      case  Interpolation:
      {
          return findInterpolation();
      }
    }
  };
///////////////////сортировка///////////////////////////////
template<typename __Type>
void MyVector<__Type>::sortBubble() //поплавок.
    {
      size_t i, j;
      bool flag = true;// признак наличия перестановок
      size_t numLength = this->size(); // размер вектора
      nswap = 0; // количество перестановок
      for(i = 1; (i <= numLength) && flag; i++) {
        flag = false;
          for (j = 0; j < (numLength - 1); j++) {
            if ((*this)[j + 1] < (*this)[j]) {
              nswap++;
              temp = (*this)[j];
              (*this)[j] = (*this)[j + 1];
              (*this)[j + 1] = temp;
              flag = true; // Перестановка произошла
            }
          }
        }
      };

template<typename __Type>
void MyVector<__Type>::sortInsertion() //вставок.
    {
        nswap=0;
        for(int i = 0; i < this->size(); i++) {
            for(int j = i; (j > 0) && ( (*this)[j-1] > (*this)[j] ); j--) {
                nswap++;
                int temp=(*this)[j-1];
                (*this)[j-1]=(*this)[j];
                (*this)[j]=temp;
            }
        }
    }

template<typename __Type>
void MyVector<__Type>::sortCount() //подсчётом.
    {
        nswap = 0;
        sortCountMinMax();
        std::vector<__Type> tempVector ((countMax - countMin) + 1, 0u);
        auto k = this->begin();
        for (auto i = k; i != this->end(); ++i) {
            ++tempVector[*i - countMin];
            nswap++;
        }
        for (auto i = countMin; i <= countMax; ++i) {
            for (auto j = 0; j < tempVector[i - countMin]; ++j) {
                 nswap++;
                *k++ = i;
            }
        }

    }
/////////////////////Поиск////////////////////////////////
template<typename __Type>
int MyVector<__Type>::findBinary()
    {
        nview=0;
        int left=0;
        int right=this->size();
        int mid;
        while(left < right) {
            nview++;
            mid=left+(right-left)/2;
            if (key < (*this)[mid]) right=mid-1;
            else if (key > (*this)[mid]) left=mid+1;
            else return mid;
        }
        return -1;
    }


template<typename __Type>
int MyVector<__Type>::findInterpolation()
    {
        nview=0;
        int left=0;
        int right=this->size()-1;
        int mid;

        while ((*this)[left]<=key && (*this)[right]>=key) {
            nview++;
            mid=left+((key-(*this)[left])*(right-left))/((*this)[right]-(*this)[left]);
            if ((*this)[mid]<key) left=mid+1;
            else if ((*this)[mid]>key) right=mid-1;
            else return mid;
        }
        if ((*this)[left]==key) return left;
        else return -1;
    }
/////////////////////helpers/////////////////////////////

template<typename __Type>
void MyVector<__Type>::sortCountMinMax()
    {
        countMin=(*this)[0];
        countMax=countMin;
        for(int i = 1; i < this->size(); i++) {
            if(countMin > (*this)[i])
                countMin = (*this)[i];
            if(countMax < (*this)[i])
                countMax = (*this)[i];
        }
    }


template<typename __Type>
void MyVector<__Type>::fillWithRandomNumbers(int n)
    {
        n -= this->size();
        for (auto i = 0; i < n; i++) {
            this->push_back(random(apcel_RAND_MIN,apcel_RAND_MAX));
        }
    }

template<typename __Type>
int MyVector<__Type>::random(int a, int b)
{
    int u=rand(); // от 0 до RAND_MAX (2^16)
    return a+u%(b-a); // для b>a
};



template<typename __Type>
std::ostream &operator << (std::ostream &output, const MyVector<__Type> &v)//вывод вектора
{
  int i = 0;
  typename MyVector<__Type>::const_iterator it = v.begin();
  while( it != v.end() ) {
    if ( i > 0 )
      std::cout << " ";
    std::cout << (*it);
    ++it;
    ++i;
  }
  return output;
};
