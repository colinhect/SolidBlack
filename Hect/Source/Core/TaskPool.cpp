#include "Hect.h"

using namespace hect;

Task::Task()
{
}

void Task::wait()
{
    if (!_data)
    {
        return;
    }

    Task::Data* data = _data.get();
    while (!data->done)
    {
        std::this_thread::yield();
    }

    // Re-throw the error if one occurred
    if (data->errorOccurred)
    {
        throw data->error;
    }
}

bool Task::isDone() const
{
    if (!_data)
    {
        return true;
    }

    Task::Data* data = _data.get();
    return data->done;
}

Task::Task(const std::shared_ptr<Data>& data) :
    _data(data)
{
}

TaskPool::TaskPool(size_t threadCount) :
    _stop(false)
{
    _initializeThreads(threadCount);
}

TaskPool::~TaskPool()
{
    // Notify all threads that the pool is stopping
    {
        std::unique_lock<std::mutex> lock(_queueMutex);
        _stop = true;
        _condition.notify_all();
    }

    // Join all of the threads
    for (std::thread& thread : _threads)
    {
        thread.join();
    }
}

Task TaskPool::enqueue(TaskAction action)
{
    // Create the task data
    auto data = std::make_shared<Task::Data>();
    data->action = action;
    data->done = false;
    data->errorOccurred = false;

    // Create the task
    Task task(data);

    if (_threads.empty())
    {
        // The task pool has no threads so execute the action synchronously
        try
        {
            action();
        }
        catch (Error& error)
        {
            data->errorOccurred = true;
            data->error = error;
        }

        data->done = true;
    }
    else
    {
        // Add this task to the queue
        {
            std::unique_lock<std::mutex> lock(_queueMutex);
            _taskQueue.push_back(task);
        }

        // Notify one of the threads that a new task is available
        _condition.notify_one();
    }

    return task;
}

void TaskPool::_initializeThreads(size_t threadCount)
{
    for (unsigned i = 0; i < threadCount; ++i)
    {
        _threads.push_back(std::thread([this]
        {
            _threadLoop();
        }));
    }
}

void TaskPool::_threadLoop()
{
    while (true)
    {
        Task task;

        {
            std::unique_lock<std::mutex> lock(_queueMutex);

            while (!_stop && _taskQueue.empty())
            {
                _condition.wait(lock);
            }

            if (_stop)
            {
                return;
            }

            // Get the next task
            task = _taskQueue.front();
            _taskQueue.pop_front();
        }

        // Execute the task
        Task::Data* data = task._data.get();
        if (data)
        {
            try
            {
                data->action();
            }
            catch (Error& error)
            {
                data->errorOccurred = true;
                data->error = error;
            }

            data->done = true;
        }
    }
}