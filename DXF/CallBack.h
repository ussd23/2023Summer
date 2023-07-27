#pragma once

class CCallBackBase
{
public:
    virtual void Interpret() {};
};

template <class ObjType, typename FuncType>
class CallBack : public CCallBackBase
{
public:
    CallBack(ObjType* p_Obj, FuncType p_Fun)
        : m_Obj(p_Obj), m_Fun(p_Fun) {}
    ~CallBack() {}

    void Interpret()
    {
        (m_Obj->*m_Fun)();
    }

private:
    ObjType* m_Obj;
    FuncType m_Fun;
};

template <class ObjType, typename FuncType>
CallBack<ObjType, FuncType>* SetProc(ObjType p_Obj, FuncType p_Fun)
{
    return new CallBack<ObjType, FuncType>(&p_Obj, p_Fun);
}
