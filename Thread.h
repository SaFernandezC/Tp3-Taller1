#ifndef _THREAD_H
#define _THREAD_H

#include <thread>

class Thread {
  private:
    std::thread thread;

  public:
    Thread();

    void start();

    void join();

    virtual void run() = 0;   //Virtual puro para
                          //forzar que lo defina cada clase hija

    virtual ~Thread();

    Thread(Thread&& other);
    Thread& operator=(Thread&& other);

  private:
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

};

#endif
