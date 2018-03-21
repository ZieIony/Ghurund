#pragma once

#include "Collection.h"
#include "Array.h"

namespace Ghurund {

    template<class Value, class Key = size_t>class ObjectArray:List<Value*, Key> {
    public:
        ObjectArray() {
            memset(v, 0, sizeof(Value*)*capacity);
        }
        ObjectArray(const ObjectArray &t1) {
            capacity = t1.capacity;
            initial = t1.initial;
            size = t1.size;
            v = ghnew Value*[capacity];
            memcpy(v, t1.v, sizeof(v));
            for(Key i = 0; i<size; i++)
                v[i]->addReference();
        }
        ~ObjectArray() {
            for(Key i = 0; i<size; i++)
                v[i]->release();
        }
        /*
        inline void resize(Key c){//if c<size some items will be lost, cannot resize to less than 1 item
        for(Key i=c;i<size;i++)
        ((Pointer*)v[i])->release();
        Key c2=max<Key>(c,1);
        Value *t1=ghnew Value[c2];
        memcpy(t1,v,min(c,size)*sizeof(Value));
        memset(t1+min(c,size),0,(c2-min(c,size))*sizeof(Value));
        capacity=c2;
        size=min(size,c);
        delete []v;
        v=t1;
        }
        */
        inline void add(Value *e) {//allows to add null item
            if(size==capacity)
                resize(capacity+initial);
            e->addReference();
            v[size] = e;
            size++;
            return;
        }
        inline void set(Key i, Value *e) {
            e->addReference();
            v[i]->release();
            v[i] = e;
        }
        inline Value *get(Key i)const {
            v[i]->addReference();
            return v[i];
        }
        inline void remove(Key i) {
            v[i]->release();
            v[i] = v[size-1];
            size--;
        }
        /* Value &operator[](Key i){	// trzeba uwa?a? przy przypisaniu
        ((Pointer*)v[i])->addReference();
        return v[i];
        }
        const  Value &operator[](Key i)const{
        return v[i];
        }*/
        inline void clear() {
            for(Key i = 0; i<size; i++)
                v[i]->release();
            size = 0;
        }

        inline Key find(Value *item) {
            for(Key i = 0; i<size; i++)
                if(v[i]->equals(item))
                    return i;
            return size;
        }

        inline bool contains(Value *item) {
            for(Key i = 0; i<size; i++)
                if(v[i]->equals(item))
                    return true;
            return false;
        }
    };

}