#pragma once

// The purpose of our queue is to manage scheduling.
//
// We manage this by providing different functions for manipulating the PCB
// queue, which are each useful for various policies. 
//
// interpreter.h provides two functions:
//  1. run_pcb_to_completion
//  2. run_pcb_for_n_steps
//
// The schedule_policy.{h,c} file defines a 'schedule_policy' struct which
// contains pointers to the functions which will appropriately implement
// the tasks required by a particular policy. This allows us to expose a common
// interface, shared by all policies, that can be used to actually execute
// scripts. The details are handled in schedule_policy.c and interpreter.c.


// defined before because schedule_policy.h requires this definition.
struct queue;

#include "schedule_policy.h"


// Notes/aside: a probably a better plan would be to make a separate
// `struct scheduler` which contains both a policy and a queue,
// and provides policy independent interfaces to everything in the schedule_policy
// and not just the queue stuff.

// All of our policies share a single queue type. If that weren't the case,
// we could add alloc/dealloc functions to the policy struct and replace
// struct queue pointers with void pointers everywhere.

struct queue *alloc_queue();
void free_queue(struct queue *q);

// To determine if processes have the same name, we need a way of scanning
// the queue contents for a given filename.
int program_already_scheduled(struct queue *q, char *name);

// This particular function is policy independent, but its interface matches
// the regular enqueue function just to keep things clean.
void enqueue_ignoring_priority(struct queue *q, struct PCB *pcb);

// FCFS, RR
void enqueue_fcfs(struct queue *q, struct PCB *pcb);
// SJF
void enqueue_sjf(struct queue *q, struct PCB *pcb);
// Aging
// enqueue_sjf is almost correct, but we should leave the given pcb at the head
// if it's tied with the current head, rather than doing an FCFS tiebreak.
void enqueue_aging(struct queue *q, struct PCB *pcb);

// FCFS, RR, SJF
struct PCB *dequeue_typical(struct queue *q);
// Aging
struct PCB *dequeue_aging(struct queue *q);
