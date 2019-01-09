#include <iostream>
#define ARRAY_LENGTH 100000

struct queue
{
    int key;
    float priority;
};

void display_queues(queue queues[], const int count)
{
    std::cout << "KEY\tPRIORITY" << std::endl;
    for (int i = 0; i < count; i++)
    {
        std::cout << queues[i].key << "\t" << queues[i].priority << std::endl;
    }
}

void display_queue(queue queue)
{
    std::cout << "KEY:" << queue.key << " PRIORITY:" << queue.priority << std::endl;
}

void max_heapify(queue a[], int i, int const count)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest;

    if (l < count && a[l].priority > a[i].priority)
    {
        largest = l;
    }
    else
    {
        largest = i;
    }

    if (r < count && a[r].priority > a[largest].priority)
    {
        largest = r;
    }

    if (largest != i)
    {
        queue temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        max_heapify(a, largest, count);
    }
}

void build_max_heap(queue a[], int const count)
{
    for (int i = (count - 1) / 2; i >= 0; i--)
    {
        max_heapify(a, i, count);
    }
}

queue max_heap(queue a[])
{
    return a[0];
}

queue heap_extract_max(queue a[], int const count)
{
    if (count <= 0)
    {
        std::cerr << "Heap Error" << std::endl;
        return queue();
    }
    queue max = a[0];
    a[0] = a[count - 1];
    max_heapify(a, 0, count - 1);
    return max;
}

void heap_insert_max(queue a[], queue queue, int const count_before_insert)
{
    if (count_before_insert > ARRAY_LENGTH)
    {
        std::cout << "Heap overflow!" << std::endl;
        return;
    }

    int i = count_before_insert;
    while (i > 0 && a[(i - 1) / 2].priority < queue.priority)
    {
        a[i] = a[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    a[i] = queue;
}

int main()
{
    std::cout << "Enter the number of queue : ";
    int count;
    std::cin >> count;
    if (count <= 0)
    {
        std::cout << "Enter a positive integer!" << std::endl;
        return -1;
    }

    queue queues[ARRAY_LENGTH];
    std::cout << "Enter the keys of queue : ";
    for (int i = 0; i < count; i++)
    {
        std::cin >> queues[i].key;
    }
    std::cout << "Enter the priorities of queue : ";
    for (int i = 0; i < count; i++)
    {
        std::cin >> queues[i].priority;
    }

    std::cout << "[current queues]" << std::endl;
    build_max_heap(queues, count);
    display_queues(queues, count);

    while (true)
    {
        std::cout << std::endl
                  << "[command]" << std::endl;
        std::cout << " i : insert" << std::endl;
        std::cout << " m : show the queue which has the max priority" << std::endl;
        std::cout << " e : show the queue which has the max priority and extract it" << std::endl;
        std::cout << " q : quit" << std::endl;
        std::cout << "Enter the command : ";
        char command;
        std::cin >> command;
        switch (command)
        {
        case 'i':
            std::cout << "Enter the key and priority to insert : ";
            queue queue;
            std::cin >> queue.key >> queue.priority;
            heap_insert_max(queues, queue, count++);
            std::cout << "[heapified]" << std::endl;
            display_queues(queues, count);
            break;
        case 'm':
            if (count >= 1)
            {
                std::cout << "[max-priority queue]" << std::endl;
                display_queue(max_heap(queues));
            }
            else
            {
                std::cout << "There is no queue." << std::endl;
            }
            break;
        case 'e':
            if (count >= 2)
            {
                std::cout << "[max-priority queue]" << std::endl;
                display_queue(heap_extract_max(queues, count--));
                std::cout << "[current queue]" << std::endl;
                display_queues(queues, count);
            }
            else if (count == 1)
            {
                std::cout << "[max-priority queue]" << std::endl;
                display_queue(heap_extract_max(queues, count--));
                std::cout << "[current queue]" << std::endl
                          << "NO QUEUE" << std::endl;
            }
            else
            {
                std::cout << "Couldn't extract! There is no queue left." << std::endl;
            }
            break;
        case 'q':
            return 0;
        default:
            continue;
        }
    }
}