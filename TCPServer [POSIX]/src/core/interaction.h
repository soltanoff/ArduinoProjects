#ifndef INTERACTION_H
#define INTERACTION_H
/* ================================================================================================================== */
class CBaseInteractionClass {
public:
    virtual int exec() = 0;
    virtual void close() = 0;

    ~CBaseInteractionClass() = default;
protected:
    virtual bool get_answer(int& bytesRecv, char* answer) = 0;
    virtual bool send_message(const char* msg) = 0;
};
/* ================================================================================================================== */
#endif /* INTERACTION_H */
