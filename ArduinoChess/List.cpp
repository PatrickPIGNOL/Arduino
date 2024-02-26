#include "List.h"

template<typename T>
List<T>::List()
{
    this->aCount = 0;
    this->aItems = new T*[this.aCount];
}

template<typename T>
List<T>::~List()
{
    this->mClear();
    delete[](this->aItems);
}

template<typename T>
void List<T>::mAdd(T* pItem)
{
    T** vTemp = new T* [this->aCount + 1];
    unsigned int vIndex = 0;
    while(vIndex < this.aCount)
    {
        vTemp[vIndex] = this->aItems[vIndex];
        vIndex++;
    }
    vTemp[vIndex] = pItem;
    delete[] (this->aItems);
    this->aItems = vTemp;
    this->aCount++;
}

template<typename T>
void List<T>::mInsert(T* pItem, int pIndex)
{
    T** vTemp = new T* [this->aCount + 1];
    unsigned int vIndex = 0;
    while(vIndex < pIndex)
    {
        vTemp[vIndex] = this->aItems[vIndex];
        vIndex++;
    }
    vTemp[vIndex] = pItem;
    vIndex++;
    while(vIndex - 1 < this->aCount)
    {
        vTemp[vIndex] = this->aItems[vIndex - 1];
        vIndex++;
    }
    delete[] (this->aItems);
    this->aItems = vTemp;
    this->aCount++;
}

template<typename T>
int List<T>::mIndexOf(T* pItem)
{
    int vIndex = 0;
    while
    (
        (this->aItems[vIndex] != pItem)
        &&
        (vIndex < this->aCount)
    )
    {
        vIndex++;
    }
    if(vIndex >= this->aCount)
    {
        return -1;
    }
    return vIndex;
}

template<typename T>
T* List<T>::mItem(int pIndex)
{
    return this->aItems[pIndex];
}

template<typename T>
void List<T>::mItem(int pIndex, T* pItem)
{
    this->aItems[pIndex] = pItem;
}

template<typename T>
T* List<T>::operator[](int pIndex)
{
    return this->aItems[pIndex];
}

template<typename T>
void List<T>::mRemove(T* pItem)
{
    T** vTemp = new T* [this->aCount - 1];
    unsigned int vIndex = 0;
    while(this->aItems[vIndex] != pItem)
    {
        vTemp[vIndex] = this->aItems[vIndex];
        vIndex++;
    }
    vIndex++;
    while(vIndex < this->aCount)
    {
        vTemp[vIndex - 1] = this->aItems[vIndex];
        vIndex++;
    }
    delete[] (this->aItems);
    this->aItems = vTemp;
    this->aCount--;
}

template<typename T>
void List<T>::mClear()
{
    delete[](this->aItems);
    this->aItems = new T*[0];
    this->aCount = 0;
}
