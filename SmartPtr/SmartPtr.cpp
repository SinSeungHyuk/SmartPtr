// SmartPtr.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>

using namespace std;


class Resource {
    int* data;
    string s;
    shared_ptr<Resource> other;
    weak_ptr<Resource> w_other;
public:
    Resource() { data = new int[100]; cout << "리소스 획득\n"; }
    Resource(const string& s) { this->s = s; cout << "리소스 획득\n"; }
    ~Resource() { cout << "소멸자 호출\n"; delete[] data; }

    void prt() { cout << "출력함수 호출\n"; }
    void setOther(shared_ptr<Resource> o) {
        other = o;
    }
    void setW_Other(weak_ptr<Resource> o) {
        w_other = o;
    }
    void access_other() {
        shared_ptr<Resource> o = w_other.lock();
        if (o) { cout << "access : " << o->s << endl; }
        else { cout << "이미 파괴된 객체\n"; }
    }
};

void uPtrFunc(Resource* uptr) {
    uptr->prt();
}

int main()
{
    //unique_ptr<Resource> pRsc(new Resource());
    //cout << pRsc.get() << endl;

    //unique_ptr<Resource> pRsc2(move(pRsc)); // 소유권 이전

    //cout << pRsc2.get() << endl;
    //cout << pRsc.get() << endl; // pRsc.get() -> 주소 반환

    //uPtrFunc(pRsc2.get());
    // ===================================== unique_ptr


    //vector<shared_ptr<Resource>> vec;

    //vec.push_back(shared_ptr<Resource>(new Resource()));
    //vec.push_back(shared_ptr<Resource>(vec[0]));
    //vec.push_back(shared_ptr<Resource>(vec[1]));

    //cout << vec[0].use_count() << endl;
    //vec.erase(vec.begin());
    //cout << vec[0].use_count() << endl;
    //vec.erase(vec.begin());
    //cout << vec[0].use_count() << endl;
    //vec.erase(vec.begin());

    //Resource* r = new Resource();

    //shared_ptr<Resource> sp1(r);
    //cout << sp1.use_count() << endl;
    //shared_ptr<Resource> sp2(sp1);
    //cout << sp2.use_count() << endl;

    //shared_ptr<Resource> sp1(new Resource());
    //shared_ptr<Resource> sp2(new Resource());
    //sp1->setOther(sp2);
    //sp2->setOther(sp1); // 순환 참조
    // ====================================== shared_ptr
    

    shared_ptr<Resource> sp1(new Resource("sp1"));
    shared_ptr<Resource> sp2(new Resource("sp2"));
    
    sp1->setW_Other(sp2);
    sp2->setW_Other(sp1);

    sp2->access_other();

    sp1.~shared_ptr();
    sp2->access_other();


    cout << "main 종료\n\n";


    return 0;
}

