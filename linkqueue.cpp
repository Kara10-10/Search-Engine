
#include <iostream>
#include "linkqueue.h"
#include <pthread.h>
#include <unistd.h>
// ToDo: Move to compile options
#undef _TRACE

#ifdef _TRACE
#define Trace(msg) std::cout << msg << std::endl;
#else
#define Trace(msg);
#endif

void* msgReceiver(void* arg)
{
    Trace("Broadcaster thread started");
    linkQueue* LinkQueue = (linkQueue*)arg;
    while(true)
    {
        Trace("Waiting for link");
        pthread_cond_wait(&LinkQueue->condvar, &LinkQueue->mutex);
        Trace("Link received");
       // std::cout << "Queue size" << LinkQueue->_linkQueue.size() << std::endl;
        //std::cout << "Handler size" << LinkQueue->_handlers.size() << std::endl;
        pthread_t th;
       pthread_create(&th, NULL, HandlerInvoker, arg);
        pthread_mutex_unlock(&LinkQueue->mutex);
       // std։։cout << "Broadcasting link" << link << std::endl;
      
    }
}

void * HandlerInvoker(void * arg)
{
    linkQueue* LinkQueue = (linkQueue*)arg;

    while(LinkQueue -> _linkQueue.size())
    {
        pthread_mutex_lock(&LinkQueue->mutex);
         std::string link = LinkQueue->_linkQueue.front();
        Trace(link);
        LinkQueue->_linkQueue.pop();
        Trace("Link removed from queue");
        pthread_mutex_unlock(&LinkQueue->mutex);
       for(auto i = LinkQueue->_handlers.begin(); i != LinkQueue->_handlers.end(); ++i)
        {
            (*i)(link);
        }
    }
         
}

linkQueue::linkQueue()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condvar, NULL);
    pthread_create(&thread, NULL, msgReceiver, (void*)this);
 
    sleep(1);
}



void linkQueue::addLink(std::string link)
{
    Trace("Locking mutex");
    pthread_mutex_lock(&this->mutex);
    Trace("Adding link");
    this->_linkQueue.push(link);
    pthread_cond_signal(&this->condvar);
    Trace("Cond var is signaled");
    pthread_mutex_unlock(&this->mutex);

}

void linkQueue::registerHandler(linkHandler handler)
{
    this->_handlers.insert(handler);
}
