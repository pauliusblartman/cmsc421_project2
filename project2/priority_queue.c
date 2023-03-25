
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <assert.h>



struct priority_queue_node
{
    struct priority_queue_node* m_nextPid;
    long m_pid;
};

struct bst_node
{
    long m_priority;
    struct priority_queue_node* m_headOfQueue;
    struct bst_node* m_left;
    struct bst_node* m_right;
};


//const variables
const int MAX_NODES = 100;
const long NO_ERR;

// global variables
struct bst_node * m_bst_head = NULL;


/*long pqueue_init(void):	Initializes the queue system, setting up the initial state of the
Binary Search Tree. You may initialize the Binary Search Tree by adding the root node
which is the priority of the first node in the queue. Return 0 on success.
*/

long pqueue_init(void)
{
    // initialize the bst by creating an empty list
    long rv = pqueue_create((MAX_NODES + 1)/2);
    return rv;
}

long clear_queue(struct priority_queue_node* _head)
{
    if (_head->m_nextPid == NULL)
        return NO_ERR;
    else
    {
        long rv = clear_queue(_head->m_nextPid == NULL);
        free(_head->m_nextPid );
        _head->m_nextPid = NULL;
        return rv;
    }
    
}

long clear_tree(struct bst_node* _head)
{
    if (_head->m_left == NULL)
        return NO_ERR;
    else
    {
        long rv = clear_queue(_head->m_nextPid == NULL);
        free(_head->m_nextPid );
        _head->m_nextPid = NULL;
        return;
    }
}

/*Shuts down the queue system, deleting all existing queues and any PIDS contained therein. Returns 0 on success.*/
long pqueue_shutdown(void)
{

}

long pqueue_create(unsigned long priority):	Creates a new pqueue with the
given priority if it does not already exist (no duplicates are allowed). Returns 0 on success
or an appropriate error on failure.
long pqueue_destroy(unsigned long priority):	Deletes the pqueue identified
by priority if it exists. If the queue has any PIDs stored in it, they should be deleted.
Returns 0 on success or an appropriate error code on failure.
long pqueue_count(unsigned long priority):	Print the number of PIDS in the
queue to the system log identified by priority if it exists. Returns an appropriate error code
on failure.
long pqueue_send(unsigned long priority, unsigned long PID):	Sends a new
PID to the queue identified by priority if it exists. Put at the back of the queue. Returns 0
on success or an appropriate error code on failure.
long pqueue_recv(unsigned long priority):	Reads the PID that is at the top of the
FIFO queue identified by priority if it exists. The priority and PID are written to the
system log. The PID is not deleted. An appropriate return code is issued if the priority
does not exist. Note: this might be helpful for debugging.
long pqueue_delete(unsigned long priority):	Reads the PID that is at the top of
the FIFO queue identified by priority if it exists. The priority and PID are written to the
system log. The PID is deleted. An appropriate return code is issued if the priority does
not exist.