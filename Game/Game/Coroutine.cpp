#include "pch.h"
#include "Coroutine.h"

using namespace std;

Coroutine::Coroutine(coroutine_handle<promise_type> handle) :
    co_handler_(handle)
{
}

Coroutine::~Coroutine()
{
    if (co_handler_)
    {
        co_handler_.destroy();
    }
}
