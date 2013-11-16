#pragma once

namespace hect
{

///
/// An action for a task to execute.
typedef std::function<void()> TaskAction;

///
/// A handle for an enqueued task.
class Task
{
    friend class TaskPool;
public:

    ///
    /// Creates an empty task.
    Task();

    ///
    /// Waits until the task has completed.
    ///
    /// \throws Error If an error occurred while executing the task's action.
    void wait();

    ///
    /// Returns whether the task is done.
    bool isDone() const;

private:
    struct Data
    {
        TaskAction action;
        std::atomic<bool> done;
        bool errorOccurred;
        Error error;
    };

    Task(const std::shared_ptr<Data>& data);

    std::shared_ptr<Data> _data;
};

///
/// Provides the functionality for executing asynchronous tasks.
class TaskPool :
    public Uncopyable
{
public:

    ///
    /// Constructs a task pool with a specific number of worker threads.
    ///
    /// \param threadCount The number of worker threads.
    TaskPool(size_t threadCount);

    ///
    /// Waits until all running tasks complete (ignores any enqueued tasks
    /// remaining).
    ~TaskPool();

    ///
    /// Enqueues a task to be executed asynchronously.
    ///
    /// \param action The action for the task to perform.
    ///
    /// \returns The queued task.
    Task enqueue(TaskAction action);

private:
    void _initializeThreads(size_t threadCount);
    void _threadLoop();

    std::deque<Task> _taskQueue;

    std::vector<std::thread> _threads;

    std::mutex _queueMutex;
    std::condition_variable _condition;
    bool _stop;
};

}