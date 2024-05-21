#ifndef DISCARDSTACK_H
#define DISCARDSTACK_H

class stack{
private:
    myList myStack;
public:
    stack(){

    }

    void push(int item){
        myStack.prepend(item);
    }
    int pop(){
        myStack.start();
        return myStack.removeCurrent();
    }
    int peek(){
        myStack.start();
        return myStack.getCurrentValue();
    }

    ~stack(){
        for(int i = 0; i < myStack.getLength(); i++){
            myStack.removeCurrent();
        }
    }

};

#endif // DISCARDSTACK_H
