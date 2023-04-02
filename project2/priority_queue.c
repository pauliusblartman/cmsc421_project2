
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
        long rv = clear_queue(_head->m_nextPid);
        free(_head->m_nextPid );
        _head->m_nextPid = NULL;
        return rv;
    }
    
}

long clear_tree(struct bst_node* _head)
{
    long rv = 0;
    if (_head->m_left != NULL)
    {
        rv = clear_tree(_head->m_left);
        free(_head->m_left );
        _head->m_left = NULL;
    }
    if (_head->m_right != NULL)
    {
        long rv = clear_tree(_head->m_right);
        free(_head->m_right );
        _head->m_right = NULL;
    }
    clear_queue(_head->m_headOfQueue);
    free(_head->m_headOfQueue);
    _head->m_headOfQueue == NULL;
    return;
}

/*Shuts down the queue system, deleting all existing queues and any PIDS contained therein. Returns 0 on success.*/
long pqueue_shutdown(void)
{
    clear_tree(m_bst_head);
    free(m_bst_head);
    m_bst_head = NULL;
}


long insert_node(struct bst_node* _head, const unsigned long priority)
{
    struct bst_node** insertionNode;
    if (_head->m_priority == priority)
        return NO_ERR;
    else if (_head->m_priority > priority)
    {
        if (_head->m_right != NULL)
            return insert_node(_head->m_right,priority);
        else
            insertionNode = _head->m_right;
    }
    else
    {
        if (_head->m_left != NULL)
            return insert_node(_head->m_left,priority);
        else
            insertionNode =  _head->m_left;
    }

    // create new node
     *insertionNode = (struct bst_node*)calloc(1,sizeof(struct bst_node));
     assert(*insertionNode != NULL);
     (*insertionNode )->m_priority = NULL;
     return 0;

}
/*Creates a new pqueue with the
given priority if it does not already exist (no duplicates are allowed). Returns 0 on success
or an appropriate error on failure.*/
long pqueue_create(unsigned long priority)
{
    return insert_node(m_bst_head, priority);
}



/*:	Deletes the pqueue identified
by priority if it exists. If the queue has any PIDs stored in it, they should be deleted.
Returns 0 on success or an appropriate error code on failure.*/
long pqueue_destroy(unsigned long priority)
{
    
}
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