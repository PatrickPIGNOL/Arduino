#ifndef LIST_H
#define LIST_H

template <typename T>
class List
{
    private:
        T** aItems;
        int aCount;
    public:
        List<T>();
        virtual ~List();
        void mAdd(T* pItem);
        void mInsert(T* pItem, int pIndex);
        int mIndexOf(T* pItem);
        T* operator [](int pIndex);
        T* mItem(int pIndex);
        void mItem(int pIndex, T* pItem);
        void mRemove(T* pItem);
        void mClear();
};

#endif
