const unsigned maxThreadCount = 6;
const unsigned maxTaskCount = 8;

void emptyTask() { }

void shortTask()
{
    volatile float total = 0.0f;
    for (int i = 0; i < 1024; ++i)
    {
        total += i;
        total *= 1.0f / (float)i;
    }
}

void longTask()
{
    volatile float total = 0.0f;
    for (int i = 0; i < 4096 * 4; ++i)
    {
        total += i;
        total *= 1.0f / (float)i;
    }
}

void testTasks(unsigned threadCount, unsigned taskCount, TaskAction action)
{
    TaskPool taskPool(threadCount);

    bool taskDone[maxTaskCount];
    std::vector<Task> tasks;

    for (unsigned i = 0; i < taskCount; ++i)
    {
        bool* thisTaskDone = &taskDone[i];
        tasks.push_back(taskPool.enqueue([action, thisTaskDone]
        {
            action();
            *thisTaskDone = true;
        }));
    }

    unsigned i = 0;
    for (auto& task : tasks)
    {
        task.wait();

        CHECK_EQUAL(true, taskDone[i]);
        CHECK_EQUAL(task.isDone(), taskDone[i++]);
    }
}

void testTasksWithErrors(unsigned threadCount, unsigned taskCount, TaskAction action)
{
    TaskPool taskPool(threadCount);

    std::vector<Task> tasks;

    for (unsigned i = 0; i < taskCount; ++i)
    {
        tasks.push_back(taskPool.enqueue([action]
        {
            action();
            throw Error("Task error");
        }));
    }

    for (auto& task : tasks)
    {
        bool errorThrown = false;
        try
        {
            task.wait();
        }
        catch (Error&)
        {
            errorThrown = true;
        }

        CHECK_EQUAL(true, errorThrown);
    }
}

#define TEST_TASKS(action)\
    for (unsigned threadCount = 0; threadCount < maxThreadCount; ++threadCount) {\
        for (unsigned taskCount = 1; taskCount < maxTaskCount; ++taskCount) {\
            testTasks(threadCount, taskCount, action);\
        }\
    }

#define TEST_TASKS_WITH_ERRORS(action)\
    for (unsigned threadCount = 0; threadCount < maxThreadCount; ++threadCount) {\
        for (unsigned taskCount = 1; taskCount < maxTaskCount; ++taskCount) {\
            testTasksWithErrors(threadCount, taskCount, action);\
        }\
    }

SUITE(TaskPool)
{
    TEST(EmptyTasks)
    {
        TEST_TASKS(emptyTask);
    }

    TEST(ShortTasks)
    {
        TEST_TASKS(shortTask);
    }

    TEST(LongTasks)
    {
        TEST_TASKS(longTask);
    }

    TEST(EmptyTasksWithErrors)
    {
        TEST_TASKS_WITH_ERRORS(emptyTask);
    }

    TEST(ShortTasksWithErrors)
    {
        TEST_TASKS_WITH_ERRORS(shortTask);
    }

    TEST(LongTasksWithErrors)
    {
        TEST_TASKS_WITH_ERRORS(longTask);
    }
}